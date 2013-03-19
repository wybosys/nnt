/***********************************************************************/
/*                                                                     */
/* ADMImageOld.h                                                       */
/* Old versions of ADM Image suite                                     */
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

#ifndef __ADMImageOld__
#define __ADMImageOld__

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
//		* ADM Image Suite, version 1
// =============================================================================

#define kADMImageSuiteVersion1 1
#define kADMImageSuiteVersion kADMImageSuiteVersion1	// not current, just frozen

// -----------------------------------------------------------------------------

typedef struct ADMImageSuite1
{
	ADMImageRef ADMAPI (*Create)(ADMInt32 inWidth, ADMInt32 inHeight);
	void ADMAPI (*Destroy)(ADMImageRef inImage);

	ADMInt32 ADMAPI (*GetWidth)(ADMImageRef inImage);
	ADMInt32 ADMAPI (*GetHeight)(ADMImageRef inImage);
	ADMInt32 ADMAPI (*GetByteWidth)(ADMImageRef inImage);
	ADMInt32 ADMAPI (*GetBitsPerPixel)(ADMImageRef inImage);
	
	ADMBytePtr ADMAPI (*BeginBaseAddressAccess)(ADMImageRef inImage);
	void ADMAPI (*EndBaseAddressAccess)(ADMImageRef inImage);
	
	ADMDrawerRef ADMAPI (*BeginADMDrawer)(ADMImageRef inImage);
	void ADMAPI (*EndADMDrawer)(ADMImageRef inImage);
	
	void ADMAPI (*BeginAGMImageAccess)(ADMImageRef inImage, struct _t_ADMAGMImageRecord* inImageRecord);
	void ADMAPI (*EndAGMImageAccess)(ADMImageRef inImage);
	
	ADMErr ADMAPI (*GetPixel)(ADMImageRef inImage, const ADMPoint* inPoint, ADMRGBColor* outColor);
	ADMErr ADMAPI (*SetPixel)(ADMImageRef inImage, const ADMPoint* inPoint, const ADMRGBColor* inColor);
	
	ADMImageRef ADMAPI (*CreateBitmap)(ADMInt32 inWidth, ADMInt32 inHeight);
	ADMImageRef ADMAPI (*CreateOffscreen)(ADMInt32 inWidth, ADMInt32 inHeight);

}
ADMImageSuite1;

typedef ADMImageSuite1 ADMImageSuite;	// for historical reasons


// -----------------------------------------------------------------------------

#pragma ADM_PRAGMA_IMPORT_END
#pragma ADM_PRAGMA_ALIGN_END

#ifdef __cplusplus
}
#endif

#endif
