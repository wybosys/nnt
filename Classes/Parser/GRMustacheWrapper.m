
# import "Core.h"
# import "GRMustache.h"
# import "GRMustacheWrapper.h"
# import "GRMustacheRendering_private.h"
# import "GRMustacheTextElement_private.h"
# import "GRMustacheVariableElement_private.h"
# import "GRMustacheRendering_private.h"
# import "GRMustacheBundleTemplateLoader_private.h"
# import "GRMustacheDirectoryTemplateLoader_private.h"
# import "GRMustacheLambda_private.h"
# import "GRMustacheSection_private.h"
# import "GRMustacheTemplate_private.h"
# import "GRMustacheTemplateLoader_private.h"
# import "GRMustacheToken_private.h"
# import "GRMustacheTokenizer_private.h"
# import "GRBoolean.h"

NNT_BEGIN_OBJC

static void appendRenderingElementsWithContext(NSMutableString *buffer, NSArray *elems, GRMustacheContext *context);
static NSString* renderContextSection(GRMustacheSection *elem, GRMustacheContext *context);
static NSString *renderContextVariableElement(GRMustacheVariableElement *elem, GRMustacheContext *context);

@interface GRMustacheTemplateWrapper : NSObject

+ (BOOL)objectIsFalseValue:(id)object;

@end

@implementation GRMustacheTemplateWrapper

+ (BOOL)objectIsFalseValue:(id)object {
	return (object == nil ||
			object == [NSNull null] ||
			object == [GRNo no] ||
			(void *)object == (void *)kCFBooleanFalse ||
			([object isKindOfClass:[NSString class]] && ((NSString*)object).length == 0));
}

+ (GRMustacheObjectKind)objectKind:(id)object {
	if ([self objectIsFalseValue:object]) {
		return GRMustacheObjectKindFalseValue;
	}
	
	if ([object isKindOfClass:[NSDictionary class]]) {
		return GRMustacheObjectKindTrueValue;
	}
	
	if ([object conformsToProtocol:@protocol(NSFastEnumeration)]) {
		return GRMustacheObjectKindEnumerable;
	}
	
	// TODO: why can't we test for protocol on iOS?
	// if ([object conformsToProtocol:@protocol(GRMustacheHelper)]) -> tests fails on iOS
	if ([object respondsToSelector:@selector(renderObject:withSection:)]) {
		return GRMustacheObjectKindLambda;
	}
	
	return GRMustacheObjectKindTrueValue;
}

@end

@interface GRMustacheTextElement()
@property (nonatomic, retain) NSString *text;
@end

@interface GRMustacheSection()
@property (nonatomic, retain) NSString *name;
@property (nonatomic, retain) NSString *baseTemplateString;
@property (nonatomic) NSRange range;
@property (nonatomic) BOOL inverted;
@property (nonatomic, retain) NSArray *elems;
@end

@interface GRMustacheVariableElement()
@property (nonatomic, retain) NSString *name;
@property (nonatomic) BOOL raw;
@end

static NSString *htmlEscapeVariableElement(GRMustacheVariableElement* elem, NSString *string) {
    NSMutableString *result = [NSMutableString stringWithString:string];
    [result replaceOccurrencesOfString:@"&" withString:@"&amp;" options:NSLiteralSearch range:NSMakeRange(0, result.length)];
    [result replaceOccurrencesOfString:@"<" withString:@"&lt;" options:NSLiteralSearch range:NSMakeRange(0, result.length)];
    [result replaceOccurrencesOfString:@">" withString:@"&gt;" options:NSLiteralSearch range:NSMakeRange(0, result.length)];
    [result replaceOccurrencesOfString:@"\"" withString:@"&quot;" options:NSLiteralSearch range:NSMakeRange(0, result.length)];
    [result replaceOccurrencesOfString:@"'" withString:@"&apos;" options:NSLiteralSearch range:NSMakeRange(0, result.length)];
    return result;
}

