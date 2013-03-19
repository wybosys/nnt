// sysinfo.cpp : Defines the entry point for the console application.
//

# include <wsi/WSIFoundation.h>
# include <wsi/WTL/Device+WSI.h>

WSIAPP_BEGIN

class App
    : public cross::Console
{
public:

    void load()
    {
# define OUTPUT(name, val) ::std::cout << name << ": " << val << ::std::endl;

        // cpu
        {
            wtl::cpu::Info<> cpuid;
            OUTPUT("CPU", "");
            OUTPUT("Family", cpuid.vid());
            OUTPUT("No.", core::type_cast<core::string>(cpuid.serialno()));
        }

        // bios.
        {
            wtl::dev::Bios<> bios;
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
            wtl::dev::Mainboard<> mb;
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
            wtl::dev::Disk<> dk;
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
            wtl::dev::Memory<> mem;
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

WSIAPP_END

int main(int argc, char* argv[])
{
    ::wsiapp::App app;
    return app.execute(argc, argv);
}
