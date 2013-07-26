LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := NntCore
LOCAL_SRC_FILES := NntCore.cpp

include $(BUILD_SHARED_LIBRARY)
