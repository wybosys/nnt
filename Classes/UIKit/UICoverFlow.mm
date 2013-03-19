
# import "Core.h"
# import "UICoverFlow.h"
# import "UICoverFlowItem.h"
# import <QuartzCore/QuartzCore.h>
# import "Graphic+NNT.h"
# import "UIImageView+NNT.h"
# import "UIImage+NNT.h"

NNT_BEGIN_OBJC

@interface UICoverFlow (hidden)

// init
- (void)setUpInitialState;

// get cover
- (UIItemView*)coverForIndex:(int)coverIndex;

// update item.
- (void)updateCover:(UIItemView*)item;
- (void)updateCover:(UIItemView*)item animated:(BOOL)animated;
- (void)updateCoverFrom:(int)lowBound to:(int)upperBound animated:(BOOL)animated;

// layout covers
- (void)layoutCover:(UIItemView*)item indexSelected:(int)indexSelected animated:(BOOL)animated;
- (void)layoutCovers:(UIItemView*)item from:(int)lowerBound to:(int)upperBound animated:(BOOL)animated;

// find cover
- (UIItemView*)findCoverOnscreen:(CALayer *)targetLayer;

@end

NNTDECL_PRIVATE_BEGIN(UICoverFlow, NSObject)

@property (nonatomic, retain) NSMutableDictionary *onscreen_covers, *offscreen_covers;
@property (nonatomic, retain) UIScrollView *scrollView;
@property (nonatomic, assign) int lowerVisibleCover, upperVisibleCover;
@property (nonatomic, assign) UIItemView *selectedItem;
@property (nonatomic, assign) int beginningCover;
@property (nonatomic, assign) BOOL isSingleTap, isDoubleTap, isDraggingACover;
@property (nonatomic, assign) real startPosition;
@property (nonatomic, assign) CGPadding padding;
@property (nonatomic, assign) CGPoint centerPoint;
@property (nonatomic, assign) int halfMaxCoversOnScreen;

NNTDECL_PRIVATE_IMPL(UICoverFlow)

@synthesize offscreen_covers, onscreen_covers;
@synthesize scrollView;
@synthesize lowerVisibleCover, upperVisibleCover;
@synthesize selectedItem;
@synthesize isSingleTap, isDoubleTap, isDraggingACover, startPosition, beginningCover;
@synthesize padding;
@synthesize centerPoint;
@synthesize halfMaxCoversOnScreen;

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    zero_release(onscreen_covers);
    zero_release(offscreen_covers);
    zero_release(scrollView);    
    [super dealloc];
}

- (UICoverFlowItem*)selectedCover {
    return (UICoverFlowItem*)selectedItem.contentView;
}

- (int)selectedIndex {
    return self.selectedCover.number;
}

- (void)setSelectedItem:(UIItemView *)item {
    if (selectedItem == item)
        return;
    
    selectedItem = item;
    
    [d_owner layoutCovers:selectedItem from:lowerVisibleCover to:upperVisibleCover animated:YES];
    [d_owner emit:kSignalSelectChanged result:selectedItem];
}

NNTDECL_PRIVATE_END

@implementation UICoverFlow

@synthesize delegate = _delegate;
@synthesize coverSpacing = _coverSpacing, centerCoverOffset = _centerCoverOffset, coverAngle = _coverAngle, coverAngleStep = _coverAngleStep, coverZPositionStep = _coverZPositionStep, coverZPosition = _coverZPosition;
@synthesize maxCoversOnScreen = _maxCoversOnScreen, numberOfCovers = _numberOfCovers;
@synthesize preferredWidth = _preferredWidth, preferredHeight = _preferredHeight;
@synthesize padding  = _padding;
@synthesize coverSlant = _coverSlant;
@synthesize coverScale = _coverScale;
@dynamic isCoverDragging;
@synthesize scaleToFit = _scaleToFit;
@synthesize centerOffset = _centerOffset;
@synthesize items = _items;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self == nil)
        return nil;
    
    NNTDECL_PRIVATE_INIT(UICoverFlow);

    _coverSpacing = 40.f;
    _centerCoverOffset = 70.f;
    _coverAngle = .21f;
    _coverAngleStep = 0.f;
    _coverZPositionStep = 1.f;
    _coverZPosition = -50.f;
    _padding = CGPaddingMake(.05f, .05f, .15f, .15f);
    _coverSlant = -0.005f;
    _coverScale = 1.f;
    _scaleToFit = NO;
    _centerOffset = CGPointZero;
    _items = [[UIItemsContainer alloc] init];
    
    self.maxCoversOnScreen = 10;
    
    // for content clicked.
    [self connect:kSignalViewClicked sel:@selector(_act_view_clicked:)];
    
    // touches signal.
    [self connect:kSignalTouchesBegin sel:@selector(_act_touches_begin:)];
    [self connect:kSignalTouchesMoved sel:@selector(_act_touches_moved:)];
    [self connect:kSignalTouchesEnd sel:@selector(_act_touches_end:)];
    
    return self;
}

