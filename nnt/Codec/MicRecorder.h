
# ifndef __NNT_MIC_RECORDER_253CED61B8274FACA4BB2BFA57B86A4F_H_INCLUDED
# define __NNT_MIC_RECORDER_253CED61B8274FACA4BB2BFA57B86A4F_H_INCLUDED

# include "../Drivers/MicDevice.h"
# include "AudioFile.h"
# include "../Drivers/AudioBuffer.h"

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

@interface NNTMicRecorder : NNTObject
@end

NNT_EXTERN signal_t kSignalStart, kSignalStop, kSignalPause, kSignalResume;

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(mic)

NNTDECL_PRIVATE_HEAD_CXX(Recorder);

class Recorder
: public ns::Object<NNTMicRecorder>
{
    
    NNTDECL_PRIVATE_CXX(Recorder);
  
public:
    
    Recorder(Device* = NULL);
    ~Recorder();
    
    void set(Device&);
    void set(Device*);
    bool start();
    bool stop();
    
    audio::Buffer const& buffer() const;

    audio::FileType type;
    audio::FormatType format;
    
protected:
    
    Device* _dev;
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif

# endif
