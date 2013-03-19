
# import "Core.h"
# import "Directory+NNT.h"
# import "App.h"
# import "Resource+NNT.h"

NNT_BEGIN_OBJC

NNT_EXTERN NSURL *NNTDirectoryTouchWithType(NSString* path, NNTDirectoryType type) {
    NSFileManager *fs_mgr = [NSFileManager defaultManager];    
    NSString *str_tgt = @"";
    switch (NNTDirectoryTypeMajor(type)) {
        default: {
            dthrow([NSException exceptionWithName:@"type unknown" reason:@"unknown directory type." userInfo:nil]);
        } break;
            
        case NNTDirectoryTypeNone: {
            str_tgt = path;
            if ([str_tgt isEqualToString:@""]) {
                return [NSURL URLWithString:@"/"];
            }
        } break;
            
        case NNTDirectoryTypeSystem: {
            uint min_type = NNTDirectoryTypeMinor(type);
            uint nnt_type = NNTDirectoryTypeWsiMinor(type);
            
            /*
            if (nnt_type && !min_type) {
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
            
            if (nnt_type) {
                
# ifdef NNT_TARGET_MAC
                str_tgt = [str_tgt stringByAppendingPathComponent:@"nnt"];
                str_tgt = [str_tgt stringByAppendingPathComponent:[NNTApplication shared].applicationIdentity];
# endif
                str_tgt = [str_tgt stringByAppendingPathComponent:@"var"];
                
                if (MASK_CHECK(NSTemplateDirectory, nnt_type)) {
                    str_tgt = [str_tgt stringByAppendingPathComponent:@"tmp"];
                }
                else if (MASK_CHECK(NSVariableDirectory, nnt_type)) {
                    PASS;
                }
                else if (MASK_CHECK(NSLogDirectory, nnt_type)) {
                    str_tgt = [str_tgt stringByAppendingPathComponent:@"log"];
                }
            }
            
            str_tgt = [str_tgt stringByAppendingPathComponent:path];
            
        } break;
            
        case NNTDirectoryTypeBundle:
        case NNTDirectoryTypeBundleWritable:
# ifdef NNT_JAILBREAK
        case NNTDirectoryTypeTemplate:
# endif
        {
            NSString *str = [[NSBundle mainBundle] bundlePath];
            
# ifdef NNT_JAILBREAK
            if (NNTDirectoryTypeMajor(type) == NNTDirectoryTypeTemplate) {
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

NSURL *NNTDirectoryCreateWithType(NSString *path, NNTDirectoryType type) {
    NSFileManager *fs_mgr = [NSFileManager defaultManager];
    NSString *str_tgt = @"";
    switch (NNTDirectoryTypeMajor(type)) {
        default: {
            dthrow([NSException exceptionWithName:@"type unknown" reason:@"unknown directory type." userInfo:nil]);
        } break;
            
        case NNTDirectoryTypeNone: {
            str_tgt = path;
            if ([str_tgt isEqualToString:@""]) {
                return [NSURL URLWithString:@"/"];
            }
        } break;

        case NNTDirectoryTypeSystem: {
            uint min_type = NNTDirectoryTypeMinor(type);
            uint nnt_type = NNTDirectoryTypeWsiMinor(type);
            
            /*
            if (nnt_type && !min_type) {
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
            
            if (nnt_type) {
                
# ifdef NNT_TARGET_MAC
                
                str_tgt = [str_tgt stringByAppendingPathComponent:@"nnt"];
                str_tgt = [str_tgt stringByAppendingPathComponent:[NNTApplication shared].applicationIdentity];
                
# endif         
                
                // add 'var' directory.
                str_tgt = [str_tgt stringByAppendingPathComponent:@"var"];
                
                // var's sub directory.
                if (MASK_CHECK(NSTemplateDirectory, nnt_type)) {
                    str_tgt = [str_tgt stringByAppendingPathComponent:@"tmp"];
                }
                else if (MASK_CHECK(NSVariableDirectory, nnt_type)) {
                    PASS;
                }
                else if (MASK_CHECK(NSLogDirectory, nnt_type)) {
                    str_tgt = [str_tgt stringByAppendingPathComponent:@"log"];
                }
            }
            
            str_tgt = [str_tgt stringByAppendingPathComponent:path];
            
        } break;
            
        case NNTDirectoryTypeBundle:
        case NNTDirectoryTypeBundleWritable:
# ifdef NNT_JAILBREAK
        case NNTDirectoryTypeTemplate: 
# endif
        {
            NSString *str = [[NSBundle mainBundle] bundlePath];
            
# ifdef NNT_JAILBREAK
            if (NNTDirectoryTypeMajor(type) == NNTDirectoryTypeTemplate) {
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

NSURL *NNTFileTouchWithType(NSString* path, NNTDirectoryType type)
{
    NSURL* url = NULL;
    if (type == NNTDirectoryTypeAbsolute)
    {
        url = [NSURL fileURLWithPath:path];
    }
    else
    {
        url = NNTDirectoryCreateWithType(@"", type);
        if (type == NNTDirectoryTypeBundleWritable)
        {
            NSFileManager *fs_mgr = [NSFileManager defaultManager];
            NSURL* tgt = NNTDirectoryCreateWithType(@"", (NSVariableDirectory | NNTDirectoryTypeSystem));
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

BOOL NNTDirectoryRemoveWithType(NSString* path, NNTDirectoryType type)
{
    NSURL* url = NNTDirectoryTouchWithType(path, type);
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
    NSString* path = [NNTResource PathOf:retina];
    if ([NSDirectory fileReadable:path])
        return retina;
    return file;
}

@end

NNT_END_OBJC
