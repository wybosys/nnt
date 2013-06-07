
# include "Core.h"
# include "Python+NNT.h"
# include "python.site.prv/pynnt.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(script)

NNTDECL_PRIVATE_BEGIN_CXX(Python)

void init()
{
    Py_SetProgramName(pystr("PyNNT"));
    
    static core::string path_library = GetPythonLibraryPath();
    Py_SetProgramName(pystr(path_library.c_str()));
    
    Py_InitializeEx(0);
}

void dealloc()
{
    if (Py_IsInitialized())
        Py_Finalize();
}

NNTDECL_PRIVATE_END_CXX

Python::Python()
{
    NNTDECL_PRIVATE_CONSTRUCT(Python);
}

Python::~Python()
{
    NNTDECL_PRIVATE_DESTROY();
}

NNT_END_NS
NNT_END_CXX
