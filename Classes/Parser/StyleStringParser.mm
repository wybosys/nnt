
# import "Core.h"
# import "StyleStringParser.h"
# import "NSStyleString.h"
# import "XmlParser.h"

WSI_BEGIN_OBJC

@interface StyleStringParser ()

@property (nonatomic, retain) NSString* string;

@end

@interface StyleStringParser (hidden)

- (void)_parse_xml:(XmlNode *)node;

@end

@implementation StyleStringParser (hidden)

- (void)_parse_xml:(XmlNode *)node {
    NSMutableString* str = [[NSMutableString alloc] initWithCapacity:1024];
    NSArray* texts = [node childrenForName:@"text"];
    NSMutableArray* sss = [[NSMutableArray alloc] initWithCapacity:texts.count];
    for (XmlNode *each in texts) {
        
        NSStyleString* ss = [[NSStyleString alloc] initWithString:each.value];
        
        // load style.
        XmlAttribute* attr_style = [each attributeForName:@"style"];
        [ss loadCss:attr_style.value];
        
        [sss addObject:ss];
        [ss release];
        
        // append value.
        [str appendString:each.value];
    }
    
    // set result.
    self.string = str;
    [str release];
    
    // set sss.
    self.styleStrings = sss;
    [sss release];
}

@end

@implementation StyleStringParser

@synthesize string;
@synthesize styleStrings;

- (void)dealloc {
    zero_release(string);
    zero_release(styleStrings);
    [super dealloc];
}

- (void)parseString:(NSString *)_string {
    XmlParser* xml = [[XmlParser alloc] initWithString:[NSString stringWithFormat:@"<root>%@</root>", _string]];
    [self _parse_xml:xml.rootNode];
    [xml release];
}

- (void)parseData:(NSData *)_data {
    NSMutableData *data = [[NSMutableData alloc] initWithData:[@"<root>" dataUsingEncoding:NSUTF8StringEncoding]];
    [data appendData:_data];
    [data appendData:[@"</root>" dataUsingEncoding:NSUTF8StringEncoding]];
    XmlParser* xml = [[XmlParser alloc] initWithData:data];
    [data release];
    [self _parse_xml:xml.rootNode];
    [xml release];
}

@end

WSI_END_OBJC