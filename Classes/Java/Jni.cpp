
# include "Core.h"
# include "Jni.h"
# include <jni.h>

NNT_BEGIN_C

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
	return JNI_VERSION_1_2;
}

JNIEXPORT void JNI_OnUnload(JavaVM* vm, void* reserved)
{

}

JNIEXPORT void JNICALL Java_com_nnt_Java_Test(JNIEnv* env, jobject obj)
{

}

NNT_END_C

NNT_BEGIN_CXX
NNT_BEGIN_NS(java)


NNT_END_NS
NNT_END_CXX
