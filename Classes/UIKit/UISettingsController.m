
# import "Core.h"
# import <MessageUI/MessageUI.h>
# import "UISettingsController.h"
# import "UISettingsSpecifier.h"
# import "UISettingsReader.h"
# import "UISettingsStore.h"
# import "UISettingsStoreUserDefaults.h"
# import "UISettingsSpecifierValuesController.h"
# import "UISettingsItems.h"
# import "UITableView+WSI.h"
# import "CoreGraphic+WSI.h"

WSI_BEGIN_OBJC

static const CGFloat KEYBOARD_ANIMATION_DURATION = 0.3;
static const CGFloat MINIMUM_SCROLL_FRACTION = 0.2;
static const CGFloat MAXIMUM_SCROLL_FRACTION = 0.8;

static NSString *kIASKCredits = @"Powered by InAppSettingsKit";

# define kUISettingsSpecifierValuesControllerIndex       0
# define kUISettingsSpecifierChildViewControllerIndex        1

# define kIASKCreditsViewWidth                         285

@interface UISettingsControllerPrivate : NSObject <MFMailComposeViewControllerDelegate> {
    UISettingsController *d_owner;
}

@property (nonatomic, assign) UISettingsController *d_owner;

@end

@implementation UISettingsControllerPrivate

@synthesize d_owner;

- (id)init {
    self = [super init];
    return self;
}

- (void)dealloc {
    [super dealloc];
}

# pragma mark MFMailComposeViewControllerDelegate Function

-(void)mailComposeController:(MFMailComposeViewController*)controller didFinishWithResult:(MFMailComposeResult)result error:(NSError*)error {
    [d_owner dismissModalViewControllerAnimated:YES];
}

@end

@interface UISettingsController ()

- (void)_textChanged:(id)sender;
- (void)_keyboardWillShow:(NSNotification*)notification;
- (void)_keyboardWillHide:(NSNotification*)notification;
- (void)synchronizeSettings;
- (void)reload;

@end

@implementation UISettingsController

@synthesize delegate = _delegate;
@synthesize tableView = _tableView;
@synthesize currentIndexPath=_currentIndexPath;
@synthesize settingsReader = _settingsReader;
@synthesize file = _file;
@synthesize currentFirstResponder = _currentFirstResponder;
@synthesize showCreditsFooter = _showCreditsFooter;
@synthesize showDoneButton = _showDoneButton;
@synthesize settingsStore = _settingsStore;
@synthesize targetController = _targetController;

- (id)init {
    self = [super init];
    WSIDECL_PRIVATE_INIT(UISettingsController);   
    
    _targetController = self;
    
    return self;
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    
    zero_release(_viewList);
    zero_release(_currentIndexPath);
    zero_release(_file);
    zero_release(_currentFirstResponder);
    zero_release(_settingsReader);
    zero_release(_settingsStore);
    zero_release(_tableView);
    zero_release(_targetController);
	
	_delegate = nil;
    
    WSIDECL_PRIVATE_DEALLOC();
    [super dealloc];
}

#pragma mark accessors

- (UISettingsReader*)settingsReader {
	if (!_settingsReader) {
		_settingsReader = [[UISettingsReader alloc] initWithFile:self.file];
	}
	return _settingsReader;
}

- (id<UISettingsStore>)settingsStore {
	if (!_settingsStore) {
		_settingsStore = [[UISettingsStoreUserDefaults alloc] init];
	}
	return _settingsStore;
}

- (NSString*)file {
	if (!_file) {
		return @"Root";
	}
	return [[_file retain] autorelease];
}

- (void)setFile:(NSString *)file {
	if (file != _file) {
		[_file release];
		_file = [file copy];
	}
	
	self.settingsReader = nil; // automatically initializes itself
}

#pragma mark standard view controller methods

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        // If set to YES, will display credits for InAppSettingsKit creators
        _showCreditsFooter = YES;
        
        // If set to YES, will add a DONE button at the right of the navigation bar
        _showDoneButton = YES;
    }
    return self;
}

- (void)awakeFromNib {
	// If set to YES, will display credits for InAppSettingsKit creators
	_showCreditsFooter = YES;
	
	// If set to YES, will add a DONE button at the right of the navigation bar
	// if loaded via NIB, it's likely we sit in a TabBar- or NavigationController
	// and thus don't need the Done button
	_showDoneButton = NO;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // Add views
    _viewList = [[NSMutableArray alloc] init];
    [_viewList addObject:[NSDictionary dictionaryWithObjectsAndKeys:@"UISettingsSpecifierValuesView", @"ViewName",nil]];
    [_viewList addObject:[NSDictionary dictionaryWithObjectsAndKeys:@"IASKAppSettingsView", @"ViewName",nil]];
    
    // add table view.
    if (_tableView == nil) {
        _tableView = [[WSIUITableView alloc] initWithFrame:CGRectZero style:UITableViewStyleGrouped];
        _tableView.delegate = self;
        _tableView.dataSource = self;
        [self.view addSubview:_tableView];
    }
}

