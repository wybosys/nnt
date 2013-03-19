
# ifndef __NNT_ICRCAMERA_CONTROLLER_F96B81C48BDF4E298379824561273B1B_H_INCLUDED
# define __NNT_ICRCAMERA_CONTROLLER_F96B81C48BDF4E298379824561273B1B_H_INCLUDED

# import "UIViewController+NNT.h"
# import "UICameraView.h"

NNT_BEGIN_HEADER_OBJC

@interface ICRCameraView : NNTUIView {
    UICameraView* _camera;
}

@property (nonatomic, readonly) UICameraView* camera;

@end

NNTDECL_PRIVATE_HEAD(ICRCameraController);

@interface ICRCameraController : NNTUIViewController {
    
    ICRCameraView* _cameraView;    
    
    NNTDECL_PRIVATE(ICRCameraController);
}

@property (nonatomic, readonly) ICRCameraView* cameraView;

- (void)suspend;
- (void)resume;

@end

NNT_EXTERN signal_t kSignalSnapshot;

# ifdef NNT_CXX

_CXXCONTROLLER_DECL(ICRCameraController);

# endif

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(ui)

class IICRCamera
: public IViewController
{
public:
};

class ICRCamera
: public SimpleController<ICRCamera, _CXXCONTROLLER(ICRCameraController), UICameraView, Camera, IICRCamera>
{
    typedef
    SimpleController<ICRCamera, _CXXCONTROLLER(ICRCameraController), UICameraView, Camera, IICRCamera>
    super;
    
public:
    
    ICRCamera()
    {
        PASS;
    }
    
    ~ICRCamera()
    {
        PASS;
    }
    
    virtual void view_loaded()
    {
        PASS;
    }
    
    void suspend()
    {
        [this->_self suspend];
    }
    
    void resume()
    {
        [this->_self resume];
    }
    
};

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
