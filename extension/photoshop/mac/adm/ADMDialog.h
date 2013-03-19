/*******************************************************************************
*
* ADMDialog.h -- ADM Dialog Suite
*
* ADOBE SYSTEMS INCORPORATED
* Copyright 1996-2003 Adobe Systems Incorporated
* All Rights Reserved
*
* NOTICE: Adobe permits you to use, modify, and distribute this file in
* accordance with the terms of the Adobe license agreement accompanying it.
* If you have received this file from a source other than Adobe, then your use,
* modification, or distribution of it requires the prior written permission of
* Adobe.
*
* Started by Dave Lazarony, 10 Mar 1996
*
********************************************************************************/

/** @file ADMDialog.h ADM Dialog Suite */

#ifndef __ADMDialog__
#define __ADMDialog__

#ifndef __ADMItem__
#include "ADMItem.h"
#endif

#ifndef __ADMTypes__
#include "ADMTypes.h"
#endif

#ifndef __SPInterface__
#include "SPInterf.h"
#endif


// -----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

#pragma ADM_PRAGMA_ALIGN_BEGIN
#pragma ADM_PRAGMA_IMPORT_BEGIN

// Mac OS headers #define GetItem, but we want to use it as a name.
#ifdef GetItem
#undef GetItem
#endif


// -----------------------------------------------------------------------------
//	Create custom item message.

/** ... */
#define kADMCaller "Adobe Dialog Manager"
/** ... */
#define kADMCreateCustomItem "Create Custom Item"

/** ... */
typedef struct
{
	/** ... */
	SPMessageData d;
	/** ... */
	ADMDialogRef dialog;
	/** ... */
	ADMInt32 itemID;
	/** ... */
	ADMItemType itemType;
	/** ... */
	ADMRect boundsRect;
	/** ... */
	ADMItemInitProc initProc;
	/** ... */
	ADMUserData data;
	/** ... */
	ADMItemRef item;
}
ADMCreateCustomItemMessage;


// -----------------------------------------------------------------------------
//	Dialog options (for Create() call).
//	Options above 1L << 28 are reserved for internal use.

/** ... */
#define kADMTabbedDialogShowsCycleOption (1L << 0)
		// When creating tabbed dialog with a cycle button on the tab.

/** ... */
#define kADMPassMouseDownEventInModalDialogOption (1L << 1)
		// To allow modal dialogs pass mouse down events through to
		// the user dialog tracker on the application side.

/** ... */
#define kReservedForUseByCustomResourcesOption (1L << 2)

/** ... */
#define kADMKeypadEnterNotDefault (1L << 3)
		// Keypad 'enter' key does not activate default item.

/** ... */
#define kADMCreateDialogItemsHiddenByDefault (1L << 4)
		// Reduce flicker by creating items hidden.

/** ... */
#define kADMForceRomanFontForDialog (1L << 5)
		// Forces for all items within dialog, except as overridden.

/** ... */
#define kADMTrackEnterBeforeDialogDoesOK	(1L << 6)
		// Track the enter keys (carriage return and keypad enter) before the
		// dialog treats the event as equivalent to pressing the OK button --
		// and prevent that behavior if the tracker returns true. Note that by
		// default, the enter keys cause text item trackers to commit their text
		// and return true, so this option normally prevents the "OK" behavior
		// when enter is pressed within a text item.
		// (This option currently relevant only on Mac platform.)

/** ... */
#define kADMModalDialogHasPaletteSystemControlsOption (1L << 7)
		// 0 by default. If set, ADM Modal dialogs on Windows will have a 
		// close box on the top right hand corner. Also there is a host
		// option that a user can use if all dialogs in the application
		// need that behavior. 
		// dagashe:09/29/00:added for Acrobat 5.0 bug #382265

/** ... */
#define kADMCreatePopupDialogAsFloatingClassOption (1L << 8)
		//If this option is set for a dialog of style kADMPopupControldialogStyle
		//then ADM will create the dialog of kFloatingwindowclass. This option
		//is currently used only on MacOSX.

// -----------------------------------------------------------------------------
//	Dialog styles (for Create() call).
//	Style constants above FFFF are reserved for host use.
 
