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
    // 4-stage "normally distributed" AMBM |x + jy|
    //
    // S1: abs + max/min + left=min<<8
    // S2: rightk=max*SEGk + segment compare -> seg_idx
    // S3: alpha/beta mux + 2 mult + >>>AMBM_FRAC -> term_a/term_b
    // S4: add only -> mag_out reg
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
    // S1: abs + max/min + left=min<<8
    // ============================================================
    gamma_t x0, y0;
    gamma_t ax0, ay0;
    gamma_t max0, min0;

    assign x0  = gm_in_real;
    assign y0  = gm_in_imag;

    assign ax0 = x0[GAMMA_W-1] ? gamma_t'(-$signed(x0)) : x0;
    assign ay0 = y0[GAMMA_W-1] ? gamma_t'(-$signed(y0)) : y0;

    assign max0 = ($signed(ax0) >= $signed(ay0)) ? ax0 : ay0;
    assign min0 = ($signed(ax0) >= $signed(ay0)) ? ay0 : ax0;

    logic [GAMMA_W-1:0] max_u0, min_u0;
    assign max_u0 = max0;
    assign min_u0 = min0;

    logic [GAMMA_W+8-1:0] left1_c;
    assign left1_c = {min_u0, 8'b0};

    // S1 registers
    gamma_t               max_s1, min_s1;
    logic [GAMMA_W-1:0]   max_u1;
    logic [GAMMA_W+8-1:0] left1;
    logic                 max_zero1;

    always_ff @(posedge clk) begin
        if (rst) begin
            max_s1     <= '0;
            min_s1     <= '0;
            max_u1     <= '0;
            left1      <= '0;
            max_zero1  <= 1'b1;
        end else begin
            max_s1     <= max0;
            min_s1     <= min0;
            max_u1     <= max_u0;
            left1      <= left1_c;
            max_zero1  <= (max_u0 == '0);
        end
    end

    // ============================================================
    // S2: rightk=max*SEGk + segment compare -> seg_idx
    // ============================================================
    logic [GAMMA_W+8-1:0] right0_c, right1_c, right2_c, right3_c;
    logic [GAMMA_W+8-1:0] right4_c, right5_c, right6_c, right7_c;

    assign right0_c = max_u1 * SEG0;
    assign right1_c = max_u1 * SEG1;
    assign right2_c = max_u1 * SEG2;
    assign right3_c = max_u1 * SEG3;
    assign right4_c = max_u1 * SEG4;
    assign right5_c = max_u1 * SEG5;
    assign right6_c = max_u1 * SEG6;
    assign right7_c = max_u1 * SEG7;

    // segment index:
    // 0..7 -> ALPHA/BETA 0..7
    // 8    -> default ALPHA/BETA 8 (r >= SEG7)
    // 9    -> special for max==0 (force 0)
    logic [3:0] seg_idx_c;

    always_comb begin
        seg_idx_c = 4'd8; // default

        if (max_zero1) begin
            seg_idx_c = 4'd9;
        end
        else if (left1 < right0_c) seg_idx_c = 4'd0;
        else if (left1 < right1_c) seg_idx_c = 4'd1;
        else if (left1 < right2_c) seg_idx_c = 4'd2;
        else if (left1 < right3_c) seg_idx_c = 4'd3;
        else if (left1 < right4_c) seg_idx_c = 4'd4;
        else if (left1 < right5_c) seg_idx_c = 4'd5;
        else if (left1 < right6_c) seg_idx_c = 4'd6;
        else if (left1 < right7_c) seg_idx_c = 4'd7;
    end

    // S2 registers
    logic [3:0] seg_idx_s2;
    gamma_t     max_s2, min_s2;

    always_ff @(posedge clk) begin
        if (rst) begin
            seg_idx_s2 <= 4'd9;
            max_s2     <= '0;
            min_s2     <= '0;
        end else begin
            seg_idx_s2 <= seg_idx_c;
            max_s2     <= max_s1;
            min_s2     <= min_s1;
        end
    end

    // ============================================================
    // S3: alpha/beta mux + 2 mult + shift -> term regs
    // ============================================================
    ambm_t alpha_s3_c, beta_s3_c;

    always_comb begin
        // default for seg_idx 8
        alpha_s3_c = ALPHA8;
        beta_s3_c  = BETA8;

        unique case (seg_idx_s2)
            4'd0: begin alpha_s3_c = ALPHA0; beta_s3_c = BETA0; end
            4'd1: begin alpha_s3_c = ALPHA1; beta_s3_c = BETA1; end
            4'd2: begin alpha_s3_c = ALPHA2; beta_s3_c = BETA2; end
            4'd3: begin alpha_s3_c = ALPHA3; beta_s3_c = BETA3; end
            4'd4: begin alpha_s3_c = ALPHA4; beta_s3_c = BETA4; end
            4'd5: begin alpha_s3_c = ALPHA5; beta_s3_c = BETA5; end
            4'd6: begin alpha_s3_c = ALPHA6; beta_s3_c = BETA6; end
            4'd7: begin alpha_s3_c = ALPHA7; beta_s3_c = BETA7; end
            4'd9: begin alpha_s3_c = '0;     beta_s3_c  = '0;    end
            default: ; // keep ALPHA8/BETA8
        endcase
    end

    logic signed [AMBM_W+GAMMA_W-1:0] prod_a_full_c, prod_b_full_c;
    assign prod_a_full_c = $signed(alpha_s3_c) * $signed(max_s2);
    assign prod_b_full_c = $signed(beta_s3_c)  * $signed(min_s2);

    logic signed [MAG_W:0] term_a_c, term_b_c;
    assign term_a_c = $signed(prod_a_full_c >>> AMBM_FRAC);
    assign term_b_c = $signed(prod_b_full_c >>> AMBM_FRAC);

    // S3 registers
    logic signed [MAG_W:0] term_a_s3, term_b_s3;

    always_ff @(posedge clk) begin
        if (rst) begin
            term_a_s3 <= '0;
            term_b_s3 <= '0;
        end else begin
            term_a_s3 <= term_a_c;
            term_b_s3 <= term_b_c;
        end
    end

    // ============================================================
    // S4: add only -> mag_out reg
    // ============================================================
    logic signed [MAG_W:0] z_sum_c;
    assign z_sum_c = term_a_s3 + term_b_s3;

    always_ff @(posedge clk) begin
        if (rst) begin
            mag_out <= '0;
        end else begin
            mag_out <= mag_t'(z_sum_c[MAG_W-1:0]);
        end
    end

endmodule

