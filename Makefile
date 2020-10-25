# From ECE 571

MODE ?= veloce
#MODE ?= puresim

all: clean lib compile run

lib:
ifeq ($(MODE),puresim)
	vlib work.$(MODE)
	vmap work work.$(MODE) 
else	
	vellib work.$(MODE)
	velmap work work.$(MODE)
endif

compile:
ifeq ($(MODE),puresim)
	# tbxbindings.h isn't really nessesary, as that's the default file name
	# still, nice to call it out here
	vlog hdl/proto_alu.sv hdl/proto_alu_tb.sv -dpiheader tbxbindings.h 
	vlog hvl/alu-tb.cxx
else
	velanalyze hdl/proto_alu.sv hdl/proto_alu_tb.sv
	velcomp
endif

run:
ifeq ($(MODE),puresim)
	vsim -c proto_alu_tb -do "run -all" | tee transcript.puresim
else
	velrun -64bit -emul Greg  | tee transcript.veloce
endif

clean:
	rm -rf edsenv transcript modelsim.ini transcript.veloce transcript.puresim veloce.map veloce.wave velrunopts.ini work work.veloce veloce.out veloce.med veloce.log tbxbindings.h

