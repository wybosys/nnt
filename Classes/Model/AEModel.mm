
# import "Core.h"
# import "AEModel.h"
# import "HttpRequest.h"
# import "JsonObjParser.h"

NNT_BEGIN_OBJC

NNT_USINGCXXNAMESPACE;

@interface AppEngineModel ()

@property (nonatomic, copy) NSString* errmsg;

@end

@implementation AppEngineModel

@synthesize appid = _appid, odd = _odd, errmsg = _errmsg;

- (id)init {
    self = [super init];
    
    self.classRpc = [HttpRequest_Get class];
    self.verbose = YES;
    self.verboseWait = YES;
    
    JsonObjParser* parser = [[JsonObjParser alloc] init];
    self.objparser = parser;
    [parser release];
    
    self.url = @"http://libwsi.hp.af.cm";
    //self.url = @"http://localhost:8000";
    
    self.appid = @"toolkit";
    
    return self;
}

- (void)dealloc {
    safe_release(_appid);
    safe_release(_odd);
    safe_release(_errmsg);
    [super dealloc];
}

- (NSString*)url {
    ns::String ret = _url;
    ret += @"/api?";
        
    ns::MutableArray params = self.get_params;
    
    params.add(pair(@"appid", self.appid));
    params.add(pair(@"method", self.method));
    params.add(pair(@"sign", @"test"));
    
    if (self.odd)
        params.add(pair(@"odd", self.odd));
    
    for (uint i = 0; i < params.count();) {
        ns::Pair p = (id)params[i];
        
        ret += ns::String::As(p.first());
        ret += @"=";
        ret += ns::String::As(p.second());
        
        if (++i != params.count())
            ret += @"&";
    }
    
    return ret.consign();
}

- (BOOL)process:(id)result {
    ns::Dictionary res(result);
    ns::Number code = res[@"code"];
    if (code < 0) {
        ulong errcode = -(long)code;
        ns::String msg;
        if (MASK_CHECK(AEEC_LOST, errcode))
        {
            msg = @"LOST";
        }
        else if (MASK_CHECK(AEEC_OVERFLOW, errcode))
        {
            msg = @"OVERFLOW";
        }
        else if (MASK_CHECK(AEEC_INVALID, errcode))
        {
            msg = @"INVALID";
        }
        else if (MASK_CHECK(AEEC_DUPLICATE, errcode))
        {
            msg = @"DUPLICATE";
        }
        
        if (MASK_CHECK(AEEC_NOMETHOD, errcode))
            msg += @" METHOD";
        if (MASK_CHECK(AEEC_ARGUMENT, errcode))
            msg += @" ARGUMENT";
        if (MASK_CHECK(AEEC_PERMISSION, errcode))
            msg += @" PERMISSION";
        if (MASK_CHECK(AEEC_HANDLE, errcode))
            msg += @" HANDLE";
        if (MASK_CHECK(AEEC_TIMEOUT, errcode))
            msg += @" TIMEOUT";
        if (MASK_CHECK(AEEC_SIGN, errcode))
            msg += @" SIGNATURE";
        if (msg.is_empty())
            msg = @"UNCATEGORY FAILURE";
        msg += @".";
        self.errmsg = msg;
        return NO;
    }
    
    // callback to success.
    id obj = res[@"result"];
    if (ns::null == obj)
        obj = nil;
    [self success:obj];
    
    return YES;
}

- (void)activeVerbose {
    [Msgbox fatal:self.errmsg];
}

- (void)success:(id)obj {
    PASS;
}

- (void)beginWaiting {
    [[UIWaitingOverlap shared] show];
}

- (void)endWaiting {
    [[UIWaitingOverlap shared] hide];
}

@end

NNTCONVERTOR_MODEL_IMPL_BEGIN(AppEngineModel)

- (NSMutableArray*)get_params {
    ns::MutableArray arr = [super get_params];
    ae::model::IAppEngine* ae = (ae::model::IAppEngine*)model;
    ae->params(arr);
    return arr;
}

- (void)success:(id)obj {
    ae::model::IAppEngine* ae = (ae::model::IAppEngine*)model;
    ae->success(obj);
}

NNTCONVERTOR_MODEL_IMPL_END

NNT_END_OBJC

WAE_MODEL_BEGIN

WAE_MODEL_END
