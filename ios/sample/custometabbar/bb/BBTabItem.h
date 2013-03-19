
# ifndef __BBTABBARITEM_9253AFB87D604C63A9A43DADD46379A1_H_INCLUDED
# define __BBTABBARITEM_9253AFB87D604C63A9A43DADD46379A1_H_INCLUDED


WSI_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(BBTabBar);

@interface BBTabItem : NSObject {
    NSString *_title;
    NSString *_icon;
    id        _object;
    int       _badgeNumber;
    BBTabBar *_tabBar;
}

@property (nonatomic, copy)   NSString *title;
@property (nonatomic, copy)   NSString *icon;
@property (nonatomic, retain) id  object;
@property (nonatomic)         int badgeNumber;

- (id)initWithTitle:(NSString *)title;

- (id)initWithImage:(NSString *)image;

- (id)initWithTitle:(NSString *)title withImage:(NSString *)image;

@end

WSI_END_HEADER_OBJC

# endif