
# ifndef __NNT_MODEL_CHART2D_D7E44BD8F50E4D67A93D4AD13C302C9B_H_INCLUDED
# define __NNT_MODEL_CHART2D_D7E44BD8F50E4D67A93D4AD13C302C9B_H_INCLUDED

# import "MChartRecord.h"

NNT_BEGIN_HEADER_OBJC

NNTDECL_PRIVATE_HEAD(MChart2D);

@interface MChart2DValue : NSObject {
    NSNumber *value;
    NSNumber *position;
    NSString *label;
    NSNumber *color;
}

@property (nonatomic, copy) NSNumber *value;
@property (nonatomic, copy) NSNumber *position;
@property (nonatomic, copy) NSString *label;
@property (nonatomic, copy) NSNumber *color;

@end

@interface MChart2D : MChartRecord {        
    
    NSNumber *max_position;
    NSNumber *max_value;
    
    NNTDECL_PRIVATE_EX(MChart2D, _d_ptr_chart2d);
}

@property (nonatomic, readonly) NSNumber *max_position;
@property (nonatomic, readonly) NSNumber *max_value;


//! @function add value
- (void)add_value:(MChart2DValue*)__value;

//! @function size
- (uint)size;

//! @function get value
- (MChart2DValue*)get_at:(uint)__index;

@end

NNT_END_HEADER_OBJC

# endif