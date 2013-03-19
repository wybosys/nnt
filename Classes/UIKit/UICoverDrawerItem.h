
# ifndef __NNT_UIKIT_COVERDRAWERITEM_D561E46E27B640F2A8EE8587BE997738_H_INCLUDED
# define __NNT_UIKIT_COVERDRAWERITEM_D561E46E27B640F2A8EE8587BE997738_H_INCLUDED

# import "UIView+NNT.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_PRIVATE_HEAD(UICoverDrawerItem);
NNTDECL_EXTERN_CLASS(UICoverDrawer);
NNTDECL_EXTERN_CLASS(NgLineStyle);

@interface UICoverDrawerItem : NNTUIView {
    
    //! level
    NSInteger level;
    
    //! is level >= 0, is on the sreen
    BOOL shouldOnScreen;
    BOOL isOnScreen;
    
    //! the owner
    UICoverDrawer *drawer;
    
    //! default size
    CGSize contentSize;
    
    //! index
    //! dynamic index
    NSUInteger index_dyn;
    //! static index
    NSUInteger index_sta;
    
    //! image
    UIImage *image;
        
    //! title
    NSString *title;

    //! draggable
    BOOL draggable;
    real interval_draggable;
    
    NNTDECL_PRIVATE(UICoverDrawerItem);
    
    //! navigator
    UICoverDrawerItem *hdl_preitem, *hdl_nextitem;
}

@property (nonatomic) NSInteger level;
@property (nonatomic, readonly) BOOL shouldOnScreen;
@property (nonatomic) BOOL isOnScreen;
@property (nonatomic, assign) UICoverDrawerItem *hdl_preitem, *hdl_nextitem;
@property (nonatomic, assign) UICoverDrawer *drawer;
@property (nonatomic) CGSize contentSize;
@property (nonatomic, readonly) NSUInteger index_dyn;
@property (nonatomic) NSUInteger index_sta;
@property (nonatomic, retain) UIImage *image;
@property (nonatomic, copy) NSString *title;
@property (nonatomic) BOOL draggable;
@property (nonatomic) real interval_draggable;
@property (nonatomic, readonly) UICoverDrawerItem *next, *previous;

+ (id)item;

//! calc best size
- (CGSize)calcBestSize;

//! distance, A - TGT - B,
//! A:TGT, < 0; TGT:B, > 0.
//! @return 0, if notfound or is self.
- (NSInteger)distance:(UICoverDrawerItem*)item;

//! CGRect of content.
- (CGRect)contentRect;

//! set feature.
- (void)setFeatureAsNext:(UICoverDrawerItem*)item;
- (void)setFeatureAsPre:(UICoverDrawerItem*)item;

//! force hide
- (void)forceHide;
- (void)forceShow;

@end

NNT_END_HEADER_OBJC

# endif