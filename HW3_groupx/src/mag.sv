`include "../include/data_type.svh"

module mag (
    input  logic   clk,
    input  logic   rst,        // assume ACTIVE-HIGH, synchronous (matches your recent RTL)

    input  gamma_t gm_in_real,
    input  gamma_t gm_in_imag,

    output mag_t   mag_out
);
    // ------------------------------------------------------------
    // This RTL implements the same AMBM piecewise |x + jy| idea
    // as your SystemC ambm_pw_hypot_fx(), with 1-cycle latency.
    //
    // Key truncation rule preserved:
    //   - Avoid early truncation on segment decision math.
    //   - alpha/beta are Q2.8 (ambm_t), ax/ay are Q6.8 (gamma_t).
    //   - (alpha_raw * ax_raw) >>> 8 returns a Q6.8-scaled raw.
    //
    // Hardware efficiency:
    //   - NO divider for r = ay/ax.
    //   - Segment selection uses cross-multiply compare:
    //       r < k/256  <=>  (ay_raw << 8) < (ax_raw * k)
    //     where k is the 8-bit ratio threshold.
    // ------------------------------------------------------------

    // -------------------------
    // Segment thresholds (ratio_t Q0.8)
    // Use EXACT bit patterns from your SystemC literals.
    // NOTE: segment[5] comment in SC looked inconsistent with bits;
    //       we follow the literal (0b0.10101011 = 0xAB).
    // -------------------------
    localparam ratio_t SEG0 = 8'b00011001; // 0.00011001
    localparam ratio_t SEG1 = 8'b00110011; // 0.00110011
    localparam ratio_t SEG2 = 8'b01001110; // 0.01001110
    localparam ratio_t SEG3 = 8'b01101010; // 0.01101010
    localparam ratio_t SEG4 = 8'b10001001; // 0.10001001
    localparam ratio_t SEG5 = 8'b10101011; // 0.10101011 (as written)
    localparam ratio_t SEG6 = 8'b11001000; // 0.11001000
    localparam ratio_t SEG7 = 8'b11010010; // 0.11010010

    // -------------------------
    // alpha/beta LUTs (ambm_t Q2.8)
    // Encoded as raw Q2.8 bit patterns to match SystemC strings.
    // 10 bits: [9]=sign, [8]=int bit, [7:0]=frac
    // -------------------------
    localparam ambm_t ALPHA0 = 10'sb01_00110011; // 1.00110011
    localparam ambm_t ALPHA1 = 10'sb00_11111110; // 0.11111110
    localparam ambm_t ALPHA2 = 10'sb00_11111010; // 0.11111010
    localparam ambm_t ALPHA3 = 10'sb00_11110011; // 0.11110011
    localparam ambm_t ALPHA4 = 10'sb00_11101010; // 0.11101010
    localparam ambm_t ALPHA5 = 10'sb00_11011111; // 0.11011111
    localparam ambm_t ALPHA6 = 10'sb00_11010001; // 0.11010001
    localparam ambm_t ALPHA7 = 10'sb00_11010001; // 0.11010001
    localparam ambm_t ALPHA8 = 10'sb00_10110101; // 0.10110101

    localparam ambm_t BETA0  = 10'sb00_00000110; // 0.00000110
    localparam ambm_t BETA1  = 10'sb00_00011111; // 0.00011111
    localparam ambm_t BETA2  = 10'sb00_00111000; // 0.00111000
    localparam ambm_t BETA3  = 10'sb00_01010000; // 0.01010000
    localparam ambm_t BETA4  = 10'sb00_01101000; // 0.01101000
    localparam ambm_t BETA5  = 10'sb00_01111110; // 0.01111110
    localparam ambm_t BETA6  = 10'sb00_10010011; // 0.10010011
    localparam ambm_t BETA7  = 10'sb00_10010011; // 0.10010011
    localparam ambm_t BETA8  = 10'sb00_10110100; // 0.10110100

    // -------------------------
    // Absolute values and max/min selection
    // -------------------------
    gamma_t x_s, y_s;
    gamma_t ax_s, ay_s;
    gamma_t max_s, min_s;

    assign x_s  = gm_in_real;
    assign y_s  = gm_in_imag;

    // abs for signed fixed raw vectors
    assign ax_s = x_s[GAMMA_W-1] ? gamma_t'(-$signed(x_s)) : x_s;
    assign ay_s = y_s[GAMMA_W-1] ? gamma_t'(-$signed(y_s)) : y_s;

    assign max_s = ($signed(ax_s) >= $signed(ay_s)) ? ax_s : ay_s;
    assign min_s = ($signed(ax_s) >= $signed(ay_s)) ? ay_s : ax_s;

    // Treat magnitudes as unsigned raw for ratio compares
    wire logic [GAMMA_W-1:0] max_u = max_s;
    wire logic [GAMMA_W-1:0] min_u = min_s;

    // -------------------------
    // Segment decision with cross-multiply:
    //   r < k/256  <=>  (min_raw << 8) < (max_raw * k)
    // -------------------------
    logic [GAMMA_W+8-1:0] left_min_x256;
    assign left_min_x256 = {min_u, 8'b0};

    logic [GAMMA_W+8-1:0] right0, right1, right2, right3, right4, right5, right6, right7;
    assign right0 = max_u * SEG0;
    assign right1 = max_u * SEG1;
    assign right2 = max_u * SEG2;
    assign right3 = max_u * SEG3;
    assign right4 = max_u * SEG4;
    assign right5 = max_u * SEG5;
    assign right6 = max_u * SEG6;
    assign right7 = max_u * SEG7;

    // -------------------------
    // Alpha/Beta selection
    // -------------------------
    ambm_t alpha_sel;
    ambm_t beta_sel;

    always_comb begin
        // defaults (r >= SEG7)
        alpha_sel = ALPHA8;
        beta_sel  = BETA8;

        if (max_u == '0) begin
            alpha_sel = '0;
            beta_sel  = '0;
        end
        else if (left_min_x256 < right0) begin
            alpha_sel = ALPHA0; beta_sel = BETA0;
        end
        else if (left_min_x256 < right1) begin
            alpha_sel = ALPHA1; beta_sel = BETA1;
        end
        else if (left_min_x256 < right2) begin
            alpha_sel = ALPHA2; beta_sel = BETA2;
        end
        else if (left_min_x256 < right3) begin
            alpha_sel = ALPHA3; beta_sel = BETA3;
        end
        else if (left_min_x256 < right4) begin
            alpha_sel = ALPHA4; beta_sel = BETA4;
        end
        else if (left_min_x256 < right5) begin
            alpha_sel = ALPHA5; beta_sel = BETA5;
        end
        else if (left_min_x256 < right6) begin
            alpha_sel = ALPHA6; beta_sel = BETA6;
        end
        else if (left_min_x256 < right7) begin
            alpha_sel = ALPHA7; beta_sel = BETA7;
        end
    end

    // -------------------------
    // Compute z = alpha*max + beta*min
    // Raw multiply scaling:
    //   alpha_sel is Q2.8, max_s is Q6.8
    //   product raw has frac 16
    //   >>> AMBM_FRAC (8) => back to Q6.8 raw
    // -------------------------
    logic signed [AMBM_W+GAMMA_W-1:0] prod_a_full;
    logic signed [AMBM_W+GAMMA_W-1:0] prod_b_full;

    assign prod_a_full = $signed(alpha_sel) * $signed(max_s);
    assign prod_b_full = $signed(beta_sel)  * $signed(min_s);

    logic signed [MAG_W:0] term_a_q68;
    logic signed [MAG_W:0] term_b_q68;

    assign term_a_q68 = $signed(prod_a_full >>> AMBM_FRAC);
    assign term_b_q68 = $signed(prod_b_full >>> AMBM_FRAC);

    logic signed [MAG_W:0] z_sum_q68;
    assign z_sum_q68 = term_a_q68 + term_b_q68;

    wire mag_t z_w = mag_t'(z_sum_q68[MAG_W-1:0]);

    // -------------------------
    // 1-cycle latency output register
    // -------------------------
    always_ff @(posedge clk) begin
        if (rst) begin
            mag_out <= '0;
        end else begin
            mag_out <= z_w;
        end
    end

endmodule

