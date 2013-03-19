
# import "Foundation+NNT.h"
# import "WSIExecution.h"
#import <UIKit/UIKit.h>
# import "custometabbarAppDelegate.h"

int main(int argc, char *argv[])
{
    int ret;
    WSI_AUTORELEASEPOOL_BEGIN
    ret = UIApplicationMain(argc, argv, nil, NSStringFromClass([custometabbarAppDelegate class]));
    WSI_AUTORELEASEPOOL_END
    return ret;

}

WSIDEBUG_THEME_IMPL;
