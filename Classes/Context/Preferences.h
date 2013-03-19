
# ifndef __NNT_CTX_PREFERENCES_6C8BCCAE82204D4A83F171A1B87BE6D4_H_INCLUDED
# define __NNT_CTX_PREFERENCES_6C8BCCAE82204D4A83F171A1B87BE6D4_H_INCLUDED

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(Context);
NNTDECL_PRIVATE_HEAD(Preferences);

//! @class preferences
@interface Preferences : NNTObject {	
    
	Context *ctx; //! context	
	NNTDECL_PRIVATE(Preferences);
}

@property (nonatomic, assign) Context *ctx;

- (NSString*)findSetting:(NSString*)__key;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

# include "../Core/NSPreference+NNT.h"

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ns)

class Context;

class Preferences
: public ns::Object< ::Preferences>
{
    typedef ns::Object< ::Preferences> super;
    
public:
    
    Preferences()
    : super(nil)
    {
        PASS;
    }
    
    core::Preference defaults;
    
    friend class Context;
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif
// end cxx

# endif
// end objc

# endif
