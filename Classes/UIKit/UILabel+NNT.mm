
# import "Core.h"
# import "UILabel+NNT.h"
# import "FontManager.h"
# import "FontLabelStringDrawing.h"
# import "ZFont.h"
# import "UIObject+NNT.h"
# import "NGFill.h"
# import "StyleStringParser.h"
# import "NSStyleString.h"
# import "UIScreen+NNT.h"
# import "UIView+NNT.h"
# import "QzDisplayLink.h"

NNT_BEGIN_OBJC

signal_t kSignalMarqueeNext = @"::nnt::marquee::next";

static CGPoint __gs_view_touchpoint = {-999999, -999999};
static BOOL __gs_view_waitingtouch = NO;

@implementation UILabel (NNT)

NNTUIVIEW_NOTINHERIT_MUST_IMPL;

- (void)applyTextStyle:(NgTextStyle*)ts {
    self.font = [ts uiFont];
    
    UIColor* color = [[UIColor alloc] initWithCGColor:ts.color.cgColor];
    self.textColor = color;
    [color release];
    
    self.textAlignment = (UITextAlignment)ts.alignment;
}

@end

@interface NNTUILabel ()

- (void)_update_fontscale;

@end

@implementation NNTUILabel

NNTOBJECT_IMPL_NOSIGNALS;

@dynamic multiLines;
@synthesize scaleToFit = _scaleToFit;
//@synthesize zFont;
//@synthesize zAttributedText;
@synthesize backgroundFill = _backgroundFill;
@synthesize sendGlobalEvent = _sendGlobalEvent;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    self.backgroundColor = [UIColor clearColor];
    self.userInteractionEnabled = YES;
    _sendGlobalEvent = YES;
    _scaleToFit = NO;
    
    return self;
}

