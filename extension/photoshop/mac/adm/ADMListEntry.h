/*******************************************************************************
*
* ADMListEntry.h -- ADM List Entry Suite
*
* ADOBE SYSTEMS INCORPORATED
* Copyright 1997-2001,2003 Adobe Systems Incorporated
* All Rights Reserved
*
* NOTICE: Adobe permits you to use, modify, and distribute this file in
* accordance with the terms of the Adobe license agreement accompanying it.
* If you have received this file from a source other than Adobe, then your use,
* modification, or distribution of it requires the prior written permission of
* Adobe.
*
* Started by Wei Huang, 17 Oct 1997
*
********************************************************************************/

/** @file ADMListEntry.h ADM List Entry Suite */

#ifndef __ADMListEntry__
#define __ADMListEntry__

#ifndef __ADMTypes__
#include "ADMTypes.h"
#endif

#ifndef __ADMTracker__
#include "ADMTracker.h"
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

/** ... */
typedef ADMBoolean ADMAPI (*ADMListEntryTimerProc)(ADMListEntryRef inEntry,
			ADMTimerRef inTimer);

/** ... */
typedef void ADMAPI (*ADMListEntryTimerAbortProc)(ADMListEntryRef inEntry,
			ADMTimerRef inTimer, ADMAction abortAction);


// =============================================================================
//		* ADM List Entry Suite
// =============================================================================

/** ... */
#define kADMListEntrySuite "ADM List Entry Suite"
/** ... */
#define kADMListEntrySuiteVersion4 4

// -----------------------------------------------------------------------------

