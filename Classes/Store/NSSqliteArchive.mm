
# import "Core.h"
# import <sqlite/sqlite3.h>
//# import <sqlite/sqlite3ext.h>
# import "NSSqliteArchive.h"

NNT_BEGIN_OBJC

@interface _NSInteger : NSObject @end @implementation _NSInteger @end
@interface _NSFloat : NSObject @end @implementation _NSFloat @end

@interface NSSqliteArchive ()

@property (nonatomic, copy) NSString* tableName;

@end

@implementation NSSqliteArchive

@synthesize sqlite = _db, tableName = _tablename;

- (id)init {
    self = [super init];
    
    sqlite3_initialize();
    
    self.tableName = @"data";
    
    return self;
}

- (void)dealloc {
    [self close];
    
    sqlite3_shutdown();
    
    [super dealloc];
}

- (void)close {
    if (_db) {
        sqlite3_close(_db);
        _db = NULL;
    }
}

- (id)initWithDbname:(NSString *)name {
    self = [self init];
    
    NSURL* dir = NNTDirectoryCreateWithType(@"nnt.archive", NSAppTempDirectory);
    dir = [dir URLByAppendingPathComponent:[NSString stringWithFormat:@"%@.db", name]];
    
    char const* file = [[dir relativePath] cStringUsingEncoding:NSUTF8StringEncoding];
    int flag = SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE;
    int sta = sqlite3_open_v2(file, &_db, flag, NULL);
    if (sta != SQLITE_OK) {
        [self release];
        return nil;
    }

    return self;
}

- (id)initWithDbname:(NSString *)name tableName:(NSString *)table {
    self = [self init];
    self.tableName = table;
    
    NSURL* dir = NNTDirectoryCreateWithType(@"nnt.archive", NSAppTempDirectory);
    dir = [dir URLByAppendingPathComponent:[NSString stringWithFormat:@"%@.db", name]];
    
    char const* file = [[dir relativePath] cStringUsingEncoding:NSUTF8StringEncoding];
    int flag = SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE;
    int sta = sqlite3_open_v2(file, &_db, flag, NULL);
    if (sta != SQLITE_OK) {
        [self release];
        return nil;
    }
    
    return self;
}

- (id)initWithFile:(NSString*)name {
    self = [self init];
    
    char const* file = [name cStringUsingEncoding:NSUTF8StringEncoding];
    int flag = SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE;
    int sta = sqlite3_open_v2(file, &_db, flag, NULL);
    if (sta != SQLITE_OK) {
        [self release];
        return nil;
    }
    
    return self;
}

- (void)dropTable {
    ::std::string tbl = [_tablename cStringUsingEncoding:NSUTF8StringEncoding];
    ::std::string cmd = "select * from sqlite_master where type='table' and name='" + tbl + "'";
    sqlite3_stmt *stmt;
    sqlite3_prepare(_db, cmd.c_str(), cmd.length(), &stmt, NULL);
    sqlite3_step(stmt);
    int exist = sqlite3_data_count(stmt);
    sqlite3_finalize(stmt);
    if (exist) {
        cmd = "drop table " + tbl;
        sqlite3_exec(_db, cmd.c_str(), NULL, NULL, NULL);
    }
}

- (void)createTable:(NSArray*)arr {
    NSMutableDictionary* fields = [[NSMutableDictionary alloc] init];
    for (NSDictionary* each in arr) {
        if ([each isKindOfClass:[NSDictionary class]] == NO)
            continue;
        for (id key in each.allKeys) {
            if ([key isKindOfClass:[NSString class]] == NO)
                continue;
            Class cls = [fields objectForKey:key];
            id val = [each objectForKey:key];
            Class ccls = [val class];
            if (cls == nil) {
                if (cls == [NSNumber class]) {
                    ::std::string ot = ((NSNumber*)val).objCType;
                    if (ot == @encode(int) ||
                        ot == @encode(unsigned int) ||
                        ot == @encode(short) ||
                        ot == @encode(unsigned short) ||
                        ot == @encode(long) ||
                        ot == @encode(unsigned long)) {
                        ccls = [_NSInteger class];
                    } else if (ot == @encode(float) ||
                               ot == @encode(double)) {
                        ccls = [_NSFloat class];
                    } else {
                        trace_msg(@"warning: skip unknown fields");
                    }
                }
                [fields setObject:ccls forKey:key];
            } else {
                if (cls != ccls) {
                    trace_msg(@"warning: difference fields");
                    continue;
                }
            }
        }
    }
    ::std::string tbl = [_tablename cStringUsingEncoding:NSUTF8StringEncoding];
    ::std::string cmd = "create table " + tbl;
    if (fields.count) {
        cmd += " (";
        
        // create id filed.
        cmd += "_id_ integer primary key autoincrement ";
        
        for (NSString* key in fields.allKeys) {
            Class cls = [fields objectForKey:key];
            char const* fld_name = [key cStringUsingEncoding:NSUTF8StringEncoding];
            
            cmd += ", ";
            cmd += fld_name;
            cmd += " ";
            
            if (cls == [NSString class] ||
                cls == [[NSString string] class]) {
                cmd += "text";
            } else if (cls == [_NSInteger class]) {
                cmd += "integer";
            } else if (cls == [_NSFloat class]) {
                cmd += "real";
            }
            
        }
        
        cmd += ")";
    }
    [fields release];
    
    sqlite3_exec(_db, cmd.c_str(), NULL, NULL, NULL);
}

