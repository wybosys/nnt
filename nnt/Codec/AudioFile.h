
# ifndef __NNT_AUDIOFILE_6800445606AD4BC59E5C468D1835F405_H_INCLUDED
# define __NNT_AUDIOFILE_6800445606AD4BC59E5C468D1835F405_H_INCLUDED

# ifdef NNT_MACH

# include <AudioToolbox/AudioToolbox.h>
# include <CoreAudio/CoreAudio.h>

# endif

# include "../Drivers/AudioObject.h"

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX

NNT_BEGIN_NS(core)

class IoStream;

NNT_END_NS

NNT_BEGIN_NS(audio)

class FileType;

class FormatType
{
public:
    
    FormatType();
    ~FormatType();
    
    void set_channel(uint);
    uint channel() const;
    void set_bits(uint);
    uint bits() const;
    void set_sampler(real);
    real sampler() const;
    
# ifdef NNT_MACH
    
    void update(AudioQueueRef);
    
# endif
    
    void update(FileType const&);
    void update();
    
# ifdef NNT_MACH
    
    AudioStreamBasicDescription* operator -> ()
    {
        return &_format;
    }
    
    AudioStreamBasicDescription const* operator -> () const
    {
        return &_format;
    }
    
    operator AudioStreamBasicDescription& ()
    {
        return _format;
    }
    
    operator AudioStreamBasicDescription const& () const
    {
        return _format;
    }
    
    operator AudioStreamBasicDescription const* () const
    {
        return &_format;
    }
    
# endif
    
protected:
    
# ifdef NNT_MACH
    
    AudioStreamBasicDescription _format;
    
# endif
    
};

class FileType
{
public:
    
    FileType();
    FileType(core::string const&);
    FileType(NntAudioFormat);
    
    ~FileType();
    
    void set(core::string const&);
    
    bool is_bigedian(FormatType const&) const;
    
# ifdef NNT_MACH
    
    static AudioFileTypeID FindType(core::string const&);
    
    operator AudioFileTypeID const& () const
    {
        return _type;
    }
    
    operator AudioFileTypeID const* () const
    {
        return &_type;
    }
    
# endif
    
    operator core::string () const
    {
        return _strtype;
    }
    
protected:
    
    core::string _strtype;
    
# ifdef NNT_MACH
    
    AudioFileTypeID _type;
    
# endif
    
};

/*
class FileFormat
{
public:
    
    FileFormat();
    ~FileFormat();
    
    void load(core::IoStream&);
    
    FileType ft;
    FormatType mt;
    
};
 */

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
