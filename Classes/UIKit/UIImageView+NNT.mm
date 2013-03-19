
# import "Core.h"
# import "UIImageView+NNT.h"
# import "AbstractCache.h"
# import "UIImageDesktop.h"
# import "CoreGraphic+NNT.h"
# import "UIColor+NNT.h"
# import "UIView+NNT.h"
# import "NNTUIObject.h"
# import "Model.h"
# import "UIActivityIndicatorView+NNT.h"
# import "UIKit.res"
# import "NSFileConnection.h"
# include <sys/stat.h>
# import "GifParser.h"

NNT_BEGIN_OBJC

signal_t kSignalImageChanged = @"::nnt::ui::image::changed";
signal_t kSignalImageFetched  = @"::nnt::ui::image::fetched";
signal_t kSignalImageCacheLoaded = @"::nnt::ui::image::cacheloaded";
signal_t kSignalActiveScale = @"::nnt::ui::scale::active";
signal_t kSignalImageFetchedError = @"::nnt::ui::image::fetch::error";

real kUIImageViewActivityDefalteRate = .5f;

@implementation UIImageView (NNT)

@end

@interface NNTUIImageView (hidden)

// get acitvity frame.
- (CGRect)_activityFrame;

// fetch from url.
- (void)_fetchFromURL:(NSURL*)url;

@end

@implementation NNTUIImageView

@synthesize enableWaiting = _enableWaiting, waitingView = _waitingView, waitingStyle = _waitingStyle, failedImg = _failedImg, imageForScale = _imageForScale, urlForScale = _urlForScale;
@synthesize activeBackgroundColor = _activeBackgroundColor;
@synthesize cacheTime = _cacheTime;
@synthesize defaultFailedImage = _defaultFailedImage;
@dynamic image;
@synthesize autoResizeImage = _autoResizeImage;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    self.activeBackgroundColor = [UIColor colorWithRGBA:0x00000099];
    _waitingStyle = UIActivityIndicatorViewStyleGray;
    _autoResizeImage = NO;
    
# ifdef NNT_DEBUG
    self.cacheTime = DT_15MIN;
# else
    self.cacheTime = DT_1HOUR;
# endif
    
    _imageView = [[UIImageView alloc] initWithZero];
    _imageView.layer.masksToBounds = YES;
    [self addSubview:_imageView];
    safe_release(_imageView);

    return self;
}

- (id)initWithURL:(NSURL *)url cache:(BOOL)iscache {
    self = [self initWithURL:url cache:iscache failedImg:nil];
    return self;
}

- (id)initWithURL:(NSURL *)url cache:(BOOL)iscache failedImg:(UIImage *)__failedImg {
    self = [super init];
    
    [self loadURL:url cache:iscache failedImg:__failedImg];
            
    return self;
}

- (id)initWithData:(NSData *)data {
    self = [super init];
    
    [self loadData:data];    
    
    return self;
}

- (id)initWithImage:(UIImage *)img {
    self = [super init];
    
    _imageView.image = img;
    
    return self;
}

