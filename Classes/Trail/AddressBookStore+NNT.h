
# ifndef __NNT_TRAIL_CONTACTSTORE_3FBEDDB72D76432880FC9AD460D1DF14_H_INCLUDED
# define __NNT_TRAIL_CONTACTSTORE_3FBEDDB72D76432880FC9AD460D1DF14_H_INCLUDED

# import "Contact+NNT.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(NNTSqlite);

@interface NNTAddressBookStore : NNTObject {
    NNTSqlite* db;
}

NNTDECL_SINGLETON(NNTAddressBookStore);

//! refresh.
- (void)refresh;

//! search.
- (NSArray*)search:(NSString*)query;

@end

NNT_END_HEADER_OBJC

# endif