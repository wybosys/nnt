
# import "Core.h"
# import "Directory+WSI.h"
# import "App.h"
# import "WSIResource.h"

WSI_BEGIN_OBJC

WSI_EXTERN NSURL *WSIDirectoryTouchWithType(NSString* path, WSIDirectoryType type) {
    NSFileManager *fs_mgr = [NSFileManager defaultManager];    
    NSString *str_tgt = @"";
    switch (WSIDirectoryTypeMajor(type)) {
        default: {
            dthrow([NSException exceptionWithName:@"type unknown" reason:@"unknown directory type." userInfo:nil]);
        } break;
            
        case WSIDirectoryTypeNone: {
            str_tgt = path;
            if ([str_tgt isEqualToString:@""]) {
                return [NSURL URLWithString:@"/"];
            }
        } break;
            
        case WSIDirectoryTypeSystem: {
            uint min_type = WSIDirectoryTypeMinor(type);
            uint wsi_type = WSIDirectoryTypeWsiMinor(type);
            
            /*
            if (wsi_type && !min_type) {
                min_type = NSDocumentDirectory;
            }
             */
            
            if (min_type) {
                NSArray *paths = NSSearchPathForDirectoriesInDomains(min_type,
                                                                     NSUserDomainMask,
                                                                     YES);
                if ([paths count]) {
                    str_tgt = [paths objectAtIndex:0];
                }
            } else {
                str_tgt = NSTemporaryDirectory();
            }
            
            if (wsi_type) {
                
# ifdef WSI_TARGET_MAC
                str_tgt = [str_tgt stringByAppendingPathComponent:@"wsi"];
                str_tgt = [str_tgt stringByAppendingPathComponent:[WSIApplication shared].applicationIdentity];
# endif
                str_tgt = [str_tgt stringByAppendingPathComponent:@"var"];
                
                if (MASK_CHECK(NSTemplateDirectory, wsi_type)) {
                    str_tgt = [str_tgt stringByAppendingPathComponent:@"tmp"];
                }
                else if (MASK_CHECK(NSVariableDirectory, wsi_type)) {
                    PASS;
                }
                else if (MASK_CHECK(NSLogDirectory, wsi_type)) {
                    str_tgt = [str_tgt stringByAppendingPathComponent:@"log"];
                }
            }
            
            str_tgt = [str_tgt stringByAppendingPathComponent:path];
            
        } break;
            
        case WSIDirectoryTypeBundle:
        case WSIDirectoryTypeBundleWritable:
# ifdef WSI_JAILBREAK
        case WSIDirectoryTypeTemplate:
# endif
        {
            NSString *str = [[NSBundle mainBundle] bundlePath];
            
# ifdef WSI_JAILBREAK
            if (WSIDirectoryTypeMajor(type) == WSIDirectoryTypeTemplate) {
                str = [str stringByAppendingPathComponent:@"var"];
                str = [str stringByAppendingPathComponent:@"tmp"];
            }
# endif
            
            str = [str stringByAppendingPathComponent:path];
            str_tgt = str;
        } break;
            
    }
    
    NSURL *ret = nil;
    BOOL is_dir;
    if ([fs_mgr fileExistsAtPath:str_tgt isDirectory:&is_dir]) {
        if (is_dir) {
            ret = [NSURL fileURLWithPath:str_tgt isDirectory:YES];
        }
    } else {
        ret = [NSURL fileURLWithPath:str_tgt isDirectory:YES];
    }
    
    return ret;
}

NSURL *WSIDirectoryCreateWithType(NSString *path, WSIDirectoryType type) {
    NSFileManager *fs_mgr = [NSFileManager defaultManager];
    NSString *str_tgt = @"";
    switch (WSIDirectoryTypeMajor(type)) {
        default: {
            dthrow([NSException exceptionWithName:@"type unknown" reason:@"unknown directory type." userInfo:nil]);
        } break;
            
        case WSIDirectoryTypeNone: {
            str_tgt = path;
            if ([str_tgt isEqualToString:@""]) {
                return [NSURL URLWithString:@"/"];
            }
        } break;

        case WSIDirectoryTypeSystem: {
            uint min_type = WSIDirectoryTypeMinor(type);
            uint wsi_type = WSIDirectoryTypeWsiMinor(type);
            
            /*
            if (wsi_type && !min_type) {
                min_type = NSDocumentDirectory;
            }
             */
            
            if (min_type) {
                NSArray *paths = NSSearchPathForDirectoriesInDomains(min_type,
                                                                     NSUserDomainMask,
                                                                     YES);
                if ([paths count]) {
                    str_tgt = [paths objectAtIndex:0];
                }
            } else {
                str_tgt = NSTemporaryDirectory();
            }
            
            if (wsi_type) {
                
# ifdef WSI_TARGET_MAC
                
                str_tgt = [str_tgt stringByAppendingPathComponent:@"wsi"];
                str_tgt = [str_tgt stringByAppendingPathComponent:[WSIApplication shared].applicationIdentity];
                
# endif         
                
                // add 'var' directory.
                str_tgt = [str_tgt stringByAppendingPathComponent:@"var"];
                
                // var's sub directory.
                if (MASK_CHECK(NSTemplateDirectory, wsi_type)) {
                    str_tgt = [str_tgt stringByAppendingPathComponent:@"tmp"];
                }
                else if (MASK_CHECK(NSVariableDirectory, wsi_type)) {
                    PASS;
                }
                else if (MASK_CHECK(NSLogDirectory, wsi_type)) {
                    str_tgt = [str_tgt stringByAppendingPathComponent:@"log"];
                }
            }
            
            str_tgt = [str_tgt stringByAppendingPathComponent:path];
            
        } break;
            
        case WSIDirectoryTypeBundle:
        case WSIDirectoryTypeBundleWritable:
# ifdef WSI_JAILBREAK
        case WSIDirectoryTypeTemplate: 
# endif
        {
            NSString *str = [[NSBundle mainBundle] bundlePath];
            
# ifdef WSI_JAILBREAK
            if (WSIDirectoryTypeMajor(type) == WSIDirectoryTypeTemplate) {
                str = [str stringByAppendingPathComponent:@"var"];
                str = [str stringByAppendingPathComponent:@"tmp"];
            }
# endif
            
            str = [str stringByAppendingPathComponent:path];
            str_tgt = str;            
        } break;
            
    }
    
    BOOL is_dir;
    NSURL* ret = nil;
    if ([fs_mgr fileExistsAtPath:str_tgt isDirectory:&is_dir]) {
        if (is_dir) {
            ret = [NSURL fileURLWithPath:str_tgt isDirectory:YES];
        }
    } else {
        if ([fs_mgr createDirectoryAtPath:str_tgt withIntermediateDirectories:YES attributes:nil error:nil]) {
            ret = [NSURL fileURLWithPath:str_tgt isDirectory:YES];
        }
    }
    
    return ret;
}

