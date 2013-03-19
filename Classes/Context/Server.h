
# ifndef __NNT_CTX_SERVER_E13B4C59324848F3932AE8D1057ED359_H_INCLUDED
# define __NNT_CTX_SERVER_E13B4C59324848F3932AE8D1057ED359_H_INCLUDED

# include "../Model/Model.h"

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(Context);
NNTDECL_EXTERN_CLASS(Model);
NNTDECL_PRIVATE_HEAD(Server);

typedef void (*func_server_callback)(id);

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX

typedef void (Object::*func_server_objcallback)(id);
typedef void (Object::*func_server_modelcallback)(::wsi::ns::IModel*);
typedef void (Object::*func_server_modelscallback)(::wsi::core::vector< ::wsi::ns::IModel*> const&);

# define _objaction(func) (::wsi::func_server_objcallback)&func
# define _mdlaction(func) (::wsi::func_server_modelcallback)&func
# define _mdlsaction(func) (::wsi::func_server_modelscallback)&func

NNT_END_HEADER_CXX

# endif

enum {
    //! will callback in a new thread by system default.
    ServerCallbackTypeThread,
    
    //! will callback in mainThread.
    ServerCallbackTypeMainThread,
    
    //! will callback in background thread.
    ServerCallbackTypeBackgroundThread,
    
    //! default.
    ServerCallbackTypeDefault = ServerCallbackTypeMainThread,
};

typedef uint ServerCallbackType;

@interface ServerCallbackObject : NSObject {
    
    SEL _objc_action;
    id _objc_target;
    func_server_callback _sta_func;
    
# ifdef NNT_CXX
    
    ::wsi::func_server_modelcallback _cxxmdl_func;
    ::wsi::func_server_modelscallback _cxxmdls_func;
    ::wsi::func_server_objcallback _cxx_func;
    ::wsi::Object* _cxx_target;
    
# endif
    
    ServerCallbackType _callbackType;
    
}

@property (nonatomic, assign) SEL objc_action;
@property (nonatomic, retain) id objc_target;
@property (nonatomic, assign) func_server_callback sta_func;

# ifdef NNT_CXX

@property (nonatomic, assign) ::wsi::func_server_modelcallback cxxmdl_func;
@property (nonatomic, assign) ::wsi::func_server_modelscallback cxxmdls_func;
@property (nonatomic, assign) ::wsi::func_server_objcallback cxx_func;
@property (nonatomic, assign) ::wsi::Object* cxx_target;

# endif

@property (nonatomic, assign) ServerCallbackType callbackType;

- (id)initWithAction:(SEL)act target:(id)target;
- (id)initWithFunction:(func_server_callback)func;

# ifdef NNT_CXX

- (id)initWithCxxAction:(::wsi::func_server_objcallback)action target:(::wsi::Object*)target;
- (id)initWithCxxMdlAction:(::wsi::func_server_modelcallback)action target:(::wsi::Object*)target;
- (id)initWithCxxMdlsAction:(::wsi::func_server_modelscallback)action target:(::wsi::Object*)target;

# endif

- (void)backgroundCall:(id)obj;
- (void)threadCall:(id)obj;
- (void)mainthreadCall:(id)obj;
- (void)call:(id)obj;

@end

@interface Server : NNTObject {
	
    //! refercence point to context.
	Context *_ctx;
    
    //! if use cache mechi.
    BOOL _GlobalCache;
    
    //! default rpc class for model get. default is HttpRequest.
    Class _classRpc;
	
	NNTDECL_PRIVATE(Server);
}

@property (nonatomic, assign) Context *ctx;
@property (nonatomic, assign) BOOL GlobalCache;
@property (nonatomic, assign) Class classRpc;

//! @function retrieve model sync
- (BOOL)retrieve_model:(Model*)model;

//! @function retrieve mode sync and use cache
- (BOOL)retrieve_model:(Model *)model cachename:(NSString*)cachename cachetime:(NSUInteger)cachetime;

//! @function retrieve model async
//! @param model Model object.
- (void)retrieve_model_async:(Model*)model;

//! @function retrieve model async
//! @param model Model object.
//! @param callbackType callback mechi.
- (void)retrieve_model_async:(Model*)model callbackType:(ServerCallbackType)callbackType;

//! @param model Model object.
//! @param selector will be - (void)callback:(Model*)model {} to obj.
- (void)retrieve_model_async:(Model*)model selector:(SEL)sel object:(NSObject*)obj;

//! @param model Model object.
//! @param selector will be - (void)callback:(Model*)model {} to obj.
//! @param callbackType callback mechi.
- (void)retrieve_model_async:(Model*)model selector:(SEL)sel object:(NSObject*)obj callbackType:(ServerCallbackType)callbackType;

