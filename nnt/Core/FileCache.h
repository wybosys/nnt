
# ifndef __NNT_CORE_FILECACHE_02C2CCCD4CB9495FBD2AF30387725DD2_H_INCLUDED
# define __NNT_CORE_FILECACHE_02C2CCCD4CB9495FBD2AF30387725DD2_H_INCLUDED

# import "Directory+NNT.h"
# import "AbstractCache.h"

NNT_BEGIN_HEADER_OBJC

@interface AbstractUrlCache : AbstractCache {    
    NSURL *url;
}

@property (nonatomic, copy) NSURL *url;

//! init
- (id)initWithPath:(NSString*)path type:(NNTDirectoryType)type;

@end

NNTDECL_PRIVATE_HEAD(FileCache);

@interface FileCache : AbstractUrlCache {    
    
    //! index file.
    NSString* indexFile;
    
    NNTDECL_PRIVATE(FileCache);
}

@property (nonatomic, copy) NSString* indexFile;

@end

NNT_END_HEADER_OBJC

# endif