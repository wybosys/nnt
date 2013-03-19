
# ifndef __NNT_UIKIT_SMSCONTROLLER_AAFB1E2E11A74A57912EFFE70645A038_H_INCLUDED
# define __NNT_UIKIT_SMSCONTROLLER_AAFB1E2E11A74A57912EFFE70645A038_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

NNTDECL_PRIVATE_HEAD(UISMSController);

@interface UISMSController : NNTObject {
    NSMutableArray* _recipients;
    
    NNTDECL_PRIVATE(UISMSController);
}

@property (nonatomic, copy) NSArray* recipients;
@property (nonatomic, copy) NSString* body;

//! execute.
- (void)execute;

//! add phone.
- (void)add:(NSString*)phone;

//! available.
+ (BOOL)available;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

class SMSController
: public ns::Object<UISMSController>
{
public:
    
    SMSController()
    {
        PASS;
    }
    
    void add(ns::String const& phone)
    {
        [this->_self add:phone];
    }
    
    void set(ns::String const& str)
    {
        this->_self.body _assign_ str;
    }
    
    void execute()
    {
        [this->_self execute];
    }
    
    static bool available()
    {
        return [UISMSController available];
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif