
# ifndef __NNT_UIKIT_CPGRAPHHOSTINGVIEW_68C8CC85EF6C4499B0D92136DE82A379_H_INCLUDED
# define __NNT_UIKIT_CPGRAPHHOSTINGVIEW_68C8CC85EF6C4499B0D92136DE82A379_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface CPGraphHostingView (NNT)

@end

NNTDECL_PRIVATE_HEAD(UICPGraphHostingView);

@interface UICPGraphHostingView : CPGraphHostingView {
 
    //! allow user tap.
    BOOL allowTap;
    
    //! background image.
    UIImage *backgroundImage;
    
    NNTDECL_PRIVATE(UICPGraphHostingView);
}

@property (nonatomic) BOOL allowTap;
@property (nonatomic, retain) UIImage *backgroundImage;

@end

NNT_END_HEADER_OBJC

# endif