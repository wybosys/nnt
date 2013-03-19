
# ifndef __WSI_IOS_PRINTER_FA3F015118EE4DB29304135F4AD9E850_H_INCLUDED
# define __WSI_IOS_PRINTER_FA3F015118EE4DB29304135F4AD9E850_H_INCLUDED

# import <UIKit/UIPrintError.h>
# import <UIKit/UIPrintFormatter.h>
# import <UIKit/UIPrintInfo.h>
# import <UIKit/UIPrintInteractionController.h>
# import <UIKit/UIPrintPageRenderer.h>
# import <UIKit/UIPrintPaper.h>

WSI_BEGIN_HEADER_OBJC

WSIDECL_PRIVATE_HEAD(InteractionPrinter);

@interface InteractionPrinter : WSIObject {
    WSIDECL_PRIVATE(InteractionPrinter);
}

@property (nonatomic,retain) UIPrintPageRenderer *printPageRenderer;
@property (nonatomic,retain) UIPrintFormatter    *printFormatter;
@property (nonatomic,copy)   id                   printItem;
@property (nonatomic,copy)   NSArray             *printItems;

//! is support print.
+ (BOOL)IsSupported;

//! execute interaction print job.
//! while for iphone, can pass nil.
- (void)execute:(CGRect)rect inView:(UIView*)view animated:(BOOL)animated;

@end

@interface UIPrintFormatter (WSI)

- (NSInteger)defaultPageCount;

@end

WSIDECL_OBJCXX_WRAPPER(UIPrintPageRenderer);
WSIDECL_OBJCXX_WRAPPER(UISimpleTextPrintFormatter);

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(driver)
WSI_BEGIN_NS(print)
WSI_BEGIN_NS(ns)

WSI_BEGIN_NS(formatter)

class IFormatter
: public ::wsi::ns::cxx::IObject
{
public:
    
    virtual uint page_count() const = 0;
    
};

WSI_BEGIN_NS(tpl)

template <typename fmtT,
typename fmtI = IFormatter
>
class Formatter
: public ::wsi::ns::cxx::Object<fmtT, fmtI>
{
    
    typedef ::wsi::ns::cxx::Object<fmtT, fmtI> super;
    
protected:
    
    Formatter(id obj)
    : super(obj)
    {
        PASS;
    }
 
public:
    
    Formatter()
    {
        PASS;
    }
    
    ~Formatter()
    {
        PASS;
    }
    
    typedef struct {} formatter_type;
    
    void set_startpage(uint idx)
    {
        this->_self.startPage = idx;
    }
    
    uint startpage() const
    {
        return this->_self.startPage;
    }
    
    void set_contentedge(cg::Insets const& val)
    {
        this->_self.contentInsets = val;
    }
    
    void set_maximum_content_height(real val)
    {
        this->_self.maximumContentHeight = val;
    }
    
    void set_maximum_content_width(real val)
    {
        this->_self.maximumContentWidth = val;
    }
    
    virtual uint page_count() const
    {
        return [this->_self defaultPageCount];
    }
    
};

WSI_END_NS

class SimpleText
: public tpl::Formatter< WSI_OBJCXX_WRAPPER(UISimpleTextPrintFormatter) >
{
    typedef tpl::Formatter< WSI_OBJCXX_WRAPPER(UISimpleTextPrintFormatter) > super;
    
public:
    
    SimpleText()
    : super(nil)
    {
        this->_set([[objc_type alloc] initWithText:@""]);
    }
    
    void set_text(::wsi::ns::String const& str)
    {
        this->_self.text = str;
    }
    
    ::wsi::ns::String text() const
    {
        return this->_self.text;
    }
    
    void set_color(ui::Color const& cor)
    {
        this->_self.color = cor;
    }
    
    void set_font(ui::Font const& ft)
    {
        this->_self.font = ft;
    }
    
    void set_alignment(UITextAlignment align)
    {
        this->_self.textAlignment = align;
    }
    
};

WSI_END_NS

class PageRender
: public ::wsi::ns::cxx::Object< WSI_OBJCXX_WRAPPER(UIPrintPageRenderer) >
{
public:
    
    template <typename fmtT>
    void add(fmtT const& fmt, uint atidx = 0)
    {
        wtl::const_pointer<fmtT> ptr(fmt);
        [this->_self addPrintFormatter:*ptr startingAtPageAtIndex:atidx];
    }
    
};

class Printer
: public ::wsi::ns::Object<InteractionPrinter>
{
public:
    
    Printer()
    {
        PASS;
    }
    
    ~Printer()
    {
        PASS;
    }
    
    static bool IsSupported()
    {
        return [objc_type IsSupported];
    }
    
    void execute(cg::Rect const& rc, UIView* view, bool animated = true)
    {
        [this->_self execute:rc inView:view animated:animated];
    }
    
    void set_render(PageRender* render)
    {
        this->_self.printPageRenderer = *render;
    }
    
};

WSI_END_NS
WSI_END_NS
WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
