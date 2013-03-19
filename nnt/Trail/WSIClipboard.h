
# ifndef __WSI_TRAIL_CLIPBOARD_79B495BE60EF46B2805AAEF1D2ABEBB9_H_INCLUDED
# define __WSI_TRAIL_CLIPBOARD_79B495BE60EF46B2805AAEF1D2ABEBB9_H_INCLUDED

# ifdef WSI_OBJC

WSI_BEGIN_HEADER_OBJC

WSIDECL_EXTERN_CLASS(UIPasteboard);

WSIDECL_PRIVATE_HEAD(Clipboard);

@interface Clipboard : WSIObject {
    WSIDECL_PRIVATE(Clipboard);
}

- (id)init;
- (id)initWithUnique;
- (id)initWithName:(NSString*)name;

- (UIPasteboard*)pasteboard;

@end

WSI_EXTERN signal_t kSignalContentChanged;

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(sys)

class Clipboard
: public ns::Object< ::Clipboard >
{
    typedef ns::Object< ::Clipboard > super;
    
public:
    
    Clipboard();
    Clipboard(ns::String const&);
    
    bool is_string() const;
    bool is_url() const;
    bool is_image() const;
    bool is_color() const;
    
    ns::String to_string() const;
    operator ns::String () const;
    
    ns::URL to_url() const;
    operator ns::URL () const;
    
    ui::Image to_image() const;
    operator ui::Image () const;
    
    ui::Color to_color() const;
    operator ui::Color () const;
    
    void clear();
    uint count() const;
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif

# endif
