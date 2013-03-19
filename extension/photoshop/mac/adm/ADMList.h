/*******************************************************************************
*
* ADMList.h -- ADM List Suite
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
* Started by Dave Lazarony, 07 May 1996
*
********************************************************************************/

/** @file ADMList.h ADM List Suite */

#ifndef __ADMList__
#define __ADMList__

#ifndef __ADMTypes__
#include "ADMTypes.h"
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
//	User-provided function types

/** ... */
typedef ADMErr ADMAPI (*ADMEntryInitProc)(ADMEntryRef inEntry);
/** ... */
typedef void ADMAPI (*ADMEntryDrawProc)(ADMEntryRef inEntry, ADMDrawerRef inDrawer);
/** ... */
typedef ADMBoolean ADMAPI (*ADMEntryTrackProc)(ADMEntryRef inEntry, ADMTrackerRef inTracker);
/** ... */
typedef void ADMAPI (*ADMEntryNotifyProc)(ADMEntryRef inEntry, ADMNotifierRef inNotifier);
/** ... */
typedef void ADMAPI (*ADMEntryDestroyProc)(ADMEntryRef inEntry);


// =============================================================================
//		* ADM List Suite
// =============================================================================

/** ... */
#define kADMListSuite "ADM List Suite"
/** ... */
#define kADMListSuiteVersion4 4

// -----------------------------------------------------------------------------

/** ... */
typedef struct ADMListSuite4
{

	// *** This suite is FROZEN.
	// *** It shipped with Acrobat 6.0.

	// menu IDs

	/** ... */
	void ADMAPI (*SetMenuID)(ADMListRef inList, SPPluginRef inMenuResPlugin,
				ADMInt32 inMenuResID, const char* inMenuResName);

	/** ... */
	ADMInt32 ADMAPI (*GetMenuID)(ADMListRef inList);

	// container accessor
	
	/** ... */
	ADMItemRef ADMAPI (*GetItem)(ADMListRef inList);

	// user data storage
	
	/** ... */
	void ADMAPI (*SetUserData)(ADMListRef inList, ADMUserData inUserData);
	/** ... */
	ADMUserData ADMAPI (*GetUserData)(ADMListRef inList);

	// override hooks

	/** ... */
	void ADMAPI (*SetInitProc)(ADMListRef inList, ADMEntryInitProc inInitProc);
	/** ... */
	ADMEntryInitProc ADMAPI (*GetInitProc)(ADMListRef inList);
	
	/** ... */
	void ADMAPI (*SetDrawProc)(ADMListRef inList, ADMEntryDrawProc inDrawProc);
	/** ... */
	ADMEntryDrawProc ADMAPI (*GetDrawProc)(ADMListRef inList);
	
	/** ... */
	void ADMAPI (*SetTrackProc)(ADMListRef inList, ADMEntryTrackProc inTrackProc);
	/** ... */
	ADMEntryTrackProc ADMAPI (*GetTrackProc)(ADMListRef inList);
	
	/** ... */
	void ADMAPI (*SetNotifyProc)(ADMListRef inList, ADMEntryNotifyProc inNotifyProc);
	/** ... */
	ADMEntryNotifyProc ADMAPI (*GetNotifyProc)(ADMListRef inList);
	
	/** ... */
	void ADMAPI (*SetDestroyProc)(ADMListRef inList, ADMEntryDestroyProc inDestroyProc);
	/** ... */
	ADMEntryDestroyProc ADMAPI (*GetDestroyProc)(ADMListRef inList);

	// entry bounds accessors
	
	/** ... */
	void ADMAPI (*SetEntryWidth)(ADMListRef inList, ADMInt32 inWidth);
	/** ... */
	ADMInt32 ADMAPI (*GetEntryWidth)(ADMListRef inList);
	
	/** ... */
	void ADMAPI (*SetEntryHeight)(ADMListRef inList, ADMInt32 inHeight);
	/** ... */
	ADMInt32 ADMAPI (*GetEntryHeight)(ADMListRef inList);
	
	/** ... */
	void ADMAPI (*SetEntryTextRect)(ADMListRef inList, const ADMRect* inRect);
	/** ... */
	void ADMAPI (*GetEntryTextRect)(ADMListRef inList, ADMRect* outRect);
	
	// entry array accessors
	
	/** ... */
	ADMEntryRef ADMAPI (*InsertEntry)(ADMListRef inList, ADMInt32 inIndex);
	/** ... */
	void ADMAPI (*RemoveEntry)(ADMListRef inList, ADMInt32 inIndex);
	
	/** ... */
	ADMEntryRef ADMAPI (*GetEntry)(ADMListRef inList, ADMInt32 inEntryID);
	/** ... */
	ADMEntryRef ADMAPI (*IndexEntry)(ADMListRef inList, ADMInt32 inIndex);
	/** ... */
	ADMEntryRef ADMAPI (*FindEntry)(ADMListRef inList, const char* inText);
	/** ... */
	ADMEntryRef ADMAPI (*PickEntry)(ADMListRef inList, const ADMPoint* inPoint);
	
	/** ... */
	ADMEntryRef ADMAPI (*GetActiveEntry)(ADMListRef inList);
	/** ... */
	ADMEntryRef ADMAPI (*IndexSelectedEntry)(ADMListRef inList, ADMInt32 inSelectionIndex);
	
	/** ... */
	ADMInt32 ADMAPI (*NumberOfEntries)(ADMListRef inList);
	/** ... */
	ADMInt32 ADMAPI (*NumberOfSelectedEntries)(ADMListRef inList);

	// item action mask
	
	/** ... */
	void ADMAPI (*SetMask)(ADMListRef inEntry, ADMActionMask inActionMask);
	/** ... */
	ADMActionMask ADMAPI (*GetMask)(ADMListRef inEntry);

	// user data storage for notifiers

	/** ... */
	void ADMAPI (*SetNotifierData)(ADMListRef inEntry, ADMUserData inUserData);
	/** ... */
	ADMUserData ADMAPI (*GetNotifierData)(ADMListRef inEntry);

	// customizing appearance
	
	/** ... */
	void ADMAPI (*SetBackgroundColor)(ADMListRef inList, ADMColor inColor);
	
	// searching
	
	/** ... */
	void ADMAPI (*SelectByText)(ADMListRef inList, const char* inFindText);
	/** ... */
	void ADMAPI (*SelectByTextW)(ADMListRef inList, const ADMUnicode* inFindText);
	
	/** ... */
	ADMEntryRef ADMAPI (*FindEntryW)(ADMListRef inList, const ADMUnicode* inText);

} ADMListSuite4;


// -----------------------------------------------------------------------------
//	Old versions of suites

#ifndef __ADMListOld__
#ifdef MAC_ENV
#include "ADMListOld.h"
#else
#include ".\Legacy\ADMListOld.h"
#endif
#endif

// -----------------------------------------------------------------------------

#pragma ADM_PRAGMA_IMPORT_END
#pragma ADM_PRAGMA_ALIGN_END

#ifdef __cplusplus
}
#endif

// -----------------------------------------------------------------------------

#endif	// __ADMList__
