
# ifndef __NNT_AUDIOSTREAM_994260C3757F40CB958C6BAAE2670905_H_INCLUDED
# define __NNT_AUDIOSTREAM_994260C3757F40CB958C6BAAE2670905_H_INCLUDED

# ifdef NNT_TARGET_IOS

class AudioStreamBasicDescription;

# endif

NNT_BEGIN_HEADER_CXX

class CCAbstractPCMAudioStream
: public cxx::Object<>
{
public:
    
    CCAbstractPCMAudioStream();
    ~CCAbstractPCMAudioStream();
    
    // 读取一个文件
    virtual bool load(core::string const&) = 0;
    
};

# ifdef NNT_TARGET_IOS

class CCPCMAudioStreamIOS
: public CCAbstractPCMAudioStream
{
public:
    
    CCPCMAudioStreamIOS();
    ~CCPCMAudioStreamIOS();
    
    virtual bool load(core::string const&);
    
protected:
    
    AudioStreamBasicDescription* _ofmt;
    core::data _buf;
    
    friend class CCOpenALAudioPlayer;
};

typedef CCPCMAudioStreamIOS CCPCMAudioStream;

# endif

# ifdef NNT_TARGET_ANDROID

class CCPCMAudioStreamAndroid
: public CCAbstractPCMAudioStream
{
public:
    
    CCPCMAudioStreamAndroid();
    ~CCPCMAudioStreamAndroid();
    
    virtual bool load(CCString const&);
    
};

typedef CCPCMAudioStreamAndroid CCPCMAudioStream;

# endif

NNT_END_HEADER_CXX

# endif

