
# ifndef __WSI_UICAMERAVIEW_50F967DEB0E04D6F9CF0FDEEFC3D77F7_H_INCLUDED
# define __WSI_UICAMERAVIEW_50F967DEB0E04D6F9CF0FDEEFC3D77F7_H_INCLUDED

WSI_BEGIN_HEADER_OBJC

WSIDECL_PRIVATE_HEAD(UICameraView);

@interface UICameraView : WSIUIView {    
    WSIDECL_PRIVATE_EX(UICameraView, d_ptr_camera);
}

- (void)snapshot;

@end

WSI_EXTERN signal_t kSignalSnapshot;

# ifdef WSI_CXX

_CXXVIEW_DECL(UICameraView);

# endif

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

class ICamera
: public IView
{
public:
    
};

class Camera
: public View<Camera, _CXXVIEW(UICameraView), ICamera>
{
    typedef View<Camera, _CXXVIEW(UICameraView), ICamera> super;
    
public:
    
    Camera()
    {
        PASS;
    }
    
    Camera(objc_type* o, bool r)
    : super(o, r)
    {
        PASS;
    }
    
    ~Camera()
    {
        PASS;
    }
    
    void layout_subviews()
    {
        PASS;
    }
    
    void snapshot()
    {
        [this->_self snapshot];
    }
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
