`include "include/data_type.svh"

module top (
    input  logic   clk,
    input  logic   rst,
    input  logic   in_valid,
    input  in_r_t  rx_re_in,
    input  in_r_t  rx_img_in,
    input  rho_t   rho,
    output theta_t theta,
    output eps_t   epsilon,
    output logic   out_valid
);
    import data_type::*;

    // -------------------------
    // Fixed system constants
    // -------------------------
    localparam int N          = 256;
    localparam int L          = 16;
    localparam int PIPE_DELAY = 12;

    localparam int FIRST_SAMPLES = 2*N + L; // 528
    localparam int STEP_SAMPLES  = N;       // 256

    // -------------------------
    // Internal signals
    // -------------------------
    r_t     r_d1_real, r_d1_imag;
    r_t     r_dN_out_real, r_dN_out_imag;

    phi_t   phi_out_s;

    gamma_t gamma_out_real_s, gamma_out_imag_s;

    mag_t   mag_out_s;
    ang_t   ang_out_s;

    lambda_t lambda_out_s;

    theta_t theta_sig_s;
    eps_t   epsilon_sig_s;

    // -------------------------
    // Instances
    // -------------------------
    delay_n U_DELAY_N (
        .clk           (clk),
        .rst           (rst),
        .r_in_real     (rx_re_in),
        .r_in_imag     (rx_img_in),
        .r_d1_real     (r_d1_real),
        .r_d1_imag     (r_d1_imag),
        .r_dN_out_real (r_dN_out_real),
        .r_dN_out_imag (r_dN_out_imag)
    );

    phi_sum U_PHI_SUM (
        .clk                 (clk),
        .rst                 (rst),
        .r_k_in_real         (r_d1_real),
        .r_k_in_imag         (r_d1_imag),
        .r_k_minus_N_in_real (r_dN_out_real),
        .r_k_minus_N_in_imag (r_dN_out_imag),
        .rho_in              (rho),
        .phi_out             (phi_out_s)
    );

    gamma_sum U_GAMMA_SUM (
        .clk                 (clk),
        .rst                 (rst),
        .r_k_in_real         (r_d1_real),
        .r_k_in_imag         (r_d1_imag),
        .r_k_minus_N_in_real (r_dN_out_real),
        .r_k_minus_N_in_imag (r_dN_out_imag),
        .gamma_out_real      (gamma_out_real_s),
        .gamma_out_imag      (gamma_out_imag_s)
    );

    mag U_MAG (
        .clk        (clk),
        .rst        (rst),
        .gm_in_real (gamma_out_real_s),
        .gm_in_imag (gamma_out_imag_s),
        .mag_out    (mag_out_s)
    );

    angle U_ANGLE (
        .clk        (clk),
        .rst        (rst),
        .gm_in_real (gamma_out_real_s),
        .gm_in_imag (gamma_out_imag_s),
        .ang_out    (ang_out_s)
    );

    minus U_MINUS (
        .clk        (clk),
        .rst        (rst),
        .mag_in     (mag_out_s),
        .phi_in     (phi_out_s),
        .rho_in     (rho),
        .lambda_out (lambda_out_s)
    );

    argmax U_ARGMAX (
        .clk       (clk),
        .rst       (rst),
        .angle_in  (ang_out_s),
        .lambda_in (lambda_out_s),
        .theta_out (theta_sig_s),
        .eps_out   (epsilon_sig_s)
    );

    // -------------------------
    // Drive top-level outputs
    // -------------------------
    assign theta   = theta_sig_s;
    assign epsilon = epsilon_sig_s;

    // -------------------------
    // out_valid generation
    // boundary at sample counts:
    //   528, 784, 1040, ...
    // pulse delayed by 12 cycles
    // -------------------------
    int unsigned sample_cnt;
    logic boundary_pulse;

    // Since STEP_SAMPLES = 256 (power of two),
    // we can avoid % by using a mask.
    localparam int STEP_MASK = STEP_SAMPLES - 1; // 255

    always_ff @(posedge clk) begin
        if (rst) begin
            sample_cnt     <= 0;
            boundary_pulse <= 1'b0;
        end else begin
            boundary_pulse <= 1'b0;

            if (in_valid) begin
                sample_cnt <= sample_cnt + 1;

                // check "next" count for precise 1-cycle pulse
                // next = sample_cnt + 1
                if ((sample_cnt + 1) >= FIRST_SAMPLES) begin
                    // boundary if (next - FIRST_SAMPLES) is multiple of 256
                    if (((sample_cnt + 1 - FIRST_SAMPLES) & STEP_MASK) == 0)
                        boundary_pulse <= 1'b1;
                end
            end
        end
    end

    // 12-cycle delay line for valid
    logic [PIPE_DELAY-1:0] vpipe;

    always_ff @(posedge clk) begin
        if (rst) begin
            vpipe <= '0;
        end else begin
            vpipe <= {vpipe[PIPE_DELAY-2:0], boundary_pulse};
        end
    end

    assign out_valid = vpipe[PIPE_DELAY-1];

endmodule
