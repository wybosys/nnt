/*******************************************************************************
*
* ADMHostInitUnicode.h -- ADM Host Init Unicode Conversion Suite
*
* ADOBE SYSTEMS INCORPORATED
* Copyright 1999-2003 Adobe Systems Incorporated
* All Rights Reserved
*
* NOTICE: Adobe permits you to use, modify, and distribute this file in
* accordance with the terms of the Adobe license agreement accompanying it.
* If you have received this file from a source other than Adobe, then your use,
* modification, or distribution of it requires the prior written permission of
* Adobe.
*
* Started by Eric Scouten, 15 Nov 1999
* Updated by Dave Hackel, 01 Feb 2000
*
********************************************************************************/

/** @file ADMHostInitUnicode.h ADM Host Init Unicode Conversion Suite */

#ifndef __ADMUnicode__
#define __ADMUnicode__

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
#define kADMScriptRoman			0
/** ... */
#define	kADMScriptJapanese		1
/** ... */
#define	kADMScriptTradChinese	2
/** ... */
#define	kADMScriptKorean		3
/** ... */
#define kADMScriptArabic		4
/** ... */
#define kADMScriptHebrew		5
/** ... */
#define kADMScriptGreek			6
/** ... */
#define	kADMScriptCyrillic		7
/** ... */
#define	kADMScriptSimpChinese	25
/** ... */
#define	kADMScriptEastEurope	29

// [cpaduan] 8/23/02 - WinSoft Integration
#if BUILD_WINSOFT
/* [WinSoft - 02/2002]
The following constant have been added to support Baltic and Turkish script. 
These values are compatible with other Adobe CE product
*/
/** ... */
#define kADMScriptTurkish 81
/** ... */
#define kADMScriptBaltic 85
#endif // BUILD_WINSOFT

// =============================================================================
//		* ADM Host Init Unicode Conversion Suite
// =============================================================================
//	The host of ADM can provide this suite for ADM to use at runtime.
//	This suite is only required if the host application (or any of its plugins)
//	wishes to set or retrieve text from ADM's interfaces via Unicode.
//	If the application only communicates with ADM using multibyte encodings,
//	this suite can be omitted.
 
/** ... */
#define kADMHostInitUnicodeSuite "ADM Host Init Unicode Suite"
/** ... */
#define kADMHostInitUnicodeSuiteVersion1 1

// -----------------------------------------------------------------------------

/** ... */
typedef struct ADMHostInitUnicodeSuite1
{

	// *** This suite is FROZEN.
	// *** It shipped with Acrobat 5.0.

	// character conversion

	/** ... */
	ADMErr ADMAPI (*MultibyteToUnicode)(const char* inMBCSText, ADMUInt32 inSourceLength,
				ADMUnicode* outUnicodeText, ADMUInt32* outUnicodeSize, ADMUInt32 inADMScriptCode);

	/** ... */
	ADMErr ADMAPI (*UnicodeToMultibyte)(const ADMUnicode* inUnicodeText,
				ADMUInt32 inSourceLength, char* outMBCSText,
				ADMUInt32* outMBCSSize, ADMUInt32 inADMScriptCode);

	// script determination
	
	/** ... */
	ADMErr ADMAPI (*GetPreferredScript)(const ADMUnicode* inUnicodeText,
				ADMUInt32 inDefaultScript, ADMUInt32* outMBCSScript);

	/** ... */
	ADMErr ADMAPI (*GetFontForScript)(ADMUInt32 inADMScriptCode,
				ADMFont inFontSelector, ADMPlatformFontRef* outFont);

	// allowing the host to sub-class input windows to enable keyboard
	// layout switching

	/** ... */
	ADMErr ADMAPI (*SubclassItemForUnicodeInput)(ADMWindowRef inWindow);
	/** ... */
	ADMErr ADMAPI (*GetCurrentUnicodeInputScript)(ADMWindowRef inWindow, ADMUInt32 *outADMScriptCode);
	/** ... */
	ADMErr ADMAPI (*SetCurrentInputScriptFromUnicode)(ADMWindowRef inWindow, const ADMUnicode* inUnicodeText);
	/** ... */
	ADMErr ADMAPI (*UnsubclassItemForUnicodeInput)(ADMWindowRef inWindow);
}
ADMHostInitUnicodeSuite1;


// -----------------------------------------------------------------------------

#pragma ADM_PRAGMA_IMPORT_END
#pragma ADM_PRAGMA_ALIGN_END

#ifdef __cplusplus
}
#endif

// -----------------------------------------------------------------------------

#endif	// __ADMUnicode__
