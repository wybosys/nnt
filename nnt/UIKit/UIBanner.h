
# ifndef __WSI_UIKIT_UIBANNER_E02B2B15EC7B4111949C85628197530E_H_INCLUDED
# define __WSI_UIKIT_UIBANNER_E02B2B15EC7B4111949C85628197530E_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(UIBanner);
WSIDECL_EXTERN_CLASS(WCGFill);

typedef enum {
    UIBannerPositionTop,
    UIBannerPositionLeft,
    UIBannerPositionRight,
    UIBannerPositionBottom
} UIBannerPosition;

@protocol UIBannerDelegate <NSObject>

@optional

- (void)bannerLayoutSubViews:(UIBanner*)banner;

@end

@interface UIBanner : UIView {
    //! banner calc its size by according view
    UIView *according;
    
    //! delegate
    id <UIBannerDelegate> delegate;
    
    //! position
    UIBannerPosition bannerPosition;
    
    //! use indicator
    BOOL indicatorEnable;
    
    //! position of indicator
    int indicatorPosition;
    
    //! label
    UILabel *textLabel;
    
    //! backgroud fill
    WCGFill *backgroundFill;
    
    //! height
    NSUInteger height;
}

@property (nonatomic, assign) UIView *according;
@property (nonatomic, assign) id <UIBannerDelegate> delegate;
@property (nonatomic) UIBannerPosition bannerPosition;
@property (nonatomic) BOOL indicatorEnable;
@property (nonatomic) int indicatorPosition;
@property (nonatomic, readonly) UILabel *textLabel;
@property (nonatomic, retain) WCGFill *backgroundFill;
@property (nonatomic) NSUInteger height;

//! init
- (id)initWithAccording:(UIView*)__view;

//! update show with according.
- (void)updateShow;

//! hide
- (void)hide;

//! show
- (void)show;

@end

WSI_END_HEADER_OBJC

# endif