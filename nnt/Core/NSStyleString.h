
# ifndef __NNT_NSSTYLESTRING_5004149A982048D4B3BE9135A4A8B6E3_H_INCLUDED
# define __NNT_NSSTYLESTRING_5004149A982048D4B3BE9135A4A8B6E3_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(NgTextStyle);

@interface NSStyleString : NNTObject {
    
    //! string.
    NSString* string;
    
    //! text style.
    NgTextStyle* textStyle;
    
}

@property (nonatomic, copy) NSString* string;
@property (nonatomic, retain) NgTextStyle* textStyle;

//! init.
- (id)initWithString:(NSString*)str;

//! load css style.
- (void)loadCss:(NSString*)str;

@end

NNT_END_HEADER_OBJC

# endif