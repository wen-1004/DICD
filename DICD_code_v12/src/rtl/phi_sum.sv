`include "include/data_type.svh"

module phi_sum (
    input  logic clk,
    input  logic rst,  // ACTIVE-HIGH reset (matches reset_signal_is(rst, true))

    input  r_t   r_k_in_real,
    input  r_t   r_k_in_imag,
    input  r_t   r_k_minus_N_in_real,
    input  r_t   r_k_minus_N_in_imag,

    input  rho_t rho_in,

    output phi_t phi_out
);
    import data_type::*;

    localparam int L_CONST_PHI = 16;

    // Energy delay line (each entry is phi_t Q6.8)
    phi_t delay_line [0:L_CONST_PHI-1];

    phi_t current_sum, current_sum_next;
    phi_t phi_out_reg, phi_out_reg_next;

    // -------------------------
    // Fixed-point helpers (raw math)
    // -------------------------
    // r_t is Q1.6 => raw signed 7-bit
    logic signed [R_W-1:0] rk_re_raw, rk_im_raw, rkmN_re_raw, rkmN_im_raw;
    logic signed [RHO_W-1:0] rho_raw;

    assign rk_re_raw   = r_k_in_real;
    assign rk_im_raw   = r_k_in_imag;
    assign rkmN_re_raw = r_k_minus_N_in_real;
    assign rkmN_im_raw = r_k_minus_N_in_imag;
    assign rho_raw     = rho_in;

    // Squares: raw*raw => Q2.12 (because 6+6 frac)
    logic signed [2*R_W-1:0] rk_re_sq_raw12, rk_im_sq_raw12;
    logic signed [2*R_W-1:0] rkmN_re_sq_raw12, rkmN_im_sq_raw12;

    assign rk_re_sq_raw12   = rk_re_raw   * rk_re_raw;
    assign rk_im_sq_raw12   = rk_im_raw   * rk_im_raw;
    assign rkmN_re_sq_raw12 = rkmN_re_raw * rkmN_re_raw;
    assign rkmN_im_sq_raw12 = rkmN_im_raw * rkmN_im_raw;

    // Convert square to phi Q6.8 raw:
    // from Q?.12 to Q?.8 => >>> 4
    logic [PHI_W+3:0] rk_re_sq_phi, rk_im_sq_phi;
    logic [PHI_W+3:0] rkmN_re_sq_phi, rkmN_im_sq_phi;

    assign rk_re_sq_phi     = $unsigned(rk_re_sq_raw12   >>> 4);
    assign rk_im_sq_phi     = $unsigned(rk_im_sq_raw12   >>> 4);
    assign rkmN_re_sq_phi   = $unsigned(rkmN_re_sq_raw12 >>> 4);
    assign rkmN_im_sq_phi   = $unsigned(rkmN_im_sq_raw12 >>> 4);

    // |r|^2 in phi domain
    logic [PHI_W+4:0] r_k_sq_phi_full, r_kmN_sq_phi_full;
    assign r_k_sq_phi_full   = rk_re_sq_phi   + rk_im_sq_phi;
    assign r_kmN_sq_phi_full = rkmN_re_sq_phi + rkmN_im_sq_phi;

    // rho_half (keep Q1.7 scaling)
    logic signed [RHO_W-1:0] rho_half_raw;
    assign rho_half_raw = rho_raw >>> 1;

    // sum of squares (Q6.8 raw-ish)
    logic [PHI_W+5:0] sum_sq_phi_full;
    assign sum_sq_phi_full = r_k_sq_phi_full + r_kmN_sq_phi_full;

    // energy = rho_half * sum_sq
    // rho_half Q1.7, sum_sq Q6.8 => product frac=15
    // back to Q6.8 => >>> 7
    logic signed [RHO_W + (PHI_W+6) - 1:0] energy_prod_full;
    logic signed [PHI_W+6:0] energy_phi_full;

    assign energy_prod_full =
        $signed(rho_half_raw) * $signed({1'b0, sum_sq_phi_full});

    assign energy_phi_full = energy_prod_full >>> RHO_FRAC;

    // Truncate/wrap to phi_t width like SystemC default behavior
    phi_t energy_to_sum;
    assign energy_to_sum = energy_phi_full[PHI_W-1:0];

    // Oldest energy
    phi_t old_energy;
    assign old_energy = delay_line[L_CONST_PHI-1];

    // Next-state sum (use a wider signed intermediate)
    logic signed [PHI_W:0] sum_calc;
    always_comb begin
        sum_calc = $signed({1'b0, current_sum})
                 + $signed({1'b0, energy_to_sum})
                 - $signed({1'b0, old_energy});
        current_sum_next = sum_calc[PHI_W-1:0];

        // 1-cycle delayed output semantics
        phi_out_reg_next = current_sum_next;
    end

    // -------------------------
    // Sequential
    // -------------------------
    integer i;
    always_ff @(posedge clk) begin
        if (rst) begin
            for (i = 0; i < L_CONST_PHI; i++) begin
                delay_line[i] <= '0;
            end
            current_sum  <= '0;
            phi_out_reg  <= '0;
            phi_out      <= '0;
        end else begin
            // output previous registered sum (matches SystemC)
            phi_out <= phi_out_reg;

            // update running sum
            current_sum <= current_sum_next;

            // shift delay line AFTER reading old_energy conceptually
            for (i = L_CONST_PHI-1; i > 0; i--) begin
                delay_line[i] <= delay_line[i-1];
            end
            delay_line[0] <= energy_to_sum;

            // update output register with new sum
            phi_out_reg <= phi_out_reg_next;
        end
    end

endmodule