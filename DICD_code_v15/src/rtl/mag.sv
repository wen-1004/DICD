`include "../include/data_type.svh"

module mag (
    input  logic   clk,
    input  logic   rst,        // ACTIVE-HIGH, synchronous

    input  gamma_t gm_in_real,
    input  gamma_t gm_in_imag,

    output mag_t   mag_out
);
    import data_type::*;

    // ------------------------------------------------------------
    // 5-stage pipelined AMBM |x + jy| approximation
    //
    // S1: abs + max/min
    // S2: cross-multiply terms
    // S3: segment compare -> alpha/beta
    // S4a: compute prod_a_full / prod_b_full (REGISTER)
    // S4b: shift + add -> mag_out (REGISTER)
    // ------------------------------------------------------------

    // -------------------------
    // Segment thresholds (ratio_t Q0.8)
    // -------------------------
    localparam ratio_t SEG0 = 8'b00011001;
    localparam ratio_t SEG1 = 8'b00110011;
    localparam ratio_t SEG2 = 8'b01001110;
    localparam ratio_t SEG3 = 8'b01101010;
    localparam ratio_t SEG4 = 8'b10001001;
    localparam ratio_t SEG5 = 8'b10101011;
    localparam ratio_t SEG6 = 8'b11001000;
    localparam ratio_t SEG7 = 8'b11010010;

    // -------------------------
    // alpha/beta LUTs (ambm_t Q2.8)
    // -------------------------
    localparam ambm_t ALPHA0 = 10'sb01_00110011;
    localparam ambm_t ALPHA1 = 10'sb00_11111110;
    localparam ambm_t ALPHA2 = 10'sb00_11111010;
    localparam ambm_t ALPHA3 = 10'sb00_11110011;
    localparam ambm_t ALPHA4 = 10'sb00_11101010;
    localparam ambm_t ALPHA5 = 10'sb00_11011111;
    localparam ambm_t ALPHA6 = 10'sb00_11010001;
    localparam ambm_t ALPHA7 = 10'sb00_11010001;
    localparam ambm_t ALPHA8 = 10'sb00_10110101;

    localparam ambm_t BETA0  = 10'sb00_00000110;
    localparam ambm_t BETA1  = 10'sb00_00011111;
    localparam ambm_t BETA2  = 10'sb00_00111000;
    localparam ambm_t BETA3  = 10'sb00_01010000;
    localparam ambm_t BETA4  = 10'sb00_01101000;
    localparam ambm_t BETA5  = 10'sb00_01111110;
    localparam ambm_t BETA6  = 10'sb00_10010011;
    localparam ambm_t BETA7  = 10'sb00_10010011;
    localparam ambm_t BETA8  = 10'sb00_10110100;

    // ============================================================
    // S1: abs + max/min
    // ============================================================
    gamma_t x0, y0, ax0, ay0, max0, min0;

    assign x0  = gm_in_real;
    assign y0  = gm_in_imag;

    assign ax0 = x0[GAMMA_W-1] ? gamma_t'(-$signed(x0)) : x0;
    assign ay0 = y0[GAMMA_W-1] ? gamma_t'(-$signed(y0)) : y0;

    assign max0 = ($signed(ax0) >= $signed(ay0)) ? ax0 : ay0;
    assign min0 = ($signed(ax0) >= $signed(ay0)) ? ay0 : ax0;

    gamma_t max_s1, min_s1;
    logic [GAMMA_W-1:0] max_u1, min_u1;

    always_ff @(posedge clk) begin
        if (rst) begin
            max_s1 <= '0; min_s1 <= '0;
            max_u1 <= '0; min_u1 <= '0;
        end else begin
            max_s1 <= max0; min_s1 <= min0;
            max_u1 <= max0; min_u1 <= min0;
        end
    end

    // ============================================================
    // S2: cross-multiply terms
    // ============================================================
    logic [GAMMA_W+8-1:0] left2_c;
    logic [GAMMA_W+8-1:0] right0_c, right1_c, right2_c, right3_c;
    logic [GAMMA_W+8-1:0] right4_c, right5_c, right6_c, right7_c;
    logic                 max_zero_c;

    assign left2_c    = {min_u1, 8'b0};
    assign right0_c   = max_u1 * SEG0;
    assign right1_c   = max_u1 * SEG1;
    assign right2_c   = max_u1 * SEG2;
    assign right3_c   = max_u1 * SEG3;
    assign right4_c   = max_u1 * SEG4;
    assign right5_c   = max_u1 * SEG5;
    assign right6_c   = max_u1 * SEG6;
    assign right7_c   = max_u1 * SEG7;
    assign max_zero_c = (max_u1 == '0);

    logic [GAMMA_W+8-1:0] left2;
    logic [GAMMA_W+8-1:0] right0_2, right1_2, right2_2, right3_2;
    logic [GAMMA_W+8-1:0] right4_2, right5_2, right6_2, right7_2;
    logic                 max_zero2;
    gamma_t               max_s2, min_s2;

    always_ff @(posedge clk) begin
        if (rst) begin
            left2 <= '0;
            right0_2 <= '0; right1_2 <= '0; right2_2 <= '0; right3_2 <= '0;
            right4_2 <= '0; right5_2 <= '0; right6_2 <= '0; right7_2 <= '0;
            max_zero2 <= 1'b1;
            max_s2 <= '0; min_s2 <= '0;
        end else begin
            left2 <= left2_c;
            right0_2 <= right0_c; right1_2 <= right1_c; right2_2 <= right2_c; right3_2 <= right3_c;
            right4_2 <= right4_c; right5_2 <= right5_c; right6_2 <= right6_c; right7_2 <= right7_c;
            max_zero2 <= max_zero_c;
            max_s2 <= max_s1; min_s2 <= min_s1;
        end
    end

    // ============================================================
    // S3: segment compare -> alpha/beta
    // ============================================================
    ambm_t alpha3_c, beta3_c;

    always_comb begin
        alpha3_c = ALPHA8;
        beta3_c  = BETA8;

        if (max_zero2) begin
            alpha3_c = '0; beta3_c = '0;
        end
        else if (left2 < right0_2) begin alpha3_c = ALPHA0; beta3_c = BETA0; end
        else if (left2 < right1_2) begin alpha3_c = ALPHA1; beta3_c = BETA1; end
        else if (left2 < right2_2) begin alpha3_c = ALPHA2; beta3_c = BETA2; end
        else if (left2 < right3_2) begin alpha3_c = ALPHA3; beta3_c = BETA3; end
        else if (left2 < right4_2) begin alpha3_c = ALPHA4; beta3_c = BETA4; end
        else if (left2 < right5_2) begin alpha3_c = ALPHA5; beta3_c = BETA5; end
        else if (left2 < right6_2) begin alpha3_c = ALPHA6; beta3_c = BETA6; end
        else if (left2 < right7_2) begin alpha3_c = ALPHA7; beta3_c = BETA7; end
    end

    ambm_t alpha_s3, beta_s3;
    gamma_t max_s3, min_s3;

    always_ff @(posedge clk) begin
        if (rst) begin
            alpha_s3 <= '0; beta_s3 <= '0;
            max_s3 <= '0;   min_s3 <= '0;
        end else begin
            alpha_s3 <= alpha3_c;
            beta_s3  <= beta3_c;
            max_s3   <= max_s2;
            min_s3   <= min_s2;
        end
    end

    // ============================================================
    // S4a: compute products (REGISTER HERE)
    // ============================================================
    logic signed [AMBM_W+GAMMA_W-1:0] prod_a_full_w, prod_b_full_w;
    assign prod_a_full_w = $signed(alpha_s3) * $signed(max_s3);
    assign prod_b_full_w = $signed(beta_s3)  * $signed(min_s3);

    logic signed [AMBM_W+GAMMA_W-1:0] prod_a_full_s4;
    logic signed [AMBM_W+GAMMA_W-1:0] prod_b_full_s4;

    always_ff @(posedge clk) begin
        if (rst) begin
            prod_a_full_s4 <= '0;
            prod_b_full_s4 <= '0;
        end else begin
            prod_a_full_s4 <= prod_a_full_w;
            prod_b_full_s4 <= prod_b_full_w;
        end
    end

    // ============================================================
    // S4b: shift + add -> mag_out
    // ============================================================
    logic signed [MAG_W:0] term_a_q68_w;
    logic signed [MAG_W:0] term_b_q68_w;

    assign term_a_q68_w = $signed(prod_a_full_s4 >>> AMBM_FRAC);
    assign term_b_q68_w = $signed(prod_b_full_s4 >>> AMBM_FRAC);

    logic signed [MAG_W:0] z_sum_q68_w;
    assign z_sum_q68_w = term_a_q68_w + term_b_q68_w;

    always_ff @(posedge clk) begin
        if (rst) begin
            mag_out <= '0;
        end else begin
            mag_out <= mag_t'(z_sum_q68_w[MAG_W-1:0]);
        end
    end

endmodule
