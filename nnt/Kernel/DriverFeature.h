
# ifndef __NNT_KERNEL_DRIVERFEATURE_55dba2a58c864cce9273145b03dc3365_H_INCLUDED
# define __NNT_KERNEL_DRIVERFEATURE_55dba2a58c864cce9273145b03dc3365_H_INCLUDED

# include "./DriverObject.h"
# include "../TL/Class+NNT.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(driver)

# ifdef NNT_KERNEL_SPACE

class App;

enum DriverFeatureType
{
    DFT_OPEN,
    DFT_CLOSE,
    DFT_READ,
    DFT_WRITE,
};

# ifdef NNT_UNIX

typedef int (*driver_dispatch_t)();

# define _NNTDECL_DISPATCH(name) \
    int name ()

# endif

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

# ifdef NNT_UNIX

    ulong dftype;
    driver_dispatch_t dispatch;

# endif

# ifdef NNT_BSD

    cdev* device;
    int flag;
    int devtype;
    thread* thd;
    uio* io;
    
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

NNT_BEGIN_NS(feature)

# define _NNT_DRIVER_DISP(name)                 \
    disp_##name

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

# define _NNTDECL_DRIVER_DISP(name)                                 \
    DRIVER_DISPATCH _NNT_DRIVER_DISP(name);                         \
    NTSTATUS _NNT_DRIVER_DISP(name) (PDEVICE_OBJECT dev, PIRP irp)

# endif

# ifdef NNT_UNIX

# define _NNTDECL_DRIVER_DISP(name) \
    _NNTDECL_DISPATCH( _NNT_DRIVER_DISP(name) )

template <uint Dft, driver_dispatch_t Dispatch>
    class FeatureImpl
    : public Feature
{
public:

    FeatureImpl()
    {
        this->dftype = Dft;
        this->dispatch = Dispatch;
    }
    
};

# endif

NNT_EXTERN _NNTDECL_DRIVER_DISP(open);
NNT_EXTERN _NNTDECL_DRIVER_DISP(close);
NNT_EXTERN _NNTDECL_DRIVER_DISP(read);
NNT_EXTERN _NNTDECL_DRIVER_DISP(write);

class Open
: public FeatureImpl<
NNT_MSVC_EXPRESS(IRP_MJ_CREATE) NNT_UNIX_EXPRESS(DFT_OPEN),
  _NNT_DRIVER_DISP(open)>
{
public:

    Open();

    void main();

    pmp_inherit(Open);
    pmp_end;
};

class Close
: public FeatureImpl<
NNT_MSVC_EXPRESS(IRP_MJ_CLOSE) NNT_UNIX_EXPRESS(DFT_CLOSE),
  _NNT_DRIVER_DISP(close)>
{
public:

    Close();

    void main();

    pmp_inherit(Close);
    pmp_end;
};

class Read
: public FeatureImpl<
NNT_MSVC_EXPRESS(IRP_MJ_READ) NNT_UNIX_EXPRESS(DFT_READ),
  _NNT_DRIVER_DISP(read)>
{
public:

    Read();
    ~Read();

    ulong length, offset;

    NNT_MSVC_EXPRESS(void* buffer);
    NNT_UNIX_EXPRESS(core::data stm);

    void prepare();
    core::data data() const;

    pmp_inherit(Read);
    pmp_end;    
};

class Write
: public FeatureImpl<
NNT_MSVC_EXPRESS(IRP_MJ_WRITE) NNT_UNIX_EXPRESS(DFT_WRITE),
  _NNT_DRIVER_DISP(write)>
{
public:

    Write();
    ~Write();

    ulong length, offset;

    NNT_MSVC_EXPRESS(void* buffer);
    NNT_UNIX_EXPRESS(core::data stm);

    void prepare();
    core::data data() const;

    pmp_inherit(Write);
    pmp_end;
};

NNT_END_NS

# endif // kernel.

NNT_END_NS
NNT_END_HEADER_CXX

# endif