- (BOOL)insert:(NSDictionary*)dict {
    ::std::string tbl = [_tablename cStringUsingEncoding:NSUTF8StringEncoding];
    ::std::string cmd = "insert into " + tbl + " ";
    ::std::string fields = "(";
    ::std::string params = "(";
    
    int count = 0;
    for (NSString* key in dict.allKeys) {
        if ([key isKindOfClass:[NSString class]] == NO)
            continue;

        if (count != 0) {
            fields += ", ";
            params += ", ";
        }
        ++count;
        
        char const* fld_name = [key cStringUsingEncoding:NSUTF8StringEncoding];
        fields += fld_name;
        
        ::std::stringstream ss;
        ss << count;
        params += ":" + ss.str();
    }
    
    fields += ")";
    params += ")";
    
    cmd += fields;
    cmd += " values ";
    cmd += params;
    
    // bind sql.
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(_db, cmd.c_str(), cmd.length(), &stmt, NULL);
    if (stmt == NULL)
        return NO;
    
    count = 0;
    for (NSString* key in dict.allKeys) {
        if ([key isKindOfClass:[NSString class]] == NO)
            continue;
        
        ++count;
        
        id val = [dict objectForKey:key];
        if ([val isKindOfClass:[NSString class]] ||
            [val isKindOfClass:[[NSString string] class]]) {
            char const* str = [val cStringUsingEncoding:NSUTF8StringEncoding];
            sqlite3_bind_text(stmt, count, str, strlen(str), NULL);
        } else if ([val isKindOfClass:[NSNumber class]]) {
            ::std::string ot = ((NSNumber*)val).objCType;
            if (ot == @encode(int) ||
                ot == @encode(unsigned int) ||
                ot == @encode(short) ||
                ot == @encode(unsigned short) ||
                ot == @encode(long) ||
                ot == @encode(unsigned long)) {
                sqlite3_bind_int(stmt, count, ((NSNumber*)val).intValue);
            } else if (ot == @encode(float) ||
                       ot == @encode(double)) {
                sqlite3_bind_double(stmt, count, ((NSNumber*)val).doubleValue);
            }
        }
    }
    
    BOOL suc = SQLITE_FAIL != sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return suc;
}

- (BOOL)archive:(NSArray *)arr {
    // delete old table.
    [self dropTable];
    
    // create new table.
    [self createTable:arr];
    
    // insert record.
    for (NSDictionary* each in arr) {
        if ([each isKindOfClass:[NSDictionary class]] == NO)
            continue;
        
        [self insert:each];
    }
    
    return YES;
}

- (NSArray*)unarchive {
    NSMutableArray* ret = [NSMutableArray array];
    
    ::std::string tbl = [_tablename cStringUsingEncoding:NSUTF8StringEncoding];
    ::std::string cmd = "select * from " + tbl;
    sqlite3_stmt* stmt = NULL;
    sqlite3_prepare_v2(_db, cmd.c_str(), cmd.length(), &stmt, NULL);
    if (stmt == NULL)
        return nil;
    
    while (SQLITE_ROW == sqlite3_step(stmt)) {
        int const cnt_cols = sqlite3_column_count(stmt);
        NSMutableDictionary* dict = [[NSMutableDictionary alloc] initWithCapacity:cnt_cols];
        
        for (int i = 0; i < cnt_cols; ++i) {
            int sct = sqlite3_column_type(stmt, i);
            char const* fld_name = sqlite3_column_name(stmt, i);
            NSString* key = [[NSString alloc] initWithCString:fld_name encoding:NSUTF8StringEncoding];
            
            id val = nil;
            switch (sct)
            {
                case SQLITE_TEXT: {
                    char const* str = (char const*)sqlite3_column_text(stmt, i);
                    val = [[NSString alloc] initWithCString:str encoding:NSUTF8StringEncoding];
                } break;
                case SQLITE_INTEGER: {
                    val = [[NSNumber alloc] initWithInt:sqlite3_column_int(stmt, i)];
                } break;
                case SQLITE_FLOAT: {
                    val = [[NSNumber alloc] initWithDouble:sqlite3_column_double(stmt, i)];
                } break;
            }
            [dict setObject:val forKey:key];
            [val release];
            
            [key release];
        }
        
        [ret addObject:dict];
        [dict release];
    }
    
    return ret;
}

