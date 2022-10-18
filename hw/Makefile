# This file is too large to commit to the git repo (>10M), so this makefile will unzip it before Vivado is run.  
LARGE_IP_FILE = digilent_ip/vivado-library/ip/audio_codec_ctrl_v1.0/src/fifo/hdl/blk_mem_gen_v8_4_vhsyn_rfs.vhd

all: $(LARGE_IP_FILE)
	vivado -source ecen427.tcl

clean:
	rm -rf ecen427 *.jou *.log *.debug *.str $(LARGE_IP_FILE)

ecen427.bit: ecen427/ecen427.runs/impl_1/system_wrapper.bit
	cp $< $@


# This target will unzip the LARGE_IP_FILES
$(LARGE_IP_FILE):
	zip -s 0 zip/ip.zip --out ip_unsplit.zip
	unzip ip_unsplit.zip
	rm ip_unsplit.zip

# This can be used to zip the large IP file
ip.zip: 
	zip -s 9m zip/ip.zip $(LARGE_IP_FILE)
	rm $(LARGE_IP_FILE)

sim_pit:
	vivado -source sim_proj.tcl -source run_sim.tcl
