/***********************************************************************/
/*                                                                     */
/* ADMEntryOld.h                                                       */
/* Old versions of ADM Entry Suite                                     */
/*                                                                     */
/* ADOBE SYSTEMS INCORPORATED                                          */
/* Copyright 1996-2002 Adobe Systems Incorporated                      */
/* All Rights Reserved                                                 */
/*                                                                     */
/* NOTICE:  Adobe permits you to use, modify, and distribute this file */
/* in accordance with the terms of the Adobe license agreement         */
/* accompanying it. If you have received this file from a source other */
/* than Adobe, then your use, modification, or distribution of it      */
/* requires the prior written permission of Adobe.                     */
/*                                                                     */
/***********************************************************************/

#ifndef __ADMEntryOld__
#define __ADMEntryOld__


// -----------------------------------------------------------------------------
 
#ifdef __cplusplus
extern "C" {
#endif

#pragma ADM_PRAGMA_ALIGN_BEGIN
#pragma ADM_PRAGMA_IMPORT_BEGIN


// =============================================================================
//		* ADM Entry Suite, version 1
// =============================================================================
 
#define kADMEntrySuiteVersion1 1

// -----------------------------------------------------------------------------

typedef struct ADMEntrySuite1
{

	// entry creation/destruction

	ADMEntryRef ADMAPI (*Create)(ADMListRef inList);
	void ADMAPI (*Destroy)(ADMEntryRef inEntry);
	
	// default behaviors
	
	void ADMAPI (*DefaultDraw)(ADMEntryRef inEntry, ADMDrawerRef inDrawer);
	ADMBoolean ADMAPI (*DefaultTrack)(ADMEntryRef inEntry, ADMTrackerRef inTracker);
	void ADMAPI (*DefaultNotify)(ADMEntryRef inEntry, ADMNotifierRef inNotifier);
	void ADMAPI (*SendNotify)(ADMEntryRef inEntry, const char* inNotifierType);
	
	// container accessors
	
	ADMInt32 ADMAPI (*GetIndex)(ADMEntryRef inEntry);
	ADMListRef ADMAPI (*GetList)(ADMEntryRef inEntry);
	
	// entry ID
		
	void ADMAPI (*SetID)(ADMEntryRef inEntry, ADMInt32 inEntryID);
	ADMInt32 ADMAPI (*GetID)(ADMEntryRef inEntry);
	
	// entry user data storage
	
	void ADMAPI (*SetUserData)(ADMEntryRef inEntry, ADMUserData inUserData);
	ADMUserData ADMAPI (*GetUserData)(ADMEntryRef inEntry);

	// entry selection status

	void ADMAPI (*Select)(ADMEntryRef inEntry, ADMBoolean inSelect);
	ADMBoolean ADMAPI (*IsSelected)(ADMEntryRef inEntry);
	
	// entry state accessors

	void ADMAPI (*Enable)(ADMEntryRef inEntry, ADMBoolean inEnable);
	ADMBoolean ADMAPI (*IsEnabled)(ADMEntryRef inEntry);
	
	void ADMAPI (*Activate)(ADMEntryRef inEntry, ADMBoolean inActivate);
	ADMBoolean ADMAPI (*IsActive)(ADMEntryRef inEntry);
	
	void ADMAPI (*Check)(ADMEntryRef inEntry, ADMBoolean inCheck);
	ADMBoolean ADMAPI (*IsChecked)(ADMEntryRef inEntry);
	
	void ADMAPI (*MakeSeparator)(ADMEntryRef inEntry, ADMBoolean inSeparator);
	ADMBoolean ADMAPI (*IsSeparator)(ADMEntryRef inEntry);

	// entry bounds accessors

	void ADMAPI (*GetLocalRect)(ADMEntryRef inEntry, ADMRect* outLocalRect);
	void ADMAPI (*GetBoundsRect)(ADMEntryRef inEntry, ADMRect* outBoundsRect);
	
	// coordinate transformations

	void ADMAPI (*LocalToScreenPoint)(ADMEntryRef inEntry, ADMPoint* ioPoint);
	void ADMAPI (*ScreenToLocalPoint)(ADMEntryRef inEntry, ADMPoint* ioPoint);
	
	void ADMAPI (*LocalToScreenRect)(ADMEntryRef inEntry, ADMRect* ioRect);
	void ADMAPI (*ScreenToLocalRect)(ADMEntryRef inEntry, ADMRect* ioRect);
	
	// redraw requests
	
	void ADMAPI (*Invalidate)(ADMEntryRef inEntry);
	void ADMAPI (*Update)(ADMEntryRef inEntry);
	
	// entry picture accessors
	
	void ADMAPI (*SetPictureID)(ADMEntryRef inEntry, ADMInt32 inPictureResID);
	ADMInt32 ADMAPI (*GetPictureID)(ADMEntryRef inEntry);
	
	void ADMAPI (*SetSelectedPictureID)(ADMEntryRef inEntry, ADMInt32 inPictureResID);
	ADMInt32 ADMAPI (*GetSelectedPictureID)(ADMEntryRef inEntry);
	
	void ADMAPI (*SetDisabledPictureID)(ADMEntryRef inEntry, ADMInt32 inPictureResID);
	ADMInt32 ADMAPI (*GetDisabledPictureID)(ADMEntryRef inEntry);
	
	// entry text accessors

	void ADMAPI (*SetText)(ADMEntryRef inEntry, const char* inText);
	void ADMAPI (*GetText)(ADMEntryRef inEntry, char* outText, ADMInt32 inMaxLength);
	ADMInt32 ADMAPI (*GetTextLength)(ADMEntryRef inEntry);
	
	// entry timer accessors
	
	ADMTimerRef ADMAPI (*CreateTimer)(ADMEntryRef inEntry, ADMUInt32 inMilliseconds,
				ADMActionMask inAbortMask, ADMEntryTimerProc inTimerProc,
				ADMEntryTimerAbortProc inTimerAbortProc);

	void ADMAPI (*AbortTimer)(ADMEntryRef inEntry, ADMTimerRef inTimer);

	// entry visibility
	
	void ADMAPI (*MakeInBounds)(ADMEntryRef inEntry);
	ADMBoolean ADMAPI (*IsInBounds)(ADMEntryRef inEntry);

} ADMEntrySuite1;


// =============================================================================
//		* ADM Entry Suite, version 2
// =============================================================================

#define kADMEntrySuiteVersion2 2
#define kADMEntrySuiteVersion kADMEntrySuiteVersion2	// for historical reasons

// -----------------------------------------------------------------------------

typedef struct ADMEntrySuite2
{

	// entry creation/destruction

	ADMEntryRef ADMAPI (*Create)(ADMListRef inList);
	void ADMAPI (*Destroy)(ADMEntryRef inEntry);
	
	// default behaviors
	
	void ADMAPI (*DefaultDraw)(ADMEntryRef inEntry, ADMDrawerRef inDrawer);
	ADMBoolean ADMAPI (*DefaultTrack)(ADMEntryRef inEntry, ADMTrackerRef inTracker);
	void ADMAPI (*DefaultNotify)(ADMEntryRef inEntry, ADMNotifierRef inNotifier);
	void ADMAPI (*SendNotify)(ADMEntryRef inEntry, const char* inNotifierType);
	
	// container accessors
	
	ADMInt32 ADMAPI (*GetIndex)(ADMEntryRef inEntry);
	ADMListRef ADMAPI (*GetList)(ADMEntryRef inEntry);
	
	// entry ID
		
	void ADMAPI (*SetID)(ADMEntryRef inEntry, ADMInt32 inEntryID);
	ADMInt32 ADMAPI (*GetID)(ADMEntryRef inEntry);
	
	// entry user data storage
	
	void ADMAPI (*SetUserData)(ADMEntryRef inEntry, ADMUserData inUserData);
	ADMUserData ADMAPI (*GetUserData)(ADMEntryRef inEntry);

	// entry selection status

	void ADMAPI (*Select)(ADMEntryRef inEntry, ADMBoolean inSelect);
	ADMBoolean ADMAPI (*IsSelected)(ADMEntryRef inEntry);
	
	// entry visibility
	
	void ADMAPI (*MakeInBounds)(ADMEntryRef inEntry);
	ADMBoolean ADMAPI (*IsInBounds)(ADMEntryRef inEntry);

	// entry state accessors

	void ADMAPI (*Enable)(ADMEntryRef inEntry, ADMBoolean inEnable);
	ADMBoolean ADMAPI (*IsEnabled)(ADMEntryRef inEntry);
	
	void ADMAPI (*Activate)(ADMEntryRef inEntry, ADMBoolean inActivate);
	ADMBoolean ADMAPI (*IsActive)(ADMEntryRef inEntry);
	
	void ADMAPI (*Check)(ADMEntryRef inEntry, ADMBoolean inCheck);
	ADMBoolean ADMAPI (*IsChecked)(ADMEntryRef inEntry);
	
	void ADMAPI (*MakeSeparator)(ADMEntryRef inEntry, ADMBoolean inSeparator);
	ADMBoolean ADMAPI (*IsSeparator)(ADMEntryRef inEntry);

	// entry bounds accessors

	void ADMAPI (*GetLocalRect)(ADMEntryRef inEntry, ADMRect* outLocalRect);
	void ADMAPI (*GetBoundsRect)(ADMEntryRef inEntry, ADMRect* outBoundsRect);
	
	// coordinate transformations

	void ADMAPI (*LocalToScreenPoint)(ADMEntryRef inEntry, ADMPoint* ioPoint);
	void ADMAPI (*ScreenToLocalPoint)(ADMEntryRef inEntry, ADMPoint* ioPoint);
	
	void ADMAPI (*LocalToScreenRect)(ADMEntryRef inEntry, ADMRect* ioRect);
	void ADMAPI (*ScreenToLocalRect)(ADMEntryRef inEntry, ADMRect* ioRect);
	
	// redraw requests
	
	void ADMAPI (*Invalidate)(ADMEntryRef inEntry);
	void ADMAPI (*InvalidateRect)(ADMEntryRef inEntry, const ADMRect* inInvalRect);
	void ADMAPI (*Update)(ADMEntryRef inEntry);
	
	// entry picture accessors
	
	void ADMAPI (*SetPictureID)(ADMEntryRef inEntry, ADMInt32 inPictureResID);
	ADMInt32 ADMAPI (*GetPictureID)(ADMEntryRef inEntry);
	
	void ADMAPI (*SetSelectedPictureID)(ADMEntryRef inEntry, ADMInt32 inPictureResID);
	ADMInt32 ADMAPI (*GetSelectedPictureID)(ADMEntryRef inEntry);
	
	void ADMAPI (*SetDisabledPictureID)(ADMEntryRef inEntry, ADMInt32 inPictureResID);
	ADMInt32 ADMAPI (*GetDisabledPictureID)(ADMEntryRef inEntry);
	
	// entry text accessors

	void ADMAPI (*SetText)(ADMEntryRef inEntry, const char* inText);
	void ADMAPI (*GetText)(ADMEntryRef inEntry, char* outText, ADMInt32 inMaxLength);
	ADMInt32 ADMAPI (*GetTextLength)(ADMEntryRef inEntry);
	
	// entry timer accessors
	
	ADMTimerRef ADMAPI (*CreateTimer)(ADMEntryRef inEntry, ADMUInt32 inMilliseconds,
				ADMActionMask inAbortMask, ADMEntryTimerProc inTimerProc,
				ADMEntryTimerAbortProc inTimerAbortProc);

	void ADMAPI (*AbortTimer)(ADMEntryRef inEntry, ADMTimerRef inTimer);

}
ADMEntrySuite2;

typedef ADMEntrySuite2 ADMEntrySuite;


// =============================================================================
//		* ADM Entry Suite, version 3
// =============================================================================

#define kADMEntrySuiteVersion3 3

// -----------------------------------------------------------------------------

typedef struct ADMEntrySuite3
{

	// entry creation/destruction

	ADMEntryRef ADMAPI (*Create)(ADMListRef inList);
	void ADMAPI (*Destroy)(ADMEntryRef inEntry);
	
	// default behaviors
	
	void ADMAPI (*DefaultDraw)(ADMEntryRef inEntry, ADMDrawerRef inDrawer);
	ADMBoolean ADMAPI (*DefaultTrack)(ADMEntryRef inEntry, ADMTrackerRef inTracker);
	void ADMAPI (*DefaultNotify)(ADMEntryRef inEntry, ADMNotifierRef inNotifier);
	void ADMAPI (*SendNotify)(ADMEntryRef inEntry, const char* inNotifierType);
	
	// container accessors
	
	ADMInt32 ADMAPI (*GetIndex)(ADMEntryRef inEntry);
	ADMListRef ADMAPI (*GetList)(ADMEntryRef inEntry);
	
	// entry ID
		
	void ADMAPI (*SetID)(ADMEntryRef inEntry, ADMInt32 inEntryID);
	ADMInt32 ADMAPI (*GetID)(ADMEntryRef inEntry);
	
	// entry user data storage
	
	void ADMAPI (*SetUserData)(ADMEntryRef inEntry, ADMUserData inUserData);
	ADMUserData ADMAPI (*GetUserData)(ADMEntryRef inEntry);

	// entry selection status

	void ADMAPI (*Select)(ADMEntryRef inEntry, ADMBoolean inSelect);
	ADMBoolean ADMAPI (*IsSelected)(ADMEntryRef inEntry);
	
	// entry visibility
	
	void ADMAPI (*MakeInBounds)(ADMEntryRef inEntry);
	ADMBoolean ADMAPI (*IsInBounds)(ADMEntryRef inEntry);

	// entry state accessors

	void ADMAPI (*Enable)(ADMEntryRef inEntry, ADMBoolean inEnable);
	ADMBoolean ADMAPI (*IsEnabled)(ADMEntryRef inEntry);
	
	void ADMAPI (*Activate)(ADMEntryRef inEntry, ADMBoolean inActivate);
	ADMBoolean ADMAPI (*IsActive)(ADMEntryRef inEntry);
	
	void ADMAPI (*Check)(ADMEntryRef inEntry, ADMBoolean inCheck);
	ADMBoolean ADMAPI (*IsChecked)(ADMEntryRef inEntry);
	
	void ADMAPI (*MakeSeparator)(ADMEntryRef inEntry, ADMBoolean inSeparator);
	ADMBoolean ADMAPI (*IsSeparator)(ADMEntryRef inEntry);

	// entry bounds accessors

	void ADMAPI (*GetLocalRect)(ADMEntryRef inEntry, ADMRect* outLocalRect);
	void ADMAPI (*GetBoundsRect)(ADMEntryRef inEntry, ADMRect* outBoundsRect);
	
	// coordinate transformations

	void ADMAPI (*LocalToScreenPoint)(ADMEntryRef inEntry, ADMPoint* ioPoint);
	void ADMAPI (*ScreenToLocalPoint)(ADMEntryRef inEntry, ADMPoint* ioPoint);
	
	void ADMAPI (*LocalToScreenRect)(ADMEntryRef inEntry, ADMRect* ioRect);
	void ADMAPI (*ScreenToLocalRect)(ADMEntryRef inEntry, ADMRect* ioRect);
	
	// redraw requests
	
	void ADMAPI (*Invalidate)(ADMEntryRef inEntry);
	void ADMAPI (*InvalidateRect)(ADMEntryRef inEntry, const ADMRect* inInvalRect);
	void ADMAPI (*Update)(ADMEntryRef inEntry);
	
	// entry picture accessors
	
	void ADMAPI (*SetPictureID)(ADMEntryRef inEntry, ADMInt32 inPictureResID);
	ADMInt32 ADMAPI (*GetPictureID)(ADMEntryRef inEntry);
	
	void ADMAPI (*SetSelectedPictureID)(ADMEntryRef inEntry, ADMInt32 inPictureResID);
	ADMInt32 ADMAPI (*GetSelectedPictureID)(ADMEntryRef inEntry);
	
	void ADMAPI (*SetDisabledPictureID)(ADMEntryRef inEntry, ADMInt32 inPictureResID);
	ADMInt32 ADMAPI (*GetDisabledPictureID)(ADMEntryRef inEntry);
	
	// entry text accessors

	void ADMAPI (*SetText)(ADMEntryRef inEntry, const char* inText);
	void ADMAPI (*GetText)(ADMEntryRef inEntry, char* outText, ADMInt32 inMaxLength);
	ADMInt32 ADMAPI (*GetTextLength)(ADMEntryRef inEntry);
	
	// entry timer accessors
	
	ADMTimerRef ADMAPI (*CreateTimer)(ADMEntryRef inEntry, ADMUInt32 inMilliseconds,
				ADMActionMask inAbortMask, ADMEntryTimerProc inTimerProc,
				ADMEntryTimerAbortProc inTimerAbortProc);

	void ADMAPI (*AbortTimer)(ADMEntryRef inEntry, ADMTimerRef inTimer);

	// entry help ID
	// dhearst 6/28/02 - ADM no longer supports ASHelp
	ADMInt32 ADMAPI (*GetHelpID_DEPRECATED)(ADMEntryRef inEntry);
	void ADMAPI (*SetHelpID_DEPRECATED)(ADMEntryRef inEntry, ADMInt32 inHelpID);
	void ADMAPI (*Help_DEPRECATED)(ADMEntryRef inEntry);

}
ADMEntrySuite3;


// =============================================================================
//		* ADM Entry Suite, version 4
// =============================================================================

#define kADMEntrySuiteVersion4 4

// -----------------------------------------------------------------------------

typedef struct ADMEntrySuite4
{

	// *** This suite is FROZEN.
	// *** It shipped with Photoshop 5.5 and ImageReady 2.0.

	// entry creation/destruction

	ADMEntryRef ADMAPI (*Create)(ADMListRef inList);
	void ADMAPI (*Destroy)(ADMEntryRef inEntry);

	// default behaviors
	
	void ADMAPI (*DefaultDraw)(ADMEntryRef inEntry, ADMDrawerRef inDrawer);
	ADMBoolean ADMAPI (*DefaultTrack)(ADMEntryRef inEntry, ADMTrackerRef inTracker);
	void ADMAPI (*DefaultNotify)(ADMEntryRef inEntry, ADMNotifierRef inNotifier);
	void ADMAPI (*SendNotify)(ADMEntryRef inEntry, const char* inNotifierType);

	// container accessors
	
	ADMInt32 ADMAPI (*GetIndex)(ADMEntryRef inEntry);
	ADMListRef ADMAPI (*GetList)(ADMEntryRef inEntry);

	// entry ID
		
	void ADMAPI (*SetID)(ADMEntryRef inEntry, ADMInt32 inEntryID);
	ADMInt32 ADMAPI (*GetID)(ADMEntryRef inEntry);
	
	// entry user data storage
	
	void ADMAPI (*SetUserData)(ADMEntryRef inEntry, ADMUserData inUserData);
	ADMUserData ADMAPI (*GetUserData)(ADMEntryRef inEntry);

	// entry selection status

	void ADMAPI (*Select)(ADMEntryRef inEntry, ADMBoolean inSelect);
	ADMBoolean ADMAPI (*IsSelected)(ADMEntryRef inEntry);

	// entry visibility
	
	void ADMAPI (*MakeInBounds)(ADMEntryRef inEntry);
	ADMBoolean ADMAPI (*IsInBounds)(ADMEntryRef inEntry);

	// entry state accessors

	void ADMAPI (*Enable)(ADMEntryRef inEntry, ADMBoolean inEnable);
	ADMBoolean ADMAPI (*IsEnabled)(ADMEntryRef inEntry);
	
	void ADMAPI (*Activate)(ADMEntryRef inEntry, ADMBoolean inActivate);
	ADMBoolean ADMAPI (*IsActive)(ADMEntryRef inEntry);
	
	void ADMAPI (*Check)(ADMEntryRef inEntry, ADMBoolean inCheck);
	ADMBoolean ADMAPI (*IsChecked)(ADMEntryRef inEntry);
	
	void ADMAPI (*MakeSeparator)(ADMEntryRef inEntry, ADMBoolean inSeparator);
	ADMBoolean ADMAPI (*IsSeparator)(ADMEntryRef inEntry);

	// entry bounds accessors

	void ADMAPI (*GetLocalRect)(ADMEntryRef inEntry, ADMRect* outLocalRect);
	void ADMAPI (*GetBoundsRect)(ADMEntryRef inEntry, ADMRect* outBoundsRect);
	
	// coordinate transformations

	void ADMAPI (*LocalToScreenPoint)(ADMEntryRef inEntry, ADMPoint* ioPoint);
	void ADMAPI (*ScreenToLocalPoint)(ADMEntryRef inEntry, ADMPoint* ioPoint);
	
	void ADMAPI (*LocalToScreenRect)(ADMEntryRef inEntry, ADMRect* ioRect);
	void ADMAPI (*ScreenToLocalRect)(ADMEntryRef inEntry, ADMRect* ioRect);

	// redraw requests
	
	void ADMAPI (*Invalidate)(ADMEntryRef inEntry);
	void ADMAPI (*InvalidateRect)(ADMEntryRef inEntry, const ADMRect* inInvalRect);
	void ADMAPI (*Update)(ADMEntryRef inEntry);
	
	// entry picture accessors
	
	void ADMAPI (*SetPictureID)(ADMEntryRef inEntry, ADMInt32 inPictureResID,
				const char* inPictureResName);

	void ADMAPI (*GetPictureID)(ADMEntryRef inEntry, ADMInt32* outPictureResID,
				const char** outPictureResName);
	
	void ADMAPI (*SetSelectedPictureID)(ADMEntryRef inEntry, ADMInt32 inPictureResID,
				const char* inPictureResName);

	void ADMAPI (*GetSelectedPictureID)(ADMEntryRef inEntry, ADMInt32* outPictureResID,
				const char** outPictureResName);
	
	void ADMAPI (*SetDisabledPictureID)(ADMEntryRef inEntry, ADMInt32 inPictureResID,
				const char* inPictureResName);
				
	void ADMAPI (*GetDisabledPictureID)(ADMEntryRef inEntry, ADMInt32* outPictureResID,
				const char** outPictureResName);
	
	void ADMAPI (*SetPicture)(ADMEntryRef inEntry, ADMIconRef inPicture);
	ADMIconRef ADMAPI (*GetPicture)(ADMEntryRef inEntry);

	void ADMAPI (*SetSelectedPicture)(ADMEntryRef inEntry, ADMIconRef inPicture);
	ADMIconRef ADMAPI (*GetSelectedPicture)(ADMEntryRef inEntry);

	void ADMAPI (*SetDisabledPicture)(ADMEntryRef inEntry, ADMIconRef inPicture);
	ADMIconRef ADMAPI (*GetDisabledPicture)(ADMEntryRef inEntry);

	// entry text accessors

	void ADMAPI (*SetText)(ADMEntryRef inEntry, const char* inText);
	void ADMAPI (*GetText)(ADMEntryRef inEntry, char* outText, ADMInt32 inMaxLength);
	ADMInt32 ADMAPI (*GetTextLength)(ADMEntryRef inEntry);
	
	// entry timer accessors
	
	ADMTimerRef ADMAPI (*CreateTimer)(ADMEntryRef inEntry, ADMUInt32 inMilliseconds,
				ADMActionMask inAbortMask, ADMEntryTimerProc inTimerProc,
				ADMEntryTimerAbortProc inTimerAbortProc, ADMInt32 inOptions);

	void ADMAPI (*AbortTimer)(ADMEntryRef inEntry, ADMTimerRef inTimer);

	// entry help ID
	// dhearst 6/28/02 - ADM no longer supports ASHelp
	ADMInt32 ADMAPI (*GetHelpID_DEPRECATED)(ADMEntryRef inEntry);
	void ADMAPI (*SetHelpID_DEPRECATED)(ADMEntryRef inEntry, ADMInt32 inHelpID);
	void ADMAPI (*Help_DEPRECATED)(ADMEntryRef inEntry);

	// entry checkmark accessors

	void ADMAPI (*SetCheckGlyph)(ADMEntryRef inEntry, ADMStandardCheckGlyphID inCheckGlyph);
	ADMStandardCheckGlyphID ADMAPI (*GetCheckGlyph)(ADMEntryRef inEntry);
	
}
ADMEntrySuite4;	//	kADMEntrySuiteVersion4

// =============================================================================
//		* ADM Entry Suite, version 5
// =============================================================================

// -----------------------------------------------------------------------------

#define kADMEntrySuiteVersion5 5

// -----------------------------------------------------------------------------

typedef struct ADMEntrySuite5
{

	// *** This suite is FROZEN.
	// *** It shipped with Acrobat 5.0.

	// entry creation/destruction

	ADMEntryRef ADMAPI (*Create)(ADMListRef inList);
	void ADMAPI (*Destroy)(ADMEntryRef inEntry);

	// default behaviors
	
	void ADMAPI (*DefaultDraw)(ADMEntryRef inEntry, ADMDrawerRef inDrawer);
	ADMBoolean ADMAPI (*DefaultTrack)(ADMEntryRef inEntry, ADMTrackerRef inTracker);
	void ADMAPI (*DefaultNotify)(ADMEntryRef inEntry, ADMNotifierRef inNotifier);
	void ADMAPI (*SendNotify)(ADMEntryRef inEntry, const char* inNotifierType);

	// container accessors
	
	ADMInt32 ADMAPI (*GetIndex)(ADMEntryRef inEntry);
	ADMListRef ADMAPI (*GetList)(ADMEntryRef inEntry);

	// entry ID
		
	void ADMAPI (*SetID)(ADMEntryRef inEntry, ADMInt32 inEntryID);
	ADMInt32 ADMAPI (*GetID)(ADMEntryRef inEntry);
	
	// entry user data storage
	
	void ADMAPI (*SetUserData)(ADMEntryRef inEntry, ADMUserData inUserData);
	ADMUserData ADMAPI (*GetUserData)(ADMEntryRef inEntry);

	// entry selection status

	void ADMAPI (*Select)(ADMEntryRef inEntry, ADMBoolean inSelect);
	ADMBoolean ADMAPI (*IsSelected)(ADMEntryRef inEntry);

	// entry visibility
	
	void ADMAPI (*MakeInBounds)(ADMEntryRef inEntry);
	ADMBoolean ADMAPI (*IsInBounds)(ADMEntryRef inEntry);

	// entry state accessors

	void ADMAPI (*Enable)(ADMEntryRef inEntry, ADMBoolean inEnable);
	ADMBoolean ADMAPI (*IsEnabled)(ADMEntryRef inEntry);
	
	void ADMAPI (*Activate)(ADMEntryRef inEntry, ADMBoolean inActivate);
	ADMBoolean ADMAPI (*IsActive)(ADMEntryRef inEntry);
	
	void ADMAPI (*Check)(ADMEntryRef inEntry, ADMBoolean inCheck);
	ADMBoolean ADMAPI (*IsChecked)(ADMEntryRef inEntry);
	
	void ADMAPI (*MakeSeparator)(ADMEntryRef inEntry, ADMBoolean inSeparator);
	ADMBoolean ADMAPI (*IsSeparator)(ADMEntryRef inEntry);

	// entry bounds accessors

	void ADMAPI (*GetLocalRect)(ADMEntryRef inEntry, ADMRect* outLocalRect);
	void ADMAPI (*GetBoundsRect)(ADMEntryRef inEntry, ADMRect* outBoundsRect);
	
	// coordinate transformations

	void ADMAPI (*LocalToScreenPoint)(ADMEntryRef inEntry, ADMPoint* ioPoint);
	void ADMAPI (*ScreenToLocalPoint)(ADMEntryRef inEntry, ADMPoint* ioPoint);
	
	void ADMAPI (*LocalToScreenRect)(ADMEntryRef inEntry, ADMRect* ioRect);
	void ADMAPI (*ScreenToLocalRect)(ADMEntryRef inEntry, ADMRect* ioRect);

	// redraw requests
	
	void ADMAPI (*Invalidate)(ADMEntryRef inEntry);
	void ADMAPI (*InvalidateRect)(ADMEntryRef inEntry, const ADMRect* inInvalRect);
	void ADMAPI (*Update)(ADMEntryRef inEntry);
	
	// entry picture accessors
	
	void ADMAPI (*SetPictureID)(ADMEntryRef inEntry, ADMInt32 inPictureResID,
				const char* inPictureResName);

	void ADMAPI (*GetPictureID)(ADMEntryRef inEntry, ADMInt32* outPictureResID,
				const char** outPictureResName);
	
	void ADMAPI (*SetSelectedPictureID)(ADMEntryRef inEntry, ADMInt32 inPictureResID,
				const char* inPictureResName);

	void ADMAPI (*GetSelectedPictureID)(ADMEntryRef inEntry, ADMInt32* outPictureResID,
				const char** outPictureResName);
	
	void ADMAPI (*SetDisabledPictureID)(ADMEntryRef inEntry, ADMInt32 inPictureResID,
				const char* inPictureResName);
				
	void ADMAPI (*GetDisabledPictureID)(ADMEntryRef inEntry, ADMInt32* outPictureResID,
				const char** outPictureResName);
	
	void ADMAPI (*SetPicture)(ADMEntryRef inEntry, ADMIconRef inPicture);
	ADMIconRef ADMAPI (*GetPicture)(ADMEntryRef inEntry);

	void ADMAPI (*SetSelectedPicture)(ADMEntryRef inEntry, ADMIconRef inPicture);
	ADMIconRef ADMAPI (*GetSelectedPicture)(ADMEntryRef inEntry);

	void ADMAPI (*SetDisabledPicture)(ADMEntryRef inEntry, ADMIconRef inPicture);
	ADMIconRef ADMAPI (*GetDisabledPicture)(ADMEntryRef inEntry);

	// entry text accessors

	void ADMAPI (*SetText)(ADMEntryRef inEntry, const char* inText);
	void ADMAPI (*SetTextW)(ADMEntryRef inEntry, const ADMUnicode* inText);

	void ADMAPI (*GetText)(ADMEntryRef inEntry, char* outText, ADMInt32 inMaxLength);
	void ADMAPI (*GetTextW)(ADMEntryRef inEntry, ADMUnicode* outText, ADMInt32 inMaxLength);

	ADMInt32 ADMAPI (*GetTextLength)(ADMEntryRef inEntry);
	ADMInt32 ADMAPI (*GetTextLengthW)(ADMEntryRef inEntry);
	
	// entry timer accessors
	
	ADMTimerRef ADMAPI (*CreateTimer)(ADMEntryRef inEntry, ADMUInt32 inMilliseconds,
				ADMActionMask inAbortMask, ADMEntryTimerProc inTimerProc,
				ADMEntryTimerAbortProc inTimerAbortProc, ADMInt32 inOptions);

	void ADMAPI (*AbortTimer)(ADMEntryRef inEntry, ADMTimerRef inTimer);

	// entry help ID
	// dhearst 6/28/02 - ADM no longer supports ASHelp
	ADMInt32 ADMAPI (*GetHelpID_DEPRECATED)(ADMEntryRef inEntry);
	void ADMAPI (*SetHelpID_DEPRECATED)(ADMEntryRef inEntry, ADMInt32 inHelpID);
	void ADMAPI (*Help_DEPRECATED)(ADMEntryRef inEntry);

	// entry checkmark accessors

	void ADMAPI (*SetCheckGlyph)(ADMEntryRef inEntry, ADMStandardCheckGlyphID inCheckGlyph);
	ADMStandardCheckGlyphID ADMAPI (*GetCheckGlyph)(ADMEntryRef inEntry);
	
}
ADMEntrySuite5;	//	kADMEntrySuiteVersion5

#pragma ADM_PRAGMA_IMPORT_END
#pragma ADM_PRAGMA_ALIGN_END

#ifdef __cplusplus
}
#endif

#endif
