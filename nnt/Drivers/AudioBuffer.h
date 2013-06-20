
# ifndef __NNT_AUDIO_BUFFER_DC14C23D0DCB40929F7046C63F58A1C9_H_INCLUDED
# define __NNT_AUDIO_BUFFER_DC14C23D0DCB40929F7046C63F58A1C9_H_INCLUDED

# include "AudioObject.h"

NNT_BEGIN_HEADER_CXX

NNT_EXTERN cxx::signal_t kSignalBytesAvailable;

NNT_BEGIN_NS(audio)

NNTDECL_PRIVATE_HEAD_CXX(Buffer);

class Buffer
: public Object
{
    NNTDECL_PRIVATE_CXX(Buffer);
    
public:
    
    NNTDECL_SIGNALS_SLOTS;
    
    Buffer();
    ~Buffer();
    
    bool open();
    void close();
  
# ifdef NNT_MACH
    
    AudioQueueRef queue;
    AudioFileStreamID stm;
    AudioFileTypeID type;
    AudioStreamBasicDescription format;
    bool used;
    
    void receive(AudioQueueRef                   inAQ,
                 AudioQueueBufferRef             inBuffer,
                 const AudioTimeStamp *          inStartTime,
                 UInt32							inNumPackets,
                 const AudioStreamPacketDescription *inPacketDesc);
    
    core::vector<AudioQueueBufferRef>& handle();
    bool need_release;
    SInt64 packets;
    
# endif
    
    real seconds;
    core::data data;
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif
