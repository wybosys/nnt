
# import "Core.h"
# import "Server.h"
# import "Model.h"
# import "AbstractCache.h"
# import "IRpc.h"
# import "HttpRequest.h"

NNT_USINGCXXNAMESPACE;

NNT_BEGIN_OBJC

@interface Model (Server)

- (void)srvActiveVerbose;
- (void)srvActiveVerboseSuccess;
- (void)srvBeginWaiting;
- (void)srvEndWaiting;

- (void)srvActiveVerboseInThread;
- (void)srvActiveVerboseSuccessInThread;

@end

@implementation Model (Server)

- (void)srvActiveVerbose {
    if (self.verbose)
        [self activeVerbose];
}

- (void)srvActiveVerboseSuccess {
    if (self.verboseSuc)
        [self activeVerbose];
}

- (void)srvBeginWaiting {
    if (self.verboseWait)
        [self performSelectorOnMainThread:@selector(beginWaiting) withObject:nil waitUntilDone:YES];
}

- (void)srvEndWaiting {
    if (self.verboseWait)
        [self performSelectorOnMainThread:@selector(endWaiting) withObject:nil waitUntilDone:YES];
}

- (void)srvActiveVerboseInThread {
    if (self.verbose)
        [self performSelectorOnMainThread:@selector(activeVerbose) withObject:nil waitUntilDone:YES];
}

- (void)srvActiveVerboseSuccessInThread {
    if (self.verboseSuc)
        [self performSelectorOnMainThread:@selector(activeVerbose) withObject:nil waitUntilDone:YES];
}

@end

@interface CxxModelWrapper : NSObject {
    ns::IModel* _model;
}

@property (nonatomic, assign) ns::IModel* model;

@end

@implementation CxxModelWrapper

@synthesize model = _model;

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    safe_drop(_model);
    [super dealloc];
}

- (void)setModel:(ns::IModel*)mdl {
    safe_drop(_model);
    _model = mdl;
    safe_grab(_model);
}

@end

@implementation ServerCallbackObject

@synthesize objc_action = _objc_action;
@synthesize objc_target = _objc_target;
@synthesize sta_func = _sta_func;
@synthesize cxxmdl_func = _cxxmdl_func;
@synthesize cxxmdls_func = _cxxmdls_func;
@synthesize cxx_func = _cxx_func;
@synthesize cxx_target = _cxx_target;
@synthesize callbackType = _callbackType;

- (id)init {
    self = [super init];
    
    _callbackType = ServerCallbackTypeDefault;
    
    return self;
}

- (id)initWithAction:(SEL)act target:(id)target {
    self = [self init];
    
    self.objc_action = act;
    self.objc_target = target;
    
    return self;
}

- (id)initWithFunction:(func_server_callback)func {
    self = [self init];
    
    self.sta_func = func;
    
    return self;
}

- (id)initWithCxxAction:(func_server_objcallback)action target:(Object*)target {
    self = [self init];
    
    self.cxx_func = action;
    self.cxx_target = target;
    
    return self;
}

- (id)initWithCxxMdlAction:(func_server_modelcallback)action target:(Object*)target {
    self = [self init];
    
    self.cxxmdl_func = action;
    self.cxx_target = target;
    
    return self;
}

- (id)initWithCxxMdlsAction:(func_server_modelscallback)action target:(Object*)target {
    self = [self init];
    
    self.cxxmdls_func = action;
    self.cxx_target = target;
    
    return self;
}

- (void)dealloc {
    zero_release(_objc_target);
    
    [super dealloc];
}

- (void)call_static:(id) obj {
    (*_sta_func)(obj);
}

- (void)call_objcb:(id) obj {
    (_cxx_target->*_cxx_func)(obj);
}

- (void)call_mdlcb:(CxxModelWrapper*)mdl {
    (_cxx_target->*_cxxmdl_func)(mdl.model);
}

- (void)call_mdlscb:(NSArray*)mdls {
    core::vector<ns::IModel* > models;
    for (CxxModelWrapper* each in mdls) {
        models.push_back(each.model);
    }
    (_cxx_target->*_cxxmdls_func)(models);
}

