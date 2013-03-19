
# import "Core.h"
# import "UIPickerView+NNT.h"
# include "JuiceCocoa++.hpp"

NNT_BEGIN_OBJC

NSUInteger kUIPickerViewHeight = 216;

@implementation NNTUIPickerView

NNTOBJECT_IMPL;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    return self;
}

- (void)setFrame:(CGRect)frame {
    frame.size.height = kUIPickerViewHeight;
    [super setFrame:frame];
}

- (void)dealloc {
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

@end

@implementation NNTUIDatePicker

NNTOBJECT_IMPL;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    return self;
}

- (void)setFrame:(CGRect)frame {
    frame.size.height = kUIPickerViewHeight;
    [super setFrame:frame];
}

- (void)dealloc {
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

@end

_CXXCONTROL_IMPL(NNTUIDatePicker);

@implementation UIDrumPickerView

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    
    return self;
}

- (void)dealloc {
    [super dealloc];
}

- (void)drawRect:(CGRect)rect {
    [super drawRect:rect];
    
    ::juice::cocoa::Graphics gra = ::juice::cocoa::Graphics::Current(rect);
}

@end

NNT_END_OBJC
