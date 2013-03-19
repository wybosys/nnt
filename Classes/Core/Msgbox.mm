
# import "Core.h"
# import "Msgbox.h"

# ifdef WSI_TARGET_IOS
#   import <UIKit/UIKit.h>
#   import "../UIKit/UIAlertView+WSI.h"
# endif

# ifdef WSI_TARGET_MAC
#   import <AppKit/AppKit.h>
# endif

@interface Msgbox (hidden)

+ (BOOL)msgbox:(NSString*)message
         title:(NSString*)__title
          type:(MsgboxType)__type
           obj:(id)obj
            ok:(SEL)ok
        cancel:(SEL)cancel
           ctx:(id)ctx;

+ (int)msgbox_sync:(NSString*)message
             title:(NSString*)__title
              type:(MsgboxType)__type
               obj:(id)obj
                ok:(SEL)ok
            cancel:(SEL)cancel
               ctx:(id)ctx;

+ (BOOL)msgbox:(NSString*)message
         title:(NSString*)__title
          left:(NSString*)left
         right:(NSString*)right
           obj:(id)obj
       actleft:(SEL)actleft
      actright:(SEL)actright
           ctx:(id)ctx;

+ (int)msgbox_sync:(NSString*)message
             title:(NSString*)__title
              left:(NSString*)left
             right:(NSString*)right
               obj:(id)obj
           actleft:(SEL)actleft
          actright:(SEL)actright
               ctx:(id)ctx;

+ (BOOL)msgbox:(NSString*)message
         title:(NSString*)__title
          type:(MsgboxType)__type;

+ (int)msgbox_sync:(NSString*)message
             title:(NSString*)__title
              type:(MsgboxType)__type;

@end

@interface MsgboxDelegate : NSObject

# ifdef WSI_TARGET_IOS
<UIAlertViewDelegate>
# endif

{
    id _obj, _ctx;
    SEL _ok, _cancel;
    CFRunLoopRef _loop;
}

@property (nonatomic, assign) id obj;
@property (nonatomic, retain) id ctx;
@property (nonatomic, assign) SEL ok, cancel;
@property (nonatomic, assign) CFRunLoopRef loop;
@property (nonatomic, readonly) int keyAction;

@end

@implementation MsgboxDelegate

@synthesize obj = _obj, ok = _ok, cancel = _cancel, ctx = _ctx, loop = _loop, keyAction;

- (id)init {
    self = [super init];

    return self;
}

- (void)dealloc {
    self.ctx = nil;
    [super dealloc];
}

# ifdef WSI_TARGET_IOS

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
    if (buttonIndex == 0) {
        if (_ok) {
            [_obj performSelector:_ok withObject:_ctx];
        }
    } else {
        if (_cancel) {
            [_obj performSelector:_cancel withObject:_ctx];
        }
    }
    
    keyAction = buttonIndex;
    
    if (_loop) {
        CFRunLoopStop(_loop);
        _loop = NULL;
    }
}

# endif

@end

@implementation Msgbox (hidden)

+ (BOOL)msgbox:(NSString*)message
         title:(NSString*)__title
          type:(MsgboxType)__type
{
    return [Msgbox msgbox:message
                    title:__title
                     type:__type
                      obj:nil ok:nil cancel:nil ctx:nil];
}

+ (int)msgbox_sync:(NSString*)message
             title:(NSString*)__title
              type:(MsgboxType)__type
{
    return [Msgbox msgbox_sync:message
                         title:__title
                          type:__type
                           obj:nil ok:nil cancel:nil ctx:nil];
}

+ (BOOL)msgbox:(NSString *)message 
         title:(NSString *)__title 
          type:(MsgboxType)__type
           obj:(id)obj
            ok:(SEL)ok
        cancel:(SEL)cancel
           ctx:(id)ctx
{
    BOOL d_ret = YES;
    MsgboxDelegate *delegate = nil;
    NSString* otherTitle = nil;
    
	switch (__type) {
		case MsgboxTypeInfo:
		case MsgboxTypeWarn:
		case MsgboxTypeFatal:
        {
            otherTitle = nil;
		} break;
		case MsgboxTypeStop: {
            otherTitle = _W(@"cancel");
            
            delegate = [[MsgboxDelegate alloc] init];
            delegate.obj = obj;
            delegate.ok = ok;
            delegate.cancel = cancel;
                        
		} break;
	};
    
# ifdef WSI_TARGET_IOS
    
	WSIUIAlertView *alert = [[WSIUIAlertView alloc] initWithTitle:__title
                                                          message:message
                                                         delegate:delegate
                                                cancelButtonTitle:_W(@"ok")
                                                otherButtonTitles:otherTitle, nil];
    if (delegate) {
        delegate.ctx = ctx;
        [alert storeSet:@"::delegate" obj:delegate];
        safe_release(delegate);
    }
    
	if (alert == nil) {
        [alert release];
		return YES;
	}
    
    // show in mainthread.
    [alert performSelectorOnMainThread:@selector(show) withObject:nil waitUntilDone:YES];
    
    safe_release(alert);
    
# endif
    
	return d_ret;
}

