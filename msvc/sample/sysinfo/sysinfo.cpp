// sysinfo.cpp : Defines the entry point for the console application.
//

# include <nnt/Foundation+NNT.h>
# include <nnt/TL/Device+NNT.h>

NNTAPP_BEGIN

class App
    : public cross::Console
{
public:

    void load()
    {
# define OUTPUT(name, val) ::std::cout << name << ": " << val << ::std::endl;

        // cpu
        {
            ntl::cpu::Info<> cpuid;
            OUTPUT("CPU", "");
            OUTPUT("Family", cpuid.vid());
            OUTPUT("No.", core::type_cast<core::string>(cpuid.serialno()));
        }

        // bios.
        {
            ntl::dev::Bios<> bios;
            OUTPUT("BIOS", "");
            if (bios.is_null())
            {
                OUTPUT("Found", "NO");
            }
            else 
            {
                OUTPUT("Name", bios.name());
                OUTPUT("IdCode", bios.serialno());
                OUTPUT("Manufacturer", bios.manufacturer());
            }
        }

        // main board.
        {
            ntl::dev::Mainboard<> mb;
            OUTPUT("MainBoard", "");
            if (mb.is_null())
            {
                OUTPUT("Found:", "NO");
            }
            else
            {
                OUTPUT("No.", mb.serialno());
            }
        }

        // disk.
        {
            ntl::dev::Disk<> dk;
            OUTPUT("Disk", "");
            if (dk.is_null())
            {
                OUTPUT("Found:", "NO");
            }
            else
            {
                OUTPUT("No.", dk.serialno());
                OUTPUT("IDR", dk.deviceid());
                OUTPUT("Sig", dk.signature());
            }
        }

        // memory.
        {
            ntl::dev::Memory<> mem;
            OUTPUT("Memory", "");
            if (mem.is_null())
            {
                OUTPUT("Found:", "NO");
            }
            else
            {
                OUTPUT("Banklabel", mem.banklabel());
            }
        }
    }

};

NNTAPP_END

int main(int argc, char* argv[])
{
    ::nntapp::App app;
    return app.execute(argc, argv);
}
