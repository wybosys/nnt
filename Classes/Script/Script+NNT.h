
# ifndef __NNT_SCRIPT_F7E9958F9B97447CA1E16B9B57A85DAA_H_INCLUDED
# define __NNT_SCRIPT_F7E9958F9B97447CA1E16B9B57A85DAA_H_INCLUDED

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

@protocol NNTScript <NSObject>

@required

//! run script string.
- (BOOL)executeString:(NSString*)str;

//! get error message.
- (NSString*)errorMessage;

@end

NNT_END_HEADER_OBJC

# endif

# endif