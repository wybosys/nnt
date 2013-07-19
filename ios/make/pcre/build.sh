#!/bin/sh

XCODE_DIR=/Applications/Xcode.app/Contents/Developer/Platforms
SIMU_DIR=${XCODE_DIR}/iPhoneSimulator.platform
DEVI_DIR=${XCODE_DIR}/iPhoneOS.platform

SIMU_SDK=${SIMU_DIR}/Developer/SDKs/iPhoneSimulator5.1.sdk
DEVI_SDK=${DEVI_DIR}/Developer/SDKs/iPhoneOS6.1.sdk

SIMU_BIN=${SIMU_DIR}/Developer/usr/bin
DEVI_BIN=${DEVI_DIR}/Developer/usr/bin

# compile simu
export LD=${SIMU_BIN}/ld
export AR=${SIMU_BIN}/ar
export AS=${SIMU_BIN}/as
export NM=${SIMU_BIN}/nm
export RANLIB=${SIMU_BIN}/ranlib
export LDFLAGS="-arch i386 -pipe -Os -gdwarf-2 -no-cpp-precomp -isysroot ${SIMU_SDK}"
export CFLAGS=${LDFLAGS}
export CXXFLAGS=${LDFLAGS}
export CC=${SIMU_BIN}/gcc
export CXX=${SIMU_BIN}/g++

../configure --enable-unicode-properties --prefix=/work/develop/other/stage/pcre/pcre-sim  -host=i386-apple-darwin10

make
make install
make clean

# compile armv7
export CC=${DEVI_BIN}/gcc
export CXX=${DEVI_BIN}/g++
export LD=${DEVI_BIN}/ld
export AR=${DEVI_BIN}/ar
export AS=${DEVI_BIN}/as
export NM=${DEVI_BIN}/nm
export RANLIB=${DEVI_BIN}/ranlib

export LDFLAGS="-arch armv7 -mthumb -pipe -Os -gdwarf-2 -no-cpp-precomp -isysroot ${DEVI_SDK}"
export CFLAGS=${LDFLAGS}
export CXXFLAGS=${LDFLAGS}

../configure --enable-unicode-properties --prefix=/work/develop/other/stage/pcre/pcre-armv7 -host=arm-apple-darwin10

make
make install
make clean

# compile armv7s
export LDFLAGS="-arch armv7s -mthumb -pipe -Os -gdwarf-2 -no-cpp-precomp -isysroot ${DEVI_SDK}"
export CFLAGS=${LDFLAGS}
export CXXFLAGS=${LDFLAGS}

../configure --enable-unicode-properties --prefix=/work/develop/other/stage/pcre/pcre-armv7s -host=arm-apple-darwin10

make
make install
make clean