- (void)dealloc {
    [self cnt_clear];
        
    zero_release(_waitingView);
    zero_release(_failedImg);
    zero_release(_imageForScale);
    zero_release(_urlForScale);
    zero_release(_activeBackgroundColor);
    zero_release(_defaultFailedImage);
    
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

- (void)setContentMode:(UIViewContentMode)mode {
    _imageView.contentMode = mode;
}

- (UIViewContentMode)contentMode {
    return _imageView.contentMode;
}

- (void)_fetchFromURL:(NSURL *)url {
    if (url == NULL) {
        // set failed image.
        if (self.failedImg == nil)
            self.failedImg = self.defaultFailedImage;
        [self setImage:self.failedImg];
        
        // signal.
        [self emit:kSignalImageFetchedError];
        
        return;
    }        
    
    // load from url.
    [self performSelectorInBackground:@selector(thd_fetch_image:) withObject:url]; 
}

- (BOOL)loadData:(NSData *)data {    
    // stop gif animating.
    if ([_imageView isAnimating])
        [_imageView stopAnimating];
    
    // ret.
    BOOL suc = YES;
    
    // if is gif.
    if ([GifParser isGifData:data]) {
        // clear.
        _imageView.image = nil;
        
        // parser gif data.
        GifParser* parser = [[GifParser alloc] initWithData:data];
        
        // make anims.
        NSMutableArray* arr = [[NSMutableArray alloc] init];
        uint ava_delay = 0;
        for (GifImage* each in parser.images) {
            ava_delay += each.delay;
            UIImage* img = [UIImage imageWithCGImage:each.image];
            [arr addObject:img];
        }
        
        // set default image.
        self.image = [arr objectAtIndex:0 null:nil];
        
        [_imageView setAnimationImages:arr];
        _imageView.animationDuration = ava_delay * 0.001f;
        [_imageView startAnimating];
        
        suc = [arr count] != 0;
        
        safe_release(arr);
        safe_release(parser);
        
    } else {
        
        // load other format image.
        self.image = [UIImage imageWithData:data];
        
        suc = self.image != nil;
    }
    
    return suc;
}

- (void)loadURL:(NSURL *)url {
    [self loadURL:url cache:YES];
}

- (void)loadURL:(NSURL *)url cache:(BOOL)cache {
    [self loadURL:url cache:cache failedImg:nil];
}

- (void)loadURL:(NSURL *)url cache:(BOOL)iscache failedImg:(id)__failedImg {
    if (url == nil) {
        [self emit:kSignalImageFetchedError];
        return;
    }
    
    NSMutableArray* arr = [[NSMutableArray alloc] init];
    [arr addObject:url];
    [arr addObject:TRIEXP(iscache, NSNumberYes, NSNumberNo)];
    [arr addObject:TRIEXP(__failedImg, __failedImg, [NSNull null])];
    [self performSelectorInBackground:@selector(doLoadCacheURL:) withObject:arr];
    [arr release];
}

- (void)doLoadCacheURL:(NSArray*)params {
    NSURL* url = [params objectAtIndex:0];
    BOOL iscache = [params objectAtIndex:1] == NSNumberYes;
    id __failedImg = [params objectAtIndex:2];
    if ([__failedImg isKindOfClass:[NSNull class]])
        __failedImg = nil;
    
    BOOL image_loaded = NO;
    UIImage *tgtimage = nil;
    
    // load from cache.
    AbstractCache *cache = [AbstractCache defaultCache];
    if (iscache && cache && url) {
        NSData *data = [cache objectForKey:[url absoluteString]];
        if ([data isKindOfClass:[NSData class]]) {
            image_loaded = YES;
            
            // load image.
            [self loadData:data];
            
            // emit fetched.
            [self emit:kSignalImageFetched result:tgtimage];
        }
    }
    
    if (image_loaded == NO) {
        // failed get image.
        if (self.failedImg == nil)
            self.failedImg = __failedImg;
        
        // fetch data.
        [self _fetchFromURL:url];
    }
}

- (void)setEnableWaiting:(BOOL)enableWaiting {
    _enableWaiting = enableWaiting;
    
    if (_enableWaiting) {
        [self performSelectorOnMainThread:@selector(show_waiting) withObject:nil waitUntilDone:YES];
    } else {
        [self performSelectorOnMainThread:@selector(hide_waiting) withObject:nil waitUntilDone:YES];
    }
}

NNTEVENT_BEGIN
NNTEVENT_SIGNAL(kSignalViewClicked)
NNTEVENT_SIGNAL(kSignalImageChanged)
NNTEVENT_SIGNAL(kSignalImageFetched)
NNTEVENT_SIGNAL(kSignalActiveScale)
NNTEVENT_SIGNAL(kSignalImageFetchedError)
NNTEVENT_END

- (void)drawRect:(CGRect)rect {
    [super drawRect:rect];
}
 
- (void)show_waiting {
    if (!self.waitingView) {        
        _waitingView = [[NNTUIActivityIndicatorView alloc] initWithActivityIndicatorStyle:_waitingStyle];
        _waitingView.frame = [self _activityFrame];
        [self addSubview:_waitingView];
        [_waitingView startAnimating];
    }
}

- (void)hide_waiting {
    if (self.waitingView) {
        [self.waitingView stopAnimating];
        [self.waitingView removeFromSuperview];
        self.waitingView = nil;
    }
}

- (CGRect)_activityFrame {
    CGRect rc_client = self.bounds;
    CGRect rc_act = CGRectDeflateCenterR(rc_client, kUIImageViewActivityDefalteRate, kUIImageViewActivityDefalteRate);
    rc_act = CGRectToSquare2(rc_act);
    if (rc_act.size.width < 36) {
        CGPoint pt = CGRectCenterPoint(&rc_act);
        rc_act.size.width = rc_act.size.height = 36;
        rc_act = CGRectMoveCenter(rc_act, pt);
    }
    return rc_act;
}

- (void)setFrame:(CGRect)frame {    
    [super setFrame:frame];
    
    if ((self.autoResizeImage == YES) && _imageView.image) {
        if (NO == CGSizeEqualToSize(CGSizeZero, frame.size)) {
            UIImage* nimg = [_imageView.image resizedImage:frame.size interpolationQuality:kCGInterpolationDefault];
            _imageView.image = nimg;            
        }
    }
}

- (void)layoutSubviews {
    CGRect rc_client = self.bounds;    
    CGPoint pt_center = CGRectCenterPoint2(rc_client);
    
    _imageView.frame = rc_client;
    
    if (_waitingView) {
        _waitingView.frame = [self _activityFrame];
    }
    
    if (_failed) {
        [_failed moveToCenter:pt_center];
    }
}

- (UIImage*)image {
    return _imageView.image;
}

- (void)setImage:(UIImage *)__image {    
    if (_imageView.image == __image) {
        self.enableWaiting = NO;
        return;
    }
    
    if (__image && (__image == _defaultFailedImage)) {
        _oldmode = (uint)_imageView.contentMode;
        _oldmode += 1;
        
        _imageView.contentMode = UIViewContentModeCenter;
    } else {
        if (_oldmode) {
            _imageView.contentMode = (UIViewContentMode)(_oldmode - 1);
            _oldmode = 0;
        }
    }
    
    if ((self.autoResizeImage == YES) && __image) {
        CGRect rc_client = self.bounds;
        if (NO == CGSizeEqualToSize(CGSizeZero, rc_client.size)) {
            __image = [__image resizedImage:rc_client.size interpolationQuality:kCGInterpolationDefault];
        }
    }
    
    _imageView.image = __image;
    
    [self performSelectorOnMainThread:@selector(act_image_changed) withObject:nil waitUntilDone:NO];
}

- (UIImage*)defaultFailedImage {
    NNT_SYNCHRONIZED(self)
    
    if (_defaultFailedImage == nil) {
        NgImage* img_failed = NgImageLoadPngData(png_failed_image, sizeof(png_failed_image));
        _defaultFailedImage = [[UIImage imageWithCGImage:img_failed.image] retain];
    }
    
    NNT_SYNCHRONIZED_END
    return _defaultFailedImage;
}

- (void)act_image_changed {
    // end wait.
    self.enableWaiting = NO;
    
    // send signal.
    [self emit:kSignalImageChanged result:_imageView.image];
    
    // redraw.
    [self setNeedsDisplay];
    
    // animated.
    ::nnt::qz::Transition tran;
    tran.set_type(kCATransitionFade);
    tran.play(self);
}

# pragma mark act

- (void)cnt_respond:(NNTEventObj*)evt {
    if ([(id)evt.sender isKindOfClass:[NNTNSURLConnection class]]) {
        NSURLResponse* respone = (NSURLResponse*)evt.result;
        _waitingView.progressMax = respone.expectedContentLength;
    } else if ([(id)evt.sender isKindOfClass:[NSFileConnection class]]) {
        struct stat* _sta = (struct stat*)evt.data;
        _waitingView.progressMax = _sta->st_size;
    }
    
    _waitingView.progressValue = 0;
}

- (void)cnt_receive:(NNTEventObj*)evt {
    NSData* data = (NSData*)evt.result;
    _waitingView.progressValue = [data length];
}

- (void)cnt_finish:(NNTEventObj*)evt {    
    NSData* data = (NSData*)evt.result;
    NSURL* url = nil;
    
    if ([(id)evt.sender isKindOfClass:[NNTNSURLConnection class]]) {
        url = ((NNTNSURLConnection*)evt.sender).urlRequest.URL;
    } else if ([(id)evt.sender isKindOfClass:[NSFileConnection class]]) {
        url = ((NSFileConnection*)evt.sender).url;
    }
    
    BOOL fetch_success = NO;
    
    if (data) {
        // load image.
        if ([self loadData:data]) {
            AbstractCache *cache = [AbstractCache defaultCache];
            if (cache) {
                CacheItem* item = [cache setObject:data
                                               key:[url absoluteString]];
                if (_cacheTime == -1) {
                    [item infinate];
                } else {
                    item.overdate = item.timestamp + self.cacheTime;
                }
            }
            
            fetch_success = YES;            
        }
    }
    
    if (fetch_success == NO) {
        UIImage* obj_image = nil;
        
        if (self.failedImg) {
            obj_image = [self.failedImg retain];
        } else {
            obj_image = [self.defaultFailedImage retain];                
        }            
     
        // set image
        self.image = obj_image;
        
        // release
        safe_release(obj_image);
    }       
    
    // hide progress.
    _waitingView.showProgressRing = NO;
    
    // emit event.
    if (fetch_success) {
        [self emit:kSignalImageFetched result:self.image];
    } else {
        [self emit:kSignalImageFetchedError];
    }       
    
    [self cnt_clear];
}

- (void)cnt_failed {
    // stop waiting indicator.
    self.enableWaiting = NO;
    
    // clear connect.
    [self cnt_clear];
}

- (void)cnt_clear {
    if (_connection == nil)
        return;
    
    [_connection disconnect:self];
    [_connection cancel];
    zero_release(_connection);
}

- (void)thd_fetch_image:(NSURL*)url {
    // start progress indicator.
    self.enableWaiting = YES;
    _waitingView.showProgressRing = YES;
    
    // begin.
    trace_fmt(@"fetching image from %@", url.absoluteString);
    
    // clean old connection.
    [self cnt_clear];
    
    // perform a new connection.
    if (url.isFileURL) {
        
        _connection = [[NSFileConnection alloc] initWithURL:url];
        
        NSFileConnection* cnt = (NSFileConnection*)_connection;
        cnt.inThread = YES;
        
        // connect signal.
        [cnt connect:kSignalFileConnectionOpened sel:@selector(cnt_respond:) obj:self];
        [cnt connect:kSignalFileConnectionDataChanged sel:@selector(cnt_receive:) obj:self];
        [cnt connect:kSignalFileConnectionFinish sel:@selector(cnt_finish:) obj:self];
        [cnt connect:kSignalFileConnectionError sel:@selector(cnt_failed) obj:self];
        
        // start read.
        [cnt start];
        
    } else {
        
        _connection = [[NNTNSURLConnection alloc] initWithURLRequest:[NSURLRequest requestWithURL:url] start:NO];
        
        NNTNSURLConnection* cnt = (NNTNSURLConnection*)_connection;
        cnt.inThread = YES;
        
        // connect signal.
        [cnt connect:kSignalURLConnectionReceiveResponse sel:@selector(cnt_respond:) obj:self];
        [cnt connect:kSignalURLConnectionDataChanged sel:@selector(cnt_receive:) obj:self];
        [[cnt connect:kSignalURLConnectionFinish sel:@selector(cnt_finish:) obj:self] sameThread];
        [cnt connect:kSignalURLConnectionError sel:@selector(cnt_failed) obj:self];

        // start read.
        [cnt startAsync];

    }
}

- (UIImageDesktop*)activeScale {
    [self emit:kSignalActiveScale];
    
    UIImageDesktop *desk = nil;
    
    if (_urlForScale) {
        desk = [[UIImageDesktop alloc] initWithURL:_urlForScale cache:YES];
        desk.imageView.frame = CGRectMakeSz(CGSizeMake(100, 100));
    } else if (self.imageForScale) {
        desk = [[UIImageDesktop alloc] initWithImage:self.imageForScale];    
        desk.imageView.frame = CGRectMakeSz(self.imageForScale.size);
    } else if (self.image) {
        desk = [[UIImageDesktop alloc] initWithImage:self.image];
        desk.imageView.frame = CGRectMakeSz(self.image.size);
    }
    
    if (desk) {
        [desk centerImage];
        desk.backgroundColor = _activeBackgroundColor;
        desk.enableAutoClose = YES;
        
        [desk show];
        [desk release];
    }
    
    return desk;
}

- (BOOL)containLayer:(CALayer*)layer {
    if ([self.layer isEqual:layer])
        return YES;
    if ([_imageView.layer isEqual:layer])
        return YES;
    if ([_waitingView.layer isEqual:layer])
        return YES;
    return NO;
}

@end

@implementation NNTUIImageViewActiveScale

- (id)init {
    self = [super init];
    self.userInteractionEnabled = YES;
    return self;
}

@end

NNTIMPL_CATEGORY(UIImageView, NNT);

@interface UISightImageView ()

@property (nonatomic, retain) NSURL* imageURL;

@end

@implementation UISightImageView

@synthesize imageURL;

- (void)dealloc {
    zero_release(imageURL);
    [super dealloc];
}

- (void)viewInSight {
    if (imageURL == nil)
        return;
    
    if (self.image)
        return;
    [super loadURL:imageURL cache:_cache failedImg:_failedimg];
}

- (void)viewOutSight {
    if (imageURL == nil)
        return;
    self.image = nil;
}

- (void)loadURL:(NSURL *)url cache:(BOOL)iscache failedImg:(id)__failedImg {
    safe_release(_failedimg);
    _cache = iscache;
    _failedimg = [__failedImg retain];
    self.imageURL = url;
}

@end

_CXXVIEW_IMPL(NNTUIImageView);

NNT_END_OBJC