
# ifndef __WSI_CORE_DIRECTORY_6F36C0B7105A44298C01CA30B9C4FBCB_H_INCLUDED
# define __WSI_CORE_DIRECTORY_6F36C0B7105A44298C01CA30B9C4FBCB_H_INCLUDED

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_OBJC

enum _WSIDirectoryType {
    
    //! absolute directory.
    WSIDirectoryTypeNone = 0x10000000, 
    WSIDirectoryTypeAbsolute = WSIDirectoryTypeNone,
    WSIDirectoryTypeBundle = 0x20000000, 
    
    //! bundle directory of app.
    WSIDirectoryTypeBundleWritable = 0x30000000,
    
# ifdef WSI_JAILBREAK        
    
    //! template directory of system in wsi.
    WSIDirectoryTypeTemplate = 0x40000000, 
    
# endif
    
    //! template directory.
    NSTemplateDirectory = 0x1000000,
    
    //! variable directory.
    NSVariableDirectory = 0x2000000, 
    
    //! log directory.
    NSLogDirectory = 0x3000000,
    
    //! all directories provide by apple of user, the marker will force use NSSearchPathDirectory fuction to get full path of target directory.
    WSIDirectoryTypeSystem = 0x40000000, 
    
    // other.
    NSAppTempDirectory = NSTemplateDirectory | WSIDirectoryTypeSystem,
    NSAppVarDirectory = NSVariableDirectory | WSIDirectoryTypeSystem,
    NSAppLogDirectory = NSLogDirectory | WSIDirectoryTypeSystem,
    
};

typedef uint WSIDirectoryType;

# define WSIDirectoryTypeMajor(type) \
    ((type) & 0xf0000000)

# define WSIDirectoryTypeWsiMinor(type) \
    ((type) & 0xf000000)

# define WSIDirectoryTypeMinor(type) \
    ((type) & 0xffff)

//! create a directory safely.
WSI_EXTERN NSURL *WSIDirectoryCreateWithType(NSString *path, WSIDirectoryType type);

//! remove a directory.
WSI_EXTERN BOOL WSIDirectoryRemoveWithType(NSString* path, WSIDirectoryType type);

//! touch directory.
WSI_EXTERN NSURL *WSIDirectoryTouchWithType(NSString*, WSIDirectoryType);

//! touch a file safely.
WSI_EXTERN NSURL *WSIFileTouchWithType(NSString* path, WSIDirectoryType type);

//! enum a directory.

enum {
    NSDirectoryEnumRegular = 0x1,
    NSDirectoryEnumDirectory = 0x2,
    NSDirectoryEnumSkipInvisible = 0x4,
};
typedef uint NSDirectoryEnum;

@interface NSDirectory : WSIObject {
    NSString* url;
    
@private
    NSFileManager* _fs_mgr;
}

@property (nonatomic, copy) NSString* url;

//! init.
- (id)initWith:(NSString*)url;

//! collect all items at url.
- (NSArray*)collect:(NSDirectoryEnum)flag;

//! is readable file.
+ (BOOL)fileReadable:(NSString*)file;

//! is writable file.
+ (BOOL)fileWritable:(NSString*)file;

//! exist;
+ (BOOL)fileExistsAtPath:(NSString *)path;
+ (BOOL)fileExistsAtPath:(NSString *)path isDirectory:(BOOL *)isDirectory;
+ (BOOL)directoryExistsAtPath:(NSString *)path;

//! retina file.
+ (NSString*)retinaImageNamed:(NSString*)file;

@end

WSI_END_HEADER_OBJC

# endif

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(core)

WSIAPI(core::string) dot(core::string const&);
WSIAPI(core::string) dotdot(core::string const&);
WSIAPI(bool) mkdir(core::string const&);
WSIAPI(bool) mkdirs(core::string const&);

# ifdef WSI_OBJC

inline_impl ns::URL mkdir(ns::String const& path, WSIDirectoryType type)
{
    return WSIDirectoryCreateWithType(path, type);
}

inline_impl bool rmdir(ns::String const& path, WSIDirectoryType type)
{
    return WSIDirectoryRemoveWithType(path, type);
}

inline_impl ns::URL touch(ns::String const& path, WSIDirectoryType type)
{
    return WSIFileTouchWithType(path, type);
}

# endif

WSI_END_NS

# ifdef WSI_OBJC

WSI_BEGIN_NS(ns)

class Directory
{
public:
    
    static ns::URL Variable(ns::String const& str)
    {
        return WSIDirectoryTouchWithType(str, NSAppVarDirectory);
    }
    
    static bool isFile(ns::String const& str)
    {
        BOOL isdir;
        BOOL suc = [NSDirectory fileExistsAtPath:str isDirectory:&isdir];
        return suc && !isdir;
    }
    
    static bool isFile(ns::URL const& url)
    {
        return Directory::isFile(url.relative_path());
    }
    
    static bool isDir(ns::String const& str)
    {
        BOOL isdir;
        BOOL suc = [NSDirectory fileExistsAtPath:str isDirectory:&isdir];
        return suc && isdir;
    }
    
    static bool isDir(ns::URL const& url)
    {
        return Directory::isDir(url.relative_path());
    }
    
};

WSI_END_NS

# endif

WSI_END_HEADER_CXX

# endif

# endif
