
# ifndef __NNT_KERNEL_DRIVERFEATURE_55dba2a58c864cce9273145b03dc3365_H_INCLUDED
# define __NNT_KERNEL_DRIVERFEATURE_55dba2a58c864cce9273145b03dc3365_H_INCLUDED

# include "./DriverObject.h"
# include "../TL/Class+NNT.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(driver)

# ifdef NNT_KERNEL_SPACE

class App;

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

# endif

    App* app;

    void prepare();
    void collect();
    void main();
    void complete();
    void success(usize);

    Status status;
    usize proccessed;

    pmp_begin(Feature);
    pmp_function(void, prepare, ());
    pmp_function(void, collect, ());
    pmp_function(void, main, ());
    pmp_function(void, complete, ());
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
NNT_EXTERN _NNTDECL_DRIVER_DISP(close);
NNT_EXTERN _NNTDECL_DRIVER_DISP(read);
NNT_EXTERN _NNTDECL_DRIVER_DISP(write);

class Create
    : public FeatureImpl<IRP_MJ_CREATE, _NNT_DRIVER_DISP(create)>
{
public:

    Create();

    void main();

    pmp_begin(Create);
    pmp_end;
};

class Close
    : public FeatureImpl<IRP_MJ_CLOSE, _NNT_DRIVER_DISP(close)>
{
public:

    Close();

    void main();

    pmp_begin(Close);
    pmp_end;
};

class Read
    : public FeatureImpl<IRP_MJ_READ, _NNT_DRIVER_DISP(read)>
{
public:

    Read();

    ulong length, offset;
    void* buffer;

    void prepare();
    core::data data() const;

    pmp_begin(Read);
    pmp_end;
};

class Write
    : public FeatureImpl<IRP_MJ_WRITE, _NNT_DRIVER_DISP(write)>
{
public:

    Write();

    ulong length, offset;
    void* buffer;

    void prepare();
    core::data data() const;

    pmp_begin(Write);
    pmp_end;
};

NNT_END_NS

# endif

# endif // kernel.

NNT_END_NS
NNT_END_HEADER_CXX

# endif
