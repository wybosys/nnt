
# import "Core.h"
# import "pynnt.h"
# import "nnt.modules.h"
# import "nnt.core.h"

NNT_BEGIN_OBJC

static PyObject* _info(PyObject *hdl, PyObject *args) {
    return Py_BuildValue("s", "Python Bridge of NNT. 2011.");
}

static PyMethodDef _methods[] = {
    {"info",  _info, METH_VARARGS, "Get info for PyNNT."},
    {NULL, NULL, 0, NULL}
};

static PyObject *_exception = nil;

void PyNNT_LoadModules() {
    PyObject* m = Py_InitModule("nnt", _methods);
    
    if (m == NULL)
        return;
    
    _exception = PyErr_NewException("nnt.error", NULL, NULL);
    Py_INCREF(_exception);
    PyModule_AddObject(m, "error", _exception);
    
    // load modules.
    // load core module.
    PyNNT_LoadCoreModule(m);
}

NNT_END_OBJC