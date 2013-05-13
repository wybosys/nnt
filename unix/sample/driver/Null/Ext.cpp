
extern "C" {

# include <linux/init.h>
# include <linux/kernel.h>

}

# include "Ext.h"

class Ext
{
public:

    void init();
    void fin();
    
};

void Ext::init()
{
    printk(KERN_ALERT "nnt::ext::init");
}

void Ext::fin()
{
    printk(KERN_ALERT "nnt::ext::fin");
}

//static Ext* gs_ext = NULL;

extern "C" {

    void ext_init()
    {
        printk(KERN_ALERT "nnt::ext::init");
    }

    void ext_fin()
    {
        printk(KERN_ALERT "nnt::ext::fin");
    }
    
}
