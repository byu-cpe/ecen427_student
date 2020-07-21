# Device tree compilation
SRCDIR = dts
BINDIR = dtb

DEVICETREE_BINARY = ${BINDIR}/devicetree.dtb
DEVICETREE_SOURCE = ${SRCDIR}/system.dts
DEVICETREE_SOURCES = ${DEVICETREE_SOURCE} ${SRCDIR}/board_ecen427.dtsi

binary: ${DEVICETREE_BINARY}

${DEVICETREE_BINARY}: SHELL := /bin/bash
${DEVICETREE_BINARY}: ${DEVICETREE_SOURCES}
	dtc -I dts -O dtb -o dtb/devicetree.dtb ${DEVICETREE_SOURCE}
	
# Bootloader compilation steps
BOOTDIR = boot
BOOTSRCDIR = $(realpath bootsrc)
WORKDIR = build

BOARD_PART = xc7z020clg400-1
BOARD_CONSTRAINTS = ${BOOTSRCDIR}/constraints.xdc
PS_CONFIG_TCL = ${BOOTSRCDIR}/ps7_config.tcl
export BOARD_PART
export BOARD_CONSTRAINTS
export PS_CONFIG_TCL

BOOT_BITSTREAM = ../hw/ecen427.bit

GIT_CLONE_CHECKOUT = ${BOOTSRCDIR}/git_clone_checkout
UBOOT_REPO = https://github.com/Digilent/u-boot-digilent.git
UBOOT_COMMIT = e2382ceaffc0c36dc21c01576c1e454af0e01ca1
UBOOT_CONFIG = ${BOOTSRCDIR}/u-boot.config
UBOOT_MAKE_ARGS = CROSS_COMPILE=arm-linux-gnueabihf- ARCH=arm -j4

bootimg: ${BOOTDIR}/BOOT.bin

${BOOTDIR}/BOOT.bin: ${BOOTSRCDIR}/zynq.bif ${WORKDIR}/fsbl.elf ${WORKDIR}/u-boot.elf ${WORKDIR}/bitstream.bit
	cd ${WORKDIR} && bootgen -image ${BOOTSRCDIR}/zynq.bif -o $(realpath ${BOOTDIR})/BOOT.bin -w

${WORKDIR}:
	mkdir ${WORKDIR}

${WORKDIR}/fsbl.elf: ${WORKDIR}/fsbl/executable.elf
	cp $< $@

${WORKDIR}/fsbl/executable.elf: ${WORKDIR}/pynq.hdf
	cd ${WORKDIR} && hsi -mode batch -source ${BOOTSRCDIR}/create_zynq_fsbl.tcl

${WORKDIR}/pynq.hdf: | ${WORKDIR}
	cd ${WORKDIR} && vivado -mode batch -source ${BOOTSRCDIR}/create_zynq_hdf.tcl

${WORKDIR}/u-boot.elf: ${WORKDIR}/u-boot/u-boot
	cp $< $@

${WORKDIR}/u-boot/u-boot: ${WORKDIR}/u-boot/.config
	cd ${WORKDIR}/u-boot && make ${UBOOT_MAKE_ARGS} u-boot

${WORKDIR}/u-boot/.config: ${UBOOT_CONFIG} | ${WORKDIR}/u-boot
	cp $< $@

${WORKDIR}/u-boot:
	${GIT_CLONE_CHECKOUT} ${UBOOT_REPO} ${UBOOT_COMMIT} ${WORKDIR}/u-boot

${WORKDIR}/bitstream.bit: ${BOOT_BITSTREAM} 
	cp $< $@

clean:
	rm -rf ${WORKDIR}