- (void)backgroundCall:(id)obj {
    if (_objc_target && _objc_action) {
        [_objc_target performSelectorInBackground:_objc_action withObject:obj];
    } else if (_sta_func) {
        [self performSelectorInBackground:@selector(call_static:) withObject:obj];
    } else if (_cxx_func && _cxx_target) {
        [self performSelectorInBackground:@selector(call_objcb:) withObject:obj];
    } else if (_cxxmdl_func && _cxx_target) {
        [self performSelectorInBackground:@selector(call_mdlcb:) withObject:obj];
    } else if (_cxxmdls_func && _cxx_target) {
        [self performSelectorInBackground:@selector(call_mdlscb:) withObject:obj];
    }
}

- (void)threadCall:(id)obj {
    if (_objc_target && _objc_action) {
        [_objc_target performSelector:_objc_action withObject:obj];
    } else if (_sta_func) {
        [self performSelector:@selector(call_static:) withObject:obj];
    } else if (_cxx_func && _cxx_target) {
        [self performSelector:@selector(call_objcb:) withObject:obj];
    } else if (_cxxmdl_func && _cxx_target) {
        [self performSelector:@selector(call_mdlcb:) withObject:obj];
    } else if (_cxxmdls_func && _cxx_target) {
        [self performSelector:@selector(call_mdlscb:) withObject:obj];
    }
}

- (void)mainthreadCall:(id)obj {
    if (_objc_target && _objc_action) {
        [_objc_target performSelectorOnMainThread:_objc_action withObject:obj waitUntilDone:YES];
    } else if (_sta_func) {
        [self performSelectorOnMainThread:@selector(call_static:) withObject:obj waitUntilDone:YES];
    } else if (_cxx_func && _cxx_target) {
        [self performSelectorOnMainThread:@selector(call_objcb:) withObject:obj waitUntilDone:YES];
    } else if (_cxxmdl_func && _cxx_target) {
        [self performSelectorOnMainThread:@selector(call_mdlcb:) withObject:obj waitUntilDone:YES];
    } else if (_cxxmdls_func && _cxx_target) {
        [self performSelectorOnMainThread:@selector(call_mdlscb:) withObject:obj waitUntilDone:YES];
    }
}

- (void)call:(id)obj {
    switch (_callbackType) {
        case ServerCallbackTypeThread: {
            [self threadCall:obj];
        } break;
        case ServerCallbackTypeMainThread: {
            [self mainthreadCall:obj];
        } break;
        case ServerCallbackTypeBackgroundThread: {
            [self backgroundCall:obj];
        } break;
    }
}

@end

NNTDECL_PRIVATE_BEGIN(Server, NSObject)

NNTDECL_PRIVATE_IMPL(Server)

- (id)init {
	self = [super init];
	return self;
}

- (void)dealloc {
	[super dealloc];
}

NNTDECL_PRIVATE_END

@implementation Server

@synthesize ctx = _ctx;
@synthesize GlobalCache = _GlobalCache;
@synthesize classRpc = _classRpc;

- (id)init {
	self = [super init];
    NNTDECL_PRIVATE_INIT(Server);
    
    _GlobalCache = YES;
    _classRpc = [HttpRequest class];
    
	return self;
}

- (void)dealloc {
    NNTDECL_PRIVATE_DEALLOC();
	[super dealloc];
}

- (BOOL)retrieve_model:(Model*)model
{
    autocollect;
    
    // check ava.
    NSURL *url = [model get_url];
    Class cls_rpc = model.classRpc ? model.classRpc : self.classRpc;  
    if (url == nil ||
        cls_rpc == nil) {
        dthrow_msg(@"Server", @"URL or ClassRpc is NULL.");
        return NO;
    }
    
    // begin waiting.
    [model srvBeginWaiting];
    	          
    id result = nil;
    
    // load cache.
    AbstractCache *cache = nil;
    NSString *cacheKey = nil;
    if (model.cacheable) {
        cache = [AbstractCache defaultCache];
        cacheKey = [model uniqueIdentifier];
        if (cacheKey && cache && _GlobalCache) {
            result = [cache objectForKey:cacheKey];
            if ([result isKindOfClass:[NSNull class]])
                result = nil;
        }
    }
    
    if (model.cacheUpdate)
        result = nil;
    
    if (result == nil) {
        
        NNTObject<IRpc>* irpc = [[cls_rpc alloc] init];
        result = [irpc call:model withUrl:url];
        
        if (result && cacheKey && cache && _GlobalCache) {
            CacheItem *item = [cache setObject:result key:cacheKey];
            if (model.cacheTime == 0) {
                [item infinate];
            } else {
                item.overdate = item.timestamp + model.cacheTime;
            }
        }
        
        zero_release(irpc);
    }       
    
    BOOL ret = NO;
    
	if (result == nil) {
        [model srvActiveVerbose];
    } else {
        [model srvActiveVerboseSuccess];
     
        // process result.
        ret = [model process:result];
        
        if (!ret) {
            [model srvActiveVerbose];
        } else {
            [model srvActiveVerboseSuccess];
        }
    }

    // end wait.
    [model srvEndWaiting];
    
    return ret;
}

