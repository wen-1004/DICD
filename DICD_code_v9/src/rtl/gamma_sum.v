// `include "include/data_type.svh"

// module  gamma_sum(
//         input		clk                         ,
//         input		rst                         ,
//         input r_t r_k_in_real            ,
//         input r_t r_k_in_imag            ,
//         input r_t r_k_minus_N_in_real    ,
//         input r_t r_k_minus_N_in_imag    ,
//         output gamma_t gamma_out_real,
//         output gamma_t gamma_out_imag 
// );

// parameter L = 16;
// integer i;

// reg gamma_t delay_line_real[0:L-1];
// reg gamma_t delay_line_imag[0:L-1];

// reg gamma_t product_real;
// reg gamma_t product_imag;
// reg gamma_t gamma_out_real_buf;
// reg gamma_t gamma_out_imag_buf;

// assign gamma_out_real = gamma_out_real_buf;
// assign gamma_out_imag = gamma_out_imag_buf;

// always @(*) begin                                                   // ---- cal r[k] * (conj r[k+N])
//     product_real = (r_k_in_real*r_k_minus_N_in_real) + (r_k_in_imag*r_k_minus_N_in_imag);
//     product_imag = (r_k_in_imag*r_k_minus_N_in_real) - (r_k_in_real*r_k_minus_N_in_imag);
// end

// always @(posedge clk or posedge rst) begin                          // ---- shift register ----
//     if (rst) begin
//         for (i = 0; i < L; i = i + 1) begin
//             delay_line_real[i] <= 0;
//             delay_line_imag[i] <= 0;
//         end
//     end
//     else begin
//         for (i = L-1; i > 0; i = i - 1) begin
//             delay_line_real[i] <= delay_line_real[i-1];
//             delay_line_imag[i] <= delay_line_imag[i-1];
//         end
//         delay_line_real[0] <= product_real;
//         delay_line_imag[0] <= product_imag;
//     end
// end   

// always @(posedge clk or posedge rst) begin                          // ---- moving sum ----
//         if (rst) begin
//             gamma_out_real_buf <= 0;
//             gamma_out_imag_buf <= 0;
//         end
//         else begin
//             gamma_out_real_buf <= gamma_out_real_buf + product_real - delay_line_real[L-1];
//             gamma_out_imag_buf <= gamma_out_imag_buf + product_imag - delay_line_imag[L-1];
//         end
// end

// endmodule

`include "include/data_type.svh"

module gamma_sum(
    input          clk,
    input          rst,
    input  r_t          r_k_in_real,
    input  r_t          r_k_in_imag,
    input  r_t          r_k_minus_N_in_real,
    input  r_t          r_k_minus_N_in_imag,
    output gamma_t      gamma_out_real,
    output gamma_t      gamma_out_imag
);

parameter L = 16;
integer i;

// shift registers
reg gamma_t delay_line_real[0:L-1];
reg gamma_t delay_line_imag[0:L-1];

// product & output buffers
reg gamma_t product_real;
reg gamma_t product_imag;
reg gamma_t gamma_out_real_buf;
reg gamma_t gamma_out_imag_buf;

assign gamma_out_real = gamma_out_real_buf;
assign gamma_out_imag = gamma_out_imag_buf;

// intermediate wider variables for multiplication
reg signed [31:0] product_real_full;
reg signed [31:0] product_imag_full;

// ------------------------------------------------------
// combinational: calculate full-width products
// ------------------------------------------------------
always @(*) begin
    // full 32-bit multiplication first
    product_real_full = r_k_in_real * r_k_minus_N_in_real + r_k_in_imag * r_k_minus_N_in_imag;
    product_imag_full = r_k_in_imag * r_k_minus_N_in_real - r_k_in_real * r_k_minus_N_in_imag;
end

always @(*) begin
    // right shift to reduce back to gamma_t width (16-bit)
    // Q1.15 * Q1.15 -> Q2.30, right shift 20 
    product_real_shift = product_real_full >>> 20;
    product_imag_shift = product_imag_full >>> 20;
end

always @(*) begin
    // Q?.10->Q6.10
    product_real = product_real_shift[15:0];
    product_imag = product_imag_shift[15:0];
end    

// ------------------------------------------------------
// shift register
// ------------------------------------------------------
always @(posedge clk or posedge rst) begin
    if (rst) begin
        for (i = 0; i < L; i=i+1) begin
            delay_line_real[i] <= 0;
            delay_line_imag[i] <= 0;
        end
    end else begin
        for (i = L-1; i > 0; i=i-1) begin
            delay_line_real[i] <= delay_line_real[i-1];
            delay_line_imag[i] <= delay_line_imag[i-1];
        end
        delay_line_real[0] <= product_real;
        delay_line_imag[0] <= product_imag;
    end
end

// ------------------------------------------------------
// moving sum (S[n] = S[n-1] + new - old)
 // safe because product already scaled to 16-bit
// ------------------------------------------------------
always @(posedge clk or posedge rst) begin
    if (rst) begin
        gamma_out_real_buf <= 0;
        gamma_out_imag_buf <= 0;
    end else begin
        gamma_out_real_buf <= gamma_out_real_buf + product_real - delay_line_real[L-1];
        gamma_out_imag_buf <= gamma_out_imag_buf + product_imag - delay_line_imag[L-1];
    end
end

endmodule

