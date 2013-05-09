
# include <linux/init.h>
# include <linux/kernel.h>
# include <linux/module.h>

static int __init null_init()
{
    printk(KERN_ALERT "nnt: init");
    return 0;
}

static void __exit null_exit()
{
    printk(KERN_ALERT "nnt: fin");
}

module_init(null_init);
module_exit(null_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("NNT"); //optional
MODULE_DESCRIPTION("NNT NULL DRIVER"); //optional
