
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

struct DriverExtension
{
    App* pApp;
    core::string strDevName, strSymName;
};

# endif

App::App()
{

}

App::~App()
{

}

int App::install()
{
# ifdef NNT_MSVC

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
}

# ifdef NNT_MSVC

DRIVER_UNLOAD UnloadDriver;

VOID UnloadDriver(IN PDRIVER_OBJECT pDriverObject)
{
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
}

# endif

NNT_END_NS
NNT_END_CXX

NNT_BEGIN_C

# ifdef NNT_MSVC

NTSTATUS DriverEntry(IN PDRIVER_OBJECT pDriverObject, IN PUNICODE_STRING pRegisterPath)
{
    NNTDEBUG_BREAK;

    ::nnt::driver::EntryObject eo(pDriverObject, pRegisterPath);

    // call driver's main.
    return NNT_DRIVER_MAIN(eo);
}

# endif

NNT_END_C

# endif
