
# ifndef __NNT_UIKIT_UICOVERFLOWITEM_E48F16058E6F4E60A5B9D4834DA93727_H_INCLUDED
# define __NNT_UIKIT_UICOVERFLOWITEM_E48F16058E6F4E60A5B9D4834DA93727_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(UICoverFlow);
NNTDECL_EXTERN_CLASS(NNTUIImageView);

NNT_EXTERN real kCoverFlowItemFractionReflection;

@protocol UICoverFlowItem <NSObject>

@property (nonatomic, assign) int number;

@end

@interface UICoverFlowItem : NNTUIView <UICoverFlowItem> {
 
    //! image view.
    NNTUIImageView *_imageView;
    
    //! reflection image view.
    NNTUIImageView *_reflectionImageView;
    
    //! number.
	int				_number;
    
    //! fraction reflection
    real _fractionReflection;
    
    //! space for image. default is 0.
    int _spaceImage;

}

@property (nonatomic, assign) real fractionReflection;
@property (nonatomic, readonly) NNTUIImageView *imageView, *reflectionImageView;
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

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

NNT_BEGIN_NS(tpl)

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

NNT_END_NS

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

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