- (void)viewDidUnload {
	// Release any retained subviews of the main view.
	// e.g. self.myOutlet = nil;
	self.tableView = nil;
	[_viewList release], _viewList = nil;
}

- (void)viewWillAppear:(BOOL)animated {
    [self prepareAppear:animated];	
	[super viewWillAppear:animated];
}

- (CGSize)contentSizeForViewInPopover {
    return [[self view] sizeThatFits:CGSizeMake(320, 2000)];
}

- (void)viewDidAppear:(BOOL)animated {	
    [self afterAppear:animated];
	[super viewDidAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated {
	[self prepareDisappear:animated];
	[super viewWillDisappear:animated];
}

- (void)viewDidDisappear:(BOOL)animated {
	[self afterDisappear:animated];
	[super viewDidDisappear:animated];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return YES;
}

- (void)didReceiveMemoryWarning {
	// Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
	
	// Release any cached data, images, etc that aren't in use.
}

- (void)navigationController:(UINavigationController *)navigationController willShowViewController:(UIViewController *)viewController animated:(BOOL)animated {
	if (![viewController isKindOfClass:[UISettingsController class]] && ![viewController isKindOfClass:[UISettingsSpecifierValuesController class]]) {
		[self dismiss:nil];
	}
}

#pragma mark -
#pragma mark Actions

- (IBAction)dismiss:(id)sender {
	if ([self.currentFirstResponder canResignFirstResponder]) {
		[self.currentFirstResponder resignFirstResponder];
	}
	
	[self.settingsStore synchronize];
	self.navigationController.delegate = nil;
	
	if (self.delegate && [self.delegate conformsToProtocol:@protocol(UISettingsDelegate)]) {
		[self.delegate settingsControllerDidEnd:self];
	}
}

- (void)toggledValue:(id)sender {
    UISettingsSwitch *toggle    = (UISettingsSwitch*)sender;
    UISettingsSpecifier *spec   = [_settingsReader specifierForKey:[toggle key]];
    
    if ([toggle isOn]) {
        if ([spec trueValue] != nil) {
            [self.settingsStore setObject:[spec trueValue] forKey:[toggle key]];
        }
        else {
            [self.settingsStore setBool:YES forKey:[toggle key]]; 
        }
    }
    else {
        if ([spec falseValue] != nil) {
            [self.settingsStore setObject:[spec falseValue] forKey:[toggle key]];
        }
        else {
            [self.settingsStore setBool:NO forKey:[toggle key]]; 
        }
    }
    [[NSNotificationCenter defaultCenter] postNotificationName:kIASKAppSettingChanged
                                                        object:[toggle key]
                                                      userInfo:[NSDictionary dictionaryWithObject:[self.settingsStore objectForKey:[toggle key]]
                                                                                           forKey:[toggle key]]];
}

- (void)sliderChangedValue:(id)sender {
    UISettingsSlider *slider = (UISettingsSlider*)sender;
    [self.settingsStore setFloat:[slider value] forKey:[slider key]];
    [[NSNotificationCenter defaultCenter] postNotificationName:kIASKAppSettingChanged
                                                        object:[slider key]
                                                      userInfo:[NSDictionary dictionaryWithObject:[NSNumber numberWithFloat:[slider value]]
                                                                                           forKey:[slider key]]];
}


#pragma mark -
#pragma mark UITableView Functions

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
	return [self.settingsReader numberOfSections];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [self.settingsReader numberOfRowsForSection:section];
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    UISettingsSpecifier *specifier  = [self.settingsReader specifierForIndexPath:indexPath];
    if ([[specifier type] isEqualToString:kIASKCustomViewSpecifier]) {
		if ([self.delegate respondsToSelector:@selector(tableView:heightForSpecifier:)]) {
			return [self.delegate tableView:_tableView heightForSpecifier:specifier];
		} else {
			return 0;
		}
	}
	return tableView.rowHeight;
}

- (NSString *)tableView:(UITableView*)tableView titleForHeaderInSection:(NSInteger)section {
    NSString *header = [self.settingsReader titleForSection:section];
	if (0 == header.length) {
		return nil;
	}
	return header;
}

- (UIView *)tableView:(UITableView*)tableView viewForHeaderInSection:(NSInteger)section {
	NSString *key  = [self.settingsReader keyForSection:section];
	if ([self.delegate respondsToSelector:@selector(tableView:viewForHeaderForKey:)]) {
		return [self.delegate tableView:_tableView viewForHeaderForKey:key];
	} else {
		return nil;
	}
}

- (CGFloat)tableView:(UITableView*)tableView heightForHeaderInSection:(NSInteger)section {
	NSString *key  = [self.settingsReader keyForSection:section];
	if ([self tableView:tableView viewForHeaderInSection:section] && [self.delegate respondsToSelector:@selector(tableView:heightForHeaderForKey:)]) {
		CGFloat result;
		if ((result = [self.delegate tableView:tableView heightForHeaderForKey:key])) {
			return result;
		}
		
	}
	NSString *title;
	if ((title = [self tableView:tableView titleForHeaderInSection:section])) {
		CGSize size = [title sizeWithFont:[UIFont boldSystemFontOfSize:[UIFont labelFontSize]] 
						constrainedToSize:CGSizeMake(tableView.frame.size.width - 2*kIASKHorizontalPaddingGroupTitles, INFINITY)
							lineBreakMode:UILineBreakModeWordWrap];
		return size.height+kIASKVerticalPaddingGroupTitles;
	}
	return 0;
}

- (NSString *)tableView:(UITableView *)tableView titleForFooterInSection:(NSInteger)section
{
	NSString *footerText = [self.settingsReader footerTextForSection:section];
	if (_showCreditsFooter && (section == [self.settingsReader numberOfSections]-1)) {
		// show credits since this is the last section
		if ((footerText == nil) || ([footerText length] == 0)) {
			// show the credits on their own
			return kIASKCredits;
		} else {
			// show the credits below the app's FooterText
			return [NSString stringWithFormat:@"%@\n\n%@", footerText, kIASKCredits];
		}
	} else {
		if ([footerText length] == 0) {
			return nil;
		}
		return [self.settingsReader footerTextForSection:section];
	}
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UISettingsSpecifier *specifier  = [self.settingsReader specifierForIndexPath:indexPath];
    NSString *key           = [specifier key];
    
    if ([[specifier type] isEqualToString:kIASKPSToggleSwitchSpecifier]) {
        UIToggleTableCell *cell = (UIToggleTableCell*)[tableView dequeueReusableCellWithIdentifier:[specifier type]];
        
        if (!cell) {
            /*
             cell = (UISettingsToggleSwitchSpecifierViewCell*) [[[NSBundle mainBundle] loadNibNamed:@"UISettingsToggleSwitchSpecifierViewCell" 
             owner:self 
             options:nil] 
             objectAtIndex:0
             null:nil];
             */
            cell = [UIToggleTableCell cell];
        }
        [[cell label] setText:[specifier title]];
        
		id currentValue = [self.settingsStore objectForKey:key];
		BOOL toggleState;
		if (currentValue) {
			if ([currentValue isEqual:[specifier trueValue]]) {
				toggleState = YES;
			} else if ([currentValue isEqual:[specifier falseValue]]) {
				toggleState = NO;
			} else {
				toggleState = [currentValue boolValue];
			}
		} else {
			toggleState = [specifier defaultBoolValue];
		}
		[[cell toggle] setOn:toggleState];
		
        [[cell toggle] addTarget:self action:@selector(toggledValue:) forControlEvents:UIControlEventValueChanged];
        [[cell toggle] setKey:key];
        return cell;
    }
    else if ([[specifier type] isEqualToString:kIASKPSMultiValueSpecifier]) {
        UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:[specifier type]];
        
        if (!cell) {
            cell = [[[UITitleValueTableCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:[specifier type]] autorelease];
			cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
		}
        [[cell textLabel] setText:[specifier title]];
		[[cell detailTextLabel] setText:[[specifier titleForCurrentValue:[self.settingsStore objectForKey:key] != nil ? 
                                          [self.settingsStore objectForKey:key] : [specifier defaultValue]] description]];
        return cell;
    }
    else if ([[specifier type] isEqualToString:kIASKPSTitleValueSpecifier]) {
        UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:[specifier type]];
        
        if (!cell) {
            cell = [[[UITitleValueTableCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:[specifier type]] autorelease];
			cell.accessoryType = UITableViewCellAccessoryNone;
        }
		
		cell.textLabel.text = [specifier title];
		id value = [self.settingsStore objectForKey:key] ? : [specifier defaultValue];
		
		NSString *stringValue;
		if ([specifier multipleValues] || [specifier multipleTitles]) {
			stringValue = [specifier titleForCurrentValue:value];
		} else {
			stringValue = [value description];
		}
        
		cell.detailTextLabel.text = stringValue;
		[cell setUserInteractionEnabled:NO];
		
        return cell;
    }
    else if ([[specifier type] isEqualToString:kIASKPSTextFieldSpecifier]) {
        UITextFieldTableCell *cell = (UITextFieldTableCell*)[tableView dequeueReusableCellWithIdentifier:[specifier type]];
        
        if (!cell) {
            /*
            cell = (UISettingsTextFieldSpecifierViewCell*) [[[NSBundle mainBundle] loadNibNamed:@"UISettingsTextFieldSpecifierViewCell" 
                                                                                          owner:self 
                                                                                        options:nil] 
                                                            objectAtIndex:0
                                                            null:nil];
             */
            cell = [UITextFieldTableCell cell];
            
            //cell.textField.textAlignment = UITextAlignmentLeft;
            cell.textField.returnKeyType = UIReturnKeyDone;
            cell.accessoryType = UITableViewCellAccessoryNone;
        }
        
        [[cell label] setText:[specifier title]];      
        
        NSString *textValue = [self.settingsStore objectForKey:key] != nil ? [self.settingsStore objectForKey:key] : [specifier defaultStringValue];
        if (![textValue isMemberOfClass:[NSString class]]) {
            textValue = [NSString stringWithFormat:@"%@", textValue];
        }
        [[cell textField] setText:textValue];
        
        [[cell textField] setKey:key];
        [[cell textField] setDelegate:self];
        [[cell textField] addTarget:self action:@selector(_textChanged:) forControlEvents:UIControlEventEditingChanged];
        [[cell textField] setSecureTextEntry:[specifier isSecure]];
        [[cell textField] setKeyboardType:[specifier keyboardType]];
        [[cell textField] setAutocapitalizationType:[specifier autocapitalizationType]];
        if([specifier isSecure]){
            [[cell textField] setAutocorrectionType:UITextAutocorrectionTypeNo];
        } else {
            [[cell textField] setAutocorrectionType:[specifier autoCorrectionType]];
        }
        [cell setNeedsLayout];
        return cell;
    }
	else if ([[specifier type] isEqualToString:kIASKPSSliderSpecifier]) {
        UISliderTableCell *cell = (UISliderTableCell*)[tableView dequeueReusableCellWithIdentifier:[specifier type]];
        
        if (!cell) {
            cell = (UISliderTableCell*) [[[NSBundle mainBundle] loadNibNamed:@"UISliderTableCell" 
                                                                                   owner:self 
                                                                                 options:nil]
                                         objectAtIndex:0];
		}
        
        if ([[specifier minimumValueImage] length] > 0) {
            [[cell minImage] setImage:[UIImage imageWithContentsOfFile:[_settingsReader pathForImageNamed:[specifier minimumValueImage]]]];
        }
		
        if ([[specifier maximumValueImage] length] > 0) {
            [[cell maxImage] setImage:[UIImage imageWithContentsOfFile:[_settingsReader pathForImageNamed:[specifier maximumValueImage]]]];
        }
        
        [[cell slider] setMinimumValue:[specifier minimumValue]];
        [[cell slider] setMaximumValue:[specifier maximumValue]];
        [[cell slider] setValue:[self.settingsStore objectForKey:key] != nil ? 
		 [[self.settingsStore objectForKey:key] floatValue] : [[specifier defaultValue] floatValue]];
        [[cell slider] addTarget:self action:@selector(sliderChangedValue:) forControlEvents:UIControlEventValueChanged];
        [[cell slider] setKey:key];
		[cell setNeedsLayout];
        return cell;
    }
    else if ([[specifier type] isEqualToString:kIASKPSChildPaneSpecifier]) {
        UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:[specifier type]];
        
        if (!cell) {
            cell = [[[UITitleValueTableCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:[specifier type]] autorelease];
			[cell setAccessoryType:UITableViewCellAccessoryDisclosureIndicator];
        }
        
        [[cell textLabel] setText:[specifier title]];
        return cell;
    } else if ([[specifier type] isEqualToString:kIASKOpenURLSpecifier]) {
        UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:[specifier type]];
        
        if (!cell) {
            cell = [[[UITitleValueTableCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:[specifier type]] autorelease];
			[cell setAccessoryType:UITableViewCellAccessoryDisclosureIndicator];
        }
        
		cell.textLabel.text = [specifier title];
		cell.detailTextLabel.text = [[specifier defaultValue] description];
		return cell;        
    } else if ([[specifier type] isEqualToString:kIASKButtonSpecifier]) {
        UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:[specifier type]];
		
        if (!cell) {
            cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:[specifier type]] autorelease];
        }
        cell.textLabel.text = [specifier title];
        cell.textLabel.textAlignment = UITextAlignmentCenter;
        return cell;
    } else if ([[specifier type] isEqualToString:kIASKMailComposeSpecifier]) {
        UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:[specifier type]];
        
        if (!cell) {
            cell = [[[UITitleValueTableCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:[specifier type]] autorelease];
			[cell setAccessoryType:UITableViewCellAccessoryDisclosureIndicator];
        }
        
		cell.textLabel.text = [specifier title];
		cell.detailTextLabel.text = [[specifier defaultValue] description];
		return cell;
    } else if ([[specifier type] isEqualToString:kIASKCustomViewSpecifier] && [self.delegate respondsToSelector:@selector(tableView:cellForSpecifier:)]) {
		return [self.delegate tableView:_tableView cellForSpecifier:specifier];
		
	} else {
        UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:[specifier type]];
		
        if (!cell) {
            cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:[specifier type]] autorelease];
        }
        [[cell textLabel] setText:[specifier title]];
        return cell;
    }
}

