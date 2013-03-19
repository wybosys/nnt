
# import "Core.h"
# import "UIPageControl+NNT.h"
# import "UIView+NNT.h"
# import "NNTUIObject.h"

NNT_BEGIN_OBJC

#define kDotDiameter	4.0f
#define kDotSpace		12.0f

@implementation NNTUIPageControl

@synthesize selectedColor = _selectedColor, normalColor = _normalColor;
@synthesize numberOfPages = _numberOfPages, currentPage = _currentPage;
@synthesize hidesForSinglePage;
@synthesize defersCurrentPageDisplay;
@synthesize type;
@synthesize indicatorDiameter;
@synthesize indicatorSpace;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];

    _selectedColor = [[UIColor whiteColor] retain];
    _normalColor = [[UIColor grayColor] retain];
    self.backgroundColor = [UIColor clearColor];
    type = UIPageControlTypeOnFullOffFull;
    self.hidesForSinglePage = YES;
    
    [self connect:kSignalTouchesEnd sel:@selector(_act_touches:)];
    
    return self;
}

- (id)initWithType:(UIPageControlType)theType {
	self = [self initWithFrame:CGRectZero];
    type = theType;
	return self;
}

- (void)dealloc {
    zero_release(_selectedColor);
    zero_release(_normalColor);
    [super dealloc];
}

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalSelectChanged);
NNTEVENT_END

# pragma mark overdraw

- (CGRect)stageRect {    
    // get the caller's diameter if it has been set or use the default one
	CGFloat diameter = (indicatorDiameter > 0) ? indicatorDiameter : kDotDiameter;
	CGFloat space = (indicatorSpace > 0) ? indicatorSpace : kDotSpace;
    
    // geometry
	CGRect currentBounds = self.bounds;
	CGFloat dotsWidth = self.numberOfPages * diameter + MAX(0, self.numberOfPages - 1) * space;
	CGFloat x = CGRectGetMidX(currentBounds) - dotsWidth / 2;
	CGFloat y = CGRectGetMidY(currentBounds) - diameter / 2;
    
    CGRect rc;
    rc.origin.x = x;
    rc.origin.y = y;
    
	// actually draw the dots
	for (int i = 0; i < _numberOfPages; ++i)
	{
		x += diameter + space;
	}

    rc.size.width = x - rc.origin.x - space;
    rc.size.height = diameter;
    
    if ((type == UIPageControlTypeOnFullOffFull || type == UIPageControlTypeOnFullOffEmpty) ||
        !(type == UIPageControlTypeOnEmptyOffEmpty || type == UIPageControlTypeOnFullOffEmpty))
    {
        rc = CGRectInset(rc, -1, -1);
    }
    
    return rc;
}

- (void)drawRect:(CGRect)rect {
    // get the current context
	CGContextRef context = UIGraphicsGetCurrentContext();
    
	// save the context
	CGContextSaveGState(context);
    
	// allow antialiasing
	CGContextSetAllowsAntialiasing(context, TRUE);
    
	// get the caller's diameter if it has been set or use the default one 
	CGFloat diameter = (indicatorDiameter > 0) ? indicatorDiameter : kDotDiameter;
	CGFloat space = (indicatorSpace > 0) ? indicatorSpace : kDotSpace;
    
	// geometry
	CGRect currentBounds = self.bounds;
	CGFloat dotsWidth = self.numberOfPages * diameter + MAX(0, self.numberOfPages - 1) * space;
	CGFloat x = CGRectGetMidX(currentBounds) - dotsWidth / 2;
	CGFloat y = CGRectGetMidY(currentBounds) - diameter / 2;
    
	// get the caller's colors it they have been set or use the defaults
	CGColorRef onColorCG = _selectedColor ? _selectedColor.CGColor : [UIColor colorWithWhite: 1.0f alpha: 1.0f].CGColor;
	CGColorRef offColorCG = _normalColor ? _normalColor.CGColor : [UIColor colorWithWhite: 0.7f alpha: 0.5f].CGColor;
    
	// actually draw the dots
	for (int i = 0; i < _numberOfPages; ++i)
	{
		CGRect dotRect = CGRectMake(x, y, diameter, diameter);
        
		if (i == _currentPage)
		{
			if (type == UIPageControlTypeOnFullOffFull || type == UIPageControlTypeOnFullOffEmpty)
			{
				CGContextSetFillColorWithColor(context, onColorCG);
				CGContextFillEllipseInRect(context, CGRectInset(dotRect, -1.0f, -1.0f));
			}
			else
			{
				CGContextSetStrokeColorWithColor(context, onColorCG);
				CGContextStrokeEllipseInRect(context, dotRect);
			}
		}
		else
		{
			if (type == UIPageControlTypeOnEmptyOffEmpty || type == UIPageControlTypeOnFullOffEmpty)
			{
				CGContextSetStrokeColorWithColor(context, offColorCG);
				CGContextStrokeEllipseInRect(context, dotRect);
			}
			else
			{
				CGContextSetFillColorWithColor(context, offColorCG);
				CGContextFillEllipseInRect(context, CGRectInset(dotRect, -1.0f, -1.0f));
			}
		}
        
		x += diameter + space;
	}
    
	// restore the context
	CGContextRestoreGState(context);
}

#pragma mark -
#pragma mark Accessors

- (void)changeCurrentPage:(NSInteger)pageNumber {
    // no need to update in that case
	if (_currentPage == pageNumber)
		return;
    
	// determine if the page number is in the available range
	_currentPage = MIN(MAX(0, pageNumber), _numberOfPages - 1);
    
	// in case we do not defer the page update, we redraw the view
	if (self.defersCurrentPageDisplay == NO)
		[self setNeedsDisplay];
}

- (void)setCurrentPage:(NSInteger)pageNumber {
	[self changeCurrentPage:pageNumber];
    
    // event.
    [self emit:kSignalSelectChanged result:wsi::number(_currentPage)];
}

- (NSInteger)currentPage {
    return _currentPage;
}

- (void)setNumberOfPages:(NSInteger)numOfPages {
	// make sure the number of pages is positive
	_numberOfPages = MAX(0, numOfPages);
    
	// we then need to update the current page
	_currentPage = MIN(MAX(0, _currentPage), _numberOfPages - 1);
    
	// correct the bounds accordingly
	self.bounds = self.bounds;
    
	// we need to redraw
	[self setNeedsDisplay];
    
	// depending on the user preferences, we hide the page control with a single element
	if (hidesForSinglePage && (numOfPages < 2))
		[self setHidden: YES];
	else
		[self setHidden: NO];
}

- (NSInteger)numberOfPages {
    return _numberOfPages;
}

- (void)setHidesForSinglePage:(BOOL)hide {
	hidesForSinglePage = hide;
    
	// depending on the user preferences, we hide the page control with a single element
	if (hidesForSinglePage && (_numberOfPages < 2))
		[self setHidden: YES];
}

- (void)setDefersCurrentPageDisplay:(BOOL)defers {
	defersCurrentPageDisplay = defers;
}

- (void)setType:(UIPageControlType)aType {
	type = aType;
    
	[self setNeedsDisplay];
}

- (void)setSelectedColor:(UIColor *)color {
    [NSObject refobjSet:&_selectedColor ref:color];
    [self setNeedsDisplay];
}

- (void)setNormalColor:(UIColor *)color {
    [NSObject refobjSet:&_normalColor ref:color];
    [self setNeedsDisplay];
}

- (void)setIndicatorDiameter:(CGFloat)aDiameter {
	indicatorDiameter = aDiameter;
    
	// correct the bounds accordingly
	self.bounds = self.bounds;
    
	[self setNeedsDisplay];
}

- (void)setIndicatorSpace:(CGFloat)aSpace {
	indicatorSpace = aSpace;
    
	// correct the bounds accordingly
	self.bounds = self.bounds;
    
	[self setNeedsDisplay];
}

- (void)setFrame:(CGRect)aFrame {
    CGRect rc = aFrame;
	rc.size = [self sizeForNumberOfPages:_numberOfPages];
    if (rc.size.width > aFrame.size.width)
        aFrame.size.width = rc.size.width;
    if (rc.size.height > aFrame.size.height)
        aFrame.size.height = rc.size.height;
	super.frame = aFrame;
}

- (void)setBounds:(CGRect)aBounds {
    CGRect rc = aBounds;
	rc.size = [self sizeForNumberOfPages:_numberOfPages];
    if (rc.size.width > aBounds.size.width)
        aBounds.size.width = rc.size.width;
    if (rc.size.height > aBounds.size.height)
        aBounds.size.height = rc.size.height;
	super.bounds = aBounds;
}

#pragma mark -
#pragma mark UIPageControl methods

- (void)updateCurrentPageDisplay {
	// ignores this method if the value of defersPageIndicatorUpdate is NO
	if (self.defersCurrentPageDisplay == NO)
		return;
    
	// in case it is YES, we redraw the view (that will update the page control to the correct page)
	[self setNeedsDisplay];
}

- (CGSize)sizeForNumberOfPages:(NSInteger)pageCount {
	CGFloat diameter = (indicatorDiameter > 0) ? indicatorDiameter : kDotDiameter;
	CGFloat space = (indicatorSpace > 0) ? indicatorSpace : kDotSpace;
	return CGSizeMake(pageCount * diameter + (pageCount - 1) * space + 44.0f, 0);
}

#pragma mark -
#pragma mark Touches handlers

- (void)_act_touches:(NNTEventObj*)evt {
    NSSet* touches = (NSSet*)evt.result;
    
	// get the touch location
	UITouch *theTouch = [touches anyObject];
	CGPoint touchLocation = [theTouch locationInView: self];
    
	// check whether the touch is in the right or left hand-side of the control
	if (touchLocation.x < (self.bounds.size.width / 2))
		self.currentPage = MAX(self.currentPage - 1, 0);
	else
		self.currentPage = MIN(self.currentPage + 1, _numberOfPages - 1);
}

@end

NNT_END_OBJC
