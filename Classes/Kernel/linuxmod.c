
# include <nnt/Core/Core.h>

NNT_BEGIN_C

# include <linux/module.h>

static int __init null_init(void)
{
    return 0;
}

static void __exit null_exit(void)
{
    
}

module_init(null_init);
module_exit(null_exit);

MODULE_LICENSE("BSD");
MODULE_AUTHOR("NNT"); //optional
MODULE_DESCRIPTION("NNT KERNEL DRIVER"); //optional

NNT_END_C
