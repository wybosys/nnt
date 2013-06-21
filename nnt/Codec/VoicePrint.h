
# ifndef __NNT_VOICEPRINT_054E3B6DF8FD4E7A9AFA4B8AE7861F37_H_INCLUDED
# define __NNT_VOICEPRINT_054E3B6DF8FD4E7A9AFA4B8AE7861F37_H_INCLUDED

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(vp)

NNTDECL_PRIVATE_HEAD_CXX(Digest);

class mfcc
{
public:
    
    mfcc();
    mfcc(mfcc const&);
    ~mfcc();
    
    mfcc& operator = (mfcc const& r);
    
    operator double** () const
    {
        return (double**)_data;
    }
    
    void to(core::data&) const;
    void from(core::data const&);
    
protected:
    
    double** _data;
    
};

class Result
{
public:
    
    Result();
    Result(Result const&);
    ~Result();
    
    Result& operator = (Result const&);
    real compare(Result const&);
    
    typedef core::vector<mfcc> mfccs_type;    
    
    mfccs_type mfccs;
    void* gmms;
    
};

class Digest
{
    NNTDECL_PRIVATE_CXX(Digest);
    
public:
    
    Digest();
    ~Digest();
    
    Result calc(core::data const&);
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
