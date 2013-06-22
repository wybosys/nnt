
# ifndef __NNT_OA_NULL_34CB7F06B29B4FCF8C60C7728376929B_H_INCLUDED
# define __NNT_OA_NULL_34CB7F06B29B4FCF8C60C7728376929B_H_INCLUDED

# import "Model.h"

NNT_BEGIN_HEADER_OBJC

@interface OANull : Model {
    
    //! version of api.
    version_t version;
    
    //! error code.
    NSString* error_code;
    
    //! error message.
    NSString* error_msg;
    
    //! result.
    NSDictionary* result;
}

@property (nonatomic, copy) NSString *error_code, *error_msg;
@property (nonatomic, assign) version_t version;
@property (nonatomic, retain) NSDictionary* result;

//! init.
- (id)init;

@end

NNT_END_HEADER_OBJC

# endif