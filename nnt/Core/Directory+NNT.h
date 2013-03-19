
# ifndef __NNT_CORE_DIRECTORY_6F36C0B7105A44298C01CA30B9C4FBCB_H_INCLUDED
# define __NNT_CORE_DIRECTORY_6F36C0B7105A44298C01CA30B9C4FBCB_H_INCLUDED

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

enum _NNTDirectoryType {
    
    //! absolute directory.
    NNTDirectoryTypeNone = 0x10000000, 
    NNTDirectoryTypeAbsolute = NNTDirectoryTypeNone,
    NNTDirectoryTypeBundle = 0x20000000, 
    
    //! bundle directory of app.
    NNTDirectoryTypeBundleWritable = 0x30000000,
    
# ifdef NNT_JAILBREAK        
    
    //! template directory of system in nnt.
    NNTDirectoryTypeTemplate = 0x40000000, 
    
# endif
    
    //! template directory.
    NSTemplateDirectory = 0x1000000,
    
    //! variable directory.
    NSVariableDirectory = 0x2000000, 
    
    //! log directory.
    NSLogDirectory = 0x3000000,
    
    //! all directories provide by apple of user, the marker will force use NSSearchPathDirectory fuction to get full path of target directory.
    NNTDirectoryTypeSystem = 0x40000000, 
    
    // other.
    NSAppTempDirectory = NSTemplateDirectory | NNTDirectoryTypeSystem,
    NSAppVarDirectory = NSVariableDirectory | NNTDirectoryTypeSystem,
    NSAppLogDirectory = NSLogDirectory | NNTDirectoryTypeSystem,
    
};

typedef uint NNTDirectoryType;

# define NNTDirectoryTypeMajor(type) \
    ((type) & 0xf0000000)

# define NNTDirectoryTypeNNTMinor(type) \
    ((type) & 0xf000000)

# define NNTDirectoryTypeMinor(type) \
    ((type) & 0xffff)

//! create a directory safely.
NNT_EXTERN NSURL *NNTDirectoryCreateWithType(NSString *path, NNTDirectoryType type);

//! remove a directory.
NNT_EXTERN BOOL NNTDirectoryRemoveWithType(NSString* path, NNTDirectoryType type);

//! touch directory.
NNT_EXTERN NSURL *NNTDirectoryTouchWithType(NSString*, NNTDirectoryType);

//! touch a file safely.
NNT_EXTERN NSURL *NNTFileTouchWithType(NSString* path, NNTDirectoryType type);

//! enum a directory.

enum {
    NSDirectoryEnumRegular = 0x1,
    NSDirectoryEnumDirectory = 0x2,
    NSDirectoryEnumSkipInvisible = 0x4,
};
typedef uint NSDirectoryEnum;

@interface NSDirectory : NNTObject {
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

NNT_END_HEADER_OBJC

# endif

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(core)

NNTAPI(core::string) dot(core::string const&);
NNTAPI(core::string) dotdot(core::string const&);
NNTAPI(bool) mkdir(core::string const&);
NNTAPI(bool) mkdirs(core::string const&);

# ifdef NNT_OBJC

inline_impl ns::URL mkdir(ns::String const& path, NNTDirectoryType type)
{
    return NNTDirectoryCreateWithType(path, type);
}

inline_impl bool rmdir(ns::String const& path, NNTDirectoryType type)
{
    return NNTDirectoryRemoveWithType(path, type);
}

inline_impl ns::URL touch(ns::String const& path, NNTDirectoryType type)
{
    return NNTFileTouchWithType(path, type);
}

# endif

NNT_END_NS

# ifdef NNT_OBJC

NNT_BEGIN_NS(ns)

class Directory
{
public:
    
    static ns::URL Variable(ns::String const& str)
    {
        return NNTDirectoryTouchWithType(str, NSAppVarDirectory);
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

NNT_END_NS

# endif

NNT_END_HEADER_CXX

# endif

# endif
