
# ifndef __WSI_VISION_CODECDETECT_85B639C8E30D4E74BAC69BE8392F1BC2_H_INCLUDED
# define __WSI_VISION_CODECDETECT_85B639C8E30D4E74BAC69BE8392F1BC2_H_INCLUDED

# import "ICRCameraController.h"

WSI_BEGIN_HEADER_OBJC

@interface CodecDetectMaskView : WSIUIView

@end

@interface CodecDetectView : WSIUIView {
    ICRCameraController* _icrcamera;
    WSIUIView* _maskView;
}

@property (nonatomic, readonly) ICRCameraController* icrcamera;
@property (nonatomic, retain) WSIUIView* maskView;

@end

@interface CodecDetectController : WSIUIViewController {
    BOOL _continuable;
    BOOL _processing;
}

@property (nonatomic, assign) BOOL continuable;

- (void)suspend;
- (void)resume;

@end

_CXXCONTROLLER_DECL(CodecDetectController);

WSI_EXTERN signal_t kSignalTry;
WSI_EXTERN signal_t kSignalSuccess;

WSI_END_HEADER_OBJC

# ifdef WSI_CXX

WSI_BEGIN_HEADER_CXX
WSI_BEGIN_NS(vision)

class CodecDetect
: public ui::SimpleController<CodecDetect, _CXXCONTROLLER(CodecDetectController), CodecDetectView>
{
    typedef
    SimpleController<CodecDetect, _CXXCONTROLLER(CodecDetectController), CodecDetectView>
    super;
    
public:
    
    CodecDetect()
    {
        PASS;
    }
    
    virtual void view_loaded()
    {
        PASS;
    }
    
    void set_continuable(bool b = true)
    {
        this->_self.continuable = b;
    }
    
};

WSI_END_NS
WSI_END_HEADER_CXX

# endif

# endif
