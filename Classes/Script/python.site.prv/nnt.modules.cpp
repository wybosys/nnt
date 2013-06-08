
# include "Core.h"
# include "pynnt.h"
# include "nnt.modules.h"
# include "nnt.core.h"

NNT_BEGIN_C

static PyMethodDef gs_methods[] = {
    {0, 0, 0, 0}
};

void PyNnt_LoadModules()
{
    PyObject* m = Py_InitModule("nnt", gs_methods);

    PyNnt_LoadCoreModule(m);

    Py_DECREF(m);
}

NNT_END_C
