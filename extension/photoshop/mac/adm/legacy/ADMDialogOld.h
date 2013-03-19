/***********************************************************************/
/*                                                                     */
/* ADMDialogOld.h                                                      */
/* Old versions of ADM Dialog Suite                                    */
/*                                                                     */
/* ADOBE SYSTEMS INCORPORATED                                          */
/* Copyright 1996-2003 Adobe Systems Incorporated                      */
/* All Rights Reserved                                                 */
/*                                                                     */
/* NOTICE:  Adobe permits you to use, modify, and distribute this file */
/* in accordance with the terms of the Adobe license agreement         */
/* accompanying it. If you have received this file from a source other */
/* than Adobe, then your use, modification, or distribution of it      */
/* requires the prior written permission of Adobe.                     */
/*                                                                     */
/***********************************************************************/

#ifndef __ADMDialogOld__
#define __ADMDialogOld__

#ifndef __ADMDialog__
#include "ADMDialog.h"
#endif


// -----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

#pragma ADM_PRAGMA_ALIGN_BEGIN
#pragma ADM_PRAGMA_IMPORT_BEGIN


// =============================================================================
//		* ADM Dialog Suite, version 2
// =============================================================================

#define kADMDialogSuiteVersion2 2

// -----------------------------------------------------------------------------

typedef struct ADMDialogSuite2
{

	// dialog creation

	ADMDialogRef ADMAPI (*Create)(SPPluginRef inPluginRef, const char* inName,
				ADMInt32 inDialogID, ADMDialogStyle inDialogStyle,
				ADMDialogInitProc inInitProc, ADMUserData inUserData);

	// modal dialogs

	ADMInt32 ADMAPI (*Modal)(SPPluginRef inPluginRef, ADMInt32 inDialogID,
				ADMDialogStyle inDialogStyle, ADMDialogInitProc inInitProc,
				ADMUserData inUserData);

	// dialog destruction

	void ADMAPI (*Destroy)(ADMDialogRef inDialog);

	// dialog draw proc
	
	void ADMAPI (*SetDrawProc)(ADMDialogRef inDialog, ADMDialogDrawProc inDrawProc);
	ADMDialogDrawProc ADMAPI (*GetDrawProc)(ADMDialogRef inDialog);
	void ADMAPI (*DefaultDraw)(ADMDialogRef inDialog, ADMDrawerRef inDrawer);

	// dialog track proc
	
	void ADMAPI (*SetTrackProc)(ADMDialogRef inDialog, ADMDialogTrackProc inTrackProc);
	ADMDialogTrackProc ADMAPI (*GetTrackProc)(ADMDialogRef inDialog);
	ADMBoolean ADMAPI (*DefaultTrack)(ADMDialogRef inDialog, ADMTrackerRef inTracker);

	void ADMAPI (*SetMask)(ADMDialogRef inDialog, ADMActionMask inMask);
	ADMActionMask ADMAPI (*GetMask)(ADMDialogRef inDialog);

	// dialog notify proc

	void ADMAPI (*SetNotifyProc)(ADMDialogRef inDialog, ADMDialogNotifyProc inNotifyProc);
	ADMDialogNotifyProc ADMAPI (*GetNotifyProc)(ADMDialogRef inDialog);
	void ADMAPI (*DefaultNotify)(ADMDialogRef inDialog, ADMNotifierRef inNotifier);
	void ADMAPI (*SendNotify)(ADMDialogRef inDialog, const char* inNotifierType);

	void ADMAPI (*SetNotifierData)(ADMDialogRef inDialog, ADMUserData l);
	ADMUserData ADMAPI (*GetNotifierData)(ADMDialogRef inDialog);

	// dialog destroy proc

	void ADMAPI (*SetDestroyProc)(ADMDialogRef inDialog, ADMDialogDestroyProc inDestroyProc);
	ADMDialogDestroyProc ADMAPI (*GetDestroyProc)(ADMDialogRef inDialog);
	
	// dialog timer

	ADMTimerRef ADMAPI (*CreateTimer)(ADMDialogRef inDialog, ADMUInt32 inMilliseconds,
				ADMActionMask inAbortMask, ADMDialogTimerProc inTimerProc,
				ADMDialogTimerAbortProc inAbortProc);
	
	void ADMAPI (*AbortTimer)(ADMDialogRef inDialog, ADMTimerRef inTimerID);

	// dialog user data

	void ADMAPI (*SetUserData)(ADMDialogRef inDialog, ADMUserData inUserData);
	ADMUserData ADMAPI (*GetUserData)(ADMDialogRef inDialog);

	// dialog information accessors

	ADMAPI const char* (*GetDialogName)(ADMDialogRef inDialog);
	ADMInt32 ADMAPI (*GetID)(ADMDialogRef inDialog);
	SPPluginRef ADMAPI (*GetPluginRef)(ADMDialogRef inDialog);
	ADMWindowRef ADMAPI (*GetWindowRef)(ADMDialogRef inDialog);
	
	void ADMAPI (*SetDialogStyle)(ADMDialogRef inDialog, ADMDialogStyle inDialogStyle);
	ADMDialogStyle ADMAPI (*GetDialogStyle)(ADMDialogRef inDialog);
	
	// dialog state accessors

	void ADMAPI (*Show)(ADMDialogRef inDialog, ADMBoolean inShow);
	ADMBoolean ADMAPI (*IsVisible)(ADMDialogRef inDialog);
	
	void ADMAPI (*Enable)(ADMDialogRef inDialog, ADMBoolean inEnable);
	ADMBoolean ADMAPI (*IsEnabled)(ADMDialogRef inDialog);
	
	void ADMAPI (*Activate)(ADMDialogRef inDialog, ADMBoolean inActivate);
	ADMBoolean ADMAPI (*IsActive)(ADMDialogRef inDialog);

	// dialog bounds accessors
	
	void ADMAPI (*SetLocalRect)(ADMDialogRef inDialog, const ADMRect* inLocalRect);
	void ADMAPI (*GetLocalRect)(ADMDialogRef inDialog, ADMRect* outLocalRect);
	
	void ADMAPI (*SetBoundsRect)(ADMDialogRef inDialog, const ADMRect* inBoundsRect);
	void ADMAPI (*GetBoundsRect)(ADMDialogRef inDialog, ADMRect* outBoundsRect);
	
	void ADMAPI (*Move)(ADMDialogRef inDialog, ADMInt32 inHorizPosition, ADMInt32 inVertPosition);
	void ADMAPI (*Size)(ADMDialogRef inDialog, ADMInt32 inWidth, ADMInt32 inHeight);

	// coordinate system transformations
	
	void ADMAPI (*LocalToScreenPoint)(ADMDialogRef inDialog, ADMPoint* ioPoint);
	void ADMAPI (*ScreenToLocalPoint)(ADMDialogRef inDialog, ADMPoint* ioPoint);
	
	void ADMAPI (*LocalToScreenRect)(ADMDialogRef inDialog, ADMRect* ioRect);
	void ADMAPI (*ScreenToLocalRect)(ADMDialogRef inDialog, ADMRect* ioRect);
	
	// dialog redraw requests
	
	void ADMAPI (*Invalidate)(ADMDialogRef inDialog);
	void ADMAPI (*Update)(ADMDialogRef inDialog);
	
	// cursor ID accessors

	ADMBoolean ADMAPI (*SetCursorID)(ADMDialogRef inDialog, SPPluginRef inPluginRef,
				ADMInt32 inCursorID);

	void ADMAPI (*GetCursorID)(ADMDialogRef inDialog, SPPluginRef* outPluginRef,
				ADMInt32* outCursorID);

	// dialog text accessors

	void ADMAPI (*SetFont)(ADMDialogRef inDialog, ADMFont inFont);
	ADMFont ADMAPI (*GetFont)(ADMDialogRef inDialog);

	void ADMAPI (*SetText)(ADMDialogRef inDialog, const char* inText);
	void ADMAPI (*GetText)(ADMDialogRef inDialog, char* outText, ADMInt32 inMaxLength);
	ADMInt32 ADMAPI (*GetTextLength)(ADMDialogRef inDialog);

	// dialog size constraints
	
	void ADMAPI (*SetMinWidth)(ADMDialogRef inDialog, ADMInt32 inWidth);
	ADMInt32 ADMAPI (*GetMinWidth)(ADMDialogRef inDialog);
	
	void ADMAPI (*SetMinHeight)(ADMDialogRef inDialog, ADMInt32 inHeight);
	ADMInt32 ADMAPI (*GetMinHeight)(ADMDialogRef inDialog);
	
	void ADMAPI (*SetMaxWidth)(ADMDialogRef inDialog, ADMInt32 inWidth);
	ADMInt32 ADMAPI (*GetMaxWidth)(ADMDialogRef inDialog);
	
	void ADMAPI (*SetMaxHeight)(ADMDialogRef inDialog, ADMInt32 inHeight);
	ADMInt32 ADMAPI (*GetMaxHeight)(ADMDialogRef inDialog);
	
	void ADMAPI (*SetHorizontalIncrement)(ADMDialogRef inDialog, ADMInt32 inIncrement);
	ADMInt32 ADMAPI (*GetHorizontalIncrement)(ADMDialogRef inDialog);

	void ADMAPI (*SetVerticalIncrement)(ADMDialogRef inDialog, ADMInt32 inIncrement);
	ADMInt32 ADMAPI (*GetVerticalIncrement)(ADMDialogRef inDialog);

	// item accessors

	ADMItemRef ADMAPI (*GetItem)(ADMDialogRef inDialog, ADMInt32 inItemID);
	
	ADMItemRef ADMAPI (*CreateItem)(ADMDialogRef inDialog, ADMInt32 inItemID,
				ADMItemType inItemType, const ADMRect* inBoundsRect,
				ADMItemInitProc inInitProc, ADMUserData inUserData);

	void ADMAPI (*DestroyItem)(ADMDialogRef inDialog, ADMItemRef inItem);
	
	ADMItemRef ADMAPI (*GetNextItem)(ADMDialogRef inDialog, ADMItemRef inItem);
	ADMItemRef ADMAPI (*GetPreviousItem)(ADMDialogRef inDialog, ADMItemRef inItem);

	// default/cancel items

	void ADMAPI (*SetDefaultItemID)(ADMDialogRef inDialog, ADMInt32 inItemID);
	ADMInt32 ADMAPI (*GetDefaultItemID)(ADMDialogRef inDialog);
	void ADMAPI (*SetCancelItemID)(ADMDialogRef inDialog, ADMInt32 inItemID);
	ADMInt32 ADMAPI (*GetCancelItemID)(ADMDialogRef inDialog);
	
	ADMBoolean ADMAPI (*EndModal)(ADMDialogRef inDialog, ADMInt32 inModalResultID,
				ADMBoolean inCancelling);
	
	ADMErr ADMAPI (*RegisterItemType)(SPPluginRef inPluginRef, ADMItemType inItemType);
	ADMErr ADMAPI (*UnregisterItemType)(SPPluginRef inPluginRef, ADMItemType inItemType);

	// tooltips

	void ADMAPI (*LoadToolTips)(ADMDialogRef inDialog, ADMInt32 inStringID);

	// context help
	// dhearst 6/28/02 - ADM no longer supports ASHelp
	void ADMAPI (*SetHelpID_DEPRECATED)(ADMDialogRef inDialog, ADMInt32 inHelpID);
	ADMInt32 ADMAPI (*GetHelpID_DEPRECATED)(ADMDialogRef inDialog);
	void ADMAPI (*Help_DEPRECATED)(ADMDialogRef inDialog);

	// dialog state accessors

	ADMBoolean ADMAPI (*IsCollapsed)(ADMDialogRef inDialog);
	
}
ADMDialogSuite2;


