/*******************************************************************************
*
* ADMEntry.h -- ADM Entry Suite
*
* ADOBE SYSTEMS INCORPORATED
* Copyright 1996-2001,2003 Adobe Systems Incorporated
* All Rights Reserved
*
* NOTICE: Adobe permits you to use, modify, and distribute this file in
* accordance with the terms of the Adobe license agreement accompanying it.
* If you have received this file from a source other than Adobe, then your use,
* modification, or distribution of it requires the prior written permission of
* Adobe.
*
* Started by Dave Lazarony, 09 Mar 1996
*
********************************************************************************/

/** @file ADMEntry.h ADM Entry Suite */

#ifndef __ADMEntry__
#define __ADMEntry__

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
//	User provided procedures.

/** ... */
typedef ADMBoolean ADMAPI (*ADMEntryTimerProc)(ADMEntryRef inEntry, ADMTimerRef inTimer);

/** ... */
typedef void ADMAPI (*ADMEntryTimerAbortProc)(ADMEntryRef inEntry, ADMTimerRef inTimer,
			ADMAction inAbortAction);


// -----------------------------------------------------------------------------
//	Standard checkmark glyphs

/** ... */
typedef enum
{
	/** ... */
	kADMCheckmarkGlyphID = 0,
	/** ... */
	kADMBulletGlyphID = 1,
	/** ... */
	kADMHyphenGlyphID = 2,
	/** ... */
	kADMDummyGlyphID = 0xFFFFFFFF
}
ADMStandardCheckGlyphID;


// =============================================================================
//		* ADM Entry Suite
// =============================================================================

/** ... */
#define kADMEntrySuite "ADM Entry Suite"
/** ... */
#define kADMEntrySuiteVersion6 6

// -----------------------------------------------------------------------------

