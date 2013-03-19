
# import "Core.h"
# import "UICHMController.h"
# import "UICHMView.h"
# import "../Parser/CHMObjParser.h"
# import "UITableViewCell+WSI.h"
# import "UITableViewController+WSI.h"
# import "UIWebView+WSI.h"
# import "WSIResource.h"

WSI_BEGIN_OBJC

signal_t kSignalFileLoaded = @"::wsi::file::loaded";

@interface UICHMControllerPrivate : NSObject <UITableViewDelegate, UITableViewDataSource> {
    UICHMController *d_owner;
    CHMObjParser *parser;
}

@property (nonatomic, assign) UICHMController *d_owner;
@property (nonatomic, retain) CHMObjParser *parser;

@end

@implementation UICHMControllerPrivate

@synthesize d_owner;
@synthesize parser;

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    zero_release(parser);
    [super dealloc];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    if ([tableView attachFind:@"chm"]) {
        CHMTree *chm = [tableView attachFind:@"chm"];
        return [chm.children count];
    }
    return [parser.tree.children count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [[WSIUITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"cell"];
    CHMTree *chm = nil;
    if ([tableView attachFind:@"chm"]) {
        chm = [tableView attachFind:@"chm"];
        chm = [chm.children objectAtIndex:indexPath.row];
    } else {
        chm = [parser.tree.children objectAtIndex:indexPath.row];        
    }
    cell.textLabel.text = chm.name;
    if (chm.isTree) {
        cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;        
    }
    [cell attachPush:@"chm" obj:chm];
    return [cell autorelease];
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView cellForRowAtIndexPath:indexPath];
    CHMTree *chm = [cell attachFind:@"chm"];
    if (chm.isTree) {
        WSIUITableViewController *ctlr = [[WSIUITableViewController alloc] init];
        [ctlr.tableView attachPush:@"chm" obj:chm];
        ctlr.title = chm.name;
        ctlr.tableView.dataSource = self;
        ctlr.tableView.delegate = self;
        [d_owner.navi pushViewController:ctlr animated:YES];
        [ctlr release];
    } else {
        NSData *data = [parser loadTarget:chm.local];
        if (data) {
            UIViewController *ctlr = [[UIViewController alloc] init];
            ctlr.title = chm.name;
            UIWebView *web = [[UIWebView alloc] initWithZero];
           // web.scalesPageToFit = YES;
            ctlr.view = web;
            [d_owner.navi pushViewController:ctlr animated:YES];
            [web release];
            [ctlr release];
            // load data
            NSString *str_data = [[NSString alloc] initWithData:data encoding:CFStringConvertEncodingToNSStringEncoding([parser encoding])];
            [web loadHTMLStringLocal:str_data];
            [str_data release];
        }
    }
}

@end

@implementation UICHMController

@synthesize navi;

- (id)init {
    self = [super init];
    WSIDECL_PRIVATE_INIT(UICHMController);
    return self;
}

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalFileLoaded)
WSIEVENT_END

- (void)dealloc {
    [navi release];
    WSIDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (id)initWithNamed:(NSString *)name {
    self = [self init];
    
    name = [WSIResource PathOf:name];
    [self performSelectorInBackground:@selector(thd_read_file:) withObject:name];
    
    return self;
}

- (void)loadView {
    UICHMView *view = [[UICHMView alloc] initWithZero];
    self.view = view;
    [view release];
}

- (void)viewDidLoad {
    UICHMView *view = (UICHMView*)self.view;
    
    navi = [[WSIUINavigationController alloc] init];
    view.main = navi.view;
    [view addSubview:navi.view];
}

- (void)clear {
    while ([navi.viewControllers count]) {
        [navi popViewControllerAnimated:NO];
    }
}

- (void)thd_read_file:(NSString*)name {
    WSI_AUTORELEASEPOOL_BEGIN;
    //NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    
    [self readFile:name];
    
    //[pool release];
    WSI_AUTORELEASEPOOL_END;
}

- (BOOL)readFile:(NSString *)file {    
    CHMObjParser *parser = [[CHMObjParser alloc] init];
    BOOL suc = [parser loadFile:file];
    if (suc) {
        [self clear];
        d_ptr.parser = parser;       
        [self performSelectorOnMainThread:@selector(fileDidLoaded) withObject:nil waitUntilDone:NO];
        [self emit:kSignalFileLoaded];
    }
    [parser release];
    return suc;
}

- (BOOL)readNamed:(NSString*)file {
    file = [WSIResource PathOf:file];
    return [self readFile:file];
}

- (void)fileDidLoaded {
    CHMTree *tree = d_ptr.parser.tree;
    
    WSIUITableViewController *ctlr = [[WSIUITableViewController alloc] init];
    ctlr.title = tree.name;
    ctlr.tableView.dataSource = d_ptr;
    ctlr.tableView.delegate = d_ptr;
    [ctlr attachPush:@"tree" obj:tree];
    
    [navi pushViewController:ctlr animated:NO];
    [ctlr release];
}

@end

_CXXCONTROLLER_IMPL(UICHMController);

WSI_END_OBJC
