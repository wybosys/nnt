
# import "Core.h"
# import "OAPush.h"
# import "Server.h"
# import "Context.h"
# import "OAManager.h"
# import "OAuth.h"

WSI_BEGIN_OBJC

@protocol OAPost <NSObject>

- (void)setApiType:(OAuthApiType)type;
- (void)setContent:(NSString*)str;
- (void)setTitle:(NSString*)str;
- (void)setReference:(NSString*)str;

@end

@implementation OAPush

@synthesize message, title, reference;

- (id)init {
    self = [super init];
    self.title = @"WSI";
    return self;
}

- (void)dealloc {
    [message release];
    [title release];
    [reference release];
    [super dealloc];
}

- (void)push {
    oamanager_iterator iter = [_manager iterator_begin];
    for (; iter != [_manager iterator_end]; ++iter) {
        Class clsAuth = iter->first;
        if (NO == [self is_enable_byclass:clsAuth])
            continue;
        
        oaclass_seg& seg = iter->second;
        Class clsPost = seg.clsPost;
        
        NSDictionary* data = [self load_byclass:clsAuth];
        NSObject<OAuth>* obj_auth = (NSObject<OAuth>*)[[clsAuth alloc] initFromData:data];
        NSObject* obj_post = [[clsPost alloc] initWithOAuth:obj_auth];
        
        if ([obj_post respondsToSelector:@selector(setApiType:)]) {
            [(id<OAPost>)obj_post setApiType:OAuthApiTypeJSON];
        }
        
        if ([obj_post respondsToSelector:@selector(setTitle:)]) {
            [(id<OAPost>)obj_post setTitle:self.title];
        }
        
        if ([obj_post respondsToSelector:@selector(setReference:)]) {
            [(id<OAPost>)obj_post setReference:self.reference];
        }
        
        //if ([obj_post respondsToSelector:@selector(setContent:)]) {
        [(id<OAPost>)obj_post setContent:self.message];
        //}
        
        [SERV() retrieve_model_async:(Model*)obj_post selector:@selector(act_done:) object:self];
        
        [obj_post release];
        [obj_auth release];
    }
}

- (void)act_done:(Model*)mdl {
# ifdef WSI_DEBUG
    NSString* clsName = [NSString stringWithUTF8String:object_getClassName(mdl)];
    trace_fmt(@"succeed in send a post to %@ .", clsName);
# endif
}

@end

WSI_END_OBJC