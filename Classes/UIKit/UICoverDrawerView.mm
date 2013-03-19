
# import "Core.h"
# import "UICoverDrawerView.h"
# import "UICoverDrawer.h"
# import <QuartzCore/QuartzCore.h>

WSI_BEGIN_OBJC

@interface UICoverDrawerViewPrivate : NSObject {
    
    BOOL is_dragging_cover;
    CGPoint pt_start;
    BOOL skip_move;
    
}

@property (nonatomic) BOOL is_dragging_cover;
@property (nonatomic) CGPoint pt_start;
@property (nonatomic, assign) UICoverDrawerView *d_owner;
@property (nonatomic) BOOL skip_move;

@end

@implementation UICoverDrawerViewPrivate

@synthesize is_dragging_cover;
@synthesize pt_start;
@synthesize d_owner;
@synthesize skip_move;

- (id)init {
    self = [super init];
    
    skip_move = NO;
    
    return self;
}

- (void)dealloc {
    [super dealloc];
}

@end

@implementation UICoverDrawerView

@synthesize drawer;
@synthesize scale;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    WSIDECL_PRIVATE_INIT(UICoverDrawerView);
    
    self.backgroundColor = [UIColor clearColor];
    self.scale = 1.f;
    
    return self;
}

- (void)dealloc {
    WSIDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

# pragma mark -
# pragma mark touches

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)__event {
    [super touchesBegan:touches withEvent:__event];
    
    CGPoint pt_start = [[touches anyObject] locationInView:self];
    d_ptr.is_dragging_cover = NO;
    
    CALayer *layer = [self.layer hitTest:pt_start];
    UICoverDrawerItem *item_start = [drawer find_item_bylayer_onscreen:layer];
    d_ptr.is_dragging_cover = item_start != nil;
    
    d_ptr.pt_start = pt_start;
    drawer.viewportDistance = 0;
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)__event {
    [super touchesMoved:touches withEvent:__event];
    
    if (!d_ptr.is_dragging_cover)
        return;
    
    CGPoint pt_moved = [[touches anyObject] locationInView:self];
    
    if (drawer.itemsScrollable) {
        real d_y = (d_ptr.pt_start.y - pt_moved.y) * drawer.draggingDamp;
        UICoverDrawerItem *tgt_item = d_y > 0 ? drawer.currentCover.previous : drawer.currentCover.next;
                
        if (d_y) {            
            if (fabs(d_y) < drawer.itemSpacing) {
                if (drawer.enableRing) {
                    drawer.viewportDistance = d_y;                        
                } else {
                    if (tgt_item) { 
                        drawer.viewportDistance = d_y;
                    }
                }
                
                [drawer relayoutData];
                
            } else {                
                drawer.viewportDistance = 0;
                [drawer selectItem:tgt_item animated:NO];
                d_ptr.pt_start = pt_moved;
                d_ptr.skip_move = YES;
            }                        
        }
    }
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)__event {
    [super touchesEnded:touches withEvent:__event];
    
    if (!d_ptr.is_dragging_cover)
        return;
    
    CGPoint pt_moved = [[touches anyObject] locationInView:self];
    
    if (drawer.itemsScrollable && !d_ptr.skip_move) {            
        real d_y = (d_ptr.pt_start.y - pt_moved.y) * drawer.draggingDamp;
        
        if (d_y) {
            UICoverDrawerItem *tgt_item = d_y > 0 ? drawer.currentCover.previous : drawer.currentCover.next;
            [drawer selectItem:tgt_item animated:YES];
        }
    }
        
    d_ptr.skip_move = NO;
    d_ptr.pt_start = pt_moved;
}

@end

WSI_END_OBJC