`include "../include/data_type.svh"

module gamma_sum (
    input  logic clk,
    input  logic rst,  // ACTIVE-HIGH, synchronous

    input  r_t   r_k_in_real,
    input  r_t   r_k_in_imag,
    input  r_t   r_k_minus_N_in_real,
    input  r_t   r_k_minus_N_in_imag,

    output gamma_t gamma_out_real,
    output gamma_t gamma_out_imag
);
    // -------------------------
    // Parameters
    // -------------------------
    localparam int L_CONST    = 16;
    localparam int PROD_SHIFT = (2*R_FRAC - GAMMA_FRAC); // 12-8 = 4

    // -------------------------
    // Window state
    // -------------------------
    gamma_t delay_line_real [0:L_CONST-1];
    gamma_t delay_line_imag [0:L_CONST-1];
    gamma_t current_sum_real;
    gamma_t current_sum_imag;

    // =========================================================
    // 3-stage REAL pipeline (no output-only delay buffer)
    //
    // S1: 4 multipliers (Q1.6 * Q1.6 => Q2.12)
    // S2: add/sub in Q2.12, then truncate ONCE to Q6.8 (gamma_t)
    // S3: update 16-cycle window sum and output
    // =========================================================

    // -------------------------
    // S1 regs: Q2.12 partial products
    // -------------------------
    logic signed [2*R_W-1:0] ac_mul12_s1, bd_mul12_s1, bc_mul12_s1, ad_mul12_s1;

    // -------------------------
    // S2 regs: final products in Q6.8
    // -------------------------
    gamma_t product_real_s2;
    gamma_t product_imag_s2;

    // -------------------------
    // S2 combinational: sum/diff in Q2.12 with guard bit
    // -------------------------
    logic signed [2*R_W:0] prod_real_raw12_w;
    logic signed [2*R_W:0] prod_imag_raw12_w;

    assign prod_real_raw12_w = $signed(ac_mul12_s1) + $signed(bd_mul12_s1);
    assign prod_imag_raw12_w = $signed(bc_mul12_s1) - $signed(ad_mul12_s1);

    // -------------------------
    // S3 combinational: window update math
    // -------------------------
    wire gamma_t old_real_w = delay_line_real[L_CONST-1];
    wire gamma_t old_imag_w = delay_line_imag[L_CONST-1];

    logic signed [GAMMA_W:0] sum_calc_real_w;
    logic signed [GAMMA_W:0] sum_calc_imag_w;

    assign sum_calc_real_w =
        $signed({current_sum_real[GAMMA_W-1], current_sum_real}) +
        $signed({product_real_s2[GAMMA_W-1],  product_real_s2 }) -
        $signed({old_real_w[GAMMA_W-1],       old_real_w      });

    assign sum_calc_imag_w =
        $signed({current_sum_imag[GAMMA_W-1], current_sum_imag}) +
        $signed({product_imag_s2[GAMMA_W-1],  product_imag_s2 }) -
        $signed({old_imag_w[GAMMA_W-1],       old_imag_w      });

    wire gamma_t new_sum_real_w = gamma_t'(sum_calc_real_w);
    wire gamma_t new_sum_imag_w = gamma_t'(sum_calc_imag_w);

    // -------------------------
    // Stage 1: register multipliers
    // -------------------------
    always_ff @(posedge clk) begin
        if (rst) begin
            ac_mul12_s1 <= '0;
            bd_mul12_s1 <= '0;
            bc_mul12_s1 <= '0;
            ad_mul12_s1 <= '0;
        end else begin
            ac_mul12_s1 <= $signed(r_k_in_real)         * $signed(r_k_minus_N_in_real);
            bd_mul12_s1 <= $signed(r_k_in_imag)         * $signed(r_k_minus_N_in_imag);
            bc_mul12_s1 <= $signed(r_k_in_imag)         * $signed(r_k_minus_N_in_real);
            ad_mul12_s1 <= $signed(r_k_in_real)         * $signed(r_k_minus_N_in_imag);
        end
    end

    // -------------------------
    // Stage 2: register products
    // IMPORTANT: truncate ONCE after add/sub
    // -------------------------
    always_ff @(posedge clk) begin
        if (rst) begin
            product_real_s2 <= '0;
            product_imag_s2 <= '0;
        end else begin
            product_real_s2 <= gamma_t'(prod_real_raw12_w >>> PROD_SHIFT);
            product_imag_s2 <= gamma_t'(prod_imag_raw12_w >>> PROD_SHIFT);
        end
    end

    // -------------------------
    // Stage 3: update sliding window + output
    // -------------------------
    integer i;
    always_ff @(posedge clk) begin
        if (rst) begin
            for (i = 0; i < L_CONST; i++) begin
                delay_line_real[i] <= '0;
                delay_line_imag[i] <= '0;
            end
            current_sum_real <= '0;
            current_sum_imag <= '0;
            gamma_out_real   <= '0;
            gamma_out_imag   <= '0;
        end else begin
            // shift window history
            for (i = L_CONST-1; i > 0; i--) begin
                delay_line_real[i] <= delay_line_real[i-1];
                delay_line_imag[i] <= delay_line_imag[i-1];
            end
            delay_line_real[0] <= product_real_s2;
            delay_line_imag[0] <= product_imag_s2;

            // update running sums
            current_sum_real <= new_sum_real_w;
            current_sum_imag <= new_sum_imag_w;

            // 3rd stage register = visible output
            gamma_out_real <= new_sum_real_w;
            gamma_out_imag <= new_sum_imag_w;
        end
    end

endmodule
