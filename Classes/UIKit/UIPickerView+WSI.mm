
# import "Core.h"
# import "UIPickerView+WSI.h"
# include "JuiceCocoa++.hpp"

WSI_BEGIN_OBJC

NSUInteger kUIPickerViewHeight = 216;

@implementation WSIUIPickerView

WSIOBJECT_IMPL;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    return self;
}

- (void)setFrame:(CGRect)frame {
    frame.size.height = kUIPickerViewHeight;
    [super setFrame:frame];
}

- (void)dealloc {
    WSIOBJECT_DEALLOC;
    [super dealloc];
}

@end

@implementation WSIUIDatePicker

WSIOBJECT_IMPL;

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    return self;
}

- (void)setFrame:(CGRect)frame {
    frame.size.height = kUIPickerViewHeight;
    [super setFrame:frame];
}

- (void)dealloc {
    WSIOBJECT_DEALLOC;
    [super dealloc];
}

@end

_CXXCONTROL_IMPL(WSIUIDatePicker);

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

WSI_END_OBJC
