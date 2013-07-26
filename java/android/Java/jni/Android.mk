LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := NntJava
LOCAL_SRC_FILES := NntJava.cpp

include $(BUILD_SHARED_LIBRARY)
