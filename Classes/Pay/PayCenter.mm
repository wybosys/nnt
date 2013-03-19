
# import "Core.h"
# import "PayCenter.h"
# import "PayNullApi.h"

# define ENABLE_ALIPAY
//# define ENABLE_UNIPAY

// some implements.

# ifdef ENABLE_ALIPAY
# import "AlipayApi.h"
# endif

# ifdef ENABLE_UNIPAY
# import "UnipayApi.h"
# endif

NNT_BEGIN_OBJC

static PayCenter *__gs_paycenter = nil;

@implementation PayCenter

- (id)init {
    self = [super init];
    
    NSMutableDictionary *dict = [[NSMutableDictionary alloc] initWithCapacity:10];
    
# ifdef ENABLE_ALIPAY
    [dict setObject:[AlipayApi class] forKey:[AlipayApi identity]];
# endif
    
# ifdef ENABLE_UNIPAY
    [dict setObject:[UnipayApi class] forKey:[UnipayApi identity]];
# endif
    
    classes = dict;
    
    return self;
}

- (void)dealloc {
    zero_release(classes);
    
    [super dealloc];
}

+ (PayCenter*)getInstance {
    NNT *wsiobj = [NNT shared];
    @synchronized(wsiobj) {
        if (__gs_paycenter == nil) {
            __gs_paycenter = [[PayCenter alloc] init];
            [wsiobj storeSet:@"static::paycenter" obj:__gs_paycenter];
            if (1 != [__gs_paycenter retainCount])
                [__gs_paycenter release];
        }
    }
    return __gs_paycenter;
}

- (BOOL)send:(NSString*)api data:(id)data {
    BOOL suc = NO;
    for (NSString* key in classes) {
        if ((suc = [key isEqualToString:api])) {
            PayNullApi *obj = [[[classes objectForKey:key] alloc] init];
            suc = [obj send:data];
            [obj release];            
            break;
        }
    }
    return suc;
}

- (BOOL)send:(NSString *)api data:(id)data handle:(id *)handle {
    BOOL suc = NO;
    for (NSString* key in classes) {
        if ((suc = [key isEqualToString:api])) {
            PayNullApi *obj = [[[[classes objectForKey:key] alloc] init] autorelease];
            suc = [obj send:data];
            *handle = obj;
            break;
        }
    }
    return suc;
}

@end

NNT_END_OBJC