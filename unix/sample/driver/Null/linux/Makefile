
obj-m := sample.o

WORK_DIR := $(shell pwd)
KERNEL_VER := $(shell uname -r)
KERNEL_SRC_DIR = /usr/src/kenels/$(KERNEL_VER)/
KERNEL_MOD_DIR = /lib/modules/$(KERNEL_VER)/

all:
	$(MAKE) -C $(KERNEL_MOD_DIR)/build M=$(WORK_DIR) modules

clean:
	$(MAKE) -C $(KERNEL_MOD_DIR)/build M=$(WORK_DIR) clean	
	$(RM) Module.markers modules.order