// =============================================================================
//		* ADM Dialog Suite, version 3
// =============================================================================

#define kADMDialogSuiteVersion3 3
#define kADMDialogSuiteVersion kADMDialogSuiteVersion3

// -----------------------------------------------------------------------------

typedef struct ADMDialogSuite3
{

	// dialog creation

	ADMDialogRef ADMAPI (*Create)(SPPluginRef inPluginRef, const char* inName,
				ADMInt32 inDialogID, ADMDialogStyle inDialogStyle,
				ADMDialogInitProc inInitProc, ADMUserData inUserData);

	// modal dialogs

	ADMInt32 ADMAPI (*Modal)(SPPluginRef inPluginRef, const char* inName,
				ADMInt32 inDialogID, ADMDialogStyle inDialogStyle,
				ADMDialogInitProc inInitProc, ADMUserData inUserData);

	ADMInt32 ADMAPI (*DisplayAsModal)(ADMDialogRef inDialog);

	// dialog destruction

	void ADMAPI (*Destroy)(ADMDialogRef inDialog);

	// dialog draw proc
	
	void ADMAPI (*SetDrawProc)(ADMDialogRef inDialog, ADMDialogDrawProc inDrawProc);
	ADMDialogDrawProc ADMAPI (*GetDrawProc)(ADMDialogRef inDialog);
	void ADMAPI (*DefaultDraw)(ADMDialogRef inDialog, ADMDrawerRef inDrawer);

	// dialog track proc
	
	void ADMAPI (*SetTrackProc)(ADMDialogRef inDialog, ADMDialogTrackProc inTrackProc);
	ADMDialogTrackProc ADMAPI (*GetTrackProc)(ADMDialogRef inDialog);
	ADMBoolean ADMAPI (*DefaultTrack)(ADMDialogRef inDialog, ADMTrackerRef inTracker);

	void ADMAPI (*SetMask)(ADMDialogRef inDialog, ADMActionMask inMask);
	ADMActionMask ADMAPI (*GetMask)(ADMDialogRef inDialog);

	// dialog notify proc

	void ADMAPI (*SetNotifyProc)(ADMDialogRef inDialog, ADMDialogNotifyProc inNotifyProc);
	ADMDialogNotifyProc ADMAPI (*GetNotifyProc)(ADMDialogRef inDialog);
	void ADMAPI (*DefaultNotify)(ADMDialogRef inDialog, ADMNotifierRef inNotifier);
	void ADMAPI (*SendNotify)(ADMDialogRef inDialog, const char* inNotifierType);

	void ADMAPI (*SetNotifierData)(ADMDialogRef inDialog, ADMUserData inUserData);
	ADMUserData ADMAPI (*GetNotifierData)(ADMDialogRef inDialog);

	// dialog destroy proc

	void ADMAPI (*SetDestroyProc)(ADMDialogRef inDialog, ADMDialogDestroyProc inDestroyProc);
	ADMDialogDestroyProc ADMAPI (*GetDestroyProc)(ADMDialogRef inDialog);

	// dialog timer
	
	ADMTimerRef ADMAPI (*CreateTimer)(ADMDialogRef inDialog, ADMUInt32 inMilliseconds,
				ADMActionMask inAbortMask, ADMDialogTimerProc inTimerProc,
				ADMDialogTimerAbortProc inAbortProc);
	
	void ADMAPI (*AbortTimer)(ADMDialogRef inDialog, ADMTimerRef inTimerID);

	// dialog user data

	void ADMAPI (*SetUserData)(ADMDialogRef inDialog, ADMUserData inUserData);
	ADMUserData ADMAPI (*GetUserData)(ADMDialogRef inDialog);

	// dialog information accessors
	
	ADMAPI const char* (*GetDialogName)(ADMDialogRef inDialog);
	ADMInt32 ADMAPI (*GetID)(ADMDialogRef inDialog);
	SPPluginRef ADMAPI (*GetPluginRef)(ADMDialogRef inDialog);
	ADMWindowRef ADMAPI (*GetWindowRef)(ADMDialogRef inDialog);
	
	void ADMAPI (*SetDialogStyle)(ADMDialogRef inDialog, ADMDialogStyle inDialogStyle);
	ADMDialogStyle ADMAPI (*GetDialogStyle)(ADMDialogRef inDialog);
	
	// dialog state accessors
	
	void ADMAPI (*Show)(ADMDialogRef inDialog, ADMBoolean inShow);
	ADMBoolean ADMAPI (*IsVisible)(ADMDialogRef inDialog);
	
	void ADMAPI (*Enable)(ADMDialogRef inDialog, ADMBoolean inEnable);
	ADMBoolean ADMAPI (*IsEnabled)(ADMDialogRef inDialog);
	
	void ADMAPI (*Activate)(ADMDialogRef inDialog, ADMBoolean inActivate);
	ADMBoolean ADMAPI (*IsActive)(ADMDialogRef inDialog);
	
	// dialog bounds accessors
	
	void ADMAPI (*SetLocalRect)(ADMDialogRef inDialog, const ADMRect* inLocalRect);
	void ADMAPI (*GetLocalRect)(ADMDialogRef inDialog, ADMRect* outLocalRect);
	
	void ADMAPI (*SetBoundsRect)(ADMDialogRef inDialog, const ADMRect* inBoundsRect);
	void ADMAPI (*GetBoundsRect)(ADMDialogRef inDialog, ADMRect* outBoundsRect);
	
	void ADMAPI (*Move)(ADMDialogRef inDialog, ADMInt32 inHorizPosition, ADMInt32 inVertPosition);
	void ADMAPI (*Size)(ADMDialogRef inDialog, ADMInt32 inWidth, ADMInt32 inHeight);
	
	// coordinate system transformations
	
	void ADMAPI (*LocalToScreenPoint)(ADMDialogRef inDialog, ADMPoint* ioPoint);
	void ADMAPI (*ScreenToLocalPoint)(ADMDialogRef inDialog, ADMPoint* ioPoint);
	
	void ADMAPI (*LocalToScreenRect)(ADMDialogRef inDialog, ADMRect* ioRect);
	void ADMAPI (*ScreenToLocalRect)(ADMDialogRef inDialog, ADMRect* ioRect);

	// dialog redraw requests
	
	void ADMAPI (*Invalidate)(ADMDialogRef inDialog);
	void ADMAPI (*InvalidateRect)(ADMDialogRef inDialog, const ADMRect* inInvalRect);
	void ADMAPI (*Update)(ADMDialogRef inDialog);

	// cursor ID accessors
	
	ADMBoolean ADMAPI (*SetCursorID)(ADMDialogRef inDialog, SPPluginRef inPluginRef,
				ADMInt32 inCursorID);

	void ADMAPI (*GetCursorID)(ADMDialogRef inDialog, SPPluginRef* outPluginRef,
				ADMInt32* outCursorID);

	// dialog text accessors

	void ADMAPI (*SetFont)(ADMDialogRef inDialog, ADMFont inFont);
	ADMFont ADMAPI (*GetFont)(ADMDialogRef inDialog);

	void ADMAPI (*SetText)(ADMDialogRef inDialog, const char* inText);
	void ADMAPI (*GetText)(ADMDialogRef inDialog, char* outText, ADMInt32 inMaxLength);
	ADMInt32 ADMAPI (*GetTextLength)(ADMDialogRef inDialog);
	
	// dialog size constriants
	
	void ADMAPI (*SetMinWidth)(ADMDialogRef inDialog, ADMInt32 inWidth);
	ADMInt32 ADMAPI (*GetMinWidth)(ADMDialogRef inDialog);
	
	void ADMAPI (*SetMinHeight)(ADMDialogRef inDialog, ADMInt32 inHeight);
	ADMInt32 ADMAPI (*GetMinHeight)(ADMDialogRef inDialog);
	
	void ADMAPI (*SetMaxWidth)(ADMDialogRef inDialog, ADMInt32 inWidth);
	ADMInt32 ADMAPI (*GetMaxWidth)(ADMDialogRef inDialog);
	
	void ADMAPI (*SetMaxHeight)(ADMDialogRef inDialog, ADMInt32 inHeight);
	ADMInt32 ADMAPI (*GetMaxHeight)(ADMDialogRef inDialog);
	
	void ADMAPI (*SetHorizontalIncrement)(ADMDialogRef inDialog, ADMInt32 inIncrement);
	ADMInt32 ADMAPI (*GetHorizontalIncrement)(ADMDialogRef inDialog);

	void ADMAPI (*SetVerticalIncrement)(ADMDialogRef inDialog, ADMInt32 inIncrement);
	ADMInt32 ADMAPI (*GetVerticalIncrement)(ADMDialogRef inDialog);

	// item accessors

	ADMItemRef ADMAPI (*GetItem)(ADMDialogRef inDialog, ADMInt32 inItemID);
	
	ADMItemRef ADMAPI (*CreateItem)(ADMDialogRef inDialog, ADMInt32 inItemID,
				ADMItemType inItemType, const ADMRect* inBoundsRect,
				ADMItemInitProc inInitProc, ADMUserData inUserData);

	void ADMAPI (*DestroyItem)(ADMDialogRef inDialog, ADMItemRef inItem);
	
	ADMItemRef ADMAPI (*GetNextItem)(ADMDialogRef inDialog, ADMItemRef inItem);
	ADMItemRef ADMAPI (*GetPreviousItem)(ADMDialogRef inDialog, ADMItemRef inItem);

	// default/cancel items

	void ADMAPI (*SetDefaultItemID)(ADMDialogRef inDialog, ADMInt32 inItemID);
	ADMInt32 ADMAPI (*GetDefaultItemID)(ADMDialogRef inDialog);

	void ADMAPI (*SetCancelItemID)(ADMDialogRef inDialog, ADMInt32 inItemID);
	ADMInt32 ADMAPI (*GetCancelItemID)(ADMDialogRef inDialog);
	
	ADMBoolean  ADMAPI (*EndModal)(ADMDialogRef inDialog, ADMInt32 inModalResultID,
				ADMBoolean inCancelling);

	// custom item types
	
	ADMErr ADMAPI (*RegisterItemType)(SPPluginRef inPluginRef, ADMItemType inItemType);
	ADMErr ADMAPI (*UnregisterItemType)(SPPluginRef inPluginRef, ADMItemType inItemType);

	// tooltips

	void ADMAPI (*LoadToolTips)(ADMDialogRef inDialog, ADMInt32 inStringID);

	// context help
	// dhearst 6/28/02 - ADM no longer supports ASHelp
	void ADMAPI (*SetHelpID_DEPRECATED)(ADMDialogRef inDialog, ADMInt32 inHelpID);
	ADMInt32 ADMAPI (*GetHelpID_DEPRECATED)(ADMDialogRef inDialog);
	void ADMAPI (*Help_DEPRECATED)(ADMDialogRef inDialog);

	// dialog state accessors

	ADMBoolean ADMAPI (*IsCollapsed)(ADMDialogRef inDialog);
	
}
ADMDialogSuite3;

