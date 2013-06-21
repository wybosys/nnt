
# include "Core.h"
# include "VoicePrint.h"
# include "../Math/Statistic.h"

NNT_BEGIN_HEADER_C

# include "../../contrib/openvp/voice_id/voiceIdentify.h"

NNT_END_HEADER_C

NNT_BEGIN_CXX
NNT_BEGIN_NS(vp)

mfcc::mfcc()
{
    _data = (double**)malloc(FRAME_LEN * sizeof(double*));
    for (uint i = 0; i < FRAME_LEN; ++i)
        _data[i] = (double*)malloc(D * sizeof(double));
}

mfcc::mfcc(mfcc const& r)
{
    _data = (double**)malloc(FRAME_LEN * sizeof(double*));
    for (uint i = 0; i < FRAME_LEN; ++i)
    {
        _data[i] = (double*)malloc(D * sizeof(double));
        memcpy(_data[i], r._data[i], D * sizeof(double));
    }
}

mfcc& mfcc::operator = (mfcc const& r)
{
    for (uint i = 0; i < FRAME_LEN; ++i)
    {
        memcpy(_data[i], r._data[i], D * sizeof(double));
    }
    return *this;
}

mfcc::~mfcc()
{
    for (uint i = 0; i < FRAME_LEN; ++i)
        free(_data[i]);
    free(_data);
}

void mfcc::to(core::data &da) const
{
    da.clear();
    for (uint i = 0; i < FRAME_LEN; ++i)
    {
        da.append(_data[i], D * sizeof(double));
    }
}

void mfcc::from(core::data const& da)
{
    core::framedata fd(da.bytes(), da.length());
    for (uint i = 0; i < FRAME_LEN; ++i)
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
    
    use<GMM> gmms = this->gmms;
    for (mfccs_type::const_iterator each = mfccs.begin();
         each != mfccs.end();
         ++each)
    {
        double tmp;
        if (GMM_identify(*each, &tmp, gmms, FRAME_LEN, M))
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
        if (GMM_identify(*each, &tmp, gmms, FRAME_LEN, M))
        {
            double val = fabs(tmp);
            comprs.push_back(val);
            
# ifdef NNT_DEBUG
            printf("right %f\n", val);
# endif
        }
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

Result calc(byte* d, usize len)
{
    Result ret;
    core::framedata fd(d, len);
    
    use<GMM> gmms = ret.gmms;
    
    while (fd.length())
    {
        usize len = 320 * FRAME_LEN;
        byte* buf = fd.bytes();
        bool release = false;

        if (len > fd.length())
        {
            byte* nbuf = core::alloc::Heap<byte>::Alloc(len);
            core::alloc::Heap<byte>::Fill(nbuf, len, 0);
            core::alloc::Heap<byte>::Copy(nbuf, buf, fd.length());
            buf = nbuf;
            release = true;
        }    
        
        mfcc t_mfcc;
        if (voiceToMFCC((BYTE*)buf, len, t_mfcc, FRAME_LEN))
        {            
            if (GMMs(t_mfcc, gmms, FRAME_LEN, M))
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
    
        if (release)
            core::alloc::Heap<byte>::Free(buf);
        
        fd.move(len);
    }
    
    return ret;
}

NNTDECL_PRIVATE_END_CXX

Digest::Digest()
{
    NNTDECL_PRIVATE_CONSTRUCT(Digest);
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
