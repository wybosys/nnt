
# import "Core.h"
# import "MustacheParser.h"
# import "GRMustache.h"
# import "GRMustacheWrapper.h"
# import "Resource+NNT.h"

NNT_BEGIN_OBJC

@interface MustacheParserPrivate : NSObject {
    
    GRMustacheTemplateRender *tpl;
    MustacheParser *d_owner;
    
}

@property (nonatomic, assign) MustacheParser *d_owner;
@property (nonatomic, retain) GRMustacheTemplateRender *tpl;

@end

@implementation MustacheParserPrivate

@synthesize d_owner;
@synthesize tpl;

- (id)init {
    self = [super init];        
    return self;
}

- (void)dealloc {
    zero_release(tpl);
    [super dealloc];
}

@end

@implementation MustacheParser 

- (id)init {
    self = [super init];
    NNTDECL_PRIVATE_INIT(MustacheParser);
    return self;
}

- (id)initWithTemplate:(NSString *)tpl {
    self = [self init];
    [self loadTemplate:tpl];
    return self;
}

+ (id)parserWithTemplate:(NSString *)tpl {
    return [[[MustacheParser alloc] initWithTemplate:tpl] autorelease];
}

+ (id)parserNamed:(NSString *)file {
    return [[[MustacheParser alloc] initWithTemplate:[NNTResource ContentOf:file]] autorelease];
}

- (void)dealloc {
    NNTDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (BOOL)loadTemplate:(NSString *)tpl {
    NSError *err = nil;
    d_ptr.tpl = nil;
    id obj = [GRMustacheTemplate parseString:tpl error:&err];
    if ([obj isKindOfClass:[GRMustacheTemplate class]] == NO)
        return NO;
    if (err) 
        return NO;
    GRMustacheTemplateRender *render = [[GRMustacheTemplateRender alloc] init];
    render.tpl = obj;
    d_ptr.tpl = render;
    [render release];
    return YES;
}

- (NSString*)renderObject:(id)obj {
    if (d_ptr.tpl == nil)
        return @"";
    NSError *err = nil;
    NSString *ret = [d_ptr.tpl renderObject:obj];
    if (err)
        return @"";
    return ret;
}

@end

NNT_END_OBJC