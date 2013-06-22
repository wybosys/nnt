
# ifndef __NNT_UIKIT_UICOVERFLOWCONTROLLER_3E3B4983FDE14884AB612E412B3BEE86_H_INCLUDED
# define __NNT_UIKIT_UICOVERFLOWCONTROLLER_3E3B4983FDE14884AB612E412B3BEE86_H_INCLUDED

# import "UIViewController+NNT.h"
# import "UICoverFlow.h"

NNT_BEGIN_HEADER_OBJC

@interface UICoverFlowData : NNTObject {
    
    //! image handle.
    UIImage* _image;
    
    //! image's url.
    NSURL* _imageURL;
}

@property (nonatomic, retain) UIImage* image;
@property (nonatomic, retain) NSURL* imageURL;

@end

@interface UICoverFlowController : NNTUIViewController <UICoverFlowDelegate, UIItemsDatasource> {
    
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

NNT_END_HEADER_OBJC

# endif