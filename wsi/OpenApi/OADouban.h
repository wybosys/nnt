
# ifndef __WSI_OA_DOUBAN_1441DFEAE99A4655AEDFA41883DCF1A8_H_INCLUDED
# define __WSI_OA_DOUBAN_1441DFEAE99A4655AEDFA41883DCF1A8_H_INCLUDED

# import "OAuth.h"

WSI_BEGIN_HEADER_OBJC

@interface OARequestDouban : OARequest_1_0 {
    NSString *urlCallback;
}

@property (nonatomic, copy) NSString *urlCallback;

@end

@interface OAuthorizeDouban : OAuthorize_1_0 {
}

@end

@interface OAccessDouban : OAccess_1_0 

@end

@interface OADouban : OAuth_1_0 

@end

@interface OApiDouban : OACommonApi_1_0

@end

@interface OApiDoubanUserInfo : OApiDouban 
@end

@interface OApiDoubanDiaryPost : OApiDouban 

@property (nonatomic, copy) NSString *content;
@property (nonatomic, copy) NSString *title;

@end


WSI_END_HEADER_OBJC

# endif