
# import "Core.h"
# import "CIFilter+NNT.h"
# import <CoreImage/CoreImage.h>
# include "../Core/Layout.h"

NNT_BEGIN_OBJC

@implementation UICFFilterForNSNumber

@synthesize filter, name, slider;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    slider = [[UISliderTitleValue alloc] initWithZero];
    [slider connect:kSignalValueChanged sel:@selector(act_valuechanged) obj:self];
    [self addSubview:slider];
    [slider release];
    
    return self;
}

- (void)dealloc {
    safe_release(filter);
    safe_release(name);
    [super dealloc];
}

- (void)layoutSubviews {
    slider.frame = self.bounds;
}

- (void)act_valuechanged {
    NSNumber* num = [NSNumber numberWithFloat:slider.currentValue];
    [filter setValue:num forKey:name];
}

@end

@implementation UICFFilterForCIVector

@synthesize filter, name, slider_x, slider_y, slider_z, slider_w;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    slider_x = [[UISliderTitleValue alloc] initWithZero];
    [slider_x connect:kSignalValueChanged sel:@selector(act_valuechanged) obj:self];
    [self addSubview:slider_x];
    [slider_x release];
    
    slider_y = [[UISliderTitleValue alloc] initWithZero];
    [slider_y connect:kSignalValueChanged sel:@selector(act_valuechanged) obj:self];
    [self addSubview:slider_y];
    [slider_y release];
    
    slider_z = [[UISliderTitleValue alloc] initWithZero];
    [slider_z connect:kSignalValueChanged sel:@selector(act_valuechanged) obj:self];
    [self addSubview:slider_z];
    [slider_z release];
    
    [slider_w connect:kSignalValueChanged sel:@selector(act_valuechanged) obj:self];
    [self addSubview:slider_w];
    [slider_w release];
    
    return self;
}

- (void)dealloc {
    safe_release(filter);
    safe_release(name);
    [super dealloc];
}

- (void)layoutSubviews {
    ::nnt::CGRectLayoutVBox lyt(self.bounds);
    ::nnt::CGRectLayoutLinear lnr(lyt);
    lnr << (flex)1 << (flex)1 << (flex)1 << (flex)1;
    slider_x.frame = lyt << lnr;
    slider_y.frame = lyt << lnr;
    slider_z.frame = lyt << lnr;
    slider_w.frame = lyt << lnr;
}

- (void)act_valuechanged {
    real x = slider_x.currentValue, y = slider_y.currentValue, z = slider_z.currentValue, w = slider_w.currentValue;
    CIVector* vec = [CIVector vectorWithX:x Y:y Z:z W:w];
    [filter setValue:vec forKey:name];
}

@end

NNT_END_OBJC

NNT_BEGIN_CXX NNT_BEGIN_NS(vision) NNT_BEGIN_NS(ci)

static ::NSString* const _system_categories[] = {
    kCICategoryDistortionEffect,
    kCICategoryGeometryAdjustment,
    kCICategoryCompositeOperation,
    kCICategoryHalftoneEffect,
    kCICategoryColorAdjustment,
    kCICategoryColorEffect,
    kCICategoryTransition,
    kCICategoryTileEffect,
    kCICategoryGenerator,
    
# if defined(__MAC_10_5) | defined(__IPHONE_5_0)
    kCICategoryReduction,
# endif
    
    kCICategoryGradient,
    kCICategoryStylize,
    kCICategorySharpen,
    kCICategoryBlur,
    
    kCICategoryVideo,
    kCICategoryStillImage,
    kCICategoryInterlaced,
    kCICategoryNonSquarePixels,
    kCICategoryHighDynamicRange,
    
    //kCICategoryApplePrivate,
    
    kCICategoryBuiltIn,
    
# if defined(__MAC_10_5) && !defined(NNT_TARGET_IOS)
    kCICategoryFilterGenerator,
# endif
    
    0
};

static const uint _system_categories_count = sizeof(_system_categories) / sizeof(::NSString*) - 1;

ns::Array Filter::SystemFilters()
{
    ns::MutableDictionary dict;
    
    for (uint i = 0; i < _system_categories_count; ++i)
    {
        ::NSArray* res = [CIFilter filterNamesInCategory:_system_categories[i]];
        for (::NSString* each in res)
        {
            dict[each] = [NSNull null];
        }
    }
    
    return dict.allkeys();
}

Filter::Filter()
: _filter(NULL)
{
    
}

Filter::Filter(CIFilter* filter)
{
    _filter = [filter retain];
}

Filter::Filter(ns::String const& name)
{
    _filter = [[CIFilter filterWithName:name] retain];   
}

Filter::~Filter()
{
    safe_release(_filter);
}

ns::Array Filter::attributes() const
{
    ::NSDictionary* attrs = _filter.attributes;
    return [attrs allKeys];
}

id Filter::find(ns::String const& name) const 
{
    return [_filter.attributes objectForKey:name];
}

id Filter::instance_settings(ns::String const& name) const
{
    ::NSDictionary* dict = this->find(name);
    if ([dict isKindOfClass:[::NSDictionary class]] == NO)
        return nil;
    Class cls = NSClassFromString([dict objectForKey:@"CIAttributeClass" null:nil]);
    if (cls == nil)
        return nil;
    id obj = nil;
    if (cls == [::NSNumber class])
    {
        UICFFilterForNSNumber* ret = [[UICFFilterForNSNumber alloc] initWithZero];
        ret.filter = _filter;
        ret.name = name;
        ret.slider.currentValue = [[dict objectForKey:@"CIAttributeDefault" null:nil] floatValue];
        ret.slider.minimumValue = [[dict objectForKey:@"CIAttributeSliderMin" null:nil] floatValue];
        ret.slider.maximumValue = [[dict objectForKey:@"CIAttributeSliderMax" null:nil] floatValue];
        return [ret autorelease];
    }
    else if (cls == [CIVector class])
    {
        UICFFilterForCIVector* ret = [[UICFFilterForCIVector alloc] initWithZero];
        ret.filter = _filter;
        ret.name = name;
        ret.slider_x.currentValue = ret.slider_y.currentValue = ret.slider_z.currentValue = ret.slider_w.currentValue = 0;
        ret.slider_x.minimumValue = ret.slider_y.minimumValue = ret.slider_z.minimumValue = ret.slider_w.minimumValue = -100;
        ret.slider_x.maximumValue = ret.slider_y.maximumValue = ret.slider_z.maximumValue = ret.slider_w.maximumValue = 100;
        return [ret autorelease];
    }
    else
    {
        trace_msg([dict objectForKey:@"CIAttributeClass" null:nil]);
    }
    return obj;
}

NgImage* Filter::process(CGImageRef _img) const
{
    CIImage* img = [[CIImage alloc] initWithCGImage:_img];
    [_filter setValue:img forKey:kCIInputImageKey];
    CIImage* output = _filter.outputImage;    
    CIContext *context = [CIContext contextWithOptions:nil];
    CGImageRef resimg = [context createCGImage:output fromRect:output.extent];
    NgImage* ret = [NgImage imageWithCGImage:resimg];
    CGImageRelease(resimg);
    [img release];
    return ret;
}

NNT_END_NS NNT_END_NS NNT_END_CXX