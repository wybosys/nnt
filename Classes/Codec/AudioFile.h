
# ifndef __NNT_AUDIOFILE_6800445606AD4BC59E5C468D1835F405_H_INCLUDED
# define __NNT_AUDIOFILE_6800445606AD4BC59E5C468D1835F405_H_INCLUDED

# ifdef NNT_OBJC

# ifdef NNT_CXX

# include <AudioToolbox/AudioToolbox.h>
# include <CoreAudio/CoreAudio.h>

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(audio)

class FileType;

class FormatType
{
public:
    
    FormatType();
    ~FormatType();
    
    void set_channel(uint);
    void set_bits(uint);
    
    void update(AudioQueueRef);
    void update(FileType const&);
    
    operator AudioStreamBasicDescription const& () const
    {
        return _format;
    }
    
    operator AudioStreamBasicDescription const* () const
    {
        return &_format;
    }
    
protected:
    
    AudioStreamBasicDescription _format;
    
};

class FileType
{
public:
    
    FileType();
    FileType(ns::String const&);
    ~FileType();
    
    void set(ns::String const&);
    
    bool is_bigedian(FormatType const&) const;
    static AudioFileTypeID FindType(ns::String const&);
    
    operator AudioFileTypeID const& () const
    {
        return _type;
    }
    
    operator AudioFileTypeID const* () const
    {
        return &_type;
    }
    
protected:
    
    AudioFileTypeID _type;
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif

# endif
