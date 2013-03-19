
# import "Core.h"
# import "MChart2D.h"

NNT_BEGIN

@implementation MChart2DValue 

@synthesize value, position, label, color;

- (id)init {
    self = [super init];
    
    value = [[NSNumber alloc] initWithInt:0];
    position = nil;
    label = nil;
    color = nil;
    
    return self;
}

- (void)dealloc {
    zero_release(value);
    zero_release(position);
    zero_release(label);
    zero_release(color);
    [super dealloc];
}

@end

@interface MChart2DPrivate : NSObject {
    
    NSMutableArray *values;
    NSNumber *max_position;
    NSNumber *max_value;
    
    MChart2D *d_owner;
}

@property (nonatomic, assign) MChart2D *d_owner;
@property (nonatomic, readonly) NSMutableArray *values;
@property (nonatomic, copy) NSNumber *max_position;
@property (nonatomic, copy) NSNumber *max_value;

@end

@implementation MChart2DPrivate

@synthesize d_owner;
@synthesize values, max_position, max_value;

- (id)init {
    self = [super init];
    
    values = [NSMutableArray new];
    max_position = [[NSNumber alloc] initWithInt:0];
    max_value = [[NSNumber alloc] initWithInt:0];
    
    return self;
}

- (void)dealloc {
    zero_release(values);
    zero_release(max_position);
    zero_release(max_value);
    [super dealloc];
}

@end

@implementation MChart2D

@dynamic max_position, max_value;

- (id)init {
    self = [super init];
    NNTDECL_PRIVATE_INIT_EX(MChart2D, _d_ptr_chart2d);    
    return self;
}

- (void)dealloc {
    NNTDECL_PRIVATE_DEALLOC_EX(_d_ptr_chart2d);
    [super dealloc];
}

- (void)add_value:(MChart2DValue*)__value {
    if (nil == __value.position) __value.position = [NSNumber numberWithInt:[self size]];
    if (nil == __value.label) __value.label = [__value.position stringValue];
    [_d_ptr_chart2d.values addObject:__value];
    if (__value.value > _d_ptr_chart2d.max_value) {
        _d_ptr_chart2d.max_value = __value.value;
    }
    if (__value.position > _d_ptr_chart2d.max_position) {
        _d_ptr_chart2d.max_position = __value.position;
    }
}

- (uint)size {
    return (uint)[_d_ptr_chart2d.values count];
}

- (MChart2DValue*)get_at:(uint)__index {
    return [_d_ptr_chart2d.values objectAtIndex:__index];
}

- (NSNumber*)max_position {
    return _d_ptr_chart2d.max_position;
}

- (NSNumber*)max_value {
    return _d_ptr_chart2d.max_value;
}

@end

NNT_END