
# ifndef __WSI_UIKIT_CPGRAPHHOSTINGVIEW_68C8CC85EF6C4499B0D92136DE82A379_H_INCLUDED
# define __WSI_UIKIT_CPGRAPHHOSTINGVIEW_68C8CC85EF6C4499B0D92136DE82A379_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

@interface CPGraphHostingView (WSI)

@end

WSIDECL_PRIVATE_HEAD(UICPGraphHostingView);

@interface UICPGraphHostingView : CPGraphHostingView {
 
    //! allow user tap.
    BOOL allowTap;
    
    //! background image.
    UIImage *backgroundImage;
    
    WSIDECL_PRIVATE(UICPGraphHostingView);
}

@property (nonatomic) BOOL allowTap;
@property (nonatomic, retain) UIImage *backgroundImage;

@end

WSI_END_HEADER_OBJC

# endif