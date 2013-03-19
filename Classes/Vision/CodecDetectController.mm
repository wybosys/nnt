
# import "Core.h"
# import "CodecDetectController.h"
# import "ImageCodecReader.h"
# import "JuiceCocoa++.hpp"

WSI_BEGIN_OBJC

signal_t kSignalTry = @"::wsi::try";
signal_t kSignalSuccess = @"::wsi::success";

@implementation CodecDetectMaskView

- (void)drawRect:(CGRect)rect {
    [super drawRect:rect];
    
    ::wsi::cg::Rect rc(rect);
    ::wsi::cg::Rect irc = rc.deflate(::wsi::cg::ratio(0.27f), 0.27f, 0.21f);
    irc.set_height(irc.width());
    
    ::juice::cocoa::Graphics gra = ::juice::cocoa::Graphics::Current();
    
    // draw bk.
    {
        ::juice::cocoa::Path ph;
        ph.add_rect(rc, ::juice::cocoa::cw);
        ph.add_rect(irc, ::juice::cocoa::ccw);
        
        // fill solid.
        {
            ::juice::cocoa::Brush br(::juice::cocoa::Color::RGBA(0x353535F2));
            ph.fill(gra, br);
        }
        
        // fill grid.
        {
            ::juice::cocoa::GridPointBrush br(::juice::cocoa::Color::RGBA(0x46464672), ::wsi::cg::Size(10, 10), 2);
            ph.fill(gra, br);
        }
        
        // draw cross.
        {
            ::juice::cocoa::Pen pen(::juice::cocoa::Color::RGBA(0xA8AAB072));
            uint count = rand01() * 10 + 5;
            for (uint i = 0; i < count; ++i)
            {
                ::wsi::cg::Rect wrc;
                wrc.set_x(rand01() * rc.width() + rc.x());
                wrc.set_y(rand01() * rc.height() + rc.y());
                wrc.set_width(rand01() * rc.width() * 0.1f);
                wrc.set_height(wrc.width());
                if (irc.is_intersect(wrc))
                    continue;
                
                ::juice::cocoa::Path ph;
                ph.move_to(::wsi::cg::Line(wrc.lt(), wrc.rt()).center());
                ph.line_to(::wsi::cg::Line(wrc.lb(), wrc.rb()).center());
                ph.move_to(::wsi::cg::Line(wrc.lt(), wrc.lb()).center());
                ph.line_to(::wsi::cg::Line(wrc.rt(), wrc.rb()).center());
                pen.set_width(rand01() * wrc.width() * .5f);
                ph.stroke(gra, pen);
            }
        }
        
        // draw box.
        {
            ::juice::cocoa::Brush br(::juice::cocoa::Color::RGBA(0xA8AAB072));
            uint count = rand01() * 20 + 10;
            for (uint i = 0; i < count; ++i)
            {
                ::wsi::cg::Rect wrc;
                wrc.set_x(rand01() * rc.width() + rc.x());
                wrc.set_y(rand01() * rc.height() + rc.y());
                wrc.set_width(rand01() * rc.width() * 0.1f);
                wrc.set_height(wrc.width());
                if (irc.is_intersect(wrc))
                    continue;
                br.fill(gra, wrc);
            }
        }
    }
    
    // draw edge.
    {
        ::juice::cocoa::Pen pn(::juice::cocoa::Color::Red(), 3);
        pn.stroke(gra, irc);
    }
}

@end

@implementation CodecDetectView

@synthesize icrcamera = _icrcamera;
@synthesize maskView = _maskView;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    _icrcamera = [[ICRCameraController alloc] init];
    [self addSubController:_icrcamera];
    [_icrcamera release];
    
    _maskView = [[CodecDetectMaskView alloc] initWithZero];
    [self addSubview:_maskView];
    
    return self;
}

- (void)dealloc {
    safe_release(_maskView);
    [super dealloc];
}

- (void)layoutSubviews {
    _icrcamera.view.frame = self.bounds;
    _maskView.frame = self.bounds;
}

- (void)setMaskView:(WSIUIView *)view {
    if (view == _maskView)
        return;
    
    // old.
    [_maskView removeFromSuperview];
    
    // set.
    _maskView = view;
    [self addSubview:_maskView];
    
    // relayout.
    [self setNeedsLayout];
}

@end

@implementation CodecDetectController

@synthesize continuable = _continuable;

- (id)init {
    self = [super init];
    
    _continuable = YES;
    _processing = NO;
    
    return self;
}

- (void)dealloc {
    [super dealloc];
}

WSIEVENT_BEGIN
WSIEVENT_SIGNAL(kSignalTry)
WSIEVENT_SIGNAL(kSignalSuccess)
WSIEVENT_END

- (void)loadView {
    CodecDetectView* view = [[CodecDetectView alloc] initWithZero];
    self.view = view;
    [view release];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    CodecDetectView* view = (CodecDetectView*)self.view;
    
    // get image.
    [view.icrcamera connect:kSignalSnapshot sel:@selector(_act_snapshot:) obj:self];
}

- (void)_act_snapshot:(WSIEventObj*)evt {
    //trace_msg(@"snap a shot.");
    
    if (_processing == YES)
        return;
    
    UIImage* image = (UIImage*)evt.result;
    [self performSelectorInBackground:@selector(_thd_processimage:) withObject:image];
}

- (void)_thd_processimage:(UIImage*)image {
    autocollect;
    
    _processing = YES;
    //trace_msg(@"read code from image.");
    
    UIImage* gray = image.grayImage;
    
    if (gray == nil) {
        _processing = NO;
        trace_msg(@"failed to grayscale.");
        return;
    }
    
    // send try signal.
    [self emit:kSignalTry result:image data:gray];
    
    // gray image data.
    NSData* data = [gray rawData];
    
    // read code from image.
    ImageCodecReader* reader = [[ImageCodecReader alloc] init];
    NSData* result = [reader readRaw:(byte*)data.bytes
                                dlen:data.length
                               width:gray.size.width
                              height:gray.size.height];
    safe_release(reader);
    
    // next process.
    if (result != nil) {
        if (self.continuable == NO)
            [self suspend];
        
        // got result from code.
        [self emit:kSignalSuccess result:result];
    }
    
    _processing = NO;
}

- (void)suspend {
    CodecDetectView* view = (CodecDetectView*)self.view;
    [view.icrcamera suspend];
}

- (void)resume {
    CodecDetectView* view = (CodecDetectView*)self.view;
    [view.icrcamera resume];
}

@end

_CXXCONTROLLER_IMPL(CodecDetectController);

WSI_END_OBJC
