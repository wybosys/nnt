//
//  main.m
//  performance
//
//  Created by 王 渊博 on 12-1-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

# import "WSIFoundation.h"
# import "WSIExecution.h"
# import "AppDelegate.h"

int main(int argc, char *argv[])
{
    int ret;
    WSI_AUTORELEASEPOOL_BEGIN
    ret = UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
    WSI_AUTORELEASEPOOL_END
    return ret;
}
