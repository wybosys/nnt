
# ifndef __NNT_UIKIT_WCGIMAGETRANSITION_67B9B68CFAFF4E889B2292E2936EFE42_H_INCLUDED
# define __NNT_UIKIT_WCGIMAGETRANSITION_67B9B68CFAFF4E889B2292E2936EFE42_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

NNTDECL_PRIVATE_HEAD(WCGImageTransition);

typedef void (*WCGImageTransitionLineProc)(void* des, void const* src, int left, int right, uint len);

typedef struct {
    uint row;
    uint counter;
    real time;
    real velocity;
    void *ctx;
} WCGImageTransitionLineOffsetParam;

typedef int (*WCGImageTransitionLineOffset)(WCGImageTransitionLineOffsetParam*);

@protocol WCGImageTransitionDelegate <NSObject>

//! for each frame.
- (void)imageTransition:(WCGImageTransition*)sender image:(CGImageRef)image param:(WCGImageTransitionLineOffsetParam*)param;

@optional
- (void)imageTransitionBegin:(WCGImageTransition*)sender;
- (void)imageTransitionEnd:(WCGImageTransition*)sender;

@end

@interface WCGImageTransition : NNTObject {
    
    CGImageRef image_default;
    CGImageRef image;
    WCGImageTransitionLineProc proc_line;
    CFTimeInterval duration, frame_duration;
    id<WCGImageTransitionDelegate> delegate;
    WCGImageTransitionLineOffset offset_left, offset_right;
    void *offset_context;
    uint counter;
    real fps;
    NSInteger frame_interval;
    real velocity;
    
    NNTDECL_PRIVATE(WCGImageTransition);
}

@property (nonatomic, assign) CGImageRef image_default;
@property (nonatomic, readonly) CGImageRef image;
@property (nonatomic, assign) WCGImageTransitionLineProc proc_line;
@property (nonatomic, assign) CFTimeInterval duration;
@property (nonatomic, readonly) CFTimeInterval frame_duration;
@property (nonatomic, assign) id<WCGImageTransitionDelegate> delegate;
@property (nonatomic, assign) WCGImageTransitionLineOffset offset_left, offset_right;
@property (nonatomic, assign) void *offset_context;
@property (nonatomic, assign) uint counter;
@property (nonatomic, readonly) real fps;
@property (nonatomic, assign) NSInteger frame_interval;
@property (nonatomic, assign) real velocity;

- (id)initWithCGImage:(CGImageRef)image;
- (void)clear;

- (void)start;
- (void)stop;

@end

extern void kARGBLineDoubleInsetProc(argb_t*, argb_t const*, int, int, uint);
extern const CFTimeInterval kWCGImageTransitionDefaultDuration;
extern int kOffsetZero(WCGImageTransitionLineOffsetParam*);

NNT_END_HEADER_OBJC

# endif