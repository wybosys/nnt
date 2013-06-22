
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
    // alloc gmm.
    gmms = new GMM;
}

Result::Result(Result const& r)
{
    // alloc.
    gmms = new GMM;
    
    // copy mfcc
    mfccs = r.mfccs;
    
    // copy gmm
    *(GMM*)gmms = *(GMM*)r.gmms;
}

Result::~Result()
{
    safe_delete<GMM>(gmms);
}

Result& Result::operator = (Result const& r)
{
    // copy mfcc
    mfccs = r.mfccs;
    
    // copy gmm
    *(GMM*)gmms = *(GMM*)r.gmms;
    
    return *this;
}

real Result::compare(Result const& r)
{
    if (!mfccs.size() || !r.mfccs.size())
        return 0;
    
    typedef core::vector<double> comprs_type;
    comprs_type comprs;
    
    /*
    use<GMM> gmms = this->gmms;
    for (mfccs_type::const_iterator each = mfccs.begin();
         each != mfccs.end();
         ++each)
    {
        double tmp;
        if (GMM_identify(*each, &tmp, gmms, SLICE_LEN, M))
        {
            double val = fabs(tmp);
            comprs.push_back(val);
            
# ifdef NNT_DEBUG
            printf("left %f\n", val);
# endif
        }
    }
        
    for (mfccs_type::const_iterator each = r.mfccs.begin();
         each != r.mfccs.end();
         ++each)
    {
        double tmp;
        if (GMM_identify(*each, &tmp, gmms, SLICE_LEN, M))
        {
            double val = fabs(tmp);
            comprs.push_back(val);
            
# ifdef NNT_DEBUG
            printf("right %f\n", val);
# endif
        }
    }
     */
    
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

Result calc(byte* d, usize dlen)
{
    Result ret;    
    core::framedata fd(d, dlen);
    
    use<GMM> gmms = ret.gmms;
    
    usize const framelen = dlen / FRAME_LEN;
    
    // calc mfcc.
    mfcc t_mfcc(framelen);
    if (voiceToMFCC((BYTE*)d, dlen, t_mfcc, 200))
    {
        if (GMMs(t_mfcc, gmms, 200, M))
        {
            ret.mfccs.push_back(t_mfcc);
            
            trace_msg("processed slice for vp");
        }
# ifdef NNT_DEBUG
        else
        {
            trace_msg("skip slice for vp");
        }
# endif
    }
    
    return ret;
}

NNTDECL_PRIVATE_END_CXX

Digest::Digest()
{
    NNTDECL_PRIVATE_CONSTRUCT(Digest);
    
    slice = 44100 * 5; // 5 seconds.
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
