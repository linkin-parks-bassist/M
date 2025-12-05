`define PIPELINE_READY 			0
`define PIPELINE_PROCESSING 	1
`define PIPELINE_INVALID	 	2

`define BLOCK_INSTR_NOP 	0
`define BLOCK_INSTR_ADD 	1
`define BLOCK_INSTR_MUL 	2
`define BLOCK_INSTR_MAC		3
`define BLOCK_INSTR_ABS		4
`define BLOCK_INSTR_BIQ_DF1	5

`define BLOCK_OP_TYPE_WIDTH 3

`define DATA_TYPE_Q1_15 0
`define DATA_TYPE_Q8_8 	1

module distributed_multiplier
	#(
		parameter width = 18,
		parameter n_blocks = 32
	)
	(
		input wire clk,
		input wire reset,
		
		input wire signed [width - 1:0] x [0 : n_blocks - 1],
		input wire signed [width - 1:0] y [0 : n_blocks - 1],
		
		output reg signed [2 * width - 1 : 0] prod,
		
		output reg  [n_blocks - 1 : 0] done
	);
	
	localparam index_width = $clog2(n_blocks);
	localparam [index_width - 1 : 0] initial_index = index_width'(n_blocks - 1);
	
	reg [index_width - 1 : 0] index = initial_index;
	
	integer i;
	always @(posedge clk) begin
		if (reset) begin
			index <= initial_index;
			
			for (i = 0; i < n_blocks; i = i + 1) begin
				done[i] <= 0;
			end
			
			prod <= 0;
		end
		else begin
			prod <= x[index] * y[index];
			
			done <= '0;
			done[index] <= 1;
			
			if (index == 0) begin
				index <= initial_index;
			end
			else begin
				index <= index - 1;
			end
		end
	end
endmodule

// Note: ensure 4 * `BLOCK_ADDR_WIDTH + `BLOCK_INSTR_OP_WIDTH + 3 < `BLOCK_INSTR_WIDTH
// and max($clog2(n_channels), $clog2(n_registers)) <= `BLOCK_ADDR_WIDTH
`define BLOCK_INSTR_WIDTH 		32

`define BLOCK_INSTR_OP_WIDTH 	5
`define BLOCK_ADDR_WIDTH   		4
`define BLOCK_PMS_WIDTH			5

// Block FSM states

`define BLOCK_STATE_BEGIN 		0
`define BLOCK_STATE_DONE		1

`define BLOCK_STATE_ADD_WAIT	2
`define BLOCK_STATE_ADD_STORE	3

`define BLOCK_STATE_MUL_WAIT	2
`define BLOCK_STATE_MUL_STORE	3

`define BLOCK_STATE_MAC_MUL_WAIT	2
`define BLOCK_STATE_MAC_ADD_WAIT	3
`define BLOCK_STATE_MAC_STORE		4

`define BLOCK_STATE_BIQUAD_DF1_MUL_1_WAIT 		1

`define BLOCK_STATE_BIQUAD_DF1_MAC_1_MUL_WAIT 	2
`define BLOCK_STATE_BIQUAD_DF1_MAC_1_ADD_WAIT 	3
`define BLOCK_STATE_BIQUAD_DF1_MAC_1_STORE 		4

`define BLOCK_STATE_BIQUAD_DF1_MAC_2_MUL_WAIT 	5
`define BLOCK_STATE_BIQUAD_DF1_MAC_2_ADD_WAIT 	6
`define BLOCK_STATE_BIQUAD_DF1_MAC_2_STORE 		7

`define BLOCK_STATE_BIQUAD_DF1_MAC_3_MUL_WAIT 	8
`define BLOCK_STATE_BIQUAD_DF1_MAC_3_ADD_WAIT 	9
`define BLOCK_STATE_BIQUAD_DF1_MAC_3_STORE 		10

`define BLOCK_STATE_BIQUAD_DF1_MAC_4_MUL_WAIT 	11
`define BLOCK_STATE_BIQUAD_DF1_MAC_4_ADD_WAIT 	12
`define BLOCK_STATE_BIQUAD_DF1_MAC_4_STORE 		13

