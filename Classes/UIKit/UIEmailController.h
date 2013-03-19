
# ifndef __WSI_UIKIT_EMAILCONTROLLER_B7B799FC02D94D0FA2D3830E9C235517_H_INCLUDED
# define __WSI_UIKIT_EMAILCONTROLLER_B7B799FC02D94D0FA2D3830E9C235517_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

WSIDECL_PRIVATE_HEAD(UIEmailController);

@interface UIEmailController : WSIObject {
    
    NSMutableArray* _to;
    NSMutableArray* _cc;
    NSMutableArray* _bcc;
    
    NSString *_body, *_html;
    
    WSIDECL_PRIVATE(UIEmailController);
}

@property (nonatomic, copy) NSArray *to; 
@property (nonatomic, copy) NSArray *cc;
@property (nonatomic, copy) NSArray *bcc;
@property (nonatomic, copy) NSString *body, *html;

//! add address.
- (void)addTo:(NSString*)addr;
- (void)addCc:(NSString*)addr;
- (void)addBcc:(NSString*)addr;

//! exec.
- (void)execute;

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

class EmailController
: public ns::Object<UIEmailController>
{
public:
    
    EmailController()
    {
        PASS;
    }
    
    void to(ns::String const& addr)
    {
        [this->_self addTo:addr];
    }
    
    void cc(ns::String const& addr)
    {
        [this->_self addCc:addr];
    }
    
    void bcc(ns::String const& addr)
    {
        [this->_self addBcc:addr];
    }
    
    void set_body(ns::String const& str)
    {
        this->_self.body _assign_ str;
    }
    
    void set_html(ns::String const& str)
    {
        this->_self.html _assign_ str;
    }
    
    void execute()
    {
        [this->_self execute];
    }
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif