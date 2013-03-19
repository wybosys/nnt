
# import "Core.h"
# import "UITabBar+WSI.h"
# import "CoreGraphic+WSI.h"
# import <QuartzCore/QuartzCore.h>
# import "UIBadgeIndicator.h"
# import "UIColor+WSI.h"

WSI_BEGIN_OBJC

signal_t kSignalArrowMoving = @"::wsi::ui::arrow:moving";
signal_t kSignalArrowMoved = @"::wsi::ui::arrow:moved";

real kTabMargin = 2.0f;

# define RGBCOLOR(r,g,b) [UIColor colorWithRed:(r)/255.0 green:(g)/255.0 blue:(b)/255.0 alpha:1]
# define RGBACOLOR(r,g,b,a) [UIColor colorWithRed:(r)/255.0 green:(g)/255.0 blue:(b)/255.0 alpha:(a)]

@interface WSIUITabBarItem ()

- (void)synclyt_badge;

@end

@implementation WSIUITabBarItem

@synthesize titleImage, rightBorder, itemStyle, title;
@synthesize normalTitleStyle, selectedTitleStyle, maskNormalColor, maskHighlightColor;
@synthesize selectedColor, selectedEdgeShadow;
@synthesize badgeValue, badgeStyle, badgeLineStyle, badgeColor, badge;
@synthesize enableGraphite;

- (id)init {
    self = [super init];
    if (self == nil)
        return nil;
            
    self.adjustsImageWhenHighlighted = NO;
    self.backgroundColor = [UIColor clearColor];
    self.itemStyle = WSIUITabBarItemStyleDefault;
    self.layer.cornerRadius = 5.f;
    self.layer.masksToBounds = YES;
    self.layer.borderWidth = 0.f;
    
	return self;
}

- (id)initWithTitleImageName:(NSString *)imageName {
    self = [self init];
    if (self == nil)
        return nil;
    
    self.titleImage = [UIImage imageNamed:imageName];

	return self;
}

- (id)initWithTitleImage:(UIImage *)image {
    self = [self init];
    if (self == nil)
        return nil;

    self.titleImage = image;

	return self;
}

- (void)dealloc {
    zero_release(titleImage);
    zero_release(rightBorder);
    zero_release(title);
    zero_release(normalTitleStyle);
    zero_release(selectedTitleStyle);
    zero_release(maskNormalColor);
    zero_release(maskHighlightColor);
    zero_release(selectedColor);
    zero_release(selectedEdgeShadow);
    zero_release(badgeValue);
    zero_release(badgeColor);
    zero_release(badgeLineStyle);
    zero_release(badgeStyle);
    zero_release(badge);
    
    [super dealloc];
}

+ (UIImage*)HighlightImage:(UIImage *)image color:(UIColor *)color bk:(BOOL)bk {
    UIGraphicsBeginImageContext(image.size);
    CGContextRef ctx = UIGraphicsGetCurrentContext();   
    CGRect rect = CGRectMakePtSz(CGPointZero, image.size);    
    
    CGContextSaveGState(ctx);
    //CGContextTranslateCTM(ctx, 0, rect.size.height);
    //CGContextScaleCTM(ctx, 1.f, -1.f);
    //CGContextDrawImage(ctx, rect, image.CGImage);
    //CGContextRestoreGState(ctx);
    CGContextDrawImageOri(ctx, rect, image.CGImage);
    
    CGContextSetBlendMode(ctx, kCGBlendModeLuminosity);
    CGContextSetFillColorWithColor(ctx, color.CGColor);
    CGContextFillRect(ctx, rect);
    
    CGContextSetBlendMode(ctx, kCGBlendModeDestinationIn);
    CGContextDrawImageOri(ctx, rect, image.CGImage);
    
    CGContextSetBlendMode(ctx, kCGBlendModeNormal);
    
    // draw bk.
    if (bk) {
        WCGColor *begin = [WCGColor colorWithRGBA:0x00000099];
        WCGColor *end = [WCGColor colorWithRGBA:0x00000000];
        WCGGradient *grad = [WCGGradient gradientWithBeginningColor:begin endingColor:end];
        grad.angle = 135;
        [grad fillRect:rect inContext:ctx];
    }
    
    UIImage *tgt = UIGraphicsGetImageFromCurrentImageContext();    
    UIGraphicsEndImageContext();
    return tgt;
}

