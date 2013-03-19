
# import "Foundation+NNT.h"
# import "Execution+NNT.h"
# import "WSIExecution+Chart.h"

# import "AppDelegate.h"

int main(int argc, char *argv[])
{
    int ret;
    WSI_AUTORELEASEPOOL_BEGIN
    ret = UIApplicationMain(argc, argv, nil, NSStringFromClass([WSIAppDelegate class]));
    WSI_AUTORELEASEPOOL_END
    return ret;
}