+ (int)msgbox_sync:(NSString *)message
             title:(NSString *)__title
              type:(MsgboxType)__type
               obj:(id)obj
                ok:(SEL)ok
            cancel:(SEL)cancel
               ctx:(id)ctx
{
    MsgboxDelegate *delegate = nil;
    NSString* otherTitle = nil;
    
	switch (__type) {
		case MsgboxTypeInfo:
		case MsgboxTypeWarn:
		case MsgboxTypeFatal:
        {
            otherTitle = nil;
		} break;
		case MsgboxTypeStop:
        {
            otherTitle = _W(@"cancel");
		} break;
	};
    
    delegate = [[MsgboxDelegate alloc] init];
    delegate.obj = obj;
    delegate.ok = ok;
    delegate.ctx = ctx;
    delegate.cancel = cancel;
    delegate.loop = CFRunLoopGetCurrent();
    
# ifdef WSI_TARGET_IOS
    
	WSIUIAlertView *alert = [[WSIUIAlertView alloc] initWithTitle:__title
                                                          message:message
                                                         delegate:delegate
                                                cancelButtonTitle:_W(@"ok")
                                                otherButtonTitles:otherTitle, nil];
    [alert storeSet:@"::delegate" obj:delegate];
    safe_release(delegate);
    
	if (alert == nil) {
        [alert release];
		return 0;
	}
    
    // show in mainthread.
    [alert performSelectorOnMainThread:@selector(show) withObject:nil waitUntilDone:YES];
    
    safe_release(alert);
    
# endif
    
    // wait.
    CFRunLoopRun();
    
	return delegate.keyAction;
}

+ (BOOL)msgbox:(NSString*)message
         title:(NSString*)__title 
          left:(NSString*)left 
         right:(NSString*)right 
           obj:(id)obj 
       actleft:(SEL)actleft 
      actright:(SEL)actright
           ctx:(id)ctx
{
    
    BOOL d_ret = YES;
    MsgboxDelegate *delegate = [[MsgboxDelegate alloc] init];
    delegate.obj = obj;
    delegate.ok = actleft;
    delegate.cancel = actright;
    delegate.ctx = ctx;
    
# ifdef WSI_TARGET_IOS
    
    WSIUIAlertView *alert = [[WSIUIAlertView alloc] initWithTitle:__title
                                                          message:message
                                                         delegate:delegate
                                                cancelButtonTitle:left
                                                otherButtonTitles:right, nil];
    [alert storeSet:@"::delegate" obj:delegate];
    safe_release(delegate);

	if (alert == nil) {
        [alert release];
		return YES;
	}
    
    // show in mainthread.
    [alert performSelectorOnMainThread:@selector(show) withObject:nil waitUntilDone:YES];

    safe_release(alert);
    
# endif
    
	return d_ret;
}

+ (int)msgbox_sync:(NSString*)message
             title:(NSString*)__title
              left:(NSString*)left
             right:(NSString*)right
               obj:(id)obj
           actleft:(SEL)actleft
          actright:(SEL)actright
               ctx:(id)ctx
{
    
    MsgboxDelegate *delegate = [[MsgboxDelegate alloc] init];
    delegate.obj = obj;
    delegate.ok = actleft;
    delegate.cancel = actright;
    delegate.ctx = ctx;
    delegate.loop = CFRunLoopGetCurrent();
    
# ifdef WSI_TARGET_IOS
    
    WSIUIAlertView *alert = [[WSIUIAlertView alloc] initWithTitle:__title
                                                          message:message
                                                         delegate:delegate
                                                cancelButtonTitle:left
                                                otherButtonTitles:right, nil];
    [alert storeSet:@"::delegate" obj:delegate];
    safe_release(delegate);

	if (alert == nil) {
        [alert release];
		return 0;
	}
    
    // show in mainthread.
    [alert performSelectorOnMainThread:@selector(show) withObject:nil waitUntilDone:YES];
    
    safe_release(alert);
    
# endif
    
    CFRunLoopRun();
    
	return delegate.keyAction;
}

