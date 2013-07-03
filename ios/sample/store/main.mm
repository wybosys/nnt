
# import "Foundation+NNT.h"
# import "Execution+NNT.h"
# import "AppDelegate.h"

int main(int argc, char *argv[])
{
    int ret;
    NNT_AUTORELEASEPOOL_BEGIN
    ret = UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
    NNT_AUTORELEASEPOOL_END
    return ret;
}
