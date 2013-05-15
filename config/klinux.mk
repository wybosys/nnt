
WORK_DIR := $(shell pwd)
KERNEL_VER := $(shell uname -r)
KERNEL_SRC_DIR = /usr/src/kernels/$(KERNEL_VER)
KERNEL_MOD_DIR = /lib/modules/$(KERNEL_VER)
NNT_DIR = /develop/nnt/
NNT_LIB_DIR = $(NNT_DIR)/lib/Build

obj-m := $(NAME).o
LINUXINCLUDE += -I${NNT_DIR} -I/usr/include/sys

ifeq ($V,1)
Q=
STDIO=
else
Q=@
STDIO= 1>/dev/null 2>/dev/null
endif

NNT_CFLAGS = -DLIBNNT -DKERNELNNT

ifdef DEBUG
NNT_CFLAGS_DEBUG += -D_DEBUG -g
endif

NNT_CFLAGS += $(NNT_CFLAGS_DEBUG)

ccflags-y := $(NNT_CFLAGS)

NNT_INCLUDE_ALONE = -I $(KERNEL_SRC_DIR)/include/ -I $(KERNEL_SRC_DIR)/arch/x86/include/ -isystem /usr/lib/gcc/x86_64-redhat-linux/4.7.2/include -I$(KERNEL_SRC_DIR)/arch/x86/include -Iarch/x86/include/generated -Iinclude -include$(KERNEL_SRC_DIR)/include/linux/kconfig.h -I $(NNT_DIR) -I /usr/include/sys
NNT_PREPROCESSOR_ALONE = -D__KERNEL__ -DCONFIG_AS_CFI=1 -DCONFIG_AS_CFI_SIGNAL_FRAME=1 -DCONFIG_AS_CFI_SECTIONS=1 -DCONFIG_AS_FXSAVEQ=1 -DCONFIG_AS_AVX=1 -DCC_HAVE_ASM_GOTO -DMODULE
NNT_CFLAGS_ALONE = -fno-strict-aliasing -fno-common -fno-delete-null-pointer-checks -O2 -m64 -mtune=generic -mno-red-zone -mcmodel=kernel -funit-at-a-time -maccumulate-outgoing-args -fstack-protector  -pipe -fno-asynchronous-unwind-tables -mno-sse -mno-mmx -mno-sse2 -mno-3dnow -mno-avx -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-strict-overflow -fconserve-stack -pg $(NNT_CFLAGS)
NNT_CXXFLAGS_ALONE = $(NNT_CFLAGS_ALONE) -fno-operator-names -fno-exceptions -fpermissive

# nnt all
nntall: nnt_prepare all nnt_sources nnt_link nnt_check
	$(Q)echo "completed."

all:
	$(MAKE) -C $(KERNEL_MOD_DIR)/build M=$(WORK_DIR) modules

clean:
	$(MAKE) -C $(KERNEL_MOD_DIR)/build M=$(WORK_DIR) clean	
	$(RM) Module.markers modules.order

# source target
%.cpp.o: %.cpp
	$(Q)$(CXX) $(NNT_INCLUDE_ALONE) $(NNT_PREPROCESSOR_ALONE) $(NNT_CXXFLAGS_ALONE) -o $@ -c $< $(STDIO)

# search source target
nnt_sources_target =

define CPP_TARGET

# add a source (cpp)
nnt_sources_target += $(1).o

endef 

# search in SRC variable
$(foreach i, $(SRC), $(eval $(call CPP_TARGET, $(i))))

PHONY += FORCE
FORCE:

PHONY += nnt_prepare
nnt_prepare:
	@if [ ! -e $(NAME).c ] ; then ln -s ${NNT_DIR}/Classes/Kernel/linuxmod.c $(NAME).c ; fi

PHONY += nnt_sources
nnt_sources: $(nnt_sources_target)

PHONY += nnt_link
nnt_link:
	$(Q)if [ ! -d nntlib ] ; then mkdir nntlib; fi
	$(Q)cd nntlib; find ${NNT_LIB_DIR} -name "*.a" -exec ar -x {} \;
	$(Q)$(LD) -r -m elf_x86_64 -T $(KERNEL_SRC_DIR)/scripts/module-common.lds --build-id -o $(NAME).ko $(NAME).o $(NAME).mod.o $(nnt_sources_target) nntlib/*.o

PHONY += nnt_check
nnt_check:
	$(Q)undefs=`python $(NNT_DIR)/config/chkmod.py $(NAME).ko`; \
	count=`echo -e $$undefs | wc -w`; \
	if [ $$count -gt 0 ]; \
	then \
		echo -e "\e[0;31;1mERROR: undefine $$undefs ! \e[0m"; \
	else \
		echo -e "\e[0;32;1mCHECK: passed. \e[0m"; \
	fi

.PHONY: $(PHONY)