/** ... */
typedef struct ADMEntrySuite6
{

	// *** This suite is FROZEN.
	// *** It shipped with Acrobat 6.0.

	// entry creation/destruction

	/** ... */
	ADMEntryRef ADMAPI (*Create)(ADMListRef inList);
	/** ... */
	void ADMAPI (*Destroy)(ADMEntryRef inEntry);

	// default behaviors
	
	/** ... */
	void ADMAPI (*DefaultDraw)(ADMEntryRef inEntry, ADMDrawerRef inDrawer);
	/** ... */
	ADMBoolean ADMAPI (*DefaultTrack)(ADMEntryRef inEntry, ADMTrackerRef inTracker);
	/** ... */
	void ADMAPI (*DefaultNotify)(ADMEntryRef inEntry, ADMNotifierRef inNotifier);
	/** ... */
	void ADMAPI (*SendNotify)(ADMEntryRef inEntry, const char* inNotifierType);

	// container accessors
	
	/** ... */
	ADMInt32 ADMAPI (*GetIndex)(ADMEntryRef inEntry);
	/** ... */
	ADMListRef ADMAPI (*GetList)(ADMEntryRef inEntry);

	// entry ID
		
	/** ... */
	void ADMAPI (*SetID)(ADMEntryRef inEntry, ADMInt32 inEntryID);
	/** ... */
	ADMInt32 ADMAPI (*GetID)(ADMEntryRef inEntry);
	
	// entry user data storage
	
	/** ... */
	void ADMAPI (*SetUserData)(ADMEntryRef inEntry, ADMUserData inUserData);
	/** ... */
	ADMUserData ADMAPI (*GetUserData)(ADMEntryRef inEntry);

	// entry selection status

	/** ... */
	void ADMAPI (*Select)(ADMEntryRef inEntry, ADMBoolean inSelect);
	/** ... */
	ADMBoolean ADMAPI (*IsSelected)(ADMEntryRef inEntry);

	// entry visibility
	
	/** ... */
	void ADMAPI (*MakeInBounds)(ADMEntryRef inEntry);
	/** ... */
	ADMBoolean ADMAPI (*IsInBounds)(ADMEntryRef inEntry);

	// entry state accessors

	/** ... */
	void ADMAPI (*Enable)(ADMEntryRef inEntry, ADMBoolean inEnable);
	/** ... */
	ADMBoolean ADMAPI (*IsEnabled)(ADMEntryRef inEntry);
	
	/** ... */
	void ADMAPI (*Activate)(ADMEntryRef inEntry, ADMBoolean inActivate);
	/** ... */
	ADMBoolean ADMAPI (*IsActive)(ADMEntryRef inEntry);
	
	/** ... */
	void ADMAPI (*Check)(ADMEntryRef inEntry, ADMBoolean inCheck);
	/** ... */
	ADMBoolean ADMAPI (*IsChecked)(ADMEntryRef inEntry);
	
	/** ... */
	void ADMAPI (*MakeSeparator)(ADMEntryRef inEntry, ADMBoolean inSeparator);
	/** ... */
	ADMBoolean ADMAPI (*IsSeparator)(ADMEntryRef inEntry);

	// entry bounds accessors

	/** ... */
	void ADMAPI (*GetLocalRect)(ADMEntryRef inEntry, ADMRect* outLocalRect);
	/** ... */
	void ADMAPI (*GetBoundsRect)(ADMEntryRef inEntry, ADMRect* outBoundsRect);
	
	// coordinate transformations

	/** ... */
	void ADMAPI (*LocalToScreenPoint)(ADMEntryRef inEntry, ADMPoint* ioPoint);
	/** ... */
	void ADMAPI (*ScreenToLocalPoint)(ADMEntryRef inEntry, ADMPoint* ioPoint);
	
	/** ... */
	void ADMAPI (*LocalToScreenRect)(ADMEntryRef inEntry, ADMRect* ioRect);
	/** ... */
	void ADMAPI (*ScreenToLocalRect)(ADMEntryRef inEntry, ADMRect* ioRect);

	// redraw requests
	
	/** ... */
	void ADMAPI (*Invalidate)(ADMEntryRef inEntry);
	/** ... */
	void ADMAPI (*InvalidateRect)(ADMEntryRef inEntry, const ADMRect* inInvalRect);
	/** ... */
	void ADMAPI (*Update)(ADMEntryRef inEntry);
	
	// entry picture accessors
	
	/** ... */
	void ADMAPI (*SetPictureID)(ADMEntryRef inEntry, ADMInt32 inPictureResID,
				const char* inPictureResName);

	/** ... */
	void ADMAPI (*GetPictureID)(ADMEntryRef inEntry, ADMInt32* outPictureResID,
				const char** outPictureResName);
	
	/** ... */
	void ADMAPI (*SetSelectedPictureID)(ADMEntryRef inEntry, ADMInt32 inPictureResID,
				const char* inPictureResName);

	/** ... */
	void ADMAPI (*GetSelectedPictureID)(ADMEntryRef inEntry, ADMInt32* outPictureResID,
				const char** outPictureResName);
	
	/** ... */
	void ADMAPI (*SetDisabledPictureID)(ADMEntryRef inEntry, ADMInt32 inPictureResID,
				const char* inPictureResName);
				
	/** ... */
	void ADMAPI (*GetDisabledPictureID)(ADMEntryRef inEntry, ADMInt32* outPictureResID,
				const char** outPictureResName);
	
	/** ... */
	void ADMAPI (*SetPicture)(ADMEntryRef inEntry, ADMIconRef inPicture);
	/** ... */
	ADMIconRef ADMAPI (*GetPicture)(ADMEntryRef inEntry);

	/** ... */
	void ADMAPI (*SetSelectedPicture)(ADMEntryRef inEntry, ADMIconRef inPicture);
	/** ... */
	ADMIconRef ADMAPI (*GetSelectedPicture)(ADMEntryRef inEntry);

	/** ... */
	void ADMAPI (*SetDisabledPicture)(ADMEntryRef inEntry, ADMIconRef inPicture);
	/** ... */
	ADMIconRef ADMAPI (*GetDisabledPicture)(ADMEntryRef inEntry);

	// entry text accessors

	/** ... */
	void ADMAPI (*SetText)(ADMEntryRef inEntry, const char* inText);
	/** ... */
	void ADMAPI (*SetTextW)(ADMEntryRef inEntry, const ADMUnicode* inText);

	/** ... */
	void ADMAPI (*GetText)(ADMEntryRef inEntry, char* outText, ADMInt32 inMaxLength);
	/** ... */
	void ADMAPI (*GetTextW)(ADMEntryRef inEntry, ADMUnicode* outText, ADMInt32 inMaxLength);

	/** ... */
	ADMInt32 ADMAPI (*GetTextLength)(ADMEntryRef inEntry);
	/** ... */
	ADMInt32 ADMAPI (*GetTextLengthW)(ADMEntryRef inEntry);
	
	// entry timer accessors
	
	/** ... */
	ADMTimerRef ADMAPI (*CreateTimer)(ADMEntryRef inEntry, ADMUInt32 inMilliseconds,
				ADMActionMask inAbortMask, ADMEntryTimerProc inTimerProc,
				ADMEntryTimerAbortProc inTimerAbortProc, ADMInt32 inOptions);

	/** ... */
	void ADMAPI (*AbortTimer)(ADMEntryRef inEntry, ADMTimerRef inTimer);

	// entry help ID
	// dhearst 6/28/02 - ADM no longer supports ASHelp
	/** ... */
	ADMInt32 ADMAPI (*GetHelpID_DEPRECATED)(ADMEntryRef inEntry);
	/** ... */
	void ADMAPI (*SetHelpID_DEPRECATED)(ADMEntryRef inEntry, ADMInt32 inHelpID);
	/** ... */
	void ADMAPI (*Help_DEPRECATED)(ADMEntryRef inEntry);

	// entry checkmark accessors

	/** ... */
	void ADMAPI (*SetCheckGlyph)(ADMEntryRef inEntry, ADMStandardCheckGlyphID inCheckGlyph);
	/** ... */
	ADMStandardCheckGlyphID ADMAPI (*GetCheckGlyph)(ADMEntryRef inEntry);
	
	// [cpaduan] 8/23/02 - set/get entry script
	/** ... */
	void ADMAPI (*SetScript)(ADMEntryRef inEntry, ADMInt16 inScript);
	/** ... */
	ADMInt16 ADMAPI (*GetScript)(ADMEntryRef inEntry);
	
}
ADMEntrySuite6;


// -----------------------------------------------------------------------------
//	Old versions of suites

#ifndef __ADMEntryOld__
#ifdef MAC_ENV
#include "ADMEntryOld.h"
#else
#include ".\Legacy\ADMEntryOld.h"
#endif
#endif

// -----------------------------------------------------------------------------

#pragma ADM_PRAGMA_IMPORT_END
#pragma ADM_PRAGMA_ALIGN_END

#ifdef __cplusplus
}
#endif

// -----------------------------------------------------------------------------

#endif	// __ADMEntry__
