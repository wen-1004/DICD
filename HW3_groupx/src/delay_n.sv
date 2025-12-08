`include "../include/data_type.svh"

module delay_n (
    input  logic clk,
    input  logic rst,          

    input  in_r_t   r_in_real,
    input  in_r_t   r_in_imag,

    output r_t   r_d1_real,
    output r_t   r_d1_imag,
    output r_t   r_dN_out_real,
    output r_t   r_dN_out_imag
);
    localparam int N = 256;

    r_t delay_line_real [0:N-1];
    r_t delay_line_imag [0:N-1];

    integer i;

    always_ff @(posedge clk) begin
        if (rst) begin
            for (i = 0; i < N; i = i + 1) begin
                delay_line_real[i] <= '0;
                delay_line_imag[i] <= '0;
            end
            r_d1_real     <= '0;
            r_d1_imag     <= '0;
            r_dN_out_real <= '0;
            r_dN_out_imag <= '0;
        end else begin
            // 1-cycle delayed tap (matches SC signal update semantics)
            r_d1_real <= r_in_real[15:9];
            r_d1_imag <= r_in_imag[15:9];

            // N-cycle delayed tap (read tail before shift)
            r_dN_out_real <= delay_line_real[N-1];
            r_dN_out_imag <= delay_line_imag[N-1];

            // Shift register update
            for (i = N-1; i > 0; i = i - 1) begin
                delay_line_real[i] <= delay_line_real[i-1];
                delay_line_imag[i] <= delay_line_imag[i-1];
            end
            delay_line_real[0] <= r_in_real[$bits(in_r_t)-1 -: $bits(r_t)];
            delay_line_imag[0] <= r_in_imag[$bits(in_r_t)-1 -: $bits(r_t)];
        end
    end

endmodule