- (NSIndexPath *)tableView:(UITableView *)tableView willSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	UISettingsSpecifier *specifier  = [self.settingsReader specifierForIndexPath:indexPath];
	
	if ([[specifier type] isEqualToString:kIASKPSToggleSwitchSpecifier]) {
		return nil;
	} else {
		return indexPath;
	}
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    UISettingsSpecifier *specifier  = [self.settingsReader specifierForIndexPath:indexPath];
    
    if ([[specifier type] isEqualToString:kIASKPSToggleSwitchSpecifier]) {
        [tableView deselectRowAtIndexPath:indexPath animated:NO];
    }
    else if ([[specifier type] isEqualToString:kIASKPSMultiValueSpecifier]) {
        UISettingsSpecifierValuesController *targetViewController = [[_viewList objectAtIndex:kUISettingsSpecifierValuesControllerIndex] objectForKey:@"viewController"];
		
        if (targetViewController == nil) {
            // the view controller has not been created yet, create it and set it to our viewList array
            // create a new dictionary with the new view controller
            NSMutableDictionary *newItemDict = [NSMutableDictionary dictionaryWithCapacity:3];
            [newItemDict addEntriesFromDictionary: [_viewList objectAtIndex:kUISettingsSpecifierValuesControllerIndex]];	// copy the title and explain strings
            
            targetViewController = [[UISettingsSpecifierValuesController alloc] initWithNibName:@"UISettingsSpecifierValuesView" bundle:nil];
            // add the new view controller to the dictionary and then to the 'viewList' array
            [newItemDict setObject:targetViewController forKey:@"viewController"];
            [_viewList replaceObjectAtIndex:kUISettingsSpecifierValuesControllerIndex withObject:newItemDict];
            [targetViewController release];
            
            // load the view controll back in to push it
            targetViewController = [[_viewList objectAtIndex:kUISettingsSpecifierValuesControllerIndex] objectForKey:@"viewController"];
        }
        self.currentIndexPath = indexPath;
        [targetViewController setCurrentSpecifier:specifier];
        targetViewController.settingsReader = self.settingsReader;
        targetViewController.settingsStore = self.settingsStore;
        [[self navigationController] pushViewController:targetViewController animated:YES];
    }
    else if ([[specifier type] isEqualToString:kIASKPSSliderSpecifier]) {
        [tableView deselectRowAtIndexPath:indexPath animated:NO];
    }
    else if ([[specifier type] isEqualToString:kIASKPSTextFieldSpecifier]) {
		UITextFieldTableCell *textFieldCell = (id)[tableView cellForRowAtIndexPath:indexPath];
		[textFieldCell.textField becomeFirstResponder];
    }
    else if ([[specifier type] isEqualToString:kIASKPSChildPaneSpecifier]) {
        
        
        Class vcClass = [specifier viewControllerClass];
        if (vcClass) {
            SEL initSelector = [specifier viewControllerSelector];
            if (!initSelector) {
                initSelector = @selector(init);
            }
            UIViewController * vc = [vcClass alloc];
            [vc performSelector:initSelector withObject:[specifier file] withObject:[specifier key]];
			if ([vc respondsToSelector:@selector(setDelegate:)]) {
				[vc performSelector:@selector(setDelegate:) withObject:self.delegate];
			}
			if ([vc respondsToSelector:@selector(setSettingsStore:)]) {
				[vc performSelector:@selector(setSettingsStore:) withObject:self.settingsStore];
			}
			self.navigationController.delegate = nil;
            [self.navigationController pushViewController:vc animated:YES];
            [vc release];
            return;
        }
        
        if (nil == [specifier file]) {
            [tableView deselectRowAtIndexPath:indexPath animated:YES];
            return;
        }        
        
        UISettingsController *targetViewController = [[_viewList objectAtIndex:kUISettingsSpecifierChildViewControllerIndex] objectForKey:@"viewController"];
		
        if (targetViewController == nil) {
            // the view controller has not been created yet, create it and set it to our viewList array
            // create a new dictionary with the new view controller
            NSMutableDictionary *newItemDict = [NSMutableDictionary dictionaryWithCapacity:3];
            [newItemDict addEntriesFromDictionary: [_viewList objectAtIndex:kUISettingsSpecifierChildViewControllerIndex]];	// copy the title and explain strings
            
            targetViewController = [[[self class] alloc] initWithNibName:@"IASKAppSettingsView" bundle:nil];
			targetViewController.showDoneButton = NO;
			targetViewController.settingsStore = self.settingsStore; 
			targetViewController.delegate = self.delegate;
            
            // add the new view controller to the dictionary and then to the 'viewList' array
            [newItemDict setObject:targetViewController forKey:@"viewController"];
            [_viewList replaceObjectAtIndex:kUISettingsSpecifierChildViewControllerIndex withObject:newItemDict];
            [targetViewController release];
            
            // load the view controll back in to push it
            targetViewController = [[_viewList objectAtIndex:kUISettingsSpecifierChildViewControllerIndex] objectForKey:@"viewController"];
        }
        self.currentIndexPath = indexPath;
		targetViewController.file = specifier.file;
		targetViewController.title = specifier.title;
        targetViewController.showCreditsFooter = NO;
        [[self navigationController] pushViewController:targetViewController animated:YES];
    } else if ([[specifier type] isEqualToString:kIASKOpenURLSpecifier]) {
        [tableView deselectRowAtIndexPath:indexPath animated:YES];
		[[UIApplication sharedApplication] openURL:[NSURL URLWithString:specifier.file]];    
    } else if ([[specifier type] isEqualToString:kIASKButtonSpecifier]) {
        [tableView deselectRowAtIndexPath:indexPath animated:YES];
		if ([self.delegate respondsToSelector:@selector(settingsViewController:buttonTappedForKey:)]) {
			[self.delegate settingsController:self buttonTappedForKey:[specifier key]];
		} else {
			// legacy code, provided for backward compatibility
			// the delegate mechanism above is much cleaner and doesn't leak
			Class buttonClass = [specifier buttonClass];
			SEL buttonAction = [specifier buttonAction];
			if ([buttonClass respondsToSelector:buttonAction]) {
				[buttonClass performSelector:buttonAction withObject:self withObject:[specifier key]];
				NSLog(@"InAppSettingsKit Warning: Using IASKButtonSpecifier without implementing the delegate method is deprecated");
			}
		}
    } else if ([[specifier type] isEqualToString:kIASKMailComposeSpecifier]) {
        [tableView deselectRowAtIndexPath:indexPath animated:YES];
        if ([MFMailComposeViewController canSendMail]) {
            MFMailComposeViewController *mailViewController = [[MFMailComposeViewController alloc] init];
            
            if ([specifier localizedObjectForKey:kIASKMailComposeSubject]) {
                [mailViewController setSubject:[specifier localizedObjectForKey:kIASKMailComposeSubject]];
            }
            if ([[specifier specifierDict] objectForKey:kIASKMailComposeToRecipents]) {
                [mailViewController setToRecipients:[[specifier specifierDict] objectForKey:kIASKMailComposeToRecipents]];
            }
            if ([[specifier specifierDict] objectForKey:kIASKMailComposeCcRecipents]) {
                [mailViewController setCcRecipients:[[specifier specifierDict] objectForKey:kIASKMailComposeCcRecipents]];
            }
            if ([[specifier specifierDict] objectForKey:kIASKMailComposeBccRecipents]) {
                [mailViewController setBccRecipients:[[specifier specifierDict] objectForKey:kIASKMailComposeBccRecipents]];
            }
            if ([specifier localizedObjectForKey:kIASKMailComposeBody]) {
                BOOL isHTML = NO;
                if ([[specifier specifierDict] objectForKey:kIASKMailComposeBodyIsHTML]) {
                    isHTML = [[[specifier specifierDict] objectForKey:kIASKMailComposeBodyIsHTML] boolValue];
                }
                
                if ([self.delegate respondsToSelector:@selector(mailComposeBody)]) {
                    [mailViewController setMessageBody:[self.delegate mailComposeBody] isHTML:isHTML];
                }
                else {
                    [mailViewController setMessageBody:[specifier localizedObjectForKey:kIASKMailComposeBody] isHTML:isHTML];
                }
            }
            
            UIViewController *vc = nil;
            
            if ([self.delegate respondsToSelector:@selector(viewControllerForMailComposeView)]) {
                vc = [self.delegate viewControllerForMailComposeView];
                if (vc) {
                    mailViewController.mailComposeDelegate = (UIViewController<MFMailComposeViewControllerDelegate>*)vc;
                }
            }
            
            if (vc == nil) {
                vc = self;
                mailViewController.mailComposeDelegate = d_ptr;
            }
            
            [vc presentModalViewController:mailViewController animated:YES];
            [mailViewController release];
        } else {
            UIAlertView *alert = [[UIAlertView alloc]
                                  initWithTitle:NSLocalizedString(@"Mail not configured", @"InAppSettingsKit")
                                  message:NSLocalizedString(@"This device is not configured for sending Email. Please configure the Mail settings in the Settings app.", @"InAppSettingsKit")
                                  delegate: nil
                                  cancelButtonTitle:NSLocalizedString(@"OK", @"InAppSettingsKit")
                                  otherButtonTitles:nil];
            [alert show];
            [alert release];
        }
        
	} else {
        [tableView deselectRowAtIndexPath:indexPath animated:NO];
    }
}

