
# import "Core.h"
# import "OAManager.h"

// impls.
# import "OAuths.h"

WSI_BEGIN_OBJC

@interface OAManagerPrivate : NSObject

@property (nonatomic, assign) OAManager *d_owner;
@property (nonatomic, readonly) ::wsi::core::map<Class, oaclass_seg>* classes;

@end

@implementation OAManagerPrivate

@synthesize d_owner;
@synthesize classes;

- (id)init {
    self = [super init];

    classes = new ::wsi::core::map<Class, oaclass_seg>;
    
    return self;
}

- (void)dealloc {
    safe_delete(classes);
    
    [super dealloc];
}

@end

@interface OAManager ()

- (oaclass_seg&)_register_api:(Class)cls seg:(oaclass_seg)seg;

@end

@implementation OAManager

WSIIMPL_SINGLETON(OAManager);

- (id)init {
    self = [super init];
    WSIDECL_PRIVATE_INIT(OAManager);
    return self;
}

- (void)dealloc {
    WSIDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

WSISINGLETON_INIT() {
    
    // register main class.
//    [self _register_api:[OASinaWeibo class] 
//                    seg:(oaclass_seg){[OApiSinaWeiboPost class]}];
//    
//    [self _register_api:[OATencentWeibo class]
//                    seg:(oaclass_seg){[OApiTencentWeiboPost class]}];
//    
//    [self _register_api:[OATencentOS class] 
//                    seg:(oaclass_seg){[OApiQQOSAddShare class]}];
//    
//    [self _register_api:[OANeteaseWeibo class] 
//                    seg:(oaclass_seg){[OApiNeteaseWeiboPost class]}];
//    
//    [self _register_api:[OAKaixin class]  
//                    seg:(oaclass_seg){[OApiKaixinDiaryPost class]}];
//    
//    [self _register_api:[OARenRen class]
//                    seg:(oaclass_seg){[OApiRenRenWeiboPost class]}];
//    
//    [self _register_api:[OASohu class]
//                    seg:(oaclass_seg){[OApiSohuPost class]}];
//    
//    [self _register_api:[OADouban class]
//                    seg:(oaclass_seg){[OApiDoubanDiaryPost class]}];
}

- (oaclass_seg&)_register_api:(Class)cls seg:(oaclass_seg)seg {
    oamanager_iterator iter = d_ptr.classes->insert(::std::make_pair(cls, seg)).first;
    return iter->second;
}

+ (BOOL)registerApi:(Class)cls {
    return [[OAManager getInstance] registerApi:cls];
}

- (BOOL)registerApi:(Class)cls {
    d_ptr.classes->insert(::std::make_pair(cls, oaclass_seg()));
    return YES;
}

+ (uint)count {
    return [[OAManager getInstance] count];
}

- (uint)count {
    return d_ptr.classes->size();
}

+ (Class)classAtIndex:(uint)idx {
    return [[OAManager getInstance] classAtIndex:idx];
}

- (Class)classAtIndex:(uint)idx {
    oamanager_iterator iter = d_ptr.classes->begin();
    while (idx--) {
        ++iter;
    }
    return iter->first;
}

- (oamanager_iterator)iterator_begin {
    return d_ptr.classes->begin();
}

- (oamanager_iterator)iterator_end {
    return d_ptr.classes->end();
}

- (void)showAllWeibo {
    
    [self showSina];
    [self showTencent];
    [self showTencentOS];
    [self showNetease];
    [self showKaixin];
    [self showRenren];
    [self showSohu];
    [self showDouban];
}

- (void)showSina {
    
    [self _register_api:[OASinaWeibo class] 
                    seg:(oaclass_seg){[OApiSinaWeiboPost class]}];
}

- (void)showTencent {
    
    [self _register_api:[OATencentWeibo class]
                    seg:(oaclass_seg){[OApiTencentWeiboPost class]}];
}

- (void)showTencentOS {
    
    [self _register_api:[OATencentOS class] 
                    seg:(oaclass_seg){[OApiQQOSAddShare class]}];
}

- (void)showNetease {
 
    [self _register_api:[OANeteaseWeibo class] 
                    seg:(oaclass_seg){[OApiNeteaseWeiboPost class]}];
}

- (void)showKaixin {
    
    [self _register_api:[OAKaixin class]  
                    seg:(oaclass_seg){[OApiKaixinDiaryPost class]}];
}

- (void)showRenren {
    
    [self _register_api:[OARenRen class]
                    seg:(oaclass_seg){[OApiRenRenWeiboPost class]}];
}

- (void)showSohu {
    
    [self _register_api:[OASohu class]
                    seg:(oaclass_seg){[OApiSohuPost class]}];
}

- (void)showDouban {
    
    [self _register_api:[OADouban class]
                    seg:(oaclass_seg){[OApiDoubanDiaryPost class]}];
}

@end

WSI_END_OBJC