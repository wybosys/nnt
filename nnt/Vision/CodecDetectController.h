
# ifndef __NNT_VISION_CODECDETECT_85B639C8E30D4E74BAC69BE8392F1BC2_H_INCLUDED
# define __NNT_VISION_CODECDETECT_85B639C8E30D4E74BAC69BE8392F1BC2_H_INCLUDED

# import "ICRCameraController.h"

NNT_BEGIN_HEADER_OBJC

@interface CodecDetectMaskView : NNTUIView

@end

@interface CodecDetectView : NNTUIView {
    ICRCameraController* _icrcamera;
    NNTUIView* _maskView;
}

@property (nonatomic, readonly) ICRCameraController* icrcamera;
@property (nonatomic, retain) NNTUIView* maskView;

@end

@interface CodecDetectController : NNTUIViewController {
    BOOL _continuable;
    BOOL _processing;
}

@property (nonatomic, assign) BOOL continuable;

- (void)suspend;
- (void)resume;

@end

_CXXCONTROLLER_DECL(CodecDetectController);

NNT_EXTERN signal_t kSignalTry;
NNT_EXTERN signal_t kSignalSuccess;

NNT_END_HEADER_OBJC

# ifdef NNT_CXX

NNT_BEGIN_HEADER_CXX
NNT_BEGIN_NS(vision)

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

NNT_END_NS
NNT_END_HEADER_CXX

# endif

# endif
