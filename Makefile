GCC_DIR = ${HOME}/g++-arm-8.2-ecen427/

TEMPD= $(shell mktemp -d)

none:
	echo "Please specify a target"

g++-arm-8.2:
	cd $(TEMPD) && \
	wget "https://developer.arm.com/-/media/Files/downloads/gnu-a/8.2-2018.08/gcc-arm-8.2-2018.08-x86_64-arm-linux-gnueabihf.tar.xz?revision=51f3ba22-a569-4dda-aedc-7988690c3c17&ln=en&hash=4E3701F9F706EC18F254CB00DD0E8D153CA1A2AA" && \
	tar -xf "gcc-arm-8.2-2018.08-x86_64-arm-linux-gnueabihf.tar.xz?revision=51f3ba22-a569-4dda-aedc-7988690c3c17&ln=en&hash=4E3701F9F706EC18F254CB00DD0E8D153CA1A2AA" && \
	cp -r gcc-arm-8.2-2018.08-x86_64-arm-linux-gnueabihf $(GCC_DIR)/
	rm -rf $(TEMPD)


	