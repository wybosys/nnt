
# include "Core.h"
# include "Module.h"
# include <dlfcn.h>
# include "../TL/URI+NNT.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(core)

NNTDECL_PRIVATE_BEGIN_CXX(Module)

void init()
{
    handle = NULL;
}

void dealloc()
{
    close();
}

void close()
{
    if (handle)
    {
        dlclose(handle);
        handle = NULL;
    }
}

void* handle;

NNTDECL_PRIVATE_END_CXX

Module::Module()
{
    NNTDECL_PRIVATE_CONSTRUCT(Module);
}

Module::Module(core::string const& str)
{
    NNTDECL_PRIVATE_CONSTRUCT(Module);
    
    open(str);
}

Module::~Module()
{
    NNTDECL_PRIVATE_DESTROY();
}

bool Module::open(core::string const& str)
{
    close();
    
    core::uri file(str);
    file.filename() = PrefixName() + file.filename() + "." + ExtName();
    
    core::string fp = file.combine();
    d_ptr->handle = dlopen(fp.c_str(), RTLD_LAZY);
    if (d_ptr->handle == NULL)
        d_ptr->handle = dlopen(str.c_str(), RTLD_LAZY);
    
    if (d_ptr->handle == NULL)
        trace_msg("failed to open shared library");
    
    return d_ptr->handle != NULL;
}

void Module::close()
{
    d_ptr->close();
}

core::string Module::PrefixName()
{
# ifdef NNT_UNIX
    return "lib";
# endif
    
    return "";
}

core::string Module::ExtName()
{
# ifdef NNT_WINDOWS
    return "dll";
    
# else
    
    return "so";
    
# endif
}

bool Module::is_opened() const
{
    return d_ptr->handle != NULL;
}

void* Module::find(core::string const& name) const
{
# ifdef NNT_WINDOWS
    
# else
    
    void* ret = dlsym(d_ptr->handle, name.c_str());
    if (ret == NULL)
        trace_msg(dlerror());
    
    return ret;
    
# endif
}

NNT_END_NS
NNT_END_CXX
