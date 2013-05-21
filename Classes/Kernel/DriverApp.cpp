
# include "Core.h"
# include "DriverApp.h"
# include "../Core/Task+NNT.h"

# ifdef NNT_KERNEL_SPACE

# ifdef NNT_MSVC
#   pragma warning (disable:28101)
# endif

NNT_BEGIN_CXX
NNT_BEGIN_NS(driver)

# ifdef NNT_MSVC
    
EntryObject::EntryObject(PDRIVER_OBJECT _0, PUNICODE_STRING _1)
: pDriverObject(_0), pDeviceObject(NULL)
{
    if (_1 != NULL)
        strRegisterPath = core::string(*_1);
}

# endif

# ifdef NNT_BSD

static Feature* feature_open = NULL;
static Feature* feature_close = NULL;
static Feature* feature_read = NULL;
static Feature* feature_write = NULL;

static int nnt_disp_open(cdev* dev, int oflags, int devtype, thread* thd)
{
    if (feature_open == NULL)
        return 0;
    feature_open->device = dev;
    feature_open->flag = oflags;
    feature_open->devtype = devtype;
    feature_open->thd = thd;
    feature_open->app = gs_nntapp;
    return feature::_NNT_DRIVER_DISP(open)();
}

static int nnt_disp_close(cdev* dev, int fflags, int devtype, thread* thd)
{
    if (feature_close == NULL)
        return 0;
    feature_close->device = dev;
    feature_close->flag = fflags;
    feature_close->devtype = devtype;
    feature_close->thd = thd;
    feature_close->app = gs_nntapp;
    return feature::_NNT_DRIVER_DISP(close)();
}

static int nnt_disp_read(cdev* dev, uio* io, int ioflag)
{
    if (feature_read == NULL)
        return 0;
    feature_read->device = dev;
    feature_read->flag = ioflag;
    feature_read->io = io;
    return feature::_NNT_DRIVER_DISP(read)();
}

static int nnt_disp_write(cdev* dev, uio* io, int ioflag)
{
    if (feature_write == NULL)
        return 0;
    feature_write->device = dev;
    feature_write->flag = ioflag;
    feature_write->io = io;
    return feature::_NNT_DRIVER_DISP(write)();
}

EntryObject::EntryObject()
    : arg(NULL), dev(NULL), mod(0)
{
    memset(&devsw, 0, sizeof(devsw));
    
    devsw.d_version = D_VERSION;
    devsw.d_open = nnt_disp_open;
    devsw.d_close = nnt_disp_close;
    devsw.d_read = nnt_disp_read;
    devsw.d_write = nnt_disp_write;
}

# endif

# ifdef NNT_LINUX

static Feature* feature_open = NULL;
static Feature* feature_close = NULL;
static Feature* feature_read = NULL;
static Feature* feature_write = NULL;

int nnt_disp_open(struct inode* inode, struct file* f)
{
    if (feature_open == NULL)
        return 0;
    feature_open->inode = inode;
    feature_open->file = f;
    feature_open->app = gs_nntapp;
    return feature::_NNT_DRIVER_DISP(open)();
}

int nnt_disp_close(struct inode* inode, struct file* f)
{
    if (feature_close == NULL)
        return 0;
    feature_close->inode = inode;
    feature_close->file = f;
    feature_close->app = gs_nntapp;
    return feature::_NNT_DRIVER_DISP(close)();
}

ssize_t nnt_disp_read(struct file* f, char __user* buf, size_t count, loff_t* pos)
{
    if (feature_read == NULL)
        return 0;
    feature_read->file = f;
    feature_read->buf = buf;
    feature_read->count = count;
    feature_read->pos = pos;
    feature_read->app = gs_nntapp;
    if (Status::Failed(feature::_NNT_DRIVER_DISP(read)()))
        return -EINVAL;
    return feature_read->proccessed;
}

ssize_t nnt_disp_write(struct file* f, const char __user* buf, size_t count, loff_t* pos)
{
    if (feature_write == NULL)
        return 0;
    feature_write->file = f;
    feature_write->buf = buf;
    feature_write->count = count;
    feature_write->pos = pos;
    feature_write->app = gs_nntapp;
    if (Status::Failed(feature::_NNT_DRIVER_DISP(write)()))
        return -EINVAL;
    return feature_write->proccessed;
}

EntryObject::EntryObject()
    : devno_major(0), devno_minor(0), dev(NULL)
{
    fops->read = nnt_disp_read;
    fops->write = nnt_disp_write;
    fops->open = nnt_disp_open;
    fops->release = nnt_disp_close;
}

# endif

NNTDECL_PRIVATE_BEGIN(App)