+ (UIImage*)NormalImage:(UIImage *)image color:(UIColor *)color {
    UIGraphicsBeginImageContext(image.size);
    CGContextRef ctx = UIGraphicsGetCurrentContext();
    CGRect rect = CGRectMakeSz(image.size);
    
    //CGContextSaveGState(ctx);
    //CGContextTranslateCTM(ctx, 0, rect.size.height);
    //CGContextScaleCTM(ctx, 1.f, -1.f);
    //CGContextDrawImage(ctx, rect, image.CGImage);
    //CGContextRestoreGState(ctx);
    CGContextDrawImageOri(ctx, rect, image.CGImage);
    
    CGContextSetFillColorWithColor(ctx, color.CGColor);
    CGContextSetBlendMode(ctx, kCGBlendModeSourceAtop);
    CGContextFillRect(ctx, rect);
    
    UIImage *tgt = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return tgt;
}

- (void)drawRect:(CGRect)rect {
    CGContextRef ctx = UIGraphicsGetCurrentContext();    
    CGRect rc_client = self.bounds;
    CGRect rc_img = CGRectZero;
    CGRect rc_title = CGRectZero;
    NSString *theTitle = self.title;
    WCGTextStyle *theNormalTs = self.normalTitleStyle;
    WCGTextStyle *theSelectedTs = self.selectedTitleStyle ? self.selectedTitleStyle : theNormalTs;                 
    
    if (self.selected) {        
                          
        CGSize sz_title = [theSelectedTs sizeOfString:theTitle];
        switch (itemStyle) {
            case WSIUITabBarItemStyleDefault: {            
                rc_img = rc_client;
                rc_img.size.height -= sz_title.height;
                uint width = MIN(rc_img.size.width, rc_img.size.height);
                rc_img.origin.x += (rc_img.size.width - width) * .5f;
                rc_img.size.width = width;
                
                rc_title.size = CGSizeMake(rc_client.size.width, rc_client.size.height - rc_img.size.height);
                rc_title.origin.y = rc_img.origin.y + rc_img.size.height;
            } break;
        }; 
        
        // draw background color
        if ([selectedColor isKindOfClass:[NSArray class]]) {
            uint const count = [(NSArray*)selectedColor count];
            for (uint i = 0; i < count; ++i) {
                UIColor *color = [(NSArray*)selectedColor objectAtIndex:i];
                [color set];
                CGContextSetFillColorWithColor(ctx, color.CGColor);
                CGContextFillRect(ctx, CGRectMake(0, rc_client.size.height * i / count, rc_client.size.width, rc_client.size.height / count));
            }
        } else if ([selectedColor isKindOfClass:[UIColor class]]) {
            CGContextSetFillColorWithColor(ctx, ((UIColor*)selectedColor).CGColor);
            CGContextFillRect(ctx, rect);
        } else if ([selectedColor isKindOfClass:[WCGColor class]]) {
            WCGColor *color = (WCGColor*)selectedColor;
            CGContextSetFillColorWithColor(ctx, color.cgColor);
            CGContextFillRect(ctx, rect);
        } else if ([selectedColor isKindOfClass:[WCGGradient class]]) {
            [(WCGGradient*)selectedColor fillRect:rect inContext:ctx];
        }
        
        // draw edge
        if (selectedEdgeShadow) {
            self.innerShadowColor = selectedEdgeShadow.shadowColor;
            self.innerShadowBlur = selectedEdgeShadow.opacity;
            self.innerShadowLength = selectedEdgeShadow.radius;
            [super drawInnerShadow:ctx];
        }
                
        if (self.titleImage) {
            [[WSIUITabBarItem HighlightImage:self.titleImage 
                                       color:maskHighlightColor 
                                          bk:!self.enableGraphite] drawInRect:rc_img];
            CGContextAddTextInRect(ctx, rc_title, theTitle, theSelectedTs);
        } else {
            CGContextAddTextInRect(ctx, rc_client, theTitle, theSelectedTs);
        }
        
    } else {
        
        CGSize sz_title = [theNormalTs sizeOfString:theTitle];
        switch (itemStyle) {
            case WSIUITabBarItemStyleDefault: {            
                rc_img = rc_client;
                rc_img.size.height -= sz_title.height;
                uint width = MIN(rc_img.size.width, rc_img.size.height);
                rc_img.origin.x += (rc_img.size.width - width) * .5f;
                rc_img.size.width = width;
                
                rc_title.size = CGSizeMake(rc_client.size.width, rc_client.size.height - rc_img.size.height);
                rc_title.origin.y = rc_img.origin.y + rc_img.size.height;
            } break;
        }; 
     
        if (self.titleImage) {
            [[WSIUITabBarItem NormalImage:self.titleImage color:maskNormalColor] drawInRect:rc_img];
            CGContextAddTextInRect(ctx, rc_title, theTitle, theNormalTs);
        } else {
            CGContextAddTextInRect(ctx, rc_client, theTitle, theNormalTs);
        }        
    }    
}

