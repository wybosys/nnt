
# include "Core.h"
# include "VoicePrint.h"

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

Result::Result()
{    
    // alloc gmm.
    gmms = new GMM;
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
        }
    }
    
    /*
    for (comprs_type::const_iterator each = comprs.begin();
         each != comprs.end();
         ++each)
    {
        printf("%f\n", *each);
    }
     */
    
    core::pair<double, double> mm = core::max_min<double>(comprs.begin(), comprs.end());
    return mm.second / mm.first;
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
            }
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