static NSString *renderContextVariableElement(GRMustacheVariableElement *elem, GRMustacheContext *context) {
	id value = [context valueForKey:elem.name];
	if ([GRMustacheTemplateWrapper objectIsFalseValue:value]) {
		return @"";
	}
	if (elem.raw) {
		return [value description];
	}
    return htmlEscapeVariableElement(elem, [value description]);
}

static NSString* renderContextSection(GRMustacheSection *elem, GRMustacheContext *context) {
    NSMutableString *result = nil;
    NSAutoreleasePool *pool = [NSAutoreleasePool new];
	id value = [context valueForKey:elem.name];
	switch([GRMustacheTemplateWrapper objectKind:value]) {
		case GRMustacheObjectKindFalseValue:
			if (elem.inverted) {
                result = [[NSMutableString string] retain];
                appendRenderingElementsWithContext(result, elem.elems, context);
			}
			break;
			
		case GRMustacheObjectKindTrueValue:
			if (!elem.inverted) {
                result = [[NSMutableString string] retain];
                appendRenderingElementsWithContext(result, elem.elems, [context contextByAddingObject:value]);
            }
			break;
			
		case GRMustacheObjectKindEnumerable:
			if (elem.inverted) {
				BOOL empty = YES;
				for (id object in value) {
					empty = NO;
					break;
				}
				if (empty) {
                    result = [[NSMutableString string] retain];
                    appendRenderingElementsWithContext(result, elem.elems, context);
				}
			} else {
                result = [[NSMutableString string] retain];
				for (id object in value) {
                    appendRenderingElementsWithContext(result, elem.elems, [context contextByAddingObject:object]);
				}
			}
			break;
            
		case GRMustacheObjectKindLambda:
			if (!elem.inverted) {
                result = [[(id<GRMustacheHelper>)value renderObject:context withSection:elem] mutableCopy];
            }
			break;
			
		default: { @throw [NSException exceptionWithName:@"GRMustache" reason:@"unsupport kind" userInfo:nil]; } break;
	}
    [pool drain];
    if (!result) {
        return @"";
    }
    return [result autorelease];
}

static inline NSString* renderContextTextElement(GRMustacheTextElement* elem, GRMustacheContext *context) {
    return elem.text;
}

static void appendRenderingElementsWithContext(NSMutableString *buffer, NSArray *elems, GRMustacheContext *context) {
    for (NSObject <GRMustacheRenderingElement> * elem in elems) {
        NSString *str = nil;
        Class class = [elem class];
        
        if (class == [GRMustacheSection class]) {
            str = renderContextSection((GRMustacheSection *)elem, context);
        } else if (class == [GRMustacheTextElement class]) {
            str = renderContextTextElement((GRMustacheTextElement *)elem, context);
        } else if (class == [GRMustacheVariableElement class]) {
            str = renderContextVariableElement((GRMustacheVariableElement *)elem, context);
        } else {
            @throw [NSException exceptionWithName:@"GRMustache" reason:@"render a unknown element" userInfo:nil];
        }
        
# ifdef NNT_DEBUG
        if (0) {
            [buffer appendString:[elem renderContext:context]];
        }
# endif
        
        if (str)
            [buffer appendString:str];
    }
}

@implementation GRMustacheTemplateRender (private)

- (NSString *)renderContext:(GRMustacheContext *)context {
    NSMutableString *result = [NSMutableString string];
    NSAutoreleasePool *pool = [NSAutoreleasePool new];
    appendRenderingElementsWithContext(result, tpl.elems, context);
    [pool drain];
    return result;
}

@end

@implementation GRMustacheTemplateRender

@synthesize tpl;

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    zero_release(tpl);
    [super dealloc];
}

- (NSString*)renderObject:(id)object {
    return [self renderContext:[GRMustacheContext contextWithObject:object]];
}

@end

NNT_END_OBJC