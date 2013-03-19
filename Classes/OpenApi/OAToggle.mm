
# import "Core.h"
# import "OAToggle.h"
# import "OAuths.h"
# import "OAManager.h"

NNT_BEGIN_OBJC

@interface OAToggle ()

- (NSString*)get_uid:(uindex)idx;
- (NSString*)get_uid_byclass:(Class)cls;

@end

@implementation OAToggle

@synthesize delegate;
@dynamic showAllWeibo, showSina, showTencent, showTencentOS, showKaixin, showDouban, showSohu, showRenren, showNetease;

- (id)init {
    self = [super init];
    
    _manager = [OAManager getInstance];
    return self;
}

- (void)dealloc {
    [super dealloc];
}

- (void)initShowWeibo {
    
    if ([delegate respondsToSelector:@selector(toggleShowWeibo:)]) {
        [delegate toggleShowWeibo:self];
    } else {
        [self showAllWeibo];
    }
}

- (usize)count {
    [self initShowWeibo];
    return [_manager count];
}

- (NSString*)name:(uindex)idx {
    Class cls = [_manager classAtIndex:idx];
    return [cls Name];
}

- (UIImage*)logoImage:(uindex)idx {
    Class cls = [_manager classAtIndex:idx];
    return [cls LogoImage];
}

- (NSString*)get_uid:(uindex)idx {
    Class cls = [_manager classAtIndex:idx];
    NSString* uid = [cls UniqueIdentity];
    return uid;
}

- (NSString*)get_uid_byclass:(Class)cls {
    return [cls UniqueIdentity];
}

- (NSDictionary*)load:(uindex)idx {
    NSString* uid = [self get_uid:idx];
    if (delegate == nil) 
        dthrow_msg(@"NULL", @"delegate of OAToggle is NULL!");
    return [delegate load:uid];
}

- (NSDictionary*)load_byclass:(Class)cls {
    NSString* uid = [self get_uid_byclass:cls];
    if (delegate == nil) 
        dthrow_msg(@"NULL", @"delegate of OAToggle is NULL!");
    return [delegate load:uid];
}

- (NSDictionary*)load_unsafe:(uindex)idx {
    NSString* uid = [self get_uid:idx];
    return [delegate load:uid];
}

- (NSDictionary*)load_byclass_unsafe:(Class)cls {
    NSString* uid = [self get_uid_byclass:cls];
    return [delegate load:uid];
}

- (void)save:(NSDictionary*)data idx:(uindex)idx {
    NSString* uid = [self get_uid:idx];
    [delegate save:data uid:uid];
}

- (void)del:(uindex)idx {
    NSString *uid = [self get_uid:idx];
    [delegate del:uid];
}

- (void)authorize:(uindex)idx {
    Class cls = [_manager classAtIndex:idx];
    id obj = [[cls alloc] init];
    [obj storeSet:@"toggle::index" obj:::nnt::number(idx)];
    [obj connect:kSignalAuthorizeSuccess sel:@selector(__suc_authorize:) obj:self];
    [obj retrieve];
    [obj release];
}

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(@"kSignalToggleAuthorizeSuccess")
NNTEVENT_END

- (void)__suc_authorize:(NNTEventObj*)evt {
    ::nnt::ns::MutableDictionary dict;
    dict[@"enable"] = NSNumberYes;

    id sender = (id)evt.sender;
    [sender saveTo:dict];
    
    uindex idx = [[(id)sender storeFind:@"toggle::index"] unsignedIntValue];
    NSString* uid = [self get_uid:idx];
    
    if (delegate == nil) 
        dthrow_msg(@"NULL", @"delegate of OAToggle is NULL!");

    [delegate save:dict uid:uid];
    [self emit:@"kSignalToggleAuthorizeSuccess"];
}

- (BOOL)is_enable:(uindex)idx {
    ::nnt::ns::Dictionary dict([self load:idx]);
    return dict[@"enable"] == NSNumberYes;
}

- (BOOL)is_enable_byclass:(Class)cls {
    ::nnt::ns::Dictionary dict([self load_byclass:cls]);
    return dict[@"enable"] == NSNumberYes;
}

- (void)setShowAllWeibo:(BOOL)show {
    if(show)
        [_manager showAllWeibo];
}

- (void)setShowSina:(BOOL)is_show {
    if (is_show)
        [_manager showSina];
}

- (void)setShowTencent:(BOOL)is_show {
    if (is_show)
        [_manager showTencent];
}

- (void)setShowTencentOS:(BOOL)is_show {
    if (is_show)
        [_manager showTencentOS];
}

- (void)setShowNetease:(BOOL)is_show {
    if (is_show)
        [_manager showNetease];
}

- (void)setShowKaixin:(BOOL)is_show {
    if (is_show)
        [_manager showKaixin];
}

- (void)setShowRenren:(BOOL)is_show {
    if (is_show)
        [_manager showRenren];
}

- (void)setShowSohu:(BOOL)is_show {
    if (is_show)
        [_manager showSohu];
}

- (void)setShowDouban:(BOOL)show {
    if (show)
        [_manager showDouban];
}

@end

NNT_END_OBJC