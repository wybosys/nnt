
# ifndef __NNT_KERNEL_DRIVEROBJECT_bed49de42d8e481ea9bca62581254b12_H_INCLUDED
# define __NNT_KERNEL_DRIVEROBJECT_bed49de42d8e481ea9bca62581254b12_H_INCLUDED
 
NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(driver)

class Status
{
public:

    Status();
    ~Status();

    //! check value.
    static bool Success(int);
    static bool Failed(int);

    //! get value.
    operator ulong () const;

    //! set error code.
    void success();

protected:

    ulong _val;

};

inline_impl Status::operator ulong () const
{
    return _val;
}

class Memory
{
public:

    Memory(void* ptr, usize len);
    ~Memory();

    bool is_readable(ubyte align = 4) const;
    bool is_writable(ubyte align = 4) const;

protected:

    void* _ptr;
    usize _len;

};

class Object
    : public ::nnt::Object
{
public:

    Object();
    ~Object();

};

NNT_END_NS
NNT_END_HEADER_CXX

# endif
