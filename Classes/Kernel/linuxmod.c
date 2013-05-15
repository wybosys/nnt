
# include <nnt/Core/Core.h>
# include <nnt/Kernel/DriverApp.h>
# include <nnt/Mach/klinux.h>

NNT_BEGIN_C

static int __init nnt_redirect_init(void)
{
    return nnt_ckernel_init();
}

static void __exit nnt_redirect_exit(void)
{
    nnt_ckernel_exit();
}

module_init(nnt_redirect_init);
module_exit(nnt_redirect_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("NNT"); //optional
MODULE_DESCRIPTION("NNT KERNEL DRIVER"); //optional

struct module* nnt_module_current(void)
{
    return THIS_MODULE;
}

struct dev_class* nnt_create_device_class(struct module* mod, char const* name)
{
    return (struct dev_class*)class_create(mod, name);
}

struct device* nnt_create_device(struct dev_class* cls, struct device* parent, dev_t devt, void* drvdata, char const* name)
{
    return device_create((struct class*)cls, parent, devt, drvdata, name);
}

void nnt_destroy_device(struct dev_class* cls, dev_t devt)
{
    device_destroy((struct class*)cls, devt);
}

void nnt_destroy_device_class(struct dev_class* cls)
{
    class_destroy((struct class*)cls);
}

ulong nnt_copy_to_user(void* des, void* src, ulong sz)
{
    return copy_to_user(des, src, sz);
}

ulong nnt_copy_from_user(void* des, void* src, ulong sz)
{
    return copy_from_user(des, src, sz);
}

NNT_END_C
