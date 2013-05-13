
WORK_DIR := $(shell pwd)
KERNEL_VER := $(shell uname -r)
KERNEL_SRC_DIR = /usr/src/kernels/$(KERNEL_VER)
KERNEL_MOD_DIR = /lib/modules/$(KERNEL_VER)

ifeq (V,1)
Q=
else
Q=@
endif

ifdef DEBUG
NNT_CFLAGS_DEBUG += -D_DEBUG -g
endif

NNT_INCLUDE_ALONE = -I $(KERNEL_SRC_DIR)/include/ -I $(KERNEL_SRC_DIR)/arch/x86/include/ -isystem /usr/lib/gcc/x86_64-redhat-linux/4.7.2/include -I$(KERNEL_SRC_DIR)/arch/x86/include -Iarch/x86/include/generated -Iinclude -include$(KERNEL_SRC_DIR)/include/linux/kconfig.h
NNT_PREPROCESSOR_ALONE = -D__KERNEL__ -DCONFIG_AS_CFI=1 -DCONFIG_AS_CFI_SIGNAL_FRAME=1 -DCONFIG_AS_CFI_SECTIONS=1 -DCONFIG_AS_FXSAVEQ=1 -DCONFIG_AS_AVX=1 -DCC_HAVE_ASM_GOTO -DMODULE
NNT_CFLAGS_ALONE = -fno-strict-aliasing -fno-common -fno-delete-null-pointer-checks -O2 -m64 -mtune=generic -mno-red-zone -mcmodel=kernel -funit-at-a-time -maccumulate-outgoing-args -fstack-protector  -pipe -fno-asynchronous-unwind-tables -mno-sse -mno-mmx -mno-sse2 -mno-3dnow -mno-avx -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-strict-overflow -fconserve-stack -pg $(NNT_CFLAGS_DEBUG)
NNT_CXXFLAGS_ALONE = $(NNT_CFLAGS_ALONE) -fno-operator-names -fno-exceptions -fpermissive

define NNT_LINK
	@echo "successfully!"
endef

# source target
%.cpp.o: %.cpp
	$(Q)$(CXX) $(NNT_INCLUDE_ALONE) $(NNT_PREPROCESSOR_ALONE) $(NNT_CXXFLAGS_ALONE) -o $@ -c $< 1>/dev/null 2>/dev/null

# nnt all
nntall: all nnt_sources nnt_link
	$(call NNT_LINK)

# default target
all:
	$(MAKE) -C $(KERNEL_MOD_DIR)/build M=$(WORK_DIR) modules

clean:
	$(MAKE) -C $(KERNEL_MOD_DIR)/build M=$(WORK_DIR) clean	
	$(RM) Module.markers modules.order

nnt_sources_target =

define CPP_TARGET

nnt_sources_target += $(1).o

$(1).o: $(1) FORCE

endef

$(foreach i, $(SRC), $(eval $(call CPP_TARGET, $(i)))) 

PHONY += FORCE
FORCE:

PHONY += nnt_sources
nnt_sources: $(nnt_sources_target)

PHONY += nnt_link
nnt_link:
	$(Q)$(LD) -r -m elf_x86_64 -T $(KERNEL_SRC_DIR)/scripts/module-common.lds --build-id -o $(NAME).ko sample.o sample.mod.o $(nnt_sources_target)

.PHONY: $(PHONY)
