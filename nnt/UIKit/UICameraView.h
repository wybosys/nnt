
# ifndef __NNT_UICAMERAVIEW_50F967DEB0E04D6F9CF0FDEEFC3D77F7_H_INCLUDED
# define __NNT_UICAMERAVIEW_50F967DEB0E04D6F9CF0FDEEFC3D77F7_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

NNTDECL_PRIVATE_HEAD(UICameraView);

@interface UICameraView : NNTUIView {    
    NNTDECL_PRIVATE_EX(UICameraView, d_ptr_camera);
}

- (void)snapshot;

@end

NNT_EXTERN signal_t kSignalSnapshot;

# ifdef NNT_CXX

_CXXVIEW_DECL(UICameraView);

# endif

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

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

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
