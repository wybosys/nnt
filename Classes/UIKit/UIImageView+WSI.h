
# ifndef __NNT_UIKIT_UIIMAGEVIEW_93B7862E02B74F9AA825582AC10AF5CA_H_INCLUDED
# define __NNT_UIKIT_UIIMAGEVIEW_93B7862E02B74F9AA825582AC10AF5CA_H_INCLUDED

# import "UIView+NNT.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(NNTUIActivityIndicatorView);
NNTDECL_EXTERN_CLASS(UIImageDesktop);

@interface UIImageView (NNT)

@end

@interface NNTUIImageView : NNTUIView {    
    //! enable waiting show.
    BOOL _enableWaiting;
    
    //! waiting view.
    NNTUIActivityIndicatorView *_waitingView;
    
    //! waiting style.
    UIActivityIndicatorViewStyle _waitingStyle;
    
    //! image while failed.
    UIImage *_failedImg;
    
    //! image for scale.
    UIImage *_imageForScale;
    NSURL *_urlForScale;
            
    //! active background color.
    UIColor *_activeBackgroundColor;

    //! cache time. -1 is infinate. default use system.
    uint _cacheTime;
    
    //! autoresize image. default is NO.
    BOOL _autoResizeImage;
    
    @protected
    UIImageView* _imageView;
    
    @private
    UIView* _failed;
    uint _oldmode;
    id _connection;
}

@property (nonatomic) BOOL enableWaiting;
@property (nonatomic, retain) NNTUIActivityIndicatorView *waitingView;
@property (nonatomic) UIActivityIndicatorViewStyle waitingStyle;
@property (nonatomic, retain) UIImage *failedImg;
@property (nonatomic, retain) UIImage *imageForScale;
@property (nonatomic, retain) NSURL *urlForScale;
@property (nonatomic, retain) UIColor *activeBackgroundColor;
@property (nonatomic, assign) uint cacheTime;
@property (nonatomic, retain) UIImage *defaultFailedImage;
@property (nonatomic, retain) UIImage *image;
@property (nonatomic, assign) BOOL autoResizeImage;

//! init with url.
- (id)initWithURL:(NSURL*)url cache:(BOOL)cache;
- (id)initWithURL:(NSURL*)url cache:(BOOL)cache failedImg:(UIImage*)failedImg;
- (id)initWithFrame:(CGRect)frame;
- (id)initWithData:(NSData*)data;
- (id)initWithImage:(UIImage*)img;

//! load from url.
- (void)loadURL:(NSURL*)url;
- (void)loadURL:(NSURL*)url cache:(BOOL)cache;
- (void)loadURL:(NSURL*)url cache:(BOOL)cache failedImg:(UIImage*)failedImg;

//! load from data.
- (BOOL)loadData:(NSData*)data;

//! active scale view.
- (UIImageDesktop*)activeScale;

//! contain layer.
- (BOOL)containLayer:(CALayer*)layer;

@end

@interface NNTUIImageViewActiveScale : NNTUIImageView
@end

@interface UISightImageView : NNTUIImageView <NNTUIViewInSight> {
    NSURL* imageURL;
    
    @private
    BOOL _cache;
    id _failedimg;
}

@property (nonatomic, readonly, retain) NSURL* imageURL;

@end

//! clicked.
NNT_EXTERN signal_t kSignalViewClicked;

//! image changed.
NNT_EXTERN signal_t kSignalImageChanged;

//! active scale.
NNT_EXTERN signal_t kSignalActiveScale;

//! image fetched.
NNT_EXTERN signal_t kSignalImageFetched;

//! failed to fetch image.
NNT_EXTERN signal_t kSignalImageFetchedError;

//! image cache loaded.
NNT_EXTERN signal_t kSignalImageCahceLoaded;

NNTDECL_CATEGORY(UIImageView, NNT);

# ifdef NNT_CXX

# include "UIView+NNT.h"

NNT_BEGIN_HEADER_OBJC

_CXXVIEW_DECL(NNTUIImageView);

NNT_END_HEADER_OBJC

NNT_BEGIN_HEADER_CXX 
NNT_BEGIN_NS(ui)

class ImageView
: public View<ImageView, 
_CXXVIEW(NNTUIImageView)
>
{        
    
    typedef View<ImageView, 
    _CXXVIEW(NNTUIImageView)
    > super;
    
public:
    
    ImageView()
    {
        PASS;
    }
    
    ImageView(NSURL* url, bool cache = true, UIImage* failedimg = NULL)
    : super(nil, true)
    {
        this->_self = [[objc_type alloc] initWithURL:url cache:cache failedImg:failedimg];
        this->_updateself();
    }
    
    ImageView(NSData* data)
    : super(nil, true)
    {
        this->_self = [[objc_type alloc] initWithData:data];
        this->_updateself();
    }
    
    ImageView(UIImage* image)
    : super(nil, true)
    {
        this->_self = [[objc_type alloc] initWithImage:image];
        this->_updateself();
    }
    
    ImageView(NNTUIImageView* r)
    : super((objc_type*)r)
    {
        PASS;
    }
    
    ImageView(Image const& image)
    : super(nil, true)
    {
        this->_self = [[objc_type alloc] initWithImage:image];
        this->_updateself();
    }
    
    ~ImageView()
    {
        PASS;
    }
    
    void load(NSURL* url, bool cache = true, UIImage* failedimg = NULL)
    {
        [this->_self loadURL:url cache:cache failedImg:failedimg];
    }
    
    void load(NSData* data)
    {
        [this->_self loadData:data];
    }
    
    void set_image(Image const& img)
    {
        this->_self.image = img;
    }
    
    UIImage* image() const
    {
        return this->_self.image;
    }
    
    virtual void layout_subviews()
    {
        PASS;
    }
    
    UIImageDesktop* active_scale()
    {
        return [this->_self activeScale];
    }
    
    void set_image_autoresize(bool v)
    {
        this->_self.autoResizeImage = v;
    }
    
    bool image_autoresize() const
    {
        return this->_self.autoResizeImage;
    }
    
};

NNT_END_NS 
NNT_END_HEADER_CXX

# endif

NNT_END_HEADER_OBJC

# endif