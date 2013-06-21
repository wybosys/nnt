
# ifndef __NNT_AUDIOFILE_6800445606AD4BC59E5C468D1835F405_H_INCLUDED
# define __NNT_AUDIOFILE_6800445606AD4BC59E5C468D1835F405_H_INCLUDED

# ifdef NNT_MACH

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
    void set_sampler(real);
    
    void update(AudioQueueRef);
    void update(FileType const&);
    void update();
    
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
    
# ifdef NNT_OBJC
    FileType(ns::String const&);
# else
    FileType(core::string const&);
# endif
    
    ~FileType();
    
# ifdef NNT_OBJC
    void set(ns::String const&);
# else
    void set(core::string const&);
# endif
    
    bool is_bigedian(FormatType const&) const;
    
# ifdef NNT_OBJC
    static AudioFileTypeID FindType(ns::String const&);
# else
    static AudioFileTypeID FindType(core::string const&);
# endif
    
    operator AudioFileTypeID const& () const
    {
        return _type;
    }
    
    operator AudioFileTypeID const* () const
    {
        return &_type;
    }
    
# ifdef NNT_OBJC
    operator ns::String const& () const
    {
        return _strtype;
    }
# endif
    
    operator core::string () const
    {
        return core::type_cast<core::string>(_strtype);
    }
    
protected:
    
# ifdef NNT_OBJC
    ns::String _strtype;
# else
    core::string _strtype;
# endif
    
    AudioFileTypeID _type;
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif

# endif
