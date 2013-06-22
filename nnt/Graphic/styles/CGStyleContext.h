
# ifndef __NNT_CG_STYLECONTEXT_0C00BE4C4DCD4313A52A3DCCBAA09781_H_INCLUDED
# define __NNT_CG_STYLECONTEXT_0C00BE4C4DCD4313A52A3DCCBAA09781_H_INCLUDED

# import "../shapes/CGShape.h"

NNT_BEGIN_HEADER_OBJC

@interface NgStyleContext : NSObject {
    CGContextRef _ctx;
    NgShape* _shape;
}

@property (nonatomic, assign) CGContextRef context;
@property (nonatomic, assign) CGRect bounds;
@property (nonatomic, assign) NgShape* shape;

@end

NNT_END_HEADER_OBJC

# endif