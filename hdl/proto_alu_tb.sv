module proto_alu_tb;

parameter width = 32;

logic clk, reset, request, valid, ready;
logic [width-1:0] operandA, operandB, result;
logic [1:0] opcode;

//clock generator
//tbx clkgen
initial
begin
    clk = 0;
    forever
    begin
        #10 clk = ~clk; 
    end
end


//reset generator
//tbx clkgen
initial
begin
    reset = 1;
    #20 reset = 0;
end


import "DPI-C" context task doReset();
import "DPI-C" task getData(output bit [31:0] operandA, output bit [31:0] operandB, output bit [1:0] opcode, output bit [31:0] ready);
import "DPI-C" task putData(input bit [31:0] result);
import "DPI-C" task doFinish();

initial begin
    @(posedge clk);
    while(reset) @(posedge clk);
    doReset;
end

export "DPI-C" function sayHello;

function void sayHello();
    $display("---hello export world---");
endfunction

always @(posedge clk) begin
    if (!reset) begin
        getData(operandA, operandB, opcode, ready);
        
        if (ready == 0) begin
           doFinish;
           $finish();
        end
        
        @(posedge clk);
        request = 1;
        
        while(!valid) @(posedge clk);
        
        request = 0;
        putData(result);
    end
end

proto_alu #(.width(width)) dut (clk,
    reset,
    request,
    operandA,
    operandB,
    opcode,
    result,
    valid);

endmodule
