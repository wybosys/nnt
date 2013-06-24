
# import "Core.h"
# import "ccView+NNT.h"
# import "cocos2dx.prv.h"
# import "../../../contrib/cocos2dx/cocos2dx/platform/ios/EAGLView.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(cocos)

View::View()
{
    _gl = [EAGLView viewWithFrame:[[UIScreen mainScreen] bounds]
                      pixelFormat:kEAGLColorFormatRGBA8
                      depthFormat:GL_DEPTH_COMPONENT16
               preserveBackbuffer:NO
                       sharegroup:nil
                    multiSampling:NO
                  numberOfSamples:0];
    
    [_self addSubview:_gl];
}

View::~View()
{
    
}

void View::layout_subviews()
{
    _gl.frame = bounds();
}

NNT_END_NS
NNT_END_CXX