typedef ADMDialogSuite3 ADMDialogSuite; 


// =============================================================================
//		* ADM Dialog Suite, version 4
// =============================================================================

#define kADMDialogSuiteVersion4 4

// -----------------------------------------------------------------------------

typedef struct ADMDialogSuite4
{

	// dialog creation

	ADMDialogRef ADMAPI (*Create)(SPPluginRef inPluginRef, const char* inName,
				ADMInt32 inDialogID, ADMDialogStyle inDialogStyle,
				ADMDialogInitProc inInitProc, ADMUserData inUserData, ADMInt32 inOptions);

	// modal dialogs

	ADMInt32 ADMAPI (*Modal)(SPPluginRef inPluginRef, const char* inName,
				ADMInt32 inDialogID, ADMDialogStyle inDialogStyle,
				ADMDialogInitProc inInitProc, ADMUserData inUserData, ADMInt32 inOptions);

	ADMInt32 ADMAPI (*PopupModal)(SPPluginRef inPluginRef, const char* inName,
				ADMInt32 inDialogID, ADMDialogInitProc inInitProc, ADMUserData inUserData,
				ADMInt32 inOptions);

	ADMInt32 ADMAPI (*DisplayAsModal)(ADMDialogRef inDialog);

	// dialog destruction

	void ADMAPI (*Destroy)(ADMDialogRef inDialog);

	// dialog draw proc
	
	void ADMAPI (*SetDrawProc)(ADMDialogRef inDialog, ADMDialogDrawProc inDrawProc);
	ADMDialogDrawProc ADMAPI (*GetDrawProc)(ADMDialogRef inDialog);
	void ADMAPI (*DefaultDraw)(ADMDialogRef inDialog, ADMDrawerRef inDrawer);

	// dialog track proc
	
	void ADMAPI (*SetTrackProc)(ADMDialogRef inDialog, ADMDialogTrackProc inTrackProc);
	ADMDialogTrackProc ADMAPI (*GetTrackProc)(ADMDialogRef inDialog);
	ADMBoolean ADMAPI (*DefaultTrack)(ADMDialogRef inDialog, ADMTrackerRef inTracker);

	void ADMAPI (*SetMask)(ADMDialogRef inDialog, ADMActionMask inMask);
	ADMActionMask ADMAPI (*GetMask)(ADMDialogRef inDialog);

	// dialog notify proc

	void ADMAPI (*SetNotifyProc)(ADMDialogRef inDialog, ADMDialogNotifyProc inNotifyProc);
	ADMDialogNotifyProc ADMAPI (*GetNotifyProc)(ADMDialogRef inDialog);
	void ADMAPI (*DefaultNotify)(ADMDialogRef inDialog, ADMNotifierRef inNotifier);
	void ADMAPI (*SendNotify)(ADMDialogRef inDialog, const char* inNotifierType);

	void ADMAPI (*SetNotifierData)(ADMDialogRef inDialog, ADMUserData inUserData);
	ADMUserData ADMAPI (*GetNotifierData)(ADMDialogRef inDialog);

	// dialog destroy proc

	void ADMAPI (*SetDestroyProc)(ADMDialogRef inDialog, ADMDialogDestroyProc inDestroyProc);
	ADMDialogDestroyProc ADMAPI (*GetDestroyProc)(ADMDialogRef inDialog);

	// dialog timer
	
	ADMTimerRef ADMAPI (*CreateTimer)(ADMDialogRef inDialog, ADMUInt32 inMilliseconds,
				ADMActionMask inAbortMask, ADMDialogTimerProc inTimerProc,
				ADMDialogTimerAbortProc inAbortProc, ADMInt32 inOptions);
	
	void ADMAPI (*AbortTimer)(ADMDialogRef inDialog, ADMTimerRef inTimerID);

	// dialog user data

	void ADMAPI (*SetUserData)(ADMDialogRef inDialog, ADMUserData inUserData);
	ADMUserData ADMAPI (*GetUserData)(ADMDialogRef inDialog);

	// dialog information accessors

	ADMAPI const char* (*GetDialogName)(ADMDialogRef inDialog);
	ADMInt32 ADMAPI (*GetID)(ADMDialogRef inDialog);
	SPPluginRef ADMAPI (*GetPluginRef)(ADMDialogRef inDialog);
	ADMWindowRef ADMAPI (*GetWindowRef)(ADMDialogRef inDialog);
	
	void ADMAPI (*SetDialogStyle)(ADMDialogRef inDialog, ADMDialogStyle inDialogStyle);
	ADMDialogStyle ADMAPI (*GetDialogStyle)(ADMDialogRef inDialog);

	// dialog state accessors
	
	void ADMAPI (*Show)(ADMDialogRef inDialog, ADMBoolean inShow);
	ADMBoolean ADMAPI (*IsVisible)(ADMDialogRef inDialog);
	
	void ADMAPI (*Enable)(ADMDialogRef inDialog, ADMBoolean inEnable);
	ADMBoolean ADMAPI (*IsEnabled)(ADMDialogRef inDialog);
	
	void ADMAPI (*Activate)(ADMDialogRef inDialog, ADMBoolean inActivate);
	ADMBoolean ADMAPI (*IsActive)(ADMDialogRef inDialog);

	// dialog bounds accessors
	
	void ADMAPI (*SetLocalRect)(ADMDialogRef inDialog, const ADMRect* inLocalRect);
	void ADMAPI (*GetLocalRect)(ADMDialogRef inDialog, ADMRect* outLocalRect);
	
	void ADMAPI (*SetBoundsRect)(ADMDialogRef inDialog, const ADMRect* inBoundsRect);
	void ADMAPI (*GetBoundsRect)(ADMDialogRef inDialog, ADMRect* outBoundsRect);
	
	void ADMAPI (*Move)(ADMDialogRef inDialog, ADMInt32 inHorizPosition, ADMInt32 inVertPosition);
	void ADMAPI (*Size)(ADMDialogRef inDialog, ADMInt32 inWidth, ADMInt32 inHeight);

	// coordinate system transformations
	
	void ADMAPI (*LocalToScreenPoint)(ADMDialogRef inDialog, ADMPoint* ioPoint);
	void ADMAPI (*ScreenToLocalPoint)(ADMDialogRef inDialog, ADMPoint* ioPoint);
	
	void ADMAPI (*LocalToScreenRect)(ADMDialogRef inDialog, ADMRect* ioRect);
	void ADMAPI (*ScreenToLocalRect)(ADMDialogRef inDialog, ADMRect* ioRect);
	
	// dialog redraw requests
	
	void ADMAPI (*Invalidate)(ADMDialogRef inDialog);
	void ADMAPI (*InvalidateRect)(ADMDialogRef inDialog, const ADMRect* inInvalRect);
	void ADMAPI (*Update)(ADMDialogRef inDialog);

	// cursor ID accessors
	
	ADMBoolean ADMAPI (*SetCursorID)(ADMDialogRef inDialog, SPPluginRef inPluginRef,
				ADMInt32 inCursorID);

	void ADMAPI (*GetCursorID)(ADMDialogRef inDialog, SPPluginRef* outPluginRef,
				ADMInt32* outCursorID);

	// dialog text accessors

	void ADMAPI (*SetFont)(ADMDialogRef inDialog, ADMFont inFont);
	ADMFont ADMAPI (*GetFont)(ADMDialogRef inDialog);

	void ADMAPI (*SetText)(ADMDialogRef inDialog, const char* inText);
	void ADMAPI (*GetText)(ADMDialogRef inDialog, char* outText, ADMInt32 inMaxLength);
	ADMInt32 ADMAPI (*GetTextLength)(ADMDialogRef inDialog);
	
	// dialog size constraints
	
	void ADMAPI (*SetMinWidth)(ADMDialogRef inDialog, ADMInt32 inWidth);
	ADMInt32 ADMAPI (*GetMinWidth)(ADMDialogRef inDialog);
	
	void ADMAPI (*SetMinHeight)(ADMDialogRef inDialog, ADMInt32 inHeight);
	ADMInt32 ADMAPI (*GetMinHeight)(ADMDialogRef inDialog);
	
	void ADMAPI (*SetMaxWidth)(ADMDialogRef inDialog, ADMInt32 inWidth);
	ADMInt32 ADMAPI (*GetMaxWidth)(ADMDialogRef inDialog);
	
	void ADMAPI (*SetMaxHeight)(ADMDialogRef inDialog, ADMInt32 inHeight);
	ADMInt32 ADMAPI (*GetMaxHeight)(ADMDialogRef inDialog);
	
	void ADMAPI (*SetHorizontalIncrement)(ADMDialogRef inDialog, ADMInt32 inIncrement);
	ADMInt32 ADMAPI (*GetHorizontalIncrement)(ADMDialogRef inDialog);

	void ADMAPI (*SetVerticalIncrement)(ADMDialogRef inDialog, ADMInt32 inIncrement);
	ADMInt32 ADMAPI (*GetVerticalIncrement)(ADMDialogRef inDialog);
	
	// item accessors

	ADMItemRef ADMAPI (*GetItem)(ADMDialogRef inDialog, ADMInt32 inItemID);
	
	ADMItemRef ADMAPI (*CreateItem)(ADMDialogRef inDialog, ADMInt32 inItemID,
				ADMItemType inItemType, const ADMRect* inBoundsRect,
				ADMItemInitProc inInitProc, ADMUserData inUserData, ADMInt32 inOptions);

	void ADMAPI (*DestroyItem)(ADMDialogRef inDialog, ADMItemRef inItem);
	
	ADMItemRef ADMAPI (*GetNextItem)(ADMDialogRef inDialog, ADMItemRef inItem);
	ADMItemRef ADMAPI (*GetPreviousItem)(ADMDialogRef inDialog, ADMItemRef inItem);

	// default/cancel items

	void ADMAPI (*SetDefaultItemID)(ADMDialogRef inDialog, ADMInt32 inItemID);
	ADMInt32 ADMAPI (*GetDefaultItemID)(ADMDialogRef inDialog);

	void ADMAPI (*SetCancelItemID)(ADMDialogRef inDialog, ADMInt32 inItemID);
	ADMInt32 ADMAPI (*GetCancelItemID)(ADMDialogRef inDialog);
	
	ADMBoolean  ADMAPI (*EndModal)(ADMDialogRef inDialog, ADMInt32 inModalResultID,
				ADMBoolean inCancelling);

	// custom item types
	
	ADMErr ADMAPI (*RegisterItemType)(SPPluginRef inPluginRef, ADMItemType inItemType);
	ADMErr ADMAPI (*UnregisterItemType)(SPPluginRef inPluginRef, ADMItemType inItemType);

	// tooltips

	void ADMAPI (*LoadToolTips)(ADMDialogRef inDialog, ADMInt32 inStringID);

	// context help
	// dhearst 6/28/02 - ADM no longer supports ASHelp
	void ADMAPI (*SetHelpID_DEPRECATED)(ADMDialogRef inDialog, ADMInt32 inHelpID);
	ADMInt32 ADMAPI (*GetHelpID_DEPRECATED)(ADMDialogRef inDialog);
	void ADMAPI (*Help_DEPRECATED)(ADMDialogRef inDialog);

	// dialog state accessors

	ADMBoolean ADMAPI (*IsCollapsed)(ADMDialogRef inDialog);

	ADMItemRef ADMAPI (*CreateGroupInDialog)(ADMDialogRef inDialog, SPPluginRef inPluginRef,
				const char* inName, ADMInt32 inDialogID, ADMItemInitProc inInitProc,
				ADMUserData inUserData, ADMInt32 inOptions);

	void ADMAPI (*SetWindowRef)(ADMDialogRef inDialog, ADMWindowRef inWindowRef);
	
	ADMAPI void (*SetDialogName)(ADMDialogRef inDialog, const char* inName);

}
ADMDialogSuite4;


