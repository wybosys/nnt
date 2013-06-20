
# ifndef __NNT_MIC_DEVICE_215A7AD1371A4FD3BB53661D396AA5F8_H_INCLUDED
# define __NNT_MIC_DEVICE_215A7AD1371A4FD3BB53661D396AA5F8_H_INCLUDED

# include "AudioObject.h"
# include "AudioBuffer.h"

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(mic)

NNTDECL_PRIVATE_HEAD_CXX(Device);

class Device
: public cxx::Object<>
{
    NNTDECL_PRIVATE_CXX(Device);
    
public:
    
    Device();
    ~Device();
    
    static real SampleRate();
    
    bool add(audio::Buffer&);
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