- (BOOL)retrieve_model:(Model *)model 
             cachename:(NSString *)cachename 
             cachetime:(NSUInteger)cachetime
{
    autocollect;
    
    // check ava.
    Class cls_rpc = model.classRpc ? model.classRpc : self.classRpc;
    if (cls_rpc == nil) {
        dthrow_msg(@"NULL", @"class for RPC is NULL.");
        return NO;
    }
    
    // begin wait.
    [model srvBeginWaiting];
    
    // find in cache.
    id result = nil;
    AbstractCache* cache = nil;
    if (model.cacheable) {
        cache = [AbstractCache defaultCache];
        result = [cache objectForKey:cachename];
        if ([result isKindOfClass:[NSNull class]])
            result = nil;
    }
        
    if (result == nil) {
        // get from url.
        NSURL *url = [model get_url];
        
        // alloc rpc.
        NNTObject<IRpc>* irpc = [[cls_rpc alloc] init];
        
        // get result.
        result = [irpc call:model withUrl:url];
        
        // save.
        if (cache) {
            CacheItem *item = [cache setObject:result key:cachename];
            item.overdate = item.timestamp + cachetime;
        }
        
        zero_release(irpc);
    }    
    
    BOOL ret = NO;
	if (result == nil) {
        [model srvActiveVerbose];
    } else {
        [model srvActiveVerboseSuccess];
        
        // process callback.
        ret = [model process:result];
        
        if (!ret) {
            [model srvActiveVerbose];
        } else {
            [model srvActiveVerboseSuccess];
        }        
    }
    
    // stop ending.
    [model srvEndWaiting];
    
    return ret;
}

- (BOOL)retrieve_cxxmodel:(ns::IModel*)cxxmodel {
    autocollect;
    
    Model* model = cxxmodel->nsmodel();
    
    // check ava.
	NSURL *url = [model get_url];
    Class cls_rpc = model.classRpc ? model.classRpc : self.classRpc;            
    if (url == nil || 
        cls_rpc == nil) {
        dthrow_msg(@"NULL", @"URL or ClassRpc is NULL.");
        return NO;
    }
    
    // begin wait.
    [model srvBeginWaiting];
    
    id result = nil;
        
    // find in cache.
    AbstractCache* cache = nil;
    NSString* cacheKey = nil;
    if (model.cacheable) {
        cache = [AbstractCache defaultCache];
        cacheKey = [model uniqueIdentifier];
        if (cacheKey && cache && _GlobalCache) {
            result = [cache objectForKey:cacheKey];
            if ([result isKindOfClass:[NSNull class]])
                result = nil;
        }
        if (model.cacheUpdate)
            result = nil;
    }
    
    if (result == nil) {
        
        NNTObject<IRpc>* irpc = [[cls_rpc alloc] init];
        result = [irpc call:model withUrl:url];

        if (result && cache && cacheKey && _GlobalCache) {
            CacheItem *item = [cache setObject:result key:cacheKey];
            if (model.cacheTime == 0) {
                [item infinate];
            } else {
                item.overdate = item.timestamp + model.cacheTime;
            }
        }
        
        zero_release(irpc);
    }       
    
    BOOL ret = NO;
    
	if (result == nil) {
        [model srvActiveVerbose];
    } else {
        [model srvActiveVerboseSuccess];
        
        // process result.
        ret = [model process:result];
        
        if (!ret) {
            [model srvActiveVerbose];
        } else {
            [model srvActiveVerboseSuccess];
        }
    }
    
    [model srvEndWaiting];
    
    return ret;
}

- (void)retrieve_model_async:(Model *)model {
    [self retrieve_model_async:model 
                      selector:@selector(act_none:) 
                        object:self];
}

- (void)retrieve_model_async:(Model*)model
                callbackType:(ServerCallbackType)callbackType {
    [self retrieve_model_async:model
                      selector:@selector(act_none:)
                        object:self
                  callbackType:callbackType];
}


- (void)retrieve_models_async:(NSArray *)models {
    [self retrieve_models_async:models 
                       selector:@selector(act_none:) 
                         object:self];
}

- (void)retrieve_model_async:(Model *)model selector:(SEL)sel object:(NSObject *)obj { 
    [self retrieve_model_async:model 
                      selector:sel
                        object:obj
                  callbackType:ServerCallbackTypeDefault];
}

- (void)retrieve_model_async:(Model*)model 
                    selector:(SEL)sel 
                      object:(NSObject*)obj 
                callbackType:(ServerCallbackType)callbackType
{

    if (obj == nil) {
# ifdef NNT_DEBUG
        @throw [NSException exceptionWithName:@"server" reason:@"object is nil" userInfo:nil];
# endif
        return;
    }
        
    // send model.
    ServerCallbackObject *callback = [[ServerCallbackObject alloc] initWithAction:sel target:obj];
    callback.callbackType = callbackType;
    NSArray *arr = [[NSArray alloc] initWithObjects:model, callback, nil];
    [callback release];    
    
    // fetch data from server.
    [self performSelectorInBackground:@selector(_thd_retrieve_model:) withObject:arr];                
    
    // clean.
    [arr release];
}

- (void)retrieve_models_async:(NSArray *)models 
                     selector:(SEL)sel 
                       object:(NSObject *)obj
{
    // do
    [self retrieve_models_async:models 
                       selector:sel 
                         object:obj 
                   callbackType:ServerCallbackTypeDefault];
}

- (void)retrieve_models_async:(NSArray *)models 
                     selector:(SEL)sel 
                       object:(NSObject *)obj 
                 callbackType:(ServerCallbackType)callbackType
{
    
    if (obj == nil) {
# ifdef NNT_DEBUG
        @throw [NSException exceptionWithName:@"server" reason:@"object is nil" userInfo:nil];
# endif
        return;
    }
    
    // send model.
    ServerCallbackObject *callback = [[ServerCallbackObject alloc] initWithAction:sel target:obj];
    callback.callbackType = callbackType;
    NSArray *arr = [[NSArray alloc] initWithObjects:models, callback, nil];
    [callback release];
    
    // fetch data.
    [self performSelectorInBackground:@selector(_thd_retrieve_models:) withObject:arr];   
    
    // clean.
    [arr release];
}

- (void)retrieve_cxxmodels_async:(core::vector<ns::IModel*> const&)model
                          action:(func_server_modelscallback)func
                          target:(Object*)target
{
    // do.
    [self retrieve_cxxmodels_async:model
                            action:func
                            target:target
                      callbackType:ServerCallbackTypeDefault];
}

- (void)retrieve_cxxmodels_async:(core::vector<ns::IModel*> const&)model
                          action:(func_server_modelscallback)func
                          target:(Object*)target
                    callbackType:(ServerCallbackType)callbackType
{
    ns::MutableArray models;
    for (uint i = 0; i < model.size(); ++i) {
        CxxModelWrapper* wrapper = [[CxxModelWrapper alloc] init];
        wrapper.model = model[i];
        models.add(wrapper);
        safe_release(wrapper);
    }
    
    // send model.
    ServerCallbackObject *callback = [[ServerCallbackObject alloc] initWithCxxMdlsAction:func target:target];
    callback.callbackType = callbackType;
    NSArray *arr = [[NSArray alloc] initWithObjects:models, callback, nil];
    [callback release];
    
    // fetch data.
    [self performSelectorInBackground:@selector(_thd_retrieve_models:) withObject:arr];   
    
    // clean.
    [arr release];
}

- (void)retrieve_model_async:(Model*)model 
                    selector:(SEL)sel 
                      object:(NSObject*)obj 
                   fselector:(SEL)fsel 
                     fobject:(NSObject*)fobj
{
    
    // do.
    [self retrieve_model_async:model 
                      selector:sel 
                        object:obj 
                     fselector:fsel 
                       fobject:fobj 
                  callbackType:ServerCallbackTypeDefault];
}

- (void)retrieve_model_async:(Model*)model
                    selector:(SEL)sel 
                      object:(NSObject*)obj 
                   fselector:(SEL)fsel 
                     fobject:(NSObject*)fobj 
                callbackType:(ServerCallbackType)callbackType
{
    
    // check obj is nil.
    if (obj == nil) {
# ifdef NNT_DEBUG
        @throw [NSException exceptionWithName:@"server" reason:@"object is nil" userInfo:nil];
# endif
        return;
    }
    
    // send model.
    ServerCallbackObject *callback = [[ServerCallbackObject alloc] initWithAction:sel target:obj];
    ServerCallbackObject *fcallback = [[ServerCallbackObject alloc] initWithAction:fsel target:fobj];
    callback.callbackType = callbackType;
    fcallback.callbackType = callbackType;
    NSArray *arr = [[NSArray alloc] initWithObjects:model, callback, fcallback, nil];
    [callback release];
    [fcallback release];
    
    // fetch data.
    [self performSelectorInBackground:@selector(_thd_retrieve_model:) withObject:arr];                
    
    // clean.
    [arr release];
}

- (void)retrieve_model_async:(Model*)model 
                        func:(func_server_callback)func
{
    // do.
    [self retrieve_model_async:model
                          func:func
                  callbackType:ServerCallbackTypeDefault];
}

- (void)retrieve_model_async:(Model*)model 
                        func:(func_server_callback)func 
                callbackType:(ServerCallbackType)callbackType
{
    
    if (func == nil) {
# ifdef NNT_DEBUG
        @throw [NSException exceptionWithName:@"server" reason:@"callback function is nil" userInfo:nil];
# endif
        return;
    }
        
    // send model.
    ServerCallbackObject *callback = [[ServerCallbackObject alloc] initWithFunction:func];
    callback.callbackType = callbackType;
    NSArray *arr = [[NSArray alloc] initWithObjects:model, callback, nil];
    [callback release];
    
    // fetch data.
    [self performSelectorInBackground:@selector(_thd_retrieve_model:) withObject:arr];         
    
    // clean.
    [arr release];
}

- (void)retrieve_model_async:(Model*)model 
                        func:(func_server_callback)func 
                      failed:(func_server_callback)failed
{
    // do.
    [self retrieve_model_async:model
                          func:func
                        failed:failed
                  callbackType:ServerCallbackTypeDefault];
}

- (void)retrieve_model_async:(Model*)model 
                        func:(func_server_callback)func 
                      failed:(func_server_callback)failed 
                callbackType:(ServerCallbackType)callbackType
{
    
    if (func == nil) {
# ifdef NNT_DEBUG
        @throw [NSException exceptionWithName:@"server" reason:@"callback func is nil" userInfo:nil];
# endif
        return;
    }
    
    // send model.
    ServerCallbackObject *callback = [[ServerCallbackObject alloc] initWithFunction:func];
    ServerCallbackObject *fcallback = [[ServerCallbackObject alloc] initWithFunction:failed];
    callback.callbackType = callbackType;
    fcallback.callbackType = callbackType;
    NSArray *arr = [[NSArray alloc] initWithObjects:model, callback, fcallback, nil];
    [callback release];
    [fcallback release];
    
    // fetch data.
    [self performSelectorInBackground:@selector(_thd_retrieve_model:) withObject:arr];        
    
    // clean.
    [arr release];
}

- (void)retrieve_model_async:(Model*)model 
                      action:(func_server_objcallback)func
                      target:(Object*)target
{
    // do.
    [self retrieve_model_async:model
                        action:func
                        target:target
                  callbackType:ServerCallbackTypeDefault];
}

- (void)retrieve_model_async:(Model*)model 
                      action:(func_server_objcallback)func
                      target:(Object*)target
                callbackType:(ServerCallbackType)callbackType
{
    
    if (func == nil) {
# ifdef NNT_DEBUG
        @throw [NSException exceptionWithName:@"server" reason:@"callback function is nil" userInfo:nil];
# endif
        return;
    }
    
    // send model.
    ServerCallbackObject *callback = [[ServerCallbackObject alloc] initWithCxxAction:func target:target];
    callback.callbackType = callbackType;
    NSArray *arr = [[NSArray alloc] initWithObjects:model, callback, nil];
    [callback release];
    
    // fetch data.
    [self performSelectorInBackground:@selector(_thd_retrieve_model:) withObject:arr];         
    
    // clean.
    [arr release];
}

- (void)retrieve_cxxmodel_async:(ns::IModel*)model
                         action:(func_server_modelcallback)func
                         target:(Object*)target
{
    
    // do.
    [self retrieve_cxxmodel_async:model
                           action:func
                           target:target
                     callbackType:ServerCallbackTypeDefault];
}

- (void)retrieve_cxxmodel_async:(ns::IModel*)model
                         action:(func_server_modelcallback)func
                         target:(Object*)target
                   callbackType:(ServerCallbackType)callbackType
{
    
    if (func == nil) {
# ifdef NNT_DEBUG
        @throw [NSException exceptionWithName:@"server" reason:@"callback function is nil" userInfo:nil];
# endif
        return;
    }
    
    CxxModelWrapper* wrapper = [[CxxModelWrapper alloc] init];
    wrapper.model = model;
    
    // send model.
    ServerCallbackObject *callback = [[ServerCallbackObject alloc] initWithCxxMdlAction:func 
                                                                                 target:target];
    callback.callbackType = callbackType;
    NSArray *arr = [[NSArray alloc] initWithObjects:wrapper, callback, nil];
    [callback release];
    
    // fetch data.
    [self performSelectorInBackground:@selector(_thd_retrieve_model:) withObject:arr];         
    
    // clean.
    safe_release(wrapper);
    [arr release];
}

- (void)retrieve_model_async:(Model *)model 
                    selector:(SEL)sel 
                      object:(NSObject *)obj 
                   cachename:(NSString*)cachename 
                   cachetime:(NSUInteger)cachetime
{
    
    if (obj == nil) {
# ifdef NNT_DEBUG
        @throw [NSException exceptionWithName:@"server" reason:@"object is nil" userInfo:nil];
# endif
        return;
    }        
    
    AbstractCache* cache = [AbstractCache defaultCache];
    if (cache == nil) {
        [self retrieve_model_async:model selector:sel object:obj];
        return;
    }
    
    // begin.
    [model beginWaiting];
    
    // from cache.
    id result = [cache objectForKey:cachename];
    if ([result isKindOfClass:[NSNull class]])
        result = nil;
    
    if (model.cacheUpdate)
        result = nil;
    if (result == nil) {
        
        ServerCallbackObject *callback = [[ServerCallbackObject alloc] initWithAction:sel target:obj];
        NSArray *arr = [[NSArray alloc] initWithObjects:model, callback, cachename, [NSNumber numberWithUnsignedInteger:cachetime], nil];
        [callback release];
        
        [self performSelectorInBackground:@selector(_thd_retrieve_model_with_cache:) withObject:arr];
        
        [arr release];
        return;
    }
    
    // send model.
    ServerCallbackObject *callback = [[ServerCallbackObject alloc] initWithAction:sel target:obj];
    NSArray *arr = [[NSArray alloc] initWithObjects:model, callback, result, nil];
    [callback release];
        
    [self performSelectorInBackground:@selector(_thd_process_result:) withObject:arr];
    
    // clean
    [arr release];
}

- (void)retrieve_model_async:(Model *)model 
                    selector:(SEL)sel 
                      object:(NSObject *)obj 
                   fselector:(SEL)fsel 
                     fobject:(NSObject*)fobj 
                   cachename:(NSString*)cachename 
                   cachetime:(NSUInteger)cachetime
{
    
    if (obj == nil) {
# ifdef NNT_DEBUG
        @throw [NSException exceptionWithName:@"server" reason:@"object is nil" userInfo:nil];
# endif
        return;
    }        
        
    AbstractCache *cache = [AbstractCache defaultCache];
    if (cache == nil) {
        [self retrieve_model_async:model selector:sel object:obj];
        return;
    }
    
    // begin.
    [model srvBeginWaiting];
    
    // from cache.
    id result = [cache objectForKey:cachename];
    if ([result isKindOfClass:[NSNull class]])
        result = nil;
    
    if (model.cacheUpdate)
        result = nil;
    if (result == nil) {
        
        ServerCallbackObject *callback = [[ServerCallbackObject alloc] initWithAction:sel target:obj];
        ServerCallbackObject *fcallback = [[ServerCallbackObject alloc] initWithAction:fsel target:fobj];
        NSArray *arr = [[NSArray alloc] initWithObjects:model, callback, cachename, [NSNumber numberWithUnsignedInteger:cachetime], fcallback, nil];
        [callback release];
        [fcallback release];
        
        [self performSelectorInBackground:@selector(_thd_retrieve_model_with_cache:) withObject:arr];
        
        // clean.
        [arr release];
        return;
    }
    
    ServerCallbackObject *callback = [[ServerCallbackObject alloc] initWithAction:sel target:obj];
    ServerCallbackObject *fcallback = [[ServerCallbackObject alloc] initWithAction:fsel target:fobj];
    NSArray *arr = [[NSArray alloc] initWithObjects:model, callback, fcallback, result, nil];
    [callback release];
    [fcallback release];
    
    [self performSelectorInBackground:@selector(_thd_process_result:) withObject:arr];
    
    // clean.
    [arr release];
}

- (void)_thd_retrieve_model:(NSArray*)params
{
    autocollect;

    // get model.
    Model *model = [params objectAtIndex:0];
    if ([model isKindOfClass:[CxxModelWrapper class]]) {
        CxxModelWrapper* wrapper = (CxxModelWrapper*)model;
        model = (Model*)wrapper.model->nsmodel();
    }
    
    NSURL* url = [model get_url];
    Class cls_rpc = model.classRpc ? model.classRpc : self.classRpc;    
    if (url == nil || 
        cls_rpc == nil) {
        dthrow_msg(@"NULL", @"URL or ClassRpc is NULL.");
        return;
    }
    
    // begin.
    [model srvBeginWaiting];
    
    ServerCallbackObject *callback = (ServerCallbackObject*)[params objectAtIndex:1];
    if (model.demo) {
        // cb.
        [callback call:model];
        
        // end.
        [model srvEndWaiting];
        return;
    }
    
    id result = nil;
    AbstractCache* cache = nil;
    NSString* cacheKey = nil;
    
    // find in cache.
    if (model.cacheable) {
        cache = [AbstractCache defaultCache];
        cacheKey = [model uniqueIdentifier];
        if (cache && cacheKey && _GlobalCache) {
            result = [cache objectForKey:cacheKey];
            if ([result isKindOfClass:[NSNull class]])
                result = nil;
        }
    
        if (model.cacheUpdate)
            result = nil;
    }
    
    // get model.
    if (result == nil) {
        
        NNTObject<IRpc>* irpc = [[cls_rpc alloc] init];
        result = [irpc call:model withUrl:url];
        
        if (result && cache && cacheKey && _GlobalCache) {
            CacheItem *item = [cache setObject:result key:cacheKey];
            if (item) {
                if (model.cacheTime == 0) {
                    [item infinate];
                } else {
                    item.overdate = item.timestamp + model.cacheTime;
                }
            }
        }
        
        zero_release(irpc);
    }
    
    BOOL suc = NO;
    
    if (result)
        suc = [model process:result];

    if (suc) {
        // callback, successful
        [callback call:model];
        
        // messge
        [model srvActiveVerboseSuccessInThread];
        
    } else {
        // error
        if ([params count] > 2) {
            ServerCallbackObject* fcallback = (ServerCallbackObject*)[params objectAtIndex:2];
            
            [fcallback call:model];
        }
        
        // message
        [model srvActiveVerboseInThread];
    }
    
    [model srvEndWaiting];
}

- (void)_thd_retrieve_model_with_cache:(NSArray*)params
{
    autocollect;
    
    Model *model = [params objectAtIndex:0];   
    
    // check ava.
    NSURL *url = [model get_url];
    Class cls_rpc = model.classRpc ? model.classRpc : self.classRpc;
    if (url == nil || 
        cls_rpc == nil) {
        dthrow_msg(@"NULL", @"URL or ClassRpc is NULL.");
        return;
    }
    
    // begin.
    [model srvBeginWaiting];
    
    // get param.
    ServerCallbackObject* callback = (ServerCallbackObject*)[params objectAtIndex:1];
    NSString *cachename = [params objectAtIndex:2];
    NSNumber *cachetime = [params objectAtIndex:3];
    
    // get data.
    NNTObject<IRpc>* irpc = [[cls_rpc alloc] init];
    id result = [irpc call:model withUrl:url];    
    zero_release(irpc);
    
    // in cache.
    if (model.cacheable) {
        AbstractCache *cache = [AbstractCache defaultCache];
        if (cache) {
            CacheItem *item = [cache setObject:result key:cachename];
            item.overdate = item.timestamp + [cachetime intValue];
        }
    }
    
    // process.
    BOOL suc = NO;
    
    if (result)
        suc = [model process:result];
    
    if (suc) {
        // callback, successful
        [callback call:model];
        
        // verbose
        [model srvActiveVerboseSuccessInThread];
    } else {
        // failed
        if ([params count] > 4) {
            ServerCallbackObject* fcallback = (ServerCallbackObject*)[params objectAtIndex:4];
            
            [fcallback call:model];
        }
        
        [model srvActiveVerboseInThread];
    }
    
    [model srvEndWaiting];
}