- (NSDictionary*)query:(NSDictionary*)item {
    ::std::string tbl = [_tablename cStringUsingEncoding:NSUTF8StringEncoding];
    ::std::string cmd = "select * from " + tbl + " where ";
    
    int count = 0;
    for (NSString* key in item.allKeys) {
        if ([key isKindOfClass:[NSString class]] == NO)
            continue;
        
        if (count != 0)
            cmd += " and ";
        ++count;
        
        char const* fld_name = [key cStringUsingEncoding:NSUTF8StringEncoding];
        cmd += fld_name;
        
        cmd += "=";
        
        ::std::stringstream ss;
        ss << count;
        cmd += ":" + ss.str();
    }
    
    // bind sql.
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(_db, cmd.c_str(), cmd.length(), &stmt, NULL);
    if (stmt == NULL)
        return nil;
    
    count = 0;
    for (NSString* key in item.allKeys) {
        if ([key isKindOfClass:[NSString class]] == NO)
            continue;
        
        ++count;
        
        id val = [item objectForKey:key];
        if ([val isKindOfClass:[NSString class]] ||
            [val isKindOfClass:[[NSString string] class]]) {
            char const* str = [val cStringUsingEncoding:NSUTF8StringEncoding];
            sqlite3_bind_text(stmt, count, str, strlen(str), NULL);
        } else if ([val isKindOfClass:[NSNumber class]]) {
            ::std::string ot = ((NSNumber*)val).objCType;
            if (ot == @encode(int) ||
                ot == @encode(unsigned int) ||
                ot == @encode(short) ||
                ot == @encode(unsigned short) ||
                ot == @encode(long) ||
                ot == @encode(unsigned long)) {
                sqlite3_bind_int(stmt, count, ((NSNumber*)val).intValue);
            } else if (ot == @encode(float) ||
                       ot == @encode(double)) {
                sqlite3_bind_double(stmt, count, ((NSNumber*)val).doubleValue);
            }
        }
    }
    
    NSMutableDictionary* ret = [NSMutableDictionary dictionary];
    int const cnt_cols = sqlite3_column_count(stmt);
    if (SQLITE_ROW == sqlite3_step(stmt)) {
        for (int i = 0; i < cnt_cols; ++i) {
            int sct = sqlite3_column_type(stmt, i);
            char const* fld_name = sqlite3_column_name(stmt, i);
            NSString* key = [[NSString alloc] initWithCString:fld_name encoding:NSUTF8StringEncoding];
            
            id val = nil;
            switch (sct)
            {
                case SQLITE_TEXT: {
                    char const* str = (char const*)sqlite3_column_text(stmt, i);
                    val = [[NSString alloc] initWithCString:str encoding:NSUTF8StringEncoding];
                } break;
                case SQLITE_INTEGER: {
                    val = [[NSNumber alloc] initWithInt:sqlite3_column_int(stmt, i)];
                } break;
                case SQLITE_FLOAT: {
                    val = [[NSNumber alloc] initWithDouble:sqlite3_column_double(stmt, i)];
                } break;
            }
            [ret setObject:val forKey:key];
            [val release];
            
            [key release];
        }
    }
    sqlite3_finalize(stmt);
    
    return ret;
}

- (BOOL)delete:(NSDictionary*)item {
    ::std::string tbl = [_tablename cStringUsingEncoding:NSUTF8StringEncoding];
    ::std::string cmd = "delete from " + tbl + " where ";
    
    int count = 0;
    for (NSString* key in item.allKeys) {
        if ([key isKindOfClass:[NSString class]] == NO)
            continue;
        
        if (count != 0)
            cmd += " and ";
        ++count;
        
        char const* fld_name = [key cStringUsingEncoding:NSUTF8StringEncoding];
        cmd += fld_name;
        
        cmd += "=";
        
        ::std::stringstream ss;
        ss << count;
        cmd += ":" + ss.str();
    }
    
    // bind sql.
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(_db, cmd.c_str(), cmd.length(), &stmt, NULL);
    if (stmt == NULL)
        return nil;
    
    count = 0;
    for (NSString* key in item.allKeys) {
        if ([key isKindOfClass:[NSString class]] == NO)
            continue;
        
        ++count;
        
        id val = [item objectForKey:key];
        if ([val isKindOfClass:[NSString class]] ||
            [val isKindOfClass:[[NSString string] class]]) {
            char const* str = [val cStringUsingEncoding:NSUTF8StringEncoding];
            sqlite3_bind_text(stmt, count, str, strlen(str), NULL);
        } else if ([val isKindOfClass:[NSNumber class]]) {
            ::std::string ot = ((NSNumber*)val).objCType;
            if (ot == @encode(int) ||
                ot == @encode(unsigned int) ||
                ot == @encode(short) ||
                ot == @encode(unsigned short) ||
                ot == @encode(long) ||
                ot == @encode(unsigned long)) {
                sqlite3_bind_int(stmt, count, ((NSNumber*)val).intValue);
            } else if (ot == @encode(float) ||
                       ot == @encode(double)) {
                sqlite3_bind_double(stmt, count, ((NSNumber*)val).doubleValue);
            }
        }
    }

    BOOL suc = SQLITE_FAIL != sqlite3_step(stmt);
    
    sqlite3_finalize(stmt);
    
    return suc;
}

