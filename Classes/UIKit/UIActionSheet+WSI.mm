
# import "Core.h"
# import "UIActionSheet+NNT.h"

NNT_BEGIN_OBJC

signal_t kSignalCancelButtonClicked = @"::wsi::ui::button::cancel::clicked";
signal_t kSignalDestructButtonClicked = @"::wsi::ui::button::destruct::clicked";

@interface NNTUIActionSheet ()

- (id)_addItem:(uint)idx;
- (id)_findItem:(uint)idx;

@end

@implementation NNTUIActionSheet

NNTOBJECT_IMPL_NOSIGNALS;

- (id)init {
    self = [super init];
    
    _items = [[NSMutableDictionary alloc] init];
    
    return self;
}

- (id)initWithTitle:(NSString*)title {
    self = [super initWithTitle:title 
                       delegate:self
              cancelButtonTitle:nil
         destructiveButtonTitle:nil
              otherButtonTitles:nil];
    return self;
}

- (id)initWithTitle:(NSString*)title cancel:(NSString*)cancel destruct:(NSString*)destruct {
    self = [super initWithTitle:title 
                       delegate:self
              cancelButtonTitle:cancel
         destructiveButtonTitle:destruct
              otherButtonTitles:nil];    
    return self;
}

- (void)dealloc {
    zero_release(_items);
    
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

- (void)initSignals {
    NNTEVENT_SIGNAL(kSignalViewAppear);
    NNTEVENT_SIGNAL(kSignalViewDisappear);
}

- (id)addItem:(NSString*)title {
    uint idx = [self addButtonWithTitle:title];
    return [self _addItem:idx];
}

- (id)setCancel:(NSString*)title {
    if (self.cancelButtonIndex == -1) {
        uint idx = [self addButtonWithTitle:title];
        self.cancelButtonIndex = idx;
        return [self _addItem:idx];
    }
    
    NNTObject* obj = [self _findItem:self.cancelButtonIndex];
    obj = [obj retain];
    [_items removeObjectForKey:[NSNumber numberWithUnsignedInteger:self.cancelButtonIndex]];
    uint idx = [self addButtonWithTitle:title];
    self.cancelButtonIndex = idx;
    [obj release];
    return [self _addItem:idx];
}

- (id)_addItem:(uint)idx {
    NNTObject* obj = [[NNTObject alloc] init];
    [obj register_signal:kSignalButtonClicked];
    [_items setObject:obj
               forKey:[NSNumber numberWithUnsignedInteger:idx]];
    [obj release];
    return obj;
}

- (id)_findItem:(uint)idx {
    return [_items objectForKey:[NSNumber numberWithUnsignedInteger:idx]
                           null:nil];
}

// delegate.

- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex {
    NNTObject* obj = [_items objectForKey:[NSNumber numberWithUnsignedInteger:buttonIndex]];
    [obj emit:kSignalButtonClicked];
}

- (void)actionSheetCancel:(UIActionSheet *)actionSheet {
    [self emit:kSignalCancelButtonClicked];
}

- (void)didPresentActionSheet:(UIActionSheet *)actionSheet {
    [self emit:kSignalViewAppear];
}

- (void)actionSheet:(UIActionSheet *)actionSheet willDismissWithButtonIndex:(NSInteger)buttonIndex {
    PASS;
}

- (void)actionSheet:(UIActionSheet *)actionSheet didDismissWithButtonIndex:(NSInteger)buttonIndex {
    if (self.cancelButtonIndex != -1) {
        if (self.cancelButtonIndex == buttonIndex) {
            NNTObject* obj = [self _findItem:buttonIndex];
            [obj emit:kSignalButtonClicked];
        }
    }
    
    [self emit:kSignalViewDisappear];
}

@end

NNT_END_OBJC