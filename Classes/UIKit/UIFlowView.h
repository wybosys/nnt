
# ifndef __NNT_UIKIT_FLOWVIEW_EBD0809215FB4A7C916DB0A059308535_H_INCLUDED
# define __NNT_UIKIT_FLOWVIEW_EBD0809215FB4A7C916DB0A059308535_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface UIFlowView : NNTUIScrollView {
    
    //! margin. default is zero.
    CGMargin margin;
    
}

@property (nonatomic, assign) CGMargin margin;

//! views for flow.
- (NSArray*)viewsForFlow;

//! update layout.
- (void)updateLayout;

@end

NNT_END_HEADER_OBJC

# endif