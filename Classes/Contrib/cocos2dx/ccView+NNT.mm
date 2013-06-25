
# import "Core.h"
# import "cocos2dx+NNT.h"
# import "ccView+NNT.h"

NNT_BEGIN_HEADER_OBJC

@interface EAGLView : UIView

+ (id) viewWithFrame:(CGRect)frame
         pixelFormat:(NSString*)format
         depthFormat:(GLuint)depth
  preserveBackbuffer:(BOOL)retained
          sharegroup:(EAGLSharegroup*)sharegroup
       multiSampling:(BOOL)multisampling
     numberOfSamples:(unsigned int)samples;

@end

NNT_END_HEADER_OBJC

NNT_BEGIN_CXX
NNT_BEGIN_NS(ui)
NNT_BEGIN_NS(cocos2d)

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
NNT_END_NS
NNT_END_CXX
