
# include "Core.h"
# include "pynnt.h"
# include "nnt.core.h"
# include "../PythonExtension.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(python)

ntl::string pynnt_stdout_buffer, pynnt_stderr_buffer;

class ModuleStdout
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

    ModuleStdout()
        : Module("_nnt.core.stdio.out.capature")
    {
        add(write);
        add(flush);
    }

    Write write;
    Flush flush;

};

class ModuleStderr
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
            pynnt_stderr_buffer += str;
            return success();
        }

    };

    ModuleStderr()
        : Module("_nnt.core.stdio.err.capature")
    {
        add(write);
    }

    Write write;

};

class ModuleCore
    : public Module
{
public:

    class Version
        : public Method<Version>
    {
    public:

        Version()
        {
            set_name("version");
            set_type(NOARGS);
        }

        static core::Object method(core::Object const&, core::Argument const& args)
        {
            char const* str = NNT_VERSION_STR;
            return core::Value(str);
        }

    };

    ModuleCore()
        : Module("nnt.core")
    {
        add(version);
    }

    Version version;
};

NNT_END_NS
NNT_END_CXX

NNT_BEGIN_C

void PyNnt_LoadCoreModule(PyObject* m)
{
    NNT_USINGCXXNAMESPACE;

    // replace stdio.
    static python::ModuleStdout m_stdout;
    python::System::Set("stdout", m_stdout);
    python::System::Set("flush", m_stdout);

    static python::ModuleStdout m_stderr;
    python::System::Set("stderr", m_stderr);

    // insert core.
    static python::ModuleCore m_core;

    PyModule_AddObject(m, "core", m_core);
}

NNT_END_C
