# a-el-you-tbx
Another simple ALU. This time using TBX.

This project uses Function-based System Verilog DPI accelerated channel to communicate between a rather simple testbench and a very simple ALU.

The requirement was for 10,000 tests, so we simply loop through the numbers 0-50 for all 4 opcodes of the ALU. This gives us just over 10k tests.

First we increment the first operand, then once that has completed a round, we increment the other operand and repeat. It should be noted that this is a terrible way to test an ALU.

Transcripts are included for running in simulation and on the veloce emulator.
