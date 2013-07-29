LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := NntCodec
LOCAL_SRC_FILES := NntCodec.cpp \
../src/AudioStream.cpp \
../src/AudioPlayer.cpp \
../src/OpenSL+NNT.cpp

LOCAL_LDLIBS := -llog \
-L../Core/libs/armeabi -lNntCore \
-L../Java/libs/armeabi -lNntJava

LOCAL_C_INCLUDES := \
../../../Classes/Core \
../../../Classes/

include $(BUILD_SHARED_LIBRARY)