- (void)dealloc {
    safe_release(_items);
    
    NNTDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalActiveScale)
NNTEVENT_SIGNAL(kSignalItemClicked)
NNTEVENT_SIGNAL(kSignalContentClicked)
NNTEVENT_SIGNAL(kSignalSelectChanged)
NNTEVENT_END

- (BOOL)isCoverDragging {
    return d_ptr.isDraggingACover;
}

- (void)_act_view_clicked:(NNTEventObj*)evt {
    NSSet *touches = (NSSet*)evt.result;
    CGPoint pt = [[touches anyObject] locationInView:d_ptr.scrollView];
    CGRect rc = d_ptr.selectedItem.frame;
    if (CGRectContainsPoint(rc, pt)) {
        [self emit:kSignalItemClicked result:d_ptr.selectedItem];
        [self emit:kSignalContentClicked result:d_ptr.selectedCover];
    }
}

- (void)reloadData {
    [self performSelectorOnMainThread:@selector(_do_reload_data)
                           withObject:nil
                        waitUntilDone:YES];
}

- (void)_do_reload_data {
    // init
    [self setUpInitialState];
    
    // layout
    [self relayoutData:NO];
}

- (void)relayoutData:(BOOL)animated {
    CGRect rc = self.bounds;
    
    CGPadding pp = CGPaddingZero;
    pp.left = rc.size.width * _padding.left;
    pp.right = rc.size.width * _padding.right;
    pp.top = rc.size.height * _padding.top;
    pp.bottom = rc.size.height * _padding.bottom;
    d_ptr.padding = pp;
    
    CGRect rc_work = CGRectMake(rc.origin.x + pp.left, 
                                rc.origin.y + pp.top, 
                                rc.size.width - pp.left - pp.right, 
                                rc.size.height - pp.top - pp.bottom);
    
    // set center point.
    CGPoint pt_center = CGRectCenterPoint(&rc_work);
    d_ptr.centerPoint = CGPointMake(pt_center.x + rc_work.size.width * _centerOffset.x,
                                    pt_center.y + rc_work.size.height * _centerOffset.y);
    
    // update covers.
    [self updateCoverFrom:d_ptr.lowerVisibleCover to:d_ptr.upperVisibleCover animated:animated];
    
    // layout covers.
    [self layoutCovers:d_ptr.selectedItem from:d_ptr.lowerVisibleCover to:d_ptr.upperVisibleCover animated:animated];
    
    // center selected.
	[self centerOnSelectedCover:animated];
}

- (void)layoutSubviews {
    CGRect rc = self.bounds;
    if (CGRectEqualToRect(rc, CGRectZero))
        return;        
    
    // fill scroll view.
    d_ptr.scrollView.frame = rc;
    
    // auto fit process.
    if (_scaleToFit) {
        CGPadding pp = CGPaddingZero;
        pp.left = rc.size.width * _padding.left;
        pp.right = rc.size.width * _padding.right;
        pp.top = rc.size.height * _padding.top;
        pp.bottom = rc.size.height * _padding.bottom;
        d_ptr.padding = pp;
        
        CGRect rc_work = CGRectMake(rc.origin.x + pp.left, 
                                    rc.origin.y + pp.top, 
                                    rc.size.width - pp.left - pp.right, 
                                    rc.size.height - pp.top - pp.bottom);
        
        if (d_ptr.halfMaxCoversOnScreen) {
            self.preferredWidth = rc_work.size.width / d_ptr.halfMaxCoversOnScreen * 2;
            self.preferredHeight = rc_work.size.height / d_ptr.halfMaxCoversOnScreen * 2;
        }
        
        self.centerCoverOffset = self.preferredWidth * .5f;
    }
    
    // relayout.
    [self relayoutData:NO];
}

