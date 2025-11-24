`include "include/data_type.svh"

module top#(
    parameter INT_BITS = 1,  
    parameter FRAC_BITS = 15,
    parameter RHO_INT_BITS = 1,
    parameter RHO_FRAC_BITS = 7
) (
    input  clk,
    input  rst,
    input  in_valid,
    input  signed  [INT_BITS+FRAC_BITS-1:0] rx_re_in,
    input  signed  [INT_BITS+FRAC_BITS-1:0] rx_img_in,
    input  [RHO_INT_BITS+RHO_FRAC_BITS-1:0] rho,
    output [7:0]   theta,
    output [20:0]   epsilon,
    output out_valid
);

// delay_n output
wire r_t r_real;
wire r_t r_imag;
wire r_t r_dN_real;
wire r_t r_dN_imag;

// phi_sum output
wire phi_t phi_out;

// gamma_sum output
wire gamma_t gamma_out_real;
wire gamma_t gamma_out_imag;

// phi_rho output
wire phi_t phi_rho;

// mag output
wire mag_t mag_out;

// angle output
wire ang_t ang_out;

// minus output
wire lambda_t lambda_out;

// argmax output
wire theta_t  theta_out;

// select_eps output
wire eps_t  eps_out;

// buf output
wire ang_t angle_buf;
wire [7:0] write_ptr;

// ---- 計算拉高 out_valid 的時機 ----
parameter N = 256;
parameter L = 16;

reg [(2*N+L)-1:0] valid_shift;
integer i;
always @(posedge clk or posedge rst) begin
    if (rst)
        valid_shift <= 0;
    else
        valid_shift <= {valid_shift[(2*N+L)-2:0], in_valid};
end

assign out_valid = valid_shift[(2*N+L)-1];  
assign theta = theta_out;
assign epsilon = eps_out;

delay_n u_delay_n(
    .clk(clk),
    .rst(rst),
    .rx_re_in(rx_re_in),
    .rx_img_in(rx_img_in),
    .r_real(r_real),
    .r_imag(r_imag),
    .r_dN_real(r_dN_real),
    .r_dN_imag(r_dN_imag)
);

phi_sum u_phi_sum(
    .clk(clk),
    .rst(rst),
    .r_k_in_real(r_real),
    .r_k_in_imag(r_imag),
    .r_k_minus_N_in_real(r_dN_real),
    .r_k_minus_N_in_imag(r_dN_imag),
    .rho(rho),
    .phi_out(phi_out)
);

gamma_sum u_gamma_sum(
    .clk(clk),
    .rst(rst),
    .r_k_in_real(r_real),
    .r_k_in_imag(r_imag),
    .r_k_minus_N_in_real(r_dN_real),
    .r_k_minus_N_in_imag(r_dN_imag),
    .gamma_out_real(gamma_out_real),
    .gamma_out_imag(gamma_out_imag)
);

phi_rho u_phi_rho(
    .clk(clk),
    .rst(rst),
    .phi_in(phi_out),
    .rho_in(rho),
    .phi_rho(phi_rho)
);

minus u_minus(
    .mag_in(mag_out),
    .phi_rho(phi_rho),
    .lambda_out(lambda_out)
);

angle u_angle(
    .clk(clk),
    .rst(rst),
    .gamma_in_real(gamma_out_real),
    .gamma_in_imag(gamma_out_imag),
    .angle_out(ang_out)
);

mag u_mag(
    .clk(clk),
    .rst(rst),
    .gamma_in_real(gamma_out_real),
    .gamma_in_imag(gamma_out_imag),
    .mag_out(mag_out)
);

argmax u_argmax(
    .clk(clk),
    .rst(rst),
    .lambda(lambda_out),
    .theta_out(theta_out)
);

buf u_buf(
    .clk(clk),
    .rst(rst),
    .ang_in(ang_out),
    .angle_buf(angle_buf),
    .write_ptr(write_ptr)
);

select_eps u_select_eps(
    .angle_buf(angle_buf),
    .write_ptr(write_ptr),
    .theta_in(theta_out),
    .eps_out(eps_out)
);

endmodule