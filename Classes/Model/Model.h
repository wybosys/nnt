
# ifndef __NNT_MODEL_501D4F67DA324B8A85BB74E9DF2EAB6E_H_INCLUDED
# define __NNT_MODEL_501D4F67DA324B8A85BB74E9DF2EAB6E_H_INCLUDED

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

// @interface Model
@protocol IModel

//! @function check result if can be processed
- (BOOL)is_valid:(id)result;

//! @function process result
- (BOOL)process:(id)result;

@end

NNTDECL_EXTERN_PROTOCOL(NullObjParser);

@interface Model : NNTObject <IModel> {
    
    //! url for fetch data.
	NSString *_url;
    
    //! service name.
	NSString *_service;
    
    //! method name.
	NSString *_method;
    
    //! store the params.
	NSMutableArray *_params;
    
    //! parse params and result for model. default is NullObjParser;
    id<NullObjParser> _objparser;
    
    //! cache overdate time. 0 indicate not-overdate forever.
    NSUInteger _cacheTime;
    
    //! if force update the cache item, set cacheTime to YES, will ignore cache and set the data back to cache. default is NO. will find object in default cache first.    
    BOOL _cacheUpdate;
    
    //! cacheble. default is YES.
    BOOL _cacheable;
    
    //! cache append string. default is nil.
    NSString* _cacheAppendr;
    
    //! verbose fatal, default is NO.
    BOOL _verbose;
    
    //! verbose waiting. default is NO.
    BOOL _verboseWait;
    
    //! verbose success. default is NO.
    BOOL _verboseSuc;
    
    //! verbose data. default is NO.
    BOOL _verboseData;
    
    //! memory useage. it may be used for present memory of object in model. so use it carefully.
    size_t _memoryUsage;
    
    //! rpc class. use for instance rpc object while server fetching data. default is nil, thus the server will use its defaultRpc to instace the rpc object.
    Class _classRpc;
    
    //! demo mode. default is NO.
    BOOL _demo;
    
@protected
    
    NSMutableArray *_extend_datas;
    
}

@property (nonatomic, retain) NSString *url;
@property (nonatomic, copy) NSString *service;
@property (nonatomic, copy) NSString *method;
@property (nonatomic, retain, getter = get_params) NSMutableArray *params;
@property (nonatomic, retain, getter = get_extend_datas) NSMutableArray *extendDatas;
@property (nonatomic, retain) id<NullObjParser> objparser;
@property (nonatomic, assign) NSUInteger cacheTime;
@property (nonatomic, assign) BOOL cacheUpdate, cacheable;
@property (nonatomic, copy) NSString* cacheAppendr;
@property (nonatomic, assign) BOOL verbose, verboseSuc, verboseWait, verboseData;
@property (nonatomic, assign) size_t memoryUsage;
@property (nonatomic, assign) Class classRpc;
@property (nonatomic, assign) BOOL demo;

//! get params.
- (NSMutableArray*)get_params;
- (NSMutableArray*)get_params_deep;
- (NSMutableArray*)dup_params;
- (NSMutableArray*)get_extend_datas;
- (NSMutableArray*)get_extend_datas_deep;
- (NSMutableArray*)dup_extend_datas;

//! get url.
- (NSURL*)get_url;

//! get method.
- (NSString*)get_method;

//! get service.
- (NSString*)get_service;

//! collect all params.
- (NSArray*)collect;

//! unique id.
- (NSString*)uniqueIdentifier;

//! verbose.
- (void)activeVerbose;
- (void)beginWaiting;
- (void)endWaiting;

@end

@protocol ModelPage <NSObject>

- (void)nextPage;
- (void)previousPage;

@end

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ns)

class IModel;
class Model;

NNT_END_NS
NNT_END_HEADER_CXX


@interface __cxxmodel_wrapper : Model {
    @protected
    ::wsi::ns::IModel* model;
}

@property (nonatomic, assign) ::wsi::ns::IModel* model;

- (NSURL*)get_url;

@end

# endif

# ifdef NNT_CXX

# define NNTCONVERTOR_MODEL(mdl) \
__cxxmodel_convertor_##mdl

# define NNTCONVERTOR_MODEL_DECL(mdl) \
@interface NNTCONVERTOR_MODEL(mdl) : mdl { \
@protected \
::wsi::ns::IModel* model; \
} \
@property (nonatomic, assign) ::wsi::ns::IModel* model; \
@end