module pipeline_block
	#(
		parameter integer data_width 		= 16,
		parameter integer n_channels   		= 16,
		parameter integer n_registers  		= 16
	)
	(
		input wire clk,
		
		input wire tick,
		input wire reset,
		
		input  wire [data_width - 1 : 0] ch_in  [0 : n_channels - 1],
		output wire [data_width - 1 : 0] ch_out [0 : n_channels - 1],
		
		input wire [`BLOCK_INSTR_WIDTH - 1 : 0] instr_val,
		input wire instr_write,
		
		input wire [data_width - 1 		: 0] reg_val,
		input wire [$clog2(n_registers) - 1 : 0] reg_target,
		input wire reg_write,
		input wire reg_update,
		
		output reg [data_width - 1 : 0] mul_req_a,
		output reg [data_width - 1 : 0] mul_req_b,
		
		input wire signed [2 * data_width - 1 : 0] mul_result,
		input wire mul_done,
		
		output reg done
	);
	
	genvar j;
	generate
		for (j = 0; j < n_channels; j = j + 1) begin
			assign ch_out[j] = ch_regs[j];
		end
	endgenerate
	
	//
	// Block instruction
	//
	reg  [`BLOCK_INSTR_WIDTH 	- 1 : 0] instr;
	
	//
	// Instruction decoding
	//
	wire [`BLOCK_INSTR_OP_WIDTH - 1 : 0] operation = instr[`BLOCK_INSTR_OP_WIDTH - 1 : 0];
	
	wire [`BLOCK_ADDR_WIDTH - 1 : 0] src_a = instr[1 * `BLOCK_ADDR_WIDTH + `BLOCK_INSTR_OP_WIDTH - 1 : 0 * `BLOCK_ADDR_WIDTH + `BLOCK_INSTR_OP_WIDTH];
	wire [`BLOCK_ADDR_WIDTH - 1 : 0] src_b = instr[2 * `BLOCK_ADDR_WIDTH + `BLOCK_INSTR_OP_WIDTH - 1 : 1 * `BLOCK_ADDR_WIDTH + `BLOCK_INSTR_OP_WIDTH];
	wire [`BLOCK_ADDR_WIDTH - 1 : 0] src_c = instr[3 * `BLOCK_ADDR_WIDTH + `BLOCK_INSTR_OP_WIDTH - 1 : 2 * `BLOCK_ADDR_WIDTH + `BLOCK_INSTR_OP_WIDTH];
	wire [`BLOCK_ADDR_WIDTH - 1 : 0] dest  = instr[4 * `BLOCK_ADDR_WIDTH + `BLOCK_INSTR_OP_WIDTH - 1 : 3 * `BLOCK_ADDR_WIDTH + `BLOCK_INSTR_OP_WIDTH];
	
	localparam operand_type_start_index = 4 * `BLOCK_ADDR_WIDTH + `BLOCK_INSTR_OP_WIDTH;
	
	wire src_a_reg = instr[operand_type_start_index + 0];
	wire src_b_reg = instr[operand_type_start_index + 1];
	wire src_c_reg = instr[operand_type_start_index + 2];
	wire dest_reg  = instr[operand_type_start_index + 3];
	
	localparam pms_start_index = operand_type_start_index + 4;
	
	//
	// Local storage: channels and registers
	//
	reg signed [data_width  - 1 : 0] ch_regs [0 : n_channels  - 1];
	reg signed [data_width	- 1 : 0] regs 	 [0 : n_registers - 1];
	reg signed [data_width	- 1 : 0] reg_updates[0 : n_registers - 1];
	reg reg_updated[0 : n_registers - 1];
	
	wire signed [data_width - 1 : 0] unified_regs [0 : n_channels + n_registers - 1];
	
	genvar k;
	generate
		for (k = 0; k < n_channels + n_registers; k = k + 1) begin
			if (k < n_channels) begin
				assign unified_regs[k] = ch_regs[k];
			end
			else begin
				assign unified_regs[k] = regs[k - n_channels];
			end
		end
	endgenerate
	
	localparam int UNIFIED_W = $clog2(n_channels + n_registers);
	
	wire [$clog2(n_channels + n_registers) - 1 : 0] src_a_unified_addr =
		src_a_reg ? UNIFIED_W'(src_a) + UNIFIED_W'(n_channels) : UNIFIED_W'(src_a);
	wire [$clog2(n_channels + n_registers) - 1 : 0] src_b_unified_addr =
		src_b_reg ? UNIFIED_W'(src_b) + UNIFIED_W'(n_channels) : UNIFIED_W'(src_b);
	wire [$clog2(n_channels + n_registers) - 1 : 0] src_c_unified_addr =
		src_c_reg ? UNIFIED_W'(src_c) + UNIFIED_W'(n_channels) : UNIFIED_W'(src_c);
	wire [$clog2(n_channels + n_registers) - 1 : 0] dest_unified_addr =
		dest_reg ? UNIFIED_W'(dest) + UNIFIED_W'(n_channels) : UNIFIED_W'(dest);
	
	task automatic unified_write;
		input bit is_reg;
		input [UNIFIED_W-1:0] uaddr;
		input signed [data_width-1:0] value;
	begin
		if (is_reg)
			regs[4'(uaddr - UNIFIED_W'(n_channels))] <= value;
		else
			ch_regs[4'(uaddr)] <= value;
	end
	endtask
	
	reg signed [data_width - 1 : 0] src_a_latched;
	reg signed [data_width - 1 : 0] src_b_latched;
	reg signed [data_width - 1 : 0] src_c_latched;
	
	//
	// Local adder
	//
	reg signed [data_width - 1 : 0] summand_a = 0;
	reg signed [data_width - 1 : 0] summand_b = 0;
	
	wire signed [data_width:0] summand_a_ext =
		{ summand_a[data_width-1], summand_a };

	wire signed [data_width:0] summand_b_ext =
		{ summand_b[data_width-1], summand_b };

	// Async perform addition on given summands. Saturate in procedural block
	wire signed [data_width:0] sum_ext = summand_a_ext + summand_b_ext;
	
	//
	// Saturation and format compensation for muls
	//
	localparam integer MAX_SHIFT = 2 * data_width - 2;
	localparam integer SHIFT_WIDTH = $clog2(MAX_SHIFT + 1);
	
	wire [SHIFT_WIDTH - 1 : 0] post_mul_shift = (operation == `BLOCK_INSTR_BIQ_DF1) ? {{(SHIFT_WIDTH - 1){1'b0}}, 1'b1} :
		{{(SHIFT_WIDTH - `BLOCK_PMS_WIDTH){1'b0}}, instr[pms_start_index + `BLOCK_PMS_WIDTH - 1 : pms_start_index]};

	// Explicitly sized saturation limits in FULL multiply width
	wire signed [2*data_width-1:0] SAT_MAX_EXT =
		{{(data_width){1'b0}}, {1'b0, {(data_width-1){1'b1}}}};

	wire signed [2*data_width-1:0] SAT_MIN_EXT =
		{{(data_width){1'b1}}, {1'b1, {(data_width-1){1'b0}}}};

	// Arithmetic shift
	wire signed [2 * data_width - 1 : 0] mul_result_shifted =
		$signed(mul_result) >>> (15 - post_mul_shift);

	// Final saturation and narrowing
	wire signed [data_width-1:0] mul_result_final =
		(mul_result_shifted > SAT_MAX_EXT) ?  SAT_MAX_EXT[data_width-1:0] :
		(mul_result_shifted < SAT_MIN_EXT) ?  SAT_MIN_EXT[data_width-1:0] :
											 mul_result_shifted[data_width-1:0];
	
	reg signed [data_width - 1 : 0] sum;
	reg signed [data_width - 1 : 0] prod;
	
	reg mul_wait_begin = 0;
	
	wire mul_ready = ~mul_wait_begin & mul_done;
	
	reg [8:0] state = 0;
	
	integer i;
	always @(posedge clk) begin
	
		//
		// Addition saturator
		//
		
		if (sum_ext > $signed({1'b0, {data_width{1'b1}}})) begin
			sum <= {1'b0, {data_width-1{1'b1}}};   // +32767
		end
		else if (sum_ext < $signed({1'b1, {data_width{1'b0}}})) begin
			sum <= {1'b1, {data_width-1{1'b0}}};   // -32768
		end
		else begin
			sum <= sum_ext[data_width-1:0];
		end
	
		//
		// Accept any register writes
		//
		if (reg_write) begin
			regs[reg_target] <= reg_val;
		end
		else if (reg_update) begin
			reg_updates[reg_target] <= reg_val;
			reg_updated[reg_target] <= 1;
		end
		
		//
		// Accept new instruction
		//
		if (instr_write) begin
			instr <= instr_val;
		end
		
		//
		// On tick: shift in channels from prev stage
		//
		if (tick) begin
			for (i = 0; i < n_channels; i++) begin
				ch_regs[i] <= ch_in[i];
			end
			
			for (i = 0; i < n_registers; i++) begin
				if (reg_updated[i]) begin
					if (reg_updates[i] < regs[i]) begin
						regs[i] <= regs[i] - 1;
					end
					else if (reg_updates[i] > regs[i]) begin
						regs[i] <= regs[i] + 1;
					end
					else begin
						reg_updated[i] <= 0;
					end
				end
			end
			
			state <= `BLOCK_STATE_BEGIN;
			done <= 0;
		end
		else if (!done) begin
			case (operation)
				`BLOCK_INSTR_NOP: begin
					state <= `BLOCK_STATE_DONE;
					done <= 1;
				end
				
				`BLOCK_INSTR_ADD: begin
					case (state)
						`BLOCK_STATE_BEGIN: begin
							summand_a <= src_a_reg ? regs[src_a] : ch_regs[src_a];
							summand_b <= src_b_reg ? regs[src_b] : ch_regs[src_b];
							state <= `BLOCK_STATE_ADD_WAIT;
						end
						
						`BLOCK_STATE_ADD_WAIT: begin
							state <= `BLOCK_STATE_ADD_STORE;
						end
						
						`BLOCK_STATE_ADD_STORE: begin
							if (dest_reg) begin
								regs[dest] <= sum;
							end
							else begin
								ch_regs[dest] <= sum;
							end
							state <= `BLOCK_STATE_DONE;
							done <= 1;
						end
						
						default: begin end
					endcase
					
					done <= 1;
				end
				
				`BLOCK_INSTR_MUL: begin
					case (state)
						`BLOCK_STATE_BEGIN: begin
							mul_req_a <= src_a_reg ? regs[src_a] : ch_regs[src_a];
							mul_req_b <= src_b_reg ? regs[src_b] : ch_regs[src_b];
							
							mul_wait_begin <= 1;
							state <= `BLOCK_STATE_MUL_WAIT;
						end
						
						`BLOCK_STATE_MUL_WAIT: begin
							if (mul_ready) begin
								prod  <= mul_result_final;
								state <= `BLOCK_STATE_MUL_STORE;
							end
							mul_wait_begin <= 0;
						end
						
						`BLOCK_STATE_MUL_STORE: begin
							if (dest_reg) begin
								regs[dest] <= prod;
							end
							else begin
								ch_regs[dest] <= prod;
							end
							
							state <= `BLOCK_STATE_DONE;
							done <= 1;
						end
						
						default: begin end
					endcase
				end
				
				`BLOCK_INSTR_MAC: begin
					case (state)
						`BLOCK_STATE_BEGIN: begin
							mul_req_a <= src_a_reg ? regs[src_a] : ch_regs[src_a];
							mul_req_b <= src_b_reg ? regs[src_b] : ch_regs[src_b];
							
							mul_wait_begin <= 1;
							state <= `BLOCK_STATE_MAC_MUL_WAIT;
						end
						
						`BLOCK_STATE_MAC_MUL_WAIT: begin
							if (mul_ready) begin
								summand_a  <= mul_result_final;
								summand_b <= src_c_reg ? regs[src_c] : ch_regs[src_c];
								state <= `BLOCK_STATE_MAC_ADD_WAIT;
							end
							mul_wait_begin <= 0;
						end
						
						`BLOCK_STATE_MAC_ADD_WAIT: begin
							state <= `BLOCK_STATE_MAC_STORE;
						end
						
						`BLOCK_STATE_MAC_STORE: begin
							if (dest_reg) begin
								regs[dest] <= sum;
							end
							else begin
								ch_regs[dest] <= sum;
							end
							
							state <= `BLOCK_STATE_DONE;
							done <= 1;
						end
						
						default: begin end
					endcase
				end
				
				`BLOCK_INSTR_ABS: begin
					if (src_a_reg) begin
						if (dest_reg) begin
							regs[dest] <= regs[src_a] < 0 ? -regs[src_a] : regs[src_a];
						end
						else begin
							ch_regs[dest] <= regs[src_a] < 0 ? -regs[src_a] : regs[src_a];
						end
					end
					else begin
						if (dest_reg) begin
							regs[dest] <= ch_regs[src_a] < 0 ? -ch_regs[src_a] : ch_regs[src_a];
						end
						else begin
							ch_regs[dest] <= ch_regs[src_a] < 0 ? -ch_regs[src_a] : ch_regs[src_a];
						end
					end
					
					done <= 1;
				end
				
				`BLOCK_INSTR_BIQ_DF1: begin
					case (state)
						`BLOCK_STATE_BEGIN: begin
							src_a_latched <= unified_regs[src_a_unified_addr];
							
							mul_req_a <= regs[0];
							mul_req_b <= unified_regs[src_a_unified_addr];
							
							mul_wait_begin <= 1;
							state <= `BLOCK_STATE_BIQUAD_DF1_MUL_1_WAIT;
						end
					
						`BLOCK_STATE_BIQUAD_DF1_MUL_1_WAIT: begin
							if (mul_ready) begin
								regs[9] <= mul_result_final;
								
								mul_req_a <= regs[1];
								mul_req_b <= regs[5];
								
								mul_wait_begin <= 1;
								state <= `BLOCK_STATE_BIQUAD_DF1_MAC_1_MUL_WAIT;
							end
							else begin
								mul_wait_begin <= 0;
							end
						end
						
						`BLOCK_STATE_BIQUAD_DF1_MAC_1_MUL_WAIT: begin
							if (mul_ready) begin
								
								summand_a <= regs[9];
								summand_b <= mul_result_final;
								
								state <= `BLOCK_STATE_BIQUAD_DF1_MAC_1_ADD_WAIT;
							end
							mul_wait_begin <= 0;
						end
						
						`BLOCK_STATE_BIQUAD_DF1_MAC_1_ADD_WAIT: begin
							state <= `BLOCK_STATE_BIQUAD_DF1_MAC_1_STORE;
						end
						
						`BLOCK_STATE_BIQUAD_DF1_MAC_1_STORE: begin
							regs[9] <= sum;
							
							mul_req_a <= regs[2];
							mul_req_b <= regs[6];
							
							mul_wait_begin <= 1;
							state <= `BLOCK_STATE_BIQUAD_DF1_MAC_2_MUL_WAIT;
						end
						
						`BLOCK_STATE_BIQUAD_DF1_MAC_2_MUL_WAIT: begin
							if (mul_ready) begin
								
								summand_a <= regs[9];
								summand_b <= mul_result_final;
								
								state <= `BLOCK_STATE_BIQUAD_DF1_MAC_2_ADD_WAIT;
							end
							mul_wait_begin <= 0;
						end
						
						`BLOCK_STATE_BIQUAD_DF1_MAC_2_ADD_WAIT: begin
							state <= `BLOCK_STATE_BIQUAD_DF1_MAC_2_STORE;
						end
						
						`BLOCK_STATE_BIQUAD_DF1_MAC_2_STORE: begin
							regs[9] <= sum;
							
							mul_req_a <= regs[3];
							mul_req_b <= regs[7];
							
							mul_wait_begin <= 1;
							state <= `BLOCK_STATE_BIQUAD_DF1_MAC_3_MUL_WAIT;
						end
						
						`BLOCK_STATE_BIQUAD_DF1_MAC_3_MUL_WAIT: begin
							if (mul_ready) begin
								
								summand_a <= regs[9];
								summand_b <= -mul_result_final;
								
								state <= `BLOCK_STATE_BIQUAD_DF1_MAC_3_ADD_WAIT;
							end
							mul_wait_begin <= 0;
						end
						
						`BLOCK_STATE_BIQUAD_DF1_MAC_3_ADD_WAIT: begin
							state <= `BLOCK_STATE_BIQUAD_DF1_MAC_3_STORE;
						end
						
						
						`BLOCK_STATE_BIQUAD_DF1_MAC_3_STORE: begin
							regs[9] <= sum;
							
							mul_req_a <= regs[4];
							mul_req_b <= regs[8];
							
							mul_wait_begin <= 1;
							state <= `BLOCK_STATE_BIQUAD_DF1_MAC_4_MUL_WAIT;
						end
						
						`BLOCK_STATE_BIQUAD_DF1_MAC_4_MUL_WAIT: begin
							if (mul_ready) begin
								
								summand_a <= regs[9];
								summand_b <= -mul_result_final;
								
								state <= `BLOCK_STATE_BIQUAD_DF1_MAC_4_ADD_WAIT;
							end
							mul_wait_begin <= 0;
						end
						
						`BLOCK_STATE_BIQUAD_DF1_MAC_4_ADD_WAIT: begin
							state <= `BLOCK_STATE_BIQUAD_DF1_MAC_4_STORE;
						end
						
						`BLOCK_STATE_BIQUAD_DF1_MAC_4_STORE: begin
							unified_write(dest_reg, dest_unified_addr, sum);
							
							regs[6] <= regs[5];
							regs[5] <= src_a_latched;
							
							regs[8] <= regs[7];
							regs[7] <= sum;
							
							state <= `BLOCK_STATE_DONE;
							done <= 1;
						end
					endcase
				end
			endcase
		end
		
		if (reset) begin
			for (i = 0; i < n_channels; i++) begin
				ch_regs[i] <= 0;
			end
			
			for (i = 0; i < n_registers; i++) begin
				regs[i] <= 0;
				reg_updates[i] <= 0;
				reg_updated[i] <= 0;
			end
		end
	end

endmodule


module pipeline_section_controller
	#(
		parameter integer n_blocks     = 32,
		parameter integer data_width = 16,
		parameter integer n_channels   = 16
	)
	(
		input wire clk,
		
		input wire reset
		
		
	);
	
    
endmodule

module pipeline
	#(
		parameter n_blocks = 2,
		parameter n_block_registers = 16,
		parameter data_width = 16,
		parameter n_channels = 16
	)
	(
		input wire clk,
		input wire signed [data_width - 1:0] in_sample,
		input wire in_valid,
		
		input wire reset,
		
		output wire [data_width - 1:0] out_sample,
		output reg ready,
		
		input wire [$clog2(n_blocks) - 1 : 0] block_target,
		input wire [$clog2(n_block_registers) - 1 : 0] reg_target,
		
		input wire [`BLOCK_INSTR_WIDTH - 1 : 0] instr_val,
		input wire instr_write,
		
		input wire [data_width - 1 : 0] reg_val,
		input wire reg_update,
		input wire reg_write,
		
		output wire error
	);
	
	reg signed [data_width - 1 : 0] sample_latched;
	
	reg [15:0] state;
	
	reg [15:0] ctr;
	
	reg invalid = 0;
	assign error = invalid;
	
	always @(posedge clk) begin
		if (reset) begin
			state 			<= `PIPELINE_READY;
			sample_latched 	<= 0;
			ready 			<= 1;
			invalid 		<= 0;
		end
		else begin
			case (state)
				`PIPELINE_READY: begin
					ready <= 1;
					
					if (in_valid) begin
						state 	<= `PIPELINE_PROCESSING;
						ctr 	<= 0;
						ready 	<= 0;
					end
				end
			
				`PIPELINE_PROCESSING: begin
					ready <= &dones;
				end
				
				`PIPELINE_INVALID: begin
					invalid 	<= 1;
					ready 	<= 0;
				end
				
				default: begin
					invalid <= 1;
					state 	<= `PIPELINE_INVALID;
				end
			endcase
		end
	end
	
	wire [data_width - 1 : 0] bus [0 : n_blocks][0 : n_channels - 1];
	wire [n_blocks - 1 : 0] dones;

	genvar c;
    generate
        for (c = 0; c < n_channels; c = c + 1) begin
            assign bus[0][c] = (c == 0) ? in_sample : '0;
        end
    endgenerate
    
    assign out_sample = bus[n_blocks][0];
    
    wire [data_width 		- 1 : 0] mul_bus_x [0 : n_blocks - 1];
    wire [data_width 		- 1 : 0] mul_bus_y [0 : n_blocks - 1];
    wire [2 * data_width 	- 1 : 0] mul_result;
    wire [n_blocks 			- 1 : 0] mul_done;
    
    distributed_multiplier #(.width(data_width), .n_blocks(n_blocks)) mul
		(
			.clk(clk),
			.reset(reset),
			
			.x(mul_bus_x),
			.y(mul_bus_y),
			
			.prod(mul_result),
			
			.done(mul_done)
		);
	
	genvar i;
	generate
		for (i = 0; i < n_blocks; i = i + 1) begin : blocks
			pipeline_block #(
				.n_registers(n_block_registers),
                .data_width(data_width),
                .n_channels(n_channels)
            ) block_inst (
                .clk   (clk),
                .tick(in_valid),
                .reset(reset),
                .ch_in (bus[i]),
                .ch_out(bus[i+1]),
                
                .mul_req_a(mul_bus_x[i]),
                .mul_req_b(mul_bus_y[i]),
                
                .mul_result(mul_result),
                .mul_done(mul_done[i]),
                
                .instr_val(instr_val),
                .instr_write(instr_write & (i == block_target)),
                
                .reg_target(reg_target),
                .reg_val(reg_val),
                .reg_write(reg_write & (i == block_target)),
                .reg_update(reg_update & (i == block_target)),
                
                .done(dones[i])
            );
		end
	endgenerate
endmodule
