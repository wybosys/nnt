/***********************************************************************/
/*                                                                     */
/* ADMDialogGroupOld.h                                                 */
/* Old versions of ADM Dialog Group Suite                              */
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

#ifndef __ADMDialogGroupOld__
#define __ADMDialogGroupOld__

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
//		* ADM Dialog Group Suite, version 1
// =============================================================================

#define kADMDialogGroupSuiteVersion1 1
#define kADMDialogGroupSuiteVersion 1
#define kADMDialogGroupVersion kADMDialogGroupSuiteVersion1

// -----------------------------------------------------------------------------

typedef struct ADMDialogGroupSuite1
{

	ADMErr ADMAPI (*GetDialogName)(ADMDialogRef inDialog, const char** outName);

	ADMErr ADMAPI (*GetDialogGroupInfo)(ADMDialogRef inDialog, const char** outGroupName,
				ADMInt32* outPositionCode);

	ADMErr ADMAPI (*SetDialogGroupInfo)(ADMDialogRef inDialog, const char* inGroupName,
				ADMInt32 inPositionCode);

	// The queries below take a docking position code obtained from above functions or prefs

		// You should always create a palette that is not stand alone
	ADMBoolean ADMAPI (*IsStandAlonePalette)(ADMInt32 inPositionCode);

		// Your "show palette" menu would be "Show..." unless palette dock code returns true for
		// IsDockVisible() and IsFrontTab(). 
	ADMBoolean ADMAPI (*IsDockVisible)(ADMInt32 inPositionCode);
	ADMBoolean ADMAPI (*IsFrontTab)(ADMInt32 inPositionCode);

		// You probably won't ever use this, but it here for completeness.
	ADMBoolean ADMAPI (*IsCollapsed)(ADMInt32 inPositionCode);

	ADMErr ADMAPI (*SetTabGroup)(ADMDialogRef inDialog, const char* inTabGroupName,
				ADMBoolean inBringToFront);
 
	ADMErr ADMAPI (*CountDialogs)(ADMInt32* outCount);
	ADMErr ADMAPI (*GetNthDialog)(ADMInt32 inIndex, ADMDialogRef* outDialog);
	ADMErr ADMAPI (*GetNamedDialog)(const char* inName, ADMDialogRef* outDialog);

	void ADMAPI (*ToggleAllFloatingDialogs)();

} ADMDialogGroupSuite1;

typedef ADMDialogGroupSuite1 ADMDialogGroupSuite;	// for historical reasons


// =============================================================================
//		* ADM Dialog Group Suite, version 2
// =============================================================================

#define kADMDialogGroupSuiteVersion2 2

// -----------------------------------------------------------------------------

typedef struct ADMDialogGroupSuite2
{

	// *** This suite is FROZEN.
	// *** It shipped with Photoshop 5.5 and ImageReady 2.0.

	// dialog info

	ADMErr ADMAPI (*GetDialogName)(ADMDialogRef inDialog, const char** outName);

	ADMErr ADMAPI (*GetDialogGroupInfo)(ADMDialogRef inDialog, const char** outGroupName,
				ADMInt32* outPositionCode);

	ADMErr ADMAPI (*SetDialogGroupInfo)(ADMDialogRef inDialog, const char* inGroupName,
				ADMInt32 inPositionCode);

	// docking group info

		// The position codes used below are obtained from above functions or prefs.

		// You should always create a palette that is not stand alone
	ADMBoolean ADMAPI (*IsStandAlonePalette)(ADMInt32 inPositionCode);

		// Your "show palette" menu would be "Show..." unless palette dock code
		// returns true for IsDockVisible() and IsFrontTab().
	ADMBoolean ADMAPI (*IsDockVisible)(ADMInt32 inPositionCode);
	ADMBoolean ADMAPI (*IsFrontTab)(ADMInt32 inPositionCode);

		// You probably won't ever use this, but it here for completeness.
	ADMBoolean ADMAPI (*IsCollapsed)(ADMInt32 inPositionCode);

	// place a dialog in a tab group

	ADMErr ADMAPI (*SetTabGroup)(ADMDialogRef inDialog, const char* inTabGroupName,
				ADMBoolean inBringToFront);
 
 	// dialog list accessors
 
	ADMErr ADMAPI (*CountDialogs)(ADMInt32* outCount);
	ADMErr ADMAPI (*GetNthDialog)(ADMInt32 inIndex, ADMDialogRef* outDialog);
	ADMErr ADMAPI (*GetNamedDialog)(const char* inName, ADMDialogRef* outDialog);

	// show/hide floating palettes

	void ADMAPI (*ToggleAllFloatingDialogs)();
	void ADMAPI (*ShowAllFloatingDialogs)(ADMBoolean inShow);

}
ADMDialogGroupSuite2;

// -----------------------------------------------------------------------------

#pragma ADM_PRAGMA_IMPORT_END
#pragma ADM_PRAGMA_ALIGN_END

#ifdef __cplusplus
}
#endif

#endif