# define NNTCONVERTOR_MODEL_IMPL(mdl) \
NNTCONVERTOR_MODEL_IMPL_BEGIN(mdl) \
NNTCONVERTOR_MODEL_IMPL_END

# define NNTCONVERTOR_MODEL_IMPL_BEGIN(mdl) \
@implementation NNTCONVERTOR_MODEL(mdl) \
@synthesize model; \

# define NNTCONVERTOR_MODEL_IMPL_END \
@end

# else

# define NNTCONVERTOR_MODEL_DECL(mdl)
//# define NNTCONVERTOR_MODEL_IMPL(mdl)

# endif


NNT_END_HEADER_OBJC

//! url model.
# import "MURLModel.h"

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ns)

class IModel
: public ::wsi::RefObject
{
public:
    
    //! process.
    virtual bool process(id result) = 0;
    
    //! get objc-model.
    virtual id nsmodel() const = 0;
    
};

NNT_BEGIN_NS(tpl)

template <typename mdlT, typename ImdlT = ns::IModel>
class Model
: public ns::Object<mdlT, ImdlT>
{
public:
    
    enum {
        VERBOSE_NONE = 0,
        VERBOSE = 0x1,
        VERBOSE_WAIT = 0x2,
        VERBOSE_SUC = 0x4,
    };
    
    Model()
    {
        this->_self.model = this;
    }
    
    virtual bool process(id)
    {
        return true;
    }
    
    virtual id nsmodel() const
    {
        return (id)this->_self;
    }
    
    virtual void set_update(bool val)
    {
        this->_self.cacheUpdate = val;
    }
    
    virtual void set_verbose(uint d)
    {
        this->_self.verbose = MASK_CHECK(VERBOSE, d);
        this->_self.verboseWait = MASK_CHECK(VERBOSE_WAIT, d);
        this->_self.verboseSuc = MASK_CHECK(VERBOSE_SUC, d);
    }
    
    virtual void set_url(ns::String const& url)
    {
        this->_self.url = url;
    }
    
    virtual void set_method(ns::String const& mtd)
    {
        this->_self.method = mtd;
    }

};

NNT_END_NS

class Model
: public tpl::Model< __cxxmodel_wrapper >
{
public:
    
    Model()
    {
        PASS;
    }
        
    //! get params of model.
    virtual Array params() const;
    
    //! show verbose.
    virtual void active_verbose() const;    
    
    //! show waiting.
    virtual void begin_waiting() const;    
    
    //! close waiting.
    virtual void end_waiting() const; 
    
    //! get url of model/
    virtual URL url() const;
            
    //! set model's parser.
    template <typename parserT>
    void set_parser(parserT const& parser)
    {
        ntl::const_pointer<parserT> ptr(parser);
        this->_self.objparser = *ptr;
    }
    
    //! set VERBOSE MODE.
    virtual void set_verbose(uint);
    
    //! set rpc class use for comm with server.
    virtual void set_rpc(Class cls);
    
    //! set url.
    virtual void set_url(ns::String const&);
    
    //! set if force update, other words, force refresh.
    virtual void set_update(bool val);
    
    //! set cache enable.
    virtual void tog_cache(bool able);
    
    //! set appendr.
    virtual void set_appendr(ns::String const&);
    
    //! set method.
    virtual void set_method(ns::String const&);
    
    //! get method.
    virtual ns::String method() const;
    
    //! set service.
    virtual void set_service(ns::String const&);
    
    //! get service.
    virtual ns::String service() const;
    
    //! set cache time.
    virtual void set_overdate(uint secs);
    
protected:
    
    //! set if is demo model.
    void _set_demo(bool = true);
    
    //! get url string.
    ns::String _url() const;
    
    //! get mutable params.
    ns::MutableArray _params() const;
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif
// end cxx

# endif
// end objc

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(model)

class IModel
	: public RefObject
{
public:

};

NNTCLASS(Model);

class Model
	: public IModel
{

public:

};

NNT_BEGIN_NS(tpl)

template <typename baseM = model::Model>
class Model
	: public baseM
{

public:

};

NNT_END_NS

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# include "MOpeModel.h"

# endif
