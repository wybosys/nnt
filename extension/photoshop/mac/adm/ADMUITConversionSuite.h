/*******************************************************************************
*
* ADMUITConversion.h -- ADM UIT Conversion Suite
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
* Started by Deepali Agashe 16th September 2002
*
********************************************************************************/

/** @file ADMUITConversionSuite.h ADM UIT Conversion Suite */

#ifndef __ADMUITConversion__
#define __ADMUITConversion__

#ifndef __ADMDialog__
#include "ADMDialog.h"
#endif

#ifndef __SPUITTypes__
#include "spuit_Types.h"
#endif


// -----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

#pragma ADM_PRAGMA_ALIGN_BEGIN
#pragma ADM_PRAGMA_IMPORT_BEGIN



// =============================================================================
//		* ADM UIT Conversion Suite
// =============================================================================

/** ... */
#define kADMUITConversionSuite "ADM UIT Conversion Suite"
/** ... */
#define kADMUITConversionSuiteVersion1 1

// -----------------------------------------------------------------------------
/*	Important : Before using this suite please make sure that you are using these
	APIs ONLY in UIT context. Do not use them with old ADM windows.*/
/** ... */
typedef struct ADMUITConversionSuite1
{

	// *** This suite is FROZEN.
	// *** It shipped with Acrobat 6.0.

	// UIT Item to ADM Item
	/** ... */
	ADMItemRef ADMAPI (*GetADMItemRef)(UITItemRef inItem);

	// ADM Item to UIT Item
	/** ... */
	UITItemRef ADMAPI (*GetUITItemRef)(ADMItemRef inItem);

	// UIT window as dialog
	/** ... */
	ADMDialogRef ADMAPI (*CreateUITWindow)(SPPluginRef inPluginRef, const char* inName,
				ADMInt32 inDialogID, ADMDialogStyle inDialogStyle,
				ADMDialogInitProc inInitProc, ADMUserData inUserData,
				ADMInt32 inOptions);
	
	// Create and Show UIT Window as Modal
	/** ... */
	ADMInt32 ADMAPI (*ModalUITWindow)(SPPluginRef inPluginRef, const char* inName, 
				ADMInt32 inDialogID, ADMDialogStyle inDialogStyle, ADMDialogInitProc inInitProc, 
				ADMUserData inUserData, ADMInt32 inOptions);

	// UIT Window to ADM Dialog
	/** ... */
	ADMDialogRef ADMAPI (*GetADMDialogRef)(UITWindowRef inUITWindow);

	// ADM Dialog to UIT Window
	/** ... */
	UITWindowRef ADMAPI (*GetUITWindowRef)(ADMDialogRef inADMDialog);

	// Retrieve a child item with specified ADMItem ID while searching
	// below a specified Pane
	/** ... */
	ADMItemRef ADMAPI (*GetChildItemByID)(UITItemRef inParentUITItem, ADMInt32 inID);
	
	/** ... */
	ADMErr ADMAPI (*CreateAdapterForUnadaptedItem)(UITItemRef inItem, ADMInt32 inItemID, ADMUserData inUserData);
}
ADMUITConversionSuite1;


#pragma ADM_PRAGMA_IMPORT_END
#pragma ADM_PRAGMA_ALIGN_END

#ifdef __cplusplus
}
#endif

// -----------------------------------------------------------------------------

#endif	// __ADMUITConversion__
