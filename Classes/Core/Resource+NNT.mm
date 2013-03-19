
# import "Core.h"
# import "NNTResource.h"

NNT_BEGIN_OBJC

@implementation NNTResource

+ (BOOL)IsExist:(NSString *)tgt {
    NSString* file = [NNTResource PathOf:tgt];
    NSFileManager* fs = [NSFileManager defaultManager];
    return [fs fileExistsAtPath:file];
}

+ (NSString *)PathOf:(NSString*)tgt {
    NSString* bundle = [[NSBundle mainBundle] bundlePath];
    
# ifdef NNT_TARGET_MAC
    bundle = [bundle stringByAppendingPathComponent:@"Contents"];
    bundle = [bundle stringByAppendingPathComponent:@"Resources"];
# endif
    
    NSString* ret = [bundle stringByAppendingPathComponent:tgt];
    return ret;
}

+ (NSString *)ContentOf:(NSString*)tgt {
    return [NNTResource ContentOf:tgt inBundle:YES];
}

+ (NSString *)ContentOf:(NSString*)tgt inBundle:(BOOL)inBundle {
    NSString *path = inBundle == YES ? [NNTResource PathOf:tgt] : tgt;
    NSData *data = [[[NSData alloc] initWithContentsOfFile:path] autorelease];
    if (nil == data) {
        trace_fmt(@"failed to load %@, it may be non-exist.", path);
        return @"";
    }
    NSString *str = [[[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding] autorelease];
    return str;
}

+ (NSData *)DataOf:(NSString*)tgt inBundle:(BOOL)inBundle {
    NSString *path = inBundle == YES ? [NNTResource PathOf:tgt] : tgt;
    NSData *data = [[[NSData alloc] initWithContentsOfFile:path] autorelease];
    if (nil == data) {
        trace_fmt(@"failed to load %@, it may be non-exist.", path);
        return nil;
    }
    return data;   
}

+ (NSData *)DataOf:(NSString*)tgt {
     return [NNTResource DataOf:tgt inBundle:YES];
}

@end

NNT_END_OBJC

NNT_BEGIN_CXX

bool Resource::IsExist(NSString *tgt)
{
    return [NNTResource IsExist:tgt];
}

core::string Resource::PathOf(::NSString *tgt)
{
    ::NSString* str = [NNTResource PathOf:tgt];
    return ntl::tostr(str);
}

core::string Resource::PathOf(const core::string &tgt)
{
    ::NSString* str = ::wsi::tostr(tgt);
    return Resource::PathOf(str);
}

NNT_END_CXX