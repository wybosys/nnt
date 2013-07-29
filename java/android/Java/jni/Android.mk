LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := NntJava
LOCAL_SRC_FILES := NntJava.cpp \
../src/Jni.cpp \
../src/Android.cpp

LOCAL_C_INCLUDES := \
../../../Classes/Core \
../../../Classes/

LOCAL_LDLIBS := -llog
LOCAL_LDFLAGS := -L../Core/libs/armeabi -lNntCore

include $(BUILD_SHARED_LIBRARY)
