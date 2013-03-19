
# ifndef __WSI_UIKIT_B6DC89247D3547C2ACC8865508C5F22D_H_INCLUDED
# define __WSI_UIKIT_B6DC89247D3547C2ACC8865508C5F22D_H_INCLUDED

# ifndef LIBWSI
#   define LIBWSI
#   define NO_LIBWSI
# endif

# ifdef WSI_TARGET_IOS
# import <UIKit/UIKit.h>
# endif

// add base frameworks.
# import <QuartzCore/QuartzCore.h>
# import "../Graphic/CoreGraphic+WSI.h"

// add layout support.
# import "../Core/Layout.h"

// ui base object.
# import "WSIUIObject.h"

// quartz + wsi.
# import "QzAnimation.h"
# import "QzTransition.h"
# import "QzDisplayLink.h"

// for ios.
# ifdef WSI_TARGET_IOS

# import "UIScreen+WSI.h"
# import "UIDevice+WSI.h"
# import "UIColor+WSI.h"
# import "UIFont+WSI.h"
# import "UIView+WSI.h"
# import "UIControl+WSI.h"
# import "UIAnimation.h"
# import "UIViewController+WSI.h"
# import "UILabel+WSI.h"
# import "UITextField+WSI.h"
# import "UITextView+WSI.h"
# import "UIAlertView+WSI.h"
# import "UIActivityIndicatorView+WSI.h"
# import "UIWindow+WSI.h"
# import "UIImageView+WSI.h"
# import "UIWebView+WSI.h"
# import "UIWebController.h"
# import "UIImage+WSI.h"
# import "UIDesktop.h"
# import "UIButton+WSI.h"
# import "UIScrollView+WSI.h"
# import "UIConcaveButton.h"
# import "UIBadgeIndicator.h"
# import "UITabBar+WSI.h"
# import "UITabBarController+WSI.h"
# import "UITableViewController+WSI.h"
# import "UITableTreeViewController.h"
# import "UISegmentedControl+WSI.h"
# import "UIPickerView+WSI.h"
# import "UIBarButtonItem+WSI.h"
# import "UINavigationBar+WSI.h"
# import "UINavigationController+WSI.h"
# import "UIToolbar+WSI.h"
# import "UISwitch+WSI.h"
# import "UISlider+WSI.h"
# import "UIPageControl+WSI.h"
# import "UISearchBar+WSI.h"
# import "UICameraView.h"
# import "UIImagePickerController+WSI.h"
# import "UIMapView.h"
# import "UILineSeparator.h"
# import "UIPickerControl.h"
# import "UIContactField.h"
# import "UIVideoController.h"
# import "UITouch+WSI.h"
# import "UIActionSheet+WSI.h"
# import "UISearchDisplayController+WSI.h"
# import "UIPopoverController+WSI.h"

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
# import "UIChartController.h"
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

# import "../Core/NSNotification+WSI.h"

# endif

// for mac.
# ifdef WSI_TARGET_MAC

# import "NSImage+WSI.h"
# import "NSWindow+WSI.h"
# import "NSWindowController+WSI.h"
# import "NSView+WSI.h"
# import "NSViewController+WSI.h"
# import "NSControl+WSI.h"
# import "NSButton+WSI.h"
# import "NSTextField+WSI.h"
# import "NSTextView+WSI.h"
# import "NSTableView+WSI.h"
# import "NSListView+WSI.h"
# import "NSTabView+WSI.h"
# import "NSImageView+WSI.h"

# import "NSMessageBox.h"

# endif

// other.
# import "../Core/App.h"
# import "UITheme.h"

# ifdef NO_LIBWSI
#   undef NO_LIBWSI
#   undef LIBWSI
# endif

# endif
