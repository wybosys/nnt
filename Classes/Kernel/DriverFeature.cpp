
# include "Core.h"
# include "DriverFeature.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(driver)

# ifdef NNT_KERNEL_SPACE

Feature::Feature()
# ifdef NNT_MSVC
: irptype(0), dispatch(NULL), device(NULL), irp(NULL), status(STATUS_NOT_IMPLEMENTED)
# endif
{
    pmp_impl(main);
}

Feature::~Feature()
{

}

void Feature::main()
{
    NNTDEBUG_BREAK;
}

NNT_BEGIN_NS(feature)

# ifdef NNT_MSVC

# define _NNTIMPL_DRIVER_DISP(name) \
    Feature* feature_##name = NULL; \
    _NNTDECL_DRIVER_DISP(name) \
{ \
    feature_##name->device = dev; \
    feature_##name->irp = irp; \
    pmp_call(feature_##name, main, ()); \
    return feature_##name->status; \
}

_NNTIMPL_DRIVER_DISP(create);
_NNTIMPL_DRIVER_DISP(read);
_NNTIMPL_DRIVER_DISP(write);

Create::Create()
{
    feature_create = this;
}

Read::Read()
{
    feature_read = this;
}

Write::Write()
{
    feature_write = this;
}

# endif

NNT_END_NS

# endif

NNT_END_NS
NNT_END_CXX
