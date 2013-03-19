
# ifndef __WSI_NSSTYLESTRING_5004149A982048D4B3BE9135A4A8B6E3_H_INCLUDED
# define __WSI_NSSTYLESTRING_5004149A982048D4B3BE9135A4A8B6E3_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(WCGTextStyle);

@interface NSStyleString : WSIObject {
    
    //! string.
    NSString* string;
    
    //! text style.
    WCGTextStyle* textStyle;
    
}

@property (nonatomic, copy) NSString* string;
@property (nonatomic, retain) WCGTextStyle* textStyle;

//! init.
- (id)initWithString:(NSString*)str;

//! load css style.
- (void)loadCss:(NSString*)str;

@end

WSI_END_HEADER_OBJC

# endif