- (void)setNumberOfCovers:(uint)number {
	_numberOfCovers = number;
    
	d_ptr.scrollView.contentSize = CGSizeMake(number * _coverSpacing + self.bounds.size.width,
                                              self.bounds.size.height);
    
	int lowerBound = MAX(0L, d_ptr.selectedIndex - d_ptr.halfMaxCoversOnScreen);
	int upperBound = MIN(self.numberOfCovers - 1L, d_ptr.selectedIndex + d_ptr.halfMaxCoversOnScreen);
	
	if (d_ptr.selectedItem) {
		[self layoutCovers:d_ptr.selectedItem from:lowerBound to:upperBound animated:NO];
    }
	else {
		[self setSelectedCoverById:0];
    }
	
	[self centerOnSelectedCover:NO];
}

- (void)setMaxCoversOnScreen:(uint)val {
    _maxCoversOnScreen = val;
    d_ptr.halfMaxCoversOnScreen = ceil(val * .5f);
}

- (void)_act_touches_begin:(NNTEventObj*)evt {
    NSSet* touches = (NSSet*)evt.result;
    
	CGPoint startPoint = [[touches anyObject] locationInView:self];
	d_ptr.isDraggingACover = NO;
	
	// Which cover did the user tap?
	CALayer *targetLayer = (CALayer *)[d_ptr.scrollView.layer hitTest:startPoint];
	UIItemView *targetItem = [self findCoverOnscreen:targetLayer];
    
	d_ptr.isDraggingACover = (targetItem != nil);
    
	d_ptr.beginningCover = d_ptr.selectedIndex;
	// Make sure the user is tapping on a cover.
	d_ptr.startPosition = (startPoint.x / 1.5) + d_ptr.scrollView.contentOffset.x;
	
	if (d_ptr.isSingleTap)
		d_ptr.isDoubleTap = YES;
    
	d_ptr.isSingleTap = ([touches count] == 1);
}

- (void)_act_touches_moved:(NNTEventObj*)evt {
    NSSet* touches = (NSSet*)evt.result;
    
	d_ptr.isSingleTap = NO;
	d_ptr.isDoubleTap = NO;
	
	// Only scroll if the user started on a cover.
	if (!d_ptr.isDraggingACover)
		return;
	
	CGPoint movedPoint = [[touches anyObject] locationInView:self];
	CGFloat offset = d_ptr.startPosition - (movedPoint.x / 1.5);
	CGPoint newPoint = CGPointMake(offset, 0);
	d_ptr.scrollView.contentOffset = newPoint;
	int newCover = offset / _coverSpacing;
	if (newCover != d_ptr.selectedIndex) {
		if (newCover < 0)
			[self setSelectedCoverById:0];
		else if (newCover >= self.numberOfCovers)
			[self setSelectedCoverById:self.numberOfCovers - 1];
		else
			[self setSelectedCoverById:newCover];
	}
}

- (void)_act_touches_end:(NNTEventObj*)evt {
    NSSet* touches = (NSSet*)evt.result;
    
	if (d_ptr.isSingleTap) {
		CGPoint targetPoint = [[touches anyObject] locationInView:self];
		CALayer *targetLayer = (CALayer *)[d_ptr.scrollView.layer hitTest:targetPoint];
		UIItemView *targetItem = [self findCoverOnscreen:targetLayer];
        if (targetItem) {
            UICoverFlowItem* cover = (UICoverFlowItem*)targetItem.contentView;
            if (cover.number != d_ptr.selectedIndex) {
                [self setSelectedCoverById:cover.number];
            }
        }
	}
    
	[self centerOnSelectedCover:YES];
	
	// And send the delegate the newly selected cover message.
	if (d_ptr.beginningCover != d_ptr.selectedIndex) {
		if ([self.delegate respondsToSelector:@selector(openFlowView:selectionDidChange:)]) {
			[self.delegate coverFlow:self selectionDidChange:d_ptr.selectedIndex];
        }
    }
}

