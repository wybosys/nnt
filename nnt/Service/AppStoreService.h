
# ifndef __WSI_SERVICE_APPSTORE_D521E33D1FE945BEBA035F7EB78B3817_H_INCLUDED
# define __WSI_SERVICE_APPSTORE_D521E33D1FE945BEBA035F7EB78B3817_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(RateAppReminder);

@protocol RateAppReminderDelegate <NSObject>

- (BOOL)rateReminderCanRemind:(RateAppReminder*)reminder;
- (void)rateReminderRemind:(RateAppReminder*)reminder;

@end

WSIDECL_PRIVATE_HEAD(RateAppReminder);

@interface RateAppReminder : WSIObject
<RateAppReminderDelegate>
{
    
    id<RateAppReminderDelegate> _delegate;
    NSString* _appurl;
    
    WSIDECL_PRIVATE(RateAppReminder);
}

@property (nonatomic, assign) id<RateAppReminderDelegate> delegate;
@property (nonatomic, copy) NSString* appurl;

+ (RateAppReminder*)shared;
- (id)init;

//! if system or user allow remind.
+ (BOOL)AllowRemind;
+ (BOOL)AllowRemindDelay;

//! start reminder.
- (void)remind;

@end

WSI_END_HEADER_OBJC

# endif
