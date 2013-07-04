
# ifndef __NNT_STORE_SQLITEARCHIVE_CAB71D81F99A4B08950D07F7C4CEBCAD_H_INCLUDED
# define __NNT_STORE_SQLITEARCHIVE_CAB71D81F99A4B08950D07F7C4CEBCAD_H_INCLUDED

# ifdef NNT_OBJC

# ifndef SQLITE_VERSION

typedef struct {} *sqlite3;

# endif

NNT_BEGIN_HEADER_OBJC

@interface NSSqliteArchive : NSObject {
    sqlite3* _db;
    NSString* _tablename;
}

@property (nonatomic, readonly) sqlite3* sqlite;
@property (nonatomic, copy, readonly) NSString* tableName;
@property (nonatomic, copy) NSString* cryptoKey;

- (id)initWithDbname:(NSString*)name;
- (id)initWithDbname:(NSString*)name tableName:(NSString*)table;
- (id)initWithFile:(NSString*)name;

- (BOOL)archive:(NSArray*)arr;
- (NSArray*)unarchive;
- (NSDictionary*)query:(NSDictionary*)item;
- (BOOL)delete:(NSDictionary*)item;
- (BOOL)update:(NSDictionary*)item forData:(NSDictionary*)data;
- (BOOL)insert:(NSDictionary*)item;

@end

NNT_END_HEADER_OBJC

# endif

# endif
