
# import "Core.h"
# import "Model.h"
# import "Context.h"
# import "Preferences.h"
# import "NullObjParser.h"

NNT_BEGIN_OBJC

@implementation Model

@synthesize url = _url, service = _service, method = _method, params = _params, objparser = _objparser;
@synthesize cacheTime = _cacheTime, cacheUpdate = _cacheUpdate, cacheAppendr = _cacheAppendr, cacheable = _cacheable;
@synthesize verbose = _verbose, verboseSuc = _verboseSuc, verboseWait = _verboseWait, verboseData = _verboseData;
@synthesize memoryUsage = _memoryUsage;
@synthesize classRpc = _classRpc;
@synthesize extendDatas = _extend_datas;
@synthesize demo = _demo;

- (id)init {
	self = [super init];
		
	_params = [[NSMutableArray alloc] init];
    _extend_datas = [[NSMutableArray alloc] init];
    
# ifdef NNT_DEBUG
    _cacheTime = DT_5MIN;
# else
    _cacheTime = DT_15MIN;
# endif
    
    _cacheUpdate = NO;
    _cacheable = YES;
    
    _verbose = NO;
    _verboseSuc = NO;
    _verboseWait = NO;
    _verboseData = NNTDEBUG_EXPRESS(YES) NNTRELEASE_EXPRESS(NO);
    
    _classRpc = nil;
    _demo = NO;
	
	return self;
}

- (void)dealloc {
	zero_release(_url);
	zero_release(_service);
	zero_release(_method);
	zero_release(_params);
    zero_release(_objparser);
    zero_release(_extend_datas);
    zero_release(_cacheAppendr);
    
	[super dealloc];
}

- (BOOL)is_valid:(id)result {
	return NO;
}

- (BOOL)process:(id)result {
	return NO;
}

- (NSMutableArray*)get_params {
    return _params;
}

- (NSMutableArray*)get_params_deep {
    return _params;
}

- (NSMutableArray*)dup_params {
     return [[[NSMutableArray alloc] initWithArray:_params] autorelease];
}

- (NSMutableArray*)get_extend_datas {
    return _extend_datas;
}

- (NSMutableArray*)get_extend_datas_deep {
    return _extend_datas;
}

- (NSMutableArray*)dup_extend_datas {
    return [[[NSMutableArray alloc] initWithArray:_extend_datas] autorelease];
}

- (NSArray*)collect {
    NSMutableArray* ret = [NSMutableArray array];
    
    NSString* str = [[self get_url] absoluteString];
    if (str)
        [ret addObject:str];
    
    str = [self get_service];
    if (str)
        [ret addObject:str];
    
    str = [self get_method];
    if (str)
        [ret addObject:str];
    
    NSArray* arr = [self get_params];
    if (arr)
        [ret addObject:arr];
    
    return ret;
}

- (void)setObjparser:(id<NullObjParser>)objparser {
    [NNTObject refobjSet:&_objparser ref:objparser];

    if ([_objparser isKindOfClass:[NullObjParser class]]) {
        ((NullObjParser*)_objparser).owner = self;
    }
}

- (void)activeVerbose {
    PASS;
}

- (void)beginWaiting {
    PASS;
}

- (void)endWaiting {
    PASS;
}

- (NSURL*)get_url {
    return [NSURL URLWithUTF8String:self.url];
}

- (NSString*)get_method {
    return self.method;
}

- (NSString*)get_service {
    return self.service;
}

- (NSString*)uniqueIdentifier {
    NSArray *arr = [self collect];
    NSString* str_arr = [NNTObject json_encode:arr];
    NSString* ret = [NSString stringWithFormat:@":%@:%@:%@", str_arr, self.url, _cacheAppendr];
    return ret;
}

@end

@implementation __cxxmodel_wrapper

@synthesize model;

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    [super dealloc];
}

- (NSURL*)get_url {
    return ((::wsi::ns::Model*)model)->url().consign();
}

- (NSString*)get_method {
    return ((::wsi::ns::Model*)model)->method().consign();
}

- (NSString*)get_service {
    return ((::wsi::ns::Model*)model)->service().consign();
}

- (NSArray*)get_params {
    return ((::wsi::ns::Model*)model)->params().consign();
}

- (BOOL)process:(NSDictionary *)result {
    id obj = result;
    if ([result isKindOfClass:[NSPointer class]])
        obj = (id)((NSPointer*)result).addr;
	return ((::wsi::ns::Model*)model)->process(obj);
}

- (void)activeVerbose {
    ((::wsi::ns::Model*)model)->active_verbose();
}

- (void)beginWaiting {
    ((::wsi::ns::Model*)model)->begin_waiting();
}

- (void)endWaiting {
    ((::wsi::ns::Model*)model)->end_waiting();
}

@end

NNT_END_OBJC

NNT_BEGIN_CXX
NNT_BEGIN_NS(ns)

void Model::active_verbose() const
{
    PASS;
}

void Model::begin_waiting() const
{
    PASS;
}

void Model::end_waiting() const
{
    PASS;
}

Array Model::params() const
{
    return [this->_self get_params_deep];
}

void Model::set_verbose(uint d)
{
    this->_self.verbose = MASK_CHECK(VERBOSE, d);
    this->_self.verboseWait = MASK_CHECK(VERBOSE_WAIT, d);
    this->_self.verboseSuc = MASK_CHECK(VERBOSE_SUC, d);
}

void Model::set_rpc(Class cls)
{
    this->_self.classRpc = cls;
}

void Model::_set_demo(bool val)
{
    this->_self.demo = val;
}

void Model::set_update(bool val)
{
    this->_self.cacheUpdate = val;
}

URL Model::url() const
{
    return URL(this->_self.url);
}

void Model::set_url(ns::String const& str)
{
    this->_self.url = str;
}

ns::String Model::_url() const
{
    return this->_self.url;
}

void Model::set_method(ns::String const& method)
{
    this->_self.method = method;
}

ns::String Model::method() const
{
    return this->_self.method;
}

void Model::set_service(ns::String const& str)
{
    this->_self.service = str;
}

void Model::set_appendr(const ns::String & str)
{
    this->_self.cacheAppendr = str;
}

ns::String Model::service() const
{
    return this->_self.service;
}

void Model::set_overdate(uint secs)
{
    this->_self.cacheTime = secs;
}

ns::MutableArray Model::_params() const 
{
    return this->_self.params;
}

void Model::tog_cache(bool able)
{
    this->_self.cacheable = able;
}

NNT_END_NS
NNT_END_CXX
