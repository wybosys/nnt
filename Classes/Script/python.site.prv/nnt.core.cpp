
# include "Core.h"
# include "pynnt.h"
# include "nnt.core.h"

NNT_USINGCXXNAMESPACE;

NNT_BEGIN_C

core::string pynnt_stdout_buffer;

static PyObject* stdio_write(PyObject* obj, PyObject* args)
{
    char const* what;
    if (!PyArg_ParseTuple(args, "s", &what))
        return NULL;
    pynnt_stdout_buffer += what;
    return Py_BuildValue("");
}

static PyObject* stdio_flush(PyObject* obj, PyObject* args)
{
    pynnt_stdout_buffer.clear();
    return Py_BuildValue("");
}

static PyMethodDef stdio_methods[] = {
    {"write", stdio_write, METH_VARARGS, "capature stdout"},
    {"flush", stdio_flush, METH_VARARGS, "flush stdout"},
    {0, 0, 0, 0}
};

void PyNnt_LoadCoreModule(PyObject* m)
{
    PyObject* m_stdio = Py_InitModule("_nnt.core.stdio.capature", stdio_methods);
    PySys_SetObject("stdout", m_stdio);
    PySys_SetObject("flush", m_stdio);
}

NNT_END_C