- (void)setFrame:(CGRect)aFrame {
	[super setFrame:aFrame];
    [self synclyt_badge];
    
	//[self setNeedsDisplay];
    
    UIEdgeInsets imageInsets = UIEdgeInsetsMake(floor((self.bounds.size.height / 2) -
                                                      (self.imageView.image.size.height / 2)),
												floor((self.bounds.size.width / 2) -
                                                      (self.imageView.image.size.width / 2)),
												floor((self.bounds.size.height / 2) -
                                                      (self.imageView.image.size.height / 2)),
												floor((self.bounds.size.width / 2) -
                                                      (self.imageView.image.size.width / 2)));
	self.imageEdgeInsets = imageInsets;
}

- (void)setBadgeValue:(NSString *)value {
    [badgeValue release];
    badgeValue = [value copy];
    
    if (!badgeValue || [badgeValue isEqualToString:@""]) {
        if (badge) {
            [badge removeFromSuperview];
            self.badge = nil;
        }
        return;
    }        
    
    if (!badge) {
        badge = [[UIBadgeIndicator alloc] init];
        [self.superview addSubview:badge];
    }
    
    badge.badgeLineStyle = self.badgeLineStyle;
    badge.badgeColor = self.badgeColor;
    badge.badgeStyle = self.badgeStyle;
    badge.value = badgeValue;

    [self synclyt_badge];    
}

- (void)synclyt_badge {
    if (badge == nil)
        return;
    
    CGRect rc_frame = self.frame;
    CGPoint pt_rt = CGRectRightTop(&rc_frame);
    [badge moveToCenter:pt_rt];
}

@end

@implementation WSIUITabBarItemArrow

@synthesize color;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    self.backgroundColor = [UIColor clearColor];
    self.color = [UIColor blackColor];
    
    return self;
}

- (void)dealloc {
    zero_release(color);
    
    [super dealloc];
}

- (void)drawRect:(CGRect)rect {
    CGContextRef ctx = UIGraphicsGetCurrentContext();
    
    CGMutablePathRef path = CGPathCreateMutable();    
    CGPathMoveToPoint(path, nil, rect.origin.x, rect.origin.y);
    CGPathAddLineToPoint(path, nil, rect.origin.x + rect.size.width, rect.origin.y);
    CGPathAddLineToPoint(path, nil, rect.origin.x + rect.size.width * .5f, rect.origin.y + rect.size.height);
    CGPathCloseSubpath(path);
    
    CGContextAddPath(ctx, path);
    CGContextSetFillColorWithColor(ctx, color.CGColor);
    CGContextFillPath(ctx);
    
    CGPathRelease(path);
}

@end

@interface WSIUITabBar ()

- (void)positionArrowAnimated:(BOOL)animated;

@end

@implementation WSIUITabBar

@synthesize padding;
@synthesize tabs, delegate, arrow, selectedTab;
@synthesize normalTitleStyle, selectedTitleStyle, maskNormalColor, maskHighlightColor;
@synthesize itemSelectedColor, itemSelectedEdgeShadow;
@synthesize arrowPosition;
@synthesize badgeStyle, badgeLineStyle, badgeColor;
@synthesize enableGraphite;
@synthesize itemWidth;
@synthesize preferredCount;