- (void)_thd_process_result:(NSArray*)params
{
    autocollect;
    
    Model *model = [params objectAtIndex:0];
    ServerCallbackObject* callback = (ServerCallbackObject*)[params objectAtIndex:1];
    ServerCallbackObject* fcallback = (ServerCallbackObject*)[params objectAtIndex:2];
    id result = [params objectAtIndex:3];

    BOOL suc = NO;
    
    if (result)
        suc = [model process:result];
    
    if (suc) {
        // callback
        [callback call:model];
        
        // message
        [model srvActiveVerboseSuccessInThread];
    } else {
        [fcallback call:model];
        
        // message
        [model srvActiveVerboseInThread];
    }
    
    [model srvEndWaiting];
}

- (void)act_none:(id)obj
{
    PASS;
}

- (void)_thd_retrieve_models:(NSArray*)params
{
    autocollect;
    
    NSArray *models = [params objectAtIndex:0];
    ServerCallbackObject* callback = (ServerCallbackObject*)[params objectAtIndex:1];
    
    BOOL suc = NO;
    for (id each in models) {
        Model* model = each;
        if ([each isKindOfClass:[CxxModelWrapper class]]) {
            CxxModelWrapper* wrapper = (CxxModelWrapper*)model;
            model = (Model*)wrapper.model->nsmodel();
        }
        
        // check ava.
        NSURL* url = [model get_url];
        Class cls_rpc = model.classRpc ? model.classRpc : self.classRpc;
        if (url == nil || 
            cls_rpc == nil) {
            dthrow_msg(@"NULL", @"URL or ClassRpc is NULL.");
            continue;
        }
        
        // begin.
        [model beginWaiting];          
        
        id result = nil;
        AbstractCache* cache = nil;
        NSString* cacheKey = nil;
        
        // find in cache.
        if (model.cacheable) {
            cache = [AbstractCache defaultCache];
            cacheKey = [model uniqueIdentifier];
            if (cache && cacheKey && _GlobalCache) {
                result = [cache objectForKey:cacheKey];
                if ([result isKindOfClass:[NSNull class]])
                    result = nil;
            }
        
            if (model.cacheUpdate)
                result = nil;
        }
        
        if (result == nil) {
            
            NNTObject<IRpc>* irpc = [[cls_rpc alloc] init];
            result = [irpc call:model withUrl:url];
            
            if (result && cache && cacheKey && _GlobalCache) {
                CacheItem *item = [cache setObject:result key:cacheKey];
                if (model.cacheTime == 0) {
                    [item infinate];
                } else {
                    item.overdate = item.timestamp + model.cacheTime;
                }
            }
            
            zero_release(irpc);
        }
               
        suc = NO;
        
        if (result)
            suc = [model process:result];
        
        if (suc) {            
            // messge
            [model srvActiveVerboseSuccessInThread];
        } else {
            // error
            if ([params count] > 3) {
                SEL fsel = [[params objectAtIndex:3] selector];
                NSObject *fobj = [params objectAtIndex:4];                
                [fobj performSelector:fsel withObject:model];
            }
            
            // message
            [model srvActiveVerboseInThread];
        }
        
        [model srvEndWaiting];
        
        if (suc == NO)
            break;
    }               
    
    if (suc) {
        // callback, successful
        [callback threadCall:models];
    } else {
        if ([params count] > 2) {
            ServerCallbackObject* fcallback = (ServerCallbackObject*)[params objectAtIndex:2];
            [fcallback threadCall:models];
        }
    }
}

@end

NNT_END_OBJC
