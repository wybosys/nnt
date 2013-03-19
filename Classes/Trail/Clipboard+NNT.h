
# ifndef __NNT_TRAIL_CLIPBOARD_79B495BE60EF46B2805AAEF1D2ABEBB9_H_INCLUDED
# define __NNT_TRAIL_CLIPBOARD_79B495BE60EF46B2805AAEF1D2ABEBB9_H_INCLUDED

# ifdef NNT_OBJC

NNT_BEGIN_HEADER_OBJC

NNTDECL_EXTERN_CLASS(UIPasteboard);

NNTDECL_PRIVATE_HEAD(Clipboard);

@interface Clipboard : NNTObject {
    NNTDECL_PRIVATE(Clipboard);
}

- (id)init;
- (id)initWithUnique;
- (id)initWithName:(NSString*)name;

- (UIPasteboard*)pasteboard;

@end

NNT_EXTERN signal_t kSignalContentChanged;

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(sys)

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

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif

# endif
