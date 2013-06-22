
# ifndef __OA_PUSH_E840742E108D43E099470CED3E91A898_H_INCLUDED
# define __OA_PUSH_E840742E108D43E099470CED3E91A898_H_INCLUDED

# import "OAToggle.h"

NNT_BEGIN_HEADER_OBJC

@interface OAPush : OAToggle {
    
    //! message.
    NEED NSString* message;
    
    //! title.
    OPTIONAL NSString* title;
    
    //! src url.
    OPTIONAL NSString* reference;
}

@property (nonatomic, copy) NSString *message, *title, *reference;

//! push.
- (void)push;

@end

NNT_END_HEADER_OBJC

# endif