- (id)initWithFrame:(CGRect)aFrame {    
	self = [super initWithFrame:aFrame];
    if (self) {
        
		self.userInteractionEnabled = YES;
        
        WCGMutableTextStyle *ts = [WCGMutableTextStyle new];
        ts.fontSize = 15;
        ts.color = [WCGColor whiteColor];
        ts.alignment = WCGAlignmentCenter;
        self.normalTitleStyle = ts;      
        [ts release];
        
        ts = [WCGMutableTextStyle new];
        ts.fontSize = 15;
        ts.color = [WCGColor whiteColor];
        ts.alignment = WCGAlignmentCenter;
        ts.textShadow = [CGShadow textShadow];
        self.selectedTitleStyle = ts;        
        [ts release];
        
        self.maskHighlightColor = [UIColor colorWithRGBA:0x3399CCFF];
        self.maskNormalColor = [UIColor colorWithRGBA:0xFFFFFFFF];
        
        self.itemSelectedColor = [NSArray arrayWithObjects:[UIColor colorWithRGB:0x1b1b1b], [UIColor colorWithRGB:0x0d0d0d], nil];
                    
        arrow = [[WSIUITabBarItemArrow alloc] initWithFrame:CGRectMake(0, 0, 10, 10)];        
        self.arrowPosition = UITabBarArrowPositionTop;
		[self addSubview:self.arrow];
        
        WCGMutableLineStyle *ls = [WCGMutableLineStyle new];
        ls.lineColor = [WCGColor whiteColor];
        ls.lineWidth = 2;
        self.badgeLineStyle = ls;
        [ls release];
                
        self.badgeColor = [UIColor redColor];
        
        ts = [WCGMutableTextStyle new];
        ts.fontSize = 16;
        ts.color = [WCGColor whiteColor];
        ts.alignment = WCGAlignmentCenter;
        self.badgeStyle = ts;        
        [ts release];
        
        enableGraphite = NO;
        itemWidth = 0;
	}
	
	return self;
}

- (void)dealloc {
    zero_release(tabs);
    zero_release(arrow);
    zero_release(normalTitleStyle);
    zero_release(selectedTitleStyle);
    zero_release(maskHighlightColor);
    zero_release(maskNormalColor);
    zero_release(itemSelectedColor);
    zero_release(badgeColor);
    zero_release(badgeLineStyle);
    zero_release(badgeStyle);
    
    [super dealloc];
}

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalSelectChanged)
WSIEVENT_SIGNAL(kSignalArrowMoving)
WSIEVENT_SIGNAL(kSignalArrowMoved)
WSIEVENT_END

- (void)setArrow:(UIView *)view {
    [arrow removeFromSuperview];
    [NSObject refobjSet:&arrow ref:view];
    if (arrow) {
        [self addSubview:arrow];
    }
}

- (void)setTabs:(NSArray *)array {
	for (WSIUITabBarItem *each in tabs) {
		[each removeFromSuperview];
	}
	
	[tabs release];
	tabs = [array retain];
	
    for (uint i = 0; i < [array count]; ++i) {
        WSIUITabBarItem *item = [array objectAtIndex:i];
        
        item.userInteractionEnabled = YES;
        item.selectedColor = self.itemSelectedColor;
        
		[item addTarget:self action:@selector(tabSelected:) forControlEvents:UIControlEventTouchDown];
        if (item.superview) {
            @throw [NSException exceptionWithName:@"tabitem" reason:@"item has parent" userInfo:nil];
        }
        [self addSubview:item];
    }
}

- (void)setSelectedTab:(WSIUITabBarItem *)aTab animated:(BOOL)animated {
	if (aTab == selectedTab)
        return;
    
    selectedTab.selected = NO;
    selectedTab = aTab;
    selectedTab.selected = YES;
    
    // event.
    [self emit:kSignalSelectChanged result:selectedTab];
    
    // move arrow.
    [self positionArrowAnimated:animated];        
}

- (void)setSelectedTab:(WSIUITabBarItem *)aTab {
	[self setSelectedTab:aTab animated:YES];
}

- (void)tabSelected:(WSIUITabBarItem *)sender {
	[self.delegate tabBar:self didSelectTabAtIndex:[self.tabs indexOfObject:sender]];
}

- (void)positionArrowAnimated:(BOOL)animated {
    [self emit:kSignalArrowMoving];
    
	if (animated) {
		[UIView beginAnimations:nil context:NULL];
		[UIView setAnimationDuration:0.2];
	}
    
	CGRect f = self.arrow.frame;
	f.origin.x = self.selectedTab.frame.origin.x + ((self.selectedTab.frame.size.width / 2) - (f.size.width / 2));
	self.arrow.frame = f;
	
	if (animated) {
		[UIView commitAnimations];
	}
    
    [self emit:kSignalArrowMoved];
}

