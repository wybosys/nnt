
# ifndef __NNT_CORE_RESOURCE_FB520FEAA36744E8ABD3957088F9B450_H_INCLUDED
# define __NNT_CORE_RESOURCE_FB520FEAA36744E8ABD3957088F9B450_H_INCLUDED

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

@interface NNTResource : NNTObject

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

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX

class Resource
{
public:
    
    static bool IsExist(NSString* tgt);
    static core::string PathOf(NSString* tgt);
    static core::string PathOf(core::string const& tgt);
    
};

NNT_END_HEADER_CXX

# endif

# endif

# endif