- (void)centerOnSelectedCover:(BOOL)animated {
	CGPoint selectedOffset = CGPointMake(_coverSpacing * d_ptr.selectedIndex, 0);
	[d_ptr.scrollView setContentOffset:selectedOffset animated:animated];
}

- (void)setSelectedCoverById:(int)newSelectedCover {
	if (d_ptr.selectedCover &&
        (newSelectedCover == d_ptr.selectedCover.number))
		return;
    
    if (newSelectedCover >= self.numberOfCovers)
        newSelectedCover = 0;
	
	int newLowerBound = MAX(0L, newSelectedCover - d_ptr.halfMaxCoversOnScreen);
	int newUpperBound = MIN(self.numberOfCovers - 1L, newSelectedCover + d_ptr.halfMaxCoversOnScreen);
    
	if (!d_ptr.selectedCover) {
		// Allocate and display covers from newLower to newUpper bounds.
		for (int i = newLowerBound; i <= newUpperBound; i++) {
			UIItemView* item = [self coverForIndex:i];
            
            // set cover.
			[d_ptr.onscreen_covers setObject:item forKey:::nnt::number(i)];
            [d_ptr.offscreen_covers removeObjectForKey:::nnt::number(i)];
            
            // update cover.
            [self updateCover:item];
			[d_ptr.scrollView.layer addSublayer:item.layer];
            [self layoutCover:item indexSelected:newSelectedCover animated:NO];
		}
		
		d_ptr.lowerVisibleCover = newLowerBound;
		d_ptr.upperVisibleCover = newUpperBound;

	} else {
        // Check to see if the new & current ranges overlap.
        if ((newLowerBound > d_ptr.lowerVisibleCover) ||
            (newUpperBound < d_ptr.upperVisibleCover)) {
                        
            for (int i = d_ptr.lowerVisibleCover; i <= d_ptr.upperVisibleCover; ++i) {
                UIItemView* item = [d_ptr.onscreen_covers objectForKey:::nnt::number(i)];
                
                [d_ptr.offscreen_covers setObject:item forKey:::nnt::number(i)];
                [d_ptr.onscreen_covers removeObjectForKey:::nnt::number(i)];
                
                [item.layer removeFromSuperlayer];
            }
            
            // Move all available covers to new location.
            for (int i = newLowerBound; i <= newUpperBound; ++i) {
                UIItemView* item = [self coverForIndex:i];
                
                [d_ptr.onscreen_covers setObject:item forKey:::nnt::number(i)];
                [d_ptr.offscreen_covers removeObjectForKey:::nnt::number(i)];
                
                [self updateCover:item];
                [d_ptr.scrollView.layer addSublayer:item.layer];
                [self layoutCover:item indexSelected:newSelectedCover animated:NO];
            }
            
            d_ptr.lowerVisibleCover = newLowerBound;
            d_ptr.upperVisibleCover = newUpperBound;
            
        } else if (newSelectedCover > d_ptr.selectedCover.number) {
        
            for (int i = d_ptr.lowerVisibleCover; i < newLowerBound; ++i) {
                UIItemView* item = [d_ptr.onscreen_covers objectForKey:::nnt::number(i)];
                
                if (d_ptr.upperVisibleCover > newUpperBound) {
                    [d_ptr.offscreen_covers setObject:item forKey:::nnt::number(i)];
                    [d_ptr.onscreen_covers removeObjectForKey:::nnt::number(i)];
                    
                    [item.layer removeFromSuperlayer];
                }                
            }
            
            d_ptr.lowerVisibleCover = newLowerBound;
            
            // Add in any missing covers on the right up to the newUpperBound.
            for (int i = d_ptr.upperVisibleCover + 1; i <= newUpperBound; ++i) {
                UIItemView* item = [self coverForIndex:i];
                
                [d_ptr.onscreen_covers setObject:item forKey:::nnt::number(i)];
                [d_ptr.offscreen_covers removeObjectForKey:::nnt::number(i)];
                
                [self updateCover:item];
                [d_ptr.scrollView.layer addSublayer:item.layer];
                [self layoutCover:item indexSelected:newSelectedCover animated:NO];
            }
            
            d_ptr.upperVisibleCover = newUpperBound;
            
        } else {
            
            for (int i = d_ptr.upperVisibleCover; i > newUpperBound; --i) {
                UIItemView* item = [d_ptr.onscreen_covers objectForKey:[NSNumber numberWithInt:i]];
                
                if (d_ptr.lowerVisibleCover < newLowerBound) {
                    [d_ptr.offscreen_covers setObject:item forKey:::nnt::number(i)];
                    [d_ptr.onscreen_covers removeObjectForKey:::nnt::number(i)];
                    
                    [item.layer removeFromSuperlayer];                    
                }
            }
            
            d_ptr.upperVisibleCover = newUpperBound;
            
            // Add in any missing covers on the left down to the newLowerBound.
            for (int i = d_ptr.lowerVisibleCover - 1; i >= newLowerBound; --i) {
                UIItemView* item = [self coverForIndex:i];
                
                [d_ptr.onscreen_covers setObject:item forKey:::nnt::number(i)];
                [d_ptr.offscreen_covers removeObjectForKey:::nnt::number(i)];
                
                [self updateCover:item];
                [d_ptr.scrollView.layer addSublayer:item.layer];
                [self layoutCover:item indexSelected:newSelectedCover animated:NO];
            }
            
            d_ptr.lowerVisibleCover = newLowerBound;
            
        }
    }
    
    // set select.
	d_ptr.selectedItem = [d_ptr.onscreen_covers objectForKey:::nnt::number(newSelectedCover)];
}

