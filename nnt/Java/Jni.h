
# ifndef __NNT_JNI_A08636757F00437F8AFF10B79F636BC4_H_INCLUDED
# define __NNT_JNI_A08636757F00437F8AFF10B79F636BC4_H_INCLUDED

# ifdef NNT_TARGET_ANDROID

# include <jni.h>

# endif

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(java)

NNTCLASS(Jni);
NNTCLASS(Class);
NNTCLASS(Method);

template <typename T>
class Handle
{
public:

    Handle(T h = NULL)
        : _h(NULL)
    {
        set(h);
    }

    Handle(Handle const& r)
        : _h(NULL)
    {
        set(r._h);
    }

    ~Handle()
    {
        set(NULL);
    }

    void set(T r)
    {        
        _h = r;
    }

    Handle& operator = (T r)
    {
        set(r);
        return *this;
    }

    operator T () const
	{
    	return (T)_h;
	}

protected:

    T _h;
    
};

class Method
{
protected:

    typedef
# ifdef JNI_H_
    jmethodID
# else
    void*
# endif
    handle_type;
    
public:

    Method();
    ~Method();

protected:

    Handle<handle_type> _h;

    friend class Jni;
    friend class Class;
};

class Class
{
protected:

    typedef
# ifdef JNI_H_
    jclass
# else
    void*
# endif
    handle_type;
    
public:

    Class();
    ~Class();

    Method static_method(core::string const& name, core::string const& paramcode) const;

protected:

    Jni const* _jni;
    Handle<handle_type> _h;

    friend class Jni;
};

NNTDECL_PRIVATE_HEAD_CXX(Jni);

class Jni
{
    NNTDECL_PRIVATE_CXX(Jni);
    
public:

	Jni();
	~Jni();

    Class find_class(core::string const&) const;
    
private:

    friend class Class;

};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

