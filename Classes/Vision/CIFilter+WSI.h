
# ifndef __NNT_VISION_CIFILTER_7C9861510B7A4C428404267D62B57E26_H_INCLUDED
# define __NNT_VISION_CIFILTER_7C9861510B7A4C428404267D62B57E26_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

@interface UICFFilterForNSNumber : NNTUIView {    
    CIFilter* filter;
    NSString* name;    
    UISliderTitleValue* slider;
}

@property (nonatomic, retain) CIFilter* filter;
@property (nonatomic, copy) NSString* name;
@property (nonatomic, readonly) UISliderTitleValue* slider;

@end

@interface UICFFilterForCIVector : NNTUIView {    
    CIFilter* filter;
    NSString* name;    
    UISliderTitleValue *slider_x, *slider_y, *slider_z, *slider_w;
}

@property (nonatomic, retain) CIFilter* filter;
@property (nonatomic, copy) NSString* name;
@property (nonatomic, readonly) UISliderTitleValue *slider_x, *slider_y, *slider_z, *slider_w;

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX NNT_BEGIN_NS(vision) NNT_BEGIN_NS(ci)

class Filter
{
public:
    
    Filter();
    Filter(CIFilter*);
    Filter(ns::String const& name);
    ~Filter();
    
    //! get all filters in system.
    static ns::Array SystemFilters();
    
    //! get attributes.
    ns::Array attributes() const;
    
    //! find attribute.
    id find(ns::String const& name) const;
    
    //! ui for setting.
    id instance_settings(ns::String const& name) const;
    
    //! image.
    WCGImage* process(CGImageRef) const;
    
    //! retype.
    operator CIFilter* () const
    {
        return (CIFilter*)_filter;
    }
    
protected:
    
    CIFilter* _filter;
    
};

NNT_END_NS NNT_END_NS NNT_END_HEADER_CXX

# endif

# endif