#pragma mark -
#pragma mark UITextFieldDelegate Functions

- (void)_textChanged:(id)sender {
    UISettingsTextField *text = (UISettingsTextField*)sender;
    [_settingsStore setObject:[text text] forKey:[text key]];
    [[NSNotificationCenter defaultCenter] postNotificationName:kIASKAppSettingChanged
                                                        object:[text key]
                                                      userInfo:[NSDictionary dictionaryWithObject:[text text]
                                                                                           forKey:[text key]]];
}

- (BOOL)textFieldShouldBeginEditing:(UITextField *)textField {
	//[textField setTextAlignment:UITextAlignmentLeft];
	self.currentFirstResponder = textField;
    return YES;
}

- (void)textFieldDidBeginEditing:(UITextField *)textField {
	self.currentFirstResponder = textField;
	if ([_tableView indexPathsForVisibleRows].count) {
		_topmostRowBeforeKeyboardWasShown = (NSIndexPath*)[[_tableView indexPathsForVisibleRows] objectAtIndex:0];
	} else {
		// this should never happen
		_topmostRowBeforeKeyboardWasShown = [NSIndexPath indexPathForRow:0 inSection:0];
		[textField resignFirstResponder];
	}
}

- (void)textFieldDidEndEditing:(UITextField *)textField {
	self.currentFirstResponder = nil;
    //[textField setTextAlignment:UITextAlignmentRight];
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField{
    [textField resignFirstResponder];
	return YES;
}

#pragma mark Keyboard Management
- (void)_keyboardWillShow:(NSNotification*)notification {
	if (self.navigationController.topViewController == _targetController) {
		NSDictionary* userInfo = [notification userInfo];
        
		// we don't use SDK constants here to be universally compatible with all SDKs ≥ 3.0
		NSValue* keyboardFrameValue = [userInfo objectForKey:@"UIKeyboardBoundsUserInfoKey"];
		if (!keyboardFrameValue) {
			keyboardFrameValue = [userInfo objectForKey:@"UIKeyboardFrameEndUserInfoKey"];
		}
		
		// Reduce the tableView height by the part of the keyboard that actually covers the tableView
		CGRect windowRect = [[UIApplication sharedApplication] keyWindow].bounds;
		if (UIInterfaceOrientationLandscapeLeft == self.interfaceOrientation ||UIInterfaceOrientationLandscapeRight == self.interfaceOrientation ) {
			windowRect = CGRectSwap(&windowRect);
		}
		CGRect viewRectAbsolute = [_tableView convertRect:_tableView.bounds toView:[[UIApplication sharedApplication] keyWindow]];
		if (UIInterfaceOrientationLandscapeLeft == self.interfaceOrientation ||UIInterfaceOrientationLandscapeRight == self.interfaceOrientation ) {
			viewRectAbsolute = CGRectSwap(&viewRectAbsolute);
		}
		CGRect frame = _tableView.frame;
		frame.size.height -= [keyboardFrameValue CGRectValue].size.height - CGRectGetMaxY(windowRect) + CGRectGetMaxY(viewRectAbsolute);
        
		[UIView beginAnimations:nil context:NULL];
		[UIView setAnimationDuration:[[userInfo objectForKey:UIKeyboardAnimationDurationUserInfoKey] doubleValue]];
		[UIView setAnimationCurve:[[userInfo objectForKey:UIKeyboardAnimationCurveUserInfoKey] intValue]];
		_tableView.frame = frame;
		[UIView commitAnimations];
		
		UITableViewCell *textFieldCell = (id)((UITextField *)self.currentFirstResponder).superview.superview;
		NSIndexPath *textFieldIndexPath = [_tableView indexPathForCell:textFieldCell];
        
		// iOS 3 sends hide and show notifications right after each other
		// when switching between textFields, so cancel -scrollToOldPosition requests
		[NSObject cancelPreviousPerformRequestsWithTarget:self];
		
		[_tableView scrollToRowAtIndexPath:textFieldIndexPath atScrollPosition:UITableViewScrollPositionMiddle animated:YES];
	}
}


- (void) scrollToOldPosition {
    [_tableView scrollToRowAtIndexPath:_topmostRowBeforeKeyboardWasShown atScrollPosition:UITableViewScrollPositionTop animated:YES];
}

- (void)_keyboardWillHide:(NSNotification*)notification {
	if (self.navigationController.topViewController == _targetController) {
		NSDictionary* userInfo = [notification userInfo];
		
		[UIView beginAnimations:nil context:NULL];
		[UIView setAnimationDuration:[[userInfo objectForKey:UIKeyboardAnimationDurationUserInfoKey] doubleValue]];
		[UIView setAnimationCurve:[[userInfo objectForKey:UIKeyboardAnimationCurveUserInfoKey] intValue]];
		_tableView.frame = self.view.bounds;
		[UIView commitAnimations];
		
		[self performSelector:@selector(scrollToOldPosition) withObject:nil afterDelay:0.1];
	}
}	

#pragma mark Notifications

- (void)synchronizeSettings {
    [_settingsStore synchronize];
}

- (void)reload {
	// wait 0.5 sec until UI is available after applicationWillEnterForeground
	[_tableView performSelector:@selector(reloadData) withObject:nil afterDelay:0.5];
}

@end

@implementation UISettingsController (direct)

- (void)prepareAppear:(BOOL)animated {
    if (_tableView) {
        [_tableView reloadData];
		_tableView.frame = self.view.bounds;
    }
	
	self.navigationItem.rightBarButtonItem = nil;
    self.navigationController.delegate = self;
    if (_showDoneButton) {
        UIBarButtonItem *buttonItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone 
                                                                                    target:self 
                                                                                    action:@selector(dismiss:)];
        self.navigationItem.rightBarButtonItem = buttonItem;
        [buttonItem release];
    } 
    if (!self.title) {
        self.title = NSLocalizedString(@"Settings", @"");
    }
	
	if (self.currentIndexPath) {
		if (animated) {
			// animate deselection of previously selected row
			[_tableView selectRowAtIndexPath:self.currentIndexPath animated:NO scrollPosition:UITableViewScrollPositionNone];
			[_tableView deselectRowAtIndexPath:self.currentIndexPath animated:YES];
		}
		self.currentIndexPath = nil;
	}   
}

