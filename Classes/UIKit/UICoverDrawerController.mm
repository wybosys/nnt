
# import "Core.h"
# import "UICoverDrawerController.h"

WSI_BEGIN_OBJC

@implementation UICoverDrawData

@synthesize title, image;

- (void)dealloc {
    [title release];
    [image release];
    [super dealloc];
}

+ (id)dataWith:(NSString*)title image:(UIImage*)image {
    UICoverDrawData* data = [[UICoverDrawData alloc] init];
    data.title = title;
    data.image = image;
    return [data autorelease];
}

@end

@implementation UICoverDrawerController

@dynamic coverDrawer;
@synthesize datas;

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    zero_release(datas);
    [super dealloc];
}

- (void)loadView {
    UICoverDrawer* view = [[UICoverDrawer alloc] initWithZero];
    self.view = view;
    [view release];
    
    view.dataSource = self;
    view.delegate = self;
}

- (UICoverDrawer*)coverDrawer {
    return (UICoverDrawer*)self.view;
}

- (void)reloadData {
    [self.coverDrawer reloadData];
}

# pragma mark delegate & datasource impl.

- (uint)coverdrawerNumberCovers:(UICoverDrawer*)cd {
    return [datas count];
}

- (UICoverDrawerItem*)coverdrawerCover:(UICoverDrawer *)cd idx:(uint)idx {
    UICoverDrawerItem* item = [UICoverDrawerItem item];
    UICoverDrawData* data = [datas objectAtIndex:idx];
    item.image = data.image;
    item.title = data.title;
    //item.backgroundColor = [UIColor redColor];
    return item;
}

- (void)coverdrawerItemAdded:(UICoverDrawer*)cd item:(UICoverDrawerItem*)item {
    trace_msg(@"add a item into coverdrawer");
}

- (void)coverdrawerItemDragBegin:(UICoverDrawer*)cd item:(UICoverDrawerItem*)item touchs:(NSSet*)touchs {
    trace_msg(@"begin drag coveritem");
}

- (void)coverdrawerItemDragging:(UICoverDrawer*)cd item:(UICoverDrawerItem*)item touchs:(NSSet*)touchs {
    trace_msg(@"dragging coveritem");
}

- (void)coverdrawerItemDragEnd:(UICoverDrawer*)cd item:(UICoverDrawerItem*)item touchs:(NSSet*)touchs {
    trace_msg(@"end drag coveritem");
}

- (void)coverdrawerItemSelectedChanged:(UICoverDrawer*)cd cur:(UICoverDrawerItem*)curitem pas:(UICoverDrawerItem*)pasitem {
    trace_msg(@"coveritem selected");
}

@end

WSI_END_OBJC