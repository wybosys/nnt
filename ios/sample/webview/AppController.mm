
# import "Foundation+NNT.h"
# import "AppController.h"

WSI_BEGIN_OBJC

@implementation AppController

- (void)viewIsLoading {
    [self.htmlView loadHTMLStringLocal:file_load(@"index.html")];
}

@end

WSI_END_OBJC