/** ... */
typedef enum
{
	/** ... */
	kADMModalDialogStyle = 0,
	/** ... */
	kADMAlertDialogStyle = 1,
	/** ... */
	kADMFloatingDialogStyle = 2,
	/** ... */
	kADMTabbedFloatingDialogStyle = 3,
	/** ... */
	kADMResizingFloatingDialogStyle = 4,
	/** ... */
	kADMTabbedResizingFloatingDialogStyle = 5,
	/** ... */
	kADMPopupDialogStyle = 6,
	/** ... */
	kADMNoCloseFloatingDialogStyle = 7,
	/** ... */
	kADMSystemAlertDialogStyle = 8,
	/** ... */
	kADMPopupControlDialogStyle = 9,
	/** ... */
	kADMResizingModalDialogStyle = 10,
	/** ... */
	kADMLeftSidedFloatingDialogStyle = 11,
	/** ... */
	kADMLeftSidedNoCloseFloatingDialogStyle = 12,
	/** ... */
	kADMNoTitleDockFloatingDialogStyle = 13,
	/** ... */
	kADMTabbedHierarchyFloatingDialogStyle = 14,			// hathaway : 8/22/02 : Added these ...Hierarchy... enums to allow creation of 
	/** ... */
	kADMTabbedResizingHierarchyFloatingDialogStyle = 15,    // hierarchical palette menus in Pangea
	/** ... */
	kADMHostDefinedDialogStyle = 65536,
	/** ... */
	kADMDummyDialogStyle = 0xFFFFFFFF
}
ADMDialogStyle;

 
// -----------------------------------------------------------------------------
//	Standard dialog item IDs

/** ... */
typedef enum
{
	/** ... */
	kADMUniqueItemID = 0,
	/** ... */
	kADMFirstItemID = -1,
	/** ... */
	kADMLastItemID = -2,
	/** ... */
	kADMDefaultItemID = -3,
	/** ... */
	kADMCancelItemID = -4,
	/** ... */
	kADMMenuItemID = -5,
	/** ... */
	kADMResizeItemID = -6,
	/** ... */
	kADMPrivateUniqueItemID = -7,	// dhearst 1/31/01 - changed from -10 to kADMFirstUnusedPrivateItemID.
									// Part of fix for EveParser Bug (ABTS #409214)
	// The constant kADMFirstUnusedPrivateItemID should ALWAYS be one more negative than the last
	// non-Dummy value in this enum. If you add more enum values, be sure to update kADMFirstUnusedPrivateItemID.
	/** ... */
	kADMFirstUnusedPrivateItemID = -8,
	/** ... */
	kADMDummyItemID = 0x7FFFFFFF
}
ADMStandardDialogItemID;


// -----------------------------------------------------------------------------
//	Dialog error codes
 
/** ... */
#define kDialogResourceNotFoundError 'DLOG'
			// error data == resID

/** ... */
#define kDialogItemListResourceNotFoundError 'DITL'
			// error data == resID

/** ... */
#define kCouldntCreateItemError '!itm'
			// error data == resID


// -----------------------------------------------------------------------------
//	User-provided function prototypes

// ADMItemRef and ADMDialogRef are declared in ADMTypes.h

/** ... */
typedef ADMErr ADMAPI (*ADMDialogInitProc)(ADMDialogRef inDialog);
/** ... */
typedef void ADMAPI (*ADMDialogDrawProc)(ADMDialogRef inDialog, ADMDrawerRef inDrawer);
/** ... */
typedef ADMBoolean ADMAPI (*ADMDialogTrackProc)(ADMDialogRef inDialog, ADMTrackerRef inTracker);
/** ... */
typedef void ADMAPI (*ADMDialogNotifyProc)(ADMDialogRef inDialog, ADMNotifierRef inNotifier);
/** ... */
typedef void ADMAPI (*ADMDialogDestroyProc)(ADMDialogRef inDialog);
/** ... */
typedef ADMBoolean ADMAPI (*ADMDialogTimerProc)(ADMDialogRef inDialog, ADMTimerRef inTimerID);
/** ... */
typedef void ADMAPI (*ADMDialogTimerAbortProc)(ADMDialogRef inDialog, ADMTimerRef inTimerID,
			ADMAction inAbortAction);


// =============================================================================
//		* ADM Dialog Suite
// =============================================================================

/** ... */
#define kADMDialogSuite "ADM Dialog Suite"
/** ... */
#define kADMDialogSuiteVersion9 9

// -----------------------------------------------------------------------------

