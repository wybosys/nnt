
# ifndef __NNTNS_IMAGEVIEW_6CDB039EA8C64B81B64262F9079A392C_H_INCLUDED
# define __NNTNS_IMAGEVIEW_6CDB039EA8C64B81B64262F9079A392C_H_INCLUDED

# include "NSControl+NNT.h"

NNT_BEGIN_HEADER_OBJC

@interface NSImageView (NNT)

- (id)initWithURL:(NSURL*)url;

- (void)loadURL:(NSURL*)url;

@end

@interface NNTNSImageView : NSImageView

@end

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX NNT_BEGIN_NS(ui)

template <typename imageT = NNTNSImageView>
class ImageView
: public Control<imageT, ImageView<imageT> >
{
    typedef Control<imageT, ImageView<imageT> > super;
    
public:
    
    ImageView()
    {
        imageT* img = [[imageT alloc] initWithZero];
        this->_sethandle(img);
        [img release];
    }
    
    inline void set_image(NSURL* url)
    {
        [this->hdl() loadURL:url];
    }
    
    inline void set_image(NSImage* img)
    {
        this->hdl().image = img;
    }
    
    inline ::NSImage* get_image() const
    {
        return this->hdl().image;
    }
    
};

NNT_END_NS NNT_END_HEADER_CXX

# endif

# endif