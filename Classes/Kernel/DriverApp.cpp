
//# include "Core.h"
# include <ntddk.h>
# include "DriverApp.h"

# ifdef NNT_MSVC
#   pragma warning (disable:28101)
# endif

# ifdef NNT_KERNEL_SPACE

NNT_BEGIN_CXX

# ifdef NNT_MSVC

NTSTATUS CreateDevice(IN PDRIVER_OBJECT pDriverObject)
{
    NTSTATUS ret = STATUS_FILE_CLOSED;
    return ret;
}

DRIVER_UNLOAD DriverUnload;

__drv_dispatchType(IRP_MJ_CREATE) DRIVER_DISPATCH DispatchCreate;
__drv_dispatchType(IRP_MJ_READ) DRIVER_DISPATCH DispatchRead;
__drv_dispatchType(IRP_MJ_WRITE) DRIVER_DISPATCH DispatchWrite;
__drv_dispatchType(IRP_MJ_CLOSE) DRIVER_DISPATCH DispatchClose;

VOID DriverUnload(IN PDRIVER_OBJECT pDriverObject)
{

}

NTSTATUS DispatchCreate(IN PDEVICE_OBJECT pDevObj, IN PIRP pIrp)
{
    NTSTATUS ret = STATUS_FILE_CLOSED;
    return ret;
}

NTSTATUS DispatchRead(IN PDEVICE_OBJECT pDevObj, IN PIRP pIrp)
{
    NTSTATUS ret = STATUS_FILE_CLOSED;
    return ret;
}

NTSTATUS DispatchWrite(IN PDEVICE_OBJECT pDevObj, IN PIRP pIrp)
{
    NTSTATUS ret = STATUS_FILE_CLOSED;
    return ret;
}

NTSTATUS DispatchClose(IN PDEVICE_OBJECT pDevObj, IN PIRP pIrp)
{
    NTSTATUS ret = STATUS_FILE_CLOSED;
    return ret;
}

# endif

NNT_END_CXX

NNT_BEGIN_C

# ifdef NNT_MSVC

NTSTATUS DriverEntry(IN PDRIVER_OBJECT pDriverObject, IN PUNICODE_STRING pRegisterPath)
{
    // call app main entry.
    //NNTKS_MAIN();

    // driver impl.
    NTSTATUS ret;

    // register.
    pDriverObject->DriverUnload = ::nnt::DriverUnload;
    pDriverObject->MajorFunction[IRP_MJ_CREATE] = ::nnt::DispatchCreate;
    pDriverObject->MajorFunction[IRP_MJ_CLOSE] = ::nnt::DispatchClose;
    pDriverObject->MajorFunction[IRP_MJ_WRITE] = ::nnt::DispatchWrite;
    pDriverObject->MajorFunction[IRP_MJ_READ] = ::nnt::DispatchRead;

    // create.
    ret = ::nnt::CreateDevice(pDriverObject);

    return ret;
}

# endif

NNT_END_C

# endif
