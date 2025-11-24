`include "include/data_type.svh"

module argmax (
    input  logic    clk,
    input  logic    rst,        // Active-high reset
    input  lambda_t lambda_in,  
    output theta_t  theta_out   
);

    // System Constants
    localparam int N = 256;
    
    // 輸入緩衝區 (Shift Register)，對應 SystemC 的 buf[N]
    // 這裡模擬 Sliding Window，每個 cycle 移入新資料
    lambda_t data_buffer [0:N-1];
    
    always_ff @(posedge clk or posedge rst) begin
        if (rst) begin
            for (int i = 0; i < N; i++) begin
                data_buffer[i] <= 16'sd0; 
            end
        end else begin
            // Shift operation: buf[i] = buf[i-1]
            for (int i = N-1; i > 0; i--) begin
                data_buffer[i] <= data_buffer[i-1];
            end
            // Insert new value at head
            data_buffer[0] <= lambda_in;
        end
    end

    // 定義 Pipeline Tree 的資料結構
    typedef struct packed {
        lambda_t val;
        theta_t  idx;
    } pair_t;

    pair_t stages [0:8][0:N-1];

    // Stage 0: 初始化層 
    // 根據 SystemC 邏輯: idx = 255 - pos. 
    // data_buffer[0] 是最新的, 對應 pos=0, 所以 idx=255
    // data_buffer[255] 是最舊的, 對應 pos=255, 所以 idx=0
    always_comb begin
        for (int i = 0; i < N; i++) begin
            stages[0][i].val = data_buffer[i];
            stages[0][i].idx = 8'(255 - i); 
        end
    end

    // Stage 1 ~ 8: Pipelined Comparator Tree
    // 使用 generate 迴圈建立 8 級比較器
    genvar level, k;
    generate
        for (level = 0; level < 8; level++) begin : pipe_stage
            // 目前層級的對數 (256 -> 128 -> 64 ...)
            localparam int num_pairs = N >> (level + 1); 
            
            for (k = 0; k < num_pairs; k++) begin : comp_unit
                always_ff @(posedge clk or posedge rst) begin
                    if (rst) begin
                        // Reset to minimum value and logic 0 index
                        stages[level+1][k].val <= 16'sd-32768; // Min value for signed 16-bit
                        stages[level+1][k].idx <= 8'd0;
                    end else begin
                        // 比較邏輯: 比較相鄰的兩個元素 (2*k 和 2*k+1)
                        // 如果左邊大於等於右邊，保留左邊；否則保留右邊
                        if (stages[level][2*k].val >= stages[level][2*k+1].val) begin
                            stages[level+1][k] <= stages[level][2*k];
                        end else begin
                            stages[level+1][k] <= stages[level][2*k+1];
                        end
                    end
                end
            end
        end
    endgenerate

    // 輸出結果
    // 經過 8 個 stages 後，stages[8][0] 保存了最大值及其索引
    assign theta_out = stages[8][0].idx;

endmodule