void init()
{

}

void dealloc()
{
    clear_features();
    clear_calls();
}

void clear_features()
{
    while (!features.empty())
    {
        Feature* ftu = features.pop();
        pmp_destroy(ftu);
    }
}

void clear_calls()
{
    while (!calls.empty())
    {
        Feature* call = calls.pop();
        pmp_destroy(call);
    }
}

typedef core::list<Feature*> features_type;
features_type features;
features_type calls;

NNTDECL_PRIVATE_END

App::App()
{
    NNTDECL_PRIVATE_CONSTRUCT(App);

    memory_mode = MEMORY_BUFFER;
}

App::~App()
{    
    NNTDECL_PRIVATE_DESTROY();
}

int App::main()
{
    trace_msg("fatal: wrong call to App::main()");
    return 0;
}

int App::install()
{
    NNTDEBUG_BREAK;
   
# ifdef NNT_MSVC

    // create device.
    core::string str_devname = "\\Device\\" + name;
    NTSTATUS sta = ::IoCreateDevice(eo.pDriverObject,
        sizeof(DriverExtension),
        str_devname,
        FILE_DEVICE_UNKNOWN,
        0,
        TRUE,
        &eo.pDeviceObject);

    if (!NT_SUCCESS(sta))
        return sta;

    use<DriverExtension> ext = eo.pDeviceObject->DeviceExtension;
    ext->pApp = this;
    ext->strDevName = str_devname;
    ext->strSymName = "\\??\\" + name;

    // set device's memory mode.
    switch (memory_mode)
    {
    case MEMORY_BUFFER: eo.pDeviceObject->Flags |= DO_BUFFERED_IO; break;
    case MEMORY_MAP: eo.pDeviceObject->Flags |= DO_DIRECT_IO; break;
    }

    // create symbol link.
    sta = ::IoCreateSymbolicLink(ext->strSymName, ext->strDevName);
    if (!NT_SUCCESS(sta))
    {
        ::IoDeleteDevice(eo.pDeviceObject);
        eo.pDeviceObject = NULL;
        return sta;
    }

    return STATUS_SUCCESS;

# endif

# ifdef NNT_BSD
   
    trace_msg("making device");
    eo.dev = make_dev(&eo.devsw,
                      0,
                      UID_ROOT,
                      GID_WHEEL,
                      0600,
                      name.c_str(),
                      NULL);

    if (eo.dev)
        trace_msg("made device");

    return TRIEXP(eo.dev != NULL, 0, -1);
    
# endif

# ifdef NNT_LINUX

    trace_msg("making device");

    // alloc device.
    dev_t dev;
    int res = 0;
    if (eo.devno_major)
    {
        dev = MKDEV(eo.devno_major, eo.devno_minor);
        res = register_chrdev_region(dev, 1, name.c_str());
    }
    else
    {
        res = alloc_chrdev_region(&dev, 0, 1, name.c_str());
    }
    
    eo.devno_major = MAJOR(dev);
    eo.devno_minor = MINOR(dev);        

    if (res < 0)
    {
        trace_msg("failed to made device");
        return res;
    }
    else
    {
        trace_msg("made device");
    }

    // setup device.
    eo.dev = nnt_cdev_new();
    nnt_cdev_init(eo.dev, eo.fops);

    // add dev.
    res = cdev_add(eo.dev, dev, 1);

    if (res < 0)
    {
        trace_msg("failed to add device");
        return res;
    }
    else
    {
        trace_msg("device added");
    }

    // create dev port.
    eo.devclass_name = name + "_Class";
    eo.devclass = nnt_create_device_class(eo.fops->owner,
                                          eo.devclass_name.c_str());
    if (eo.devclass == NULL)
    {
        trace_msg("failed to create device class");
        return -1;
    }

    eo.device = nnt_create_device(eo.devclass,
                                  NULL,
                                  dev,
                                  NULL,
                                  name.c_str());
    if (eo.device == NULL)
    {
        trace_msg("failed to create device");
        return -1;
    }

    return res;
    
# endif
    
}

