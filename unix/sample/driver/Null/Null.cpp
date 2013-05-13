
# include <nnt/Foundation+NNT.h>

# ifdef NNT_LINUX

# include "Ext.h"

# endif

# ifdef NNT_CXX

NNT_BEGIN_CXX

NNTDECL_PRIVATE_HEAD(CA);

NNTDECL_PRIVATE_BEGIN(CA)

void init()
{
}

void dealloc()
{
}

NNTDECL_PRIVATE_END

class CA
{
public:

    NNTDECL_PRIVATE(CA);
    
    CA() {
        NNTDECL_PRIVATE_CONSTRUCT(CA);
    }

    ~CA() {
        NNTDECL_PRIVATE_DESTROY();
    }

    void proc() {
        int a = 10;
        a += 12;
    }
    
};


NNT_END_CXX

# endif

NNT_BEGIN_C

# ifdef NNT_BSD

int null_entry(module_t mod, int event, void* arg)
{
# ifdef NNT_CXX
    
    ::nnt::CA a;
    a.proc();
    ::nnt::CA* ptr = new ::nnt::CA;
    ptr->proc();

# endif
    
    return 0;
}

DEV_MODULE(Null, null_entry, NULL);

# endif

# ifdef NNT_LINUX

static int __init null_init()
{
    ext_init();
    return 0;
}

static void __exit null_exit()
{
    ext_fin();
}

module_init(null_init);
module_exit(null_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("NNT"); //optional
MODULE_DESCRIPTION("NNT NULL DRIVER"); //optional

# endif

NNT_END_C
