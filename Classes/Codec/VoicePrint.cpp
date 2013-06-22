
# include "Core.h"
# include "VoicePrint.h"
# include "../Math/Statistic.h"

NNT_BEGIN_HEADER_C

# include "../../contrib/openvp/voice_id/voiceIdentify.h"

NNT_END_HEADER_C

NNT_BEGIN_CXX
NNT_BEGIN_NS(vp)

mfcc::mfcc(usize sz)
: _count(sz), _data(0)
{
    _data = (double**)malloc(_count * sizeof(double*));
    for (uint i = 0; i < _count; ++i)
    {
        _data[i] = (double*)calloc(D, sizeof(double));
    }
}

mfcc::mfcc(mfcc const& r)
{
    _count = r._count;
    _data = (double**)malloc(_count * sizeof(double*));
    for (uint i = 0; i < _count; ++i)
    {
        _data[i] = (double*)malloc(D * sizeof(double));
        memcpy(_data[i], r._data[i], D * sizeof(double));
    }
}

mfcc& mfcc::operator = (mfcc const& r)
{
    clear();
    
    _count = r._count;
    _data = (double**)malloc(_count * sizeof(double*));
    for (uint i = 0; i < _count; ++i)
    {
        _data[i] = (double*)malloc(D * sizeof(double));
        memcpy(_data[i], r._data[i], D * sizeof(double));
    }
    return *this;
}

mfcc::~mfcc()
{
    clear();
}

void mfcc::clear()
{
    for (uint i = 0; i < _count; ++i)
        free(_data[i]);
    free(_data);
    _count = 0;
    _data = NULL;
}

void mfcc::to(core::data &da) const
{
    da.clear();
    for (uint i = 0; i < _count; ++i)
    {
        da.append(_data[i], D * sizeof(double));
    }
}

void mfcc::from(core::data const& da)
{
    clear();
    
    _count = da.length() / sizeof(double) / D;
    _data = (double**)malloc(_count * sizeof(double*));
    for (uint i = 0; i < _count; ++i)
    {
        _data[i] = (double*)malloc(D * sizeof(double));
    }
    
    core::framedata fd(da.bytes(), da.length());
    for (uint i = 0; i < _count; ++i)
    {
        memcpy(_data[i], fd.bytes(), D * sizeof(double));
        fd.move(D * sizeof(double));
    }
}

Result::Result()
{    

}

Result::Result(Result const& r)
{
    codes = r.codes;
}

Result::~Result()
{
    
}

Result& Result::operator = (Result const& r)
{
    codes = r.codes;
    return *this;
}

bool Result::empty() const
{
    return codes.size() == 0;
}

real Result::compare(Result const& r)
{
    if (!codes.size() || !r.codes.size())
        return 1;
    
    typedef core::vector<double> comprs_type;
    comprs_type comprs;
    
    for (codes_type::const_iterator each = codes.begin();
         each != codes.end();
         ++each)
    {
        comprs.push_back(*each);
    }
    
    for (codes_type::const_iterator each = r.codes.begin();
         each != r.codes.end();
         ++each)
    {

        comprs.push_back(*each);
    }
    
    double dev = stat::deviation_standard<double, comprs_type::const_iterator>::o(comprs.begin(), comprs.end());
    double avg = stat::sum<double, comprs_type::const_iterator>::o(comprs.begin(), comprs.end()) / comprs.size();
    return dev / avg;
}

NNTDECL_PRIVATE_BEGIN_CXX(Digest)

void init()
{
    
}

void dealloc()
{
    
}

# define TRAINFRAME 300

Result calc(byte* d, usize dlen)
{
    Result ret;    
    core::framedata fd(d, dlen);
    
    usize const framelen = d_owner->slice / FRAME_LEN;
    if (framelen < TRAINFRAME)
        return ret;
    
    while (fd.length() > d_owner->slice)    {
        
        mfcc t_mfcc(framelen);
        GMM gmm;
        
        if (voiceToMFCC((BYTE*)fd.bytes(), d_owner->slice, t_mfcc, TRAINFRAME))
        {
            if (GMMs(t_mfcc, &gmm, TRAINFRAME, M))
            {
                double val = 0;
                if (GMM_identify(t_mfcc, &val, &gmm, framelen, M))
                {
                    val = fabs(val);
                    ret.codes.push_back(val);
                    
                    trace_fmt("succeed calc slice's code, %f", val);                    
                }
                else
                {
                    trace_msg("failed to calc slice's code");
                }
            }
# ifdef NNT_DEBUG
            else
            {
                trace_msg("skip slice for vp");
            }
# endif
        }
        
        fd.move(d_owner->slice);
    }
    
    return ret;
}

NNTDECL_PRIVATE_END_CXX

Digest::Digest()
{
    NNTDECL_PRIVATE_CONSTRUCT(Digest);
    
    slice = 44100 * 2; // 5 seconds.
}

Digest::~Digest()
{
    NNTDECL_PRIVATE_DESTROY();
}

Result Digest::calc(core::data const& da)
{
    return d_ptr->calc(da.bytes(), da.length());
}

NNT_END_NS
NNT_END_CXX
