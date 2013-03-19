/***********************************************************************/
/*                                                                     */
/* ADMHostInitOld.h                                                    */
/* Old versions of ADM Host Initialization Suite                       */
/*                                                                     */
/* ADOBE SYSTEMS INCORPORATED                                          */
/* Copyright 1997-2002 Adobe Systems Incorporated                      */
/* All Rights Reserved                                                 */
/*                                                                     */
/* NOTICE:  Adobe permits you to use, modify, and distribute this file */
/* in accordance with the terms of the Adobe license agreement         */
/* accompanying it. If you have received this file from a source other */
/* than Adobe, then your use, modification, or distribution of it      */
/* requires the prior written permission of Adobe.                     */
/*                                                                     */
/***********************************************************************/

#ifndef __ADMHostInitOld__
#define __ADMHostInitOld__

// -----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

#pragma ADM_PRAGMA_ALIGN_BEGIN
#pragma ADM_PRAGMA_IMPORT_BEGIN


// =============================================================================
//		* ADM Host Initialization Suite, version 1
// =============================================================================

#define kADMHostInitSuiteVersion1 1
#define kADMHostInitSuiteVersion kADMHostInitSuiteVersion1

// -----------------------------------------------------------------------------

typedef struct ADMHostInitSuite1
{

	// *** This suite is FROZEN.
	// *** It shipped with Photoshop 5.5 and ImageReady 2.0.

	void ADMAPI (*GetADMHostAppContextProcs)(ADMHostAppContextProcs* outAppContextProcs);
	void ADMAPI (*GetADMHostAppName)(char* outHostName, ADMInt16 inMaxLength);
	void ADMAPI (*GetADMResourceAccessProcs)(ADMResourceAccessProcs* outResProcs);
	void ADMAPI (*GetADMHostOptions)(ADMInt32* outOptions);
	void ADMAPI (*GetHostModifyPaletteLayoutBoundsProc)(ModifyPaletteLayoutBoundsProc* outProc);
	
	#ifdef MAC_ENV
		ADMWindowActivateProc ADMAPI (*GetWindowActivateProc)();
		void ADMAPI (*GetModalEventProc)(ADMModalEventProc* outModalEventProc);
	#endif

	#ifdef WIN_ENV
		ADMWindowRef ADMAPI (*GetAppWindow)();
		void ADMAPI (*GetUIResourceDirectory)(SPPlatformFileSpecification* outResDir);
					// default is 'System'
	#endif

	ADMBoolean ADMAPI (*GetIndexString)(ADMInt16 inStringID, ADMInt16 inStringIndex,
		char *outString, ADMInt16 inMaxLength);

}
ADMHostInitSuite1;

typedef ADMHostInitSuite1 ADMHostInitSuite;

// =============================================================================
//		* ADM Host Initialization Suite, version 2
// =============================================================================

#define kADMHostInitSuiteVersion2 2

// -----------------------------------------------------------------------------

typedef struct ADMHostInitSuite2
{
	// *** This suite is FROZEN.
	// *** It was used during development of Acrobat 5.0.

	void ADMAPI (*GetADMHostAppContextProcs)(ADMHostAppContextProcs* outAppContextProcs);
	void ADMAPI (*GetADMHostAppName)(char* outHostName, ADMInt16 inMaxLength);
	void ADMAPI (*GetADMResourceAccessProcs)(ADMResourceAccessProcs* outResProcs);
	void ADMAPI (*GetADMHostOptions)(ADMInt32* outOptions);
	void ADMAPI (*GetHostModifyPaletteLayoutBoundsProc)(ModifyPaletteLayoutBoundsProc* outProc);
	
	#ifdef MAC_ENV
		ADMWindowActivateProc ADMAPI (*GetWindowActivateProc)();
		void ADMAPI (*GetModalEventProc)(ADMModalEventProc* outModalEventProc);
	#endif

	#ifdef WIN_ENV
		ADMWindowRef ADMAPI (*GetAppWindow)();
		void ADMAPI (*GetUIResourceDirectory)(SPPlatformFileSpecification* outResDir);
					// default is 'System'
	#endif

	ADMBoolean ADMAPI (*GetIndexString)(ADMInt16 inStringID, ADMInt16 inStringIndex,
			char *outString, ADMInt16 outMaxLength);

}
ADMHostInitSuite2;

// -----------------------------------------------------------------------------

#pragma ADM_PRAGMA_IMPORT_END
#pragma ADM_PRAGMA_ALIGN_END

#ifdef __cplusplus
}
#endif

// -----------------------------------------------------------------------------

#endif	// __ADMHostInitOld__
