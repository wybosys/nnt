
# ifndef __NNT_UIKIT_UITABBAR_20F4DDFC59334B37B6A470437F755140_H_INCLUDED
# define __NNT_UIKIT_UITABBAR_20F4DDFC59334B37B6A470437F755140_H_INCLUDED

# import "UIButton+NNT.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(UIBadgeIndicator);
NNTDECL_EXTERN_CLASS(WCGMutableTextStyle);
NNTDECL_EXTERN_CLASS(WCGLineStyle);
NNTDECL_EXTERN_CLASS(CGShadow);

enum {
    NNTUITabBarItemStyleDefault, //! image is upon the title.
};
typedef uint NNTUITabBarItemStyle;

enum {
    //! arrow at bottom edge.
    UITabBarArrowPositionBottom,
    
    //! no arrow.
    UITabBarArrowPositionNone,
    
    //! arrow at top edge.
    UITabBarArrowPositionTop,
    
    //! custom.
    UITabBarArrowPositionCustom,
};
typedef uint UITabBarArrowPosition;

@interface NNTUITabBarItem : UIBevelButton {
    
    //! background image.
    UIImage *titleImage;
    
    //! right border.
	UIImage *rightBorder;
    
    //! item style.
    NNTUITabBarItemStyle itemStyle; //! style, default is default.
    
    //! item title.
    NSString *title;
    
    //! normal style for title, it will affect to image's size.
    WCGMutableTextStyle *normalTitleStyle;
    
    //! selected style for title.
    WCGMutableTextStyle *selectedTitleStyle;
    
    //! highlight color for mask.
    UIColor *maskHighlightColor;
    
    //! normal color for mask.
    UIColor *maskNormalColor;
    
    //! badge's value.
    NSString *badgeValue;
    
    //! text style for badge.
    WCGMutableTextStyle *badgeStyle;
    
    //! color for badge.
    UIColor *badgeColor;
    
    //! line style for badge.
    WCGLineStyle *badgeLineStyle;
    
    //! badge.
    UIBadgeIndicator *badge;
    
    //! enable graphite mode. default is NO, it will draw a gradient from rt to lb.
    BOOL enableGraphite;
    
    //! selected color.
    id selectedColor;
    
    //! selected edge shadow.
    CGShadow *selectedEdgeShadow;
}

@property (nonatomic, retain) UIImage *titleImage;
@property (nonatomic, retain) UIImage *rightBorder;
@property (nonatomic, assign) NNTUITabBarItemStyle itemStyle;
@property (nonatomic, copy)   NSString *title;
@property (nonatomic, retain) WCGMutableTextStyle *normalTitleStyle, *selectedTitleStyle;
@property (nonatomic, retain) UIColor *maskHighlightColor, *maskNormalColor;
@property (nonatomic, retain) id selectedColor;
@property (nonatomic, copy) NSString *badgeValue;
@property (nonatomic, retain) WCGMutableTextStyle *badgeStyle;
@property (nonatomic, retain) UIColor *badgeColor;
@property (nonatomic, retain) WCGLineStyle *badgeLineStyle;
@property (nonatomic, retain) UIBadgeIndicator *badge;
@property (nonatomic, assign) BOOL enableGraphite;
@property (nonatomic, retain) CGShadow *selectedEdgeShadow;

- (id)initWithTitleImageName:(NSString *)imageName;
- (id)initWithTitleImage:(UIImage*)image;
- (id)init;

+ (UIImage*)HighlightImage:(UIImage*)image color:(UIColor*)color bk:(BOOL)bk;
+ (UIImage*)NormalImage:(UIImage*)image color:(UIColor*)color;

@end

@interface NNTUITabBarItemArrow : UIView {
 
    UIColor *color;
    
}

@property (nonatomic, retain) UIColor *color;

@end

NNTDECL_EXTERN_CLASS(NNTUITabBar);
//NNTDECL_EXTERN_CLASS(NNTUITabBarView);