/** ... */
typedef struct ADMListEntrySuite4
{

	// *** This suite is FROZEN.
	// *** It shipped with Acrobat 5.0.

	// entry creation/destruction

	/** ... */
	ADMListEntryRef ADMAPI (*Create)(ADMHierarchyListRef inList);
	/** ... */
	void ADMAPI (*Destroy)(ADMListEntryRef inEntry);
	
	// entry sequence
	
	/** ... */
	ADMInt32 ADMAPI (*GetIndex)(ADMListEntryRef inEntry);
	
	// container accessors
	
	/** ... */
	ADMItemRef ADMAPI (*GetItem)(ADMListEntryRef inEntry);
	/** ... */
	ADMHierarchyListRef ADMAPI (*GetList)(ADMListEntryRef inEntry);

	// hierarchy accessors
	
	/** ... */
	ADMHierarchyListRef ADMAPI (*GetChildList)(ADMListEntryRef inEntry);
	/** ... */
	ADMHierarchyListRef ADMAPI (*CreateChildList)(ADMListEntryRef inEntry);
	/** ... */
	void ADMAPI (*DeleteChildList)(ADMListEntryRef inEntry);

	/** ... */
	void ADMAPI (*ExpandHierarchy)(ADMListEntryRef inEntry, ADMBoolean inExpand);
	/** ... */
	ADMBoolean ADMAPI (*IsHierarchyExpanded)(ADMListEntryRef inEntry);

	/** ... */
	void ADMAPI (*HideEntryName)(ADMListEntryRef inEntry, ADMBoolean inHideName);
	/** ... */
	ADMBoolean ADMAPI (*IsEntryNameHidden)(ADMListEntryRef inEntry);

	/** ... */
	void ADMAPI (*EnableChildSelection)(ADMListEntryRef inEntry, ADMBoolean inEnable);
	/** ... */
	ADMBoolean ADMAPI (*IsChildSelectable)(ADMListEntryRef inEntry);

	/** ... */
	ADMInt32 ADMAPI (*GetHierarchyDepth)(ADMListEntryRef inEntry);
	/** ... */
	ADMInt32 ADMAPI (*GetVisualHierarchyDepth)(ADMListEntryRef inEntry);

	// entry ID

	/** ... */
	void ADMAPI (*SetID)(ADMListEntryRef inEntry, ADMInt32 inEntryID);
	/** ... */
	ADMInt32 ADMAPI (*GetID)(ADMListEntryRef inEntry);

	// entry user storage
	
	/** ... */
	void ADMAPI (*SetUserData)(ADMListEntryRef inEntry, ADMUserData inUserData);
	/** ... */
	ADMUserData ADMAPI (*GetUserData)(ADMListEntryRef inEntry);

	// default behaviors

	/** ... */
	void ADMAPI (*DefaultDraw)(ADMListEntryRef inEntry, ADMDrawerRef inDrawer);
	/** ... */
	ADMBoolean ADMAPI (*DefaultTrack)(ADMListEntryRef inEntry, ADMTrackerRef inTracker);
	/** ... */
	void ADMAPI (*DefaultNotify)(ADMListEntryRef inEntry, ADMNotifierRef inNotifier);
	/** ... */
	void ADMAPI (*SendNotify)(ADMListEntryRef inEntry, const char* inNotifierType);

	// selection
	
	/** ... */
	void ADMAPI (*Select)(ADMListEntryRef inEntry, ADMBoolean inSelect);
	/** ... */
	ADMBoolean ADMAPI (*IsSelected)(ADMListEntryRef inEntry);
	/** ... */
	ADMBoolean ADMAPI (*AreChildrenSelected)(ADMListEntryRef inEntry);

	// display settings
	
	/** ... */
	void ADMAPI (*Enable)(ADMListEntryRef inEntry, ADMBoolean inEnable);
	/** ... */
	ADMBoolean ADMAPI (*IsEnabled)(ADMListEntryRef inEntry);
	
	/** ... */
	void ADMAPI (*Activate)(ADMListEntryRef inEntry, ADMBoolean inActivate);
	/** ... */
	ADMBoolean ADMAPI (*IsActive)(ADMListEntryRef inEntry);
	
	/** ... */
	void ADMAPI (*Check)(ADMListEntryRef inEntry, ADMBoolean inCheck);
	/** ... */
	ADMBoolean ADMAPI (*IsChecked)(ADMListEntryRef inEntry);
	
	/** ... */
	void ADMAPI (*MakeSeparator)(ADMListEntryRef inEntry, ADMBoolean inSeparator);
	/** ... */
	ADMBoolean ADMAPI (*IsSeparator)(ADMListEntryRef inEntry);

	// bounds accessors

	/** ... */
	void ADMAPI (*GetLocalRect)(ADMListEntryRef inEntry, ADMRect* outLocalRect);
	/** ... */
	void ADMAPI (*GetExpandArrowLocalRect)(ADMListEntryRef inEntry, ADMRect* outLocalRect);
	/** ... */
	void ADMAPI (*GetBoundsRect)(ADMListEntryRef inEntry, ADMRect* outBoundsRect);

	// coordinate transformations
	
	/** ... */
	void ADMAPI (*LocalToScreenPoint)(ADMListEntryRef inEntry, ADMPoint* ioPoint);
	/** ... */
	void ADMAPI (*ScreenToLocalPoint)(ADMListEntryRef inEntry, ADMPoint* ioPoint);
	
	/** ... */
	void ADMAPI (*LocalToScreenRect)(ADMListEntryRef inEntry, ADMRect* inRect);
	/** ... */
	void ADMAPI (*ScreenToLocalRect)(ADMListEntryRef inEntry, ADMRect* inRect);

	// redrawing
	
	/** ... */
	void ADMAPI (*Invalidate)(ADMListEntryRef inEntry);
	/** ... */
	void ADMAPI (*Update)(ADMListEntryRef inEntry);

	// entry pictures
	
	/** ... */
	void ADMAPI (*SetPictureID)(ADMListEntryRef inEntry, ADMInt32 inPictureResID,
				const char* inPictureResName);

	/** ... */
	void ADMAPI (*GetPictureID)(ADMListEntryRef inEntry, ADMInt32* inPictureResID,
				const char** outPictureResName);
	
	/** ... */
	void ADMAPI (*SetSelectedPictureID)(ADMListEntryRef inEntry, ADMInt32 inPictureResID,
				const char* inPictureResName);

	/** ... */
	void ADMAPI (*GetSelectedPictureID)(ADMListEntryRef inEntry, ADMInt32* outPictureResID,
				const char** outPictureResName);
	
	/** ... */
	void ADMAPI (*SetDisabledPictureID)(ADMListEntryRef inEntry, ADMInt32 inPictureResID,
				const char* inPictureResName);

	/** ... */
	void ADMAPI (*GetDisabledPictureID)(ADMListEntryRef inEntry, ADMInt32* outPictureResID,
				const char** outPictureResName);
	
	// entry text
	
	/** ... */
	void ADMAPI (*SetText)(ADMListEntryRef inEntry, const char* inText);
	/** ... */
	void ADMAPI (*SetTextW)(ADMListEntryRef inEntry, const ADMUnicode* inText);

	/** ... */
	void ADMAPI (*GetText)(ADMListEntryRef inEntry, char* outText, ADMInt32 inMaxLength);
	/** ... */
	void ADMAPI (*GetTextW)(ADMListEntryRef inEntry, ADMUnicode* outText, ADMInt32 inMaxLength);

	/** ... */
	ADMInt32 ADMAPI (*GetTextLength)(ADMListEntryRef inEntry);
	/** ... */
	ADMInt32 ADMAPI (*GetTextLengthW)(ADMListEntryRef inEntry);
	
	// entry timer
	
	/** ... */
	ADMTimerRef ADMAPI (*CreateTimer)(ADMListEntryRef inEntry, ADMUInt32 inMilliseconds,
				ADMActionMask inAbortMask, ADMListEntryTimerProc inTimerProc,
				ADMListEntryTimerAbortProc inAbortProc, ADMInt32 inOptions);

	/** ... */
	void ADMAPI (*AbortTimer)(ADMListEntryRef inEntry, ADMTimerRef inTimer);

	// entry visibility

	/** ... */
	void ADMAPI (*MakeInBounds)(ADMListEntryRef inEntry);
	/** ... */
	ADMBoolean ADMAPI (*IsInBounds)(ADMListEntryRef inEntry);

	// entry help
	// dhearst 6/28/02 - ADM no longer supports ASHelp
	/** ... */
	ADMInt32 ADMAPI (*GetHelpID_DEPRECATED)(ADMListEntryRef inEntry);
	/** ... */
	void ADMAPI (*SetHelpID_DEPRECATED)(ADMListEntryRef inEntry, ADMInt32 inHelpID);
	/** ... */
	void ADMAPI (*Help_DEPRECATED)(ADMListEntryRef inEntry);

	// entry pictures

	/** ... */
	void ADMAPI (*SetPicture)(ADMListEntryRef inEntry, ADMIconRef inPicture);
	/** ... */
	ADMIconRef ADMAPI (*GetPicture)(ADMListEntryRef inEntry);

	/** ... */
	void ADMAPI (*SetSelectedPicture)(ADMListEntryRef inEntry, ADMIconRef inPicture);
	/** ... */
	ADMIconRef ADMAPI (*GetSelectedPicture)(ADMListEntryRef inEntry);

	/** ... */
	void ADMAPI (*SetDisabledPicture)(ADMListEntryRef inEntry, ADMIconRef inPicture);
	/** ... */
	ADMIconRef ADMAPI (*GetDisabledPicture)(ADMListEntryRef inEntry);

	// for in-place editing: text rect used to display the edit field.

	/** ... */
	void ADMAPI (*SetEntryTextRect)(ADMListEntryRef inEntry, ADMRect* inRect);

	// for controls in lists

	/** ... */
	ADMItemRef ADMAPI (*GetEntryItem)(ADMListEntryRef inEntry);
	/** ... */
	void ADMAPI (*SetEntryItem)(ADMListEntryRef inEntry, ADMItemRef inItem);
	
	// customizing appearance
	
	/** ... */
	void ADMAPI (*SetFont)(ADMListEntryRef inEntry, ADMFont inFont);
	/** ... */
	void ADMAPI (*SetTextColor)(ADMListEntryRef inEntry, ADMColor inColor);
	/** ... */
	void ADMAPI (*SetBackgroundColor)(ADMListEntryRef inEntry, ADMColor inColor);
	/** ... */
	void ADMAPI (*SetDividingLineColor)(ADMListEntryRef inEntry, ADMColor inColor);

}
ADMListEntrySuite4;


// -----------------------------------------------------------------------------
//	Old versions of suites

#ifndef __ADMListEntryOld__
#ifdef MAC_ENV
#include "ADMListEntryOld.h"
#else
#include ".\Legacy\ADMListEntryOld.h"
#endif
#endif

// -----------------------------------------------------------------------------

#pragma ADM_PRAGMA_IMPORT_END
#pragma ADM_PRAGMA_ALIGN_END

#ifdef __cplusplus
}
#endif

// -----------------------------------------------------------------------------

#endif	// __ADMListEntry__
