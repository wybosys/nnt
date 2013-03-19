
# ifndef __NNT_IFLYTEKVOICE_8BD019552FFB4581ABDAB06B8C54E578_H_INCLUDED
# define __NNT_IFLYTEKVOICE_8BD019552FFB4581ABDAB06B8C54E578_H_INCLUDED

# include "VoiceObject.h"

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

NNTDECL_PRIVATE_HEAD(IFlytekVoiceRecognizer);

@interface IFlytekVoiceRecognizer : NNTObject {
    NNTDECL_PRIVATE(IFlytekVoiceRecognizer);
    
    NSString* _appid;
    NSString* _engineurl;
    
}

@property (nonatomic, copy) NSString *appid, *engineurl;

- (void)execute;

@end

NNTDECL_PRIVATE_HEAD(IFlytekSpeech);

@interface IFlytekSpeech : NNTObject {
    NNTDECL_PRIVATE(IFlytekSpeech);
    
    NSString* _appid;
    NSString* _engineurl;
    NSString* _text;
    
}

@property (nonatomic, copy) NSString *appid, *engineurl, *text;

- (void)speak;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(iflytek)

class VoiceRecognizer
: public ns::Object<IFlytekVoiceRecognizer>
{
public:
    
    VoiceRecognizer();
    ~VoiceRecognizer();
    
    void set_appid(ns::String const&);
    void set_engineurl(ns::String const&);
    
    void execute();
    
};

class Speech
: public ns::Object<IFlytekSpeech>
{
public:
    
    Speech();
    ~Speech();
    
    void set_appid(ns::String const&);
    void set_engineurl(ns::String const&);
    
    void set_text(ns::String const&);
    void speak();

};

NNT_END_NS
NNT_END_HEADER_CXX

# endif // end cxx

# endif // end objc

# endif
