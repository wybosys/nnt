/***********************************************************************/
/*                                                                     */
/* ADMItemOld.h                                                        */
/* Old versions of ADM Item Suite                                      */
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

#ifndef __ADMItemOld__
#define __ADMItemOld__

#ifndef __ADMTypes__
#include "ADMTypes.h"
#endif


// -----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

#pragma ADM_PRAGMA_ALIGN_BEGIN
#pragma ADM_PRAGMA_IMPORT_BEGIN


// =============================================================================
//		* ADM Item Suite, version 3
// =============================================================================

#define kADMItemSuiteVersion3 3

// -----------------------------------------------------------------------------

typedef struct ADMItemSuite3
{

	// item creation/destruction

	ADMItemRef ADMAPI (*Create)(ADMDialogRef inDialog, ADMInt32 inItemID, ADMItemType inItemType,
				const ADMRect* inBoundsRect, ADMItemInitProc inInitProc, ADMUserData inUserData);

	void ADMAPI (*Destroy)(ADMItemRef inItem);
	
	// item draw proc
	
	void ADMAPI (*SetDrawProc)(ADMItemRef inItem, ADMItemDrawProc inDrawProc);
	ADMItemDrawProc ADMAPI (*GetDrawProc)(ADMItemRef inItem);
	void ADMAPI (*DefaultDraw)(ADMItemRef inItem, ADMDrawerRef inDrawer);

	// item track proc
	
	void ADMAPI (*SetTrackProc)(ADMItemRef inItem, ADMItemTrackProc inTrackProc);
	ADMItemTrackProc ADMAPI (*GetTrackProc)(ADMItemRef inItem);
	ADMBoolean ADMAPI (*DefaultTrack)(ADMItemRef inItem, ADMTrackerRef inTracker);

	void ADMAPI (*SetMask)(ADMItemRef inItem, ADMActionMask inActionMask);
	ADMActionMask ADMAPI (*GetMask)(ADMItemRef inItem);

	// item notify proc

	void ADMAPI (*SetNotifyProc)(ADMItemRef inItem, ADMItemNotifyProc inNotifyProc);
	ADMItemNotifyProc ADMAPI (*GetNotifyProc)(ADMItemRef inItem);
	void ADMAPI (*DefaultNotify)(ADMItemRef inItem, ADMNotifierRef inNotifier);
	void ADMAPI (*SendNotify)(ADMItemRef inItem, const char* inNotifierType);

	void ADMAPI (*SetNotifierData)(ADMItemRef inItem, ADMUserData inNotifierData);
	ADMUserData ADMAPI (*GetNotifierData)(ADMItemRef inItem);

	// item destroy proc

	void ADMAPI (*SetDestroyProc)(ADMItemRef inItem, ADMItemDestroyProc inDestroyProc);
	ADMItemDestroyProc ADMAPI (*GetDestroyProc)(ADMItemRef inItem);
	
	// item timer
	
	ADMTimerRef ADMAPI (*CreateTimer)(ADMItemRef inItem, ADMUInt32 inMilliseconds,
				ADMActionMask inAbortMask, ADMItemTimerProc inTimerProc,
				ADMItemTimerAbortProc inTimerAbortProc);

	void ADMAPI (*AbortTimer)(ADMItemRef inItem, ADMTimerRef inTimer);

	// item user data

	void ADMAPI (*SetUserData)(ADMItemRef inItem, ADMUserData inUserData);
	ADMUserData ADMAPI (*GetUserData)(ADMItemRef inItem);

	// item information accessors

	ADMInt32 ADMAPI (*GetID)(ADMItemRef inItem);
	ADMDialogRef ADMAPI (*GetDialog)(ADMItemRef inItem);
	ADMWindowRef ADMAPI (*GetWindowRef)(ADMItemRef inItem);
	ADMListRef ADMAPI (*GetList)(ADMItemRef inItem);
	ADMItemRef ADMAPI (*GetChildItem)(ADMItemRef inItem, ADMInt32 inChildID);	

	void ADMAPI (*SetPluginRef)(ADMItemRef inItem, SPPluginRef inPluginRef);
	SPPluginRef ADMAPI (*GetPluginRef)(ADMItemRef inItem);

	void ADMAPI (*SetItemType)(ADMItemRef inItem, ADMItemType inItemType);
	ADMItemType ADMAPI (*GetItemType)(ADMItemRef inItem);
	
	void ADMAPI (*SetItemStyle)(ADMItemRef inItem, ADMItemStyle inItemStyle);
	ADMItemStyle ADMAPI (*GetItemStyle)(ADMItemRef inItem);
	
	// item state accessors
	
	void ADMAPI (*Show)(ADMItemRef inItem, ADMBoolean inShow);
	ADMBoolean ADMAPI (*IsVisible)(ADMItemRef inItem);
	
	void ADMAPI (*Enable)(ADMItemRef inItem, ADMBoolean inEnable);
	ADMBoolean ADMAPI (*IsEnabled)(ADMItemRef inItem);
	
	void ADMAPI (*Activate)(ADMItemRef inItem, ADMBoolean inActivate);
	ADMBoolean ADMAPI (*IsActive)(ADMItemRef inItem);
	
	void ADMAPI (*Known)(ADMItemRef inItem, ADMBoolean inKnown);
	ADMBoolean ADMAPI (*IsKnown)(ADMItemRef inItem);
	
	// item bounds accessors

	void ADMAPI (*SetLocalRect)(ADMItemRef inItem, const ADMRect* inLocalRect);
	void ADMAPI (*GetLocalRect)(ADMItemRef inItem, ADMRect* outLocalRect);
	
	void ADMAPI (*SetBoundsRect)(ADMItemRef inItem, const ADMRect* inBoundsRect);
	void ADMAPI (*GetBoundsRect)(ADMItemRef inItem, ADMRect* outBoundsRect);
	
	void ADMAPI (*GetBestSize)(ADMItemRef inItem, ADMPoint* outBestSize);

	void ADMAPI (*Move)(ADMItemRef inItem, ADMInt32 inHorizPosition, ADMInt32 inVertPosition);
	void ADMAPI (*Size)(ADMItemRef inItem, ADMInt32 inWidth, ADMInt32 inHeight);

	// coordinate system transformations	

	void ADMAPI (*LocalToScreenPoint)(ADMItemRef inItem, ADMPoint* ioPoint);
	void ADMAPI (*ScreenToLocalPoint)(ADMItemRef inItem, ADMPoint* ioPoint);
	
	void ADMAPI (*LocalToScreenRect)(ADMItemRef inItem, ADMRect* ioRect);
	void ADMAPI (*ScreenToLocalRect)(ADMItemRef inItem, ADMRect* ioRect);
	
	// item display
	
	void ADMAPI (*Invalidate)(ADMItemRef inItem);
	void ADMAPI (*Update)(ADMItemRef inItem);
	
	// cursor ID accessors
	
	ADMBoolean ADMAPI (*SetCursorID)(ADMItemRef inItem, SPPluginRef inPluginRef, ADMInt32 inCursorID);
	void ADMAPI (*GetCursorID)(ADMItemRef inItem, SPPluginRef* outPluginRef, ADMInt32* outCursorID);

	// picture ID accessors

	void ADMAPI (*SetPictureID)(ADMItemRef inItem, ADMInt32 inPictureResID);
	ADMInt32 ADMAPI (*GetPictureID)(ADMItemRef inItem);
	
	void ADMAPI (*SetSelectedPictureID)(ADMItemRef inItem, ADMInt32 inPictureResID);
	ADMInt32 ADMAPI (*GetSelectedPictureID)(ADMItemRef inItem);
	
	void ADMAPI (*SetDisabledPictureID)(ADMItemRef inItem, ADMInt32 inPictureResID);
	ADMInt32 ADMAPI (*GetDisabledPictureID)(ADMItemRef inItem);

	// tooltips

	void ADMAPI (*SetTipString)(ADMItemRef inItem, const char* inTipString);
	void ADMAPI (*GetTipString)(ADMItemRef inItem, char* outTipString, ADMInt32 inMaxLength);
	
	ADMInt32 ADMAPI (*GetTipStringLength)(ADMItemRef inItem);
	
	void ADMAPI (*EnableTip)(ADMItemRef inItem, ADMBoolean inEnable);
	ADMBoolean ADMAPI (*IsTipEnabled)(ADMItemRef inItem);
	
	void ADMAPI (*ShowToolTip)(ADMItemRef inItem, const ADMPoint* inWhere);
	void ADMAPI (*HideToolTip)(ADMItemRef inItem);
	
	// item text accessors

	void ADMAPI (*SetFont)(ADMItemRef inItem, ADMFont inFontID);
	ADMFont ADMAPI (*GetFont)(ADMItemRef inItem);

	void ADMAPI (*SetText)(ADMItemRef inItem, const char* inText);
	void ADMAPI (*GetText)(ADMItemRef inItem, char* outText, ADMInt32 inMaxLength);
	ADMInt32 ADMAPI (*GetTextLength)(ADMItemRef inItem);
	
	void ADMAPI (*SetMaxTextLength)(ADMItemRef inItem, ADMInt32 inLength);
	ADMInt32 ADMAPI (*GetMaxTextLength)(ADMItemRef inItem);
	
	void ADMAPI (*SelectAll)(ADMItemRef inItem);
	void ADMAPI (*SetSelectionRange)(ADMItemRef inItem, ADMInt32 inSelStart, ADMInt32 inSelEnd);
	void ADMAPI (*GetSelectionRange)(ADMItemRef inItem, ADMInt32* outSelStart, ADMInt32* outSelEnd);

	void ADMAPI (*SetJustify)(ADMItemRef inItem, ADMJustify inJustify);
	ADMJustify ADMAPI (*GetJustify)(ADMItemRef inItem);
	
	void ADMAPI (*SetUnits)(ADMItemRef inItem, ADMUnits inUnits);
	ADMUnits ADMAPI (*GetUnits)(ADMItemRef inItem);
	
	// item value accessors

	void ADMAPI (*SetPrecision)(ADMItemRef inItem, ADMInt32 inNumberOfDecimalPlaces);
	ADMInt32 ADMAPI (*GetPrecision)(ADMItemRef inItem);
	
	void ADMAPI (*SetBooleanValue)(ADMItemRef inItem, ADMBoolean inValue);
	ADMBoolean ADMAPI (*GetBooleanValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetIntValue)(ADMItemRef inItem, ADMInt32 inValue);
	ADMInt32 ADMAPI (*GetIntValue)(ADMItemRef inItem);
		
	void ADMAPI (*SetFixedValue)(ADMItemRef inItem, ADMFixed inValue);	
	ADMFixed ADMAPI (*GetFixedValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetFloatValue)(ADMItemRef inItem, float inValue);	
	float ADMAPI (*GetFloatValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetMinIntValue)(ADMItemRef inItem, ADMInt32 inValue);
	ADMInt32 ADMAPI (*GetMinIntValue)(ADMItemRef inItem);
		
	void ADMAPI (*SetMinFixedValue)(ADMItemRef inItem, ADMFixed inValue);	
	ADMFixed ADMAPI (*GetMinFixedValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetMaxIntValue)(ADMItemRef inItem, ADMInt32 inValue);
	ADMInt32 ADMAPI (*GetMaxIntValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetMinFloatValue)(ADMItemRef inItem, float inValue);	
	float ADMAPI (*GetMinFloatValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetMaxFixedValue)(ADMItemRef inItem, ADMFixed inValue);	
	ADMFixed ADMAPI (*GetMaxFixedValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetMaxFloatValue)(ADMItemRef inItem, float inValue);	
	float ADMAPI (*GetMaxFloatValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetSmallIncrement)(ADMItemRef inItem, float inIncrement);	
	float ADMAPI (*GetSmallIncrement)(ADMItemRef inItem);
	
	void ADMAPI (*SetLargeIncrement)(ADMItemRef inItem, float inIncrement);
	float ADMAPI (*GetLargeIncrement)(ADMItemRef inItem);
	
	void ADMAPI (*SetAllowUnits)(ADMItemRef inItem, ADMBoolean inAllowUnits);
	ADMBoolean ADMAPI (*GetAllowUnits)(ADMItemRef inItem);

	void ADMAPI (*SetAllowMath)(ADMItemRef inItem, ADMBoolean inAllowMath);
	ADMBoolean ADMAPI (*GetAllowMath)(ADMItemRef inItem);
	
	void ADMAPI (*SetFloatToTextProc)(ADMItemRef inItem, ADMItemFloatToTextProc inProc);
	ADMItemFloatToTextProc ADMAPI (*GetFloatToTextProc)(ADMItemRef inItem);
	ADMBoolean ADMAPI (*DefaultFloatToText)(ADMItemRef inItem, float inValue, char* outText,
				ADMInt32 inMaxLength);

	void ADMAPI (*SetTextToFloatProc)(ADMItemRef inItem, ADMItemTextToFloatProc inProc);
	ADMItemTextToFloatProc ADMAPI (*GetTextToFloatProc)(ADMItemRef inItem);
	ADMBoolean ADMAPI (*DefaultTextToFloat)(ADMItemRef inItem, const char* inText, float* outValue);

	void ADMAPI (*ShowUnits)(ADMItemRef inItem, ADMBoolean inShowUnits);
	ADMBoolean ADMAPI (*GetShowUnits)(ADMItemRef inItem);

	ADMBoolean ADMAPI (*WasPercentageChange)(ADMItemRef inItem);

	// item help ID
	// dhearst 6/28/02 - ADM no longer supports ASHelp
	void ADMAPI (*SetHelpID_DEPRECATED)(ADMItemRef inItem, ADMInt32 inHelpID);
	ADMInt32 ADMAPI (*GetHelpID_DEPRECATED)(ADMItemRef inItem);
	void ADMAPI (*Help_DEPRECATED)(ADMItemRef inDialog);

}
ADMItemSuite3;


// =============================================================================
//		* ADM Item Suite, version 4
// =============================================================================

#define kADMItemSuiteVersion4 4
#define kADMItemSuiteVersion kADMItemSuiteVersion4

// Begin AI9 #203277 -------------------------------------------------------

// FIX_ME (jreid 12/1/99) -- The following typedef is NOT part of the frozen
// ADMItemSuite4; it is being shoehorned in temporarily and WILL BE REMOVED.

typedef void ADMAPI (*ADMPreDropDownProc)(ADMItemRef ioItem);

// End AI9 #203277 ---------------------------------------------------------

// -----------------------------------------------------------------------------

