
# include "Core.h"
# include "AudioStream.h"

# ifdef NNT_TARGET_ANDROID

# include <SLES/OpenSLES.h>
# include <SLES/OpenSLES_Android.h>
# include "../Java/Jni.h"

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

bool PCMAudioStreamAndroid::load(core::string const& str)
{
    return false;
}

NNT_END_NS
NNT_END_CXX

NNT_BEGIN_C

JNIEXPORT jboolean Java_com_nnt_codec_audio_PCMStream_load(JNIEnv* env, jobject* obj, jstring file)
{    
	::nnt::java::Jni jni(env);
	::nnt::java::String str = jni.string(file);
	trace_msg(str);
	return false;
}

NNT_END_C

# endif
