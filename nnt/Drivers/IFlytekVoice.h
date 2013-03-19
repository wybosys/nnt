
# ifndef __WSI_IFLYTEKVOICE_8BD019552FFB4581ABDAB06B8C54E578_H_INCLUDED
# define __WSI_IFLYTEKVOICE_8BD019552FFB4581ABDAB06B8C54E578_H_INCLUDED

# include "VoiceObject.h"

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_OBJC

WSIDECL_PRIVATE_HEAD(IFlytekVoiceRecognizer);

@interface IFlytekVoiceRecognizer : WSIObject {
    WSIDECL_PRIVATE(IFlytekVoiceRecognizer);
    
    NSString* _appid;
    NSString* _engineurl;
    
}

@property (nonatomic, copy) NSString *appid, *engineurl;

- (void)execute;

@end

WSIDECL_PRIVATE_HEAD(IFlytekSpeech);

@interface IFlytekSpeech : WSIObject {
    WSIDECL_PRIVATE(IFlytekSpeech);
    
    NSString* _appid;
    NSString* _engineurl;
    NSString* _text;
    
}

@property (nonatomic, copy) NSString *appid, *engineurl, *text;

- (void)speak;

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(iflytek)

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

WSI_END_NS
WSI_END_HEADER_CXX

# endif // end cxx

# endif // end objc

# endif
