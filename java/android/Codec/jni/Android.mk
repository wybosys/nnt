LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := NntCodec
LOCAL_SRC_FILES := NntCodec.cpp

LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)
