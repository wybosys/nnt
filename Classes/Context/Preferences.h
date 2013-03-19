
# ifndef __WSI_CTX_PREFERENCES_6C8BCCAE82204D4A83F171A1B87BE6D4_H_INCLUDED
# define __WSI_CTX_PREFERENCES_6C8BCCAE82204D4A83F171A1B87BE6D4_H_INCLUDED

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(Context);
WSIDECL_PRIVATE_HEAD(Preferences);

//! @class preferences
@interface Preferences : WSIObject {	
    
	Context *ctx; //! context	
	WSIDECL_PRIVATE(Preferences);
}

@property (nonatomic, assign) Context *ctx;

- (NSString*)findSetting:(NSString*)__key;

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

# include "../Core/NSPreference+WSI.h"

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ns)

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

WSI_END_NS
WSI_END_HEADER_CXX

# endif
// end cxx

# endif
// end objc

# endif
