/*******************************************************************************
*
* ADMIcon.h -- ADM Icon Suite
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
* Started by Paul Asente, 01 Aug 1996
*
********************************************************************************/

/** @file ADMIcon.h ADM Icon Suite */

#ifndef __ADMIcon__
#define __ADMIcon__

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
///	Icon types
enum ADMIconType {

	/// Mac type
	kCICN,
	/// Mac type
	kPICT,
	/// Mac type
	kIconSuite,
	
	/// Windows type
	kWinIcon,
	/// Windows type
	kBMP,

	/// Either type
	kADMImageIcon,
	
	/// Mac type
	kCGImage,	// Only supported on OS X (10.2 and later)
	
	kUnknown

};

#ifndef __cplusplus
typedef enum ADMIconType ADMIconType;
#endif

// =============================================================================
//		* ADM Icon Suite
// =============================================================================

/** Icon suite name */
#define kADMIconSuite				("ADM Icon Suite")
/** Icon suite version */
#define kADMIconSuiteVersion2		(2)

// -----------------------------------------------------------------------------

/**
	Icon suite
*/
typedef struct ADMIconSuite2
{

	// *** This suite is FROZEN.
	// *** It shipped with Photoshop 5.5 and ImageReady 2.0.

	/**
		@name Icon creation/destruction
	*/
	//@{
	ADMIconRef ADMAPI (*GetFromResource)(SPPluginRef inPluginRef, const char* inName,
				ADMInt32 inIconID, ADMInt32 inIconIndex);
	/** ... */
	ADMIconRef ADMAPI (*Create)(ADMIconType inIconType, ADMInt32 inWidth,
				ADMInt32 inHeight, void* inData);
	/** ... */
	void ADMAPI (*Destroy)(ADMIconRef inIcon);
	//@}

	/**
		@name Icon data accessors
	*/
	//@{
	/** ... */
	ADMIconType ADMAPI (*GetType)(ADMIconRef inIcon);
	/** ... */
	ADMInt32 ADMAPI (*GetWidth)(ADMIconRef inIcon);
	/** ... */
	ADMInt32 ADMAPI (*GetHeight)(ADMIconRef inIcon);
	/** ... */
	ADMAPI void* (*GetData)(ADMIconRef inIcon);
	//@}

	/** ... */
	ADMBoolean ADMAPI (*IsFromResource)(ADMIconRef inIcon);

	/**
		Conversion from ADMImage

		The ADMIcon takes ownership of the image.
	*/
	ADMIconRef ADMAPI (*CreateFromImage)(ADMImageRef inImage);

}
ADMIconSuite2;


// -----------------------------------------------------------------------------
//	Old versions of suites

#ifndef __ADMIconOld__
#ifdef MAC_ENV
#include "ADMIconOld.h"
#else
#include ".\Legacy\ADMIconOld.h"
#endif
#endif

// -----------------------------------------------------------------------------

#pragma ADM_PRAGMA_IMPORT_END
#pragma ADM_PRAGMA_ALIGN_END

#ifdef __cplusplus
}
#endif
 
// -----------------------------------------------------------------------------

#endif	// __ADMIcon__