// =============================================================================
//		* ADM Dialog Suite, version 5
// =============================================================================

#define kADMDialogSuiteVersion5 5

// -----------------------------------------------------------------------------

typedef struct ADMDialogSuite5
{

	// *** This suite is FROZEN.
	// *** It shipped with Photoshop 5.5 and ImageReady 2.0.

	// dialog creation

	ADMDialogRef ADMAPI (*Create)(SPPluginRef inPluginRef, const char* inName,
				ADMInt32 inDialogID, ADMDialogStyle inDialogStyle,
				ADMDialogInitProc inInitProc, ADMUserData inUserData, ADMInt32 inOptions);

	// modal dialogs

	ADMInt32 ADMAPI (*Modal)(SPPluginRef inPluginRef, const char* inName,
				ADMInt32 inDialogID, ADMDialogStyle inDialogStyle,
				ADMDialogInitProc inInitProc, ADMUserData inUserData, ADMInt32 inOptions);

	ADMInt32 ADMAPI (*PopupModal)(SPPluginRef inPluginRef, const char* inName,
				ADMInt32 inDialogID, ADMDialogInitProc inInitProc, ADMUserData inUserData,
				ADMInt32 inOptions);

	ADMInt32 ADMAPI (*DisplayAsModal)(ADMDialogRef inDialog);

	// dialog destruction

	void ADMAPI (*Destroy)(ADMDialogRef inDialog);
	
	// dialog draw proc
	
	void ADMAPI (*SetDrawProc)(ADMDialogRef inDialog, ADMDialogDrawProc inDrawProc);
 	ADMDialogDrawProc ADMAPI (*GetDrawProc)(ADMDialogRef inDialog);
	void ADMAPI (*DefaultDraw)(ADMDialogRef inDialog, ADMDrawerRef inDrawer);

	// dialog track proc
	
	void ADMAPI (*SetTrackProc)(ADMDialogRef inDialog, ADMDialogTrackProc inTrackProc);
	ADMDialogTrackProc ADMAPI (*GetTrackProc)(ADMDialogRef inDialog);
	ADMBoolean ADMAPI (*DefaultTrack)(ADMDialogRef inDialog, ADMTrackerRef inTracker);

	void ADMAPI (*SetMask)(ADMDialogRef inDialog, ADMActionMask inMask);
	ADMActionMask ADMAPI (*GetMask)(ADMDialogRef inDialog);

	// dialog notify proc

	void ADMAPI (*SetNotifyProc)(ADMDialogRef inDialog, ADMDialogNotifyProc inNotifyProc);
	ADMDialogNotifyProc ADMAPI (*GetNotifyProc)(ADMDialogRef inDialog);
	void ADMAPI (*DefaultNotify)(ADMDialogRef inDialog, ADMNotifierRef inNotifier);
	void ADMAPI (*SendNotify)(ADMDialogRef inDialog, const char* inNotifierType);

	void ADMAPI (*SetNotifierData)(ADMDialogRef inDialog, ADMUserData inUserData);
	ADMUserData ADMAPI (*GetNotifierData)(ADMDialogRef inDialog);

	// dialog destroy proc

	void ADMAPI (*SetDestroyProc)(ADMDialogRef inDialog, ADMDialogDestroyProc inDestroyProc);
	ADMDialogDestroyProc ADMAPI (*GetDestroyProc)(ADMDialogRef inDialog);

	// dialog timer
	
	ADMTimerRef ADMAPI (*CreateTimer)(ADMDialogRef inDialog, ADMUInt32 inMilliseconds,
				ADMActionMask inAbortMask, ADMDialogTimerProc inTimerProc,
				ADMDialogTimerAbortProc inAbortProc, ADMInt32 inOptions);
	
	void ADMAPI (*AbortTimer)(ADMDialogRef inDialog, ADMTimerRef inTimerID);

	// dialog user data
	
	void ADMAPI (*SetUserData)(ADMDialogRef inDialog, ADMUserData inUserData);
	ADMUserData ADMAPI (*GetUserData)(ADMDialogRef inDialog);

	// dialog information accessors

	ADMAPI const char* (*GetDialogName)(ADMDialogRef inDialog);
	ADMInt32 ADMAPI (*GetID)(ADMDialogRef inDialog);
	SPPluginRef ADMAPI (*GetPluginRef)(ADMDialogRef inDialog);
	ADMWindowRef ADMAPI (*GetWindowRef)(ADMDialogRef inDialog);

	void ADMAPI (*SetDialogStyle)(ADMDialogRef inDialog, ADMDialogStyle inDialogStyle);
	ADMDialogStyle ADMAPI (*GetDialogStyle)(ADMDialogRef inDialog);

	// dialog state accessors
	
	void ADMAPI (*Show)(ADMDialogRef inDialog, ADMBoolean inShow);
	ADMBoolean ADMAPI (*IsVisible)(ADMDialogRef inDialog);
	
	void ADMAPI (*Enable)(ADMDialogRef inDialog, ADMBoolean inEnable);
	ADMBoolean ADMAPI (*IsEnabled)(ADMDialogRef inDialog);
	
	void ADMAPI (*Activate)(ADMDialogRef inDialog, ADMBoolean inActivate);
	ADMBoolean ADMAPI (*IsActive)(ADMDialogRef inDialog);
	
	// dialog bounds accessors
	
	void ADMAPI (*SetLocalRect)(ADMDialogRef inDialog, const ADMRect* inLocalRect);
	void ADMAPI (*GetLocalRect)(ADMDialogRef inDialog, ADMRect* outLocalRect);
	
	void ADMAPI (*SetBoundsRect)(ADMDialogRef inDialog, const ADMRect* inBoundsRect);
	void ADMAPI (*GetBoundsRect)(ADMDialogRef inDialog, ADMRect* outBoundsRect);
	
	void ADMAPI (*Move)(ADMDialogRef inDialog, ADMInt32 inHorizPosition, ADMInt32 inVertPosition);
	void ADMAPI (*Size)(ADMDialogRef inDialog, ADMInt32 inWidth, ADMInt32 inHeight);

	// coordinate system transformations
	
	void ADMAPI (*LocalToScreenPoint)(ADMDialogRef inDialog, ADMPoint* ioPoint);
	void ADMAPI (*ScreenToLocalPoint)(ADMDialogRef inDialog, ADMPoint* ioPoint);
	
	void ADMAPI (*LocalToScreenRect)(ADMDialogRef inDialog, ADMRect* ioRect);
	void ADMAPI (*ScreenToLocalRect)(ADMDialogRef inDialog, ADMRect* ioRect);

	// dialog redraw requests
	
	void ADMAPI (*Invalidate)(ADMDialogRef inDialog);
	void ADMAPI (*InvalidateRect)(ADMDialogRef inDialog, const ADMRect* inInvalRect);
	void ADMAPI (*Update)(ADMDialogRef inDialog);

	// cursor ID accessors

	ADMBoolean ADMAPI (*SetCursorID)(ADMDialogRef inDialog, SPPluginRef inPluginRef,
				ADMInt32 inCursorID);

	void ADMAPI (*GetCursorID)(ADMDialogRef inDialog, SPPluginRef* outPluginRef,
				ADMInt32* outCursorID);
	
	// dialog text accessors

	void ADMAPI (*SetFont)(ADMDialogRef inDialog, ADMFont inFont);
	ADMFont ADMAPI (*GetFont)(ADMDialogRef inDialog);

	void ADMAPI (*SetText)(ADMDialogRef inDialog, const char* inText);
	void ADMAPI (*GetText)(ADMDialogRef inDialog, char* outText, ADMInt32 inMaxLength);
	ADMInt32 ADMAPI (*GetTextLength)(ADMDialogRef inDialog);

	// dialog size constraints
	
	void ADMAPI (*SetMinWidth)(ADMDialogRef inDialog, ADMInt32 inWidth);
	ADMInt32 ADMAPI (*GetMinWidth)(ADMDialogRef inDialog);
	
	void ADMAPI (*SetMinHeight)(ADMDialogRef inDialog, ADMInt32 inHeight);
	ADMInt32 ADMAPI (*GetMinHeight)(ADMDialogRef inDialog);
	
	void ADMAPI (*SetMaxWidth)(ADMDialogRef inDialog, ADMInt32 inWidth);
	ADMInt32 ADMAPI (*GetMaxWidth)(ADMDialogRef inDialog);
	
	void ADMAPI (*SetMaxHeight)(ADMDialogRef inDialog, ADMInt32 inHeight);
	ADMInt32 ADMAPI (*GetMaxHeight)(ADMDialogRef inDialog);
	
	void ADMAPI (*SetHorizontalIncrement)(ADMDialogRef inDialog, ADMInt32 inIncrement);
	ADMInt32 ADMAPI (*GetHorizontalIncrement)(ADMDialogRef inDialog);

	void ADMAPI (*SetVerticalIncrement)(ADMDialogRef inDialog, ADMInt32 inIncrement);
	ADMInt32 ADMAPI (*GetVerticalIncrement)(ADMDialogRef inDialog);

	// item accessors

	ADMItemRef ADMAPI (*GetItem)(ADMDialogRef inDialog, ADMInt32 inItemID);
	
	ADMItemRef ADMAPI (*CreateItem)(ADMDialogRef inDialog, ADMInt32 inItemID,
				ADMItemType inItemType, const ADMRect* inBoundsRect,
				ADMItemInitProc inInitProc, ADMUserData inUserData, ADMInt32 inOptions);

	void ADMAPI (*DestroyItem)(ADMDialogRef inDialog, ADMItemRef inItem);
	
	ADMItemRef ADMAPI (*GetNextItem)(ADMDialogRef inDialog, ADMItemRef inItem);
	ADMItemRef ADMAPI (*GetPreviousItem)(ADMDialogRef inDialog, ADMItemRef inItem);

	// default/cancel items

	void ADMAPI (*SetDefaultItemID)(ADMDialogRef inDialog, ADMInt32 inItemID);
	ADMInt32 ADMAPI (*GetDefaultItemID)(ADMDialogRef inDialog);

	void ADMAPI (*SetCancelItemID)(ADMDialogRef inDialog, ADMInt32 inItemID);
	ADMInt32 ADMAPI (*GetCancelItemID)(ADMDialogRef inDialog);

	ADMBoolean ADMAPI (*EndModal)(ADMDialogRef inDialog, ADMInt32 inModalResultID,
				ADMBoolean inCancelling);
	
	// custom item types
	
	ADMErr ADMAPI (*RegisterItemType)(SPPluginRef inPluginRef, ADMItemType inItemType);
	ADMErr ADMAPI (*UnregisterItemType)(SPPluginRef inPluginRef, ADMItemType inItemType);

	// tooltips

	void ADMAPI (*LoadToolTips)(ADMDialogRef inDialog, ADMInt32 inStringID);

	// context help
	// dhearst 6/28/02 - ADM no longer supports ASHelp
	void ADMAPI (*SetHelpID_DEPRECATED)(ADMDialogRef inDialog, ADMInt32 inHelpID);
	ADMInt32 ADMAPI (*GetHelpID_DEPRECATED)(ADMDialogRef inDialog);
	void ADMAPI (*Help_DEPRECATED)(ADMDialogRef inDialog);

	// dialog state accessors	

	ADMBoolean ADMAPI (*IsCollapsed)(ADMDialogRef inDialog);

	ADMItemRef ADMAPI (*CreateGroupInDialog)(ADMDialogRef inDialog,
				SPPluginRef inPluginRef, const char* inName, ADMInt32 inDialogID,
				ADMItemInitProc inInitProc, ADMUserData inUserData, ADMInt32 inOptions);

	void ADMAPI (*SetWindowRef)(ADMDialogRef inDialog, ADMWindowRef inWindowRef);
	void ADMAPI (*SetDialogName)(ADMDialogRef inDialog, const char* inName);

	ADMBoolean ADMAPI (*IsDialogContextHidden)(ADMDialogRef inDialog);

}
ADMDialogSuite5;


