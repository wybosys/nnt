
# ifndef __WSI_ICRCAMERA_CONTROLLER_F96B81C48BDF4E298379824561273B1B_H_INCLUDED
# define __WSI_ICRCAMERA_CONTROLLER_F96B81C48BDF4E298379824561273B1B_H_INCLUDED

# import "UIViewController+WSI.h"
# import "UICameraView.h"

WSI_BEGIN_HEADER_OBJC

@interface ICRCameraView : WSIUIView {
    UICameraView* _camera;
}

@property (nonatomic, readonly) UICameraView* camera;

@end

WSIDECL_PRIVATE_HEAD(ICRCameraController);

@interface ICRCameraController : WSIUIViewController {
    
    ICRCameraView* _cameraView;    
    
    WSIDECL_PRIVATE(ICRCameraController);
}

@property (nonatomic, readonly) ICRCameraView* cameraView;

- (void)suspend;
- (void)resume;

@end

WSI_EXTERN signal_t kSignalSnapshot;

# ifdef WSI_CXX

_CXXCONTROLLER_DECL(ICRCameraController);

# endif

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(ui)

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

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
