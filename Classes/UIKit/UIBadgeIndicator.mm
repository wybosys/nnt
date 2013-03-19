
# import "Core.h"
# import "UIBadgeIndicator.h"
# import <QuartzCore/QuartzCore.h>
# import "WCGTextStyle.h"
# import "CoreGraphic+WSI.h"
# import "JuiceCocoa++.hpp"

WSI_BEGIN_OBJC

@implementation UIBadgeIndicator

@synthesize value = _value,
badgeColor = _badgeColor,
badgeOverlayColor = _badgeOverlayColor,
badgeStyle = _badgeStyle,
badgeLineStyle = _badgeLineStyle;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    // set default.
    WCGMutableTextStyle *ts = [WCGMutableTextStyle textStyle];
    ts.color = [WCGColor whiteColor];
    ts.fontType = WCGFontTypeBold;
    self.badgeStyle = ts;
    
    WCGMutableLineStyle* ls = [WCGMutableLineStyle lineStyle];
    ls.lineColor = [WCGColor whiteColor];
    ls.lineWidth = 2;
    self.badgeLineStyle = ls;
    
    self.badgeColor = [UIColor redColor];
    self.badgeOverlayColor = [UIColor colorWithWhite:1.f alpha:.5f];
    self.layer.masksToBounds = NO;
    
    return self;
}

- (void)dealloc {
    safe_release(_value);
    safe_release(_badgeColor);
    safe_release(_badgeOverlayColor);
    safe_release(_badgeStyle);
    safe_release(_badgeLineStyle);
    
    [super dealloc];
}

- (void)updateAppear {
    if (_value == nil ||
        _badgeLineStyle == nil)
        return;
    
    CGSize sz = [_badgeStyle sizeOfString:_value];
    real width = sz.width + _badgeStyle.fontSize;
    real height = sz.height + _badgeStyle.fontSize;
    if (width < height &&
        (int)(height / width) == 1)
        width = height;
        
    sz = CGSizeMake(width, height);
    self.frame = CGRectMakePtSz(self.frame.origin, sz);
    
    // redraw.
    [self setNeedsDisplay];
}

- (void)setBadgeStyle:(WCGMutableTextStyle *)badgeStyle {
    if (_badgeStyle == badgeStyle)
        return;
    
    [NSObject refobjSet:&_badgeStyle ref:badgeStyle];
    
    [self updateAppear];
}

- (void)setValue:(NSString *)value {
    [NSObject refobjCopy:&_value ref:value];
    
    [self updateAppear];
}

- (void)drawRect:(CGRect)rect {
    ::juice::cocoa::Graphics gra = ::juice::cocoa::Graphics::Current(::wsi::cg::Rect(rect).deflate(::wsi::cg::ratio(.1f), .1f, .1f, .1f));
    
    // set edge shadow.
    ::juice::cocoa::Shadow sd;
    sd.set_offset(::wsi::cg::Point(0, -1));
    sd.set_radius(.7f);
    sd.set(gra);
    
    // draw.
    gra.layer().begin();
    
    // background.
    ::juice::cocoa::Bezier bz;
    real radius = ::std::min(gra.bounds().width(), gra.bounds().height()) * .5f;
    bz.set_rounded(gra.bounds(), ::wsi::cg::Size(radius, radius));
    bz.fill(gra, ::juice::cocoa::Brush(::wsi::ui::Color(_badgeColor)));
    bz.stroke(gra, ::juice::cocoa::Pen(::wsi::cg::Color(_badgeLineStyle.lineColor), _badgeLineStyle.lineWidth));
    
    // overlay.
    gra.push_state();
    bz.place(gra);
    gra.clip();
    ::wsi::cg::Rect rcol = gra.bounds().deflate(::wsi::cg::ratio(0), 0, 0, .6f);
    radius = ::std::min(rcol.width(), rcol.height()) * .5f;
    bz.set_rounded(rcol, ::wsi::cg::Size(radius, radius));
    bz.fill(gra, ::juice::cocoa::Brush(::wsi::ui::Color(_badgeOverlayColor)));
    gra.pop_state();
    
    gra.layer().end();
    
    // text.
    ::juice::cocoa::String str(_value);
    str.style.replace(_badgeStyle);
    str.draw(gra, gra.bounds(), false);
}

@end

_CXXCONTROL_IMPL(UIBadgeIndicator);

WSI_END_OBJC
