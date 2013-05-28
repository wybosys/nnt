
# ifndef __NNT_CUDA_FUNCTION_BBA12F8996AE46BD844403D3D10A2D9D_H_INCLUDED
# define __NNT_CUDA_FUNCTION_BBA12F8996AE46BD844403D3D10A2D9D_H_INCLUDED

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(cuda)

class Dimension
{
public:
    
    Dimension();
    ~Dimension();
    
# ifdef NNT_CUDA
    
    operator cu_ndrange const& () const
    {
        return ndr;
    }
    
    operator cu_ndrange& ()
    {
        return ndr;
    }
    
    cu_ndrange* operator -> ()
    {
        return &ndr;
    }
    
    cu_ndrange const* operator -> () const
    {
        return &ndr;
    }
    
    cu_ndrange ndr;
    
# endif
    
};

class Parameter
{
public:
    
    Parameter(void*, void*, usize, bool);
    ~Parameter();
    
    static Parameter Input(void*, NNTValueType, usize count);
    static Parameter InputOutput(void*, NNTValueType, usize count);
    static Parameter Output(void*, NNTValueType, usize count);
    
    void back();
    
    operator void* () const
    {
        return (void*)_buffer;
    }
    
    template <typename T>
    operator T* () const
    {
        return (T*)(void*)*this;
    }
    
protected:
    
    usize _sz;
    void *_origin, *_buffer;
    bool _needback;
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif
