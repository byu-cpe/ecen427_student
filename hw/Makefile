all:
	vivado -source ecen427.tcl

clean:
	rm -rf ecen427 *.jou *.log *.debug *.str

ecen427.bit: ecen427/ecen427.runs/impl_1/system_wrapper.bit
	cp $< $@