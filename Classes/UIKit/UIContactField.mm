
# import "Core.h"
# import "UIContactField.h"
# import "NNTAddressBookStore.h"
# import "UIKit.res"
# import "UIAddressBookPickController.h"

NNT_BEGIN_OBJC

# define CELL_HEIGHT 50

@interface UIContactLiveTableCell : NNTUITableViewCell

@property (nonatomic, retain) NNTUILabel *labelName;
@property (nonatomic, retain) NNTUILabel *labelPhone;

+ (UIContactLiveTableCell*)cell;

@end

@implementation UIContactLiveTableCell

@synthesize labelName, labelPhone;

- (void)dealloc {
    zero_release(labelName);
    zero_release(labelPhone);
    [super dealloc];
}

+ (UIContactLiveTableCell *)cell {    
    UIContactLiveTableCell *ret = [[UIContactLiveTableCell alloc] initWithZero];
    
    NNTUILabel *labelPhone = [[NNTUILabel alloc] initWithZero];
    NNTUILabel *labelName = [[NNTUILabel alloc] initWithZero];
    
    labelName.textColor = [UIColor blueColor];
    labelName.font = [UIFont boldSystemFontOfSize:14];
    
    ret.labelName = labelName;
    ret.labelPhone = labelPhone;
    
    [ret.contentView addSubview:labelName];
    [ret.contentView addSubview:labelPhone];
    
    [labelName release];
    [labelPhone release];
    
    return [ret autorelease];
    
}

- (void)updateLayout:(CGRect)rect {
    ::nnt::CGRectLayoutVBox lyt(CGRectDeflateCenter(rect, 5, 5));
    ::nnt::CGRectLayoutLinear lnr(lyt);
    lnr << (::nnt::flex)1 << (::nnt::flex)1;
    
    labelName.frame = lyt.add_pixel(lnr.start());
    labelPhone.frame = lyt.add_pixel(lnr.next());
}

@end

@interface UIContactFieldPrivate : NSObject <UITableViewDataSource, UITableViewDelegate> {
    NNTAddressBookStore* addressBook;
    NSArray *store_all, *store_phones, *store_names;
}

@property (nonatomic, assign) UIContactField* d_owner;
@property (nonatomic, readonly, assign) NNTAddressBookStore* addressBook;
@property (nonatomic, retain) NSArray *store_all, *store_phones, *store_names;

- (CGRect)rectForLiveTable:(uint)cnt;
- (void)setPhone:(NSString*)phone;
- (void)showLive;
- (void)hideLive;

@end

@interface UIContactField ()

@property (nonatomic, retain) NNTUITableView* tableLiveMatching;

@end

@implementation UIContactFieldPrivate

@synthesize d_owner;
@synthesize addressBook;
@synthesize store_all, store_phones, store_names;

- (id)init {
    self = [super init];
    
    // addressbook.
    addressBook = [NNTAddressBookStore getInstance];
    
    // other.
    d_owner.pickerPopover = YES;

    // ui.
    [d_owner connect:kSignalValueChanged sel:@selector(act_value_changed:) obj:self];
    [d_owner connect:kSignalEndEditing sel:@selector(hideLive) obj:self];
    
    // add button.
    NNTUIImageView* contact = [[NNTUIImageView alloc] initWithData:[NSData dataWithBytesNoCopy:(void*)png_address_add length:sizeof(png_address_add) freeWhenDone:NO]];
    contact.userInteractionEnabled = YES;
    [contact connect:kSignalButtonClicked sel:@selector(act_picker_clicked:) obj:self];
    d_owner.buttonPicker = contact;
    [d_owner addSubview:contact];
    [contact release];
    
    // add listtable.
    NNTUITableView *listTable = [[NNTUITableView alloc] initWithFrame:CGRectZero style:UITableViewStylePlain];
    listTable.dataSource = self;
    listTable.delegate = self;
    listTable.layer.borderWidth = 1;
    listTable.hidden = YES;
    listTable.bounces = NO;
    d_owner.tableLiveMatching = listTable;
    [listTable release];
    
    return self;
}

- (void)dealloc {
    [store_all release];
    [store_names release];
    [store_phones release];
    [super dealloc];
}

- (void)setStore_all:(NSArray *)all {
    [NSObject refobjSet:&store_all ref:all];
    
    // refresh
    ::nnt::ns::MutableArray phones(all.count);
    ::nnt::ns::MutableArray names(all.count);
    
    for (NSDictionary* each in all) {
        NSArray* data_phones = (NSArray*)[each objectForKey:@"phones"];
        if (data_phones.count) {
            NSString* fullname = [each objectForKey:@"fullname"];
            for (NSString* each in data_phones) {
                names << fullname;
                phones << each;
            }
        } else {
            names << [each objectForKey:@"fullname"];
            phones << @"";
        }
    }
    
    self.store_names = names;
    self.store_phones = phones;
}

