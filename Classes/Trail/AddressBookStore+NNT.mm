
# import "Core.h"
# import "AddressBookStore+NNT.h"
# import "Sqlite+NNT.h"
# import "ChineseString.h"

NNT_BEGIN_OBJC

NNT_USINGCXXNAMESPACE;

@implementation NNTAddressBookStore

NNTIMPL_SINGLETON(NNTAddressBookStore);

- (id)init {
    self = [super init];
    return self;
}

- (void)instanceInit {
    db = [[NNTSqlite alloc] initWith:@"addressbook.db" type:NSAppVarDirectory];
    if ([db exist_table:"contacts"] == NO) {
        [self refresh];
    }
    
# ifdef NNT_DEBUG
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
    NNTAddressBook* addressBook = [[NNTAddressBook alloc] init];
    [addressBook refresh];
    
    int idx = 0;
    for (NNTPerson* person in addressBook.contacts) {
        ns::MutableDictionary dict;
        dict[@"firstname"] = (ignore_null)person.firstName;
        dict[@"lastname"] = (ignore_null)person.lastName;
        dict[@"fullname"] = (ignore_null)person.fullName;
        dict[@"fullname::pinyin"] = (ignore_null)[ChineseString CharacterToPinYin:dict[@"fullname"]];
        dict[@"phones"] = (ignore_null)person.phones;
        dict[@"emails"] = (ignore_null)person.emails;
        NSString* data = [NNTObject json_encode:dict];
        
        ns::MutableArray dict_simple;
        dict_simple << (ignore_null)(id)dict[@"firstname"] << (ignore_null)(id)dict[@"lastname"] << (ignore_null)(id)dict[@"fullname"] << (ignore_null)(id)dict[@"fullname::pinyin"] << (ignore_null)person.phonesSimple << (ignore_null)(id)dict[@"emails"];
        
        NSString* simple = [NNTObject json_encode:dict_simple];
        ns::String sql = @"insert into contacts (id, data, simple) values (?1, ?2, ?3)";
        ns::MutableArray params;
        params << [DBMSqlParam paramWith:number(idx++) type:NNTValueTypeInt pos:0] << [DBMSqlParam paramWith:data type:NNTValueTypeString pos:1] << [DBMSqlParam paramWith:simple type:NNTValueTypeString pos:2];
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
        arr << [NNTObject json_decode:str];
    }
    return arr.consign();
}

@end

NNT_END_OBJC