/*
- (void)setBounds:(CGRect)bounds {
    [super setBounds:bounds];    
    [self updateLayout:bounds];
}
 */

- (real)itemWidth {
    if (itemWidth)
        return itemWidth;
    if (preferredCount)
        return self.bounds.size.width / preferredCount;
    return 0;
}

- (CGSize)calcItemSize {
    uint const tabs_count = [self.tabs count];
    if (tabs_count == 0)
        return CGSizeZero;
    
    CGRect rect = self.bounds;
    
    if (self.itemWidth == 0) {       
        rect.size.width /= tabs_count;
        rect.size.width -= (kTabMargin * (tabs_count + 1)) / tabs_count;
        
        if (arrowPosition == UITabBarArrowPositionTop) {
            CGRect rc = self.arrow.frame;
            rect.origin.y += rc.size.height;
            rect.size.height -= rc.size.height;
        } else if (arrowPosition == UITabBarArrowPositionBottom) {
            CGRect rc = self.arrow.frame;
            rect.size.height -= rc.size.height;
        }                
    } else {    
        rect.size.width = self.itemWidth;
        
        if (arrowPosition == UITabBarArrowPositionTop) {
            CGRect rc = self.arrow.frame;
            rect.origin.y += rc.size.height;
            rect.size.height -= rc.size.height;
        } else if (arrowPosition == UITabBarArrowPositionBottom) {
            CGRect rc = self.arrow.frame;
            rect.size.height -= rc.size.height;
        }        
    }
    
    return rect.size;
}

- (void)updateLayout:(CGRect)rect {
    uint const tabs_count = [self.tabs count];
    if (tabs_count == 0)
        return;
    
    rect = CGRectAdd(rect, 
                     padding.left, 
                     padding.top, 
                     -CGPaddingGetWidth(&padding), 
                     -CGPaddingGetHeight(&padding));
    
    switch (arrowPosition)
    {
        case UITabBarArrowPositionNone: {
            arrow.hidden = YES;
        } break;
        case UITabBarArrowPositionTop: {
            arrow.hidden = NO;
            CGRect rc = self.arrow.frame;
            rc.origin = CGPointZero;
            self.arrow.frame = rc;
        } break;
        case UITabBarArrowPositionBottom: {
            arrow.hidden = NO;
            CGRect rc = self.arrow.frame;
            rc.origin = CGPointZero;
            rc.origin.y = self.bounds.size.height - rc.size.height;
            self.arrow.frame = rc;
        } break;
        case UITabBarArrowPositionCustom: {
            arrow.hidden = NO;
            CGPoint pos = CGRectCenterPoint(&rect);
            [self.arrow moveToCenter:pos];
        } break;
    }        
    
    if (self.itemWidth == 0) {       
        rect.size.width /= tabs_count;
        rect.size.width -= (kTabMargin * (tabs_count + 1)) / tabs_count;
        
        if (arrowPosition == UITabBarArrowPositionTop) {
            CGRect rc = self.arrow.frame;
            rect.origin.y += rc.size.height;
            rect.size.height -= rc.size.height;
        } else if (arrowPosition == UITabBarArrowPositionBottom) {
            CGRect rc = self.arrow.frame;
            rect.size.height -= rc.size.height;
        }
        
        for (WSIUITabBarItem *tab in self.tabs) {
            rect.origin.x += kTabMargin;
            tab.frame = rect;
            rect.origin.x += rect.size.width;        		
        }
        
    } else {
        
        real full_width = tabs_count * self.itemWidth;
        real spacing = (rect.size.width - full_width) * .5f;
        rect.size.width = self.itemWidth;
        
        if (arrowPosition == UITabBarArrowPositionTop) {
            CGRect rc = self.arrow.frame;
            rect.origin.y += rc.size.height;
            rect.size.height -= rc.size.height;
        } else if (arrowPosition == UITabBarArrowPositionBottom) {
            CGRect rc = self.arrow.frame;
            rect.size.height -= rc.size.height;
        }
        
        rect.origin.x = spacing;
        for (WSIUITabBarItem *tab in self.tabs) {
            tab.frame = rect;
            rect.origin.x += self.itemWidth;
        }
        
    }
}

- (void)layoutSubviews {               
    CGRect f = self.bounds;    
    [self updateLayout:f];    	
	[self positionArrowAnimated:NO];
}

@end

WSI_END_OBJC