void App::add_feature(Feature* fte)
{

# ifdef NNT_MSVC
    
    switch (fte->irptype)
    {
    default:
        {
            eo.pDriverObject->MajorFunction[fte->irptype] = fte->dispatch;            
            d_ptr->features.push_back(fte);
        } break;
    case DFT_OPEN:
        {
            d_ptr->calls.push_back(fte);
        } break;
    }

# endif

# ifdef NNT_BSD

    switch (fte->dftype)
    {
    case DFT_OPEN:
    {
        feature_open = fte;
    } break;
    case DFT_CLOSE:
    {
        feature_close = fte;
    } break;
    case DFT_READ:
    {
        feature_read = fte;
    } break;
    case DFT_WRITE:
    {
        feature_write = fte;
    } break;
    };

    d_ptr->features.push_back(fte);
    
# endif

# ifdef NNT_LINUX

    switch (fte->dftype)
    {
    case DFT_OPEN:
    {
        feature_open = fte;
    } break;
    case DFT_CLOSE:
    {
        feature_close = fte;
    } break;
    case DFT_READ:
    {
        feature_read = fte;
    } break;
    case DFT_WRITE:
    {
        feature_write = fte;
    } break;
    };

    d_ptr->features.push_back(fte);
    
# endif
        
}

Feature* App::find_call(uinteger code) const
{
    return NULL;
}

# ifdef NNT_MSVC

DRIVER_UNLOAD UnloadDriver;
VOID UnloadDriver(IN PDRIVER_OBJECT pDriverObject)
{
    NNTDEBUG_BREAK;

    PDEVICE_OBJECT pdev = pDriverObject->DeviceObject;
    while (pdev != NULL)
    {
        use<DriverExtension> ext = pdev->DeviceExtension;

        // remove symblic link.
        ::IoDeleteSymbolicLink(ext->strSymName);

        // delete device.
        PDEVICE_OBJECT pdevnx = pdev->NextDevice;       
        ::IoDeleteDevice(pdev);
        pdev = pdevnx;
    }

    NNT_DRIVER_FREEAPP();
}

DRIVER_STARTIO CallDriver;
VOID CallDriver(IN PDEVICE_OBJECT pdev, PIRP pIrp)
{
    use<DriverExtension> ext = pdev->DeviceExtension;
    PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(pIrp);
    ULONG const code = stack->Parameters.DeviceIoControl.IoControlCode;
    use<feature::Call> fcall = ext->pApp->find_call(code);
    if (fcall == NULL)
        return;
    fcall->irp = pIrp;
    pmp_call(fcall, main, ());
}

# endif

# ifdef NNT_BSD

static void unload_driver()
{
    if (gs_nntapp)
    {
        cdev* devobj = gs_nntapp->eo.dev;
        if (devobj)
        {
            destroy_dev(devobj);
        }
    }

    NNT_DRIVER_FREEAPP();

    trace_msg("unloaded driver");
}

# endif

# ifdef NNT_LINUX

static void unload_driver()
{
    if (gs_nntapp)
    {
        dev_t devno = MKDEV(gs_nntapp->eo.devno_major, gs_nntapp->eo.devno_minor);
        nnt_destroy_device(gs_nntapp->eo.devclass, devno);
        nnt_destroy_device_class(gs_nntapp->eo.devclass);
        unregister_chrdev_region(devno, 1);
    }
    
    NNT_DRIVER_FREEAPP();

    trace_msg("unloaded driver");
}

# endif

NNT_END_NS
NNT_END_CXX

NNT_BEGIN_C

# ifdef NNT_MSVC

NTSTATUS DriverEntry(IN PDRIVER_OBJECT pDriverObject, IN PUNICODE_STRING pRegisterPath)
{
    NNTDEBUG_BREAK;

    trace_msg("driver entry");

    ::nnt::driver::EntryObject eo(pDriverObject, pRegisterPath);

    // default dispatch.
    pDriverObject->DriverUnload = ::nnt::driver::UnloadDriver;
    pDriverObject->DriverStartIo = ::nnt::driver::CallDriver;

    // call driver's main.
    return NNT_DRIVER_MAIN(eo);
}

# endif

# ifdef NNT_BSD

int nnt_driver_entry(module_t mod, int event, void* arg)
{
    NNTDEBUG_BREAK;

    trace_msg("driver entry");

    int error = 0;

    ::nnt::driver::EntryObject eo;
    eo.mod = mod;
    eo.arg = arg;

    switch (event)
        {
        case MOD_LOAD:
            {
                error = NNT_DRIVER_MAIN(eo);
            } break;
        case MOD_UNLOAD:
            {
                ::nnt::driver::unload_driver();
            } break;
        default:
            error = EOPNOTSUPP;
            break;
        }
    
    return error;
}

# endif

# ifdef NNT_LINUX

int nnt_ckernel_init()
{
    NNTDEBUG_BREAK;
    
    trace_msg("driver init");
    
    ::nnt::driver::EntryObject eo;
    int ret = NNT_DRIVER_MAIN(eo);
    
    return ret;
}

void nnt_ckernel_exit()
{
    ::nnt::driver::unload_driver();
}

# endif

NNT_END_C

# endif
