
# include "Core.h"
# include "python.site.prv/pynnt.h"
# include "PythonExtension.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(python)

NNT_BEGIN_NS(core)

# define PO(o) ((PyObject*)o)

Object::~Object()
{
    if (_deref)
    {
        Py_DECREF(_obj);
    }
}

char const* Argument::to_str() const
{
    char const* buf = NULL;
    PyArg_ParseTuple(py(), "s", &buf);
    return buf;
}

Value::Value(char const* s)
{
    _obj = Py_BuildValue("s", s);
}

Value::Value(ntl::string const& s)
{
    _obj = Py_BuildValue("s", s.c_str());
}

NNT_END_NS

_Method::_Method()
{
    _name = "";
    _doc = "";    
    _type = VARARGS;
    _def = (pydef_t) new PyMethodDef;
}

_Method::~_Method()
{
    safe_delete(_def);
}

void _Method::set_name(ntl::string const& str)
{
    _name = str;
}

void _Method::set_doc(ntl::string const& str)
{
    _doc = str;
}

void _Method::set_type(enum_t v)
{
    _type = v;
}

void _Method::update()
{
    use<PyMethodDef> def = _def;
    def->ml_name = _name.c_str();
    def->ml_doc = _doc.c_str();

    def->ml_flags = 0;
    if (MASK_CHECK(VARARGS, _type))
        def->ml_flags |= METH_VARARGS;
    if (MASK_CHECK(NOARGS, _type))
        def->ml_flags |= METH_NOARGS;
    if (MASK_CHECK(KEYWORDS, _type))
        def->ml_flags |= METH_KEYWORDS;        
}

void _Method::_set_imp(void* (*func)(void*, void*))
{
    use<PyMethodDef> def = _def;
    def->ml_meth = (PyCFunction)func;
}

core::Object _Method::success()
{
    return Py_BuildValue("");
}

Module::Module(ntl::string const& name)
: _name(name)
{
    _n = PyString_FromString(name.c_str());
    static PyMethodDef methods[] = {{0, 0, 0, 0}};
    _module = Py_InitModule(name.c_str(), methods);
    _d = PyModule_GetDict(_module);
}

Module::~Module()
{
    Py_DECREF(PO(_n));
}

bool Module::add(_Method::pydef_t _def)
{
    use<PyMethodDef> def = _def;
    PyObject* v = PyCFunction_NewEx(def, NULL, (PyObject*)_n);
    if (v == NULL)
        return false;
    if (PyDict_SetItemString((PyObject*)_d, def->ml_name, v) != 0) 
    {
        Py_DECREF(v);
        return false;
    }

    Py_DECREF(v);
    return true;
}

void Module::add(Module& m)
{
    ntl::string name = m.name();
    usize pos = name.find_last_of('.');
    if (pos != ntl::string::npos)
    {
        name = name.substr(pos + 1);
    }

    PyModule_AddObject(_module, name.c_str(), m);
}

void System::Set(ntl::string const& name, core::Object& obj)
{
    PySys_SetObject(pystr(name.c_str()), PO(obj));
}

NNT_END_NS
NNT_END_CXX
