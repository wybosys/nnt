
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
            printf("failed to open device.\n");
            return;
        }

        core::data da = core::type_cast<core::data, core::string>("ABC");
        if (fd.write(da))
            printf("writen data.\n");

        printf("success.\n");
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

    // bind feature.
    add_feature(new driver::feature::Create);
    add_feature(new driver::feature::Read);
    add_feature(new driver::feature::Write);

    return 0;
}

NNTAPP_END

# endif
