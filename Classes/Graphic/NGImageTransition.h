
# ifndef __NNT_UIKIT_NgIMAGETRANSITION_67B9B68CFAFF4E889B2292E2936EFE42_H_INCLUDED
# define __NNT_UIKIT_NgIMAGETRANSITION_67B9B68CFAFF4E889B2292E2936EFE42_H_INCLUDED

NNT_BEGIN_HEADER_OBJC

NNTDECL_PRIVATE_HEAD(NgImageTransition);

typedef void (*NgImageTransitionLineProc)(void* des, void const* src, int left, int right, uint len);

typedef struct {
    uint row;
    uint counter;
    real time;
    real velocity;
    void *ctx;
} NgImageTransitionLineOffsetParam;

typedef int (*NgImageTransitionLineOffset)(NgImageTransitionLineOffsetParam*);

@protocol NgImageTransitionDelegate <NSObject>

//! for each frame.
- (void)imageTransition:(NgImageTransition*)sender image:(CGImageRef)image param:(NgImageTransitionLineOffsetParam*)param;

@optional
- (void)imageTransitionBegin:(NgImageTransition*)sender;
- (void)imageTransitionEnd:(NgImageTransition*)sender;

@end

@interface NgImageTransition : NNTObject {
    
    CGImageRef image_default;
    CGImageRef image;
    NgImageTransitionLineProc proc_line;
    CFTimeInterval duration, frame_duration;
    id<NgImageTransitionDelegate> delegate;
    NgImageTransitionLineOffset offset_left, offset_right;
    void *offset_context;
    uint counter;
    real fps;
    NSInteger frame_interval;
    real velocity;
    
    NNTDECL_PRIVATE(NgImageTransition);
}

@property (nonatomic, assign) CGImageRef image_default;
@property (nonatomic, readonly) CGImageRef image;
@property (nonatomic, assign) NgImageTransitionLineProc proc_line;
@property (nonatomic, assign) CFTimeInterval duration;
@property (nonatomic, readonly) CFTimeInterval frame_duration;
@property (nonatomic, assign) id<NgImageTransitionDelegate> delegate;
@property (nonatomic, assign) NgImageTransitionLineOffset offset_left, offset_right;
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
extern const CFTimeInterval kNgImageTransitionDefaultDuration;
extern int kOffsetZero(NgImageTransitionLineOffsetParam*);

NNT_END_HEADER_OBJC

# endif