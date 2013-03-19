
# import "Core.h"
# import "UIOAToggleView.h"
# import "UISwitch+NNT.h"
# import "OAToggle.h"
# import "UIOAToggleView.res"

NNT_BEGIN_OBJC

@interface UIOAToggleViewPrivate : NNTObject {
    UIOAToggleView *d_owner;
    OAToggle *toggle;
}

@property (nonatomic, assign) UIOAToggleView *d_owner;
@property (nonatomic, retain) OAToggle *toggle;

- (void)initToggle;
- (void)toggle_begin:(id)__id;

@end

@implementation UIOAToggleViewPrivate

@synthesize d_owner;
@synthesize toggle;

- (id)init {    
    self = [super init];
    toggle = [[OAToggle alloc] init];
    return self;
}

- (void)dealloc {    
    zero_release(toggle);
    [super dealloc];
}

- (void)initToggle {    

    int count = [toggle count];
    for (uint i = 0; i < count; ++i) {
        NSString* name = @"";
        NSDictionary* data = nil;
        UIImage* imageRes = nil;
        
        name = [toggle name:i];
        data = [toggle load_unsafe:i];
        imageRes = [toggle logoImage:i];
        
        UIImageSwitch *imageSwitch = [[UIImageSwitch alloc] initWithFrame:CGRectMake(50, 50, 50, 50)];
        imageSwitch.image = imageRes;
        imageSwitch.value = 0;
        [imageSwitch storeSet:@"index" obj:::nnt::number(i)];
        [imageSwitch storeSet:@"name" obj:name];
        
        [imageSwitch connect:kSignalValueChanged sel:@selector(act_toggle:) obj:self];
        [imageSwitch connect:kSignalButtonCloseClicked sel:@selector(act_toggle_close:) obj:self];
        
        ::nnt::ns::Number enable([data valueForKey:@"enable"]);
        if (enable == YES) {
            imageSwitch.value = 1;
        }

        if (data) {
            [imageSwitch storeSet:@"token::data" obj:data];
            imageSwitch.showClose = YES;
        }
        
        [d_owner addSubview:imageSwitch];
        [imageSwitch release];
    }
}

- (void)act_toggle:(NNTEventObj*)evt {
    
    UIImageSwitch* imageSwitch = (UIImageSwitch*)evt.sender;
    [self toggle_begin:imageSwitch];
}

- (void)toggle_begin:(id)__id {
    
    UIImageSwitch* imageSwitch = (UIImageSwitch*)__id;
    ::nnt::ns::MutableDictionary data = ::nnt::ns::MutableDictionary([imageSwitch storeFind:@"token::data"]);
    uindex idx = [[imageSwitch storeFind:@"index"] unsignedIntValue];
    
    ::nnt::ns::Number enable(data[@"enable"]);
    
    if (enable == YES) {
        data[@"enable"] = NSNumberNo;
    } else {
        data[@"enable"] = NSNumberYes;
    }
    
    [toggle save:data idx:idx];
    
    if (0 == imageSwitch.value) {
        return;
    }
    
    if (data == nil) {
        imageSwitch.value = 0;
        [toggle authorize:idx];
        [toggle storeSet:@"imageSwitch" obj:imageSwitch];
        [toggle connect:@"kSignalToggleAuthorizeSuccess" sel:@selector(act_toggle_authorize_success:) obj:self];
        return;
    }
}

- (void)act_toggle_close:(NNTEventObj*)evt {
    
    UIImageSwitch *imageSwitch = (UIImageSwitch*)evt.sender;
    NSString *name = [imageSwitch storeFind:@"name"];
    NNTUIAlertView *alertView = [[NNTUIAlertView alloc] initWithTitle:_W(@"Logout") message:[_W(@"If Logout") stringByAppendingFormat:@"%@", _W(name)] cancelButtonTitle:_W(@"cancel") okButtonTitle:_W(@"ok")];
    [alertView storeSet:@"imageSwitch" obj:imageSwitch];
    [alertView connect:kSignalIndexYes sel:@selector(act_toggle_close_ok:) obj:self];
    [alertView show];
    [alertView release];
}

- (void)act_toggle_close_ok:(NNTEventObj*)evt {
    
    NNTUIAlertView *alertView = (NNTUIAlertView*)evt.sender;
    UIImageSwitch *imageSwitch = (UIImageSwitch*)[alertView storeFind:@"imageSwitch"];
    [toggle del:[[imageSwitch storeFind:@"index"] unsignedIntValue]]; 
    
    [imageSwitch storePop:@"token::data"];
    
    imageSwitch.showClose = NO;
    imageSwitch.value = 1;
    [self toggle_begin:imageSwitch];
    [imageSwitch setNeedsDisplay];
}

- (void)act_toggle_authorize_success:(NNTEventObj*)evt {
    
    UIImageSwitch *imageSwitch = [(id)evt.sender storeFind:@"imageSwitch"];
    imageSwitch.value = 1;
    imageSwitch.showClose = YES;
    NSDictionary *data = [toggle load_unsafe:[[imageSwitch storeFind:@"index"] unsignedIntValue]];
    [imageSwitch storeSet:@"token::data" obj:data];
    [imageSwitch setNeedsDisplay];
}

@end

@implementation UIOAToggleView

@dynamic delegate;

- (id)initWithFrame:(CGRect)frame {    
    self = [super initWithFrame:frame];
    NNTDECL_PRIVATE_INIT(UIOAToggleView);
    return self;
}

- (void)dealloc {
    NNTDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

- (void)setDelegate:(id<OAToggleDelegate>)__delegate {
    d_ptr.toggle.delegate = __delegate;
}

- (id<OAToggleDelegate>)delegate {
    return d_ptr.toggle.delegate;
}

- (void)refresh {
    [d_ptr initToggle];
}

NNT_END_OBJC

@end