// =============================================================================
//		* ADM Dialog Suite, version 6
// =============================================================================

#define kADMDialogSuiteVersion6 6

// -----------------------------------------------------------------------------

typedef struct ADMDialogSuite6
{

	// *** This suite is FROZEN.
	// *** It shipped with Illustrator 9.0.

	// dialog creation

	ADMDialogRef ADMAPI (*Create)(SPPluginRef inPluginRef, const char* inName,
				ADMInt32 inDialogID, ADMDialogStyle inDialogStyle,
				ADMDialogInitProc inInitProc, ADMUserData inUserData, ADMInt32 inOptions);

	// modal dialogs

	ADMInt32 ADMAPI (*Modal)(SPPluginRef inPluginRef, const char* inName,
				ADMInt32 inDialogID, ADMDialogStyle inDialogStyle,
				ADMDialogInitProc inInitProc, ADMUserData inUserData, ADMInt32 inOptions);

	ADMInt32 ADMAPI (*PopupModal)(SPPluginRef inPluginRef, const char* inName,
				ADMInt32 inDialogID, ADMDialogInitProc inInitProc, ADMUserData inUserData,
				ADMInt32 inOptions);

	ADMInt32 ADMAPI (*DisplayAsModal)(ADMDialogRef inDialog);

	// dialog destruction

	void ADMAPI (*Destroy)(ADMDialogRef inDialog);
	
	// dialog draw proc
	
	void ADMAPI (*SetDrawProc)(ADMDialogRef inDialog, ADMDialogDrawProc inDrawProc);
 	ADMDialogDrawProc ADMAPI (*GetDrawProc)(ADMDialogRef inDialog);
	void ADMAPI (*DefaultDraw)(ADMDialogRef inDialog, ADMDrawerRef inDrawer);

	// dialog track proc
	
	void ADMAPI (*SetTrackProc)(ADMDialogRef inDialog, ADMDialogTrackProc inTrackProc);
	ADMDialogTrackProc ADMAPI (*GetTrackProc)(ADMDialogRef inDialog);
	ADMBoolean ADMAPI (*DefaultTrack)(ADMDialogRef inDialog, ADMTrackerRef inTracker);

	void ADMAPI (*SetMask)(ADMDialogRef inDialog, ADMActionMask inMask);
	ADMActionMask ADMAPI (*GetMask)(ADMDialogRef inDialog);

	// dialog notify proc

	void ADMAPI (*SetNotifyProc)(ADMDialogRef inDialog, ADMDialogNotifyProc inNotifyProc);
	ADMDialogNotifyProc ADMAPI (*GetNotifyProc)(ADMDialogRef inDialog);
	void ADMAPI (*DefaultNotify)(ADMDialogRef inDialog, ADMNotifierRef inNotifier);
	void ADMAPI (*SendNotify)(ADMDialogRef inDialog, const char* inNotifierType);

	void ADMAPI (*SetNotifierData)(ADMDialogRef inDialog, ADMUserData inUserData);
	ADMUserData ADMAPI (*GetNotifierData)(ADMDialogRef inDialog);

	// dialog destroy proc

	void ADMAPI (*SetDestroyProc)(ADMDialogRef inDialog, ADMDialogDestroyProc inDestroyProc);
	ADMDialogDestroyProc ADMAPI (*GetDestroyProc)(ADMDialogRef inDialog);

	// dialog timer
	
	ADMTimerRef ADMAPI (*CreateTimer)(ADMDialogRef inDialog, ADMUInt32 inMilliseconds,
				ADMActionMask inAbortMask, ADMDialogTimerProc inTimerProc,
				ADMDialogTimerAbortProc inAbortProc, ADMInt32 inOptions);
	
	void ADMAPI (*AbortTimer)(ADMDialogRef inDialog, ADMTimerRef inTimerID);

	// dialog user data
	
	void ADMAPI (*SetUserData)(ADMDialogRef inDialog, ADMUserData inUserData);
	ADMUserData ADMAPI (*GetUserData)(ADMDialogRef inDialog);

	// dialog information accessors

	ADMAPI const char* (*GetDialogName)(ADMDialogRef inDialog);
	ADMInt32 ADMAPI (*GetID)(ADMDialogRef inDialog);
	SPPluginRef ADMAPI (*GetPluginRef)(ADMDialogRef inDialog);
	ADMWindowRef ADMAPI (*GetWindowRef)(ADMDialogRef inDialog);

	void ADMAPI (*SetDialogStyle)(ADMDialogRef inDialog, ADMDialogStyle inDialogStyle);
	ADMDialogStyle ADMAPI (*GetDialogStyle)(ADMDialogRef inDialog);

	// dialog state accessors
	
	void ADMAPI (*Show)(ADMDialogRef inDialog, ADMBoolean inShow);
	ADMBoolean ADMAPI (*IsVisible)(ADMDialogRef inDialog);
	
	void ADMAPI (*Enable)(ADMDialogRef inDialog, ADMBoolean inEnable);
	ADMBoolean ADMAPI (*IsEnabled)(ADMDialogRef inDialog);
	
	void ADMAPI (*Activate)(ADMDialogRef inDialog, ADMBoolean inActivate);
	ADMBoolean ADMAPI (*IsActive)(ADMDialogRef inDialog);
	
	// dialog bounds accessors
	
	void ADMAPI (*SetLocalRect)(ADMDialogRef inDialog, const ADMRect* inLocalRect);
	void ADMAPI (*GetLocalRect)(ADMDialogRef inDialog, ADMRect* outLocalRect);
	
	void ADMAPI (*SetBoundsRect)(ADMDialogRef inDialog, const ADMRect* inBoundsRect);
	void ADMAPI (*GetBoundsRect)(ADMDialogRef inDialog, ADMRect* outBoundsRect);
	
	void ADMAPI (*Move)(ADMDialogRef inDialog, ADMInt32 inHorizPosition, ADMInt32 inVertPosition);
	void ADMAPI (*Size)(ADMDialogRef inDialog, ADMInt32 inWidth, ADMInt32 inHeight);

	// coordinate system transformations
	
	void ADMAPI (*LocalToScreenPoint)(ADMDialogRef inDialog, ADMPoint* ioPoint);
	void ADMAPI (*ScreenToLocalPoint)(ADMDialogRef inDialog, ADMPoint* ioPoint);
	
	void ADMAPI (*LocalToScreenRect)(ADMDialogRef inDialog, ADMRect* ioRect);
	void ADMAPI (*ScreenToLocalRect)(ADMDialogRef inDialog, ADMRect* ioRect);

	// dialog redraw requests
	
	void ADMAPI (*Invalidate)(ADMDialogRef inDialog);
	void ADMAPI (*InvalidateRect)(ADMDialogRef inDialog, const ADMRect* inInvalRect);
	void ADMAPI (*Update)(ADMDialogRef inDialog);

	// cursor ID accessors

	ADMBoolean ADMAPI (*SetCursorID)(ADMDialogRef inDialog, SPPluginRef inPluginRef,
				ADMInt32 inCursorID);

	void ADMAPI (*GetCursorID)(ADMDialogRef inDialog, SPPluginRef* outPluginRef,
				ADMInt32* outCursorID);
	
	// dialog text accessors

	void ADMAPI (*SetFont)(ADMDialogRef inDialog, ADMFont inFont);
	ADMFont ADMAPI (*GetFont)(ADMDialogRef inDialog);

	void ADMAPI (*SetText)(ADMDialogRef inDialog, const char* inText);
	void ADMAPI (*GetText)(ADMDialogRef inDialog, char* outText, ADMInt32 inMaxLength);
	ADMInt32 ADMAPI (*GetTextLength)(ADMDialogRef inDialog);

	// dialog size constraints
	
	void ADMAPI (*SetMinWidth)(ADMDialogRef inDialog, ADMInt32 inWidth);
	ADMInt32 ADMAPI (*GetMinWidth)(ADMDialogRef inDialog);
	
	void ADMAPI (*SetMinHeight)(ADMDialogRef inDialog, ADMInt32 inHeight);
	ADMInt32 ADMAPI (*GetMinHeight)(ADMDialogRef inDialog);
	
	void ADMAPI (*SetMaxWidth)(ADMDialogRef inDialog, ADMInt32 inWidth);
	ADMInt32 ADMAPI (*GetMaxWidth)(ADMDialogRef inDialog);
	
	void ADMAPI (*SetMaxHeight)(ADMDialogRef inDialog, ADMInt32 inHeight);
	ADMInt32 ADMAPI (*GetMaxHeight)(ADMDialogRef inDialog);
	
	void ADMAPI (*SetHorizontalIncrement)(ADMDialogRef inDialog, ADMInt32 inIncrement);
	ADMInt32 ADMAPI (*GetHorizontalIncrement)(ADMDialogRef inDialog);

	void ADMAPI (*SetVerticalIncrement)(ADMDialogRef inDialog, ADMInt32 inIncrement);
	ADMInt32 ADMAPI (*GetVerticalIncrement)(ADMDialogRef inDialog);

	// item accessors

	ADMItemRef ADMAPI (*GetItem)(ADMDialogRef inDialog, ADMInt32 inItemID);
	
	ADMItemRef ADMAPI (*CreateItem)(ADMDialogRef inDialog, ADMInt32 inItemID,
				ADMItemType inItemType, const ADMRect* inBoundsRect,
				ADMItemInitProc inInitProc, ADMUserData inUserData, ADMInt32 inOptions);

	void ADMAPI (*DestroyItem)(ADMDialogRef inDialog, ADMItemRef inItem);
	
	ADMItemRef ADMAPI (*GetNextItem)(ADMDialogRef inDialog, ADMItemRef inItem);
	ADMItemRef ADMAPI (*GetPreviousItem)(ADMDialogRef inDialog, ADMItemRef inItem);

	// default/cancel items

	void ADMAPI (*SetDefaultItemID)(ADMDialogRef inDialog, ADMInt32 inItemID);
	ADMInt32 ADMAPI (*GetDefaultItemID)(ADMDialogRef inDialog);

	void ADMAPI (*SetCancelItemID)(ADMDialogRef inDialog, ADMInt32 inItemID);
	ADMInt32 ADMAPI (*GetCancelItemID)(ADMDialogRef inDialog);

	ADMBoolean ADMAPI (*EndModal)(ADMDialogRef inDialog, ADMInt32 inModalResultID,
				ADMBoolean inCancelling);
	
	// custom item types
	
	ADMErr ADMAPI (*RegisterItemType)(SPPluginRef inPluginRef, ADMItemType inItemType);
	ADMErr ADMAPI (*UnregisterItemType)(SPPluginRef inPluginRef, ADMItemType inItemType);

	// tooltips

	void ADMAPI (*LoadToolTips)(ADMDialogRef inDialog, ADMInt32 inStringID);

	// context help
	// dhearst 6/28/02 - ADM no longer supports ASHelp
	void ADMAPI (*SetHelpID_DEPRECATED)(ADMDialogRef inDialog, ADMInt32 inHelpID);
	ADMInt32 ADMAPI (*GetHelpID_DEPRECATED)(ADMDialogRef inDialog);
	void ADMAPI (*Help_DEPRECATED)(ADMDialogRef inDialog);

	// dialog state accessors	

	ADMBoolean ADMAPI (*IsCollapsed)(ADMDialogRef inDialog);

	ADMItemRef ADMAPI (*CreateGroupInDialog)(ADMDialogRef inDialog,
				SPPluginRef inPluginRef, const char* inName, ADMInt32 inDialogID,
				ADMItemInitProc inInitProc, ADMUserData inUserData, ADMInt32 inOptions);

	void ADMAPI (*SetWindowRef)(ADMDialogRef inDialog, ADMWindowRef inWindowRef);
	void ADMAPI (*SetDialogName)(ADMDialogRef inDialog, const char* inName);

	ADMBoolean ADMAPI (*IsDialogContextHidden)(ADMDialogRef inDialog);

	void ADMAPI (*SetUpdateEnabled)(ADMDialogRef inDialog, ADMBoolean inEnableUpdate);
	ADMBoolean ADMAPI (*IsUpdateEnabled)(ADMDialogRef inDialog);
	
	void ADMAPI (*SetForcedOnScreen)(ADMDialogRef ioDialog,
				ADMBoolean inForcedOnScreen);
	ADMBoolean ADMAPI (*IsForcedOnScreen)(ADMDialogRef inDialog);

	ADMInt32 ADMAPI (*DisplayAsPopupModal)(ADMDialogRef inDialog);

}
ADMDialogSuite6;


