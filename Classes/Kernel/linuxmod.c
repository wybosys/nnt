
# include <nnt/Core/Core.h>
# include <nnt/Kernel/DriverApp.h>

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

MODULE_LICENSE("BSD");
MODULE_AUTHOR("NNT"); //optional
MODULE_DESCRIPTION("NNT KERNEL DRIVER"); //optional

struct module* nnt_module_current()
{
    return THIS_MODULE;
}

NNT_END_C