//! @param model Model object.
//! @param selector will be - (void)callback:(Model*)model {} to obj.
//! @param fselector wiil be invoke when failed to fetch data.
- (void)retrieve_model_async:(Model*)model selector:(SEL)sel object:(NSObject*)obj fselector:(SEL)fsel fobject:(NSObject*)fobj;
- (void)retrieve_model_async:(Model*)model selector:(SEL)sel object:(NSObject*)obj fselector:(SEL)fsel fobject:(NSObject*)fobj callbackType:(ServerCallbackType)callbackType;

//! this function use functor instead of member.
- (void)retrieve_model_async:(Model*)model func:(func_server_callback)func;
- (void)retrieve_model_async:(Model*)model func:(func_server_callback)func callbackType:(ServerCallbackType)callbackType;
- (void)retrieve_model_async:(Model*)model func:(func_server_callback)func failed:(func_server_callback)failed;
- (void)retrieve_model_async:(Model*)model func:(func_server_callback)func failed:(func_server_callback)failed callbackType:(ServerCallbackType)callbackType;

# ifdef NNT_CXX

//! retrieve model sync.
- (BOOL)retrieve_cxxmodel:(::wsi::ns::IModel*)model;

//! retrieve model async.
- (void)retrieve_model_async:(Model*)model action:(::wsi::func_server_objcallback)func target:(::wsi::Object*)target;
- (void)retrieve_model_async:(Model*)model action:(::wsi::func_server_objcallback)func target:(::wsi::Object*)target callbackType:(ServerCallbackType)callbackType;

//! retrieve models async.
- (void)retrieve_cxxmodel_async:(::wsi::ns::IModel*)model action:(::wsi::func_server_modelcallback)func target:(::wsi::Object*)target;

//! retrieve models async.
- (void)retrieve_cxxmodel_async:(::wsi::ns::IModel*)model action:(::wsi::func_server_modelcallback)func target:(::wsi::Object*)target callbackType:(ServerCallbackType)callbackType;

# endif

//! @function retrieve model async and use cache
- (void)retrieve_model_async:(Model *)model selector:(SEL)sel object:(NSObject *)obj cachename:(NSString*)cachename cachetime:(NSUInteger)cachetime;
- (void)retrieve_model_async:(Model *)model selector:(SEL)sel object:(NSObject *)obj fselector:(SEL)fsel fobject:(NSObject*)fobj cachename:(NSString*)cachename cachetime:(NSUInteger)cachetime;

//! @function retrieve models.
- (void)retrieve_models_async:(NSArray *)models;
- (void)retrieve_models_async:(NSArray *)models selector:(SEL)sel object:(NSObject *)obj;
- (void)retrieve_models_async:(NSArray *)models selector:(SEL)sel object:(NSObject *)obj callbackType:(ServerCallbackType)callbackType;

# ifdef NNT_CXX

//! @function retrieve cxx model.
- (void)retrieve_cxxmodels_async:(::wsi::core::vector< ::wsi::ns::IModel*> const&)model action:(::wsi::func_server_modelscallback)func target:(::wsi::Object*)target;

- (void)retrieve_cxxmodels_async:(::wsi::core::vector< ::wsi::ns::IModel*> const&)model action:(::wsi::func_server_modelscallback)func target:(::wsi::Object*)target callbackType:(ServerCallbackType)callbackType;

# endif

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ns)

class Context;

class Server
: public ns::Object< ::Server >
{
    NNTDECL_NOCOPY(Server);
    typedef ns::Object< ::Server > super;
    
public:
    
    Server()
    : super(nil)
    {
        PASS;  
    };
    
    template <typename mdlT>
    bool retrieve(mdlT const& model)
    {
        wtl::mutable_pointer<mdlT> ptr(model);
        return [this->_self retrieve_cxxmodel:&(*ptr)];
    }
    
    void retrieve_async(ns::IModel* model)
    {
        this->retrieve_async(model, _mdlaction(Server::__null_callback_model), this);
    }
    
    void retrieve_async(ns::IModel* model, func_server_modelcallback func, ::wsi::Object* target)
    {
        [this->_self retrieve_cxxmodel_async:model action:func target:target];
    }
    
    void retrieve_async(ns::IModel* model, func_server_modelcallback func, ::wsi::Object* target, ServerCallbackType type)
    {
        [this->_self retrieve_cxxmodel_async:model action:func target:target callbackType:type];
    }
    
    void retrieve_async(core::vector<ns::IModel*> const& mdl)
    {
        this->retrieve_async(mdl, _mdlsaction(Server::__null_callback_models), this);
    }
    
    void retrieve_async(core::vector<ns::IModel*> const& mdl, func_server_modelscallback cb, ::wsi::Object* target)
    {
        [this->_self retrieve_cxxmodels_async:mdl action:cb target:target];
    }
    
protected:
    
    void __null_callback_model(ns::IModel*)
    {
        PASS;
    }
    
    void __null_callback_models(core::vector<ns::IModel*> const&)
    {
        PASS;
    }
    
    friend class Context;
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif
// end cxx

# endif
// end objc

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(context)

class Server
	: public cxx::Object<>
{

};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
