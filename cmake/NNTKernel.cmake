
SET (NNT_BUILD_KERNEL 1 CACHE BOOL "build for kernel")

MACRO (source file)
  LIST (APPEND CURRENT_SOURCES ${file})
ENDMACRO ()

MACRO (sourcesub file)
  LIST (APPEND CURRENT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/${file})
ENDMACRO ()

MACRO (NNT_USE_HEADERS)
  INCLUDE_DIRECTORIES (AFTER "${PROJECT_SOURCE_DIR}")
ENDMACRO ()

SET (NNT_KERNEL_SRC "")

IF (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
  EXECUTE_PROCESS (COMMAND uname -r
    OUTPUT_VARIABLE NNT_KERNEL_SRC)
  STRING (REPLACE "\n" "" NNT_KERNEL_SRC ${NNT_KERNEL_SRC})
  SET (NNT_KERNEL_SRC "/usr/src/kernels/${NNT_KERNEL_SRC}")
ENDIF ()

MACRO (NNT_USE_KERNELHEADERS) 
  INCLUDE_DIRECTORIES (AFTER "/usr/include/sys")
ENDMACRO ()

MACRO (NNT_USE_LIBHEADERS)
  INCLUDE_DIRECTORIES (AFTER "${PROJECT_SOURCE_DIR}/Classes")
  INCLUDE_DIRECTORIES (AFTER "${PROJECT_SOURCE_DIR}/Classes/Core")
ENDMACRO ()

SET (NNT_ARCH 32)
IF (CMAKE_SIZEOF_VOID_P EQUAL 8)
  SET (NNT_ARCH 64)
ENDIF ()

# set build rules.

SET (NNT_KERNEL_INCLUDE "")
SET (NNT_KERNEL_C_PREPROCESSORS -DLIBNNT -DKERNELNNT)
SET (NNT_KERNELAPP_C_PREPROCESSORS -DKERNELNNT)
SET (NNT_KERNEL_C_FLAGS "-nostdinc -fno-common -fno-omit-frame-pointer -mno-aes -mno-avx -mcmodel=kernel -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -mno-3dnow -msoft-float -fno-asynchronous-unwind-tables -fstack-protector -fno-builtin -ffreestanding -Wall")
SET (NNT_KERNEL_CXX_FLAGS "-Wno-c++0x-compat -fno-operator-names -fno-exceptions -fno-rtti -fpermissive")

# build for linux-module.
IF (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
  SET (NNT_KERNEL_C_PREPROCESSORS "${NNT_KERNEL_C_PREPROCESSORS} -D__KERNEL__ -DCONFIG_AS_CFI=1 -DCONFIG_AS_CFI_SIGNAL_FRAME=1 -DCONFIG_AS_CFI_SECTIONS=1 -DCONFIG_AS_FXSAVEQ=1 -DCONFIG_AS_AVX=1 -DCC_HAVE_ASM_GOTO -DMODULE")
  SET (NNT_KERNEL_C_FLAGS " -fno-strict-aliasing -fno-common -fno-delete-null-pointer-checks -O2 -m64 -mtune=generic -mno-red-zone -mcmodel=kernel -funit-at-a-time -maccumulate-outgoing-args -fstack-protector  -pipe -fno-asynchronous-unwind-tables -mno-sse -mno-mmx -mno-sse2 -mno-3dnow -mno-avx -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-strict-overflow -fconserve-stack -pg")
  SET (NNT_KERNEL_INCLUDE "-I ${NNT_KERNEL_SRC}/include/ -I ${NNT_KERNEL_SRC}/arch/x86/include/ -isystem /usr/lib/gcc/x86_64-redhat-linux/4.7.2/include -I${NNT_KERNEL_SRC}/arch/x86/include -I${NNT_KERNEL_SRC}/arch/x86/include/generated -Iinclude  -include ${NNT_KERNEL_SRC}/include/linux/kconfig.h")
ENDIF ()

MACRO (NNT_KERNEL_CFLAGS)
  SET (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${NNT_KERNEL_C_FLAGS} ${NNT_KERNEL_INCLUDE}") 
  SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${NNT_KERNEL_C_FLAGS} ${NNT_KERNEL_CXX_FLAGS} ${NNT_KERNEL_INCLUDE}")
ENDMACRO ()