typedef struct ADMItemSuite4
{

	// item creation/destruction

	ADMItemRef ADMAPI (*Create)(ADMDialogRef inDialog, ADMInt32 inItemID, ADMItemType inItemType,
				const ADMRect* inBoundsRect, ADMItemInitProc inInitProc, ADMUserData inUserData);

	void ADMAPI (*Destroy)(ADMItemRef inItem);
	
	// item draw proc
	
	void ADMAPI (*SetDrawProc)(ADMItemRef inItem, ADMItemDrawProc inDrawProc);
	ADMItemDrawProc ADMAPI (*GetDrawProc)(ADMItemRef inItem);
	void ADMAPI (*DefaultDraw)(ADMItemRef inItem, ADMDrawerRef inDrawer);

	// item track proc
	
	void ADMAPI (*SetTrackProc)(ADMItemRef inItem, ADMItemTrackProc inTrackProc);
	ADMItemTrackProc ADMAPI (*GetTrackProc)(ADMItemRef inItem);
	ADMBoolean ADMAPI (*DefaultTrack)(ADMItemRef inItem, ADMTrackerRef inTracker);

	void ADMAPI (*SetMask)(ADMItemRef inItem, ADMActionMask inActionMask);
	ADMActionMask ADMAPI (*GetMask)(ADMItemRef inItem);

	// item notify proc

	void ADMAPI (*SetNotifyProc)(ADMItemRef inItem, ADMItemNotifyProc inNotifyProc);
	ADMItemNotifyProc ADMAPI (*GetNotifyProc)(ADMItemRef inItem);
	void ADMAPI (*DefaultNotify)(ADMItemRef inItem, ADMNotifierRef inNotifier);
	void ADMAPI (*SendNotify)(ADMItemRef inItem, const char* inNotifierType);

	void ADMAPI (*SetNotifierData)(ADMItemRef inItem, ADMUserData inNotifierData);
	ADMUserData ADMAPI (*GetNotifierData)(ADMItemRef inItem);

	// item destroy proc

	void ADMAPI (*SetDestroyProc)(ADMItemRef inItem, ADMItemDestroyProc inDestroyProc);
	ADMItemDestroyProc ADMAPI (*GetDestroyProc)(ADMItemRef inItem);
	
	// item timer
	
	ADMTimerRef ADMAPI (*CreateTimer)(ADMItemRef inItem, ADMUInt32 inMilliseconds,
				ADMActionMask inAbortMask, ADMItemTimerProc inTimerProc,
				ADMItemTimerAbortProc inTimerAbortProc);

	void ADMAPI (*AbortTimer)(ADMItemRef inItem, ADMTimerRef inTimer);

	// item user data

	void ADMAPI (*SetUserData)(ADMItemRef inItem, ADMUserData inUserData);
	ADMUserData ADMAPI (*GetUserData)(ADMItemRef inItem);

	// item information accessors

	ADMInt32 ADMAPI (*GetID)(ADMItemRef inItem);
	ADMDialogRef ADMAPI (*GetDialog)(ADMItemRef inItem);
	ADMWindowRef ADMAPI (*GetWindowRef)(ADMItemRef inItem);
	ADMListRef ADMAPI (*GetList)(ADMItemRef inItem);
	ADMItemRef ADMAPI (*GetChildItem)(ADMItemRef inItem, ADMInt32 inChildID);	

	void ADMAPI (*SetPluginRef)(ADMItemRef inItem, SPPluginRef inPluginRef);
	SPPluginRef ADMAPI (*GetPluginRef)(ADMItemRef inItem);

	void ADMAPI (*SetItemType)(ADMItemRef inItem, ADMItemType inItemType);
	ADMItemType ADMAPI (*GetItemType)(ADMItemRef inItem);
	
	void ADMAPI (*SetItemStyle)(ADMItemRef inItem, ADMItemStyle inItemStyle);
	ADMItemStyle ADMAPI (*GetItemStyle)(ADMItemRef inItem);
	
	// item state accessors
	
	void ADMAPI (*Show)(ADMItemRef inItem, ADMBoolean inShow);
	ADMBoolean ADMAPI (*IsVisible)(ADMItemRef inItem);
	
	void ADMAPI (*Enable)(ADMItemRef inItem, ADMBoolean inEnable);
	ADMBoolean ADMAPI (*IsEnabled)(ADMItemRef inItem);
	
	void ADMAPI (*Activate)(ADMItemRef inItem, ADMBoolean inActivate);
	ADMBoolean ADMAPI (*IsActive)(ADMItemRef inItem);
	
	void ADMAPI (*Known)(ADMItemRef inItem, ADMBoolean inKnown);
	ADMBoolean ADMAPI (*IsKnown)(ADMItemRef inItem);
	
	// item bounds accessors

	void ADMAPI (*SetLocalRect)(ADMItemRef inItem, const ADMRect* inLocalRect);
	void ADMAPI (*GetLocalRect)(ADMItemRef inItem, ADMRect* outLocalRect);
	
	void ADMAPI (*SetBoundsRect)(ADMItemRef inItem, const ADMRect* inBoundsRect);
	void ADMAPI (*GetBoundsRect)(ADMItemRef inItem, ADMRect* outBoundsRect);
	
	void ADMAPI (*GetBestSize)(ADMItemRef inItem, ADMPoint* outBestSize);

	void ADMAPI (*Move)(ADMItemRef inItem, ADMInt32 inHorizPosition, ADMInt32 inVertPosition);
	void ADMAPI (*Size)(ADMItemRef inItem, ADMInt32 inWidth, ADMInt32 inHeight);

	// coordinate system transformations	

	void ADMAPI (*LocalToScreenPoint)(ADMItemRef inItem, ADMPoint* ioPoint);
	void ADMAPI (*ScreenToLocalPoint)(ADMItemRef inItem, ADMPoint* ioPoint);
	
	void ADMAPI (*LocalToScreenRect)(ADMItemRef inItem, ADMRect* ioRect);
	void ADMAPI (*ScreenToLocalRect)(ADMItemRef inItem, ADMRect* ioRect);
	
	// item display
	
	void ADMAPI (*Invalidate)(ADMItemRef inItem);
	void ADMAPI (*InvalidateRect)(ADMItemRef inDialog, const ADMRect* inInvalRect);
	void ADMAPI (*Update)(ADMItemRef inItem);
	
	// cursor ID accessors
	
	ADMBoolean ADMAPI (*SetCursorID)(ADMItemRef inItem, SPPluginRef inPluginRef, ADMInt32 inCursorID);
	void ADMAPI (*GetCursorID)(ADMItemRef inItem, SPPluginRef* outPluginRef, ADMInt32* outCursorID);

	// picture ID accessors

	void ADMAPI (*SetPictureID)(ADMItemRef inItem, ADMInt32 inPictureResID);
	ADMInt32 ADMAPI (*GetPictureID)(ADMItemRef inItem);
	
	void ADMAPI (*SetSelectedPictureID)(ADMItemRef inItem, ADMInt32 inPictureResID);
	ADMInt32 ADMAPI (*GetSelectedPictureID)(ADMItemRef inItem);
	
	void ADMAPI (*SetDisabledPictureID)(ADMItemRef inItem, ADMInt32 inPictureResID);
	ADMInt32 ADMAPI (*GetDisabledPictureID)(ADMItemRef inItem);

	// tooltips

	void ADMAPI (*SetTipString)(ADMItemRef inItem, const char* inTipString);
	void ADMAPI (*GetTipString)(ADMItemRef inItem, char* outTipString, ADMInt32 inMaxLength);
	
	ADMInt32 ADMAPI (*GetTipStringLength)(ADMItemRef inItem);
	
	void ADMAPI (*EnableTip)(ADMItemRef inItem, ADMBoolean inEnable);
	ADMBoolean ADMAPI (*IsTipEnabled)(ADMItemRef inItem);
	
	void ADMAPI (*ShowToolTip)(ADMItemRef inItem, const ADMPoint* inWhere);
	void ADMAPI (*HideToolTip)(ADMItemRef inItem);
	
	// item text accessors

	void ADMAPI (*SetFont)(ADMItemRef inItem, ADMFont inFontID);
	ADMFont ADMAPI (*GetFont)(ADMItemRef inItem);

	void ADMAPI (*SetText)(ADMItemRef inItem, const char* inText);
	void ADMAPI (*GetText)(ADMItemRef inItem, char* outText, ADMInt32 inMaxLength);
	ADMInt32 ADMAPI (*GetTextLength)(ADMItemRef inItem);
	
	void ADMAPI (*SetMaxTextLength)(ADMItemRef inItem, ADMInt32 inLength);
	ADMInt32 ADMAPI (*GetMaxTextLength)(ADMItemRef inItem);
	
	void ADMAPI (*SelectAll)(ADMItemRef inItem);
	void ADMAPI (*SetSelectionRange)(ADMItemRef inItem, ADMInt32 inSelStart, ADMInt32 inSelEnd);
	void ADMAPI (*GetSelectionRange)(ADMItemRef inItem, ADMInt32* outSelStart, ADMInt32* outSelEnd);

	void ADMAPI (*SetJustify)(ADMItemRef inItem, ADMJustify inJustify);
	ADMJustify ADMAPI (*GetJustify)(ADMItemRef inItem);
	
	void ADMAPI (*SetUnits)(ADMItemRef inItem, ADMUnits inUnits);
	ADMUnits ADMAPI (*GetUnits)(ADMItemRef inItem);
	
	// item value accessors

	void ADMAPI (*SetPrecision)(ADMItemRef inItem, ADMInt32 inNumberOfDecimalPlaces);
	ADMInt32 ADMAPI (*GetPrecision)(ADMItemRef inItem);
	
	void ADMAPI (*SetBooleanValue)(ADMItemRef inItem, ADMBoolean inValue);
	ADMBoolean ADMAPI (*GetBooleanValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetIntValue)(ADMItemRef inItem, ADMInt32 inValue);
	ADMInt32 ADMAPI (*GetIntValue)(ADMItemRef inItem);
		
	void ADMAPI (*SetFixedValue)(ADMItemRef inItem, ADMFixed inValue);	
	ADMFixed ADMAPI (*GetFixedValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetFloatValue)(ADMItemRef inItem, float inValue);	
	float ADMAPI (*GetFloatValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetMinIntValue)(ADMItemRef inItem, ADMInt32 inValue);
	ADMInt32 ADMAPI (*GetMinIntValue)(ADMItemRef inItem);
		
	void ADMAPI (*SetMinFixedValue)(ADMItemRef inItem, ADMFixed inValue);	
	ADMFixed ADMAPI (*GetMinFixedValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetMaxIntValue)(ADMItemRef inItem, ADMInt32 inValue);
	ADMInt32 ADMAPI (*GetMaxIntValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetMinFloatValue)(ADMItemRef inItem, float inValue);	
	float ADMAPI (*GetMinFloatValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetMaxFixedValue)(ADMItemRef inItem, ADMFixed inValue);	
	ADMFixed ADMAPI (*GetMaxFixedValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetMaxFloatValue)(ADMItemRef inItem, float inValue);	
	float ADMAPI (*GetMaxFloatValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetSmallIncrement)(ADMItemRef inItem, float inIncrement);	
	float ADMAPI (*GetSmallIncrement)(ADMItemRef inItem);
	
	void ADMAPI (*SetLargeIncrement)(ADMItemRef inItem, float inIncrement);
	float ADMAPI (*GetLargeIncrement)(ADMItemRef inItem);
	
	void ADMAPI (*SetAllowUnits)(ADMItemRef inItem, ADMBoolean inAllowUnits);
	ADMBoolean ADMAPI (*GetAllowUnits)(ADMItemRef inItem);

	void ADMAPI (*SetAllowMath)(ADMItemRef inItem, ADMBoolean inAllowMath);
	ADMBoolean ADMAPI (*GetAllowMath)(ADMItemRef inItem);
	
	void ADMAPI (*SetFloatToTextProc)(ADMItemRef inItem, ADMItemFloatToTextProc inProc);
	ADMItemFloatToTextProc ADMAPI (*GetFloatToTextProc)(ADMItemRef inItem);

	ADMBoolean ADMAPI (*DefaultFloatToText)(ADMItemRef inItem, float inValue, char* outText,
				ADMInt32 inMaxLength);

	void ADMAPI (*SetTextToFloatProc)(ADMItemRef inItem, ADMItemTextToFloatProc inProc);
	ADMItemTextToFloatProc ADMAPI (*GetTextToFloatProc)(ADMItemRef inItem);
	ADMBoolean ADMAPI (*DefaultTextToFloat)(ADMItemRef inItem, const char* inText, float* outValue);

	void ADMAPI (*ShowUnits)(ADMItemRef inItem, ADMBoolean inShowUnits);
	ADMBoolean ADMAPI (*GetShowUnits)(ADMItemRef inItem);

	ADMBoolean ADMAPI (*WasPercentageChange)(ADMItemRef inItem);

	// item help ID
	// dhearst 6/28/02 - ADM no longer supports ASHelp
	void ADMAPI (*SetHelpID_DEPRECATED)(ADMItemRef inItem, ADMInt32 inHelpID);
	ADMInt32 ADMAPI (*GetHelpID_DEPRECATED)(ADMItemRef inItem);
	void ADMAPI (*Help_DEPRECATED)(ADMItemRef inDialog);

	// hierarchy list accessor
	
	ADMHierarchyListRef ADMAPI (*GetHierarchyList)(ADMItemRef inItem);

// Begin AI9 #203277 -------------------------------------------------------

	// Do not use the following function! It was NOT part of the frozen
	// ADMItemSuite4; it is being shoehorned in temporarily and WILL BE REMOVED.

	void ADMAPI (*SetPreDropDownProc)(ADMItemRef ioItem,
			ADMPreDropDownProc inPreDropDownProc, ADMUserData inUserData);

// End AI9 #203277 ---------------------------------------------------------

}
ADMItemSuite4;

typedef ADMItemSuite4 ADMItemSuite;


// =============================================================================
//		* ADM Item Suite, version 5
// =============================================================================

#define kADMItemSuiteVersion5 5

// -----------------------------------------------------------------------------

