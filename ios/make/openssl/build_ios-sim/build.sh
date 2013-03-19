export DEV_iSimulator=/Developer/Platforms/iPhoneSimulator.platform/Developer 
export SDK_iSimulator=${DEV_iSimulator}/SDKs/iPhoneSimulator4.3.sdk 
export COMPILER_iSimulator=${DEV_iSimulator}/usr/bin
export CC=${COMPILER_iSimulator}/gcc
export CXX=${COMPILER_iSimulator}/g++
export LDFLAGS="-arch i386 -pipe -Os -gdwarf-2 -no-cpp-precomp -mthumb -isysroot ${SDK_iSimulator}"
export CFLAGS=${LDFLAGS}
export CXXFLAGS=${LDFLAGS}
export CPP="/usr/bin/cpp ${CPPFLAGS}"
export LD=${COMPILER_iSimulator}/ld
export AR=${COMPILER_iSimulator}/ar
export AS=${COMPILER_iSimulator}/as
export NM=${COMPILER_iSimulator}/nm
export RANLIB=${COMPILER_iSimulator}/ranlib

../dist/configure -host=i386-apple-darwin10