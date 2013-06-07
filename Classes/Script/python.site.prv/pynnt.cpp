
# include "Core.h"
# include "pynnt.h"

# include "../../Core/Boost+NNT.h"
# include <boost/lexical_cast.hpp>

NNT_BEGIN_HEADER_C

# include <python/Include/frameobject.h>

NNT_END_HEADER_C

NNT_BEGIN_CXX

::nnt::core::string PyNNT_ToString(PyObject* __obj) 
{
    ::nnt::core::string r_str;
    
	if (!__obj)
		return r_str;
    
	if (PyBytes_Check(__obj))
	{
		r_str += PyBytes_AsString(__obj);
	}
	else if (PyUnicode_Check(__obj))
	{
		PyObject* p_mbcs = PyUnicode_AsASCIIString(__obj);
		r_str = PyNNT_ToString(p_mbcs);
		Py_CLEAR(p_mbcs);
	}
	else if (PyTuple_Check(__obj))
	{
		Py_ssize_t t_s = PyTuple_GET_SIZE(__obj);
		if (t_s)
		{
			PyObject* p_obj = PyTuple_GetItem(__obj, 0);
			r_str = PyNNT_ToString(p_obj);
		}
		for (Py_ssize_t t_i = 1; t_i < t_s; ++t_i)
		{
			PyObject* p_obj = PyTuple_GetItem(__obj, t_i);
			r_str += "," + PyNNT_ToString(p_obj);
		}
	}
	else if (PyList_Check(__obj))
	{
		Py_ssize_t t_s = PyList_GET_SIZE(__obj);
		if (t_s)
		{
			PyObject* p_obj = PyList_GetItem(__obj, 0);
			r_str = PyNNT_ToString(p_obj);
		}
		for (Py_ssize_t t_i = 1; t_i < t_s; ++t_i)
		{
			PyObject* p_obj = PyList_GetItem(__obj, t_i);
			r_str += "," + PyNNT_ToString(p_obj);
		}
	}
	else if (PyLong_Check(__obj))
	{
		r_str = ::boost::lexical_cast< ::nnt::core::string>(PyLong_AsLong(__obj));
	}
	else if (PyFloat_Check(__obj))
	{
		r_str = ::boost::lexical_cast< ::nnt::core::string>(PyFloat_AsDouble(__obj));
	}
	else if (PyBool_Check(__obj))
	{
		r_str = ::boost::lexical_cast< ::nnt::core::string>(__obj == Py_True);
	}
	else
	{
        trace_msg("python: out of type.");
	}
    
	return r_str;
}

::nnt::core::string PyNNT_ErrorMessage()
{
    ::nnt::core::string ret_str = "";
    
    PyObject* p_type;
	PyObject* p_value;
	PyObject* p_traceback;
        
	//PyErr_Fetch(&p_type, &p_value, &p_traceback);
    p_type = PySys_GetObject((char*)"last_type");
    p_value = PySys_GetObject((char*)"last_value");
    p_traceback = PySys_GetObject((char*)"last_traceback");
    
	if (!p_type && !p_value && !p_traceback )
	{
		ret_str = "sucessful\n";
		return ret_str;
	}
    
	if (p_type)
	{
		PyObject* p_str = PyObject_Str(p_type);
		ret_str += "ERROR TYPE: \n\t" + PyNNT_ToString(p_str) + "\n";
		Py_CLEAR(p_str);
	}
    
	if (p_value)
	{
		ret_str += "ERROR MESSAGE: \n\t" + PyNNT_ToString(p_value) + "\n";
	}
    
	if (p_traceback)
	{
		PyTracebackObject* p_tk = (PyTracebackObject*)p_traceback;
        
		ret_str += "TRACEBACK MESSAGE: \n";
        
		while (p_tk)
		{
			PyCodeObject* p_code = p_tk->tb_frame->f_code;
            
			ret_str += "\tname: " + PyNNT_ToString(p_code->co_name) + "\n";            
			ret_str += "\tfilename: " + PyNNT_ToString(p_code->co_filename) + "\n";            
			ret_str += "\tlinenum: " + ::boost::lexical_cast< ::nnt::core::string>(p_tk->tb_lineno) + "\n";
            
			p_tk = p_tk->tb_next;
		}
	}
    
	Py_CLEAR(p_type);
	Py_CLEAR(p_value);
	Py_CLEAR(p_traceback);
    
    /*
    PySys_SetObject((char*)"last_type", 0);
    PySys_SetObject((char*)"last_value", 0);
    PySys_SetObject((char*)"last_traceback", 0);
     */
    
    return ret_str;
}

NNT_BEGIN_NS(script)

# ifdef NNT_WINDOWS

core::string GetPythonLibraryPath()
{
    return "python";
}

# endif

NNT_END_NS

NNT_END_CXX
