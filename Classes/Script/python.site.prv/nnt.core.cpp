
# include "Core.h"
# include "pynnt.h"
# include "nnt.core.h"
# include "../PythonExtension.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(python)

ntl::string pynnt_stdout_buffer;

class ModuleStdio
    : public Module
{
public:

    class Write
        : public Method<Write>
    {
    public:

        Write()
        {
            set_name("write");
        }

        static core::Object method(core::Object const&, core::Argument const& args)
        {
            char const* str = args.to_str();
            if (str == NULL)
                return NULL;
            pynnt_stdout_buffer += str;
            return success();
        }

    };

    class Flush
        : public Method<Flush>
    {
    public:

        Flush()
        {
            set_name("flush");
        }

        static core::Object method(core::Object const&, core::Argument const& args)
        {
            pynnt_stdout_buffer.clear();
            return success();
        }

    };

    ModuleStdio()
        : Module("_nnt.core.stdio.capature")
    {
        add(write);
        add(flush);
    }

    Write write;
    Flush flush;
};

NNT_END_NS
NNT_END_CXX

NNT_BEGIN_C

void PyNnt_LoadCoreModule(PyObject* m)
{
    NNT_USINGCXXNAMESPACE;
    static python::ModuleStdio m_stdio;
    python::System::Set("stdout", m_stdio);
    python::System::Set("flush", m_stdio);
}

NNT_END_C
