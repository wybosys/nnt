//
//  AppDelegate.m
//  performance
//
//  Created by 王 渊博 on 12-1-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

# import "Foundation+NNT.h"
# import "AppDelegate.h"

@interface MainView : WSIUIView

@property (nonatomic, readonly) WSIUIButton *objc_add, *objc_add_prealloc, *vector_add, *vector_add_prealloc, *list_add, *set_add;

@end

@implementation MainView

@synthesize objc_add, objc_add_prealloc, vector_add, vector_add_prealloc, list_add, set_add;

- (id)initWithZero {
    self = [super initWithZero];
    
    objc_add = [WSIUIButton buttonWithType:WSIUIButtonTypeInnerRound];
    objc_add_prealloc = [WSIUIButton buttonWithType:WSIUIButtonTypeInnerRound];
    vector_add = [WSIUIButton buttonWithType:WSIUIButtonTypeInnerRound];
    vector_add_prealloc = [WSIUIButton buttonWithType:WSIUIButtonTypeInnerRound];
    list_add = [WSIUIButton buttonWithType:WSIUIButtonTypeInnerRound];
    set_add = [WSIUIButton buttonWithType:WSIUIButtonTypeInnerRound];
    
    objc_add.text = @"OBJC::ADD";
    objc_add_prealloc.text = @"OBJC::ADD::PREALLOC";
    vector_add.text = @"VECTOR::ADD";
    vector_add_prealloc.text = @"VECTOR::ADD::PREALLOC";
    list_add.text = @"LIST::ADD";
    set_add.text = @"SET::ADD::PREALLOC";
    
    [self addSubview:objc_add];
    [self addSubview:objc_add_prealloc];
    [self addSubview:vector_add];
    [self addSubview:vector_add_prealloc];
    [self addSubview:list_add];
    [self addSubview:set_add];
    
    return self;
}

- (void)layoutSubviews {
    wsi::CGRectLayoutVBox lyt(self.bounds);
    
    wsi::CGRectLayoutHBox lyt_objc(lyt.add_pixel(25));
    objc_add.frame = lyt_objc.add_fpercent(.2f);
    objc_add_prealloc.frame = lyt_objc.add_fpercent(.2f);
    
    wsi::CGRectLayoutHBox lyt_vector(lyt.add_pixel(25));
    vector_add.frame = lyt_vector.add_fpercent(.2f);
    vector_add_prealloc.frame = lyt_vector.add_fpercent(.2f);
    
    wsi::CGRectLayoutHBox lyt_list(lyt.add_pixel(25));
    list_add.frame = lyt_list.add_fpercent(.2f);
    set_add.frame = lyt_list.add_fpercent(.2f);
}

@end

@interface MainController : WSIUIViewController

@end

@implementation MainController

- (void)loadView {
    MainView* view = [[MainView alloc] initWithZero];
    self.view = view;
    [view release];
}

- (void)viewIsLoading {
    MainView* view = (MainView*)self.view;
    
    [view.objc_add connect:kSignalButtonClicked sel:@selector(objc_add) obj:self];
    [view.objc_add_prealloc connect:kSignalButtonClicked sel:@selector(objc_add_prealloc) obj:self];
    [view.vector_add connect:kSignalButtonClicked sel:@selector(vector_add) obj:self];
    [view.vector_add_prealloc connect:kSignalButtonClicked sel:@selector(vector_add_prealloc) obj:self];
    [view.list_add connect:kSignalButtonClicked sel:@selector(list_add) obj:self];
    [view.set_add connect:kSignalButtonClicked sel:@selector(set_add) obj:self];
}

# define COUNT 10000000

- (void)objc_add {
    WSI_AUTORELEASEPOOL_BEGIN
    
    NSMutableArray* arr = [NSMutableArray array];
    WSIUIView* test = [[WSIUIView alloc] initWithZero];
    ulong begin = clock();
    for (uint idx = 0; idx < COUNT; ++idx) {
        [arr addObject:test];
    }
    ulong end = clock();
    [Msgbox info:wsi::tostr(end - begin)];
    [test release];
    
    WSI_AUTORELEASEPOOL_END
}

- (void)objc_add_prealloc {
    WSI_AUTORELEASEPOOL_BEGIN
    
    NSMutableArray* arr = [NSMutableArray arrayWithCapacity:COUNT];
    WSIUIView* test = [[WSIUIView alloc] initWithZero];
    ulong begin = clock();
    for (uint idx = 0; idx < COUNT; ++idx) {
        [arr addObject:test];
    }
    ulong end = clock();
    [Msgbox info:wsi::tostr(end - begin)];
    [test release];
    
    WSI_AUTORELEASEPOOL_END
}

- (void)vector_add {
    ::wsi::core::vector<WSIUIView*> arr;
    WSIUIView* test = [[WSIUIView alloc] initWithZero];
    ulong begin = clock();
    for (uint idx = 0; idx < COUNT; ++idx) {
        arr.push_back(test);
    }
    ulong end = clock();
    [Msgbox info:wsi::tostr(end - begin)];
    [test release];
}

- (void)vector_add_prealloc {
    ::wsi::core::vector<WSIUIView*> arr;
    arr.reserve(COUNT);
    WSIUIView* test = [[WSIUIView alloc] initWithZero];
    ulong begin = clock();
    for (uint idx = 0; idx < COUNT; ++idx) {
        arr.push_back(test);
    }
    ulong end = clock();
    [Msgbox info:wsi::tostr(end - begin)];
    [test release];
}

- (void)list_add {
    ::wsi::core::list<WSIUIView*> arr;
    WSIUIView* test = [[WSIUIView alloc] initWithZero];
    ulong begin = clock();
    for (uint idx = 0; idx < COUNT; ++idx) {
        arr.push_back(test);
    }
    ulong end = clock();
    [Msgbox info:wsi::tostr(end - begin)];
    [test release];
}

- (void)set_add {
    ::wsi::core::set<WSIUIView*> arr;
    WSIUIView* test = [[WSIUIView alloc] initWithZero];
    ulong begin = clock();
    for (uint idx = 0; idx < COUNT; ++idx) {
        arr.insert(test);
    }
    ulong end = clock();
    [Msgbox info:wsi::tostr(end - begin)];
    [test release];
}

@end

@implementation AppDelegate

- (void)load {
    MainController* ctlr = [[MainController alloc] init];
    ctlr.orientationEnable = UIOrientationEnableAll;
    self.window.rootViewController = ctlr;
    [ctlr release];
}

@end

WSIDEBUG_THEME_IMPL;