cd ..

make clean

export DEV_iOS=/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer 
export SDK_iOS=${DEV_iOS}/SDKs/iPhoneOS6.0.sdk 
export COMPILER_iOS=${DEV_iOS}/usr/bin
export CC=${COMPILER_iOS}/gcc
export CXX=${COMPILER_iOS}/g++
export LDFLAGS="-arch armv7s -pipe -Os -gdwarf-2 -no-cpp-precomp -mthumb -isysroot ${SDK_iOS}"
export CFLAGS=${LDFLAGS}
export CXXFLAGS=${LDFLAGS}
export CPP="/usr/bin/cpp ${CPPFLAGS}"
export LD=${COMPILER_iOS}/ld
export AR=${COMPILER_iOS}/ar
export AS=${COMPILER_iOS}/as
export NM=${COMPILER_iOS}/nm
export RANLIB=${COMPILER_iOS}/ranlib
export GUESSOS=armv7s-apple-iphoneos
export CROSS_TOP=${DEV_iOS}
export CROSS_SDK=iPhoneOS6.0.sdk
export MACHINE=armv7s

../config

#LDFLAGS="-arch armv7s -pipe -Os -gdwarf-2 -no-cpp-precomp -mthumb -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS6.0.sdk"

make