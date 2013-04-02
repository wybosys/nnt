
# ifndef __NNT_UIKIT_B6DC89247D3547C2ACC8865508C5F22D_H_INCLUDED
# define __NNT_UIKIT_B6DC89247D3547C2ACC8865508C5F22D_H_INCLUDED

# ifndef LIBNNT
#   define LIBNNT
#   define NO_LIBNNT
# endif

# ifdef NNT_TARGET_IOS
# import <UIKit/UIKit.h>
# endif

// add base frameworks.
# import <QuartzCore/QuartzCore.h>
# import "../Graphic/Graphic+NNT.h"

// add layout support.
# import "../Core/Layout.h"

// ui base object.
# import "UIObject+NNT.h"

// quartz + nnt.
# import "QzAnimation.h"
# import "QzTransition.h"

// for ios.
# ifdef NNT_TARGET_IOS

# import "QzDisplayLink.h"
# import "UIScreen+NNT.h"
# import "UIDevice+NNT.h"
# import "UIColor+NNT.h"
# import "UIFont+NNT.h"
# import "UIView+NNT.h"
# import "UIControl+NNT.h"
# import "UIAnimation.h"
# import "UIViewController+NNT.h"
# import "UILabel+NNT.h"
# import "UITextField+NNT.h"
# import "UITextView+NNT.h"
# import "UIAlertView+NNT.h"
# import "UIActivityIndicatorView+NNT.h"
# import "UIWindow+NNT.h"
# import "UIImageView+NNT.h"
# import "UIWebView+NNT.h"
# import "UIWebController.h"
# import "UIImage+NNT.h"
# import "UIDesktop.h"
# import "UIButton+NNT.h"
# import "UIScrollView+NNT.h"
# import "UIConcaveButton.h"
# import "UIBadgeIndicator.h"
# import "UITabBar+NNT.h"
# import "UITabBarController+NNT.h"
# import "UITableViewController+NNT.h"
# import "UITableTreeViewController.h"
# import "UISegmentedControl+NNT.h"
# import "UIPickerView+NNT.h"
# import "UIBarButtonItem+NNT.h"
# import "UINavigationBar+NNT.h"
# import "UINavigationController+NNT.h"
# import "UIToolbar+NNT.h"
# import "UISwitch+NNT.h"
# import "UISlider+NNT.h"
# import "UIPageControl+NNT.h"
# import "UISearchBar+NNT.h"
# import "UICameraView.h"
# import "UIImagePickerController+NNT.h"
# import "UIMapView.h"
# import "UILineSeparator.h"
# import "UIPickerControl.h"
# import "UIContactField.h"
# import "UIVideoController.h"
# import "UITouch+NNT.h"
# import "UIActionSheet+NNT.h"
# import "UISearchDisplayController+NNT.h"
# import "UIPopoverController+NNT.h"

# import "UIDialog.h"
# import "UIWaiting.h"
# import "UITip.h"

# import "UIInitialView.h"
# import "UISwitchView.h"
# import "UISwitchController.h"
# import "UISpreadSheet.h"
# import "UISpreadSheetCell.h"
# import "UISpreadSheetCellMatrix.h"
# import "UISpreadSheetCorner.h"
# import "UISpreadSheetHeader.h"
# import "UICoverFlow.h"
# import "UICoverFlowItem.h"
# import "UICoverFlowController.h"
# import "UICoverDrawer.h"
# import "UICoverDrawerItem.h"
# import "UICoverDrawerController.h"
# import "UIBanner.h"
# import "UIGridView.h"
# import "UILayoutGridView.h"
# import "UIExposeControl.h"
# import "UICHMController.h"
# import "UIValuePicker.h"
# import "UIValuePickerView.h"
# import "UITearView.h"
# import "UINavigationDial.h"
# import "UINavigationDialView.h"
# import "UINavigationDialController.h"
# import "UISettingsController.h"
# import "UISegmentedController.h"
# import "UITabBarContainerController.h"
# import "UIRatingControl.h"
# import "UIGridPageController.h"
# import "UIPageSwitchController.h"
# import "UIGridViewController.h"
# import "UIFlowView.h"
# import "UISetControllers.h"
# import "UIStackControllers.h"
# import "UISMSController.h"
# import "UIEmailController.h"
# import "UIHudView.h"
# import "UIActivityIndicatorBar.h"
# import "UIActivityIndicatorWave.h"
# import "UIDrawerView.h"
# import "UIPageRoller.h"
# import "UIAnnualRingView.h"

# import "../Core/NSNotification+NNT.h"

# endif

// for mac.
# ifdef NNT_TARGET_MAC

# import "NSImage+NNT.h"
# import "NSWindow+NNT.h"
# import "NSWindowController+NNT.h"
# import "NSView+NNT.h"
# import "NSViewController+NNT.h"
# import "NSControl+NNT.h"
# import "NSButton+NNT.h"
# import "NSTextField+NNT.h"
# import "NSTextView+NNT.h"
# import "NSTableView+NNT.h"
# import "NSListView+NNT.h"
# import "NSTabView+NNT.h"
# import "NSImageView+NNT.h"

# import "NSMessageBox.h"

# endif

// other.
# import "../Core/App.h"
# import "UITheme.h"

# ifdef NO_LIBNNT
#   undef NO_LIBNNT
#   undef LIBNNT
# endif

# endif
