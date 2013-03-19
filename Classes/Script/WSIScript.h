
# ifndef __WSI_SCRIPT_F7E9958F9B97447CA1E16B9B57A85DAA_H_INCLUDED
# define __WSI_SCRIPT_F7E9958F9B97447CA1E16B9B57A85DAA_H_INCLUDED

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_OBJC

@protocol WSIScript <NSObject>

@required

//! run script string.
- (BOOL)executeString:(NSString*)str;

//! get error message.
- (NSString*)errorMessage;

@end

WSI_END_HEADER_OBJC

# endif

# endif