typedef struct ADMItemSuite5
{

	// *** This suite is FROZEN.
	// *** It shipped with Photoshop 5.5 and ImageReady 2.0.

	// item creation/destruction

	ADMItemRef ADMAPI (*Create)(ADMDialogRef inDialog, ADMInt32 inItemID,
				ADMItemType inItemType, const ADMRect* inBoundsRect,
				ADMItemInitProc inInitProc, ADMUserData inUserData,
				ADMInt32 inOptions);

	void ADMAPI (*Destroy)(ADMItemRef inItem);
	
	// item draw proc
	
	void ADMAPI (*SetDrawProc)(ADMItemRef inItem, ADMItemDrawProc inDrawProc);
	ADMItemDrawProc ADMAPI (*GetDrawProc)(ADMItemRef inItem);
	void ADMAPI (*DefaultDraw)(ADMItemRef inItem, ADMDrawerRef inDrawer);

	// item track proc
	
	void ADMAPI (*SetTrackProc)(ADMItemRef inItem, ADMItemTrackProc inTrackProc);
	ADMItemTrackProc ADMAPI (*GetTrackProc)(ADMItemRef inItem);
	ADMBoolean ADMAPI (*DefaultTrack)(ADMItemRef inItem, ADMTrackerRef inTracker);

	void ADMAPI (*SetMask)(ADMItemRef inItem, ADMActionMask inActionMask);
	ADMActionMask ADMAPI (*GetMask)(ADMItemRef inItem);

	// item notify proc

	void ADMAPI (*SetNotifyProc)(ADMItemRef inItem, ADMItemNotifyProc inNotifyProc);
	ADMItemNotifyProc ADMAPI (*GetNotifyProc)(ADMItemRef inItem);
	void ADMAPI (*DefaultNotify)(ADMItemRef inItem, ADMNotifierRef inNotifier);
	void ADMAPI (*SendNotify)(ADMItemRef inItem, const char* inNotifierType);

	void ADMAPI (*SetNotifierData)(ADMItemRef inItem, ADMUserData inNotifierData);
	ADMUserData ADMAPI (*GetNotifierData)(ADMItemRef inItem);

	// item destroy proc

	void ADMAPI (*SetDestroyProc)(ADMItemRef inItem, ADMItemDestroyProc inDestroyProc);
	ADMItemDestroyProc ADMAPI (*GetDestroyProc)(ADMItemRef inItem);
	
	// item timer
	
	ADMTimerRef ADMAPI (*CreateTimer)(ADMItemRef inItem, ADMUInt32 inMilliseconds,
				ADMActionMask inAbortMask, ADMItemTimerProc inTimerProc,
				ADMItemTimerAbortProc inTimerAbortProc, ADMInt32 inOptions);

	void ADMAPI (*AbortTimer)(ADMItemRef inItem, ADMTimerRef inTimer);

	// item user data

	void ADMAPI (*SetUserData)(ADMItemRef inItem, ADMUserData inUserData);
	ADMUserData ADMAPI (*GetUserData)(ADMItemRef inItem);

	// item information accessors

	ADMInt32 ADMAPI (*GetID)(ADMItemRef inItem);
	ADMDialogRef ADMAPI (*GetDialog)(ADMItemRef inItem);
	ADMWindowRef ADMAPI (*GetWindowRef)(ADMItemRef inItem);
	ADMListRef ADMAPI (*GetList)(ADMItemRef inItem);
	ADMItemRef ADMAPI (*GetChildItem)(ADMItemRef inItem, ADMInt32 inChildID);	

	void ADMAPI (*SetPluginRef)(ADMItemRef inItem, SPPluginRef inPluginRef);
	SPPluginRef ADMAPI (*GetPluginRef)(ADMItemRef inItem);

	void ADMAPI (*SetItemType)(ADMItemRef inItem, ADMItemType inItemType);
	ADMItemType ADMAPI (*GetItemType)(ADMItemRef inItem);
	
	void ADMAPI (*SetItemStyle)(ADMItemRef inItem, ADMItemStyle inItemStyle);
	ADMItemStyle ADMAPI (*GetItemStyle)(ADMItemRef inItem);
	
	// item state accessors
	
	void ADMAPI (*Show)(ADMItemRef inItem, ADMBoolean inShow);
	ADMBoolean ADMAPI (*IsVisible)(ADMItemRef inItem);
	
	void ADMAPI (*Enable)(ADMItemRef inItem, ADMBoolean inEnable);
	ADMBoolean ADMAPI (*IsEnabled)(ADMItemRef inItem);
	
	void ADMAPI (*Activate)(ADMItemRef inItem, ADMBoolean inActivate);
	ADMBoolean ADMAPI (*IsActive)(ADMItemRef inItem);
	
	void ADMAPI (*Known)(ADMItemRef inItem, ADMBoolean inKnown);
	ADMBoolean ADMAPI (*IsKnown)(ADMItemRef inItem);
	
	// item bounds accessors

	void ADMAPI (*SetLocalRect)(ADMItemRef inItem, const ADMRect* inLocalRect);
	void ADMAPI (*GetLocalRect)(ADMItemRef inItem, ADMRect* outLocalRect);
	
	void ADMAPI (*SetBoundsRect)(ADMItemRef inItem, const ADMRect* inBoundsRect);
	void ADMAPI (*GetBoundsRect)(ADMItemRef inItem, ADMRect* outBoundsRect);
	
	void ADMAPI (*GetBestSize)(ADMItemRef inItem, ADMPoint* outBestSize);

	void ADMAPI (*Move)(ADMItemRef inItem, ADMInt32 inHorizPosition, ADMInt32 inVertPosition);
	void ADMAPI (*Size)(ADMItemRef inItem, ADMInt32 inWidth, ADMInt32 inHeight);

	// coordinate system transformations	

	void ADMAPI (*LocalToScreenPoint)(ADMItemRef inItem, ADMPoint* ioPoint);
	void ADMAPI (*ScreenToLocalPoint)(ADMItemRef inItem, ADMPoint* ioPoint);
	
	void ADMAPI (*LocalToScreenRect)(ADMItemRef inItem, ADMRect* ioRect);
	void ADMAPI (*ScreenToLocalRect)(ADMItemRef inItem, ADMRect* ioRect);
	
	// item display
	
	void ADMAPI (*Invalidate)(ADMItemRef inItem);
	void ADMAPI (*InvalidateRect)(ADMItemRef inDialog, const ADMRect* inInvalRect);
	void ADMAPI (*Update)(ADMItemRef inItem);
	
	// cursor ID accessors
	
	ADMBoolean ADMAPI (*SetCursorID)(ADMItemRef inItem, SPPluginRef inPluginRef, ADMInt32 inCursorID,
				const char* inCursorName);

	void ADMAPI (*GetCursorID)(ADMItemRef inItem, SPPluginRef* outPluginRef, ADMInt32* outCursorID,
				const char** outCursorName);

	// picture ID accessors

	void ADMAPI (*SetPictureID)(ADMItemRef inItem, ADMInt32 inPictureResID,
				const char* inPictureResName);

	void ADMAPI (*GetPictureID)(ADMItemRef inItem, ADMInt32* outPictureResID,
				const char** outPictureResName);
	
	void ADMAPI (*SetSelectedPictureID)(ADMItemRef inItem, ADMInt32 inPictureResID,
				const char* inPictureResName);

	void ADMAPI (*GetSelectedPictureID)(ADMItemRef inItem, ADMInt32* outPictureResID,
				const char** outPictureResName);
	
	void ADMAPI (*SetDisabledPictureID)(ADMItemRef inItem, ADMInt32 inPictureResID,
				const char* inPictureResName);

	void ADMAPI (*GetDisabledPictureID)(ADMItemRef inItem, ADMInt32* outPictureResID,
				const char** outPictureResName);

	// tooltips

	void ADMAPI (*SetTipString)(ADMItemRef inItem, const char* inTipString);
	void ADMAPI (*GetTipString)(ADMItemRef inItem, char* outTipString, ADMInt32 inMaxLength);
	
	ADMInt32 ADMAPI (*GetTipStringLength)(ADMItemRef inItem);
	
	void ADMAPI (*EnableTip)(ADMItemRef inItem, ADMBoolean inEnable);
	ADMBoolean ADMAPI (*IsTipEnabled)(ADMItemRef inItem);
	
	void ADMAPI (*ShowToolTip)(ADMItemRef inItem, const ADMPoint* inWhere);
	void ADMAPI (*HideToolTip)(ADMItemRef inItem);
	
	// item text accessors

	void ADMAPI (*SetFont)(ADMItemRef inItem, ADMFont inFontID);
	ADMFont ADMAPI (*GetFont)(ADMItemRef inItem);

	void ADMAPI (*SetText)(ADMItemRef inItem, const char* inText);
	void ADMAPI (*GetText)(ADMItemRef inItem, char* outText, ADMInt32 inMaxLength);
	ADMInt32 ADMAPI (*GetTextLength)(ADMItemRef inItem);
	
	void ADMAPI (*SetMaxTextLength)(ADMItemRef inItem, ADMInt32 inLength);
	ADMInt32 ADMAPI (*GetMaxTextLength)(ADMItemRef inItem);
	
	void ADMAPI (*SelectAll)(ADMItemRef inItem);
	void ADMAPI (*SetSelectionRange)(ADMItemRef inItem, ADMInt32 inSelStart, ADMInt32 inSelEnd);
	void ADMAPI (*GetSelectionRange)(ADMItemRef inItem, ADMInt32* outSelStart, ADMInt32* outSelEnd);

	void ADMAPI (*SetJustify)(ADMItemRef inItem, ADMJustify inJustify);
	ADMJustify ADMAPI (*GetJustify)(ADMItemRef inItem);
	
	void ADMAPI (*SetUnits)(ADMItemRef inItem, ADMUnits inUnits);
	ADMUnits ADMAPI (*GetUnits)(ADMItemRef inItem);
	
	// item value accessors

	void ADMAPI (*SetPrecision)(ADMItemRef inItem, ADMInt32 inNumberOfDecimalPlaces);
	ADMInt32 ADMAPI (*GetPrecision)(ADMItemRef inItem);
	
	void ADMAPI (*SetBooleanValue)(ADMItemRef inItem, ADMBoolean inValue);
	ADMBoolean ADMAPI (*GetBooleanValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetIntValue)(ADMItemRef inItem, ADMInt32 inValue);
	ADMInt32 ADMAPI (*GetIntValue)(ADMItemRef inItem);
		
	void ADMAPI (*SetFixedValue)(ADMItemRef inItem, ADMFixed inValue);	
	ADMFixed ADMAPI (*GetFixedValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetFloatValue)(ADMItemRef inItem, float inValue);	
	float ADMAPI (*GetFloatValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetMinIntValue)(ADMItemRef inItem, ADMInt32 inValue);
	ADMInt32 ADMAPI (*GetMinIntValue)(ADMItemRef inItem);
		
	void ADMAPI (*SetMinFixedValue)(ADMItemRef inItem, ADMFixed inValue);	
	ADMFixed ADMAPI (*GetMinFixedValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetMaxIntValue)(ADMItemRef inItem, ADMInt32 inValue);
	ADMInt32 ADMAPI (*GetMaxIntValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetMinFloatValue)(ADMItemRef inItem, float inValue);	
	float ADMAPI (*GetMinFloatValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetMaxFixedValue)(ADMItemRef inItem, ADMFixed inValue);	
	ADMFixed ADMAPI (*GetMaxFixedValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetMaxFloatValue)(ADMItemRef inItem, float inValue);	
	float ADMAPI (*GetMaxFloatValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetSmallIncrement)(ADMItemRef inItem, float inIncrement);	
	float ADMAPI (*GetSmallIncrement)(ADMItemRef inItem);
	
	void ADMAPI (*SetLargeIncrement)(ADMItemRef inItem, float inIncrement);
	float ADMAPI (*GetLargeIncrement)(ADMItemRef inItem);
	
	void ADMAPI (*SetAllowUnits)(ADMItemRef inItem, ADMBoolean inAllowUnits);
	ADMBoolean ADMAPI (*GetAllowUnits)(ADMItemRef inItem);
	void ADMAPI (*SetAllowMath)(ADMItemRef inItem, ADMBoolean inAllowMath);
	ADMBoolean ADMAPI (*GetAllowMath)(ADMItemRef inItem);
	
	void ADMAPI (*SetFloatToTextProc)(ADMItemRef inItem, ADMItemFloatToTextProc inProc);
	ADMItemFloatToTextProc ADMAPI (*GetFloatToTextProc)(ADMItemRef inItem);
	
	ADMBoolean ADMAPI (*DefaultFloatToText)(ADMItemRef inItem, float inValue, char* outText,
		ADMInt32 inMaxLength);

	void ADMAPI (*SetTextToFloatProc)(ADMItemRef inItem, ADMItemTextToFloatProc inProc);
	ADMItemTextToFloatProc ADMAPI (*GetTextToFloatProc)(ADMItemRef inItem);
	ADMBoolean ADMAPI (*DefaultTextToFloat)(ADMItemRef inItem, const char* inText, float* outValue);

	void ADMAPI (*ShowUnits)(ADMItemRef inItem, ADMBoolean inShowUnits);
	ADMBoolean ADMAPI (*GetShowUnits)(ADMItemRef inItem);

	ADMBoolean ADMAPI (*WasPercentageChange)(ADMItemRef inItem);

	// item help ID
	// dhearst 6/28/02 - ADM no longer supports ASHelp
	void ADMAPI (*SetHelpID_DEPRECATED)(ADMItemRef inItem, ADMInt32 inHelpID);
	ADMInt32 ADMAPI (*GetHelpID_DEPRECATED)(ADMItemRef inItem);
	void ADMAPI (*Help_DEPRECATED)(ADMItemRef inDialog);

	// hierarchy list accessor
	
	ADMHierarchyListRef ADMAPI (*GetHierarchyList)(ADMItemRef inItem);
	
	// item group accessors
	
 	void ADMAPI (*AddItem)(ADMItemRef inGroup, ADMItemRef inItem);
 	void ADMAPI (*RemoveItem)(ADMItemRef inGroup, ADMItemRef inItem);

	// item pictures (from icons)
	
	void ADMAPI (*SetPicture)(ADMItemRef inItem, ADMIconRef inPicture);
	ADMIconRef ADMAPI (*GetPicture)(ADMItemRef inItem);

	void ADMAPI (*SetSelectedPicture)(ADMItemRef inItem, ADMIconRef inPicture);
	ADMIconRef ADMAPI (*GetSelectedPicture)(ADMItemRef inItem);

	void ADMAPI (*SetDisabledPicture)(ADMItemRef inItem, ADMIconRef inPicture);
	ADMIconRef ADMAPI (*GetDisabledPicture)(ADMItemRef inItem);
	
	// popup control accessors
	
	void ADMAPI (*SetPopupDialog)(ADMItemRef inItem, ADMInt32 inPopupItemID, ADMDialogRef inDialog);
	ADMDialogRef ADMAPI (*GetPopupDialog)(ADMItemRef inItem);

}
ADMItemSuite5;

// -----------------------------------------------------------------------------
// =============================================================================
//		* ADM Item Suite, version 6
// =============================================================================

#define kADMItemSuiteVersion6 6