// =============================================================================
//		* ADM Dialog Suite, version 7
// =============================================================================

#define kADMDialogSuiteVersion7 7

// -----------------------------------------------------------------------------

typedef struct ADMDialogSuite7
{

	// *** This suite is FROZEN for changes.
	// *** It shipped with Acrobat 5.0, After Effects 5.0

	// dialog creation

	ADMDialogRef ADMAPI (*Create)(SPPluginRef inPluginRef, const char* inName,
				ADMInt32 inDialogID, ADMDialogStyle inDialogStyle,
				ADMDialogInitProc inInitProc, ADMUserData inUserData, ADMInt32 inOptions);

	// modal dialogs

	ADMInt32 ADMAPI (*Modal)(SPPluginRef inPluginRef, const char* inName,
				ADMInt32 inDialogID, ADMDialogStyle inDialogStyle,
				ADMDialogInitProc inInitProc, ADMUserData inUserData, ADMInt32 inOptions);

	ADMInt32 ADMAPI (*PopupModal)(SPPluginRef inPluginRef, const char* inName,
				ADMInt32 inDialogID, ADMDialogInitProc inInitProc, ADMUserData inUserData,
				ADMInt32 inOptions);

	ADMInt32 ADMAPI (*DisplayAsModal)(ADMDialogRef inDialog);

	// dialog destruction

	void ADMAPI (*Destroy)(ADMDialogRef inDialog);
	
	// dialog draw proc
	
	void ADMAPI (*SetDrawProc)(ADMDialogRef inDialog, ADMDialogDrawProc inDrawProc);
 	ADMDialogDrawProc ADMAPI (*GetDrawProc)(ADMDialogRef inDialog);
	void ADMAPI (*DefaultDraw)(ADMDialogRef inDialog, ADMDrawerRef inDrawer);

	// dialog track proc
	
	void ADMAPI (*SetTrackProc)(ADMDialogRef inDialog, ADMDialogTrackProc inTrackProc);
	ADMDialogTrackProc ADMAPI (*GetTrackProc)(ADMDialogRef inDialog);
	ADMBoolean ADMAPI (*DefaultTrack)(ADMDialogRef inDialog, ADMTrackerRef inTracker);

	void ADMAPI (*SetMask)(ADMDialogRef inDialog, ADMActionMask inMask);
	ADMActionMask ADMAPI (*GetMask)(ADMDialogRef inDialog);

	// dialog notify proc

	void ADMAPI (*SetNotifyProc)(ADMDialogRef inDialog, ADMDialogNotifyProc inNotifyProc);
	ADMDialogNotifyProc ADMAPI (*GetNotifyProc)(ADMDialogRef inDialog);
	void ADMAPI (*DefaultNotify)(ADMDialogRef inDialog, ADMNotifierRef inNotifier);
	void ADMAPI (*SendNotify)(ADMDialogRef inDialog, const char* inNotifierType);

	void ADMAPI (*SetNotifierData)(ADMDialogRef inDialog, ADMUserData inUserData);
	ADMUserData ADMAPI (*GetNotifierData)(ADMDialogRef inDialog);

	// dialog destroy proc

	void ADMAPI (*SetDestroyProc)(ADMDialogRef inDialog, ADMDialogDestroyProc inDestroyProc);
	ADMDialogDestroyProc ADMAPI (*GetDestroyProc)(ADMDialogRef inDialog);

	// dialog timer
	
	ADMTimerRef ADMAPI (*CreateTimer)(ADMDialogRef inDialog, ADMUInt32 inMilliseconds,
				ADMActionMask inAbortMask, ADMDialogTimerProc inTimerProc,
				ADMDialogTimerAbortProc inAbortProc, ADMInt32 inOptions);
	
	void ADMAPI (*AbortTimer)(ADMDialogRef inDialog, ADMTimerRef inTimerID);

	// dialog user data
	
	void ADMAPI (*SetUserData)(ADMDialogRef inDialog, ADMUserData inUserData);
	ADMUserData ADMAPI (*GetUserData)(ADMDialogRef inDialog);

	// dialog information accessors

	ADMAPI const char* (*GetDialogName)(ADMDialogRef inDialog);
	ADMInt32 ADMAPI (*GetID)(ADMDialogRef inDialog);
	SPPluginRef ADMAPI (*GetPluginRef)(ADMDialogRef inDialog);
	ADMWindowRef ADMAPI (*GetWindowRef)(ADMDialogRef inDialog);

	void ADMAPI (*SetDialogStyle)(ADMDialogRef inDialog, ADMDialogStyle inDialogStyle);
	ADMDialogStyle ADMAPI (*GetDialogStyle)(ADMDialogRef inDialog);

	// dialog state accessors
	
	void ADMAPI (*Show)(ADMDialogRef inDialog, ADMBoolean inShow);
	ADMBoolean ADMAPI (*IsVisible)(ADMDialogRef inDialog);
	
	void ADMAPI (*Enable)(ADMDialogRef inDialog, ADMBoolean inEnable);
	ADMBoolean ADMAPI (*IsEnabled)(ADMDialogRef inDialog);
	
	void ADMAPI (*Activate)(ADMDialogRef inDialog, ADMBoolean inActivate);
	ADMBoolean ADMAPI (*IsActive)(ADMDialogRef inDialog);
	
	// dialog bounds accessors
	
	void ADMAPI (*SetLocalRect)(ADMDialogRef inDialog, const ADMRect* inLocalRect);
	void ADMAPI (*GetLocalRect)(ADMDialogRef inDialog, ADMRect* outLocalRect);
	
	void ADMAPI (*SetBoundsRect)(ADMDialogRef inDialog, const ADMRect* inBoundsRect);
	void ADMAPI (*GetBoundsRect)(ADMDialogRef inDialog, ADMRect* outBoundsRect);
	
	void ADMAPI (*Move)(ADMDialogRef inDialog, ADMInt32 inHorizPosition, ADMInt32 inVertPosition);
	void ADMAPI (*Size)(ADMDialogRef inDialog, ADMInt32 inWidth, ADMInt32 inHeight);

	// coordinate system transformations
	
	void ADMAPI (*LocalToScreenPoint)(ADMDialogRef inDialog, ADMPoint* ioPoint);
	void ADMAPI (*ScreenToLocalPoint)(ADMDialogRef inDialog, ADMPoint* ioPoint);
	
	void ADMAPI (*LocalToScreenRect)(ADMDialogRef inDialog, ADMRect* ioRect);
	void ADMAPI (*ScreenToLocalRect)(ADMDialogRef inDialog, ADMRect* ioRect);

	// dialog redraw requests
	
	void ADMAPI (*Invalidate)(ADMDialogRef inDialog);
	void ADMAPI (*InvalidateRect)(ADMDialogRef inDialog, const ADMRect* inInvalRect);
	void ADMAPI (*Update)(ADMDialogRef inDialog);

	// cursor ID accessors

	ADMBoolean ADMAPI (*SetCursorID)(ADMDialogRef inDialog, SPPluginRef inPluginRef,
				ADMInt32 inCursorID);

	void ADMAPI (*GetCursorID)(ADMDialogRef inDialog, SPPluginRef* outPluginRef,
				ADMInt32* outCursorID);
	
	// dialog text accessors

	void ADMAPI (*SetFont)(ADMDialogRef inDialog, ADMFont inFont);
	ADMFont ADMAPI (*GetFont)(ADMDialogRef inDialog);

	void ADMAPI (*SetText)(ADMDialogRef inDialog, const char* inText);
	void ADMAPI (*SetTextW)(ADMDialogRef inDialog, const ADMUnicode* inText);

	void ADMAPI (*GetText)(ADMDialogRef inDialog, char* outText, ADMInt32 inMaxLength);
	void ADMAPI (*GetTextW)(ADMDialogRef inDialog, ADMUnicode* outText, ADMInt32 inMaxLength);

	ADMInt32 ADMAPI (*GetTextLength)(ADMDialogRef inDialog);
	ADMInt32 ADMAPI (*GetTextLengthW)(ADMDialogRef inDialog);

	// dialog size constraints
	
	void ADMAPI (*SetMinWidth)(ADMDialogRef inDialog, ADMInt32 inWidth);
	ADMInt32 ADMAPI (*GetMinWidth)(ADMDialogRef inDialog);
	
	void ADMAPI (*SetMinHeight)(ADMDialogRef inDialog, ADMInt32 inHeight);
	ADMInt32 ADMAPI (*GetMinHeight)(ADMDialogRef inDialog);
	
	void ADMAPI (*SetMaxWidth)(ADMDialogRef inDialog, ADMInt32 inWidth);
	ADMInt32 ADMAPI (*GetMaxWidth)(ADMDialogRef inDialog);
	
	void ADMAPI (*SetMaxHeight)(ADMDialogRef inDialog, ADMInt32 inHeight);
	ADMInt32 ADMAPI (*GetMaxHeight)(ADMDialogRef inDialog);
	
	void ADMAPI (*SetHorizontalIncrement)(ADMDialogRef inDialog, ADMInt32 inIncrement);
	ADMInt32 ADMAPI (*GetHorizontalIncrement)(ADMDialogRef inDialog);

	void ADMAPI (*SetVerticalIncrement)(ADMDialogRef inDialog, ADMInt32 inIncrement);
	ADMInt32 ADMAPI (*GetVerticalIncrement)(ADMDialogRef inDialog);

	// item accessors

	ADMItemRef ADMAPI (*GetItem)(ADMDialogRef inDialog, ADMInt32 inItemID);
	
	ADMItemRef ADMAPI (*CreateItem)(ADMDialogRef inDialog, ADMInt32 inItemID,
				ADMItemType inItemType, const ADMRect* inBoundsRect,
				ADMItemInitProc inInitProc, ADMUserData inUserData, ADMInt32 inOptions);

	void ADMAPI (*DestroyItem)(ADMDialogRef inDialog, ADMItemRef inItem);
	
	ADMItemRef ADMAPI (*GetNextItem)(ADMDialogRef inDialog, ADMItemRef inItem);
	ADMItemRef ADMAPI (*GetPreviousItem)(ADMDialogRef inDialog, ADMItemRef inItem);

	// default/cancel items

	void ADMAPI (*SetDefaultItemID)(ADMDialogRef inDialog, ADMInt32 inItemID);
	ADMInt32 ADMAPI (*GetDefaultItemID)(ADMDialogRef inDialog);

	void ADMAPI (*SetCancelItemID)(ADMDialogRef inDialog, ADMInt32 inItemID);
	ADMInt32 ADMAPI (*GetCancelItemID)(ADMDialogRef inDialog);

	ADMBoolean ADMAPI (*EndModal)(ADMDialogRef inDialog, ADMInt32 inModalResultID,
				ADMBoolean inCancelling);
	
	// custom item types
	
	ADMErr ADMAPI (*RegisterItemType)(SPPluginRef inPluginRef, ADMItemType inItemType);
	ADMErr ADMAPI (*UnregisterItemType)(SPPluginRef inPluginRef, ADMItemType inItemType);

	// tooltips

	void ADMAPI (*LoadToolTips)(ADMDialogRef inDialog, ADMInt32 inStringID);

	// context help
	// dhearst 6/28/02 - ADM no longer supports ASHelp
	void ADMAPI (*SetHelpID_DEPRECATED)(ADMDialogRef inDialog, ADMInt32 inHelpID);
	ADMInt32 ADMAPI (*GetHelpID_DEPRECATED)(ADMDialogRef inDialog);
	void ADMAPI (*Help_DEPRECATED)(ADMDialogRef inDialog);

	// dialog state accessors	

	ADMBoolean ADMAPI (*IsCollapsed)(ADMDialogRef inDialog);

	ADMItemRef ADMAPI (*CreateGroupInDialog)(ADMDialogRef inDialog,
				SPPluginRef inPluginRef, const char* inName, ADMInt32 inDialogID,
				ADMItemInitProc inInitProc, ADMUserData inUserData, ADMInt32 inOptions);

	void ADMAPI (*SetWindowRef)(ADMDialogRef inDialog, ADMWindowRef inWindowRef);
	void ADMAPI (*SetDialogName)(ADMDialogRef inDialog, const char* inName);

	ADMBoolean ADMAPI (*IsDialogContextHidden)(ADMDialogRef inDialog);

	void ADMAPI (*SetUpdateEnabled)(ADMDialogRef inDialog, ADMBoolean inEnableUpdate);
	ADMBoolean ADMAPI (*IsUpdateEnabled)(ADMDialogRef inDialog);
	
	void ADMAPI (*SetForcedOnScreen)(ADMDialogRef ioDialog,
				ADMBoolean inForcedOnScreen);
	ADMBoolean ADMAPI (*IsForcedOnScreen)(ADMDialogRef inDialog);

	ADMInt32 ADMAPI (*DisplayAsPopupModal)(ADMDialogRef inDialog);

}
ADMDialogSuite7;


