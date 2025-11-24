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

// ---- 0 latency ----

`include "include/data_type.svh"

module minus (
    input  mag_t     mag_in,
    input  phi_t     phi_rho,
    output lambda_t  lambda_out
);

    // lambda_out = mag_in (Q6.10) - rho*phi (Q6.10)
    assign lambda_out = mag_in - phi_rho;

endmodule