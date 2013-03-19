
# ifndef __NNT_CORE_MSGBOX_F51B7CFBF50F4F28A7AA8163304F02AA_H_INCLUDED
# define __NNT_CORE_MSGBOX_F51B7CFBF50F4F28A7AA8163304F02AA_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

typedef enum {
    MsgboxTypeInfo,
    MsgboxTypeWarn,
    MsgboxTypeStop,
    MsgboxTypeFatal,
} MsgboxType;

//! @class msgbox, use signals to get callback.
@interface Msgbox : NSObject

//! info.
+ (void)info:(NSString*)message title:(NSString*)title;
+ (void)info:(NSString*)message;

//! warning.
+ (void)warn:(NSString*)message title:(NSString*)title;
+ (void)warn:(NSString*)message;

//! stop for confirm.
+ (BOOL)stop:(NSString*)message title:(NSString*)title obj:(id)obj ok:(SEL)ok cancel:(SEL)cancel;
+ (BOOL)stop:(NSString*)message obj:(id)obj ok:(SEL)ok cancel:(SEL)cancel;
+ (BOOL)stop:(NSString*)message title:(NSString*)title obj:(id)obj ok:(SEL)ok cancel:(SEL)cancel ctx:(id)ctx;
+ (BOOL)stop:(NSString*)message obj:(id)obj ok:(SEL)ok cancel:(SEL)cancel ctx:(id)ctx;

//! fatal.
+ (void)fatal:(NSString*)message title:(NSString*)title;
+ (void)fatal:(NSString*)message;

//! yesno.
+ (void)yesno:(NSString*)message left:(NSString*)left right:(NSString*)right obj:(id)obj actl:(SEL)actl actr:(SEL)actr;

@end

//!@class confirm box, use return value.
@interface Confirm : NSObject

//! info.
+ (void)info:(NSString*)message title:(NSString*)title;
+ (void)info:(NSString*)message;

+ (void)warn:(NSString*)message title:(NSString*)title;
+ (void)warn:(NSString*)message;

//! yes no.
+ (bool)yesno:(NSString*)message left:(NSString*)left right:(NSString*)right;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(core)

class Msgbox
{
public:
    
    static void info(ns::String const& msg);
    static void info(ns::String const& msg, ns::String const& title);
    
    static void warn(ns::String const& msg);
    static void warn(ns::String const& msg, ns::String const& title);
    
    static void fatal(ns::String const& msg);
    static void fatal(ns::String const& msg, ns::String const& title);
    
};

class Confirm
{
public:
    
    static void info(ns::String const& msg);
    static void info(ns::String const& msg, ns::String const& title);
    
    static void warn(ns::String const& msg);
    static void warn(ns::String const& msg, ns::String const& title);
    
    static bool yesno(ns::String const& msg, ns::String const& left, ns::String const& right);
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif