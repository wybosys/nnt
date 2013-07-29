LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := NntCore
LOCAL_SRC_FILES := NntCore.cpp \
../src/Core.cpp \
../src/Object.cpp \
../src/Module.cpp \
../src/Time+NNT.cpp \
../src/Task+NNT.cpp

LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)
