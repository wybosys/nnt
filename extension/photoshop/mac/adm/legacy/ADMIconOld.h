/***********************************************************************/
/*                                                                     */
/* ADMIconOld.h                                                        */
/* Old versions of ADM Icon Suite                                      */
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

#ifndef __ADMIconOld__
#define __ADMIconOld__

#ifndef __ADMTypes__
#include "ADMTypes.h"
#endif

#ifndef __ADMIcon__
#include "ADMIcon.h"
#endif


// -----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

#pragma ADM_PRAGMA_ALIGN_BEGIN
#pragma ADM_PRAGMA_IMPORT_BEGIN


// =============================================================================
//		* ADM Icon Suite, version 1
// =============================================================================

#define kADMIconSuiteVersion1 1
#define kADMIconSuiteVersion kADMIconSuiteVersion1

// -----------------------------------------------------------------------------

typedef struct ADMIconSuite1
{

	// icon creation/destruction

	ADMIconRef ADMAPI (*GetFromResource)(SPPluginRef inPluginRef, ADMInt32 inIconID,
				ADMInt32 inIconIndex);

	ADMIconRef ADMAPI (*Create)(ADMIconType inIconType, ADMInt32 inWidth,
				ADMInt32 inHeight, void* inData);

	void ADMAPI (*Destroy)(ADMIconRef inIcon);

	// icon data accessors

	ADMIconType ADMAPI (*GetType)(ADMIconRef inIcon);
	ADMInt32 ADMAPI (*GetWidth)(ADMIconRef inIcon);
	ADMInt32 ADMAPI (*GetHeight)(ADMIconRef inIcon);
	ADMAPI void* (*GetData)(ADMIconRef inIcon);

	ADMBoolean ADMAPI (*IsFromResource)(ADMIconRef inIcon);

}
ADMIconSuite1;

typedef ADMIconSuite1 ADMIconSuite;

// -----------------------------------------------------------------------------

#pragma ADM_PRAGMA_IMPORT_END
#pragma ADM_PRAGMA_ALIGN_END

#ifdef __cplusplus
}
#endif

#endif  // __ADMIconOld__
