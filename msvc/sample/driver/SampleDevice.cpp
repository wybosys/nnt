
# include "common.h"
# include "SampleDevice.h"

# ifdef NNT_USER_SPACE

# include <nnt/Core/File+NNT.h>

NNTAPP_BEGIN

class App
    : public cross::Console
{
public:

    void load()
    {
        File fd;
        if (!fd.open(core::DeviceUrl<>("NntSampleDriver"), 
            mask_t().on<Io::read>().on<Io::write>()))
        {
            trace_msg("failed to open device.");
            return;
        }

        trace_msg("success");
        fd.close();
    }

};

NNTAPP_END

int main(int argc, char* argv[])
{
    ::nntapp::App app;
    return app.execute(argc, argv);
}

# endif

# ifdef NNT_KERNEL_SPACE

NNTDECL_DRIVER_APP(::nntapp::Sample)

NNTAPP_BEGIN

Sample::Sample()
{
    name = "NntSampleDriver";
}

Sample::~Sample()
{

}

int Sample::main()
{
    NNTDEBUG_BREAK;
    return 0;
}

NNTAPP_END

# endif
