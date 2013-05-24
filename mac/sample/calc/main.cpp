
# include <nnt/Foundation+NNT.h>
# include <nnt/HGC/OCLDevice.h>
# include <nnt/HGC/OCLInfo.h>

int main(int argc, const char * argv[])
{
    NNT_USINGNAMESPACE;
    
    opencl::Device dev;
    opencl::Info info(dev);
    core::string str = info.name();
    
    trace_msg(str);
    str = info.vendor();
    trace_msg(str);
    
    return 0;
}