- (CGRect)rectForLiveTable:(uint)cnt {
    CGRect rc_txt = d_owner.frame;
    CGPoint rc_pt = CGRectLeftBottom(&rc_txt);
    CGRect ret = rc_txt;
    ret.size.height = MIN(5, cnt) * CELL_HEIGHT;
    ret.origin = rc_pt;
    return ret;
}

- (void)setPhone:(NSString *)phone {
    phone = [phone stringByReplacingOccurrencesOfString:@"-" withString:@""];
    d_owner.text = phone;
}

# pragma mark actions.

- (void)act_value_changed:(NNTEventObj*)evt {
    NSString *text = (NSString *)evt.result;
    if ([text notEmpty]) {
        self.store_all = [addressBook search:text];
    } else {
        self.store_all = nil;
    }
    
    if (self.store_all.count) {
        d_owner.tableLiveMatching.frame = [self rectForLiveTable:self.store_all.count];
        [self showLive];
        [d_owner.tableLiveMatching reloadData];
        [d_owner.tableLiveMatching flashScrollIndicators];
    } else {
        [self hideLive];
    }
}

- (void)showLive {
    BOOL pass = d_owner.tableLiveMatching.hidden;
    if (pass) {
        [d_owner.superview addSubview:d_owner.tableLiveMatching];
        d_owner.tableLiveMatching.hidden = NO;
        [d_owner bringSubviewToFront:d_owner.tableLiveMatching];
    }
}

- (void)hideLive {
    BOOL pass = !d_owner.tableLiveMatching.hidden;
    if (pass) {
        d_owner.tableLiveMatching.hidden = YES;
        [d_owner.tableLiveMatching removeFromSuperview];
    }
}

- (void)act_picker_clicked:(NNTEventObj*)evt {
    [self hideLive];
    UIAddressBookPickController* ctlr = [[UIAddressBookPickController alloc] initWithParentController];
    [ctlr connect:kSignalSelectChanged sel:@selector(act_picker_changed:) obj:self];
    
    if (d_owner.pickerPopover == NO) {
        ctlr.popover = NO;
        ctlr.referenceView = d_owner;
        
        if ([[d_owner superview] isKindOfClass:[UIAlertView class]]) {
            ctlr.referenceSuperView = d_owner.superview.superview;
        }
    }
    
    [ctlr present];
    [ctlr release];
}

- (void)act_picker_changed:(NNTEventObj*)evt {
    NSString* phone = (NSString*)((NSPair*)evt.result).first;
    [d_owner enable_signal:kSignalValueChanged val:NO];
    [self setPhone:phone];
    [d_owner enable_signal:kSignalValueChanged val:YES];
}

# pragma mark delegate.

- (NSInteger)tableView:(NNTUITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [self.store_names count];
}

- (UITableViewCell *)tableView:(NNTUITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UIContactLiveTableCell *cell = [UIContactLiveTableCell cell];
    cell.labelPhone.text = [self.store_phones objectAtIndex:indexPath.row];
    cell.labelName.text = [self.store_names objectAtIndex:indexPath.row];
    return cell;
}

- (void)tableView:(NNTUITableView *)tableView willDisplayCell:(UIContactLiveTableCell *)__cell forRowAtIndexPath:(NSIndexPath *)indexPath {
    [__cell updateLayout:__cell.bounds];
}


- (CGFloat)tableView:(NNTUITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return CELL_HEIGHT;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    NSString* phone = [self.store_phones objectAtIndex:indexPath.row];
    [self setPhone:phone];
    tableView.hidden = YES;
    [tableView removeFromSuperview];
}

@end

@implementation UIContactField

@synthesize buttonPicker;
@synthesize tableLiveMatching;
@synthesize pickerPopover;

- (id)init {
    self = [super init];
    NNTDECL_PRIVATE_INIT_EX(UIContactField, d_ptr_contact);
    return self;
}

- (id)initWithCoder:(NSCoder *)aDecoder {
    self = [super initWithCoder:aDecoder];
    NNTDECL_PRIVATE_INIT_EX(UIContactField, d_ptr_contact);
    return self;
}

- (id)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    NNTDECL_PRIVATE_INIT_EX(UIContactField, d_ptr_contact);
    return self;
}

- (void)dealloc {
    [buttonPicker release];
    [tableLiveMatching release];
    NNTDECL_PRIVATE_DEALLOC_EX(d_ptr_contact);
    [super dealloc];
}

- (void)layoutSubviews {
    [super layoutSubviews];
    
    ::nnt::CGRectLayoutHBox lyt(self.bounds);
    ::nnt::CGRectLayoutLinear lnr(lyt);
    lnr << (::nnt::flex)1 << (::nnt::pixel)self.bounds.size.height;
    
    lyt.add_pixel(lnr.start());
    ((UIView*)buttonPicker).frame = lyt.add_pixel(lnr.next());
}

@end

NNT_END_OBJC