
# import "Core.h"
# import "VHtml.h"

NNT_BEGIN

NNTDECL_PRIVATE_BEGIN(VHtml, NNTObject)
{
	NSMutableDictionary *dict;
}

@property (nonatomic, retain) NSMutableDictionary *dict;

NNTDECL_PRIVATE_IMPL(VHtml)

@synthesize dict;

- (id)init {
	self = [super init];
	dict = [NSMutableDictionary new];
	return self;
}

- (void)fini {
    safe_release(dict);
    [super fini];
}

NNTDECL_PRIVATE_END

@implementation VHtml 

- (id)init {
	self = [super init];
	NNTDECL_PRIVATE_INIT(VHtml);
	return self;
}

- (void)dealloc {
	NNTDECL_PRIVATE_DEALLOC();
	[super dealloc];
}

+ (NSString*)make_css:(NSString *)content {
	NSMutableString* ret = [[NSMutableString new] autorelease];
	[ret appendString:@"<style type=\"text/css\"><!--"];
	[ret appendString:content];
	[ret appendString:@"--></style>"];
	return ret;
}

+ (NSString*)make_javascript:(NSString *)content {
	NSMutableString* ret = [[NSMutableString new] autorelease];
	[ret appendString:@"<script language=\"javascript\">"];
	[ret appendString:content];
	[ret appendString:@"</script>"];
	return ret;
}

@end

NNT_END