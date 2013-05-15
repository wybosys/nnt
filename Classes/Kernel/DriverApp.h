
# ifndef __NNT_KERNEL_DRIVERAPP_5fb7c4756bb245dea76e8a3035d281a1_H_INCLUDED
# define __NNT_KERNEL_DRIVERAPP_5fb7c4756bb245dea76e8a3035d281a1_H_INCLUDED

# ifdef NNT_CXX

# include "./DriverObject.h"
# include "./DriverFeature.h"

# ifdef NNT_LINUX
#   include "../Mach/klinux.h"
# endif

# ifdef NNT_KERNEL_SPACE

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(driver)

NNTCLASS(App);

class EntryObject
{
public:

# ifdef NNT_MSVC

    EntryObject(PDRIVER_OBJECT _0 = NULL, PUNICODE_STRING _1 = NULL);

    PDRIVER_OBJECT pDriverObject;
    core::string strRegisterPath;
    PDEVICE_OBJECT pDeviceObject;

# endif

# ifdef NNT_BSD

    module_t mod;
    void* arg;
    cdevsw devsw;   
    
# endif

# ifdef NNT_UNIX

    EntryObject();

    struct cdev* dev;
    
# endif

# ifdef NNT_LINUX

    lnx::file_operations fops;
    int devno_major, devno_minor;
    
# endif
    
};

enum MemoryMode
{
    MEMORY_BUFFER,
    MEMORY_MAP,
};

NNTDECL_PRIVATE_HEAD(App);

class App
    : public ::nnt::Object
{
    NNTDECL_PRIVATE(App);

public:

    App();
    ~App();

    int main();
    int install();

    //! add driver feature.
    void add_feature(Feature*);  

    EntryObject eo;
    core::string name;
    MemoryMode memory_mode;

};

# ifdef NNT_MSVC

struct DriverExtension
{
    App* pApp;
    core::string strDevName, strSymName;
};

# endif

NNT_END_NS
NNT_END_HEADER_CXX

# ifdef NNT_BSD
#   define __NNTDECL_DRIVER_APP(name) \
    NNT_EXTERN int nnt_driver_entry(module_t, int, void*); \
    DEV_MODULE(name, nnt_driver_entry, NULL);
# else
#   define __NNTDECL_DRIVER_APP(name) SPACE
# endif

# define NNTDECL_DRIVER_APP(app, appname)               \
    NNT_BEGIN_C \
    __NNTDECL_DRIVER_APP(appname); \
    ::nnt::driver::App* gs_nntapp = NULL;            \
    int NNT_DRIVER_MAIN(::nnt::driver::EntryObject& eo) \
{ \
    gs_nntapp = new app();                \
    gs_nntapp->name = #appname;           \
    gs_nntapp->eo = eo;                   \
    int sta = ((app*)gs_nntapp)->install(); \
    if (::nnt::driver::Status::Failed(sta)) \
    {                                       \
        trace_msg("failed to install driver");  \
        return sta;                             \
    }                                           \
    sta = ((app*)gs_nntapp)->main();            \
    return sta; \
} \
    void NNT_DRIVER_FREEAPP() \
{ \
    delete gs_nntapp; \
    gs_nntapp = NULL; \
} \
    NNT_END_C

NNT_BEGIN_HEADER_C

NNT_EXTERN int NNT_DRIVER_MAIN(::nnt::driver::EntryObject&);
NNT_EXTERN void NNT_DRIVER_FREEAPP();
NNT_EXTERN ::nnt::driver::App* gs_nntapp;

NNT_END_HEADER_C

# endif

# endif // cxx

NNT_BEGIN_HEADER_C

# ifdef NNT_LINUX

NNT_EXTERN int nnt_ckernel_init(void);
NNT_EXTERN void nnt_ckernel_exit(void);

# endif

NNT_END_HEADER_C

# endif
