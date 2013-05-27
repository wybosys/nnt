
# ifndef __NNT_OCL_FUNCTION_DBCB58408A204ADA9F8BC0C3EFA6673E_H_INCLUDED
# define __NNT_OCL_FUNCTION_DBCB58408A204ADA9F8BC0C3EFA6673E_H_INCLUDED

# include "OCLDevice.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(opencl)

NNTCLASS(Parameter);

class Parameter
{
public:
    
    Parameter(void* origin, void* buf, usize sz, bool back = false);
    ~Parameter();
    
    static Parameter Input(void*, NNTOpenCLValueType, uinteger);
    static Parameter InputOutput(void*, NNTOpenCLValueType, uinteger);
    static Parameter Output(void*, NNTOpenCLValueType, uinteger);
    
    void back();
    
    operator void* () const;
    
    template <typename T>
    operator T* () const
    {
        return (T*)(void*)*this;
    }
    
protected:
    
    usize _size;
    void *_buffer, *_origin;
    bool _needback;
    
};

inline Parameter::operator void *() const
{
    return (void*)_buffer;
}

NNTCLASS(Function);
NNTCLASS(Dimension);

class Dimension
{
public:
    
    Dimension();
    ~Dimension();
    
    uinteger dim;
    uinteger offset[3];
    uinteger count[3];

    typedef struct {} *range_t;
    operator range_t () const;
    
    template <typename T>
    operator T* () const
    {
        return (T*)(range_t)*this;
    }
    
    void update(Function const&);
    
protected:
    
    void* _ndr;
    
};

class Function
{
public:
    
    typedef struct {} *block_t;
    
    Function(block_t);
    ~Function();
    
    //! workgroup size.
    usize wgs() const;
    
    //! param call.
    void invoke(Dimension const&, Parameter&, Parameter&);
    
protected:
    
    Device const& _device;
    block_t _block;
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif
