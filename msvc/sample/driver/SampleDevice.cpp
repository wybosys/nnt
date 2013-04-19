
# include "common.h"
# include "SampleDevice.h"

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
    return 0;
}

NNTAPP_END

# endif
