`include "../include/data_type.svh"

// -----------------------------------------------------------------------------
// 1-stage pre-rotation (registered) + 6-stage pipelined CORDIC (vectoring)
// Total latency = 1 + 6 = 7 cycles
//
// This matches the SystemC intent when you changed the "functional delay" to 7:
//   - pre-cordic quadrant handling is now treated as a real pipeline stage
//   - 6 iterations == 6 pipeline stages
// -----------------------------------------------------------------------------

module cordic_atan2_pipe #(
    parameter int I  = 0,
    parameter int W  = 16,
    parameter int ZW = 11,
    parameter logic signed [ZW-1:0] ATAN_LUT = '0
)(
    input  logic                     clk,
    input  logic                     rst,

    input  logic signed [W-1:0]      X_in,
    input  logic signed [W-1:0]      Y_in,
    input  logic signed [ZW-1:0]     Z_in,

    output logic signed [W-1:0]      X_out,
    output logic signed [W-1:0]      Y_out,
    output logic signed [ZW-1:0]     Z_out
);

    logic signed [W-1:0]  X_next, Y_next;
    logic signed [ZW-1:0] Z_next;

    logic signed [W-1:0]  X_shift, Y_shift;

    assign X_shift = X_in >>> I;
    assign Y_shift = Y_in >>> I;

    // Combinational update (same style as your Cordic_vector_pipe)
    always_comb begin
        if (Y_in[W-1] == 1'b0) begin // Y >= 0
            X_next = X_in + Y_shift;
            Y_next = Y_in - X_shift;
            Z_next = Z_in + ATAN_LUT;
        end else begin              // Y < 0
            X_next = X_in - Y_shift;
            Y_next = Y_in + X_shift;
            Z_next = Z_in - ATAN_LUT;
        end
    end

    // Sequential register
    always_ff @(posedge clk) begin
        X_out <= X_next;
        Y_out <= Y_next;
        Z_out <= Z_next;
    end

endmodule


module angle (
    input  logic     clk,
    input  logic     rst,

    input  gamma_t   gm_in_real,
    input  gamma_t   gm_in_imag,

    output ang_t     ang_out
);
    import data_type::*;

    localparam int ITERS = 6;

    // Derive widths from typedefs (keeps this robust with your package)
    localparam int W  = $bits(gamma_t);
    localparam int ZW = $bits(ang_t);

    // -------------------------------------------------------------------------
    // Binary atan LUT matching your SystemC table (Q?.8 style values)
    //
    // SystemC:
    //  atan(2^0)  ≈ 0.785398 -> 201/256  -> 0b0.11001001
    //  atan(2^-1) ≈ 0.463648 -> 118/256  -> 0b0.01110110
    //  atan(2^-2) ≈ 0.244979 ->  62/256  -> 0b0.00111110
    //  atan(2^-3) ≈ 0.124355 ->  31/256  -> 0b0.00011111
    //  atan(2^-4) ≈ 0.062419 ->  16/256  -> 0b0.00010000
    //  atan(2^-5) ≈ 0.031240 ->   8/256  -> 0b0.00001000
    // -------------------------------------------------------------------------
    localparam logic signed [ZW-1:0] ATAN_LUT [0:ITERS-1] = '{
        11'sb00011001001, // 201
        11'sb00001110110, // 118
        11'sb00000111110, //  62
        11'sb00000011111, //  31
        11'sb00000010000, //  16
        11'sb00000001000  //   8
    };

    // PI/2 in the same raw-in-Q8 spirit:
    // 1.570796 * 256 ≈ 402 -> binary
    localparam logic signed [ZW-1:0] PI_OVER_2_RAW = 11'sb00110010010;

    // -------------------------------------------------------------------------
    // Stage 0: quadrant fix (matches your SystemC behavior for x<0 cases)
    // We REGISTER this stage to model the extra 1-cycle pre-cordic latency.
    // -------------------------------------------------------------------------
    gamma_t x0_c, y0_c;
    ang_t   z0_c;

    gamma_t x0_r, y0_r;
    ang_t   z0_r;

    always_comb begin
        x0_c = gm_in_real;
        y0_c = gm_in_imag;
        z0_c = '0;

        if ($signed(gm_in_real) < 0) begin
            if ($signed(gm_in_imag) >= 0) begin
                // x<0, y>=0:
                // x =  y, y = -x, z = +pi/2
                x0_c = gm_in_imag;
                y0_c = -gm_in_real;
                z0_c = PI_OVER_2_RAW;
            end else begin
                // x<0, y<0:
                // x = -y, y =  x, z = -pi/2
                x0_c = -gm_in_imag;
                y0_c =  gm_in_real;
                z0_c = -PI_OVER_2_RAW;
            end
        end
    end

    always_ff @(posedge clk) begin
        x0_r <= x0_c;
        y0_r <= y0_c;
        z0_r <= z0_c;
    end

    // -------------------------------------------------------------------------
    // 6-stage pipelined CORDIC
    // -------------------------------------------------------------------------
    logic signed [W-1:0]  X [0:ITERS];
    logic signed [W-1:0]  Y [0:ITERS];
    logic signed [ZW-1:0] Z [0:ITERS];

    assign X[0] = x0_r;
    assign Y[0] = y0_r;
    assign Z[0] = z0_r;

    genvar gi;
    generate
        for (gi = 0; gi < ITERS; gi = gi + 1) begin : STAGE
            cordic_atan2_pipe #(
                .I(gi),
                .W(W),
                .ZW(ZW),
                .ATAN_LUT(ATAN_LUT[gi])
            ) u_pipe (
                .clk  (clk),
                .rst  (rst),
                .X_in (X[gi]),
                .Y_in (Y[gi]),
                .Z_in (Z[gi]),
                .X_out(X[gi+1]),
                .Y_out(Y[gi+1]),
                .Z_out(Z[gi+1])
            );
        end
    endgenerate

    // Final output is the last pipeline register (no extra register here)
    // Total latency remains 7 cycles.
    assign ang_out = ang_t'(Z[ITERS]);

endmodule
