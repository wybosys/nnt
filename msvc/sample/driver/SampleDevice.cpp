
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
            printf("failed to open device.\n error: %s.\n", Syserr::Sys().to_string().c_str());           
            return;
        }

        core::data da = core::dup_cast<core::data, core::string>("ABCDEFG");
        if (fd.write(da))
            printf("writen data %s.\n", da.c_str());
        else
            printf("failed to write data.\n");

        da.fill(0);
        if (fd.read(da))
            printf("readed: %s.\n", da.c_str());
        else
            printf("failed to read data.\n");

        FileIo io(fd);
        if (io.control(driver::feature::CallIo<1>()))
        {
            printf("success invoke ioctl.\n");
            printf("receive: %s.\n", io.receive.bytes());
        }
        else
        {
            printf("failed invoke ioctl.\n");
            printf("error: %s.\n", Syserr::Sys().to_string().c_str());
        }

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

NNTDECL_DRIVER_APP(::nntapp::Sample, NntSampleDriver);

NNTAPP_BEGIN

Sample::Sample()
{

}

Sample::~Sample()
{

}

int Sample::main()
{
    trace_msg("register sample features");
    
    // bind feature.
    add_feature(new driver::feature::Open);
    add_feature(new driver::feature::Close);
    add_feature(new SampleWrite);
    add_feature(new SampleRead);

    // bind function.
    add_feature(new SampleFunction);

    return 0;
}

SampleWrite::SampleWrite()
{
    pmp_impl_cd();
    pmp_impl(main);
}

void SampleWrite::main()
{
    NNTDEBUG_BREAK;

    core::data da = data();
    core::string str = core::type_cast<core::string>(da);
    trace_msg(str);

    success(da.length());
}

SampleRead::SampleRead()
{
    pmp_impl_cd();
    pmp_impl(main);
}

void SampleRead::main()
{
    NNTDEBUG_BREAK;

    core::data da = data();
    da.fill('a');

    success(da.length());
}

SampleFunction::SampleFunction()
{
    pmp_impl_cd();
    pmp_impl(main);
}

void SampleFunction::main()
{
    NNTDEBUG_BREAK;

    writer.fill('c');

    success(writer.length());
}

NNTAPP_END

# endif
