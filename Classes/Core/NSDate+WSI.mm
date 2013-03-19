
# import "Core.h"
# import "NSDate+WSI.h"

WSI_BEGIN_OBJC

@implementation NSDate (WSI)

- (id)initWithYear:(NSUInteger)year
             Month:(NSUInteger)month
               Day:(NSUInteger)day
              Hour:(NSUInteger)hour
            Minute:(NSUInteger)minute
            Second:(NSUInteger)second
{
    WSI_AUTORELEASEPOOL_BEGIN
    
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    //[dateFormatter setTimeZone:[NSTimeZone timeZoneWithName:@"UTC"]];
    [dateFormatter setTimeZone:[NSTimeZone localTimeZone]];
    [dateFormatter setDateFormat:@"yyyy MM dd HH mm ss"];
    NSString* str = [NSString stringWithFormat:
                     @"%d %d %d %d %d %d",
                     (int)year, (int)month, (int)day, (int)hour, (int)minute, (int)second];
    NSDate *date = [dateFormatter dateFromString:str];
    [dateFormatter release];
    
    [self dealloc];
    
    self = [date retain];
    
    WSI_AUTORELEASEPOOL_END
    
    return self;
}

@end

@implementation NSDatePeriod

@synthesize begin = _begin, end = _end;

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    safe_release(_begin);
    safe_release(_end);
    [super dealloc];
}

- (BOOL)isDuring {
    NSDate* current = [[NSDate alloc] initWithTimeIntervalSinceNow:0];
    BOOL ret = YES;
    switch ([current compare:_begin])
    {
        case NSOrderedDescending:
        case NSOrderedSame:
            ret = YES;
            break;
        default:
            ret = NO;
            break;
    }
    if (ret) {
        switch ([current compare:_end])
        {
            case NSOrderedAscending:
            case NSOrderedSame:
                ret = YES;
                break;
            default:
                ret = NO;
                break;
        }
    }
    safe_release(current);
    return ret;
}

@end

WSIIMPL_CATEGORY(NSDate, WSI);

NSString
*kTimeZoneBeijing = @"Asia/Beijing",
*kTimeZoneShanghai = @"Asia/Shanghai",
*kTimeZoneChongqing = @"Asia/Chongqing"
;

WSI_END_OBJC