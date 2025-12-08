/*
`include "include/data_type.svh"

module minus (
    input mag_t    mag_in,
    input phi_t    phi_in,
    input rho_t    rho_in,
    output lambda_t lambda_out
);

    assign lambda_out = mag_in - (rho_in * phi_in);

endmodule
*/

`include "include/data_type.svh"

module minus (
    input  mag_t     mag_in,
    input  phi_t     phi_in,
    input  rho_t     rho_in,
    output lambda_t  lambda_out
);

    // Full-precision signed product: 8b * 16b = 24b
    logic signed [23:0] prod_full;
    logic signed [23:0] prod_shifted;
    logic signed [15:0] rho_phi_q6_10;

    // Interpret rho_in as Q1.7, phi_in as Q6.10
    // prod_full is Q7.17
    assign prod_full = rho_in * phi_in;

    // Align from Q7.17 -> Q?.10: shift right by 7 (arithmetic)
    assign prod_shifted = prod_full >>> 7;

    // Convert to 16-bit Q6.10:
    // keep 16 LSBs -> wrap-on-overflow, matching sc_fixed default (SC_WRAP)
    assign rho_phi_q6_10 = prod_shifted[15:0];

    // lambda_out = mag_in (Q6.10) - rho*phi (Q6.10)
    assign lambda_out = mag_in - rho_phi_q6_10;

endmodule

