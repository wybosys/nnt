
# include "Core.h"

# ifdef NNT_LINUX

# include "klinux.h"

NNT_BEGIN_C

void* nnt_malloc(size_t sz)
{
    return kmalloc(sz, GFP_KERNEL);
}

void nnt_free(void* ptr)
{
    kfree(ptr);
}

struct cdev* nnt_cdev_new()
{
    return (struct cdev*)kmalloc(sizeof(struct cdev), GFP_KERNEL);
}

void nnt_file_operations_tokernel(struct nnt_file_operations* _i, struct file_operations** _o)
{
    if (*_o == NULL)
        *_o = nnt_malloc(sizeof(struct file_operations));
    
    struct file_operations* fo = *_o;
    fo->owner = _i->owner;
    fo->read = _i->read;
    fo->write = _i->write;
    fo->open = _i->open;
    fo->release = _i->release;
}

void nnt_cdev_init(struct cdev* dev, struct file_operations* fop)
{
    cdev_init(dev, fop);
    dev->owner = fop->owner;
    dev->ops = fop;
}

NNT_END_C

# endif
