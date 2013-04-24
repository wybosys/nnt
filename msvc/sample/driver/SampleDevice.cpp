
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

        core::data da = core::dup_cast<core::data, core::string>("ABCDEFG");
        if (fd.write(da))
            printf("writen data %s.\n", da.c_str());
        else
            printf("failed to write data.\n");

        da.fill(0);
        if (fd.read(da))
            printf("readed: %s\n.", da.c_str());
        else
            printf("failed to read data.\n");

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
    //NNTDEBUG_BREAK;

    // bind feature.
    add_feature(new driver::feature::Create);
    add_feature(new driver::feature::Close);
    add_feature(new SampleWrite);
    add_feature(new SampleRead);

    return 0;
}

SampleWrite::SampleWrite()
{
    pmp_impl(main);
}

void SampleWrite::main()
{
    NNTDEBUG_BREAK;

    core::data da = data();
    trace_msg(da.c_str());

    success(da.length());
}

SampleRead::SampleRead()
{
    pmp_impl(main);
}

void SampleRead::main()
{
    NNTDEBUG_BREAK;

    core::data da = data();
    da.fill('a');

    success(da.length());
}

NNTAPP_END

# endif
