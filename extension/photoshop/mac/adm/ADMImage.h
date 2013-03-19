/*******************************************************************************
*
* ADMImage.h -- ADM Image Suite
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
* Started by Dave Lazarony, 20 Nov 1996
*
********************************************************************************/

/** @file ADMImage.h ADM Image Suite */

#ifndef __ADMImage__
#define __ADMImage__

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

/** ... */
#define kADMImageHasAlphaChannelOption (1L << 0)


// =============================================================================
//		* ADM Image Suite
// =============================================================================

/** ... */
#define kADMImageSuite "ADM Image Suite"
/** ... */
#define kADMImageSuiteVersion2 2

// -----------------------------------------------------------------------------

/** ... */
typedef struct ADMImageSuite2
{

	// *** This suite is FROZEN.
	// *** It shipped with Photoshop 5.5 and ImageReady 2.0.

	// image creation/destruction

	/** ... */
	ADMImageRef ADMAPI (*Create)(ADMInt32 inWidth, ADMInt32 inHeight, ADMInt32 inOptions);
	/** ... */
	void ADMAPI (*Destroy)(ADMImageRef inImage);

	// image data accessors

	/** ... */
	ADMInt32 ADMAPI (*GetWidth)(ADMImageRef inImage);
	/** ... */
	ADMInt32 ADMAPI (*GetHeight)(ADMImageRef inImage);
	/** ... */
	ADMInt32 ADMAPI (*GetByteWidth)(ADMImageRef inImage);
	/** ... */
	ADMInt32 ADMAPI (*GetBitsPerPixel)(ADMImageRef inImage);
	
	// raw pixel data access
	
	/** ... */
	ADMBytePtr ADMAPI (*BeginBaseAddressAccess)(ADMImageRef inImage);
	/** ... */
	void ADMAPI (*EndBaseAddressAccess)(ADMImageRef inImage);

	// ADMDrawer access
	
	/** ... */
	ADMDrawerRef ADMAPI (*BeginADMDrawer)(ADMImageRef inImage);
	/** ... */
	void ADMAPI (*EndADMDrawer)(ADMImageRef inImage);

	// AGMImage access
		// only available if host app exports AGM suites
	
	/** ... */
	void ADMAPI (*BeginAGMImageAccess)(ADMImageRef inImage, struct _t_ADMAGMImageRecord* outImageRecord);
	/** ... */
	void ADMAPI (*EndAGMImageAccess)(ADMImageRef inImage);

	// single pixel access
	
	/** ... */
	ADMErr ADMAPI (*GetPixel)(ADMImageRef inImage, const ADMPoint* inPoint, ADMRGBColor* outColor);
	/** ... */
	ADMErr ADMAPI (*SetPixel)(ADMImageRef inImage, const ADMPoint* inPoint, const ADMRGBColor* inColor);

	// more image creation options
	
	/** ... */
	ADMImageRef ADMAPI (*CreateBitmap)(ADMInt32 inWidth, ADMInt32 inHeight, ADMInt32 inOptions);
	/** ... */
	ADMImageRef ADMAPI (*CreateOffscreen)(ADMInt32 inWidth, ADMInt32 inHeight, ADMInt32 inOptions);

}
ADMImageSuite2;


// -----------------------------------------------------------------------------
//	Old versions of suites

#ifndef __ADMImageOld__
#ifdef MAC_ENV
#include "ADMImageOld.h"
#else
#include ".\Legacy\ADMImageOld.h"
#endif
#endif

// -----------------------------------------------------------------------------

#pragma ADM_PRAGMA_IMPORT_END
#pragma ADM_PRAGMA_ALIGN_END

#ifdef __cplusplus
}
#endif

// -----------------------------------------------------------------------------

#endif	// __ADMImage__