- (void)afterAppear:(BOOL)animated {
    [_tableView flashScrollIndicators];
	NSNotificationCenter *dc = [NSNotificationCenter defaultCenter];
	IASK_IF_IOS4_OR_GREATER([dc addObserver:self selector:@selector(synchronizeSettings) name:UIApplicationDidEnterBackgroundNotification object:[UIApplication sharedApplication]];);
	IASK_IF_IOS4_OR_GREATER([dc addObserver:self selector:@selector(reload) name:UIApplicationWillEnterForegroundNotification object:[UIApplication sharedApplication]];);
	[dc addObserver:self selector:@selector(synchronizeSettings) name:UIApplicationWillTerminateNotification object:[UIApplication sharedApplication]];
    
	[dc addObserver:self
           selector:@selector(_keyboardWillShow:)
               name:UIKeyboardWillShowNotification
             object:nil];
	[dc addObserver:self
           selector:@selector(_keyboardWillHide:)
               name:UIKeyboardWillHideNotification
             object:nil];	
}

- (void)prepareDisappear:(BOOL)animated {
    [[NSNotificationCenter defaultCenter] removeObserver:self name:UIKeyboardWillShowNotification object:nil];
	if ([self.currentFirstResponder canResignFirstResponder]) {
		[self.currentFirstResponder resignFirstResponder];
	}
	[NSObject cancelPreviousPerformRequestsWithTarget:self];
}

- (void)afterDisappear:(BOOL)animated {
    NSNotificationCenter *dc = [NSNotificationCenter defaultCenter];
	IASK_IF_IOS4_OR_GREATER([dc removeObserver:self name:UIApplicationDidEnterBackgroundNotification object:nil];);
	IASK_IF_IOS4_OR_GREATER([dc removeObserver:self name:UIApplicationWillEnterForegroundNotification object:nil];);
	[dc removeObserver:self name:UIApplicationWillTerminateNotification object:nil];
	[dc removeObserver:self name:UIKeyboardWillHideNotification object:nil];
}

@end

WSI_END_OBJC