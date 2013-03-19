
# import "Core.h"
# import "WSISqlite.h"
# include <sqlite3.h>

WSI_BEGIN_OBJC

WSIDECL_PRIVATE_BEGIN(WSISqlite, WSIObject)
{
    sqlite3 *db;
}

@property (nonatomic, assign) sqlite3 *db;

- (void)close;
- (BOOL)testQuery:(uint)code;
- (id)convertColValueToNS:(sqlite3_stmt*)stmt idx:(uint)idx;

WSIDECL_PRIVATE_IMPL(WSISqlite)

@synthesize db;

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    [self close];
    [super dealloc];
}

- (void)close {
    if (db) {
        sqlite3_close(db);
        db = 0;
    }
}

- (BOOL)testQuery:(uint)code {
    BOOL suc = code == SQLITE_OK;
    if (!suc) {
        [d_owner errmsg];
    }
    return suc;
}

- (id)convertColValueToNS:(sqlite3_stmt*)stmt idx:(uint)idx {
    id ret = nil;
    int type = sqlite3_column_type(stmt, idx);
    switch (type) {
        case SQLITE_INTEGER: {
            int val = sqlite3_column_int(stmt, idx);
            ret = [NSNumber numberWithInt:val];
        } break;
        case SQLITE_FLOAT: {
            double val = sqlite3_column_double(stmt, idx);
            ret = [NSNumber numberWithDouble:val];
        } break;
        case SQLITE_TEXT: {
            uchar const* val = sqlite3_column_text(stmt, idx);
            ret = [NSString stringWithUTF8String:(char*)val];
        } break;
        default: {
            ret = [NSNull null];
        } break;
    }
    return ret;
}

WSIDECL_PRIVATE_END

@implementation WSISqlite

- (id)init {
    self = [super init];
    WSIDECL_PRIVATE_INIT(WSISqlite);
    return self;
}

- (void)dealloc {
    WSIDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (BOOL)openDbWithUrl:(NSURL *)url {
    // open
    sqlite3 *db = NULL;
    
    NSString* objcpath = url.relativePath;
    char const* path = objcpath.UTF8String;
    
    if (![d_ptr testQuery:sqlite3_open(path, &db)]) {
        sqlite3_close(db);
        return NO;
    }
    
    [d_ptr close];
    d_ptr.db = db;
    return YES;
}

- (DBMSqlDatatable*)exec_ansi:(char const *)sql params:(NSArray *)param {
    return [self exec_ansi:sql len:(uint)strlen(sql) params:param];
}

- (DBMSqlDatatable*)exec_ansi:(char const *)sql {
    return [self exec_ansi:sql len:(uint)strlen(sql)];
}

- (DBMSqlDatatable*)exec_ansi:(char const *)sql len:(usize)len params:(NSArray *)params {
    DBMSqlDatatable *ret = nil;
    sqlite3_stmt *stmt = NULL;
    char const* tail = NULL;
    int errid = 0;
    
    // lock for single thread.
    [d_ptr lock];
    
    // open sql.
    if (params) {
        if (NO == [d_ptr testQuery:sqlite3_prepare(d_ptr.db, sql, (int)len, &stmt, &tail)]) {
            [d_ptr unlock];
            return ret;
        }
        
        // bind param.
        // use DBMS SQL PARAM to pass.
        for (id each in params) {
            DBMSqlParam* param = nil;
            if ([each isKindOfClass:[DBMSqlParam class]]) {
                param = [(DBMSqlParam*)each retain];
            } else {
                NSPair* pair = (NSPair*)each;
                param = [[DBMSqlParam alloc] init];
                param.name = pair.first;
                param.type = [pair.second valueType];
                param.value = pair.second;
            }
            
            int pos = 0;
            if (param.pos != -1) {
                pos = param.pos + 1;
            } else {
                pos = sqlite3_bind_parameter_index(stmt, param.name.UTF8String);
            }

            switch (param.type) {
                default: {
                    [param release];
                    dthrow([NSException exceptionWithName:@"sqlite"
                                                   reason:@"bad_type: failed to bind unknown parameter."
                                                 userInfo:nil]);
                } break;
                case WSIValueTypeInt: case WSIValueTypeUInt:
                case WSIValueTypeChar: case WSIValueTypeUChar:
                case WSIValueTypeShort: case WSIValueTypeUShort:
                case WSIValueTypeLong: case WSIValueTypeULong: {
                    errid = sqlite3_bind_int(stmt, pos, [(NSNumber*)param.value intValue]);
                } break;
                case WSIValueTypeLongLong: case WSIValueTypeULongLong: {
                    errid = sqlite3_bind_int64(stmt, pos, [(NSNumber*)param.value longLongValue]);
                } break;
                case WSIValueTypeString: {
                    NSData *data = [(NSString*)param.value dataUsingEncoding:NSUTF8StringEncoding];
                    errid = sqlite3_bind_text(stmt, pos, (char const*)[data bytes], (int)[data length], nil);
                } break;
                case WSIValueTypeFloat: case WSIValueTypeDouble: {
                    errid = sqlite3_bind_double(stmt, pos, [(NSNumber*)param.value doubleValue]);
                } break;
            }
            if (errid != SQLITE_OK) {
                trace_msg(@"fail to bind param to sqlite.");
            }
            
            [param release];
        }
        
    } else {
        if (NO == [d_ptr testQuery:sqlite3_prepare(d_ptr.db, sql, (int)len, &stmt, &tail)]) {
            [d_ptr unlock];
            return ret;
        }
    }

    // get data.
    uint suc = sqlite3_step(stmt);
    
    if (suc == SQLITE_ERROR) {
        trace_msg(@"failed to query with SQLite.");
    }
    else if (suc == SQLITE_ROW) {
        ret = [[[DBMSqlDatatable alloc] init] autorelease];
        // add col
        int cols = sqlite3_data_count(stmt);
        if (cols) {
            NSMutableArray *arr = [[NSMutableArray alloc] initWithCapacity:cols];
            for (int i = 0; i < cols; ++i) {           
                NSString *col_name = [NSString stringWithUTF8String:sqlite3_column_name(stmt, i)];
                [arr addObject:col_name];            
            }
            ret.cols = arr;
            [arr release];
        }
        // add rows
        NSMutableArray *rows = [[NSMutableArray alloc] init];
        do {            
            if (cols) {
                NSMutableArray *row = [[NSMutableArray alloc] initWithCapacity:cols];
                for (int i = 0; i < cols; ++i) {
                    [row addObject:[d_ptr convertColValueToNS:stmt idx:i]];
                }
                [rows addObject:row];
                [row release];
            } else {
                [rows addObject:[NSNull null]];
            }            
            suc = sqlite3_step(stmt);
        } while (suc == SQLITE_ROW);
        ret.rows = rows;
        [rows release];
    }
    
    sqlite3_finalize(stmt);
    
    // unlock.
    [d_ptr unlock];
    return ret;
}

- (DBMSqlDatatable*)exec_ansi:(char const *)sql len:(usize)len {
    return [self exec_ansi:sql len:len params:nil];
}

- (DBMSqlDatatable*)exec:(NSString *)sql params:(NSArray *)params {
    NSData *data = [sql dataUsingEncoding:NSUTF8StringEncoding];
    return [self exec_ansi:(char const*)[data bytes] len:(uint)[data length] params:params];
}

- (NSString*)errmsg {
    char const* msg = sqlite3_errmsg(d_ptr.db);
    NSString *str = [NSString stringWithUTF8String:msg];
    trace_msg(str);
    return str;
}

- (void)close {
    [d_ptr close];
}

- (bool)exist_table:(char const*)table {
    wsi::core::string sql = "SELECT COUNT(*) as TabCount FROM sqlite_master where type='table' and name='";
    sql += table;
    sql += "'";
    DBMSqlDatatable* tbl = [self exec_ansi:sql.c_str() len:sql.length()];
    wsi::ns::Number num = [tbl valueForKey:@"TabCount" row:0];
    return num != 0;
}

- (void)drop_table:(const char *)table {
    wsi::core::string sql = "drop table ";
    sql += table;
    [self exec_ansi:sql.c_str() len:sql.length()];
}

- (void)create_table:(char const*)table cols:(char const*)cols {
    wsi::core::string sql = "create table \"";
    sql += table;
    sql += "\" (";
    sql += cols;
    sql += ")";
    [self exec_ansi:sql.c_str() len:sql.length()];
}

@end

WSI_END_OBJC