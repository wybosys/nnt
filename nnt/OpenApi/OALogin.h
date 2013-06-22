
# ifndef __OA_LOGIN_7F8FBC5E4B4C4A5FA208922C87ACD85A_H_INCLUDED
# define __OA_LOGIN_7F8FBC5E4B4C4A5FA208922C87ACD85A_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface OALoginParameter : NNTObject

@property (nonatomic, assign) Class clsAuth, clsUser;

@end

@interface OALogin : NNTObject

+ (void)Login:(OALoginParameter*)param sel:(SEL)sel obj:(id)obj;

@end

NNT_EXTERN signal_t kSignalSuccess;
NNT_EXTERN signal_t kSignalFailed;

NNT_END_HEADER_OBJC

# endif