NSURL *WSIFileTouchWithType(NSString* path, WSIDirectoryType type)
{
    NSURL* url = NULL;
    if (type == WSIDirectoryTypeAbsolute)
    {
        url = [NSURL fileURLWithPath:path];
    }
    else
    {
        url = WSIDirectoryCreateWithType(@"", type);
        if (type == WSIDirectoryTypeBundleWritable)
        {
            NSFileManager *fs_mgr = [NSFileManager defaultManager];
            NSURL* tgt = WSIDirectoryCreateWithType(@"", (NSVariableDirectory | WSIDirectoryTypeSystem));
            tgt = [tgt URLByAppendingPathComponent:path];
            if ([fs_mgr fileExistsAtPath:tgt.relativePath])
                return tgt;
            NSURL* src = [url URLByAppendingPathComponent:path];
            if ([fs_mgr fileExistsAtPath:src.relativePath])
            {
                NSError* err;
                if (NO == [fs_mgr copyItemAtPath:src.relativePath toPath:tgt.relativePath error:&err])
                {
                    throw [NSException exceptionWithName:err.localizedDescription reason:err.localizedFailureReason userInfo:nil];
                    return nil;
                }
            }
            url = tgt;
        }
        else
        {
            url = [url URLByAppendingPathComponent:path];
        }
    }
    return url;
}

BOOL WSIDirectoryRemoveWithType(NSString* path, WSIDirectoryType type)
{
    NSURL* url = WSIDirectoryTouchWithType(path, type);
    if (url == nil)
        return NO;
    
    NSFileManager* fs = [NSFileManager defaultManager];
    NSError* err = nil;
    BOOL suc = [fs removeItemAtPath:url.relativePath error:&err];
    if (err)
        trace_obj(err);
    return suc;
}

@implementation NSDirectory

@synthesize url;

- (id)initWith:(NSString*)_url {
    self = [super init];
    if (self) {
        self.url = _url;
        _fs_mgr = [NSFileManager defaultManager];
    }
    return self;
}

- (void)dealloc {
    [url release];
    [super dealloc];
}

- (NSArray*)collect:(NSDirectoryEnum)flag {
    NSError* err = nil;
    NSArray* res = [_fs_mgr contentsOfDirectoryAtPath:url error:&err];
    if (err)
        return nil;
    NSMutableArray *ret = [[NSMutableArray alloc] init];
    
    for (NSString* each in res) {
        NSString* str = [url stringByAppendingPathComponent:each];
        NSDictionary* attrs = [_fs_mgr attributesOfItemAtPath:str error:&err];
        if (err)
            continue;

        if (MASK_CHECK(NSDirectoryEnumSkipInvisible, flag)) {
            if ([each hasPrefix:@"."])
                continue;
        }

        if (MASK_CHECK(NSDirectoryEnumRegular, flag) &&
            [attrs objectForKey:NSFileType] == NSFileTypeRegular)
            [ret addObject:pair(each, str)];
    }
    
    return [ret autorelease];
}

+ (BOOL)fileReadable:(NSString*)file {
    return [[NSFileManager defaultManager] isReadableFileAtPath:file];
}

+ (BOOL)fileWritable:(NSString*)file {
    return [[NSFileManager defaultManager] isWritableFileAtPath:file];
}

+ (BOOL)fileExistsAtPath:(NSString *)path {
    return [[NSFileManager defaultManager] fileExistsAtPath:path];
}

+ (BOOL)fileExistsAtPath:(NSString *)path isDirectory:(BOOL *)isDirectory {
    return [[NSFileManager defaultManager] fileExistsAtPath:path isDirectory:isDirectory];
}

+ (BOOL)directoryExistsAtPath:(NSString *)path {
    BOOL isdir;
    if ([[NSFileManager defaultManager] fileExistsAtPath:path isDirectory:&isdir])
        return isdir;
    return false;
}

+ (NSString*)retinaImageNamed:(NSString*)file {
    NSString* retina = [file stringByReplacingOccurrencesOfRegex:@"(.)(png|jpg|gif|bmp|tiff)" withString:@"@2x.$2"];
    NSString* path = [WSIResource PathOf:retina];
    if ([NSDirectory fileReadable:path])
        return retina;
    return file;
}

@end

WSI_END_OBJC
