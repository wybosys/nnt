
# ifndef __OA_LOGIN_7F8FBC5E4B4C4A5FA208922C87ACD85A_H_INCLUDED
# define __OA_LOGIN_7F8FBC5E4B4C4A5FA208922C87ACD85A_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface OALoginParameter : WSIObject

@property (nonatomic, assign) Class clsAuth, clsUser;

@end

@interface OALogin : WSIObject

+ (void)Login:(OALoginParameter*)param sel:(SEL)sel obj:(id)obj;

@end

WSI_EXTERN signal_t kSignalSuccess;
WSI_EXTERN signal_t kSignalFailed;

WSI_END_HEADER_OBJC

# endif