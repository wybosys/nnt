
# ifndef __NNT_UIKIT_COVERDRAWERCONTROLLER_05FCA8B740A24B78AF597FE0A025515D_H_INCLUDED
# define __NNT_UIKIT_COVERDRAWERCONTROLLER_05FCA8B740A24B78AF597FE0A025515D_H_INCLUDED

# import "UICoverDrawer.h"

NNT_BEGIN_HEADER_OBJC

@interface UICoverDrawData : NNTObject {
    
    //! title.
    NSString* title;
    
    //! image.
    UIImage* image;
}

@property (nonatomic, copy) NSString* title;
@property (nonatomic, retain) UIImage* image;

//! init data.
+ (id)dataWith:(NSString*)title image:(UIImage*)image;

@end

@interface UICoverDrawerController : NNTUIViewController <UICoverDrawerDataSource, UICoverDrawerDelegate> {
    
    //! datas.
    NSArray* datas;
}

@property (nonatomic, readonly) UICoverDrawer* coverDrawer;
@property (nonatomic, retain) NSArray* datas;

- (void)reloadData;

@end

NNT_END_HEADER_OBJC

# endif