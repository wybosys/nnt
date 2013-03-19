
# ifndef __WSI_UIKIT_SMSCONTROLLER_AAFB1E2E11A74A57912EFFE70645A038_H_INCLUDED
# define __WSI_UIKIT_SMSCONTROLLER_AAFB1E2E11A74A57912EFFE70645A038_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

WSIDECL_PRIVATE_HEAD(UISMSController);

@interface UISMSController : WSIObject {
    NSMutableArray* _recipients;
    
    WSIDECL_PRIVATE(UISMSController);
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

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

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

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif