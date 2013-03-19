
# ifndef __WSI_CORE_FILECACHE_02C2CCCD4CB9495FBD2AF30387725DD2_H_INCLUDED
# define __WSI_CORE_FILECACHE_02C2CCCD4CB9495FBD2AF30387725DD2_H_INCLUDED

# import "Directory+WSI.h"
# import "AbstractCache.h"

WSI_BEGIN_HEADER_OBJC

@interface AbstractUrlCache : AbstractCache {    
    NSURL *url;
}

@property (nonatomic, copy) NSURL *url;

//! init
- (id)initWithPath:(NSString*)path type:(WSIDirectoryType)type;

@end

WSIDECL_PRIVATE_HEAD(FileCache);

@interface FileCache : AbstractUrlCache {    
    
    //! index file.
    NSString* indexFile;
    
    WSIDECL_PRIVATE(FileCache);
}

@property (nonatomic, copy) NSString* indexFile;

@end

WSI_END_HEADER_OBJC

# endif