/** ... */
typedef struct ADMDialogSuite9
{

	// *** This suite is FROZEN.
	// *** It shipped with Acrobat 6.0.

	// dialog creation

	/** ... */
	ADMDialogRef ADMAPI (*Create)(SPPluginRef inPluginRef, const char* inName,
				ADMInt32 inDialogID, ADMDialogStyle inDialogStyle,
				ADMDialogInitProc inInitProc, ADMUserData inUserData, ADMInt32 inOptions);

	// modal dialogs

	/** ... */
	ADMInt32 ADMAPI (*Modal)(SPPluginRef inPluginRef, const char* inName,
				ADMInt32 inDialogID, ADMDialogStyle inDialogStyle,
				ADMDialogInitProc inInitProc, ADMUserData inUserData, ADMInt32 inOptions);

	/** ... */
	ADMInt32 ADMAPI (*PopupModal)(SPPluginRef inPluginRef, const char* inName,
				ADMInt32 inDialogID, ADMDialogInitProc inInitProc, ADMUserData inUserData,
				ADMInt32 inOptions);

	/** ... */
	ADMInt32 ADMAPI (*DisplayAsModal)(ADMDialogRef inDialog);

	// dialog destruction

	/** ... */
	void ADMAPI (*Destroy)(ADMDialogRef inDialog);
	
	// dialog draw proc
	
	/** ... */
	void ADMAPI (*SetDrawProc)(ADMDialogRef inDialog, ADMDialogDrawProc inDrawProc);
	/** ... */
 	ADMDialogDrawProc ADMAPI (*GetDrawProc)(ADMDialogRef inDialog);
	/** ... */
	void ADMAPI (*DefaultDraw)(ADMDialogRef inDialog, ADMDrawerRef inDrawer);

	// dialog track proc
	
	/** ... */
	void ADMAPI (*SetTrackProc)(ADMDialogRef inDialog, ADMDialogTrackProc inTrackProc);
	/** ... */
	ADMDialogTrackProc ADMAPI (*GetTrackProc)(ADMDialogRef inDialog);
	/** ... */
	ADMBoolean ADMAPI (*DefaultTrack)(ADMDialogRef inDialog, ADMTrackerRef inTracker);

	/** ... */
	void ADMAPI (*SetMask)(ADMDialogRef inDialog, ADMActionMask inMask);
	/** ... */
	ADMActionMask ADMAPI (*GetMask)(ADMDialogRef inDialog);

	// dialog notify proc

	/** ... */
	void ADMAPI (*SetNotifyProc)(ADMDialogRef inDialog, ADMDialogNotifyProc inNotifyProc);
	/** ... */
	ADMDialogNotifyProc ADMAPI (*GetNotifyProc)(ADMDialogRef inDialog);
	/** ... */
	void ADMAPI (*DefaultNotify)(ADMDialogRef inDialog, ADMNotifierRef inNotifier);
	/** ... */
	void ADMAPI (*SendNotify)(ADMDialogRef inDialog, const char* inNotifierType);

	/** ... */
	void ADMAPI (*SetNotifierData)(ADMDialogRef inDialog, ADMUserData inUserData);
	/** ... */
	ADMUserData ADMAPI (*GetNotifierData)(ADMDialogRef inDialog);

	// dialog destroy proc

	/** ... */
	void ADMAPI (*SetDestroyProc)(ADMDialogRef inDialog, ADMDialogDestroyProc inDestroyProc);
	/** ... */
	ADMDialogDestroyProc ADMAPI (*GetDestroyProc)(ADMDialogRef inDialog);

	// dialog timer
	
	/** ... */
	ADMTimerRef ADMAPI (*CreateTimer)(ADMDialogRef inDialog, ADMUInt32 inMilliseconds,
				ADMActionMask inAbortMask, ADMDialogTimerProc inTimerProc,
				ADMDialogTimerAbortProc inAbortProc, ADMInt32 inOptions);
	
	/** ... */
	void ADMAPI (*AbortTimer)(ADMDialogRef inDialog, ADMTimerRef inTimerID);

	// dialog user data
	
	/** ... */
	void ADMAPI (*SetUserData)(ADMDialogRef inDialog, ADMUserData inUserData);
	/** ... */
	ADMUserData ADMAPI (*GetUserData)(ADMDialogRef inDialog);

	// dialog information accessors

	/** ... */
	ADMAPI const char* (*GetDialogName)(ADMDialogRef inDialog);
	/** ... */
	ADMInt32 ADMAPI (*GetID)(ADMDialogRef inDialog);
	/** ... */
	SPPluginRef ADMAPI (*GetPluginRef)(ADMDialogRef inDialog);
	/** ... */
	ADMWindowRef ADMAPI (*GetWindowRef)(ADMDialogRef inDialog);

	/** ... */
	void ADMAPI (*SetDialogStyle)(ADMDialogRef inDialog, ADMDialogStyle inDialogStyle);
	/** ... */
	ADMDialogStyle ADMAPI (*GetDialogStyle)(ADMDialogRef inDialog);

	// dialog state accessors
	
	/** ... */
	void ADMAPI (*Show)(ADMDialogRef inDialog, ADMBoolean inShow);
	/** ... */
	ADMBoolean ADMAPI (*IsVisible)(ADMDialogRef inDialog);
	
	/** ... */
	void ADMAPI (*Enable)(ADMDialogRef inDialog, ADMBoolean inEnable);
	/** ... */
	ADMBoolean ADMAPI (*IsEnabled)(ADMDialogRef inDialog);
	
	/** ... */
	void ADMAPI (*Activate)(ADMDialogRef inDialog, ADMBoolean inActivate);
	/** ... */
	ADMBoolean ADMAPI (*IsActive)(ADMDialogRef inDialog);
	
	// dialog bounds accessors
	
	/** ... */
	void ADMAPI (*SetLocalRect)(ADMDialogRef inDialog, const ADMRect* inLocalRect);
	/** ... */
	void ADMAPI (*GetLocalRect)(ADMDialogRef inDialog, ADMRect* outLocalRect);
	
	/** ... */
	void ADMAPI (*SetBoundsRect)(ADMDialogRef inDialog, const ADMRect* inBoundsRect);
	/** ... */
	void ADMAPI (*GetBoundsRect)(ADMDialogRef inDialog, ADMRect* outBoundsRect);
	
	/** ... */
	void ADMAPI (*Move)(ADMDialogRef inDialog, ADMInt32 inHorizPosition, ADMInt32 inVertPosition);
	/** ... */
	void ADMAPI (*Size)(ADMDialogRef inDialog, ADMInt32 inWidth, ADMInt32 inHeight);

	// coordinate system transformations
	
	/** ... */
	void ADMAPI (*LocalToScreenPoint)(ADMDialogRef inDialog, ADMPoint* ioPoint);
	/** ... */
	void ADMAPI (*ScreenToLocalPoint)(ADMDialogRef inDialog, ADMPoint* ioPoint);
	
	/** ... */
	void ADMAPI (*LocalToScreenRect)(ADMDialogRef inDialog, ADMRect* ioRect);
	/** ... */
	void ADMAPI (*ScreenToLocalRect)(ADMDialogRef inDialog, ADMRect* ioRect);

	// dialog redraw requests
	
	/** ... */
	void ADMAPI (*Invalidate)(ADMDialogRef inDialog);
	/** ... */
	void ADMAPI (*InvalidateRect)(ADMDialogRef inDialog, const ADMRect* inInvalRect);
	/** ... */
	void ADMAPI (*Update)(ADMDialogRef inDialog);

	// cursor ID accessors

	/** ... */
	ADMBoolean ADMAPI (*SetCursorID)(ADMDialogRef inDialog, SPPluginRef inPluginRef,
				ADMInt32 inCursorID);

	/** ... */
	void ADMAPI (*GetCursorID)(ADMDialogRef inDialog, SPPluginRef* outPluginRef,
				ADMInt32* outCursorID);
	
	// dialog text accessors

	/** ... */
	void ADMAPI (*SetFont)(ADMDialogRef inDialog, ADMFont inFont);
	/** ... */
	ADMFont ADMAPI (*GetFont)(ADMDialogRef inDialog);

	/** ... */
	void ADMAPI (*SetText)(ADMDialogRef inDialog, const char* inText);
	/** ... */
	void ADMAPI (*SetTextW)(ADMDialogRef inDialog, const ADMUnicode* inText);

	/** ... */
	void ADMAPI (*GetText)(ADMDialogRef inDialog, char* outText, ADMInt32 inMaxLength);
	/** ... */
	void ADMAPI (*GetTextW)(ADMDialogRef inDialog, ADMUnicode* outText, ADMInt32 inMaxLength);

	/** ... */
	ADMInt32 ADMAPI (*GetTextLength)(ADMDialogRef inDialog);
	/** ... */
	ADMInt32 ADMAPI (*GetTextLengthW)(ADMDialogRef inDialog);

	// dialog size constraints
	
	/** ... */
	void ADMAPI (*SetMinWidth)(ADMDialogRef inDialog, ADMInt32 inWidth);
	/** ... */
	ADMInt32 ADMAPI (*GetMinWidth)(ADMDialogRef inDialog);
	
	/** ... */
	void ADMAPI (*SetMinHeight)(ADMDialogRef inDialog, ADMInt32 inHeight);
	/** ... */
	ADMInt32 ADMAPI (*GetMinHeight)(ADMDialogRef inDialog);
	
	/** ... */
	void ADMAPI (*SetMaxWidth)(ADMDialogRef inDialog, ADMInt32 inWidth);
	/** ... */
	ADMInt32 ADMAPI (*GetMaxWidth)(ADMDialogRef inDialog);
	
	/** ... */
	void ADMAPI (*SetMaxHeight)(ADMDialogRef inDialog, ADMInt32 inHeight);
	/** ... */
	ADMInt32 ADMAPI (*GetMaxHeight)(ADMDialogRef inDialog);
	
	/** ... */
	void ADMAPI (*SetHorizontalIncrement)(ADMDialogRef inDialog, ADMInt32 inIncrement);
	/** ... */
	ADMInt32 ADMAPI (*GetHorizontalIncrement)(ADMDialogRef inDialog);

	/** ... */
	void ADMAPI (*SetVerticalIncrement)(ADMDialogRef inDialog, ADMInt32 inIncrement);
	/** ... */
	ADMInt32 ADMAPI (*GetVerticalIncrement)(ADMDialogRef inDialog);

	// item accessors

	/** ... */
	ADMItemRef ADMAPI (*GetItem)(ADMDialogRef inDialog, ADMInt32 inItemID);
	
	/** ... */
	ADMItemRef ADMAPI (*CreateItem)(ADMDialogRef inDialog, ADMInt32 inItemID,
				ADMItemType inItemType, const ADMRect* inBoundsRect,
				ADMItemInitProc inInitProc, ADMUserData inUserData, ADMInt32 inOptions);

	/** ... */
	void ADMAPI (*DestroyItem)(ADMDialogRef inDialog, ADMItemRef inItem);
	
	/** ... */
	ADMItemRef ADMAPI (*GetNextItem)(ADMDialogRef inDialog, ADMItemRef inItem);
	/** ... */
	ADMItemRef ADMAPI (*GetPreviousItem)(ADMDialogRef inDialog, ADMItemRef inItem);

	// default/cancel items

	/** ... */
	void ADMAPI (*SetDefaultItemID)(ADMDialogRef inDialog, ADMInt32 inItemID);
	/** ... */
	ADMInt32 ADMAPI (*GetDefaultItemID)(ADMDialogRef inDialog);

	/** ... */
	void ADMAPI (*SetCancelItemID)(ADMDialogRef inDialog, ADMInt32 inItemID);
	/** ... */
	ADMInt32 ADMAPI (*GetCancelItemID)(ADMDialogRef inDialog);

	/** ... */
	ADMBoolean ADMAPI (*EndModal)(ADMDialogRef inDialog, ADMInt32 inModalResultID,
				ADMBoolean inCancelling);
	
	// custom item types
	
	/** ... */
	ADMErr ADMAPI (*RegisterItemType)(SPPluginRef inPluginRef, ADMItemType inItemType);
	/** ... */
	ADMErr ADMAPI (*UnregisterItemType)(SPPluginRef inPluginRef, ADMItemType inItemType);

	// tooltips

	/** ... */
	void ADMAPI (*LoadToolTips)(ADMDialogRef inDialog, ADMInt32 inStringID);

	// context help
	// dhearst 6/28/02 - ADM no longer supports ASHelp
	/** ... */
	void ADMAPI (*SetHelpID_DEPRECATED)(ADMDialogRef inDialog, ADMInt32 inHelpID);
	/** ... */
	ADMInt32 ADMAPI (*GetHelpID_DEPRECATED)(ADMDialogRef inDialog);
	/** ... */
	void ADMAPI (*Help_DEPRECATED)(ADMDialogRef inDialog);

	// dialog state accessors	

	/** ... */
	ADMBoolean ADMAPI (*IsCollapsed)(ADMDialogRef inDialog);

	/** ... */
	ADMItemRef ADMAPI (*CreateGroupInDialog)(ADMDialogRef inDialog,
				SPPluginRef inPluginRef, const char* inName, ADMInt32 inDialogID,
				ADMItemInitProc inInitProc, ADMUserData inUserData, ADMInt32 inOptions);

	/** ... */
	void ADMAPI (*SetWindowRef)(ADMDialogRef inDialog, ADMWindowRef inWindowRef);
	/** ... */
	void ADMAPI (*SetDialogName)(ADMDialogRef inDialog, const char* inName);

	/** ... */
	ADMBoolean ADMAPI (*IsDialogContextHidden)(ADMDialogRef inDialog);

	/** ... */
	void ADMAPI (*SetUpdateEnabled)(ADMDialogRef inDialog, ADMBoolean inEnableUpdate);
	/** ... */
	ADMBoolean ADMAPI (*IsUpdateEnabled)(ADMDialogRef inDialog);
	
	/** ... */
	void ADMAPI (*SetForcedOnScreen)(ADMDialogRef ioDialog,
				ADMBoolean inForcedOnScreen);
	/** ... */
	ADMBoolean ADMAPI (*IsForcedOnScreen)(ADMDialogRef inDialog);

	/** ... */
	ADMInt32 ADMAPI (*DisplayAsPopupModal)(ADMDialogRef inDialog);
	
	//Use this function to reposition the tab order of the item in the dialog. Note the item should 
	//be already created.
	/** ... */
	ADMErr ADMAPI (*DEPRECATED_AdjustItemTabOrder)(ADMDialogRef inDialog, ADMItemRef inItem, ADMInt32 position);

	// dialog embedding

//	ADMDialogRef ADMAPI (*CreateInPlatformWindow)(ADMWindowRef inPlatformWindow, const ADMRect* inBoundsInWindow);

	// UIT window as dialog
	
	/** ... */
	ADMDialogRef ADMAPI (*CreateUITWindow_DEPRECATED)(SPPluginRef inPluginRef, const char* inName,
				ADMInt32 inDialogID, ADMDialogStyle inDialogStyle,
				ADMDialogInitProc inInitProc, ADMUserData inUserData,
				ADMInt32 inOptions);

	/** ... */
	ADMItemRef ADMAPI (*CreateNestedItem)(ADMDialogRef inDialog, ADMItemRef inParentItem,
				ADMInt32 inItemID, ADMItemType inItemType, const ADMRect* inBoundsRect,
				ADMItemInitProc inInitProc, ADMUserData inUserData, ADMInt32 inOptions);
	
	/*
		Focus Note:
		You can specify focus order in ADM in two ways. If you are specifying the order of a list
		of items the most efficiently way of doing this is to do the following:
			BeginAdjustingFocusOrder(dialog)
			SetNextFocus
			SetNextFocus
			SetFirstFocus
			...
			DoneAdjustingFocusOrder(dialog)
		
		IMPORTANT:
		You may not nest code that use:
			BeginAdjustingFocusOrder
			SetNextFocus
			SetFirstFocus
			DoneAdjustingFocusOrder
		When you call these APIs you should finish specifying the order in one dialog before proceeding to
		the next one.

		If you want to rearrange the order of an existing focus list, you should call the ADMItemSuite's
			MoveFocusItem
	*/
	
	/**
		Should be called when an entire focus list have been specified by a number of calls to
		SetNextFocus (see focus note)
		Note this method should only be called if BeginAdjustingFocusOrder has been called.
		
		This call causes SetNextFocus calls to "take" and  is necessary for ADM to know when to rearrange
		the item list as specified by ADMItemSuite's SetNextFocus call.
	*/
	ADMErr ADMAPI (*DoneAdjustingFocusOrder)(ADMDialogRef inDialog);

	/**
		Call before specifying an entire focus list by using a series of SetNextFocus call
		(see focus note)
	*/
	ADMErr ADMAPI (*BeginAdjustingFocusOrder)(ADMDialogRef inDialog);


	/**
		Return the first item of the dialog (focus) list. If the focus list is empty NULL
		is returned.
	*/
	ADMErr ADMAPI (*FirstItem)(ADMDialogRef inDialog, ADMItemRef* outItem);

	/**
		Return the last item of the dialog (focus) list. If the focus list is empty NULL
		is returned.
	*/
	ADMErr ADMAPI (*LastItem)(ADMDialogRef inDialog, ADMItemRef* outItem);

}
ADMDialogSuite9;


// -----------------------------------------------------------------------------
//	Old versions of suites

#ifndef __ADMDialogOld__
#ifdef MAC_ENV
#include "ADMDialogOld.h"
#else
#include ".\Legacy\ADMDialogOld.h"
#endif
#endif

// -----------------------------------------------------------------------------

#pragma ADM_PRAGMA_IMPORT_END
#pragma ADM_PRAGMA_ALIGN_END

#ifdef __cplusplus
}
#endif

// -----------------------------------------------------------------------------

#endif	// __ADMDialog__
