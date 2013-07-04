
# include "Foundation+NNT.h"
# include "MainController.h"

# import "Bdb+NNT.h"
# import "Sqlite+NNT.h"
# import "LevelDB+NNT.h"
# import "NSSqliteArchive.h"

NNTAPP_BEGIN_OBJC

@implementation MainController

- (void)testSqlite {
    NNTSqlite *sqlite = [[NNTSqlite alloc] initWith:@"sqlite.db" type:NNTDirectoryTypeBundleWritable];
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
    NNTBdb *bdb = [[NNTBdb alloc] initWith:@"bdb.db" type:NNTDirectoryTypeBundle];
    
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
    NNT_USINGCXXNAMESPACE;
    store::test::Bdb bdb;
    ut::Suite suit;
    suit.add(&bdb);
    suit.run();
}

- (void)testLevelDb {
    NNTLevelDB *ldb = [[NNTLevelDB alloc] initWith:@"leveldb.db" type:NNTDirectoryTypeBundle];
    
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

- (void)testSqliteArchive {
    NSSqliteArchive* sq = [[NSSqliteArchive alloc] initWithDbname:@"test" tableName:@"TEST0"];
    NSSqliteArchive* sq1 = [[NSSqliteArchive alloc] initWithDbname:@"test" tableName:@"TEST1"];
    NSArray* arr = [NSArray arrayWithObjects:
                    [NSDictionary dictionaryWithObjectsAndKeys:@"xiao a", @"name", @1, @"id", @1.12, @"value", nil],
                    [NSDictionary dictionaryWithObjectsAndKeys:@"xiao b", @"name", @2, @"id", @0.56, @"value", nil],
                    [NSDictionary dictionaryWithObjectsAndKeys:@"xiao c", @"name", @3, @"id", @1.00, @"value", nil],
                    nil];
    // archive.
    [sq archive:arr];
    [sq1 archive:arr];
    
    // unarchive.
    arr = [sq unarchive];
    
    // query.
    NSDictionary* item = [NSDictionary dictionaryWithKey:@"name" forObj:@"xiao a"];
    item = [sq query:item];
    
    // update.
    item = [NSDictionary dictionaryWithKey:@"name" forObj:@"xiao b"];
    NSDictionary* tgt = [NSDictionary dictionaryWithObjectsAndKeys:@"xiao b", @"name", @4, @"id", @9.99, @"value", nil];
    [sq update:item forData:tgt];
    
    // delete.
    item = [NSDictionary dictionaryWithKey:@"name" forObj:@"xiao c"];
    [sq delete:item];
    
    // add.
    item = [NSDictionary dictionaryWithObjectsAndKeys:@"xiao d", @"name", @9, @"id", @1.00, @"value", nil];
    [sq insert:item];
    
    [sq release];
    [sq1 release];
}

- (void)loadView {
    NNTUIView *view = [[NNTUIView alloc] initWithFrame:CGRectZero];
    view.needAssistantView = YES;
    view.identity = @"demo::assistant";
    NNTUIView *ass = [[NNTUIView alloc] initWithFrame:CGRectZero];
    ass.backgroundColor = [UIColor redColor];
    [view setAssistantView:ass];
    [ass release];
    self.view = view;
    [view release];
}

- (void)viewIsLoading {
    NNT_USINGCXXNAMESPACE;
    
    NNTUIButton *button = nil;
    
    CGRectLayoutVBox lyt(CGRectMake(0, 0, 200, 500));
    
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
    
    button = [UIBevelButton button];
    [button setTitle:@"SqliteArchive" forState:UIControlStateNormal];
    button.frame = lyt.add_pixel(25);
    [button connect:kSignalViewClicked sel:@selector(testSqliteArchive) obj:self];
    [self.view addSubview:button];
}

@end

NNTAPP_END_OBJC