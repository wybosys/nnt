
# ifndef __WSI_UIKIT_UISETTINGSCONTROLLER_AF9A951DADDA4942923F7418F482DB80_H_INCLUDED
# define __WSI_UIKIT_UISETTINGSCONTROLLER_AF9A951DADDA4942923F7418F482DB80_H_INCLUDED

# import "UIViewController+WSI.h"

WSI_BEGIN_HEADER_OBJC

WSIDECL_PRIVATE_HEAD(UISettingsController);
WSIDECL_EXTERN_CLASS(UISettingsSpecifier);
WSIDECL_EXTERN_CLASS(UISettingsReader);
WSIDECL_EXTERN_CLASS(UISettingsStore);
WSIDECL_EXTERN_PROTOCOL(UISettingsStore);
WSIDECL_EXTERN_PROTOCOL(MFMailComposeViewControllerDelegate);

@protocol UISettingsDelegate <NSObject>

//! settings controller is mit end.
- (void)settingsControllerDidEnd:(UISettingsController*)sender;

@optional

//! table view delegate redirect.
- (CGFloat)tableView:(UITableView *)tableView heightForHeaderForKey:(NSString*)key;
- (UIView *)tableView:(UITableView *)tableView viewForHeaderForKey:(NSString*)key;

//! table view delegate redirect.
- (CGFloat)tableView:(UITableView*)tableView heightForSpecifier:(UISettingsSpecifier*)specifier;
- (UITableViewCell*)tableView:(UITableView*)tableView cellForSpecifier:(UISettingsSpecifier*)specifier;

//! mail compose delegate.
- (NSString*)mailComposeBody;
- (UIViewController<MFMailComposeViewControllerDelegate>*)viewControllerForMailComposeView;

//! button tap event.
- (void)settingsController:(UISettingsController*)sender buttonTappedForKey:(NSString*)key;

@end

/*!
 *! UISettingsController
 */
@interface UISettingsController : WSIUIViewController <UITextFieldDelegate, UINavigationControllerDelegate, UITableViewDelegate, UITableViewDataSource> {
    
    //! delegate.
    id<UISettingsDelegate>  _delegate;
    
    //! tableview for datas.
    UITableView    			*_tableView;
    
    //! view list.
    NSMutableArray          *_viewList;
    
    //! current index path.
    NSIndexPath             *_currentIndexPath;
    
    //! topmost row.
	NSIndexPath				*_topmostRowBeforeKeyboardWasShown;
	
    //! reander.
	UISettingsReader		*_settingsReader;
    
    //! store.
    id<UISettingsStore>     _settingsStore;
    
    //! file name.
	NSString				*_file;
	
    //! first responder.
	id                      _currentFirstResponder;
    
    //! show credits footer.
    BOOL                    _showCreditsFooter;
    
    //! show down button.
    BOOL                    _showDoneButton;
    
    //! target controller.
    UIViewController       *_targetController;
    
    WSIDECL_PRIVATE(UISettingsController);
}

@property (nonatomic, assign) IBOutlet id delegate;
@property (nonatomic, retain) IBOutlet UITableView *tableView;
@property (nonatomic, retain) NSIndexPath   *currentIndexPath;
@property (nonatomic, retain) UISettingsReader *settingsReader;
@property (nonatomic, retain) id<UISettingsStore> settingsStore;
@property (nonatomic, copy)   NSString *file;
@property (nonatomic, retain) id currentFirstResponder;
@property (nonatomic, assign) BOOL showCreditsFooter;
@property (nonatomic, assign) BOOL showDoneButton;
@property (nonatomic, assign) UIViewController *targetController;

//! synch settings.
- (void)synchronizeSettings;

//! dismiss self.
- (IBAction)dismiss:(id)sender;

//! redirect. subclassing: optionally override these methods to customize appearance and functionality.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath;
- (NSIndexPath *)tableView:(UITableView *)tableView willSelectRowAtIndexPath:(NSIndexPath *)indexPath;
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath;
- (UIView *)tableView:(UITableView*)tableView viewForHeaderInSection:(NSInteger)section;

@end

@interface UISettingsController (direct)

- (void)prepareAppear:(BOOL)animated;
- (void)afterAppear:(BOOL)animated;
- (void)prepareDisappear:(BOOL)animated;
- (void)afterDisappear:(BOOL)animated;

@end

WSI_END_HEADER_OBJC

# endif