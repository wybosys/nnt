LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := NntCodec
LOCAL_SRC_FILES := NntCodec.cpp

include $(BUILD_SHARED_LIBRARY)