- (void)setCoverSlant:(real)val {
    if (val == _coverSlant)
        return;
    
    _coverSlant = val;
    
    CATransform3D sublayerTransform = CATransform3DIdentity;
    if (_coverSlant)
        sublayerTransform.m34 = _coverSlant;
    
	[d_ptr.scrollView.layer setSublayerTransform:sublayerTransform];
}

@end

@implementation UICoverFlow (hidden)

- (NSArray*)subviews {
    NSArray* arr;
    NNT_SYNCHRONIZED(self)
    arr = [super subviews];
    NNT_SYNCHRONIZED_END
    return arr;
}

- (void)setUpInitialState {
    NNT_SYNCHRONIZED(self)
    
    // remove all items.
    [self removeAllSubviews];
    
    NNT_SYNCHRONIZED_END
        
	NSMutableDictionary *offscreenCovers = [[NSMutableDictionary alloc] init];
    d_ptr.offscreen_covers = offscreenCovers;
    [offscreenCovers release];
    
	NSMutableDictionary *onscreenCovers = [[NSMutableDictionary alloc] init];
    d_ptr.onscreen_covers = onscreenCovers;
    [onscreenCovers release];
	
	NNTUIScrollView *scrollView = [[NNTUIScrollView alloc] initWithFrame:self.bounds];
    d_ptr.scrollView = scrollView;
    [scrollView release];
    
    // Initialize the visible and selected cover range.
	d_ptr.lowerVisibleCover = -1;
    d_ptr.upperVisibleCover = -1;
	d_ptr.selectedItem = nil;
    
    self.multipleTouchEnabled = NO;
	self.userInteractionEnabled = YES;
	self.autoresizesSubviews = NO;
    
    scrollView.userInteractionEnabled = NO;
	scrollView.multipleTouchEnabled = NO;
    
    // init
    self.numberOfCovers = _items.count;
    
    // add scroll view.
	[self addSubview:scrollView];
		
	// Set some perspective
	CATransform3D sublayerTransform = CATransform3DIdentity;
    if (_coverSlant)
        sublayerTransform.m34 = _coverSlant;
    
	[scrollView.layer setSublayerTransform:sublayerTransform];
}

- (UIItemView*)coverForIndex:(int)coverIndex {
	UIItemView *item = nil;
    
    // find in off.
    item = [d_ptr.offscreen_covers objectForKey:::nnt::number(coverIndex) null:nil];
    
    // find in on.
    if (item == nil) {
        item = [d_ptr.onscreen_covers objectForKey:::nnt::number(coverIndex) null:nil];
    }
    
	if (item == nil) {
        // alloc item.
        UICoverFlowItem* cover = [_items objectAtIndex:coverIndex];
        
        // init.
        cover.number = coverIndex;
        
        // add view into items.
        item = [UIItemsContainer View:cover];
    }
	
	return item;
}

