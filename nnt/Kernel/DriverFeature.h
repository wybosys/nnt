
# ifndef __NNT_KERNEL_DRIVERFEATURE_55dba2a58c864cce9273145b03dc3365_H_INCLUDED
# define __NNT_KERNEL_DRIVERFEATURE_55dba2a58c864cce9273145b03dc3365_H_INCLUDED

# include "./DriverObject.h"
# include "../TL/Class+NNT.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(driver)

# ifdef NNT_KERNEL_SPACE

class Feature
    : public Object
{
public:

    Feature();
    ~Feature();

# ifdef NNT_MSVC

    ULONG irptype;
    PDRIVER_DISPATCH dispatch;
    PDEVICE_OBJECT device;
    PIRP irp;
    NTSTATUS status;

# endif

    void main();

    pmp_begin(Feature);
    pmp_function(void, main, ());
    pmp_end;

};

# ifdef NNT_MSVC

template <ULONG IRP, PDRIVER_DISPATCH DISPATCH>
class FeatureImpl
    : public Feature
{
public:

    FeatureImpl()
    {
        this->irptype = IRP;
        this->dispatch = DISPATCH;
    }

};

NNT_BEGIN_NS(feature)

# define _NNT_DRIVER_DISP(name) \
    disp_##name

# define _NNTDECL_DRIVER_DISP(name) \
    DRIVER_DISPATCH _NNT_DRIVER_DISP(name); \
    NTSTATUS _NNT_DRIVER_DISP(name) (PDEVICE_OBJECT dev, PIRP irp)

NNT_EXTERN _NNTDECL_DRIVER_DISP(create);
NNT_EXTERN _NNTDECL_DRIVER_DISP(read);
NNT_EXTERN _NNTDECL_DRIVER_DISP(write);

class Create
    : public FeatureImpl<IRP_MJ_CREATE, _NNT_DRIVER_DISP(create)>
{
public:

    Create();

};

class Read
    : public FeatureImpl<IRP_MJ_READ, _NNT_DRIVER_DISP(read)>
{
public:

    Read();

};

class Write
    : public FeatureImpl<IRP_MJ_WRITE, _NNT_DRIVER_DISP(write)>
{
public:

    Write();

};

NNT_END_NS

# endif

# endif // kernel.

NNT_END_NS
NNT_END_HEADER_CXX

# endif
