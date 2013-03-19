
# ifndef __WSINS_IMAGEVIEW_6CDB039EA8C64B81B64262F9079A392C_H_INCLUDED
# define __WSINS_IMAGEVIEW_6CDB039EA8C64B81B64262F9079A392C_H_INCLUDED

# include "NSControl+WSI.h"

WSI_BEGIN_HEADER_OBJC

@interface NSImageView (WSI)

- (id)initWithURL:(NSURL*)url;

- (void)loadURL:(NSURL*)url;

@end

@interface WSINSImageView : NSImageView

@end

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX WSI_BEGIN_NS(ui)

template <typename imageT = WSINSImageView>
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

WSI_END_NS WSI_END_HEADER_CXX

# endif

# endif