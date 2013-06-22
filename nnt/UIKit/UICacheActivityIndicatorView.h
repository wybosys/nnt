
# ifndef __NNT_UIKIT_CACHEACTIVITYINDICATOR_B10B2CC738FE44908FA57B4790F50358_H_INCLUDED
# define __NNT_UIKIT_CACHEACTIVITYINDICATOR_B10B2CC738FE44908FA57B4790F50358_H_INCLUDED

# import "UIView+NNT.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(NNTUIActivityIndicatorView);

@interface UICacheActivityIndicatorView : NNTUIView {
    NNTUIActivityIndicatorView* activityIndicator;
}

@property (nonatomic, retain) NNTUIActivityIndicatorView* activityIndicator;

- (void)startAnimating;
- (void)stopAnimating;

@end

NNT_END_HEADER_OBJC

# endif