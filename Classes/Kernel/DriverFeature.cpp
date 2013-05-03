
# include "Core.h"
# include "DriverFeature.h"
# include "DriverApp.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(driver)

# ifdef NNT_KERNEL_SPACE

Feature::Feature()
    
# ifdef NNT_MSVC
    : irptype(0), dispatch(NULL), device(NULL), irp(NULL)
# endif

# ifdef NNT_UNIX
    : dftype(0), dispatch(NULL)
# endif

# ifdef NNT_BSD
    , device(NULL), oflags(0), devtype(0), thd(NULL)
# endif
    
{
    app = NULL;
    proccessed = 0;

    pmp_impl(prepare);
    pmp_impl(collect);
    pmp_impl(main);
    pmp_impl(complete);
}

Feature::~Feature()
{

}

void Feature::prepare()
{
    PASS;
}

void Feature::collect()
{
    PASS;
}

void Feature::main()
{
    NNTDEBUG_BREAK;
}

void Feature::complete()
{
# ifdef NNT_MSVC

    irp->IoStatus.Status = status;
    irp->IoStatus.Information = proccessed;
    IoCompleteRequest(irp, IO_NO_INCREMENT);

# endif
}

void Feature::success(usize len)
{
    proccessed = len;
    status.success();
    complete();
}

static App* FeatureToApp(Feature* ftu)
{
    NNTDEBUG_BREAK;
    
# ifdef NNT_MSVC
    
    use<driver::DriverExtension> ext = ftu->device->DeviceExtension;
    return ext->pApp;

# endif

    return NULL;
}

NNT_BEGIN_NS(feature)

# ifdef NNT_MSVC

# define _NNTIMPL_DRIVER_DISP(name)                                 \
    Feature* feature_##name = NULL;                                 \
    _NNTDECL_DRIVER_DISP(name)                                      \
    {                                                               \
        feature_##name->device = dev;                           \
        feature_##name->irp = irp;                              \
        feature_##name->app = FeatureToApp(feature_##name);     \
        pmp_call(feature_##name, prepare, ());                  \
        pmp_call(feature_##name, main, ());                     \
        pmp_call(feature_##name, collect, ());                  \
        return feature_##name->status;                          \
    }

# endif

# ifdef NNT_UNIX

# define _NNTIMPL_DRIVER_DISP(name)             \
    Feature* feature_##name = NULL;             \
    _NNTDECL_DRIVER_DISP(name)                  \
    {                                           \
        return feature_##name->status;          \
    }

# endif

_NNTIMPL_DRIVER_DISP(open);
_NNTIMPL_DRIVER_DISP(close);
_NNTIMPL_DRIVER_DISP(read);
_NNTIMPL_DRIVER_DISP(write);

Open::Open()
{
    feature_open = this;
    pmp_impl(main);
}

void Open::main()
{
    success(0);
}

Close::Close()
{
    feature_close = this;
    pmp_impl(main);
}

void Close::main()
{
    success(0);
}

Read::Read()
{
    feature_read = this;

    pmp_impl(prepare);
}

void Read::prepare()
{
# ifdef NNT_MSVC

    PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(irp);

    switch (app->memory_mode)
    {
    case MEMORY_BUFFER:
        {
            length = stack->Parameters.Read.Length;
            offset = stack->Parameters.Read.ByteOffset.QuadPart;
            buffer = irp->AssociatedIrp.SystemBuffer;
        } break;
    case MEMORY_MAP:
        {
            length = stack->Parameters.Read.Length;
            offset = stack->Parameters.Read.ByteOffset.QuadPart;
            buffer = MmGetSystemAddressForMdlSafe(irp->MdlAddress, NormalPagePriority);
        } break;
    }

# endif
}

core::data Read::data() const
{
    return core::data((byte*)buffer + offset, length, core::assign);
}

Write::Write()
{
    feature_write = this;

    pmp_impl(prepare);
}

void Write::prepare()
{
# ifdef NNT_MSVC

    PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(irp);

    switch (app->memory_mode)
    {
    case MEMORY_BUFFER:
        {
            length = stack->Parameters.Write.Length;
            offset = stack->Parameters.Write.ByteOffset.QuadPart;
            buffer = irp->AssociatedIrp.SystemBuffer;
        } break;
    case MEMORY_MAP:
        {
            length = stack->Parameters.Write.Length;
            offset = stack->Parameters.Write.ByteOffset.QuadPart;
            buffer = MmGetSystemAddressForMdlSafe(irp->MdlAddress, NormalPagePriority);
        } break;
    }

# endif
}

core::data Write::data() const
{
    return core::data((byte*)buffer + offset, length, core::assign);
}

NNT_END_NS

# endif

NNT_END_NS
NNT_END_CXX
