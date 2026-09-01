ROOT_DIR = $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
TOOLS_DIR = $(ROOT_DIR)/tools

none:
	echo "Please specify a target"

$(TOOLS_DIR):
	mkdir -p $@

g++-arm-11.2: $(TOOLS_DIR) $(TOOLS_DIR)/gcc-arm-11.2-2022.02-x86_64-arm-none-linux-gnueabihf/bin/arm-none-linux-gnueabihf-g++

packages:
	sudo apt install -y \
		cmake \
		build-essential

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

IN_ENV = . .venv/bin/activate;

.venv/bin/activate: requirements.txt
	python3 -m venv .venv
	$(IN_ENV) pip install -r requirements.txt
	
submit_lab1: .venv/bin/activate
	$(IN_ENV) python3 submit.py lab1

submit_lab2: .venv/bin/activate
	$(IN_ENV) python3 submit.py lab2

submit_lab3: .venv/bin/activate
	$(IN_ENV) python3 submit.py lab3

submit_lab4_m1: .venv/bin/activate
	$(IN_ENV) python3 submit.py lab4_m1

submit_lab4_m2: .venv/bin/activate
	$(IN_ENV) python3 submit.py lab4_m2

submit_lab4_m3: .venv/bin/activate
	$(IN_ENV) python3 submit.py lab4_m3

submit_lab5_m1: .venv/bin/activate
	$(IN_ENV) python3 submit.py lab5_m1

submit_lab5_m2: .venv/bin/activate
	$(IN_ENV) python3 submit.py lab5_m2

submit_lab5_m3: .venv/bin/activate
	$(IN_ENV) python3 submit.py lab5_m3

submit_lab5_m4: .venv/bin/activate
	$(IN_ENV) python3 submit.py lab5_m4

submit_lab6_m1: .venv/bin/activate
	$(IN_ENV) python3 submit.py lab6_m1

submit_lab6_m2: .venv/bin/activate
	$(IN_ENV) python3 submit.py lab6_m2

submit_lab7: .venv/bin/activate
	$(IN_ENV) python3 submit.py lab7

submit_lab8: .venv/bin/activate
	$(IN_ENV) python3 submit.py lab8
