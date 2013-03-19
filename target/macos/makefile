
include ../../unix/objects.mk

SRC_DIR = ../../Classes
CONTRIB_DIR = ../../contrib
INC_DIR = -I../../3rd -I../../3rd/Mac -I/opt/local/include
LIB_DIR = -L../../lib/Mac -L/opt/local/lib
LDWITH += -liconv -lz -lxerces-c -Xlinker -rpath /opt/local/lib

CFLAGS += -g -DDEBUG

include ../../unix/compiles.mk