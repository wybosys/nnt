
# include "Foundation+NNT.h"
# include "Execution+NNT.h"
# import "AppDelegate.h"

int main(int argc, char *argv[])
{
    int ret;
    WSI_AUTORELEASEPOOL_BEGIN
    ret = UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
    WSI_AUTORELEASEPOOL_END
    return ret;
}
