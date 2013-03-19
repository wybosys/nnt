
# import "Core.h"
# import "UISegmentedControl+NNT.h"

NNT_BEGIN_OBJC

@implementation UISegmentedControl (NNT)

-(void)setTag:(NSInteger)tag forSegmentAtIndex:(NSUInteger)segment {
    [[[self subviews] objectAtIndex:segment] setTag:tag];
}

-(void)setTintColor:(UIColor*)color forTag:(NSInteger)aTag {
    // must operate by tags.  Subview index is unreliable
    UIView *segment = [self viewWithTag:aTag];
    SEL tint = @selector(setTintColor:);
    
    // UISegment is an undocumented class, so tread carefully
    // if the segment exists and if it responds to the setTintColor message
    if (segment && ([segment respondsToSelector:tint])) {
        [segment performSelector:tint withObject:color];
    }
}

-(void)setTextColor:(UIColor*)color forTag:(NSInteger)aTag {
    UIView *segment = [self viewWithTag:aTag];
    for (UIView *view in segment.subviews) {
        SEL text = @selector(setTextColor:);

        // if the sub view exists and if it responds to the setTextColor message
        if (view && ([view respondsToSelector:text])) {
            [view performSelector:text withObject:color];
        }
    }
}

-(void)setShadowColor:(UIColor*)color forTag:(NSInteger)aTag {
    
    // you probably know the drill by now
    // you could also combine setShadowColor and setTextColor
    UIView *segment = [self viewWithTag:aTag];
    for (UIView *view in segment.subviews) {
        SEL shadowColor = @selector(setShadowColor:);
        if (view && ([view respondsToSelector:shadowColor])) {
            [view performSelector:shadowColor withObject:color];
        }
    }
}

@end

NNTIMPL_CATEGORY(UISegmentedControl, NNT);

@implementation NNTUISegmentedControl

NNTOBJECT_IMPL_NOSIGNALS;

@synthesize defaultColor, selectedColor, shadowColor, defaultTextColor, selectedTextColor, enableReselected;

- (id)initWithItems:(NSArray *)items custom:(BOOL)custom {
    self = [self initWithItems:items];
    
    enableReselected = NO;
    
    if (custom) {
        self.segmentedControlStyle = UISegmentedControlStyleBar;
        
        uint const count = [items count];
        __custom_tag_begin = 0x100;
        for (uint i = 0; i < count; ++i) {
            [self setTag:__custom_tag_begin + i forSegmentAtIndex:i];
        }                
    }
    
    return self;
}

- (id)initWithItems:(NSArray *)items {
    self = [super initWithItems:items];
    [self addTarget:self action:@selector(act_value_changed:) forControlEvents:UIControlEventValueChanged];
    return self;
}

- (void)dealloc {
    zero_release(defaultColor);
    zero_release(selectedColor);
    zero_release(shadowColor);
    zero_release(defaultTextColor);
    zero_release(selectedTextColor);
    
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

- (void)initSignals {
    NNTEVENT_SIGNAL(kSignalSelectChanged);
}

- (void)setDefaultColor:(UIColor *)__defaultColor {
    [defaultColor release];
    defaultColor = [__defaultColor retain];
    
    uint const count = self.numberOfSegments;
    for (uint i = 0; i < count; ++i) {
        [self setTintColor:defaultColor forTag:__custom_tag_begin + i];
    }
}

- (void)setShadowColor:(UIColor *)__shadowColor {
    [shadowColor release];
    shadowColor = [__shadowColor retain];
    
    uint const count = self.numberOfSegments;
    for (uint i = 0; i < count; ++i) {
        [self setShadowColor:shadowColor forTag:__custom_tag_begin + i];
    }
}

- (void)setDefaultTextColor:(UIColor *)__defaultTextColor {
    [defaultTextColor release];
    defaultTextColor = [__defaultTextColor retain];
    
    uint const count = self.numberOfSegments;
    for (uint i = 0; i < count; ++i) {
        [self setTextColor:defaultTextColor forTag:__custom_tag_begin + i];
    }
    
    if (selectedTextColor == nil)
        self.selectedTextColor = defaultTextColor;
}

- (void)setSelectedColor:(UIColor *)color {
    [NSObject refobjSet:&selectedColor ref:color];
    
    uint cur_sel = self.selectedSegmentIndex;
    if (cur_sel == UISegmentedControlNoSegment)
        return;
    
    if (selectedColor)
        [self setTintColor:selectedColor forTag:__custom_tag_begin + cur_sel];
    if (selectedTextColor)
        [self setTextColor:selectedTextColor forTag:__custom_tag_begin + cur_sel];
}

- (void)setSelectedTextColor:(UIColor *)color {
    [NSObject refobjSet:&selectedTextColor ref:color];
    
    uint cur_sel = self.selectedSegmentIndex;
    if (cur_sel == UISegmentedControlNoSegment)
        return;
    
    if (selectedColor)
        [self setTintColor:selectedColor forTag:__custom_tag_begin + cur_sel];
    if (selectedTextColor)
        [self setTextColor:selectedTextColor forTag:__custom_tag_begin + cur_sel];
}

- (void)act_value_changed:(id)sender {
    uint const count = self.numberOfSegments;
    for (uint i = 0; i < count; ++i) {
        if (defaultColor)
            [self setTintColor:defaultColor forTag:__custom_tag_begin + i];
        if (shadowColor)
            [self setShadowColor:shadowColor forTag:__custom_tag_begin + i];
        if (defaultTextColor)
            [self setTextColor:defaultTextColor forTag:__custom_tag_begin + i];
    }
    
    uint cur_sel = self.selectedSegmentIndex;
    if (selectedColor)
        [self setTintColor:selectedColor forTag:__custom_tag_begin + cur_sel];
    if (selectedTextColor)
        [self setTextColor:selectedTextColor forTag:__custom_tag_begin + cur_sel];
    
    [self emit:kSignalSelectChanged result:[NSNumber numberWithInt:cur_sel]];
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)__event {
    [super touchesBegan:touches withEvent:__event];
    
     __lst_selected = self.selectedSegmentIndex;
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)__event {
    [super touchesEnded:touches withEvent:__event];
    
    NSUInteger sel = self.selectedSegmentIndex;
    
    if ((sel == __lst_selected) && enableReselected) {
        if (sel !=  UISegmentedControlNoSegment)
            [self emit:kSignalSelectChanged];
    }
}
         
@end

NNT_END_OBJC