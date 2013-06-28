
# ifndef __NNT_AUDIO_BUFFER_DC14C23D0DCB40929F7046C63F58A1C9_H_INCLUDED
# define __NNT_AUDIO_BUFFER_DC14C23D0DCB40929F7046C63F58A1C9_H_INCLUDED

# include "AudioObject.h"
# include "../Codec/AudioFile.h"

NNT_BEGIN_HEADER_CXX

NNT_EXTERN cxx::signal_t kSignalBytesAvailable;

NNT_BEGIN_NS(core)

class IoStream;

NNT_END_NS

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
    
    virtual bool open() = 0;
    virtual void close();
    
    audio::FileType type;
    audio::FormatType format;
  
# ifdef NNT_MACH
    
    AudioQueueRef queue;
    AudioFileID stm;
    bool used;
    
    core::vector<AudioQueueBufferRef>& handle();
    bool need_release;
    SInt64 packets;
    
# endif
    
    real seconds;
    core::data data;
    
};

NNTDECL_PRIVATE_HEAD_CXX(RecordBuffer);

class RecordBuffer
: public Buffer
{
    NNTDECL_PRIVATE_CXX(RecordBuffer);
    
    RecordBuffer();
    ~RecordBuffer();
    
    virtual bool open();    
    
# ifdef NNT_MACH
    
    void receive(AudioQueueRef                   inAQ,
                 AudioQueueBufferRef             inBuffer,
                 const AudioTimeStamp *          inStartTime,
                 UInt32							inNumPackets,
                 const AudioStreamPacketDescription *inPacketDesc);
    
# endif
    
};

NNTDECL_PRIVATE_HEAD_CXX(PlayBuffer);

class PlayBuffer
: public Buffer
{
    
    NNTDECL_PRIVATE_CXX(PlayBuffer);

public:
    
    PlayBuffer();
    ~PlayBuffer();
    
    virtual bool open();
    virtual void close();
    virtual bool read(core::data&, uint offset);
    virtual usize length() const;
    
    core::IoStream* stream;

};

NNT_END_NS
NNT_END_HEADER_CXX

# endif
