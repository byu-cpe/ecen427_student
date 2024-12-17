ROOT_DIR = $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
TOOLS_DIR = $(ROOT_DIR)/tools

none:
	echo "Please specify a target"

$(TOOLS_DIR):
	mkdir -p $@

g++-arm-11.2: $(TOOLS_DIR) $(TOOLS_DIR)/gcc-arm-11.2-2022.02-x86_64-arm-none-linux-gnueabihf/bin/arm-none-linux-gnueabihf-g++

$(TOOLS_DIR)/gcc-arm-11.2-2022.02-x86_64-arm-none-linux-gnueabihf/bin/arm-none-linux-gnueabihf-g++:
	@if lsb_release -a 2>/dev/null | grep -q "Pynqlinux"; then \
	    echo "Error: This command should not be run on the PYNQ board"; \
	    exit 1; \
	fi
	$(eval TMP := $(shell mktemp -d))
	cd $(TMP) && \
	wget "https://developer.arm.com/-/media/Files/downloads/gnu/11.2-2022.02/binrel/gcc-arm-11.2-2022.02-x86_64-arm-none-linux-gnueabihf.tar.xz?rev=ffc49e4af4cb4c298c2110a4d887716c&hash=4999788F321A7617C04CA172E31F6B22520741FF" && \
	tar -xf "gcc-arm-11.2-2022.02-x86_64-arm-none-linux-gnueabihf.tar.xz?rev=ffc49e4af4cb4c298c2110a4d887716c&hash=4999788F321A7617C04CA172E31F6B22520741FF" && \
	cp -r gcc-arm-11.2-2022.02-x86_64-arm-none-linux-gnueabihf $(TOOLS_DIR)/ && \
	rm -rf $(TMP)


	