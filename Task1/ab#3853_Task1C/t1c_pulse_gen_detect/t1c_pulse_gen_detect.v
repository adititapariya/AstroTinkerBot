// AstroTinker Bot : Task 1C : Pulse Generator and Detector
/*
Instructions
-------------------
Students are not allowed to make any changes in the Module declaration.

This file is used to design a module which will generate a 10us pulse and detect incoming pulse signal.

Recommended Quartus Version : 20.1
The submitted project file must be 20.1 compatible as the evaluation will be done on Quartus Prime Lite 20.1.

Warning: The error due to compatibility will not be entertained.
-------------------
*/

// t1c_pulse_gen_detect
//Inputs : clk_50M, reset, echo_rx
//Output : trigger, distance, pulses, state

// module declaration
module t1c_pulse_gen_detect (
    input clk_50M, reset, echo_rx,
    output reg trigger, out,
    output reg [21:0] pulses,
    output reg [1:0] state
);



initial begin
    trigger = 0; out = 0; pulses = 0; state = 0;
end
//////////////////DO NOT MAKE ANY CHANGES ABOVE THIS LINE//////////////////

reg [21:0] count=0;
reg warmup_done=0;

always @(posedge clk_50M) begin
    if (reset) begin
        // Reset all registers and start from generating trigger
        trigger = 0;
        out = 0;
        pulses = 0;
        state = 0;
        count = 0;
        warmup_done = 0;
    end else begin
        case(state)
            0: begin
                // Warmup delay for 1 us
                if (count <= 50000) begin
                    count = count + 1;
                end else begin
                    count = 0;
                    warmup_done = 1;
                    state = 1;
                end
            end
            1: begin
                // Generate a 10 us trigger signal
                if (count <= 500000) begin
                    trigger = 1;
                    count = count + 1;
                end else begin
					     count = 0;
                    trigger = 0;
                end
					 state = 2;
            end
            2: begin
                // Read input signal echo_rx and determine pulse width
                if (echo_rx == 1) begin
                    pulses = count; // Pulse width in clock cycles
                    state = 3;
                end else begin
                    count = count + 1;
						  pulses=count;
                end
            end
            3: begin
                // Check if pulse width is 588200 ns
                if (pulses == 11764) begin
                    out = 1;
                end else begin
                    out = 0;
                end
                state = 1; // Jump to step 1
            end
        endcase
    end
end



//////////////////DO NOT MAKE ANY CHANGES BELOW THIS LINE//////////////////

endmodule
