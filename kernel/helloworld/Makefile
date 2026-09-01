TARGET_MODULE=helloworld

# Disable the stack protector: this kernel expects a TLS-based stack canary
# that the on-board compiler cannot generate (undefined __stack_chk_guard).
ccflags-y := -fno-stack-protector -std=gnu99 -Wno-declaration-after-statement

# If we are running by kernel building system
ifneq ($(KERNELRELEASE),)
	obj-m := $(TARGET_MODULE).o	
# If we running without kernel build system
else	
	BUILDSYSTEM_DIR:=/lib/modules/$(shell uname -r)/build
	PWD:=$(shell pwd)

all : 
	# run kernel build system to make module
	$(MAKE) -C $(BUILDSYSTEM_DIR) M=$(PWD) modules
	
clean:
	# run kernel build system to cleanup in current directory
	$(MAKE) -C $(BUILDSYSTEM_DIR) M=$(PWD) clean

install:
	$(MAKE) -C $(BUILDSYSTEM_DIR) M=$(PWD) modules_install
	depmod -A

endif
