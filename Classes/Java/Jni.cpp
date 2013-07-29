
# include "Core.h"
# include "Jni.h"

# ifdef NNT_TARGET_ANDROID

# include <jni.h>

NNT_BEGIN_CXX
NNT_BEGIN_NS(java)

static JavaVM* __gs_vm = NULL;

NNT_END_NS
NNT_END_CXX

NNT_BEGIN_C

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
	::nnt::java::__gs_vm = vm;

	trace_msg("Java JNI Loaded");
	return JNI_VERSION_1_2;
}

JNIEXPORT void JNI_OnUnload(JavaVM* vm, void* reserved)
{
	::nnt::java::__gs_vm = NULL;

	trace_msg("Java JNI Unloaded");
}

JNIEXPORT void JNICALL Java_com_nnt_Java_Test(JNIEnv* env, jobject obj)
{

}

NNT_END_C

NNT_BEGIN_CXX
NNT_BEGIN_NS(java)

NNTDECL_PRIVATE_BEGIN_CXX(Jni)

void init()
{
    env = NULL;
    need_detach = false;

    if (__gs_vm == NULL)
        trace_msg("java vm is null");
    vm = __gs_vm;

    attach();
}

void dealloc()
{
    detach();
    vm = NULL;
}

bool attach()
{
    bool ret = true;
    jint code = vm->GetEnv((void**)&env, JNI_VERSION_1_4);
    switch (code)
    {
        case JNI_OK: break;
        case JNI_EDETACHED:
        {
            if (vm->AttachCurrentThread(&env, NULL) < 0)
            {
                trace_msg("failed attach java env");
                ret = false;
            }
            else
            {
                need_detach = true;
            }
        } break;
        case JNI_EVERSION:
        {
            trace_msg("java version 1.4 is not support");
            ret = false;
        } break;
    }
    return ret;
}

void detach()
{
    if (need_detach)
    {
        vm->DetachCurrentThread();
        need_detach = false;
    }
}

JavaVM* vm;
JNIEnv* env;
bool need_detach;

NNTDECL_PRIVATE_END
    
Jni::Jni()
{
    NNTDECL_PRIVATE_CONSTRUCT(Jni);
}

Jni::~Jni()
{
    NNTDECL_PRIVATE_DESTROY();
}

NNT_END_NS
NNT_END_CXX

# endif
