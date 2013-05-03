
WERROR =

.if defined(DEBUG)
NNT_CFLAGS_DEBUG += -D_DEBUG -g
.endif

NNT_DIR = /develop/nnt
NNT_HEADERS = -I${NNT_DIR} -I${NNT_DIR}/nnt/Core
NNT_CFLAGS = -DLIBNNT -DKERNELNNT ${NNT_HEADERS} ${NNT_CFLAGS_DEBUG}
NNT_CXXFLAGS = -fno-exceptions -fno-rtti -fno-cxa-atexit

CC = clang
CXX = clang++
CPP = clang++

CFLAGS += ${NNT_CFLAGS}
CXXFLAGS += ${NNT_CXXFLAGS}

# extract nnt libs.
NNT_LIBRARY = ${NNT_DIR}/lib/Build/*.a
nntlib.o:	
	@${CC} -x c -c -o nntlib.o - < /dev/null # create nnt empty object.
	@if [ ! -d nntlib ]; then mkdir nntlib; fi
	@cd nntlib; find ${NNT_LIBRARY} -name "*.a" -exec ar -x {} \;
OBJS += nntlib.o
OBJS += nntlib/*.o

# system makefile.
.include <bsd.kmod.mk>
