
# import "Core.h"
# import "NSStyleString.h"
# import "CoreGraphic+NNT.h"

NNT_BEGIN_OBJC

@implementation NSStyleString

@synthesize textStyle;
@synthesize string;

- (id)initWithString:(NSString *)str {
    self = [super init];
    self.string = str;
    return self;
}

- (void)dealloc {
    zero_release(string);
    zero_release(textStyle);
    
    [super dealloc];
}

- (void)loadCss:(NSString *)str {
    NgMutableTextStyle* ts = [[WCGMutableTextStyle alloc] init];
    
    NSArray* groups = [str arrayOfCaptureComponentsMatchedByRegex:@"([\\w-]+):([\\w#]+)"];
    ::nnt::ns::MutableDictionary css_kv;
    
    for (NSArray* each in groups) {
        if (each.count != 3)
            continue;
        
        NSString* key = [each objectAtIndex:1];
        NSString* value = [each objectAtIndex:2];
        
        css_kv[key] = value;
    }
    
    NSString* value = nil;
    
    if ((value = css_kv[@"font-size"])) {
        ts.fontSize = [value intValue];
    }
    
    if ((value = css_kv[@"font-type"])) {
        if ([value isEqualToString:@"bold"])
            ts.fontType = NgFontTypeBold;
        else if ([value isEqualToString:@"italic"])
            ts.fontType = NgFontTypeBoldItalic;
        else if ([value isEqualToString:@"bold-italic"])
            ts.fontType = NgFontTypeBoldItalic;
    }
    
    if ((value = css_kv[@"font-color"])) {
        uint rgb = 0;
        if ([value matchedByRegex:@"#\\w+"]) {
            value = [value stringByReplacingOccurrencesOfString:@"#" withString:@"0x"];
            NSScanner *scanner = [NSScanner scannerWithString:value];            
            [scanner scanHexInt:&rgb];
        } else {
            rgb = [value intValue];
        }
        ts.color = [WCGColor colorWithRGB:rgb];
    }
    
    self.textStyle = ts;
    [ts release];
}

@end

NNT_END_OBJC