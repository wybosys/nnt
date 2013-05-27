
# include <nnt/Foundation+NNT.h>

# include <nnt/HGC/OCLInfo.h>
# include <nnt/HGC/OCLMath.h>

# include <nnt/HGC/CudaInfo.h>

int main(int argc, const char * argv[])
{
    NNT_USINGNAMESPACE;
    
    {
        opencl::Info info;
        core::string str = info.name();
    
        trace_msg(str);
        str = info.vendor();
        trace_msg(str);
    
        core::vector<float> in;
        in << 1.f << 2.f << 3.f << 4.f << 5.f << 6.f << 7.f;
        opencl::square(core::pointer(in), core::pointer(in), NNTOpenCLValueTypeFloat, in.size());
    }
    
    {
        using namespace std;
        cuda::Info info;
        cout << "version: " << info.version() << endl
        << "count: " << info.device().Count() << endl
        << "name: " << info.name() << endl
        << "memory: " << core::MemoryPresention<>::M(info.total_memory()) << endl
        << "processor count: " << info.processor_count() << endl;

    }
    
    return 0;
}

