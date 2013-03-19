
# import "Core.h"
# import "UICell.h"

WSI_BEGIN_OBJC

@implementation NSCellLine

@synthesize nextLine, prevLine;
@synthesize npos, pos;
@synthesize style;
@dynamic absolutePos;

- (void)dealloc {
    [style release];
    [super dealloc];
}

- (real)getAbsolutePos {
    real ret = pos;
    NSCellLine const* pre = self.prevLine;
    while (pre) {
        ret += pre.pos;
        pre = pre.prevLine;
    }
    return ret;
}

- (BOOL)distancePrev:(const NSCellLine *)line val:(real *)val {
    if (self == line) {
        *val = 0;
        return YES;
    }
    BOOL ret = NO;
    real sum = pos;
    NSCellLine const* pre = self.prevLine;
    while (pre) {
        if (pre == line) {
            ret = YES;
            *val = sum;
            break;
        }
        sum += pre.pos;
        pre = pre.prevLine;
    }
    return ret;
}

- (real)distancePrev:(const NSCellLine *)line {
    if (self == line)
        return 0;
    real sum = pos;
    NSCellLine const* pre = self.prevLine;
    while (pre) {
        if (pre == line) {
            return sum;
        }
        sum += pre.pos;
        pre = pre.prevLine;
    }
    return 0;
}

- (BOOL)distanceNext:(const NSCellLine *)line val:(real *)val {
    if (self == line) {
        *val = 0;
        return YES;
    }
    BOOL ret = NO;
    real sum = 0;
    NSCellLine const* next = self.nextLine;
    while (next) {
        if (next == line) {
            ret = YES;
            *val = sum;
            break;
        }
        sum += next.pos;
        next = next.nextLine;
    }
    return ret;
}

- (real)distanceNext:(const NSCellLine *)line {
    if (self == line) {
        return 0;
    }
    real sum = 0;
    NSCellLine const* next = self.nextLine;
    while (next) {
        if (next == line) {
            return sum;
        }
        sum += next.pos;
        next = next.nextLine;
    }
    return 0;
}

@end

@implementation NSCell

@synthesize text, textStyle;
@synthesize lineTop, lineLeft, lineRight, lineBottom;
@dynamic width, height;
@dynamic row, col;

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    zero_release(text);
    zero_release(textStyle);
    [super dealloc];
}

- (real)getWidth {
    return [self.lineRight distancePrev:self.lineLeft];
}

- (real)getHeight {
    return [self.lineBottom distancePrev:self.lineTop];
}

- (NSUInteger)getRow {
    return lineTop.npos;
}

- (NSUInteger)getCol {
    return lineLeft.npos;
}

- (NSString*)getText {
    return text;
}

@end

@implementation UICell

@synthesize cell;
@synthesize cellFill;

- (void)dealloc {
    [cell release];
    [cellFill release];
    [super dealloc];
}

@end

WSI_END_OBJC