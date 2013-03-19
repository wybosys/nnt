//
//  main.m
//  empty
//
//  Created by 王 渊博 on 12-3-23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

# import "Foundation+NNT.h"
# import "Execution+NNT.h"
# import "AppDelegate.h"

int main(int argc, char *argv[])
{
    int ret = 0;
    WSI_AUTORELEASEPOOL_BEGIN
    ret = UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
    WSI_AUTORELEASEPOOL_END
    return ret;
}
