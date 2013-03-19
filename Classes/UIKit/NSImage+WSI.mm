
# import "Core.h"
# import "NSImage+WSI.h"

WSI_BEGIN_OBJC

@implementation NSImage (WSI)

- (void)saveAsPNG:(NSURL*)url {
    if (url.isFileURL == NO) {
        trace_msg(@"skip directory.");
        return;
    }

    if (NO == [[url.pathExtension lowercaseString] isEqualToString:@"png"])
        url = [url URLByAppendingPathExtension:@"png"];
    
    NSBitmapImageRep *imgRep = [[self representations] objectAtIndex: 0];
    NSData *data = [imgRep representationUsingType:NSPNGFileType properties: nil];
    [data writeToFile:[url relativePath] atomically: NO];
}

- (NSData*)dataAsPNG {
    NSBitmapImageRep *imgRep = [[self representations] objectAtIndex: 0];
    NSData *data = [imgRep representationUsingType: NSPNGFileType properties: nil];
    return data;
}

@end

WSI_END_OBJC