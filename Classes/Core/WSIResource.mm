
# import "Core.h"
# import "WSIResource.h"

WSI_BEGIN_OBJC

@implementation WSIResource

+ (BOOL)IsExist:(NSString *)tgt {
    NSString* file = [WSIResource PathOf:tgt];
    NSFileManager* fs = [NSFileManager defaultManager];
    return [fs fileExistsAtPath:file];
}

+ (NSString *)PathOf:(NSString*)tgt {
    NSString* bundle = [[NSBundle mainBundle] bundlePath];
    
# ifdef WSI_TARGET_MAC
    bundle = [bundle stringByAppendingPathComponent:@"Contents"];
    bundle = [bundle stringByAppendingPathComponent:@"Resources"];
# endif
    
    NSString* ret = [bundle stringByAppendingPathComponent:tgt];
    return ret;
}

+ (NSString *)ContentOf:(NSString*)tgt {
    return [WSIResource ContentOf:tgt inBundle:YES];
}

+ (NSString *)ContentOf:(NSString*)tgt inBundle:(BOOL)inBundle {
    NSString *path = inBundle == YES ? [WSIResource PathOf:tgt] : tgt;
    NSData *data = [[[NSData alloc] initWithContentsOfFile:path] autorelease];
    if (nil == data) {
        trace_fmt(@"failed to load %@, it may be non-exist.", path);
        return @"";
    }
    NSString *str = [[[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding] autorelease];
    return str;
}

+ (NSData *)DataOf:(NSString*)tgt inBundle:(BOOL)inBundle {
    NSString *path = inBundle == YES ? [WSIResource PathOf:tgt] : tgt;
    NSData *data = [[[NSData alloc] initWithContentsOfFile:path] autorelease];
    if (nil == data) {
        trace_fmt(@"failed to load %@, it may be non-exist.", path);
        return nil;
    }
    return data;   
}

+ (NSData *)DataOf:(NSString*)tgt {
     return [WSIResource DataOf:tgt inBundle:YES];
}

@end

WSI_END_OBJC

WSI_BEGIN_CXX

bool Resource::IsExist(NSString *tgt)
{
    return [WSIResource IsExist:tgt];
}

core::string Resource::PathOf(::NSString *tgt)
{
    ::NSString* str = [WSIResource PathOf:tgt];
    return wtl::tostr(str);
}

core::string Resource::PathOf(const core::string &tgt)
{
    ::NSString* str = ::wsi::tostr(tgt);
    return Resource::PathOf(str);
}

WSI_END_CXX