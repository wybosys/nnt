/*******************************************************************************
*
* ADMRadioGroup.h -- ADM Radio Group Suite
*
* ADOBE SYSTEMS INCORPORATED
* Copyright 2003 Adobe Systems Incorporated
* All Rights Reserved
*
* NOTICE: Adobe permits you to use, modify, and distribute this file in
* accordance with the terms of the Adobe license agreement accompanying it.
* If you have received this file from a source other than Adobe, then your use,
* modification, or distribution of it requires the prior written permission of
* Adobe.
*
* Started by David Hearst, 15 Jan 2003
*
********************************************************************************/

/** @file ADMRadioGroup.h ADM Radio Group Suite */

#ifndef __ADMRadioGroup__
#define __ADMRadioGroup__
 
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
//		* ADM Radio Group Suite
// =============================================================================

/// Basic suite name
#define kADMRadioGroupSuite ("ADM Radio Group Suite")

/// Basic suite version
#define kADMRadioGroupSuiteVersion1 1

// -----------------------------------------------------------------------------

/** ... */
struct ADMRadioGroupSuite1
{

	// *** This suite is FROZEN.
	// *** It shipped with Acrobat 6.0.

	// radio group creation/destruction

	/** ... */
	ADMErr ADMAPI (*Create)(ADMDialogRef inDialog, ADMRadioGroupRef* outRadioGroup);
	/** ... */
	ADMErr ADMAPI (*Destroy)(ADMDialogRef inDialog, ADMRadioGroupRef inRadioGroup);

	/** ... */
	ADMErr ADMAPI (*Add)(ADMRadioGroupRef inRadioGroup, ADMItemRef inItem);
	/** ... */
	ADMErr ADMAPI (*Remove)(ADMRadioGroupRef inRadioGroup, ADMItemRef inItem);

	/** ... */
	ADMErr ADMAPI (*GetForItem)(ADMItemRef inItem, ADMRadioGroupRef* outRadioGroup);

};

#ifndef __cplusplus
typedef struct ADMRadioGroupSuite1 ADMRadioGroupSuite1; 
#endif

// The following is not necessary until we rev the suite for the first time...
//
//// -----------------------------------------------------------------------------
////	Old versions of suites
//
//#ifndef __ADMRadioGroupOld__
//#ifdef MAC_ENV
//#include "ADMRadioGroupOld.h"
//#else
//#include ".\Legacy\ADMRadioGroupOld.h"
//#endif
//#endif

// -----------------------------------------------------------------------------

#pragma ADM_PRAGMA_IMPORT_END
#pragma ADM_PRAGMA_ALIGN_END

#ifdef __cplusplus
}
#endif

// -----------------------------------------------------------------------------

#endif	// __ADMRadioGroup__
