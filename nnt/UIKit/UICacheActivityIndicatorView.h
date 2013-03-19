
# ifndef __WSI_UIKIT_CACHEACTIVITYINDICATOR_B10B2CC738FE44908FA57B4790F50358_H_INCLUDED
# define __WSI_UIKIT_CACHEACTIVITYINDICATOR_B10B2CC738FE44908FA57B4790F50358_H_INCLUDED

# import "UIView+WSI.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(WSIUIActivityIndicatorView);

@interface UICacheActivityIndicatorView : WSIUIView {
    WSIUIActivityIndicatorView* activityIndicator;
}

@property (nonatomic, retain) WSIUIActivityIndicatorView* activityIndicator;

- (void)startAnimating;
- (void)stopAnimating;

@end

WSI_END_HEADER_OBJC

# endif