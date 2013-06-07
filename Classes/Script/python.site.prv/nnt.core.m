
# import "Core.h"
# import "pynnt.h"
# import "nnt.core.h"

NNT_BEGIN_OBJC

static PyObject* _msgbox(PyObject *hdl, PyObject *args) {
    char const* str = nil;
    
    if (!PyArg_ParseTuple(args, "s", &str))
        return NULL;
    
    [Msgbox info:[NSString stringWithUTF8String:str]];

    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef _methods[] = {    
    {"msgbox", _msgbox, METH_VARARGS, "Msgbox"},
    {NULL, NULL, 0, NULL}
};

static PyObject *_exception = nil;

PyMODINIT_FUNC PyNNT_LoadCoreModule(PyObject* nnt) {    
    PyObject* m = Py_InitModule("nnt.core", _methods);
    if (m == NULL)
        return;
    
    _exception = PyErr_NewException("nnt.core.error", NULL, NULL);
    Py_INCREF(_exception);
    PyModule_AddObject(m, "error", _exception);
    
    Py_INCREF(m);
    PyModule_AddObject(nnt, "core", m);
}

NNT_END_OBJC