@protocol NNTUITabBarDelegate
- (void)tabBar:(NNTUITabBar *)tabbar didSelectTabAtIndex:(NSInteger)index;
@end

@interface NNTUITabBar : NNTUIView {
    
    //! padding.
    CGPadding padding;

    //! all tabs.
    NSArray *tabs;
    
    //! current selected tab.
	NNTUITabBarItem *selectedTab;
    
    //! arrow view.
	UIView *arrow;
    
    //! delegate.
	id <NNTUITabBarDelegate> delegate;
    
    //! text style for normal state.
    WCGMutableTextStyle *normalTitleStyle;
    
    //! text style for selected title.
    WCGMutableTextStyle *selectedTitleStyle;
    
    //! highlight color for mask.
    UIColor *maskHighlightColor;
    
    //! normal color for mask.
    UIColor *maskNormalColor;
    
    //! text style for badge.
    WCGMutableTextStyle *badgeStyle;
    
    //! fill color for badge region.
    UIColor *badgeColor;
    
    //! line stye for badge's edge.
    WCGLineStyle *badgeLineStyle;
    
    //! enable arrow view and position it. default is UITabBarArrowTop.
    UITabBarArrowPosition arrowPosition;
    
    //! enable graphite. default is NO.
    BOOL enableGraphite;
    
    //! selected color for item, it can be Gradient, Color, ColorArray.
    id itemSelectedColor;
    
    //! selected edge shadow.
    CGShadow *itemSelectedEdgeShadow;
    
    //! item width, if is 0, tabbar will auto fit all its tabs. default is 0.
    real itemWidth;
    
    //! preferred count. default is 0.
    uint preferredCount;
}

//! init with frame.
- (id)initWithFrame:(CGRect)aFrame;

//! set selected tab.
- (void)setSelectedTab:(NNTUITabBarItem *)aTab animated:(BOOL)animated;

@property (nonatomic, assign) CGPadding padding;
@property (nonatomic, retain) NSArray *tabs;
@property (nonatomic, assign) NNTUITabBarItem *selectedTab;
@property (nonatomic, assign) id <NNTUITabBarDelegate> delegate;
@property (nonatomic, retain) UIView *arrow;
@property (nonatomic, retain) WCGMutableTextStyle *normalTitleStyle, *selectedTitleStyle;
@property (nonatomic, retain) UIColor *maskHighlightColor, *maskNormalColor;
@property (nonatomic, retain) id itemSelectedColor;
@property (nonatomic, assign) UITabBarArrowPosition arrowPosition;
@property (nonatomic, retain) WCGMutableTextStyle *badgeStyle;
@property (nonatomic, retain) UIColor *badgeColor;
@property (nonatomic, retain) WCGLineStyle *badgeLineStyle;
@property (nonatomic, assign) BOOL enableGraphite;
@property (nonatomic, retain) CGShadow *itemSelectedEdgeShadow;
@property (nonatomic, assign) real itemWidth;
@property (nonatomic, assign) uint preferredCount;

- (CGSize)calcItemSize;

@end

NNT_EXTERN signal_t kSignalSelectChanged;
NNT_EXTERN signal_t kSignalArrowMoving;
NNT_EXTERN signal_t kSignalArrowMoved;

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

class TabBar
: public View<TabBar, NNTUITabBar>
{
    typedef View<TabBar, NNTUITabBar> super;
    
public:
    
    TabBar(NNTUITabBar* bar)
    : super(bar)
    {
        PASS;
    }
    
    void set_arrow(UITabBarArrowPosition pos)
    {
        this->_self.arrowPosition = pos;
    }
    
    virtual void layout_subviews()
    {
        PASS;
    }
    
    void set_item_width(real width)
    {
        this->_self.itemWidth = width;
    }
    
    void set_preferred_count(uint val)
    {
        this->_self.preferredCount = val;
    }
    
    void set_height(real height)
    {
        CGRect rc = this->_self.frame;
        rc.size.height = height;
        this->_self.frame = rc;
        [this->_self.superview setNeedsLayout];        
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif