
# import "Core.h"
# import "WSIAddressBookStore.h"
# import "WSISqlite.h"
# import "ChineseString.h"

WSI_BEGIN_OBJC

WSI_USINGCXXNAMESPACE;

@implementation WSIAddressBookStore

WSIIMPL_SINGLETON(WSIAddressBookStore);

- (id)init {
    self = [super init];
    return self;
}

- (void)instanceInit {
    db = [[WSISqlite alloc] initWith:@"addressbook.db" type:NSAppVarDirectory];
    if ([db exist_table:"contacts"] == NO) {
        [self refresh];
    }
    
# ifdef WSI_DEBUG
    [self refresh];
# endif
}

- (void)dealloc {
    zero_release(db);
    [super dealloc];
}

- (void)refresh {
    if ([db exist_table:"contacts"]) {
        [db drop_table:"contacts"];
    }
    [db create_table:"contacts" cols:"\"id\" integer NOT NULL, \"data\" text, \"simple\" text, PRIMARY KEY(\"id\")"];
    
    // add data.
    WSIAddressBook* addressBook = [[WSIAddressBook alloc] init];
    [addressBook refresh];
    
    int idx = 0;
    for (WSIPerson* person in addressBook.contacts) {
        ns::MutableDictionary dict;
        dict[@"firstname"] = (ignore_null)person.firstName;
        dict[@"lastname"] = (ignore_null)person.lastName;
        dict[@"fullname"] = (ignore_null)person.fullName;
        dict[@"fullname::pinyin"] = (ignore_null)[ChineseString CharacterToPinYin:dict[@"fullname"]];
        dict[@"phones"] = (ignore_null)person.phones;
        dict[@"emails"] = (ignore_null)person.emails;
        NSString* data = [WSIObject json_encode:dict];
        
        ns::MutableArray dict_simple;
        dict_simple << (ignore_null)(id)dict[@"firstname"] << (ignore_null)(id)dict[@"lastname"] << (ignore_null)(id)dict[@"fullname"] << (ignore_null)(id)dict[@"fullname::pinyin"] << (ignore_null)person.phonesSimple << (ignore_null)(id)dict[@"emails"];
        
        NSString* simple = [WSIObject json_encode:dict_simple];
        ns::String sql = @"insert into contacts (id, data, simple) values (?1, ?2, ?3)";
        ns::MutableArray params;
        params << [DBMSqlParam paramWith:number(idx++) type:WSIValueTypeInt pos:0] << [DBMSqlParam paramWith:data type:WSIValueTypeString pos:1] << [DBMSqlParam paramWith:simple type:WSIValueTypeString pos:2];
        [db exec:sql params:params];
    }
    
    [addressBook release];
}

- (NSArray*)search:(NSString *)query {
    ns::String sql = @"select data from contacts where simple like \"%";
    sql += query;
    sql += @"%\"";
    DBMSqlDatatable* dt = [db exec:sql];
    ns::MutableArray arr;
    for (NSArray* row in dt.rows) {
        NSString* str = (NSString*)[row objectAtIndex:0];
        arr << [WSIObject json_decode:str];
    }
    return arr.consign();
}

@end

WSI_END_OBJC