@end

@implementation Msgbox

+ (void)info:(NSString *)message title:(NSString*)__title {
	[Msgbox msgbox:message title:__title type:MsgboxTypeInfo];
}

+ (void)info:(NSString *)message {
	[Msgbox info:message title:_W(@"info")];
}

+ (void)warn:(NSString *)message title:(NSString*)__title {
	[Msgbox msgbox:message title:__title type:MsgboxTypeWarn];
}

+ (void)warn:(NSString *)message {
	[Msgbox warn:message title:_W(@"warn")];
}

+ (BOOL)stop:(NSString *)message title:(NSString*)__title obj:(id)obj ok:(SEL)ok cancel:(SEL)cancel {
	return [Msgbox msgbox:message title:__title type:MsgboxTypeStop obj:obj ok:ok cancel:cancel ctx:nil];
}

+ (BOOL)stop:(NSString *)message obj:(id)obj ok:(SEL)ok cancel:(SEL)cancel {
	return [Msgbox stop:message title:_W(@"stop") obj:obj ok:ok cancel:cancel];
}

+ (BOOL)stop:(NSString *)message title:(NSString*)__title obj:(id)obj ok:(SEL)ok cancel:(SEL)cancel ctx:(id)ctx {
	return [Msgbox msgbox:message title:__title type:MsgboxTypeStop obj:obj ok:ok cancel:cancel ctx:ctx];
}

+ (BOOL)stop:(NSString *)message obj:(id)obj ok:(SEL)ok cancel:(SEL)cancel ctx:(id)ctx {
	return [Msgbox stop:message title:_W(@"stop") obj:obj ok:ok cancel:cancel ctx:ctx];
}

+ (void)fatal:(NSString *)message title:(NSString*)__title {
	[Msgbox msgbox:message title:__title type:MsgboxTypeFatal];
}

+ (void)fatal:(NSString *)message {
	[Msgbox fatal:message title:_W(@"fatal")];
}

+ (void)yesno:(NSString*)message left:(NSString*)left right:(NSString*)right obj:(id)obj actl:(SEL)actl actr:(SEL)actr {
    [Msgbox msgbox:message title:nil left:left right:right obj:obj actleft:actl actright:actr ctx:nil];
}

@end

@implementation Confirm

+ (void)info:(NSString*)message title:(NSString*)title {
    [Msgbox msgbox_sync:message title:title type:MsgboxTypeInfo];
}

+ (void)info:(NSString*)message {
    [Confirm info:message title:_W(@"info")];
}

+ (void)warn:(NSString*)message title:(NSString*)title {
    [Msgbox msgbox_sync:message title:title type:MsgboxTypeWarn];
}

+ (void)warn:(NSString*)message {
    [Confirm warn:message title:_W(@"warn")];
}

+ (bool)yesno:(NSString *)message left:(NSString *)left right:(NSString *)right {
    int ret = [Msgbox msgbox_sync:message title:nil left:left right:right obj:nil actleft:nil actright:nil ctx:nil];
    return ret == 0;
}

@end

WSI_END_OBJC

WSI_BEGIN_CXX
WSI_BEGIN_NS(core)

void Msgbox::info(ns::String const& msg)
{
    [::Msgbox info:msg];
}

void Msgbox::info(ns::String const& msg, ns::String const& title)
{
    [::Msgbox info:msg title:title];
}

void Msgbox::warn(ns::String const& msg)
{
    [::Msgbox warn:msg];
}

void Msgbox::warn(ns::String const& msg, ns::String const& title)
{
    [::Msgbox warn:msg title:title];
}

void Msgbox::fatal(ns::String const& msg)
{
    [::Msgbox fatal:msg];
}

void Msgbox::fatal(ns::String const& msg, ns::String const& title)
{
    [::Msgbox fatal:msg title:title];
}

void Confirm::info(ns::String const& msg)
{
    [::Confirm info:msg];
}

void Confirm::info(ns::String const& msg, ns::String const& title)
{
    [::Confirm info:msg title:title];
}

void Confirm::warn(ns::String const& msg)
{
    [::Confirm warn:msg];
}

void Confirm::warn(ns::String const& msg, ns::String const& title)
{
    [::Confirm warn:msg title:title];
}

bool Confirm::yesno(const ns::String &msg, const ns::String &left, const ns::String &right)
{
    return [::Confirm yesno:msg left:left right:right];
}

WSI_END_NS
WSI_END_CXX
