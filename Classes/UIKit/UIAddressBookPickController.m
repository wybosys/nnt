
# import "Core.h"
# import "UIAddressBookPickController.h"
# import "NNTContact.h"

NNT_BEGIN_OBJC

@implementation UIAddressBookPickController

NNTOBJECT_IMPL_NOSIGNALS;

@synthesize presentOfController;
@synthesize popover;
@synthesize referenceView, referenceSuperView;

- (id)init {
    self = [super init];
    self.peoplePickerDelegate = self;
    self.popover = YES;
    return self;
}

- (id)initWithParentController {
    UIViewController* ctlr = [NNTApplication shared].window.rootViewController;
    //UIViewController* ctlr = [UIApplication sharedApplication].keyWindow.rootViewController;
    return [self initWithParentController:ctlr];
}

- (id)initWithParentController:(UIViewController*)ctlr {
    self = [super init];
    presentOfController = ctlr;
    self.peoplePickerDelegate = self;
    self.popover = YES;
    return self;
}

- (void)dealloc {
    NNTOBJECT_DEALLOC;
    [super dealloc];
}

- (void)initSignals {
    NNTEVENT_SIGNAL(kSignalSelectChanged);
}

- (void)present {
    if (self.popover) {
        [presentOfController presentModalViewController:self animated:YES];
    } else {
        if (referenceView == nil) 
            dthrow_msg(@"NULL", @"the referenceView is nil");        
        
        [self retain];
        
        if (referenceSuperView == nil) 
            referenceSuperView = referenceView.superview;
        
        CGRect rc = referenceView.frame;
        CGPoint pt = CGRectLeftBottom(&rc);
        CGRect rc_par = referenceSuperView.bounds;
        rc.origin = pt;
        rc.size.height = rc_par.size.height - rc.size.height - rc.origin.y;
        
        if (referenceSuperView != referenceView.superview) {
            rc = [referenceView.superview convertRect:rc toView:referenceSuperView];
        }
        
        self.view.frame = rc;
        
        [referenceSuperView addSubview:self.view];
    }
}

- (void)close {
    if (self.popover) {
        [presentOfController dismissModalViewControllerAnimated:YES];
    } else {
        [self.view removeFromSuperview];
        [self release];
    }
}

# pragma mark delegate.

- (void)peoplePickerNavigationControllerDidCancel:(ABPeoplePickerNavigationController *)peoplePicker{
    [self close];
}

- (BOOL)peoplePickerNavigationController:(ABPeoplePickerNavigationController *)peoplePicker shouldContinueAfterSelectingPerson:(ABRecordRef)person {
    return YES;
}

- (BOOL)peoplePickerNavigationController:(ABPeoplePickerNavigationController *)peoplePicker shouldContinueAfterSelectingPerson:(ABRecordRef)person property:(ABPropertyID)property identifier:(ABMultiValueIdentifier)identifier {
    NNTPerson* objperson = [[NNTPerson alloc] initWithRecord:person];
    
    ABMultiValueRef phoneProperty = ABRecordCopyValue(person, property);
    int idx = ABMultiValueGetIndexForIdentifier(phoneProperty, identifier);
    CFTypeRef ref_phone = (NSString *)ABMultiValueCopyValueAtIndex(phoneProperty,idx);

    // emit event.
    [self emit:kSignalSelectChanged result:pair((NSString*)ref_phone, objperson)];
    
    // free
    CFRelease(phoneProperty);
    CFRelease(ref_phone);
    [objperson release];
    
    [self close];
    return NO ;
}

@end

NNT_END_OBJC