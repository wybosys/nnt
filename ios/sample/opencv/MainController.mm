
# import "WSIFoundation.h"
# import "MainController.h"
# import "WGQRCode.h"

WSI_BEGIN_OBJC

@implementation MainController

- (void)viewIsLoading {
    wsi::WGQRCodeReader reader;
    
    reader.connect(kSignalProgressBegin, @selector(begin:), self);
    reader.connect(kSignalProgressEnd, @selector(end:), self);
    reader.connect(kSignalProgressError, @selector(progress:), self);
    
    //NSData* data = [NSData dataWithContentsOfFile:@"qr.png"];
    //reader.set_image((byte const*)[data bytes], [data length]);
    reader.load_image([resource_path(@"qr.png") UTF8String]);
    reader.analyze();
}

- (void)begin:(WSIEventObj*)evt {
    
}

- (void)end:(WSIEventObj*)evt {
    
}

- (void)progress:(WSIEventObj*)evt {
    
}

@end

WSI_END_OBJC