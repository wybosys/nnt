
# ifndef __WSI_CORE_RESOURCE_FB520FEAA36744E8ABD3957088F9B450_H_INCLUDED
# define __WSI_CORE_RESOURCE_FB520FEAA36744E8ABD3957088F9B450_H_INCLUDED

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_OBJC

@interface WSIResource : WSIObject

//! is exist in bundle.
+ (BOOL)IsExist:(NSString*)tgt;

//! get path in bundle.
+ (NSString *)PathOf:(NSString*)tgt;

//! read content in bundle.
+ (NSString *)ContentOf:(NSString*)tgt inBundle:(BOOL)inBundle;
+ (NSString *)ContentOf:(NSString*)tgt;

//! read data in bundle.
+ (NSData *)DataOf:(NSString*)tgt inBundle:(BOOL)inBundle;
+ (NSData *)DataOf:(NSString*)tgt;

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX

class Resource
{
public:
    
    static bool IsExist(NSString* tgt);
    static core::string PathOf(NSString* tgt);
    static core::string PathOf(core::string const& tgt);
    
};

WSI_END_HEADER_CXX

# endif

# endif

# endif