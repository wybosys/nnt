
# include "Core.h"
# include "Jni.h"

# ifdef NNT_TARGET_ANDROID

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
}

void dealloc()
{
    detach();
    vm = NULL;
}

bool attach(JNIEnv* en)
{
    bool ret = true;
    env = en;
    if (env == NULL)
    {
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
    }
    else
    {
        if (vm->AttachCurrentThread(&env, NULL) < 0)
        {
            trace_msg("failed attach java env");
            ret = false;
        }
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
    
Jni::Jni(JNIEnv* env)
{
    NNTDECL_PRIVATE_CONSTRUCT(Jni);

    d_ptr->attach(env);
}

Jni::~Jni()
{
    NNTDECL_PRIVATE_DESTROY();
}

Class Jni::find_class(core::string const& name) const
{
    Class ret;
    ret._jni = this;
    ret._h = (jclass)d_ptr->env->FindClass(name.c_str());
    return ret;
}

String Jni::string(jstring str) const
{
    String ret;
    char const* buf = d_ptr->env->GetStringUTFChars(str, NULL);
    size_t lbuf = d_ptr->env->GetStringUTFLength(str);
    ret._buf = core::string(buf, lbuf);
    d_ptr->env->ReleaseStringUTFChars(str, buf);
    return ret;
}

Class::Class()
    : _jni(NULL)
{
}

Class::~Class()
{
}

Method Class::static_method(core::string const& name, core::string const& param) const
{
    Method ret;
    ret._h = _jni->_d()->env->GetStaticMethodID(_h, name.c_str(), param.c_str());
    return ret;
}

Method::Method()
{
}

Method::~Method()
{
}

String::String()
{
}

String::~String()
{
}

NNT_END_NS
NNT_END_CXX

# endif
