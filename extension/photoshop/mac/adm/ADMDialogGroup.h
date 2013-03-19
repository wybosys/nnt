/*******************************************************************************
*
* ADMDialogGroup.h -- ADM Dialog Group Suite
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
* Started by Matt Foster, 28 Sep 1996
*
********************************************************************************/

/** @file ADMDialogGroup.h ADM Dialog Group Suite */

#ifndef __ADMDialogGroup__
#define __ADMDialogGroup__

#ifndef __ADMTypes__
#include "ADMTypes.h"
#endif


// -----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

#pragma ADM_PRAGMA_ALIGN_BEGIN
#pragma ADM_PRAGMA_IMPORT_BEGIN


// -----------------------------------------------------------------------------
//	Error codes.

/** ... */
#define kDockHostConflictError	'DOCK'
/** ... */
#define kTabGroupNotFoundError	'T!FD'
/** ... */
#define kAlreadyDockedError		'DCKD'


// -----------------------------------------------------------------------------
//	For the xxGroupInfo() functions, positionCode is a code to restore a
//	dialog's position within a docked/tabbed group. The group is
//	referred to by name, this being the name of the ADM Dialog that is
//	the first tab in the top dcok of the group.
//
//	You don't need to know what positionCode means, but if you are curious:
//
//	byte		  		meaning
//	----		 		------------------------------
//	1 (0x000000ff)		dock position. 0 is no dock, 1 is first docked (i.e. top dock), 2 etc.
//	2 (0x0000ff00)		tab position, 0 is no tab group, 1 is the 1st tab, 2 etc.
//	3 (0x00010000)		bit 16, boolean, 1 for front tab.
//	3 (0x00020000)		bit 17, boolean, 0 is zoom up, 1 is zoom down.
//	3 (0x00040000)		bit 18, boolean, 0 is in hidden dock, 1 is in visible dock.
//	4 (0x00000000)		reserved. currently unused
//
//	So for stand alone palette, the tab, dock position code is (0, ?, 0, 0)


	// default position code for stand alone palette
/** ... */
#define kADM_DPDefaultCode 0x00030000

	// dialog position byte
/** ... */
#define kADM_DPDockBit 0
/** ... */
#define kADM_DPTabBit 8
/** ... */
#define kADM_DPFrontTabBit 16
/** ... */
#define kADM_DPZoomBit 17
/** ... */
#define kADM_DPDockVisibleBit 18

	// dialog position code masks
/** ... */
#define kADM_DPDockMask 0x000000ff
/** ... */
#define kADM_DPTabMask 0x0000ff00
/** ... */
#define kADM_DPFrontTabMask 0x00010000
/** ... */
#define kADM_DPZoomMask 0x00020000
/** ... */
#define kADM_DPDockVisibleMask 0x00040000

	// strings for saving palette state into preference file
/** ... */
#define kADM_DPLocationStr "Location"
/** ... */
#define kADM_DPSizeStr "Size"			// save only for resizable standalone palettes
/** ... */
#define kADM_DPVisibleStr "Visible"
/** ... */
#define kADM_DPDockCodeStr "DockCode"
/** ... */
#define kADM_DPDockGroupStr "DockGroup"

/** ... */
#define kADM_DPDockGroupStrMaxLen 65
			// group name max size = 64 chars. 


// =============================================================================
//		* ADM Dialog Group Suite
// =============================================================================

/** ... */
#define kADMDialogGroupSuite "ADM Dialog Group Suite"
/** ... */
#define kADMDialogGroupSuiteVersion3 3

// -----------------------------------------------------------------------------

/** ... */
typedef struct ADMDialogGroupSuite3
{

	// *** This suite is FROZEN.
	// *** It shipped with Illustrator 9.0.

	// dialog info

	/** ... */
	ADMErr ADMAPI (*GetDialogName)(ADMDialogRef inDialog, const char** outName);

	/** ... */
	ADMErr ADMAPI (*GetDialogGroupInfo)(ADMDialogRef inDialog, const char** outGroupName,
				ADMInt32* outPositionCode);

	/** ... */
	ADMErr ADMAPI (*SetDialogGroupInfo)(ADMDialogRef inDialog, const char* inGroupName,
				ADMInt32 inPositionCode);

	// docking group info

		// The position codes used below are obtained from above functions or prefs.

		// You should always create a palette that is not stand alone
	/** ... */
	ADMBoolean ADMAPI (*IsStandAlonePalette)(ADMInt32 inPositionCode);

		// Your "show palette" menu would be "Show..." unless palette dock code
		// returns true for IsDockVisible() and IsFrontTab().
	/** ... */
	ADMBoolean ADMAPI (*IsDockVisible)(ADMInt32 inPositionCode);
	/** ... */
	ADMBoolean ADMAPI (*IsFrontTab)(ADMInt32 inPositionCode);

		// You probably won't ever use this, but it here for completeness.
	/** ... */
	ADMBoolean ADMAPI (*IsCollapsed)(ADMInt32 inPositionCode);

	// place a dialog in a tab group

	/** ... */
	ADMErr ADMAPI (*SetTabGroup)(ADMDialogRef inDialog, const char* inTabGroupName,
				ADMBoolean inBringToFront);
 
 	// dialog list accessors
 
	/** ... */
	ADMErr ADMAPI (*CountDialogs)(ADMInt32* outCount);
	/** ... */
	ADMErr ADMAPI (*GetNthDialog)(ADMInt32 inIndex, ADMDialogRef* outDialog);
	/** ... */
	ADMErr ADMAPI (*GetNamedDialog)(const char* inName, ADMDialogRef* outDialog);

	// show/hide floating palettes

	/** ... */
	void ADMAPI (*ToggleAllFloatingDialogs)(void);
	/** ... */
	void ADMAPI (*ToggleAllButNoCloseFloatingDialogs)(void);
	/** ... */
	void ADMAPI (*ShowAllFloatingDialogs)(ADMBoolean inShow);
}
ADMDialogGroupSuite3;


// -----------------------------------------------------------------------------
//	Old versions of suites

#ifndef __ADMDialogGroupOld__
#ifdef MAC_ENV
#include "ADMDialogGroupOld.h"
#else
#include ".\Legacy\ADMDialogGroupOld.h"
#endif
#endif

// -----------------------------------------------------------------------------

#pragma ADM_PRAGMA_IMPORT_END
#pragma ADM_PRAGMA_ALIGN_END

#ifdef __cplusplus
}
#endif

// -----------------------------------------------------------------------------

#endif	// __ADMDialogGroup__
