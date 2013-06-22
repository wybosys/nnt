
# ifndef __NNT_KERNEL_KLINUX_PRIVATE_8521FBD3418F4243A4312B138483BD8E_H_INCLUDED
# define __NNT_KERNEL_KLINUX_PRIVATE_8521FBD3418F4243A4312B138483BD8E_H_INCLUDED

# ifdef NNT_KERNEL_SPACE

# ifdef NNT_LINUX

NNT_BEGIN_HEADER_C

struct dev_class;

// impl in nnt.
NNT_EXTERN void* nnt_malloc(size_t);
NNT_EXTERN void nnt_free(void*);
NNT_EXTERN struct cdev* nnt_cdev_new(void);
NNT_EXTERN ulong nnt_copy_to_user(void*, void*, ulong);
NNT_EXTERN ulong nnt_copy_from_user(void*, void*, ulong);

// direct link in kernel.
NNT_EXTERN int cdev_add(struct cdev * p, dev_t dev, unsigned count);
NNT_EXTERN int alloc_chrdev_region(dev_t *, unsigned, unsigned, const char *);
NNT_EXTERN int register_chrdev_region(dev_t, unsigned, const char *);
NNT_EXTERN void unregister_chrdev_region(dev_t from, unsigned count);

// impl in linuxmod.c
NNT_EXTERN struct module* nnt_module_current(void);
NNT_EXTERN struct dev_class* nnt_create_device_class(struct module*, char const* name);
NNT_EXTERN struct device* nnt_create_device(struct dev_class*, struct device* parent, dev_t devt, void* drvdata, char const* name);
NNT_EXTERN void nnt_destroy_device(struct dev_class*, dev_t devt);
NNT_EXTERN void nnt_destroy_device_class(struct dev_class*);

struct nnt_file_operations {
    struct module *owner;
    ssize_t (*read) (struct file *, char __user *, size_t, loff_t *);
	ssize_t (*write) (struct file *, const char __user *, size_t, loff_t *);
	int (*open) (struct inode *, struct file *);
	int (*release) (struct inode *, struct file *);    
};

// utils.
NNT_EXTERN void nnt_file_operations_tokernel(IN struct nnt_file_operations*, INOUT struct file_operations**);
NNT_EXTERN void nnt_cdev_init(struct cdev*, struct file_operations*);

NNT_END_HEADER_C

# ifdef NNT_CXX

struct file_operations;

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(lnx)
   
class file_operations
    : public ntl::uml::composition<file_operations, nnt_file_operations>
{
public:

    file_operations();
    ~file_operations();

    operator ::file_operations* ();

protected:

    ::file_operations* _da;
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif // cxx

# endif // linux

# endif // kernel

# endif
