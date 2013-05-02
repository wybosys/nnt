
WERROR =

NNT_HEADERS = -I/develop/nnt -I/develop/nnt/nnt/Core
NNT_CFLAGS = -DLIBNNT -DKERNELNNT ${NNT_HEADERS}
NNT_CXXFLAGS = 

CC = clang
CXX = clang++
CPP = clang++

CFLAGS += ${NNT_CFLAGS}

.include <bsd.kmod.mk>
