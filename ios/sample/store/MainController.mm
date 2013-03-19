
# include "WSIFoundation.h"
# include "MainController.h"

# import "WSIBdb.h"
# import "WSISqlite.h"
# import "WSILevelDB.h"

WSIAPP_BEGIN_OBJC

@implementation MainController

- (void)testSqlite {
    WSISqlite *sqlite = [[WSISqlite alloc] initWith:@"sqlite.db" type:WSIDirectoryTypeBundleWritable];
    DBMSqlDatatable *dt = [sqlite exec_ansi:"create table if not exists test (id int)"];
    
    NSString *str = @"";
    
    int timestamp = time(NULL);
    for (int i = 0; i < 100; ++i) {
        dt = [sqlite exec_ansi:"insert into test (id) values (100)"];
    }
    timestamp = time(NULL) - timestamp;
    str = [str stringByAppendingFormat:@"100 insert: %d \n", timestamp];
    
    timestamp = time(NULL);
    for (int i = 0; i < 1000; ++i) {
        dt = [sqlite exec_ansi:"insert into test (id) values (100)"];
    }
    timestamp = time(NULL) - timestamp;
    str = [str stringByAppendingFormat:@"1000 insert: %d \n", timestamp];
    
    timestamp = time(NULL);
    for (int i = 0; i < 10000; ++i) {
        dt = [sqlite exec_ansi:"insert into test (id) values (100)"];
    }
    timestamp = time(NULL) - timestamp;
    str = [str stringByAppendingFormat:@"10000 insert: %d \n", timestamp];
    
    dt = [sqlite exec_ansi:"drop table test"];
    [sqlite release];
    trace_msg(str);
}

- (void)testBdb {
    WSIBdb *bdb = [[WSIBdb alloc] initWith:@"bdb.db" type:WSIDirectoryTypeBundle];
    
    NSString *key = @"key", *val = @"val";
    NSData *dk = [key dataUsingEncoding:NSUTF8StringEncoding];
    NSData *dv = [val dataUsingEncoding:NSUTF8StringEncoding];
    
    NSString *str = @"";
    
    int timestamp = time(NULL);
    for (int i = 0; i < 100; ++i) {
        [bdb put:dv key:dk];
    }
    timestamp = time(NULL) - timestamp;
    str = [str stringByAppendingFormat:@"100 insert: %d \n", timestamp];
    
    timestamp = time(NULL);
    for (int i = 0; i < 1000; ++i) {
        [bdb put:dv key:dk];
    }
    timestamp = time(NULL) - timestamp;
    str = [str stringByAppendingFormat:@"1000 insert: %d \n", timestamp];
    
    timestamp = time(NULL);
    for (int i = 0; i < 10000; ++i) {
        [bdb put:dv key:dk];
    }
    timestamp = time(NULL) - timestamp;
    str = [str stringByAppendingFormat:@"10000 insert: %d \n", timestamp];
    
    NSArray *arr = [bdb get:dk];
    trace_int([arr count]);
    
    [bdb release];
    trace_msg(str);
}

- (void)testBdbCxx {
    ::wsi::store::test::Bdb bdb;
    ::wsi::ut::Suite suit;
    suit.add(&bdb);
    suit.run();
}

- (void)testLevelDb {
    WSILevelDB *ldb = [[WSILevelDB alloc] initWith:@"leveldb.db" type:WSIDirectoryTypeBundle];
    
    NSString *key = @"key", *val = @"val";
    NSData *dk = [key dataUsingEncoding:NSUTF8StringEncoding];
    NSData *dv = [val dataUsingEncoding:NSUTF8StringEncoding];
    
    NSString *str = @"";
    
    int timestamp = time(NULL);
    for (int i = 0; i < 100; ++i) {
        [ldb put:dv key:dk];
    }
    timestamp = time(NULL) - timestamp;
    str = [str stringByAppendingFormat:@"100 insert: %d \n", timestamp];
    
    timestamp = time(NULL);
    for (int i = 0; i < 1000; ++i) {
        [ldb put:dv key:dk];
    }
    timestamp = time(NULL) - timestamp;
    str = [str stringByAppendingFormat:@"1000 insert: %d \n", timestamp];
    
    timestamp = time(NULL);
    for (int i = 0; i < 10000; ++i) {
        [ldb put:dv key:dk];
    }
    timestamp = time(NULL) - timestamp;
    str = [str stringByAppendingFormat:@"10000 insert: %d \n", timestamp];
    
    NSArray *arr = [ldb get:dk];
    trace_int([arr count]);
    
    [ldb release];
    trace_msg(str);
}

- (void)loadView {
    WSIUIView *view = [[WSIUIView alloc] initWithFrame:CGRectZero];
    view.needAssistantView = YES;
    view.identity = @"demo::assistant";
    WSIUIView *ass = [[WSIUIView alloc] initWithFrame:CGRectZero];
    ass.backgroundColor = [UIColor redColor];
    [view setAssistantView:ass];
    [ass release];
    self.view = view;
    [view release];
}

- (void)viewIsLoading {    
    WSIUIButton *button = nil;
    
    wsi::CGRectLayoutVBox lyt(CGRectMake(0, 0, 200, 200));
    
    button = [UIBevelButton button];
    [button setTitle:@"SQLite" forState:UIControlStateNormal];
    button.frame = lyt.add_pixel(25);
    [button connect:kSignalViewClicked sel:@selector(testSqlite) obj:self];
    [self.view addSubview:button];
    
    button = [UIBevelButton button];
    [button setTitle:@"Bdb" forState:UIControlStateNormal];
    button.frame = lyt.add_pixel(25);
    [button connect:kSignalViewClicked sel:@selector(testBdb) obj:self];
    [self.view addSubview:button];
    
    button = [UIBevelButton button];
    [button setTitle:@"Bdb C++" forState:UIControlStateNormal];
    button.frame = lyt.add_pixel(25);
    [button connect:kSignalViewClicked sel:@selector(testBdbCxx) obj:self];
    [self.view addSubview:button];
    
    button = [UIBevelButton button];
    [button setTitle:@"LevelDB" forState:UIControlStateNormal];
    button.frame = lyt.add_pixel(25);
    [button connect:kSignalViewClicked sel:@selector(testLevelDb) obj:self];
    [self.view addSubview:button];
}

@end

WSIAPP_END_OBJC