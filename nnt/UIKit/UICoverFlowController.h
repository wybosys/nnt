
# ifndef __WSI_UIKIT_UICOVERFLOWCONTROLLER_3E3B4983FDE14884AB612E412B3BEE86_H_INCLUDED
# define __WSI_UIKIT_UICOVERFLOWCONTROLLER_3E3B4983FDE14884AB612E412B3BEE86_H_INCLUDED

# import "UIViewController+WSI.h"
# import "UICoverFlow.h"

WSI_BEGIN_HEADER_OBJC

@interface UICoverFlowData : WSIObject {
    
    //! image handle.
    UIImage* _image;
    
    //! image's url.
    NSURL* _imageURL;
}

@property (nonatomic, retain) UIImage* image;
@property (nonatomic, retain) NSURL* imageURL;

@end

@interface UICoverFlowController : WSIUIViewController <UICoverFlowDelegate, UIItemsDatasource> {
    
    //! datas.
    NSMutableArray* _datas;
    
    //! default class for instance item.
    Class _itemClass;
}

@property (nonatomic, readonly) UICoverFlow *coverFlow;
@property (nonatomic, retain) NSMutableArray* datas;
@property (nonatomic, assign) Class itemClass;

- (void)reloadData;

@end

WSI_END_HEADER_OBJC

# endif