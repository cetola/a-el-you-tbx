// Simple ALU Module
// Supports Add, Subtract, AND, OR Operationsi
// 
// ALU computes result when input 'request' is high.  The output is valid
// when the output signal 'valid' is high.

module proto_alu #(parameter width = 8) (
	input clk,
	input reset,
	input request,
	input [width-1:0] operandA, operandB,
	input [1:0] opcode,

	output logic[width-1:0] result,
	output logic valid
	);


always_ff @(posedge clk)
begin 
	if(reset)
	begin 
		result <= '0;
		valid <= 0;
	end
	else
	begin
		if (request)
		begin 
			case(opcode)
			0: result <= operandA + operandB; 
			1: result <= operandA - operandB;
			2: result <= operandA & operandB;
			3: result <= operandA | operandB;
			endcase

			valid <= 1;
		end
		else 
		begin
			valid <= 0;
			result <= result;
		end
	end
end

endmodule 
