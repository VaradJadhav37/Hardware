`timescale 1ns / 1ps

module dmcache(
    input  [7:0] addr,
    input        clk,
    output reg   hit,
    output reg [7:0] out
);

    // Cache line: [12:8] -> tag, [7:0] -> data
    reg [12:0] line [0:7];

    wire [7:0] op;
    wire [2:0] ind;

    assign ind = addr[2:0];

    // RAM instantiation
    ram ram1 (
        .addr(addr),
        .clk(clk),
        .out(op)
    );

    always @(posedge clk) begin
        if (line[ind][12:8] == addr[7:3]) begin
            hit <= 1'b1;
            out <= line[ind][7:0];
        end
        else begin
            hit <= 1'b0;
            line[ind] <= {addr[7:3], op};
            out <= op;
        end
    end

endmodule