// =============================================================================
//		* ADM Dialog Suite, version 8
// =============================================================================

#define kADMDialogSuiteVersion8 8

// -----------------------------------------------------------------------------

typedef struct ADMDialogSuite8
{

	// *** This suite is FROZEN.
	// *** It shipped with Illustrator10 and Photoshop 7.

	// dialog creation

	ADMDialogRef ADMAPI (*Create)(SPPluginRef inPluginRef, const char* inName,
				ADMInt32 inDialogID, ADMDialogStyle inDialogStyle,
				ADMDialogInitProc inInitProc, ADMUserData inUserData, ADMInt32 inOptions);

	// modal dialogs

	ADMInt32 ADMAPI (*Modal)(SPPluginRef inPluginRef, const char* inName,
				ADMInt32 inDialogID, ADMDialogStyle inDialogStyle,
				ADMDialogInitProc inInitProc, ADMUserData inUserData, ADMInt32 inOptions);

	ADMInt32 ADMAPI (*PopupModal)(SPPluginRef inPluginRef, const char* inName,
				ADMInt32 inDialogID, ADMDialogInitProc inInitProc, ADMUserData inUserData,
				ADMInt32 inOptions);

	ADMInt32 ADMAPI (*DisplayAsModal)(ADMDialogRef inDialog);

	// dialog destruction

	void ADMAPI (*Destroy)(ADMDialogRef inDialog);
	
	// dialog draw proc
	
	void ADMAPI (*SetDrawProc)(ADMDialogRef inDialog, ADMDialogDrawProc inDrawProc);
 	ADMDialogDrawProc ADMAPI (*GetDrawProc)(ADMDialogRef inDialog);
	void ADMAPI (*DefaultDraw)(ADMDialogRef inDialog, ADMDrawerRef inDrawer);

	// dialog track proc
	
	void ADMAPI (*SetTrackProc)(ADMDialogRef inDialog, ADMDialogTrackProc inTrackProc);
	ADMDialogTrackProc ADMAPI (*GetTrackProc)(ADMDialogRef inDialog);
	ADMBoolean ADMAPI (*DefaultTrack)(ADMDialogRef inDialog, ADMTrackerRef inTracker);

	void ADMAPI (*SetMask)(ADMDialogRef inDialog, ADMActionMask inMask);
	ADMActionMask ADMAPI (*GetMask)(ADMDialogRef inDialog);

	// dialog notify proc

	void ADMAPI (*SetNotifyProc)(ADMDialogRef inDialog, ADMDialogNotifyProc inNotifyProc);
	ADMDialogNotifyProc ADMAPI (*GetNotifyProc)(ADMDialogRef inDialog);
	void ADMAPI (*DefaultNotify)(ADMDialogRef inDialog, ADMNotifierRef inNotifier);
	void ADMAPI (*SendNotify)(ADMDialogRef inDialog, const char* inNotifierType);

	void ADMAPI (*SetNotifierData)(ADMDialogRef inDialog, ADMUserData inUserData);
	ADMUserData ADMAPI (*GetNotifierData)(ADMDialogRef inDialog);

	// dialog destroy proc

	void ADMAPI (*SetDestroyProc)(ADMDialogRef inDialog, ADMDialogDestroyProc inDestroyProc);
	ADMDialogDestroyProc ADMAPI (*GetDestroyProc)(ADMDialogRef inDialog);

	// dialog timer
	
	ADMTimerRef ADMAPI (*CreateTimer)(ADMDialogRef inDialog, ADMUInt32 inMilliseconds,
				ADMActionMask inAbortMask, ADMDialogTimerProc inTimerProc,
				ADMDialogTimerAbortProc inAbortProc, ADMInt32 inOptions);
	
	void ADMAPI (*AbortTimer)(ADMDialogRef inDialog, ADMTimerRef inTimerID);

	// dialog user data
	
	void ADMAPI (*SetUserData)(ADMDialogRef inDialog, ADMUserData inUserData);
	ADMUserData ADMAPI (*GetUserData)(ADMDialogRef inDialog);

	// dialog information accessors

	ADMAPI const char* (*GetDialogName)(ADMDialogRef inDialog);
	ADMInt32 ADMAPI (*GetID)(ADMDialogRef inDialog);
	SPPluginRef ADMAPI (*GetPluginRef)(ADMDialogRef inDialog);
	ADMWindowRef ADMAPI (*GetWindowRef)(ADMDialogRef inDialog);

	void ADMAPI (*SetDialogStyle)(ADMDialogRef inDialog, ADMDialogStyle inDialogStyle);
	ADMDialogStyle ADMAPI (*GetDialogStyle)(ADMDialogRef inDialog);

	// dialog state accessors
	
	void ADMAPI (*Show)(ADMDialogRef inDialog, ADMBoolean inShow);
	ADMBoolean ADMAPI (*IsVisible)(ADMDialogRef inDialog);
	
	void ADMAPI (*Enable)(ADMDialogRef inDialog, ADMBoolean inEnable);
	ADMBoolean ADMAPI (*IsEnabled)(ADMDialogRef inDialog);
	
	void ADMAPI (*Activate)(ADMDialogRef inDialog, ADMBoolean inActivate);
	ADMBoolean ADMAPI (*IsActive)(ADMDialogRef inDialog);
	
	// dialog bounds accessors
	
	void ADMAPI (*SetLocalRect)(ADMDialogRef inDialog, const ADMRect* inLocalRect);
	void ADMAPI (*GetLocalRect)(ADMDialogRef inDialog, ADMRect* outLocalRect);
	
	void ADMAPI (*SetBoundsRect)(ADMDialogRef inDialog, const ADMRect* inBoundsRect);
	void ADMAPI (*GetBoundsRect)(ADMDialogRef inDialog, ADMRect* outBoundsRect);
	
	void ADMAPI (*Move)(ADMDialogRef inDialog, ADMInt32 inHorizPosition, ADMInt32 inVertPosition);
	void ADMAPI (*Size)(ADMDialogRef inDialog, ADMInt32 inWidth, ADMInt32 inHeight);

	// coordinate system transformations
	
	void ADMAPI (*LocalToScreenPoint)(ADMDialogRef inDialog, ADMPoint* ioPoint);
	void ADMAPI (*ScreenToLocalPoint)(ADMDialogRef inDialog, ADMPoint* ioPoint);
	
	void ADMAPI (*LocalToScreenRect)(ADMDialogRef inDialog, ADMRect* ioRect);
	void ADMAPI (*ScreenToLocalRect)(ADMDialogRef inDialog, ADMRect* ioRect);

	// dialog redraw requests
	
	void ADMAPI (*Invalidate)(ADMDialogRef inDialog);
	void ADMAPI (*InvalidateRect)(ADMDialogRef inDialog, const ADMRect* inInvalRect);
	void ADMAPI (*Update)(ADMDialogRef inDialog);

	// cursor ID accessors

	ADMBoolean ADMAPI (*SetCursorID)(ADMDialogRef inDialog, SPPluginRef inPluginRef,
				ADMInt32 inCursorID);

	void ADMAPI (*GetCursorID)(ADMDialogRef inDialog, SPPluginRef* outPluginRef,
				ADMInt32* outCursorID);
	
	// dialog text accessors

	void ADMAPI (*SetFont)(ADMDialogRef inDialog, ADMFont inFont);
	ADMFont ADMAPI (*GetFont)(ADMDialogRef inDialog);

	void ADMAPI (*SetText)(ADMDialogRef inDialog, const char* inText);
	void ADMAPI (*SetTextW)(ADMDialogRef inDialog, const ADMUnicode* inText);

	void ADMAPI (*GetText)(ADMDialogRef inDialog, char* outText, ADMInt32 inMaxLength);
	void ADMAPI (*GetTextW)(ADMDialogRef inDialog, ADMUnicode* outText, ADMInt32 inMaxLength);

	ADMInt32 ADMAPI (*GetTextLength)(ADMDialogRef inDialog);
	ADMInt32 ADMAPI (*GetTextLengthW)(ADMDialogRef inDialog);

	// dialog size constraints
	
	void ADMAPI (*SetMinWidth)(ADMDialogRef inDialog, ADMInt32 inWidth);
	ADMInt32 ADMAPI (*GetMinWidth)(ADMDialogRef inDialog);
	
	void ADMAPI (*SetMinHeight)(ADMDialogRef inDialog, ADMInt32 inHeight);
	ADMInt32 ADMAPI (*GetMinHeight)(ADMDialogRef inDialog);
	
	void ADMAPI (*SetMaxWidth)(ADMDialogRef inDialog, ADMInt32 inWidth);
	ADMInt32 ADMAPI (*GetMaxWidth)(ADMDialogRef inDialog);
	
	void ADMAPI (*SetMaxHeight)(ADMDialogRef inDialog, ADMInt32 inHeight);
	ADMInt32 ADMAPI (*GetMaxHeight)(ADMDialogRef inDialog);
	
	void ADMAPI (*SetHorizontalIncrement)(ADMDialogRef inDialog, ADMInt32 inIncrement);
	ADMInt32 ADMAPI (*GetHorizontalIncrement)(ADMDialogRef inDialog);

	void ADMAPI (*SetVerticalIncrement)(ADMDialogRef inDialog, ADMInt32 inIncrement);
	ADMInt32 ADMAPI (*GetVerticalIncrement)(ADMDialogRef inDialog);

	// item accessors

	ADMItemRef ADMAPI (*GetItem)(ADMDialogRef inDialog, ADMInt32 inItemID);
	
	ADMItemRef ADMAPI (*CreateItem)(ADMDialogRef inDialog, ADMInt32 inItemID,
				ADMItemType inItemType, const ADMRect* inBoundsRect,
				ADMItemInitProc inInitProc, ADMUserData inUserData, ADMInt32 inOptions);

	void ADMAPI (*DestroyItem)(ADMDialogRef inDialog, ADMItemRef inItem);
	
	ADMItemRef ADMAPI (*GetNextItem)(ADMDialogRef inDialog, ADMItemRef inItem);
	ADMItemRef ADMAPI (*GetPreviousItem)(ADMDialogRef inDialog, ADMItemRef inItem);

	// default/cancel items

	void ADMAPI (*SetDefaultItemID)(ADMDialogRef inDialog, ADMInt32 inItemID);
	ADMInt32 ADMAPI (*GetDefaultItemID)(ADMDialogRef inDialog);

	void ADMAPI (*SetCancelItemID)(ADMDialogRef inDialog, ADMInt32 inItemID);
	ADMInt32 ADMAPI (*GetCancelItemID)(ADMDialogRef inDialog);

	ADMBoolean ADMAPI (*EndModal)(ADMDialogRef inDialog, ADMInt32 inModalResultID,
				ADMBoolean inCancelling);
	
	// custom item types
	
	ADMErr ADMAPI (*RegisterItemType)(SPPluginRef inPluginRef, ADMItemType inItemType);
	ADMErr ADMAPI (*UnregisterItemType)(SPPluginRef inPluginRef, ADMItemType inItemType);

	// tooltips

	void ADMAPI (*LoadToolTips)(ADMDialogRef inDialog, ADMInt32 inStringID);

	// context help
	// dhearst 6/28/02 - ADM no longer supports ASHelp
	void ADMAPI (*SetHelpID_DEPRECATED)(ADMDialogRef inDialog, ADMInt32 inHelpID);
	ADMInt32 ADMAPI (*GetHelpID_DEPRECATED)(ADMDialogRef inDialog);
	void ADMAPI (*Help_DEPRECATED)(ADMDialogRef inDialog);

	// dialog state accessors	

	ADMBoolean ADMAPI (*IsCollapsed)(ADMDialogRef inDialog);

	ADMItemRef ADMAPI (*CreateGroupInDialog)(ADMDialogRef inDialog,
				SPPluginRef inPluginRef, const char* inName, ADMInt32 inDialogID,
				ADMItemInitProc inInitProc, ADMUserData inUserData, ADMInt32 inOptions);

	void ADMAPI (*SetWindowRef)(ADMDialogRef inDialog, ADMWindowRef inWindowRef);
	void ADMAPI (*SetDialogName)(ADMDialogRef inDialog, const char* inName);

	ADMBoolean ADMAPI (*IsDialogContextHidden)(ADMDialogRef inDialog);

	void ADMAPI (*SetUpdateEnabled)(ADMDialogRef inDialog, ADMBoolean inEnableUpdate);
	ADMBoolean ADMAPI (*IsUpdateEnabled)(ADMDialogRef inDialog);
	
	void ADMAPI (*SetForcedOnScreen)(ADMDialogRef ioDialog,
				ADMBoolean inForcedOnScreen);
	ADMBoolean ADMAPI (*IsForcedOnScreen)(ADMDialogRef inDialog);

	ADMInt32 ADMAPI (*DisplayAsPopupModal)(ADMDialogRef inDialog);
	
	//Use this function to reposition the tab order of the item in the dialog. Note the item should 
	//be already created.
	ADMErr ADMAPI (*DEPRECATED_AdjustItemTabOrder)(ADMDialogRef inDialog, ADMItemRef inItem, ADMInt32 position);

}
ADMDialogSuite8;


// -----------------------------------------------------------------------------

#pragma ADM_PRAGMA_IMPORT_END
#pragma ADM_PRAGMA_ALIGN_END

#ifdef __cplusplus
}
#endif

#endif  // __ADMDialogOld__
