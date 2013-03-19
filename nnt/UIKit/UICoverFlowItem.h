
# ifndef __WSI_UIKIT_UICOVERFLOWITEM_E48F16058E6F4E60A5B9D4834DA93727_H_INCLUDED
# define __WSI_UIKIT_UICOVERFLOWITEM_E48F16058E6F4E60A5B9D4834DA93727_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(UICoverFlow);
WSIDECL_EXTERN_CLASS(WSIUIImageView);

WSI_EXTERN real kCoverFlowItemFractionReflection;

@protocol UICoverFlowItem <NSObject>

@property (nonatomic, assign) int number;

@end

@interface UICoverFlowItem : WSIUIView <UICoverFlowItem> {
 
    //! image view.
    WSIUIImageView *_imageView;
    
    //! reflection image view.
    WSIUIImageView *_reflectionImageView;
    
    //! number.
	int				_number;
    
    //! fraction reflection
    real _fractionReflection;
    
    //! space for image. default is 0.
    int _spaceImage;

}

@property (nonatomic, assign) real fractionReflection;
@property (nonatomic, readonly) WSIUIImageView *imageView, *reflectionImageView;
@property (nonatomic, assign)   int spaceImage;

//! load url.
- (void)loadURL:(NSURL*)imageURL;

//! set image.
- (void)setImage:(UIImage*)image;

//! scale.
- (void)activeScale;

//! best size.
- (CGSize)calcBestSize;

@end

_CXXVIEW_DECL(UICoverFlowItem);

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

WSI_BEGIN_NS(tpl)

class ICoverFlowItem
: public IView
{
public:
};

template <typename implT,
typename objcT = _CXXVIEW(UICoverFlowItem),
typename objcI = ICoverFlowItem>
class CoverflowItem
: public View<implT, objcT, objcI>
{
public:
    
};

WSI_END_NS

class CoverflowItem
: public tpl::CoverflowItem<CoverflowItem>
{
public:
    
    CoverflowItem()
    {
        PASS;
    }
    
    virtual ~CoverflowItem()
    {
        PASS;
    }
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