- (void)updateCover:(UIItemView *)item {
    UICoverFlowItem* cover = (UICoverFlowItem*)item.contentView;
    CGSize sz_cover = [cover calcBestSize];
    
    if (_preferredWidth) {
        sz_cover.width = _preferredWidth;
    }
    if (_preferredHeight) {
        sz_cover.height = _preferredHeight;
    }

    // set size.
    CATransform3D mat = item.layer.transform;
    item.layer.transform = CATransform3DIdentity;
    [item moveToSize:sz_cover];
    item.layer.transform = mat;
}

- (void)layoutCover:(UIItemView*)item indexSelected:(int)indexSelected animated:(BOOL)animated  {
    UICoverFlowItem* cover = (UICoverFlowItem*)item.contentView;
    
	int coverNumber = cover.number;
	CATransform3D newTransform = CATransform3DIdentity;
    
	CGPoint newPosition;	
	newPosition.x = d_ptr.centerPoint.x + _coverSpacing * cover.number;
	newPosition.y = d_ptr.centerPoint.y;
    
    int d_index = abs(coverNumber - indexSelected);
    
    CGFloat newZPosition = _coverZPosition - _coverZPositionStep * d_index;
    CGFloat newAngle = _coverAngle + _coverAngleStep * d_index;
    
	if (coverNumber < indexSelected) {
        
		newPosition.x -= _centerCoverOffset;
        
        if (_coverScale != 1) {
            real scale = powf(_coverScale, d_index);
            newTransform = CATransform3DScale(newTransform, scale, scale, 1);
        }
        
        newTransform = CATransform3DRotate(newTransform, newAngle, 0.0f, 1.0f, 0.0f);        
        
	} else if (coverNumber > indexSelected) {
        
		newPosition.x += _centerCoverOffset;
        
        if (_coverScale != 1) {
            real scale = powf(_coverScale, d_index);
            newTransform = CATransform3DScale(newTransform, scale, scale, 1);
        }
        
        newTransform = CATransform3DRotate(newTransform, newAngle, 0.0f, -1.0f, 0.0f);
        
	} else {
        
		newZPosition = 0;
		newTransform = CATransform3DIdentity;
        
	}
	
	if (animated) {
		[UIView beginAnimations:nil context:nil];
		[UIView setAnimationCurve:UIViewAnimationCurveEaseOut];
		[UIView setAnimationBeginsFromCurrentState:YES];
	}
	
	item.layer.transform = newTransform;
	item.layer.zPosition = newZPosition;
	item.layer.position = newPosition;
	
	if (animated) {
		[UIView commitAnimations];
	}
}

- (void)layoutCovers:(UIItemView*)item from:(int)lowerBound to:(int)upperBound animated:(BOOL)animated {
    UICoverFlowItem* cover = (UICoverFlowItem*)item.contentView;
    int indexSelected = cover.number;
	for (int i = lowerBound; i <= upperBound; ++i) {
		UIItemView *each = [d_ptr.onscreen_covers objectForKey:::nnt::number(i)];
        [self layoutCover:each indexSelected:indexSelected animated:animated];
	}
}

- (void)updateCover:(UIItemView*)item animated:(BOOL)animated {
    if (animated) {
		[UIView beginAnimations:nil context:nil];
		[UIView setAnimationCurve:UIViewAnimationCurveEaseOut];
		[UIView setAnimationBeginsFromCurrentState:YES];
	}
	
    [self updateCover:item];
    
    if (animated) {
		[UIView commitAnimations];
	}
}

- (void)updateCoverFrom:(int)lowBound to:(int)upperBound animated:(BOOL)animated {
    for (int i = lowBound; i <= upperBound; ++i) {
        UIItemView *item = [d_ptr.onscreen_covers objectForKey:::nnt::number(i)];
        if (item) {
            [self updateCover:item animated:animated];
        }        
    }
}

- (UIItemView*)findCoverOnscreen:(CALayer *)targetLayer {
	NSEnumerator *coverEnumerator = [d_ptr.onscreen_covers objectEnumerator];
    UIItemView* item = nil;
	while ((item = [coverEnumerator nextObject])) {
        CALayer* layer = targetLayer;
        while (layer)
        {
            if ([layer isEqual:item.layer])
                return item;
            layer = layer.superlayer;
        }
    }
	return item;
}

@end

_CXXVIEW_IMPL(UICoverFlow);

NNT_END_OBJC
