
# include "Core.h"
# include "Python+NNT.h"
# include "python.site.prv/pynnt.h"
# include "python.site.prv/nnt.modules.h"

NNT_BEGIN_C

NNTVAR_USE(int) Py_NoSiteFlag;

static void PyNnt_InitSite()
{
    PyObject *m;
    m = PyImport_ImportModule("site");
    if (m)
    {
        Py_DECREF(m);
    }
}

static int PyNnt_Profile(PyObject* obj, PyFrameObject* frame, int what, PyObject* arg)
{
    return 0;
}

static int PyNnt_Trace(PyObject* obj, PyFrameObject* frame, int what, PyObject* arg)
{
    return 0;
}

NNT_END_C

NNT_BEGIN_CXX

NNT_BEGIN_NS(python)

NNT_EXTERN core::string pynnt_stdout_buffer;

NNT_END_NS

NNT_BEGIN_NS(script)

class PyNnt_Environment
{
public:

    PyNnt_Environment()
    {
        Py_NoSiteFlag = 1;
        Py_SetProgramName(pystr("PyNNT"));

        static core::string path_library = GetPythonLibraryPath();
        Py_SetPythonHome(pystr(path_library.c_str()));

        Py_InitializeEx(0);
        PyNnt_InitSite();
        PyNnt_LoadModules();

        PyEval_SetProfile(PyNnt_Profile, NULL);
        PyEval_SetTrace(PyNnt_Trace, NULL);

        PyErr_Clear();
    }

    ~PyNnt_Environment()
    {
        if (Py_IsInitialized())
            Py_Finalize();
    }

};

void UsePython()
{
    static const PyNnt_Environment py_env;
}

void Stdio::flush()
{
    _out = python::pynnt_stdout_buffer;
    python::pynnt_stdout_buffer.clear();
}

core::string const& Stdio::out() const
{
    return _out;
}

NNTDECL_PRIVATE_BEGIN_CXX(Python)

void init()
{
    UsePython();
}

void dealloc()
{

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

bool Python::run_file(core::uri const& file)
{
    core::string str = file;
    FILE* fp = fopen(str.c_str(), "r");
    if (fp == NULL)
        return false;
    core::string fn = file.filename();
    int sta = PyRun_SimpleFile(fp, fn.c_str());
    fclose(fp);
    bool ret = sta == 0;

# ifdef NNT_DEBUG

    if (!ret)
    {
        core::string msg = PyNnt_ErrorMessage();
        trace_msg(msg);
    }

# endif

    return ret;
}

NNT_END_NS
NNT_END_CXX
