/***********************************************************************/
/*                                                                     */
/* ADMNotifierOld.h                                                    */
/* Old versions of ADM Notifier Suite                                  */
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

#ifndef __ADMNotifierOld__
#define __ADMNotifierOld__

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
//		* ADM Notifier Suite, version 1
// =============================================================================

#define kADMNotifierSuiteVersion1 1
#define kADMNotifierSuiteVersion kADMNotifierSuiteVersion1

typedef struct ADMNotifierSuite1
{
	ADMItemRef ADMAPI (*GetItem)(ADMNotifierRef inNotifier);
	ADMDialogRef ADMAPI (*GetDialog)(ADMNotifierRef inNotifier);
	
	ADMBoolean ADMAPI (*IsNotifierType)(ADMNotifierRef inNotifier, const char* inNotifierType);
	void ADMAPI (*GetNotifierType)(ADMNotifierRef inNotifier, char* outNotifierType, ADMUInt32 inMaxLen);

}
ADMNotifierSuite1;

typedef ADMNotifierSuite1 ADMNotifierSuite;

// -----------------------------------------------------------------------------

#pragma ADM_PRAGMA_IMPORT_END
#pragma ADM_PRAGMA_ALIGN_END

#ifdef __cplusplus
}
#endif

#endif
