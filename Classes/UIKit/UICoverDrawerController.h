
# ifndef __WSI_UIKIT_COVERDRAWERCONTROLLER_05FCA8B740A24B78AF597FE0A025515D_H_INCLUDED
# define __WSI_UIKIT_COVERDRAWERCONTROLLER_05FCA8B740A24B78AF597FE0A025515D_H_INCLUDED

# import "UICoverDrawer.h"

WSI_BEGIN_HEADER_OBJC

@interface UICoverDrawData : WSIObject {
    
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

@interface UICoverDrawerController : WSIUIViewController <UICoverDrawerDataSource, UICoverDrawerDelegate> {
    
    //! datas.
    NSArray* datas;
}

@property (nonatomic, readonly) UICoverDrawer* coverDrawer;
@property (nonatomic, retain) NSArray* datas;

- (void)reloadData;

@end

WSI_END_HEADER_OBJC

# endif