
# ifndef __WSI_TRAIL_CONTACTSTORE_3FBEDDB72D76432880FC9AD460D1DF14_H_INCLUDED
# define __WSI_TRAIL_CONTACTSTORE_3FBEDDB72D76432880FC9AD460D1DF14_H_INCLUDED

# import "WSIContact.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(WSISqlite);

@interface WSIAddressBookStore : WSIObject {
    WSISqlite* db;
}

WSIDECL_SINGLETON(WSIAddressBookStore);

//! refresh.
- (void)refresh;

//! search.
- (NSArray*)search:(NSString*)query;

@end

WSI_END_HEADER_OBJC

# endif