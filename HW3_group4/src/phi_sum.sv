`include "../include/data_type.svh"

module phi_sum (
    input  logic clk,
    input  logic rst,  // ACTIVE-HIGH, synchronous

    input  r_t   r_k_in_real,
    input  r_t   r_k_in_imag,
    input  r_t   r_k_minus_N_in_real,
    input  r_t   r_k_minus_N_in_imag,
    input  rho_t rho_in,

    output phi_t phi_out
);
    import data_type::*;

    localparam int L_CONST_PHI = 16;
    localparam int SQ_SHIFT    = (2*R_FRAC - PHI_FRAC); // 12-8 = 4
    localparam int EXTRA_OUT_LAT = 3; // add 3 cycles to phi_out
    localparam rho_t RHO_CONST = 8'sb01111111;

    // -------------------------
    // Sliding window state
    // -------------------------
    phi_t delay_line [0:L_CONST_PHI-1];
    phi_t current_sum;

    // -------------------------
    // Stage 1 regs (Q2.12 squares)
    // -------------------------
    logic signed [2*R_W-1:0] a_re_sq12_s1, a_im_sq12_s1;
    logic signed [2*R_W-1:0] b_re_sq12_s1, b_im_sq12_s1;
    rho_t                    rho_s1;

    // -------------------------
    // Stage 2 regs (Q6.8 mags)
    // -------------------------
    phi_t r_k_sq_s2;
    phi_t r_kmN_sq_s2;
    rho_t rho_half_s2;

    // -------------------------
    // Stage 3 reg (Q6.8 energy)
    // -------------------------
    phi_t energy_to_sum_s3;

    // -------------------------
    // Extra output delay regs
    // -------------------------
    phi_t phi_out_d1, phi_out_d2, phi_out_d3;

    // -------------------------
    // Valid mask for delay line tail
    // 0 means "treat old value as 0"
    // -------------------------
    logic [L_CONST_PHI-1:0] valid_sr;

    always_ff @(posedge clk) begin
        if (rst) begin
            valid_sr <= '0;
        end else begin
            valid_sr <= {valid_sr[L_CONST_PHI-2:0], 1'b1};
        end
    end

    // -------------------------
    // Stage 2 combinational wires
    // Sum squares in Q2.12 FIRST, then truncate once
    // -------------------------
    logic signed [2*R_W:0] a_sum_sq12_w;
    logic signed [2*R_W:0] b_sum_sq12_w;

    assign a_sum_sq12_w = $signed(a_re_sq12_s1) + $signed(a_im_sq12_s1);
    assign b_sum_sq12_w = $signed(b_re_sq12_s1) + $signed(b_im_sq12_s1);

    // -------------------------
    // Stage 3 combinational wires
    // -------------------------
    logic signed [PHI_W:0] sum_sq_ext_w;
    assign sum_sq_ext_w =
        $signed({r_k_sq_s2[PHI_W-1],   r_k_sq_s2  }) +
        $signed({r_kmN_sq_s2[PHI_W-1], r_kmN_sq_s2});

    logic signed [RHO_W + (PHI_W+1) - 1:0] energy_prod_w;
    // assign energy_prod_w = $signed(rho_half_s2) * $signed(sum_sq_ext_w);
    // 63 * sum = (sum << 6) - sum  (exact, no early truncation)
    logic signed [PHI_W+6:0] sum_mul63_w;
    assign sum_mul63_w  = ($signed(sum_sq_ext_w) <<< 6) - $signed(sum_sq_ext_w);
    
    // Keep the same signal name/width so the rest of your pipeline is untouched
    assign energy_prod_w = $signed(sum_mul63_w);


    // -------------------------
    // Stage 4 combinational wires
    // -------------------------
    wire phi_t old_energy_raw = delay_line[L_CONST_PHI-1];
    wire phi_t old_energy_w = valid_sr[L_CONST_PHI-1] ? old_energy_raw : '0;

    logic signed [PHI_W:0] sum_calc_w;
    assign sum_calc_w =
        $signed({current_sum[PHI_W-1],      current_sum     }) +
        $signed({energy_to_sum_s3[PHI_W-1], energy_to_sum_s3}) -
        $signed({old_energy_w[PHI_W-1],     old_energy_w    });

    wire phi_t new_sum_w = phi_t'(sum_calc_w);

    // -------------------------
    // S1: square + rho pipe
    // -------------------------
    always_ff @(posedge clk) begin
        if (rst) begin
            a_re_sq12_s1 <= '0; a_im_sq12_s1 <= '0;
            b_re_sq12_s1 <= '0; b_im_sq12_s1 <= '0;
            rho_s1       <= '0;
        end else begin
            a_re_sq12_s1 <= $signed(r_k_in_real)         * $signed(r_k_in_real);
            a_im_sq12_s1 <= $signed(r_k_in_imag)         * $signed(r_k_in_imag);
            b_re_sq12_s1 <= $signed(r_k_minus_N_in_real) * $signed(r_k_minus_N_in_real);
            b_im_sq12_s1 <= $signed(r_k_minus_N_in_imag) * $signed(r_k_minus_N_in_imag);
            rho_s1       <= RHO_CONST;
        end
    end

    // -------------------------
    // S2: sum squares -> Q6.8, align rho_half
    // -------------------------
    always_ff @(posedge clk) begin
        if (rst) begin
            r_k_sq_s2   <= '0;
            r_kmN_sq_s2 <= '0;
            rho_half_s2 <= '0;
        end else begin
            r_k_sq_s2   <= phi_t'(a_sum_sq12_w >>> SQ_SHIFT);
            r_kmN_sq_s2 <= phi_t'(b_sum_sq12_w >>> SQ_SHIFT);
            rho_half_s2 <= $signed(rho_s1) >>> 1;
        end
    end

    // -------------------------
    // S3: energy = rho_half * (r_k_sq + r_kmN_sq)
    // Back to Q6.8 by >>> RHO_FRAC
    // -------------------------
    always_ff @(posedge clk) begin
        if (rst) begin
            energy_to_sum_s3 <= '0;
        end else begin
            energy_to_sum_s3 <= phi_t'(energy_prod_w >>> RHO_FRAC);
        end
    end

    // -------------------------
    // S4: sliding window accumulate
    // + 3-cycle EXTRA output delay
    // -------------------------
    integer i;
    always_ff @(posedge clk) begin
        if (rst) begin
            current_sum <= '0;

            phi_out_d1 <= '0;
            phi_out_d2 <= '0;
            phi_out_d3 <= '0;
            phi_out    <= '0;
        end else begin
            // update internal sum (keep algorithm timing unchanged)
            current_sum <= new_sum_w;

            // extra output pipeline (adds 3 cycles)
            phi_out_d1 <= new_sum_w;
            phi_out_d2 <= phi_out_d1;
            phi_out_d3 <= phi_out_d2;
            phi_out    <= phi_out_d3;
        end
    end

    always_ff @(posedge clk) begin
            // shift window
            for (i = L_CONST_PHI-1; i > 0; i--)
                delay_line[i] <= delay_line[i-1];
            delay_line[0] <= energy_to_sum_s3;

    end



endmodule