typedef struct ADMItemSuite6
{

	// *** This suite is FROZEN.
	// *** It shipped with Acrobat 5.0.

	// item creation/destruction

	ADMItemRef ADMAPI (*Create)(ADMDialogRef inDialog, ADMInt32 inItemID,
				ADMItemType inItemType, const ADMRect* inBoundsRect,
				ADMItemInitProc inInitProc, ADMUserData inUserData,
				ADMInt32 inOptions);

	void ADMAPI (*Destroy)(ADMItemRef inItem);
	
	// item draw proc
	
	void ADMAPI (*SetDrawProc)(ADMItemRef inItem, ADMItemDrawProc inDrawProc);
	ADMItemDrawProc ADMAPI (*GetDrawProc)(ADMItemRef inItem);
	void ADMAPI (*DefaultDraw)(ADMItemRef inItem, ADMDrawerRef inDrawer);

	// item track proc
	
	void ADMAPI (*SetTrackProc)(ADMItemRef inItem, ADMItemTrackProc inTrackProc);
	ADMItemTrackProc ADMAPI (*GetTrackProc)(ADMItemRef inItem);
	ADMBoolean ADMAPI (*DefaultTrack)(ADMItemRef inItem, ADMTrackerRef inTracker);

	void ADMAPI (*SetMask)(ADMItemRef inItem, ADMActionMask inActionMask);
	ADMActionMask ADMAPI (*GetMask)(ADMItemRef inItem);

	// item notify proc

	void ADMAPI (*SetNotifyProc)(ADMItemRef inItem, ADMItemNotifyProc inNotifyProc);
	ADMItemNotifyProc ADMAPI (*GetNotifyProc)(ADMItemRef inItem);
	void ADMAPI (*DefaultNotify)(ADMItemRef inItem, ADMNotifierRef inNotifier);
	void ADMAPI (*SendNotify)(ADMItemRef inItem, const char* inNotifierType);

	void ADMAPI (*SetNotifierData)(ADMItemRef inItem, ADMUserData inNotifierData);
	ADMUserData ADMAPI (*GetNotifierData)(ADMItemRef inItem);

	// item destroy proc

	void ADMAPI (*SetDestroyProc)(ADMItemRef inItem, ADMItemDestroyProc inDestroyProc);
	ADMItemDestroyProc ADMAPI (*GetDestroyProc)(ADMItemRef inItem);
	
	// item timer
	
	ADMTimerRef ADMAPI (*CreateTimer)(ADMItemRef inItem, ADMUInt32 inMilliseconds,
				ADMActionMask inAbortMask, ADMItemTimerProc inTimerProc,
				ADMItemTimerAbortProc inTimerAbortProc, ADMInt32 inOptions);

	void ADMAPI (*AbortTimer)(ADMItemRef inItem, ADMTimerRef inTimer);

	// item user data

	void ADMAPI (*SetUserData)(ADMItemRef inItem, ADMUserData inUserData);
	ADMUserData ADMAPI (*GetUserData)(ADMItemRef inItem);

	// item information accessors

	ADMInt32 ADMAPI (*GetID)(ADMItemRef inItem);
	ADMDialogRef ADMAPI (*GetDialog)(ADMItemRef inItem);
	ADMWindowRef ADMAPI (*GetWindowRef)(ADMItemRef inItem);
	ADMListRef ADMAPI (*GetList)(ADMItemRef inItem);
	ADMItemRef ADMAPI (*GetChildItem)(ADMItemRef inItem, ADMInt32 inChildID);	

	void ADMAPI (*SetPluginRef)(ADMItemRef inItem, SPPluginRef inPluginRef);
	SPPluginRef ADMAPI (*GetPluginRef)(ADMItemRef inItem);

	void ADMAPI (*SetItemType)(ADMItemRef inItem, ADMItemType inItemType);
	ADMItemType ADMAPI (*GetItemType)(ADMItemRef inItem);
	
	void ADMAPI (*SetItemStyle)(ADMItemRef inItem, ADMItemStyle inItemStyle);
	ADMItemStyle ADMAPI (*GetItemStyle)(ADMItemRef inItem);
	
	// item state accessors
	
	void ADMAPI (*Show)(ADMItemRef inItem, ADMBoolean inShow);
	ADMBoolean ADMAPI (*IsVisible)(ADMItemRef inItem);
	
	void ADMAPI (*Enable)(ADMItemRef inItem, ADMBoolean inEnable);
	ADMBoolean ADMAPI (*IsEnabled)(ADMItemRef inItem);
	
	void ADMAPI (*Activate)(ADMItemRef inItem, ADMBoolean inActivate);
	ADMBoolean ADMAPI (*IsActive)(ADMItemRef inItem);
	
	void ADMAPI (*Known)(ADMItemRef inItem, ADMBoolean inKnown);
	ADMBoolean ADMAPI (*IsKnown)(ADMItemRef inItem);
	
	// item bounds accessors

	void ADMAPI (*SetLocalRect)(ADMItemRef inItem, const ADMRect* inLocalRect);
	void ADMAPI (*GetLocalRect)(ADMItemRef inItem, ADMRect* outLocalRect);
	
	void ADMAPI (*SetBoundsRect)(ADMItemRef inItem, const ADMRect* inBoundsRect);
	void ADMAPI (*GetBoundsRect)(ADMItemRef inItem, ADMRect* outBoundsRect);
	
	void ADMAPI (*GetBestSize)(ADMItemRef inItem, ADMPoint* outBestSize);

	void ADMAPI (*Move)(ADMItemRef inItem, ADMInt32 inHorizPosition, ADMInt32 inVertPosition);
	void ADMAPI (*Size)(ADMItemRef inItem, ADMInt32 inWidth, ADMInt32 inHeight);

	// coordinate system transformations	

	void ADMAPI (*LocalToScreenPoint)(ADMItemRef inItem, ADMPoint* ioPoint);
	void ADMAPI (*ScreenToLocalPoint)(ADMItemRef inItem, ADMPoint* ioPoint);
	
	void ADMAPI (*LocalToScreenRect)(ADMItemRef inItem, ADMRect* ioRect);
	void ADMAPI (*ScreenToLocalRect)(ADMItemRef inItem, ADMRect* ioRect);
	
	// item display
	
	void ADMAPI (*Invalidate)(ADMItemRef inItem);
	void ADMAPI (*InvalidateRect)(ADMItemRef inDialog, const ADMRect* inInvalRect);
	void ADMAPI (*Update)(ADMItemRef inItem);
	
	// cursor ID accessors
	
	ADMBoolean ADMAPI (*SetCursorID)(ADMItemRef inItem, SPPluginRef inPluginRef, ADMInt32 inCursorID,
				const char* inCursorName);

	void ADMAPI (*GetCursorID)(ADMItemRef inItem, SPPluginRef* outPluginRef, ADMInt32* outCursorID,
				const char** outCursorName);

	// picture ID accessors

	void ADMAPI (*SetPictureID)(ADMItemRef inItem, ADMInt32 inPictureResID,
				const char* inPictureResName);

	void ADMAPI (*GetPictureID)(ADMItemRef inItem, ADMInt32* outPictureResID,
				const char** outPictureResName);
	
	void ADMAPI (*SetSelectedPictureID)(ADMItemRef inItem, ADMInt32 inPictureResID,
				const char* inPictureResName);

	void ADMAPI (*GetSelectedPictureID)(ADMItemRef inItem, ADMInt32* outPictureResID,
				const char** outPictureResName);
	
	void ADMAPI (*SetDisabledPictureID)(ADMItemRef inItem, ADMInt32 inPictureResID,
				const char* inPictureResName);

	void ADMAPI (*GetDisabledPictureID)(ADMItemRef inItem, ADMInt32* outPictureResID,
				const char** outPictureResName);

	// tooltips

	void ADMAPI (*SetTipString)(ADMItemRef inItem, const char* inTipString);
	void ADMAPI (*SetTipStringW)(ADMItemRef inItem, const ADMUnicode* inTipString);

	void ADMAPI (*GetTipString)(ADMItemRef inItem, char* outTipString, ADMInt32 inMaxLength);
	void ADMAPI (*GetTipStringW)(ADMItemRef inItem, ADMUnicode* outTipString, ADMInt32 inMaxLength);
	
	ADMInt32 ADMAPI (*GetTipStringLength)(ADMItemRef inItem);
	ADMInt32 ADMAPI (*GetTipStringLengthW)(ADMItemRef inItem);
	
	void ADMAPI (*EnableTip)(ADMItemRef inItem, ADMBoolean inEnable);
	ADMBoolean ADMAPI (*IsTipEnabled)(ADMItemRef inItem);
	
	void ADMAPI (*ShowToolTip)(ADMItemRef inItem, const ADMPoint* inWhere);
	void ADMAPI (*HideToolTip)(ADMItemRef inItem);
	
	// item text accessors

	void ADMAPI (*SetFont)(ADMItemRef inItem, ADMFont inFontID);
	ADMFont ADMAPI (*GetFont)(ADMItemRef inItem);

	void ADMAPI (*SetText)(ADMItemRef inItem, const char* inText);
	void ADMAPI (*SetTextW)(ADMItemRef inItem, const ADMUnicode* inText);

	void ADMAPI (*GetText)(ADMItemRef inItem, char* outText, ADMInt32 inMaxLength);
	void ADMAPI (*GetTextW)(ADMItemRef inItem, ADMUnicode* outText, ADMInt32 inMaxLength);

	ADMInt32 ADMAPI (*GetTextLength)(ADMItemRef inItem);
	ADMInt32 ADMAPI (*GetTextLengthW)(ADMItemRef inItem);
	
	void ADMAPI (*SetMaxTextLength)(ADMItemRef inItem, ADMInt32 inLength);
	ADMInt32 ADMAPI (*GetMaxTextLength)(ADMItemRef inItem);
	
	void ADMAPI (*SelectAll)(ADMItemRef inItem);
	void ADMAPI (*SetSelectionRange)(ADMItemRef inItem, ADMInt32 inSelStart, ADMInt32 inSelEnd);
	void ADMAPI (*GetSelectionRange)(ADMItemRef inItem, ADMInt32* outSelStart, ADMInt32* outSelEnd);

	void ADMAPI (*SetJustify)(ADMItemRef inItem, ADMJustify inJustify);
	ADMJustify ADMAPI (*GetJustify)(ADMItemRef inItem);
	
	void ADMAPI (*SetUnits)(ADMItemRef inItem, ADMUnits inUnits);
	ADMUnits ADMAPI (*GetUnits)(ADMItemRef inItem);
	
	// item value accessors

	void ADMAPI (*SetPrecision)(ADMItemRef inItem, ADMInt32 inNumberOfDecimalPlaces);
	ADMInt32 ADMAPI (*GetPrecision)(ADMItemRef inItem);
	
	void ADMAPI (*SetBooleanValue)(ADMItemRef inItem, ADMBoolean inValue);
	ADMBoolean ADMAPI (*GetBooleanValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetIntValue)(ADMItemRef inItem, ADMInt32 inValue);
	ADMInt32 ADMAPI (*GetIntValue)(ADMItemRef inItem);
		
	void ADMAPI (*SetFixedValue)(ADMItemRef inItem, ADMFixed inValue);	
	ADMFixed ADMAPI (*GetFixedValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetFloatValue)(ADMItemRef inItem, float inValue);	
	float ADMAPI (*GetFloatValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetMinIntValue)(ADMItemRef inItem, ADMInt32 inValue);
	ADMInt32 ADMAPI (*GetMinIntValue)(ADMItemRef inItem);
		
	void ADMAPI (*SetMinFixedValue)(ADMItemRef inItem, ADMFixed inValue);	
	ADMFixed ADMAPI (*GetMinFixedValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetMaxIntValue)(ADMItemRef inItem, ADMInt32 inValue);
	ADMInt32 ADMAPI (*GetMaxIntValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetMinFloatValue)(ADMItemRef inItem, float inValue);	
	float ADMAPI (*GetMinFloatValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetMaxFixedValue)(ADMItemRef inItem, ADMFixed inValue);	
	ADMFixed ADMAPI (*GetMaxFixedValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetMaxFloatValue)(ADMItemRef inItem, float inValue);	
	float ADMAPI (*GetMaxFloatValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetSmallIncrement)(ADMItemRef inItem, float inIncrement);	
	float ADMAPI (*GetSmallIncrement)(ADMItemRef inItem);
	
	void ADMAPI (*SetLargeIncrement)(ADMItemRef inItem, float inIncrement);
	float ADMAPI (*GetLargeIncrement)(ADMItemRef inItem);
	
	void ADMAPI (*SetAllowUnits)(ADMItemRef inItem, ADMBoolean inAllowUnits);
	ADMBoolean ADMAPI (*GetAllowUnits)(ADMItemRef inItem);

	void ADMAPI (*SetAllowMath)(ADMItemRef inItem, ADMBoolean inAllowMath);
	ADMBoolean ADMAPI (*GetAllowMath)(ADMItemRef inItem);
	
	void ADMAPI (*SetFloatToTextProc)(ADMItemRef inItem, ADMItemFloatToTextProc inProc);
	ADMItemFloatToTextProc ADMAPI (*GetFloatToTextProc)(ADMItemRef inItem);
	
	ADMBoolean ADMAPI (*DefaultFloatToText)(ADMItemRef inItem, float inValue, char* outText,
		ADMInt32 inMaxLength);

	ADMBoolean ADMAPI (*DefaultFloatToTextW)(ADMItemRef inItem, float inValue, ADMUnicode* outText,
		ADMInt32 inMaxLength);

	void ADMAPI (*SetTextToFloatProc)(ADMItemRef inItem, ADMItemTextToFloatProc inProc);
	ADMItemTextToFloatProc ADMAPI (*GetTextToFloatProc)(ADMItemRef inItem);

	ADMBoolean ADMAPI (*DefaultTextToFloat)(ADMItemRef inItem, const char* inText, float* outValue);
	ADMBoolean ADMAPI (*DefaultTextToFloatW)(ADMItemRef inItem, const ADMUnicode* inText, float* outValue);

	void ADMAPI (*ShowUnits)(ADMItemRef inItem, ADMBoolean inShowUnits);
	ADMBoolean ADMAPI (*GetShowUnits)(ADMItemRef inItem);

	ADMBoolean ADMAPI (*WasPercentageChange)(ADMItemRef inItem);

	// item help ID
	// dhearst 6/28/02 - ADM no longer supports ASHelp
	void ADMAPI (*SetHelpID_DEPRECATED)(ADMItemRef inItem, ADMInt32 inHelpID);
	ADMInt32 ADMAPI (*GetHelpID_DEPRECATED)(ADMItemRef inItem);
	void ADMAPI (*Help_DEPRECATED)(ADMItemRef inDialog);

	// hierarchy list accessor
	
	ADMHierarchyListRef ADMAPI (*GetHierarchyList)(ADMItemRef inItem);
	
	// item group accessors
	
 	void ADMAPI (*AddItem)(ADMItemRef inGroup, ADMItemRef inItem);
 	void ADMAPI (*RemoveItem)(ADMItemRef inGroup, ADMItemRef inItem);

	// item pictures (from icons)
	
	void ADMAPI (*SetPicture)(ADMItemRef inItem, ADMIconRef inPicture);
	ADMIconRef ADMAPI (*GetPicture)(ADMItemRef inItem);

	void ADMAPI (*SetSelectedPicture)(ADMItemRef inItem, ADMIconRef inPicture);
	ADMIconRef ADMAPI (*GetSelectedPicture)(ADMItemRef inItem);

	void ADMAPI (*SetDisabledPicture)(ADMItemRef inItem, ADMIconRef inPicture);
	ADMIconRef ADMAPI (*GetDisabledPicture)(ADMItemRef inItem);
	
	// popup control accessors
	
	void ADMAPI (*SetPopupDialog)(ADMItemRef inItem, ADMInt32 inPopupItemID, ADMDialogRef inDialog);
	ADMDialogRef ADMAPI (*GetPopupDialog)(ADMItemRef inItem);


	// Set/Get the WantsFocus property - whether or not the item wants to receive focus
	void ADMAPI (*SetWantsFocus)(ADMItemRef inItem, ADMBoolean inWantsFocus);
	ADMBoolean ADMAPI (*GetWantsFocus)(ADMItemRef inItem);

	// Basic color accessors for all applicable ADM items
	void ADMAPI (*SetForeColor)(ADMItemRef inItem, ADMColor inColor);
	ADMColor ADMAPI (*GetForeColor)(ADMItemRef inItem);
	void ADMAPI (*SetBackColor)(ADMItemRef inItem, ADMColor inColor);
	ADMColor ADMAPI (*GetBackColor)(ADMItemRef inItem);
}
ADMItemSuite6;

// -----------------------------------------------------------------------------

// =============================================================================
//		* ADM Item Suite, version 7
// =============================================================================

#define kADMItemSuiteVersion7 7

// -----------------------------------------------------------------------------

typedef struct ADMItemSuite7
{

	// *** This suite is FROZEN.
	// *** It shipped with Illustrator 10

	// item creation/destruction

	ADMItemRef ADMAPI (*Create)(ADMDialogRef inDialog, ADMInt32 inItemID,
				ADMItemType inItemType, const ADMRect* inBoundsRect,
				ADMItemInitProc inInitProc, ADMUserData inUserData,
				ADMInt32 inOptions);

	void ADMAPI (*Destroy)(ADMItemRef inItem);
	
	// item draw proc
	
	void ADMAPI (*SetDrawProc)(ADMItemRef inItem, ADMItemDrawProc inDrawProc);
	ADMItemDrawProc ADMAPI (*GetDrawProc)(ADMItemRef inItem);
	void ADMAPI (*DefaultDraw)(ADMItemRef inItem, ADMDrawerRef inDrawer);

	// item track proc
	
	void ADMAPI (*SetTrackProc)(ADMItemRef inItem, ADMItemTrackProc inTrackProc);
	ADMItemTrackProc ADMAPI (*GetTrackProc)(ADMItemRef inItem);
	ADMBoolean ADMAPI (*DefaultTrack)(ADMItemRef inItem, ADMTrackerRef inTracker);

	void ADMAPI (*SetMask)(ADMItemRef inItem, ADMActionMask inActionMask);
	ADMActionMask ADMAPI (*GetMask)(ADMItemRef inItem);

	// item notify proc

	void ADMAPI (*SetNotifyProc)(ADMItemRef inItem, ADMItemNotifyProc inNotifyProc);
	ADMItemNotifyProc ADMAPI (*GetNotifyProc)(ADMItemRef inItem);
	void ADMAPI (*DefaultNotify)(ADMItemRef inItem, ADMNotifierRef inNotifier);
	void ADMAPI (*SendNotify)(ADMItemRef inItem, const char* inNotifierType);

	void ADMAPI (*SetNotifierData)(ADMItemRef inItem, ADMUserData inNotifierData);
	ADMUserData ADMAPI (*GetNotifierData)(ADMItemRef inItem);

	// item destroy proc

	void ADMAPI (*SetDestroyProc)(ADMItemRef inItem, ADMItemDestroyProc inDestroyProc);
	ADMItemDestroyProc ADMAPI (*GetDestroyProc)(ADMItemRef inItem);
	
	// item timer
	
	ADMTimerRef ADMAPI (*CreateTimer)(ADMItemRef inItem, ADMUInt32 inMilliseconds,
				ADMActionMask inAbortMask, ADMItemTimerProc inTimerProc,
				ADMItemTimerAbortProc inTimerAbortProc, ADMInt32 inOptions);

	void ADMAPI (*AbortTimer)(ADMItemRef inItem, ADMTimerRef inTimer);

	// item user data

	void ADMAPI (*SetUserData)(ADMItemRef inItem, ADMUserData inUserData);
	ADMUserData ADMAPI (*GetUserData)(ADMItemRef inItem);

	// item information accessors

	ADMInt32 ADMAPI (*GetID)(ADMItemRef inItem);
	ADMDialogRef ADMAPI (*GetDialog)(ADMItemRef inItem);
	ADMWindowRef ADMAPI (*GetWindowRef)(ADMItemRef inItem);
	ADMListRef ADMAPI (*GetList)(ADMItemRef inItem);
	ADMItemRef ADMAPI (*GetChildItem)(ADMItemRef inItem, ADMInt32 inChildID);	

	void ADMAPI (*SetPluginRef)(ADMItemRef inItem, SPPluginRef inPluginRef);
	SPPluginRef ADMAPI (*GetPluginRef)(ADMItemRef inItem);

	void ADMAPI (*SetItemType)(ADMItemRef inItem, ADMItemType inItemType);
	ADMItemType ADMAPI (*GetItemType)(ADMItemRef inItem);
	
	void ADMAPI (*SetItemStyle)(ADMItemRef inItem, ADMItemStyle inItemStyle);
	ADMItemStyle ADMAPI (*GetItemStyle)(ADMItemRef inItem);
	
	// item state accessors
	
	void ADMAPI (*Show)(ADMItemRef inItem, ADMBoolean inShow);
	ADMBoolean ADMAPI (*IsVisible)(ADMItemRef inItem);
	
	void ADMAPI (*Enable)(ADMItemRef inItem, ADMBoolean inEnable);
	ADMBoolean ADMAPI (*IsEnabled)(ADMItemRef inItem);
	
	void ADMAPI (*Activate)(ADMItemRef inItem, ADMBoolean inActivate);
	ADMBoolean ADMAPI (*IsActive)(ADMItemRef inItem);
	
	void ADMAPI (*Known)(ADMItemRef inItem, ADMBoolean inKnown);
	ADMBoolean ADMAPI (*IsKnown)(ADMItemRef inItem);
	
	// item bounds accessors

	void ADMAPI (*SetLocalRect)(ADMItemRef inItem, const ADMRect* inLocalRect);
	void ADMAPI (*GetLocalRect)(ADMItemRef inItem, ADMRect* outLocalRect);
	
	void ADMAPI (*SetBoundsRect)(ADMItemRef inItem, const ADMRect* inBoundsRect);
	void ADMAPI (*GetBoundsRect)(ADMItemRef inItem, ADMRect* outBoundsRect);
	
	void ADMAPI (*GetBestSize)(ADMItemRef inItem, ADMPoint* outBestSize);

	void ADMAPI (*Move)(ADMItemRef inItem, ADMInt32 inHorizPosition, ADMInt32 inVertPosition);
	void ADMAPI (*Size)(ADMItemRef inItem, ADMInt32 inWidth, ADMInt32 inHeight);

	// coordinate system transformations	

	void ADMAPI (*LocalToScreenPoint)(ADMItemRef inItem, ADMPoint* ioPoint);
	void ADMAPI (*ScreenToLocalPoint)(ADMItemRef inItem, ADMPoint* ioPoint);
	
	void ADMAPI (*LocalToScreenRect)(ADMItemRef inItem, ADMRect* ioRect);
	void ADMAPI (*ScreenToLocalRect)(ADMItemRef inItem, ADMRect* ioRect);
	
	// item display
	
	void ADMAPI (*Invalidate)(ADMItemRef inItem);
	void ADMAPI (*InvalidateRect)(ADMItemRef inDialog, const ADMRect* inInvalRect);
	void ADMAPI (*Update)(ADMItemRef inItem);
	
	// cursor ID accessors
	
	ADMBoolean ADMAPI (*SetCursorID)(ADMItemRef inItem, SPPluginRef inPluginRef, ADMInt32 inCursorID,
				const char* inCursorName);

	void ADMAPI (*GetCursorID)(ADMItemRef inItem, SPPluginRef* outPluginRef, ADMInt32* outCursorID,
				const char** outCursorName);

	// picture ID accessors

	void ADMAPI (*SetPictureID)(ADMItemRef inItem, ADMInt32 inPictureResID,
				const char* inPictureResName);

	void ADMAPI (*GetPictureID)(ADMItemRef inItem, ADMInt32* outPictureResID,
				const char** outPictureResName);
	
	void ADMAPI (*SetSelectedPictureID)(ADMItemRef inItem, ADMInt32 inPictureResID,
				const char* inPictureResName);

	void ADMAPI (*GetSelectedPictureID)(ADMItemRef inItem, ADMInt32* outPictureResID,
				const char** outPictureResName);
	
	void ADMAPI (*SetDisabledPictureID)(ADMItemRef inItem, ADMInt32 inPictureResID,
				const char* inPictureResName);

	void ADMAPI (*GetDisabledPictureID)(ADMItemRef inItem, ADMInt32* outPictureResID,
				const char** outPictureResName);

	// tooltips

	void ADMAPI (*SetTipString)(ADMItemRef inItem, const char* inTipString);
	void ADMAPI (*SetTipStringW)(ADMItemRef inItem, const ADMUnicode* inTipString);

	void ADMAPI (*GetTipString)(ADMItemRef inItem, char* outTipString, ADMInt32 inMaxLength);
	void ADMAPI (*GetTipStringW)(ADMItemRef inItem, ADMUnicode* outTipString, ADMInt32 inMaxLength);
	
	ADMInt32 ADMAPI (*GetTipStringLength)(ADMItemRef inItem);
	ADMInt32 ADMAPI (*GetTipStringLengthW)(ADMItemRef inItem);
	
	void ADMAPI (*EnableTip)(ADMItemRef inItem, ADMBoolean inEnable);
	ADMBoolean ADMAPI (*IsTipEnabled)(ADMItemRef inItem);
	
	void ADMAPI (*ShowToolTip)(ADMItemRef inItem, const ADMPoint* inWhere);
	void ADMAPI (*HideToolTip)(ADMItemRef inItem);
	
	// item text accessors

	void ADMAPI (*SetFont)(ADMItemRef inItem, ADMFont inFontID);
	ADMFont ADMAPI (*GetFont)(ADMItemRef inItem);

	void ADMAPI (*SetText)(ADMItemRef inItem, const char* inText);
	void ADMAPI (*SetTextW)(ADMItemRef inItem, const ADMUnicode* inText);

	void ADMAPI (*GetText)(ADMItemRef inItem, char* outText, ADMInt32 inMaxLength);
	void ADMAPI (*GetTextW)(ADMItemRef inItem, ADMUnicode* outText, ADMInt32 inMaxLength);

	ADMInt32 ADMAPI (*GetTextLength)(ADMItemRef inItem);
	ADMInt32 ADMAPI (*GetTextLengthW)(ADMItemRef inItem);
	
	void ADMAPI (*SetMaxTextLength)(ADMItemRef inItem, ADMInt32 inLength);
	ADMInt32 ADMAPI (*GetMaxTextLength)(ADMItemRef inItem);
	
	void ADMAPI (*SelectAll)(ADMItemRef inItem);
	void ADMAPI (*SetSelectionRange)(ADMItemRef inItem, ADMInt32 inSelStart, ADMInt32 inSelEnd);
	void ADMAPI (*GetSelectionRange)(ADMItemRef inItem, ADMInt32* outSelStart, ADMInt32* outSelEnd);

	void ADMAPI (*SetJustify)(ADMItemRef inItem, ADMJustify inJustify);
	ADMJustify ADMAPI (*GetJustify)(ADMItemRef inItem);
	
	void ADMAPI (*SetUnits)(ADMItemRef inItem, ADMUnits inUnits);
	ADMUnits ADMAPI (*GetUnits)(ADMItemRef inItem);
	
	// item value accessors

	void ADMAPI (*SetPrecision)(ADMItemRef inItem, ADMInt32 inNumberOfDecimalPlaces);
	ADMInt32 ADMAPI (*GetPrecision)(ADMItemRef inItem);
	
	void ADMAPI (*SetBooleanValue)(ADMItemRef inItem, ADMBoolean inValue);
	ADMBoolean ADMAPI (*GetBooleanValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetIntValue)(ADMItemRef inItem, ADMInt32 inValue);
	ADMInt32 ADMAPI (*GetIntValue)(ADMItemRef inItem);
		
	void ADMAPI (*SetFixedValue)(ADMItemRef inItem, ADMFixed inValue);	
	ADMFixed ADMAPI (*GetFixedValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetFloatValue)(ADMItemRef inItem, float inValue);	
	float ADMAPI (*GetFloatValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetMinIntValue)(ADMItemRef inItem, ADMInt32 inValue);
	ADMInt32 ADMAPI (*GetMinIntValue)(ADMItemRef inItem);
		
	void ADMAPI (*SetMinFixedValue)(ADMItemRef inItem, ADMFixed inValue);	
	ADMFixed ADMAPI (*GetMinFixedValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetMaxIntValue)(ADMItemRef inItem, ADMInt32 inValue);
	ADMInt32 ADMAPI (*GetMaxIntValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetMinFloatValue)(ADMItemRef inItem, float inValue);	
	float ADMAPI (*GetMinFloatValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetMaxFixedValue)(ADMItemRef inItem, ADMFixed inValue);	
	ADMFixed ADMAPI (*GetMaxFixedValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetMaxFloatValue)(ADMItemRef inItem, float inValue);	
	float ADMAPI (*GetMaxFloatValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetSmallIncrement)(ADMItemRef inItem, float inIncrement);	
	float ADMAPI (*GetSmallIncrement)(ADMItemRef inItem);
	
	void ADMAPI (*SetLargeIncrement)(ADMItemRef inItem, float inIncrement);
	float ADMAPI (*GetLargeIncrement)(ADMItemRef inItem);
	
	void ADMAPI (*SetAllowUnits)(ADMItemRef inItem, ADMBoolean inAllowUnits);
	ADMBoolean ADMAPI (*GetAllowUnits)(ADMItemRef inItem);

	void ADMAPI (*SetAllowMath)(ADMItemRef inItem, ADMBoolean inAllowMath);
	ADMBoolean ADMAPI (*GetAllowMath)(ADMItemRef inItem);
	
	void ADMAPI (*SetFloatToTextProc)(ADMItemRef inItem, ADMItemFloatToTextProc inProc);
	ADMItemFloatToTextProc ADMAPI (*GetFloatToTextProc)(ADMItemRef inItem);
	
	ADMBoolean ADMAPI (*DefaultFloatToText)(ADMItemRef inItem, float inValue, char* outText,
		ADMInt32 inMaxLength);

	ADMBoolean ADMAPI (*DefaultFloatToTextW)(ADMItemRef inItem, float inValue, ADMUnicode* outText,
		ADMInt32 inMaxLength);

	void ADMAPI (*SetTextToFloatProc)(ADMItemRef inItem, ADMItemTextToFloatProc inProc);
	ADMItemTextToFloatProc ADMAPI (*GetTextToFloatProc)(ADMItemRef inItem);

	ADMBoolean ADMAPI (*DefaultTextToFloat)(ADMItemRef inItem, const char* inText, float* outValue);
	ADMBoolean ADMAPI (*DefaultTextToFloatW)(ADMItemRef inItem, const ADMUnicode* inText, float* outValue);

	void ADMAPI (*ShowUnits)(ADMItemRef inItem, ADMBoolean inShowUnits);
	ADMBoolean ADMAPI (*GetShowUnits)(ADMItemRef inItem);

	ADMBoolean ADMAPI (*WasPercentageChange)(ADMItemRef inItem);

	// item help ID
	// dhearst 6/28/02 - ADM no longer supports ASHelp
	void ADMAPI (*SetHelpID_DEPRECATED)(ADMItemRef inItem, ADMInt32 inHelpID);
	ADMInt32 ADMAPI (*GetHelpID_DEPRECATED)(ADMItemRef inItem);
	void ADMAPI (*Help_DEPRECATED)(ADMItemRef inDialog);

	// hierarchy list accessor
	
	ADMHierarchyListRef ADMAPI (*GetHierarchyList)(ADMItemRef inItem);
	
	// item group accessors
	
 	void ADMAPI (*AddItem)(ADMItemRef inGroup, ADMItemRef inItem);
 	void ADMAPI (*RemoveItem)(ADMItemRef inGroup, ADMItemRef inItem);

	// item pictures (from icons)
	
	void ADMAPI (*SetPicture)(ADMItemRef inItem, ADMIconRef inPicture);
	ADMIconRef ADMAPI (*GetPicture)(ADMItemRef inItem);

	void ADMAPI (*SetSelectedPicture)(ADMItemRef inItem, ADMIconRef inPicture);
	ADMIconRef ADMAPI (*GetSelectedPicture)(ADMItemRef inItem);

	void ADMAPI (*SetDisabledPicture)(ADMItemRef inItem, ADMIconRef inPicture);
	ADMIconRef ADMAPI (*GetDisabledPicture)(ADMItemRef inItem);
	
	// popup control accessors
	
	void ADMAPI (*SetPopupDialog)(ADMItemRef inItem, ADMInt32 inPopupItemID, ADMDialogRef inDialog);
	ADMDialogRef ADMAPI (*GetPopupDialog)(ADMItemRef inItem);


	// Set/Get the WantsFocus property - whether or not the item wants to receive focus
	void ADMAPI (*SetWantsFocus)(ADMItemRef inItem, ADMBoolean inWantsFocus);
	ADMBoolean ADMAPI (*GetWantsFocus)(ADMItemRef inItem);

	// Basic color accessors for all applicable ADM items
	void ADMAPI (*SetForeColor)(ADMItemRef inItem, ADMColor inColor);
	ADMColor ADMAPI (*GetForeColor)(ADMItemRef inItem);
	void ADMAPI (*SetBackColor)(ADMItemRef inItem, ADMColor inColor);
	ADMColor ADMAPI (*GetBackColor)(ADMItemRef inItem);

	
	//Accessor functions for Rollover state.

	void ADMAPI (*SetRolloverPictureID)(ADMItemRef inItem, ADMInt32 inPictureResID,
				const char* inPictureResName);

	void ADMAPI (*GetRolloverPictureID)(ADMItemRef inItem, ADMInt32* outPictureResID,
				const char** outPictureResName);

	void ADMAPI (*SetRolloverPicture)(ADMItemRef inItem, ADMIconRef inPicture);
	ADMIconRef ADMAPI (*GetRolloverPicture)(ADMItemRef inItem);

	// Set/Get the Has Rollover property - whether or not the item wants to have rollover
	void ADMAPI (*SetHasRollOverProperty)(ADMItemRef inItem, ADMBoolean inRollover);
	ADMBoolean ADMAPI (*GetHasRollOverProperty)(ADMItemRef inItem);

	// Set/Get whether or not the item is currently rolled over or not
	void ADMAPI (*SetInRollOverState)(ADMItemRef inItem, ADMBoolean inRolloverState);
	ADMBoolean ADMAPI (*IsInRollOverState)(ADMItemRef inItem);

}
ADMItemSuite7;

