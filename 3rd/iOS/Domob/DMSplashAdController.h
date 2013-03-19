//
//  DMSplashAdController.h
//
//  Copyright (c) 2012 Domob Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "DMAdView.h"

@protocol DMSplashAdControllerDelegate;
@interface DMSplashAdController : UIViewController

@property (nonatomic, assign) BOOL isReady; // 可以通过该属性获知开屏广告是否可以展现
@property (nonatomic, assign) NSObject<DMSplashAdControllerDelegate> *delegate; // 指定开屏广告的委派
@property (nonatomic, assign) UIViewController *rootViewController; // 指定开屏广告的RootViewController

// 初始化开屏广告控制器
- (id)initWithPublisherId:(NSString *)publisherId   // Domob PublisherId
                   window:(UIWindow *)window;       // 用于呈现开屏广告的Key Window

// 初始化开屏广告控制器
- (id)initWithPublisherId:(NSString *)publisherId   // Domob PublisherId
                   window:(UIWindow *)window        // 用于呈现开屏广告的Key Window
               background:(UIColor *)background;    // 开屏广告出现前的背景颜色、图片（默认为黑色）

// 初始化开屏广告控制器
- (id)initWithPublisherId:(NSString *)publisherId   // Domob PublisherId
                   window:(UIWindow *)keyWindow     // 用于呈现开屏广告的Key Window
               background:(UIColor *)background     // 开屏广告出现前的背景颜色、图片（默认为黑色）
                animation:(BOOL)yesOrNo;            // 开屏广告关闭时，是否使用渐变动画（默认有关闭动画）

// 呈现广告
- (void)present;

// 设置地理位置信息
- (void)setLocation:(CLLocation *)location;

// 设置邮编
- (void)setPostcode:(NSString *)postcode;

// 设置关键字
- (void)setKeywords:(NSString *)keywords;

// 设置用户年龄
- (void)setUserBirthday:(NSString *)userBirthday;

// 设置用户性别
- (void)setUserGender:(DMUserGenderType)userGender;

@end

////////////////////////////////////////////////////////////////////////////////////////////////////

@protocol DMSplashAdControllerDelegate
@optional
// 当开屏广告加载成功后，回调该方法
- (void)dmSplashAdSuccessToLoadAd:(DMSplashAdController *)dmSplashAd;
// 当开屏广告加载失败后，回调该方法
- (void)dmSplashAdFailToLoadAd:(DMSplashAdController *)dmSplashAd withError:(NSError *)err;

// 当插屏广告要被呈现出来前，回调该方法
- (void)dmSplashAdWillPresentScreen:(DMSplashAdController *)dmSplashAd;
// 当插屏广告被关闭后，回调该方法
- (void)dmSplashAdDidDismissScreen:(DMSplashAdController *)dmSplashAd;
@end
