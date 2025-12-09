`include "../include/data_type.svh"
import data_type::*;
`include "angle.sv"
`include "argmax.sv"
`include "delay_n.sv"
`include "gamma_sum.sv"
`include "mag.sv"
`include "minus.sv"
`include "phi_sum.sv"


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

    logic [9:0] count;

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
        .count     (count),
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

    logic isPassBarrier;
    always_ff @(posedge clk or posedge rst) begin
        if (rst) begin
            isPassBarrier <= 1'b0;
        end else begin
            if (count == 10'd0) begin
                isPassBarrier <= 1'b1;
            end else begin
                isPassBarrier <= isPassBarrier;
            end
        end
    end
    assign out_valid = (count == 10'd0) && (isPassBarrier == 1'b1);

endmodule