// -----------------------------------------------------------------------------

// =============================================================================
//		* ADM Item Suite, suite 8
// =============================================================================

#define kADMItemSuiteVersion8 8

// -----------------------------------------------------------------------------

typedef struct ADMItemSuite8
{
	// *** This suite is CLOSED for changes.
	// *** It shipped with Photoshop 7.0/ImageReady 7.0.

	// item creation/destruction

	ADMItemRef ADMAPI (*Create)(ADMDialogRef inDialog, ADMInt32 inItemID,
				ADMItemType inItemType, const ADMRect* inBoundsRect,
				ADMItemInitProc inInitProc, ADMUserData inUserData,
				ADMInt32 inOptions);

	void ADMAPI (*Destroy)(ADMItemRef inItem);
	
	// item draw proc
	
	void ADMAPI (*SetDrawProc)(ADMItemRef inItem, ADMItemDrawProc inDrawProc);
	ADMItemDrawProc ADMAPI (*GetDrawProc)(ADMItemRef inItem);
	void ADMAPI (*DefaultDraw)(ADMItemRef inItem, ADMDrawerRef inDrawer);

	// item track proc
	
	void ADMAPI (*SetTrackProc)(ADMItemRef inItem, ADMItemTrackProc inTrackProc);
	ADMItemTrackProc ADMAPI (*GetTrackProc)(ADMItemRef inItem);
	ADMBoolean ADMAPI (*DefaultTrack)(ADMItemRef inItem, ADMTrackerRef inTracker);

	void ADMAPI (*SetMask)(ADMItemRef inItem, ADMActionMask inActionMask);
	ADMActionMask ADMAPI (*GetMask)(ADMItemRef inItem);

	// item notify proc

	void ADMAPI (*SetNotifyProc)(ADMItemRef inItem, ADMItemNotifyProc inNotifyProc);
	ADMItemNotifyProc ADMAPI (*GetNotifyProc)(ADMItemRef inItem);
	void ADMAPI (*DefaultNotify)(ADMItemRef inItem, ADMNotifierRef inNotifier);
	void ADMAPI (*SendNotify)(ADMItemRef inItem, const char* inNotifierType);

	void ADMAPI (*SetNotifierData)(ADMItemRef inItem, ADMUserData inNotifierData);
	ADMUserData ADMAPI (*GetNotifierData)(ADMItemRef inItem);

	// item destroy proc

	void ADMAPI (*SetDestroyProc)(ADMItemRef inItem, ADMItemDestroyProc inDestroyProc);
	ADMItemDestroyProc ADMAPI (*GetDestroyProc)(ADMItemRef inItem);
	
	// item timer
	
	ADMTimerRef ADMAPI (*CreateTimer)(ADMItemRef inItem, ADMUInt32 inMilliseconds,
				ADMActionMask inAbortMask, ADMItemTimerProc inTimerProc,
				ADMItemTimerAbortProc inTimerAbortProc, ADMInt32 inOptions);

	void ADMAPI (*AbortTimer)(ADMItemRef inItem, ADMTimerRef inTimer);

	// item user data

	void ADMAPI (*SetUserData)(ADMItemRef inItem, ADMUserData inUserData);
	ADMUserData ADMAPI (*GetUserData)(ADMItemRef inItem);

	// item information accessors

	ADMInt32 ADMAPI (*GetID)(ADMItemRef inItem);
	ADMDialogRef ADMAPI (*GetDialog)(ADMItemRef inItem);
	ADMWindowRef ADMAPI (*GetWindowRef)(ADMItemRef inItem);
	ADMListRef ADMAPI (*GetList)(ADMItemRef inItem);
	ADMItemRef ADMAPI (*GetChildItem)(ADMItemRef inItem, ADMInt32 inChildID);	

	void ADMAPI (*SetPluginRef)(ADMItemRef inItem, SPPluginRef inPluginRef);
	SPPluginRef ADMAPI (*GetPluginRef)(ADMItemRef inItem);

	void ADMAPI (*SetItemType)(ADMItemRef inItem, ADMItemType inItemType);
	ADMItemType ADMAPI (*GetItemType)(ADMItemRef inItem);
	
	void ADMAPI (*SetItemStyle)(ADMItemRef inItem, ADMItemStyle inItemStyle);
	ADMItemStyle ADMAPI (*GetItemStyle)(ADMItemRef inItem);
	
	// item state accessors
	
	void ADMAPI (*Show)(ADMItemRef inItem, ADMBoolean inShow);
	ADMBoolean ADMAPI (*IsVisible)(ADMItemRef inItem);
	
	void ADMAPI (*Enable)(ADMItemRef inItem, ADMBoolean inEnable);
	ADMBoolean ADMAPI (*IsEnabled)(ADMItemRef inItem);
	
	void ADMAPI (*Activate)(ADMItemRef inItem, ADMBoolean inActivate);
	ADMBoolean ADMAPI (*IsActive)(ADMItemRef inItem);
	
	void ADMAPI (*Known)(ADMItemRef inItem, ADMBoolean inKnown);
	ADMBoolean ADMAPI (*IsKnown)(ADMItemRef inItem);
	
	// item bounds accessors

	void ADMAPI (*SetLocalRect)(ADMItemRef inItem, const ADMRect* inLocalRect);
	void ADMAPI (*GetLocalRect)(ADMItemRef inItem, ADMRect* outLocalRect);
	
	void ADMAPI (*SetBoundsRect)(ADMItemRef inItem, const ADMRect* inBoundsRect);
	void ADMAPI (*GetBoundsRect)(ADMItemRef inItem, ADMRect* outBoundsRect);
	
	void ADMAPI (*GetBestSize)(ADMItemRef inItem, ADMPoint* outBestSize);

	void ADMAPI (*Move)(ADMItemRef inItem, ADMInt32 inHorizPosition, ADMInt32 inVertPosition);
	void ADMAPI (*Size)(ADMItemRef inItem, ADMInt32 inWidth, ADMInt32 inHeight);

	// coordinate system transformations	

	void ADMAPI (*LocalToScreenPoint)(ADMItemRef inItem, ADMPoint* ioPoint);
	void ADMAPI (*ScreenToLocalPoint)(ADMItemRef inItem, ADMPoint* ioPoint);
	
	void ADMAPI (*LocalToScreenRect)(ADMItemRef inItem, ADMRect* ioRect);
	void ADMAPI (*ScreenToLocalRect)(ADMItemRef inItem, ADMRect* ioRect);
	
	// item display
	
	void ADMAPI (*Invalidate)(ADMItemRef inItem);
	void ADMAPI (*InvalidateRect)(ADMItemRef inDialog, const ADMRect* inInvalRect);
	void ADMAPI (*Update)(ADMItemRef inItem);
	
	// cursor ID accessors
	
	ADMBoolean ADMAPI (*SetCursorID)(ADMItemRef inItem, SPPluginRef inPluginRef, ADMInt32 inCursorID,
				const char* inCursorName);

	void ADMAPI (*GetCursorID)(ADMItemRef inItem, SPPluginRef* outPluginRef, ADMInt32* outCursorID,
				const char** outCursorName);

	// picture ID accessors

	void ADMAPI (*SetPictureID)(ADMItemRef inItem, ADMInt32 inPictureResID,
				const char* inPictureResName);

	void ADMAPI (*GetPictureID)(ADMItemRef inItem, ADMInt32* outPictureResID,
				const char** outPictureResName);
	
	void ADMAPI (*SetSelectedPictureID)(ADMItemRef inItem, ADMInt32 inPictureResID,
				const char* inPictureResName);

	void ADMAPI (*GetSelectedPictureID)(ADMItemRef inItem, ADMInt32* outPictureResID,
				const char** outPictureResName);
	
	void ADMAPI (*SetDisabledPictureID)(ADMItemRef inItem, ADMInt32 inPictureResID,
				const char* inPictureResName);

	void ADMAPI (*GetDisabledPictureID)(ADMItemRef inItem, ADMInt32* outPictureResID,
				const char** outPictureResName);

	// tooltips

	void ADMAPI (*SetTipString)(ADMItemRef inItem, const char* inTipString);
	void ADMAPI (*SetTipStringW)(ADMItemRef inItem, const ADMUnicode* inTipString);

	void ADMAPI (*GetTipString)(ADMItemRef inItem, char* outTipString, ADMInt32 inMaxLength);
	void ADMAPI (*GetTipStringW)(ADMItemRef inItem, ADMUnicode* outTipString, ADMInt32 inMaxLength);
	
	ADMInt32 ADMAPI (*GetTipStringLength)(ADMItemRef inItem);
	ADMInt32 ADMAPI (*GetTipStringLengthW)(ADMItemRef inItem);
	
	void ADMAPI (*EnableTip)(ADMItemRef inItem, ADMBoolean inEnable);
	ADMBoolean ADMAPI (*IsTipEnabled)(ADMItemRef inItem);
	
	void ADMAPI (*ShowToolTip)(ADMItemRef inItem, const ADMPoint* inWhere);
	void ADMAPI (*HideToolTip)(ADMItemRef inItem);
	
	// item text accessors

	void ADMAPI (*SetFont)(ADMItemRef inItem, ADMFont inFontID);
	ADMFont ADMAPI (*GetFont)(ADMItemRef inItem);

	void ADMAPI (*SetText)(ADMItemRef inItem, const char* inText);
	void ADMAPI (*SetTextW)(ADMItemRef inItem, const ADMUnicode* inText);

	void ADMAPI (*GetText)(ADMItemRef inItem, char* outText, ADMInt32 inMaxLength);
	void ADMAPI (*GetTextW)(ADMItemRef inItem, ADMUnicode* outText, ADMInt32 inMaxLength);

	ADMInt32 ADMAPI (*GetTextLength)(ADMItemRef inItem);
	ADMInt32 ADMAPI (*GetTextLengthW)(ADMItemRef inItem);
	
	void ADMAPI (*SetMaxTextLength)(ADMItemRef inItem, ADMInt32 inLength);
	ADMInt32 ADMAPI (*GetMaxTextLength)(ADMItemRef inItem);
	
	void ADMAPI (*SelectAll)(ADMItemRef inItem);
	void ADMAPI (*SetSelectionRange)(ADMItemRef inItem, ADMInt32 inSelStart, ADMInt32 inSelEnd);
	void ADMAPI (*GetSelectionRange)(ADMItemRef inItem, ADMInt32* outSelStart, ADMInt32* outSelEnd);

	void ADMAPI (*SetJustify)(ADMItemRef inItem, ADMJustify inJustify);
	ADMJustify ADMAPI (*GetJustify)(ADMItemRef inItem);
	
	void ADMAPI (*SetUnits)(ADMItemRef inItem, ADMUnits inUnits);
	ADMUnits ADMAPI (*GetUnits)(ADMItemRef inItem);
	
	// item value accessors

	void ADMAPI (*SetPrecision)(ADMItemRef inItem, ADMInt32 inNumberOfDecimalPlaces);
	ADMInt32 ADMAPI (*GetPrecision)(ADMItemRef inItem);
	
	void ADMAPI (*SetBooleanValue)(ADMItemRef inItem, ADMBoolean inValue);
	ADMBoolean ADMAPI (*GetBooleanValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetIntValue)(ADMItemRef inItem, ADMInt32 inValue);
	ADMInt32 ADMAPI (*GetIntValue)(ADMItemRef inItem);
		
	void ADMAPI (*SetFixedValue)(ADMItemRef inItem, ADMFixed inValue);	
	ADMFixed ADMAPI (*GetFixedValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetFloatValue)(ADMItemRef inItem, float inValue);	
	float ADMAPI (*GetFloatValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetMinIntValue)(ADMItemRef inItem, ADMInt32 inValue);
	ADMInt32 ADMAPI (*GetMinIntValue)(ADMItemRef inItem);
		
	void ADMAPI (*SetMinFixedValue)(ADMItemRef inItem, ADMFixed inValue);	
	ADMFixed ADMAPI (*GetMinFixedValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetMaxIntValue)(ADMItemRef inItem, ADMInt32 inValue);
	ADMInt32 ADMAPI (*GetMaxIntValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetMinFloatValue)(ADMItemRef inItem, float inValue);	
	float ADMAPI (*GetMinFloatValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetMaxFixedValue)(ADMItemRef inItem, ADMFixed inValue);	
	ADMFixed ADMAPI (*GetMaxFixedValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetMaxFloatValue)(ADMItemRef inItem, float inValue);	
	float ADMAPI (*GetMaxFloatValue)(ADMItemRef inItem);
	
	void ADMAPI (*SetSmallIncrement)(ADMItemRef inItem, float inIncrement);	
	float ADMAPI (*GetSmallIncrement)(ADMItemRef inItem);
	
	void ADMAPI (*SetLargeIncrement)(ADMItemRef inItem, float inIncrement);
	float ADMAPI (*GetLargeIncrement)(ADMItemRef inItem);
	
	void ADMAPI (*SetAllowUnits)(ADMItemRef inItem, ADMBoolean inAllowUnits);
	ADMBoolean ADMAPI (*GetAllowUnits)(ADMItemRef inItem);

	void ADMAPI (*SetAllowMath)(ADMItemRef inItem, ADMBoolean inAllowMath);
	ADMBoolean ADMAPI (*GetAllowMath)(ADMItemRef inItem);
	
	void ADMAPI (*SetFloatToTextProc)(ADMItemRef inItem, ADMItemFloatToTextProc inProc);
	ADMItemFloatToTextProc ADMAPI (*GetFloatToTextProc)(ADMItemRef inItem);
	
	ADMBoolean ADMAPI (*DefaultFloatToText)(ADMItemRef inItem, float inValue, char* outText,
		ADMInt32 inMaxLength);

	ADMBoolean ADMAPI (*DefaultFloatToTextW)(ADMItemRef inItem, float inValue, ADMUnicode* outText,
		ADMInt32 inMaxLength);

	void ADMAPI (*SetTextToFloatProc)(ADMItemRef inItem, ADMItemTextToFloatProc inProc);
	ADMItemTextToFloatProc ADMAPI (*GetTextToFloatProc)(ADMItemRef inItem);

	ADMBoolean ADMAPI (*DefaultTextToFloat)(ADMItemRef inItem, const char* inText, float* outValue);
	ADMBoolean ADMAPI (*DefaultTextToFloatW)(ADMItemRef inItem, const ADMUnicode* inText, float* outValue);

	void ADMAPI (*ShowUnits)(ADMItemRef inItem, ADMBoolean inShowUnits);
	ADMBoolean ADMAPI (*GetShowUnits)(ADMItemRef inItem);

	ADMBoolean ADMAPI (*WasPercentageChange)(ADMItemRef inItem);

	// item help ID
	// dhearst 6/28/02 - ADM no longer supports ASHelp
	void ADMAPI (*SetHelpID_DEPRECATED)(ADMItemRef inItem, ADMInt32 inHelpID);
	ADMInt32 ADMAPI (*GetHelpID_DEPRECATED)(ADMItemRef inItem);
	void ADMAPI (*Help_DEPRECATED)(ADMItemRef inDialog);

	// hierarchy list accessor
	
	ADMHierarchyListRef ADMAPI (*GetHierarchyList)(ADMItemRef inItem);
	
	// item group accessors
	
 	void ADMAPI (*AddItem)(ADMItemRef inGroup, ADMItemRef inItem);
 	void ADMAPI (*RemoveItem)(ADMItemRef inGroup, ADMItemRef inItem);

	// item pictures (from icons)
	
	void ADMAPI (*SetPicture)(ADMItemRef inItem, ADMIconRef inPicture);
	ADMIconRef ADMAPI (*GetPicture)(ADMItemRef inItem);

	void ADMAPI (*SetSelectedPicture)(ADMItemRef inItem, ADMIconRef inPicture);
	ADMIconRef ADMAPI (*GetSelectedPicture)(ADMItemRef inItem);

	void ADMAPI (*SetDisabledPicture)(ADMItemRef inItem, ADMIconRef inPicture);
	ADMIconRef ADMAPI (*GetDisabledPicture)(ADMItemRef inItem);
	
	// popup control accessors
	
	void ADMAPI (*SetPopupDialog)(ADMItemRef inItem, ADMInt32 inPopupItemID, ADMDialogRef inDialog);
	ADMDialogRef ADMAPI (*GetPopupDialog)(ADMItemRef inItem);


	// Set/Get the WantsFocus property - whether or not the item wants to receive focus
	void ADMAPI (*SetWantsFocus)(ADMItemRef inItem, ADMBoolean inWantsFocus);
	ADMBoolean ADMAPI (*GetWantsFocus)(ADMItemRef inItem);

	// Basic color accessors for all applicable ADM items
	void ADMAPI (*SetForeColor)(ADMItemRef inItem, ADMColor inColor);
	ADMColor ADMAPI (*GetForeColor)(ADMItemRef inItem);
	void ADMAPI (*SetBackColor)(ADMItemRef inItem, ADMColor inColor);
	ADMColor ADMAPI (*GetBackColor)(ADMItemRef inItem);

	
	//Accessor functions for Rollover state.

	void ADMAPI (*SetRolloverPictureID)(ADMItemRef inItem, ADMInt32 inPictureResID,
				const char* inPictureResName);

	void ADMAPI (*GetRolloverPictureID)(ADMItemRef inItem, ADMInt32* outPictureResID,
				const char** outPictureResName);

	void ADMAPI (*SetRolloverPicture)(ADMItemRef inItem, ADMIconRef inPicture);
	ADMIconRef ADMAPI (*GetRolloverPicture)(ADMItemRef inItem);

	// Set/Get the Has Rollover property - whether or not the item wants to have rollover
	void ADMAPI (*SetHasRollOverProperty)(ADMItemRef inItem, ADMBoolean inRollover);
	ADMBoolean ADMAPI (*GetHasRollOverProperty)(ADMItemRef inItem);

	// Set/Get whether or not the item is currently rolled over or not
	void ADMAPI (*SetInRollOverState)(ADMItemRef inItem, ADMBoolean inRolloverState);
	ADMBoolean ADMAPI (*IsInRollOverState)(ADMItemRef inItem);

	// Mutator for overriding roman script forcing of item fonts. Normally one would
	// set this with the kADMIgnoreRomanFontForcing flag (see ADMTypes.h) set as a
	// mask on the options argument in the item's Create() call. Items that are 
	// created in dialogs that are defined by platform resources do not have that 
	// ability, however, hence the mutator. Roman font forcing may be set globally by
	// client apps or on a per-dialog basis. Clients may have a need to override
	// on some items, so do that either via Create() or do it after the fact with
	// the IgnoreForceRoman() call.
	void ADMAPI (*IgnoreForceRoman)(ADMItemRef inItem, ADMBoolean inIgnoreForceRoman);

}
ADMItemSuite8;

// -----------------------------------------------------------------------------

// =============================================================================
//		* ADM Item Suite, suite 9
// =============================================================================

#define kADMItemSuiteVersion9 9

// -----------------------------------------------------------------------------

typedef struct ADMItemSuite9
{
	// *** This suite is FROZEN.
	// *** It shipped with Acrobat 6.0.
	
	// item creation/destruction

	/** ... */
	ADMItemRef ADMAPI (*Create)(ADMDialogRef inDialog, ADMInt32 inItemID,
				ADMItemType inItemType, const ADMRect* inBoundsRect,
				ADMItemInitProc inInitProc, ADMUserData inUserData,
				ADMInt32 inOptions);

	/** ... */
	void ADMAPI (*Destroy)(ADMItemRef inItem);
	
	// item draw proc
	
	/** ... */
	void ADMAPI (*SetDrawProc)(ADMItemRef inItem, ADMItemDrawProc inDrawProc);
	/** ... */
	ADMItemDrawProc ADMAPI (*GetDrawProc)(ADMItemRef inItem);
	/** ... */
	void ADMAPI (*DefaultDraw)(ADMItemRef inItem, ADMDrawerRef inDrawer);

	// item track proc
	
	/** ... */
	void ADMAPI (*SetTrackProc)(ADMItemRef inItem, ADMItemTrackProc inTrackProc);
	/** ... */
	ADMItemTrackProc ADMAPI (*GetTrackProc)(ADMItemRef inItem);
	/** ... */
	ADMBoolean ADMAPI (*DefaultTrack)(ADMItemRef inItem, ADMTrackerRef inTracker);

	/** ... */
	void ADMAPI (*SetMask)(ADMItemRef inItem, ADMActionMask inActionMask);
	/** ... */
	ADMActionMask ADMAPI (*GetMask)(ADMItemRef inItem);

	// item notify proc

	/** ... */
	void ADMAPI (*SetNotifyProc)(ADMItemRef inItem, ADMItemNotifyProc inNotifyProc);
	/** ... */
	ADMItemNotifyProc ADMAPI (*GetNotifyProc)(ADMItemRef inItem);
	/** ... */
	void ADMAPI (*DefaultNotify)(ADMItemRef inItem, ADMNotifierRef inNotifier);
	/** ... */
	void ADMAPI (*SendNotify)(ADMItemRef inItem, const char* inNotifierType);

	/** ... */
	void ADMAPI (*SetNotifierData)(ADMItemRef inItem, ADMUserData inNotifierData);
	/** ... */
	ADMUserData ADMAPI (*GetNotifierData)(ADMItemRef inItem);

	// item destroy proc

	/** ... */
	void ADMAPI (*SetDestroyProc)(ADMItemRef inItem, ADMItemDestroyProc inDestroyProc);
	/** ... */
	ADMItemDestroyProc ADMAPI (*GetDestroyProc)(ADMItemRef inItem);
	
	// item timer
	
	/** ... */
	ADMTimerRef ADMAPI (*CreateTimer)(ADMItemRef inItem, ADMUInt32 inMilliseconds,
				ADMActionMask inAbortMask, ADMItemTimerProc inTimerProc,
				ADMItemTimerAbortProc inTimerAbortProc, ADMInt32 inOptions);

	/** ... */
	void ADMAPI (*AbortTimer)(ADMItemRef inItem, ADMTimerRef inTimer);

	// item user data

	/** ... */
	void ADMAPI (*SetUserData)(ADMItemRef inItem, ADMUserData inUserData);
	/** ... */
	ADMUserData ADMAPI (*GetUserData)(ADMItemRef inItem);

	// item information accessors

	/** ... */
	ADMInt32 ADMAPI (*GetID)(ADMItemRef inItem);
	/** ... */
	ADMDialogRef ADMAPI (*GetDialog)(ADMItemRef inItem);
	/** ... */
	ADMWindowRef ADMAPI (*GetWindowRef)(ADMItemRef inItem);
	/** ... */
	ADMListRef ADMAPI (*GetList)(ADMItemRef inItem);
	/** ... */
	ADMItemRef ADMAPI (*GetChildItem)(ADMItemRef inItem, ADMInt32 inChildID);	

	/** ... */
	void ADMAPI (*SetPluginRef)(ADMItemRef inItem, SPPluginRef inPluginRef);
	/** ... */
	SPPluginRef ADMAPI (*GetPluginRef)(ADMItemRef inItem);

	/** ... */
	void ADMAPI (*SetItemType)(ADMItemRef inItem, ADMItemType inItemType);
	/** ... */
	ADMItemType ADMAPI (*GetItemType)(ADMItemRef inItem);
	
	/** ... */
	void ADMAPI (*SetItemStyle)(ADMItemRef inItem, ADMItemStyle inItemStyle);
	/** ... */
	ADMItemStyle ADMAPI (*GetItemStyle)(ADMItemRef inItem);
	
	// item state accessors
	
	/** ... */
	void ADMAPI (*Show)(ADMItemRef inItem, ADMBoolean inShow);
	/** ... */
	ADMBoolean ADMAPI (*IsVisible)(ADMItemRef inItem);
	
	/** ... */
	void ADMAPI (*Enable)(ADMItemRef inItem, ADMBoolean inEnable);
	/** ... */
	ADMBoolean ADMAPI (*IsEnabled)(ADMItemRef inItem);
	
	/** ... */
	void ADMAPI (*Activate)(ADMItemRef inItem, ADMBoolean inActivate);
	/** ... */
	ADMBoolean ADMAPI (*IsActive)(ADMItemRef inItem);
	
	/** ... */
	void ADMAPI (*Known)(ADMItemRef inItem, ADMBoolean inKnown);
	/** ... */
	ADMBoolean ADMAPI (*IsKnown)(ADMItemRef inItem);
	
	// item bounds accessors

	/** ... */
	void ADMAPI (*SetLocalRect)(ADMItemRef inItem, const ADMRect* inLocalRect);
	/** ... */
	void ADMAPI (*GetLocalRect)(ADMItemRef inItem, ADMRect* outLocalRect);
	
	/** ... */
	void ADMAPI (*SetBoundsRect)(ADMItemRef inItem, const ADMRect* inBoundsRect);
	/** ... */
	void ADMAPI (*GetBoundsRect)(ADMItemRef inItem, ADMRect* outBoundsRect);
	
	/** ... */
	void ADMAPI (*GetBestSize)(ADMItemRef inItem, ADMPoint* outBestSize);

	/** ... */
	void ADMAPI (*Move)(ADMItemRef inItem, ADMInt32 inHorizPosition, ADMInt32 inVertPosition);
	/** ... */
	void ADMAPI (*Size)(ADMItemRef inItem, ADMInt32 inWidth, ADMInt32 inHeight);

	// coordinate system transformations	

	/** ... */
	void ADMAPI (*LocalToScreenPoint)(ADMItemRef inItem, ADMPoint* ioPoint);
	/** ... */
	void ADMAPI (*ScreenToLocalPoint)(ADMItemRef inItem, ADMPoint* ioPoint);
	
	/** ... */
	void ADMAPI (*LocalToScreenRect)(ADMItemRef inItem, ADMRect* ioRect);
	/** ... */
	void ADMAPI (*ScreenToLocalRect)(ADMItemRef inItem, ADMRect* ioRect);
	
	// item display
	
	/** ... */
	void ADMAPI (*Invalidate)(ADMItemRef inItem);
	/** ... */
	void ADMAPI (*InvalidateRect)(ADMItemRef inDialog, const ADMRect* inInvalRect);
	/** ... */
	void ADMAPI (*Update)(ADMItemRef inItem);
	
	// cursor ID accessors
	
	/** ... */
	ADMBoolean ADMAPI (*SetCursorID)(ADMItemRef inItem, SPPluginRef inPluginRef, ADMInt32 inCursorID,
				const char* inCursorName);

	/** ... */
	void ADMAPI (*GetCursorID)(ADMItemRef inItem, SPPluginRef* outPluginRef, ADMInt32* outCursorID,
				const char** outCursorName);

	// picture ID accessors

	/** ... */
	void ADMAPI (*SetPictureID)(ADMItemRef inItem, ADMInt32 inPictureResID,
				const char* inPictureResName);

	/** ... */
	void ADMAPI (*GetPictureID)(ADMItemRef inItem, ADMInt32* outPictureResID,
				const char** outPictureResName);
	
	/** ... */
	void ADMAPI (*SetSelectedPictureID)(ADMItemRef inItem, ADMInt32 inPictureResID,
				const char* inPictureResName);

	/** ... */
	void ADMAPI (*GetSelectedPictureID)(ADMItemRef inItem, ADMInt32* outPictureResID,
				const char** outPictureResName);
	
	/** ... */
	void ADMAPI (*SetDisabledPictureID)(ADMItemRef inItem, ADMInt32 inPictureResID,
				const char* inPictureResName);

	/** ... */
	void ADMAPI (*GetDisabledPictureID)(ADMItemRef inItem, ADMInt32* outPictureResID,
				const char** outPictureResName);

	// tooltips

	/** ... */
	void ADMAPI (*SetTipString)(ADMItemRef inItem, const char* inTipString);
	/** ... */
	void ADMAPI (*SetTipStringW)(ADMItemRef inItem, const ADMUnicode* inTipString);

	/** ... */
	void ADMAPI (*GetTipString)(ADMItemRef inItem, char* outTipString, ADMInt32 inMaxLength);
	/** ... */
	void ADMAPI (*GetTipStringW)(ADMItemRef inItem, ADMUnicode* outTipString, ADMInt32 inMaxLength);
	
	/** ... */
	ADMInt32 ADMAPI (*GetTipStringLength)(ADMItemRef inItem);
	/** ... */
	ADMInt32 ADMAPI (*GetTipStringLengthW)(ADMItemRef inItem);
	
	/** ... */
	void ADMAPI (*EnableTip)(ADMItemRef inItem, ADMBoolean inEnable);
	/** ... */
	ADMBoolean ADMAPI (*IsTipEnabled)(ADMItemRef inItem);
	
	/** ... */
	void ADMAPI (*ShowToolTip)(ADMItemRef inItem, const ADMPoint* inWhere);
	/** ... */
	void ADMAPI (*HideToolTip)(ADMItemRef inItem);
	
	// item text accessors

	/** ... */
	void ADMAPI (*SetFont)(ADMItemRef inItem, ADMFont inFontID);
	/** ... */
	ADMFont ADMAPI (*GetFont)(ADMItemRef inItem);

	/** ... */
	void ADMAPI (*SetText)(ADMItemRef inItem, const char* inText);
	/** ... */
	void ADMAPI (*SetTextW)(ADMItemRef inItem, const ADMUnicode* inText);

	/** ... */
	void ADMAPI (*GetText)(ADMItemRef inItem, char* outText, ADMInt32 inMaxLength);
	/** ... */
	void ADMAPI (*GetTextW)(ADMItemRef inItem, ADMUnicode* outText, ADMInt32 inMaxLength);

	/** ... */
	ADMInt32 ADMAPI (*GetTextLength)(ADMItemRef inItem);
	/** ... */
	ADMInt32 ADMAPI (*GetTextLengthW)(ADMItemRef inItem);
	
	/** ... */
	void ADMAPI (*SetMaxTextLength)(ADMItemRef inItem, ADMInt32 inLength);
	/** ... */
	ADMInt32 ADMAPI (*GetMaxTextLength)(ADMItemRef inItem);
	
	/** ... */
	void ADMAPI (*SelectAll)(ADMItemRef inItem);
	/** ... */
	void ADMAPI (*SetSelectionRange)(ADMItemRef inItem, ADMInt32 inSelStart, ADMInt32 inSelEnd);
	/** ... */
	void ADMAPI (*GetSelectionRange)(ADMItemRef inItem, ADMInt32* outSelStart, ADMInt32* outSelEnd);

	/** ... */
	void ADMAPI (*SetJustify)(ADMItemRef inItem, ADMJustify inJustify);
	/** ... */
	ADMJustify ADMAPI (*GetJustify)(ADMItemRef inItem);
	
	/** ... */
	void ADMAPI (*SetUnits)(ADMItemRef inItem, ADMUnits inUnits);
	/** ... */
	ADMUnits ADMAPI (*GetUnits)(ADMItemRef inItem);
	
	// item value accessors

	/** ... */
	void ADMAPI (*SetPrecision)(ADMItemRef inItem, ADMInt32 inNumberOfDecimalPlaces);
	/** ... */
	ADMInt32 ADMAPI (*GetPrecision)(ADMItemRef inItem);
	
	/** ... */
	void ADMAPI (*SetBooleanValue)(ADMItemRef inItem, ADMBoolean inValue);
	/** ... */
	ADMBoolean ADMAPI (*GetBooleanValue)(ADMItemRef inItem);
	
	/** ... */
	void ADMAPI (*SetIntValue)(ADMItemRef inItem, ADMInt32 inValue);
	/** ... */
	ADMInt32 ADMAPI (*GetIntValue)(ADMItemRef inItem);
		
	/** ... */
	void ADMAPI (*SetFixedValue)(ADMItemRef inItem, ADMFixed inValue);	
	/** ... */
	ADMFixed ADMAPI (*GetFixedValue)(ADMItemRef inItem);
	
	/** ... */
	void ADMAPI (*SetFloatValue)(ADMItemRef inItem, float inValue);	
	/** ... */
	float ADMAPI (*GetFloatValue)(ADMItemRef inItem);
	
	/** ... */
	void ADMAPI (*SetMinIntValue)(ADMItemRef inItem, ADMInt32 inValue);
	/** ... */
	ADMInt32 ADMAPI (*GetMinIntValue)(ADMItemRef inItem);
		
	/** ... */
	void ADMAPI (*SetMinFixedValue)(ADMItemRef inItem, ADMFixed inValue);	
	/** ... */
	ADMFixed ADMAPI (*GetMinFixedValue)(ADMItemRef inItem);
	
	/** ... */
	void ADMAPI (*SetMaxIntValue)(ADMItemRef inItem, ADMInt32 inValue);
	/** ... */
	ADMInt32 ADMAPI (*GetMaxIntValue)(ADMItemRef inItem);
	
	/** ... */
	void ADMAPI (*SetMinFloatValue)(ADMItemRef inItem, float inValue);	
	/** ... */
	float ADMAPI (*GetMinFloatValue)(ADMItemRef inItem);
	
	/** ... */
	void ADMAPI (*SetMaxFixedValue)(ADMItemRef inItem, ADMFixed inValue);	
	/** ... */
	ADMFixed ADMAPI (*GetMaxFixedValue)(ADMItemRef inItem);
	
	/** ... */
	void ADMAPI (*SetMaxFloatValue)(ADMItemRef inItem, float inValue);	
	/** ... */
	float ADMAPI (*GetMaxFloatValue)(ADMItemRef inItem);
	
	/** ... */
	void ADMAPI (*SetSmallIncrement)(ADMItemRef inItem, float inIncrement);	
	/** ... */
	float ADMAPI (*GetSmallIncrement)(ADMItemRef inItem);
	
	/** ... */
	void ADMAPI (*SetLargeIncrement)(ADMItemRef inItem, float inIncrement);
	/** ... */
	float ADMAPI (*GetLargeIncrement)(ADMItemRef inItem);
	
	/** ... */
	void ADMAPI (*SetAllowUnits)(ADMItemRef inItem, ADMBoolean inAllowUnits);
	/** ... */
	ADMBoolean ADMAPI (*GetAllowUnits)(ADMItemRef inItem);

	/** ... */
	void ADMAPI (*SetAllowMath)(ADMItemRef inItem, ADMBoolean inAllowMath);
	/** ... */
	ADMBoolean ADMAPI (*GetAllowMath)(ADMItemRef inItem);
	
	/** ... */
	void ADMAPI (*SetFloatToTextProc)(ADMItemRef inItem, ADMItemFloatToTextProc inProc);
	/** ... */
	ADMItemFloatToTextProc ADMAPI (*GetFloatToTextProc)(ADMItemRef inItem);
	
	/** ... */
	ADMBoolean ADMAPI (*DefaultFloatToText)(ADMItemRef inItem, float inValue, char* outText,
		ADMInt32 inMaxLength);

	/** ... */
	ADMBoolean ADMAPI (*DefaultFloatToTextW)(ADMItemRef inItem, float inValue, ADMUnicode* outText,
		ADMInt32 inMaxLength);

	/** ... */
	void ADMAPI (*SetTextToFloatProc)(ADMItemRef inItem, ADMItemTextToFloatProc inProc);
	/** ... */
	ADMItemTextToFloatProc ADMAPI (*GetTextToFloatProc)(ADMItemRef inItem);

	/** ... */
	ADMBoolean ADMAPI (*DefaultTextToFloat)(ADMItemRef inItem, const char* inText, float* outValue);
	/** ... */
	ADMBoolean ADMAPI (*DefaultTextToFloatW)(ADMItemRef inItem, const ADMUnicode* inText, float* outValue);

	/** ... */
	void ADMAPI (*ShowUnits)(ADMItemRef inItem, ADMBoolean inShowUnits);
	/** ... */
	ADMBoolean ADMAPI (*GetShowUnits)(ADMItemRef inItem);

	/** ... */
	ADMBoolean ADMAPI (*WasPercentageChange)(ADMItemRef inItem);

	// hierarchy list accessor
	
	/** ... */
	ADMHierarchyListRef ADMAPI (*GetHierarchyList)(ADMItemRef inItem);
	
	// item group accessors
	
	/** ... */
 	void ADMAPI (*AddItem)(ADMItemRef inGroup, ADMItemRef inItem);
	/** ... */
 	void ADMAPI (*RemoveItem)(ADMItemRef inGroup, ADMItemRef inItem);

	// item pictures (from icons)
	
	/** ... */
	void ADMAPI (*SetPicture)(ADMItemRef inItem, ADMIconRef inPicture);
	/** ... */
	ADMIconRef ADMAPI (*GetPicture)(ADMItemRef inItem);

	/** ... */
	void ADMAPI (*SetSelectedPicture)(ADMItemRef inItem, ADMIconRef inPicture);
	/** ... */
	ADMIconRef ADMAPI (*GetSelectedPicture)(ADMItemRef inItem);

	/** ... */
	void ADMAPI (*SetDisabledPicture)(ADMItemRef inItem, ADMIconRef inPicture);
	/** ... */
	ADMIconRef ADMAPI (*GetDisabledPicture)(ADMItemRef inItem);
	
	// popup control accessors
	
	/** ... */
	void ADMAPI (*SetPopupDialog)(ADMItemRef inItem, ADMInt32 inPopupItemID, ADMDialogRef inDialog);
	/** ... */
	ADMDialogRef ADMAPI (*GetPopupDialog)(ADMItemRef inItem);


	// Basic color accessors for all applicable ADM items
	/** ... */
	void ADMAPI (*SetForeColor)(ADMItemRef inItem, ADMColor inColor);
	/** ... */
	ADMColor ADMAPI (*GetForeColor)(ADMItemRef inItem);
	/** ... */
	void ADMAPI (*SetBackColor)(ADMItemRef inItem, ADMColor inColor);
	/** ... */
	ADMColor ADMAPI (*GetBackColor)(ADMItemRef inItem);

	
	//Accessor functions for Rollover state.

	/** ... */
	void ADMAPI (*SetRolloverPictureID)(ADMItemRef inItem, ADMInt32 inPictureResID,
				const char* inPictureResName);

	/** ... */
	void ADMAPI (*GetRolloverPictureID)(ADMItemRef inItem, ADMInt32* outPictureResID,
				const char** outPictureResName);

	/** ... */
	void ADMAPI (*SetRolloverPicture)(ADMItemRef inItem, ADMIconRef inPicture);
	/** ... */
	ADMIconRef ADMAPI (*GetRolloverPicture)(ADMItemRef inItem);

	// Set/Get the Has Rollover property - whether or not the item wants to have rollover
	/** ... */
	void ADMAPI (*SetHasRollOverProperty)(ADMItemRef inItem, ADMBoolean inRollover);
	/** ... */
	ADMBoolean ADMAPI (*GetHasRollOverProperty)(ADMItemRef inItem);

	// Set/Get whether or not the item is currently rolled over or not
	/** ... */
	void ADMAPI (*SetInRollOverState)(ADMItemRef inItem, ADMBoolean inRolloverState);
	/** ... */
	ADMBoolean ADMAPI (*IsInRollOverState)(ADMItemRef inItem);

	/**
		Overrides roman script forcing of item fonts
		
		Normally one would set this with the kADMIgnoreRomanFontForcing flag
		(see ADMTypes.h) set as a mask on the options argument in the item's
		Create() call. Items that are  created in dialogs that are defined by
		platform resources do not have that  ability, however, hence this
		mutator. Roman font forcing may be set globally by client apps or on a
		per-dialog basis. Clients may have a need to override on some items, so
		do that either via Create() or do it after the fact with the
		IgnoreForceRoman() call.
	*/
	void ADMAPI (*IgnoreForceRoman)(ADMItemRef inItem, ADMBoolean inIgnoreForceRoman);

	// Set/Get the WantsFocus property - whether or not the item wants to receive focus
	/** ... */
	void ADMAPI (*SetWantsFocus)(ADMItemRef inItem, ADMBoolean inWantsFocus);
	/** ... */
	ADMBoolean ADMAPI (*GetWantsFocus)(ADMItemRef inItem);
	
	/**
		Used when setting up an entire list of focus items for a dialog.
		If you want to rearrange an existing list, call MoveFocusItem

		Sets the next item to receive focus when keyboard focus is advanced
		
		Before calling this method call ADMDialogSuite's BeginAdjustingFocusOrder
		After you are done specifying all items, call ADMDialogSuite's DoneAdjustingFocusOrder
		function to get SetNextFocus calls to "take".
	*/
	ADMErr ADMAPI (*SetNextFocus)(ADMItemRef inItem, ADMItemRef inNextItem);

	/**
		Used when setting up an entire list of focus items for a dialog.
		If you want to rearrange an existing list, call MoveFocusItem

		Specifies first item to receive keyboard focus
		
		Before calling this method call ADMDialogSuite's BeginAdjustingFocusOrder
		After you are done specifying all items, call ADMDialogSuite's DoneAdjustingFocusOrder
		function to get SetFirstFocus calls to "take".
	*/
	ADMErr ADMAPI (*SetFirstFocus)(ADMItemRef inItem);

	/**
		Rearrange the focus order of an existing focus list by putting the inSource item after inTarget.
		If in inTarget is NULL, then inSource is put in front of the list
	*/
	ADMErr ADMAPI (*MoveFocusItem)(ADMItemRef inSource, ADMItemRef inTarget);
}
ADMItemSuite9;

// -----------------------------------------------------------------------------

#pragma ADM_PRAGMA_IMPORT_END
#pragma ADM_PRAGMA_ALIGN_END

#ifdef __cplusplus
}
#endif

#endif
