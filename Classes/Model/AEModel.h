
# ifndef __NNT_AEMODEL_9516C4AB89354100A96B5BC4F99C4D74_H_INCLUDED
# define __NNT_AEMODEL_9516C4AB89354100A96B5BC4F99C4D74_H_INCLUDED

# import "Model.h"

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

enum AppEngineErrorCode
{
    AEEC_SUCCESS = 0,
    AEEC_FAILED = 0 - (0x1 << 28),

    AEEC_NOMETHOD = 0x1 << 8,
    AEEC_ARGUMENT = 0x2 << 8,
    AEEC_PERMISSION = 0x4 << 8,
    AEEC_HANDLE = 0x8 << 8,
    AEEC_TIMEOUT = 0x10 << 8,
    AEEC_SIGN = 0x20 << 8,
    
    AEEC_LOST = 0x1 << 24,
    AEEC_OVERFLOW = 0x2 << 24,
    AEEC_INVALID = 0x3 << 24,
    AEEC_DUPLICATE = 0x4 << 24,
};

@interface AppEngineModel : Model {
    NSString *_appid, *_odd, *_errmsg;
}

@property (nonatomic, copy) NSString *appid, *odd;

- (void)success:(id)obj;

@end

NNTCONVERTOR_MODEL_DECL(AppEngineModel);

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# define WAE_MODEL_BEGIN \
NNT_BEGIN_CXX \
NNT_BEGIN_NS(ae) \
NNT_BEGIN_NS(model) \

# define WAE_MODEL_END \
NNT_END_NS \
NNT_END_NS \
NNT_END_CXX

# define WAE_MODEL_BEGIN_NS(ns) \
WAE_MODEL_BEGIN \
NNT_BEGIN_NS(ns)

# define WAE_MODEL_END_NS \
NNT_END_NS \
WAE_MODEL_END

WAE_MODEL_BEGIN

class IAppEngine
: public ns::IModel
{
public:
    
    virtual void params(ns::MutableArray&) const {}
    virtual void success(id) {}
    
};

class AppEngine
: public ns::tpl::Model<NNTCONVERTOR_MODEL(AppEngineModel),
IAppEngine
>
{
public:
    
    NNTDECL_PROPERTY_ACCESS(appid, NSString*);
    NNTDECL_PROPERTY_ACCESS(odd, NSString*);
    
};

WAE_MODEL_END

# endif

# endif

# endif
