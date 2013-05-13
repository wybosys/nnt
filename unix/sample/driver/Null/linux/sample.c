
# ifdef __cplusplus

#   define new _cxx_ignore_new_for_c
#   define private _cxx_ignore_private_for_c
#   define namespace _cxx_ignore_namespace_for_c

extern "C" {

# endif

# include <linux/init.h>
# include <linux/kernel.h>
# include <linux/module.h>
# include "Ext.h"

static int __init null_init(void)
{
    ext_init();
    return 0;
}

static void __exit null_exit(void)
{
    ext_fin();
}

module_init(null_init);
module_exit(null_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("NNT"); //optional
MODULE_DESCRIPTION("NNT NULL DRIVER"); //optional

# ifdef __cplusplus
}
# endif
