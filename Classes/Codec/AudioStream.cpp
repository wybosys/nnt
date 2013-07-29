
# include "Core.h"
# include "AudioStream.h"

# ifdef NNT_TARGET_ANDROID

# include <SLES/OpenSLES.h>
# include <SLES/OpenSLES_Android.h>
# include "../Java/Jni.h"
# include "../Java/Android.h"

# endif

NNT_BEGIN_CXX
NNT_BEGIN_NS(audio)

AbstractPCMAudioStream::AbstractPCMAudioStream()
{
    
}

AbstractPCMAudioStream::~AbstractPCMAudioStream()
{
    
}

NNT_END_NS
NNT_END_CXX

# ifdef NNT_TARGET_ANDROID

NNT_BEGIN_CXX
NNT_BEGIN_NS(audio)

PCMAudioStreamAndroid::PCMAudioStreamAndroid()
{
}

PCMAudioStreamAndroid::~PCMAudioStreamAndroid()
{
}

static int GetFileDescriptor(char const* filename, off_t & start, off_t & length)
{
	/*
	JniMethodInfo methodInfo;
	if (! getStaticMethodInfo(methodInfo, "getAssetManager", "()Landroid/content/res/AssetManager;"))
	{
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
		return FILE_NOT_FOUND;
	}
	jobject assetManager = methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);

	AAssetManager* (*AAssetManager_fromJava)(JNIEnv* env, jobject assetManager);
	AAssetManager_fromJava = (AAssetManager* (*)(JNIEnv* env, jobject assetManager))
		dlsym(s_pAndroidHandle, "AAssetManager_fromJava");
	AAssetManager* mgr = AAssetManager_fromJava(methodInfo.env, assetManager);
	assert(NULL != mgr);

	AAsset* (*AAssetManager_open)(AAssetManager* mgr, const char* filename, int mode);
f	AAssetManager_open = (AAsset* (*)(AAssetManager* mgr, const char* filename, int mode))
		dlsym(s_pAndroidHandle, "AAssetManager_open");
	AAsset* Asset = AAssetManager_open(mgr, filename, AASSET_MODE_UNKNOWN);
	if (NULL == Asset)
	{
		//LOGD("file not found! Stop preload file: %s", filename);
		return FILE_NOT_FOUND;
	}

	// open asset as file descriptor
	int (*AAsset_openFileDescriptor)(AAsset* asset, off_t* outStart, off_t* outLength);
	AAsset_openFileDescriptor = (int (*)(AAsset* asset, off_t* outStart, off_t* outLength))
		dlsym(s_pAndroidHandle, "AAsset_openFileDescriptor");
	int fd = AAsset_openFileDescriptor(Asset, &start, &length);
	assert(0 <= fd);

	void (*AAsset_close)(AAsset* asset);
	AAsset_close = (void (*)(AAsset* asset))
		dlsym(s_pAndroidHandle, "AAsset_close");
	AAsset_close(Asset);

	return fd;
	*/
}

bool PCMAudioStreamAndroid::load(core::string const& str)
{
    return false;
}

NNT_END_NS
NNT_END_CXX

NNT_BEGIN_C

JNIEXPORT jboolean Java_com_nnt_codec_audio_PCMStream_load(JNIEnv* env, jobject* obj, jstring file)
{
	return false;
}

NNT_END_C

# endif
