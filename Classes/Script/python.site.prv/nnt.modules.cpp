
# include "Core.h"
# include "pynnt.h"
# include "nnt.modules.h"
# include "nnt.core.h"

NNT_BEGIN_C

static PyObject* pynnt_test(PyObject*, PyObject*)
{
    trace_msg("call pynnt test function");
    return Py_BuildValue("s", "Nnt + Python is ok");
}

static PyMethodDef gs_methods[] = {
    {"test", pynnt_test, METH_NOARGS, "test"},
    {0, 0, 0, 0}
};

static PyObject* pynnt_error = NULL;

void PyNnt_LoadModules_c()
{
    PyObject* m = Py_InitModule("nnt", gs_methods);
    if (m == NULL)
        return;

    pynnt_error = PyErr_NewException(pystr("nnt.error"), NULL, NULL);
    Py_INCREF(pynnt_error);
    PyModule_AddObject(m, "error", pynnt_error);

    PyNnt_LoadCoreModule(m);
}

NNT_END_C