- (BOOL)update:(NSDictionary*)from forData:(NSDictionary*)to {
    ::std::string tbl = [_tablename cStringUsingEncoding:NSUTF8StringEncoding];
    ::std::string cmd = "update " + tbl + " set ";
    
    int count = 0;
    for (NSString* key in to.allKeys) {
        if ([key isKindOfClass:[NSString class]] == NO)
            continue;
        
        if (count != 0)
            cmd += ", ";
        ++count;
        
        char const* fld_name = [key cStringUsingEncoding:NSUTF8StringEncoding];
        cmd += fld_name;
        
        cmd += "=";
        
        ::std::stringstream ss;
        ss << count;
        cmd += ":" + ss.str();
    }
    
    cmd += " where ";
    
    int tcount = 0;
    for (NSString* key in from.allKeys) {
        if ([key isKindOfClass:[NSString class]] == NO)
            continue;
        
        if (tcount != 0)
            cmd += " and ";
        ++count;
        ++tcount;
        
        char const* fld_name = [key cStringUsingEncoding:NSUTF8StringEncoding];
        cmd += fld_name;
        
        cmd += "=";
        
        ::std::stringstream ss;
        ss << count;
        cmd += ":" + ss.str();
    }
    
    // bind sql.
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(_db, cmd.c_str(), cmd.length(), &stmt, NULL);
    if (stmt == NULL)
        return nil;
    
    count = 0;
    
    for (NSString* key in to.allKeys) {
        if ([key isKindOfClass:[NSString class]] == NO)
            continue;
        
        ++count;
        
        id val = [to objectForKey:key];
        if ([val isKindOfClass:[NSString class]] ||
            [val isKindOfClass:[[NSString string] class]]) {
            char const* str = [val cStringUsingEncoding:NSUTF8StringEncoding];
            sqlite3_bind_text(stmt, count, str, strlen(str), NULL);
        } else if ([val isKindOfClass:[NSNumber class]]) {
            ::std::string ot = ((NSNumber*)val).objCType;
            if (ot == @encode(int) ||
                ot == @encode(unsigned int) ||
                ot == @encode(short) ||
                ot == @encode(unsigned short) ||
                ot == @encode(long) ||
                ot == @encode(unsigned long)) {
                sqlite3_bind_int(stmt, count, ((NSNumber*)val).intValue);
            } else if (ot == @encode(float) ||
                       ot == @encode(double)) {
                sqlite3_bind_double(stmt, count, ((NSNumber*)val).doubleValue);
            }
        }
    }
    
    for (NSString* key in from.allKeys) {
        if ([key isKindOfClass:[NSString class]] == NO)
            continue;
        
        ++count;
        
        id val = [from objectForKey:key];
        if ([val isKindOfClass:[NSString class]] ||
            [val isKindOfClass:[[NSString string] class]]) {
            char const* str = [val cStringUsingEncoding:NSUTF8StringEncoding];
            sqlite3_bind_text(stmt, count, str, strlen(str), NULL);
        } else if ([val isKindOfClass:[NSNumber class]]) {
            ::std::string ot = ((NSNumber*)val).objCType;
            if (ot == @encode(int) ||
                ot == @encode(unsigned int) ||
                ot == @encode(short) ||
                ot == @encode(unsigned short) ||
                ot == @encode(long) ||
                ot == @encode(unsigned long)) {
                sqlite3_bind_int(stmt, count, ((NSNumber*)val).intValue);
            } else if (ot == @encode(float) ||
                       ot == @encode(double)) {
                sqlite3_bind_double(stmt, count, ((NSNumber*)val).doubleValue);
            }
        }
    }

    BOOL suc = SQLITE_FAIL != sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    return suc;
}

@end

NNT_END_OBJC