- (void)dealloc {            
    //zero_release(zFont);
	//zero_release(zAttributedText);
    zero_release(_backgroundFill);
    
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

- (void)setMultiLines:(BOOL)val {
    if (val) {
        self.numberOfLines = 0;
    } else {
        self.numberOfLines = 1;
    }
}

- (BOOL)multiLines {
    return self.numberOfLines != 1;
}

- (void)initSignals {
    NNTEVENT_SIGNAL(kSignalViewClicked);
    NNTEVENT_SIGNAL(kSignalTouchesBegin);
    NNTEVENT_SIGNAL(kSignalTouchesEnd);
    NNTEVENT_SIGNAL(kSignalTouchesMoved);
    NNTEVENT_SIGNAL(kSignalTouchesCancel);
}

- (void)copyStyle:(UILabel *)r {
    self.font = r.font;
    self.textColor = r.textColor;
    self.textAlignment = r.textAlignment;
    self.backgroundColor = r.backgroundColor;
}

- (void)setBackgroundFill:(NgFill *)fill {
    [NNTObject refobjSet:&_backgroundFill ref:fill];
}

- (void)drawRect:(CGRect)rect {         
    CGContextRef ctx = UIGraphicsGetCurrentContext();
    
    // fill background.
    [_backgroundFill fillRect:rect inContext:ctx];
    
    // super draw.
    [super drawRect:rect];        
}

- (CGSize)textSize {
    CGSize ret;
    
    NNT_SYNCHRONIZED(self)
    
    NSString* tmpstr = [NSString stringWithFormat:@" %@ ", self.text];
    ret = [tmpstr sizeWithFont:self.font];
    
    NNT_SYNCHRONIZED_END
    
    return ret;
}

- (CGSize)directTextSize {
    CGSize ret;
    
    NNT_SYNCHRONIZED(self)
    
    ret = [self.text sizeWithFont:self.font];
    
    NNT_SYNCHRONIZED_END
    
    return ret;
}

- (CGSize)textSize:(NSString *)str {
    CGSize sz = [str sizeWithFont:self.font forWidth:self.bounds.size.width lineBreakMode:self.lineBreakMode];
    return sz;
}

- (CGSize)textsSize {
    CGSize ret;
    
    NNT_SYNCHRONIZED(self)
    
    CGRect rc = [self textRectForBounds:CGRectMake(0, 0, 9999, 9999) limitedToNumberOfLines:self.numberOfLines];
    ret = rc.size;
    
    NNT_SYNCHRONIZED_END
    
    return ret;
}

- (void)setFrame:(CGRect)frame {
    // set frame, it frame is float, the text will blur.
    [super setFrame:CGRectIntegral(frame)];
}

- (void)setBounds:(CGRect)bounds {
    [super setBounds:bounds];
    
    // update font.
    if (_scaleToFit)
        [self _update_fontscale];
}

- (void)setScaleToFit:(BOOL)val {
    if (_scaleToFit == val)
        return;
    _scaleToFit = val;
    [self _update_fontscale];
}

- (void)setText:(NSString *)text {
    [super setText:text];
    
    if (_scaleToFit)
        [self _update_fontscale];
}

- (void)_update_fontscale {
    if (self.multiLines)
        return;
        
    usize len_str = [self.text length];
    if (len_str == 0)
        return;
    
    real size = [self fitableFontSize];
    self.font = [UIFont fontWithName:self.font.fontName size:size];
}

- (real)fitableFontSize {
    if (self.multiLines)
        return self.font.pointSize;
    
    usize len_str = [self.text length];
    if (len_str == 0)
        return self.font.pointSize;
    
    CGSize sz_acture = [self textSize];
    CGSize sz_vis = self.bounds.size;
    real retw = sz_vis.width / sz_acture.width;
    real reth = sz_vis.height / sz_acture.height;
    real ret = MIN(retw, reth);
    
    ret *= self.font.pointSize;
    
    return ret;
}

# pragma mark view touch

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    __gs_view_waitingtouch = TRUE;  
    __gs_view_touchpoint = [[touches anyObject] locationInView:self];
    
    if (_sendGlobalEvent)
        UIViewEmitGlobalEvent(kSignalTouchesBegin, self, touches, event);
    [self emit:kSignalTouchesBegin result:touches data:event];
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {    
    if (__gs_view_waitingtouch == NO)
        return;
    
    CGPoint pt = [[touches anyObject] locationInView:self];
    if (CGPointEqualWithPrecise(pt, __gs_view_touchpoint, kUITouchRadius)) {
        [self emit:kSignalViewClicked result:touches data:event];
    }
    
    if (_sendGlobalEvent)
        UIViewEmitGlobalEvent(kSignalTouchesEnd, self, touches, event);
    [self emit:kSignalTouchesEnd result:touches data:event];
    
    __gs_view_touchpoint = kUITouchSky;
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {
    __gs_view_waitingtouch = NO;
    
    if (_sendGlobalEvent)
        UIViewEmitGlobalEvent(kSignalTouchesCancel, self, touches, event);
    [self emit:kSignalTouchesCancel result:touches data:event];    
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
    if (_sendGlobalEvent)
        UIViewEmitGlobalEvent(kSignalTouchesMoved, self, touches, event);
    [self emit:kSignalTouchesMoved result:touches data:event];
}

@end

/*

@interface ZFont (ZFontPrivate)

@property (nonatomic, readonly) CGFloat ratio;

@end

@implementation NNTUILabel (FontLabel)

- (id)initWithFrame:(CGRect)frame fontName:(NSString *)fontName pointSize:(CGFloat)pointSize {
	return [self initWithFrame:frame zFont:[[FontManager sharedManager] zFontWithName:fontName pointSize:pointSize]];
}

- (id)initWithFrame:(CGRect)frame zFont:(ZFont *)font {
	if ((self = [self initWithFrame:frame])) {
		zFont = [font retain];
	}
	return self;
}

- (id)initWithFrame:(CGRect)frame font:(CGFontRef)font pointSize:(CGFloat)pointSize {
	return [self initWithFrame:frame zFont:[ZFont fontWithCGFont:font size:pointSize]];
}

- (CGFontRef)cgFont {
	return self.zFont.cgFont;
}

- (void)setCGFont:(CGFontRef)font {
	if (self.zFont.cgFont != font) {
		self.zFont = [ZFont fontWithCGFont:font size:self.zFont.pointSize];
	}
}

- (CGFloat)pointSize {
	return self.zFont.pointSize;
}

- (void)setPointSize:(CGFloat)pointSize {
	if (self.zFont.pointSize != pointSize) {
		self.zFont = [ZFont fontWithCGFont:self.zFont.cgFont size:pointSize];
	}
}

- (void)setZAttributedText:(ZAttributedString *)attStr {
	if (zAttributedText != attStr) {
		[zAttributedText release];
		zAttributedText = [attStr copy];
		[self setNeedsDisplay];
	}
}

- (void)drawTextInRect:(CGRect)rect {
	if ((zFont == NULL) && (zAttributedText == nil)) {
        
        if (enableMarquee && marqueeIsNeeded) {
            rect.origin.x += __offset;
            rect.size.width = __width;
        }
                
		[super drawTextInRect:rect];
        
		return;
	}
	
	if (self.zAttributedText == nil) {
		// this method is documented as setting the text color for us, but that doesn't appear to be the case
		if (self.highlighted) {
			[(self.highlightedTextColor ?: [UIColor whiteColor]) setFill];
		} else {
			[(self.textColor ?: [UIColor blackColor]) setFill];
		}
		
		ZFont *actualFont = self.zFont;
		CGSize origSize = rect.size;
		if (self.numberOfLines == 1) {
			origSize.height = actualFont.leading;
			CGPoint point = CGPointMake(rect.origin.x,
										rect.origin.y + roundf(((rect.size.height - actualFont.leading) / 2.0f)));
			CGSize size = [self.text sizeWithZFont:actualFont];
			if (self.adjustsFontSizeToFitWidth && self.minimumFontSize < actualFont.pointSize) {
				if (size.width > origSize.width) {
					CGFloat desiredRatio = (origSize.width * actualFont.ratio) / size.width;
					CGFloat desiredPointSize = desiredRatio * actualFont.pointSize / actualFont.ratio;
					actualFont = [actualFont fontWithSize:MAX(MAX(desiredPointSize, self.minimumFontSize), 1.0f)];
					size = [self.text sizeWithZFont:actualFont];
				}
				if (!CGSizeEqualToSize(origSize, size)) {
					switch (self.baselineAdjustment) {
						case UIBaselineAdjustmentAlignCenters:
							point.y += roundf((origSize.height - size.height) / 2.0f);
							break;
						case UIBaselineAdjustmentAlignBaselines:
							point.y += (self.zFont.ascender - actualFont.ascender);
							break;
						case UIBaselineAdjustmentNone:
							break;
					}
				}
			}
			size.width = MIN(size.width, origSize.width);
			// adjust the point for alignment
			switch (self.textAlignment) {
				case UITextAlignmentLeft:
					break;
				case UITextAlignmentCenter:
					point.x += (origSize.width - size.width) / 2.0f;
					break;
				case UITextAlignmentRight:
					point.x += origSize.width - size.width;
					break;
			}
			[self.text drawAtPoint:point forWidth:size.width withZFont:actualFont lineBreakMode:self.lineBreakMode];
		} else {
			CGSize size = [self.text sizeWithZFont:actualFont constrainedToSize:origSize lineBreakMode:self.lineBreakMode numberOfLines:self.numberOfLines];
			CGPoint point = rect.origin;
			point.y += roundf((rect.size.height - size.height) / 2.0f);
			rect = (CGRect){point, CGSizeMake(rect.size.width, size.height)};
			[self.text drawInRect:rect withZFont:actualFont lineBreakMode:self.lineBreakMode alignment:self.textAlignment numberOfLines:self.numberOfLines];
		}
	} else {
		ZAttributedString *attStr = self.zAttributedText;
		if (self.highlighted) {
			// modify the string to change the base color
			ZMutableAttributedString *mutStr = [[attStr mutableCopy] autorelease];
			NSRange activeRange = NSMakeRange(0, attStr.length);
			while (activeRange.length > 0) {
				NSRange effective;
				UIColor *color = [attStr attribute:ZForegroundColorAttributeName atIndex:activeRange.location
							 longestEffectiveRange:&effective inRange:activeRange];
				if (color == nil) {
					[mutStr addAttribute:ZForegroundColorAttributeName value:[UIColor whiteColor] range:effective];
				}
				activeRange.location += effective.length, activeRange.length -= effective.length;
			}
			attStr = mutStr;
		}
		CGSize size = [attStr sizeConstrainedToSize:rect.size lineBreakMode:self.lineBreakMode numberOfLines:self.numberOfLines];
		CGPoint point = rect.origin;
		point.y += roundf((rect.size.height - size.height) / 2.0f);
		rect = (CGRect){point, CGSizeMake(rect.size.width, size.height)};
		[attStr drawInRect:rect withLineBreakMode:self.lineBreakMode alignment:self.textAlignment numberOfLines:self.numberOfLines];
	}
}

- (CGRect)textRectForBounds:(CGRect)bounds limitedToNumberOfLines:(NSInteger)numberOfLines {        
	if (self.zFont == NULL && self.zAttributedText == nil) {
        return [super textRectForBounds:bounds limitedToNumberOfLines:numberOfLines];
	}
	
	if (numberOfLines == 1) {
		// if numberOfLines == 1 we need to use the version that converts spaces
		CGSize size;
		if (self.zAttributedText == nil) {
			size = [self.text sizeWithZFont:self.zFont];
		} else {
			size = [self.zAttributedText size];
		}
		bounds.size.width = MIN(bounds.size.width, size.width);
		bounds.size.height = MIN(bounds.size.height, size.height);
	} else {
		if (numberOfLines > 0) bounds.size.height = MIN(bounds.size.height, self.zFont.leading * numberOfLines);
		if (self.zAttributedText == nil) {
			bounds.size = [self.text sizeWithZFont:self.zFont constrainedToSize:bounds.size lineBreakMode:self.lineBreakMode];
		} else {
			bounds.size = [self.zAttributedText sizeConstrainedToSize:bounds.size lineBreakMode:self.lineBreakMode];
		}
	}
    
	return bounds;
}

@end
 
 */

NNTIMPL_CATEGORY(UILabel, NNT);

@implementation UIStyleLabel

@synthesize styleStrings;

- (void)dealloc {
    [styleStrings release];
    [super dealloc];
}

- (void)setText:(NSString *)text {
    StyleStringParser* parser = [[StyleStringParser alloc] init];
    [parser parseString:text];
    [super setText:parser.string];
    self.styleStrings = parser.styleStrings;
    [parser release];
}

- (void)setStyleStrings:(NSArray *)arr {
    [NSObject refobjSet:&styleStrings ref:arr];
    
    if (self.text == nil &&
        styleStrings != nil) {
        
        NSMutableString* str = [[NSMutableString alloc] init];
        for (NSStyleString* each in styleStrings) {
            [str appendString:each.string];
        }
        [super setText:str];
        [str release];
    }
}

- (void)drawTextInRect:(CGRect)rect {
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGPoint cur_pt = rect.origin;
    for (NSStyleString* each in styleStrings) {
        CGSize sz = [each.textStyle sizeOfString:each.string];
        CGContextAddTextAtPoint(context, cur_pt, each.string, each.textStyle);
        cur_pt.x += sz.width;
    }
}

@end

_CXXCONTROL_IMPL(NNTUILabel);

NNTDECL_PRIVATE_BEGIN(UIMarqueeLabel, NNTObject)
{
@public
    int offset;
    int width;
    bool valid;
    bool need;
    NNTNSTimer* timer;
}

NNTDECL_PRIVATE_IMPL(UIMarqueeLabel)

- (id)init {
    self = [super init];
    
    valid = need = false;
    
    timer = [[NNTNSTimer alloc] init];
    [timer connect:kSignalTimerFired sel:@selector(act_marquee_routine) obj:self];
    
    return self;
}

- (void)dealloc {
    safe_release(timer);
    
    [super dealloc];
}

- (void)act_marquee_routine {
    if (d_owner.hidden == YES) {
        valid = false;
        return;
    }
    
    need = valid = true;
    
    CGSize sz_str = [d_owner textSize];
    CGSize sz_client = d_owner.bounds.size;
    
    offset -= d_owner.marqueeStep;
    width = MAX(sz_str.width, sz_client.width);
    
    if (offset < -sz_str.width) {
        offset = sz_client.width;
        
        // next.
        [d_owner emit:kSignalMarqueeNext];
    }
    
    // refresh.
    [d_owner setNeedsDisplay];
}

NNTDECL_PRIVATE_END

@implementation UIMarqueeLabel

@synthesize
marqueeSpeed = _marqueeSpeed,
marqueeStep = _marqueeStep;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    _marqueeStep = 1;
    _marqueeSpeed = 10;
    
    NNTDECL_PRIVATE_INIT(UIMarqueeLabel);
    return self;
}

- (void)dealloc {    
    NNTDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalMarqueeNext);
NNTEVENT_END

- (void)layoutSubviews {
    [super layoutSubviews];
    
    d_ptr->offset = self.bounds.size.width;
}

- (void)removeFromSuperview {
    [self stop];
    [super removeFromSuperview];
}

- (void)start {
    if (NO == [self.text notEmpty])
        [self emit:kSignalMarqueeNext];
    
    d_ptr->timer.interval = _marqueeSpeed * 0.001f;
    [d_ptr->timer start];
}

- (void)stop {
    [d_ptr->timer stop];
}

- (void)drawTextInRect:(CGRect)rect {
    if (d_ptr->valid && d_ptr->need) {
        rect.origin.x += d_ptr->offset;
        rect.size.width = d_ptr->width;
    }
    
    [super drawTextInRect:rect];
}

@end

_CXXCONTROL_IMPL(UIMarqueeLabel);

NNT_END_OBJC
