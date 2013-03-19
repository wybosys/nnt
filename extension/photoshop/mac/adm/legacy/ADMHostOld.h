/***********************************************************************/
/*                                                                     */
/* ADMHostOld.h                                                        */
/* Old versions of ADM Host Suite                                      */
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

#ifndef __ADMHostOld__
#define __ADMHostOld__

#ifndef __ADMTypes__
#include "ADMTypes.h"
#endif

#ifndef __SPMessageData__
#include "SPMData.h"
#endif

#ifndef __SPAccess__
#include "SPAccess.h"
#endif

#ifndef __ADMHost__
#include "ADMHost.h"
#endif


// -----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

#pragma ADM_PRAGMA_ALIGN_BEGIN
#pragma ADM_PRAGMA_IMPORT_BEGIN


// =============================================================================
//		* ADM Host Suite, version 1
// =============================================================================

#define kADMHostSuiteVersion1 1

// -----------------------------------------------------------------------------

typedef struct ADMHostSuite1
{

	// AGM calibration

	void ADMAPI (*SetAGMCalibrationProc)(ADMAGMCalibrationProc inCalibrationProc);
	ADMAGMCalibrationProc ADMAPI (*GetAGMCalibrationProc)();

	// mouse information accessors

	ADMBoolean ADMAPI (*PointerInUse)();

	// palette layout bounds modifiers

	void ADMAPI (*SetModifyPaletteLayoutBoundsProc)(ModifyPaletteLayoutBoundsProc inModifyBoundsProc);
	ModifyPaletteLayoutBoundsProc ADMAPI (*GetModifyPaletteLayoutBoundsProc)();

}
ADMHostSuite1;


// =============================================================================
//		* ADM Host Suite, version 2
// =============================================================================

#define kADMHostSuiteVersion2 2
#define kADMHostSuiteVersion kADMHostSuiteVersion2

// -----------------------------------------------------------------------------

typedef struct ADMHostSuite2
{

	// AGM calibration

	void ADMAPI (*SetAGMCalibrationProc)(ADMAGMCalibrationProc inCalibrationProc);
	ADMAGMCalibrationProc ADMAPI (*GetAGMCalibrationProc)();
	
	// mouse information accessors
	
	ADMBoolean ADMAPI (*PointerInUse)();
	
	// palette layout bounds modifiers
	
	void ADMAPI (*SetModifyPaletteLayoutBoundsProc)(ModifyPaletteLayoutBoundsProc inModifyBoundsProc);
	ModifyPaletteLayoutBoundsProc ADMAPI (*GetModifyPaletteLayoutBoundsProc)();

	// host information accessors

	void ADMAPI (*SetADMHostAppContextProcs)(const ADMHostAppContextProcs* inAppContextProcs);
	void ADMAPI (*GetADMHostAppContextProcs)(ADMHostAppContextProcs* outAppContextProcs);
	
	void ADMAPI (*SetADMHostAppName)(const char* inHostName);
	void ADMAPI (*GetADMHostAppName)(char* outHostName, ADMInt16 inMaxLength);

	void ADMAPI (*SetADMResourceAccessProcs)(const ADMResourceAccessProcs* inResProcs);
	void ADMAPI (*GetADMResourceAccessProcs)(ADMResourceAccessProcs* outResProcs);

	// ADM build version

	ADMUInt32 ADMAPI (*GetADMVersion)();
	
	// text behaviors
	
	void ADMAPI (*SetADMDefaultTextInfo)(const ADMDefaultTextInfo* inDefaultTextInfo);
	void ADMAPI (*GetADMDefaultTextInfo)(ADMDefaultTextInfo* outDefaultTextInfo);

}
ADMHostSuite2;	

typedef ADMHostSuite2 ADMHostSuite;


// =============================================================================
//		* ADM Host Suite, version 3
// =============================================================================

#define kADMHostSuiteVersion3 3

// -----------------------------------------------------------------------------

typedef struct ADMHostSuite3
{

	// *** This suite is FROZEN.
	// *** It shipped with Photoshop 5.5 and ImageReady 2.0.

	// AGM calibration

	void ADMAPI (*SetAGMCalibrationProc)(ADMAGMCalibrationProc inCalibrationProc);
	ADMAGMCalibrationProc ADMAPI (*GetAGMCalibrationProc)();
	
	// mouse information accessors
	
	ADMBoolean ADMAPI (*PointerInUse)();
	
	// palette layout bounds modifiers
	
	void ADMAPI (*SetModifyPaletteLayoutBoundsProc)(ModifyPaletteLayoutBoundsProc inModifyBoundsProc);
	ModifyPaletteLayoutBoundsProc ADMAPI (*GetModifyPaletteLayoutBoundsProc)();

	// host information accessors

	void ADMAPI (*SetADMHostAppContextProcs)(const ADMHostAppContextProcs* inAppContextProcs);
	void ADMAPI (*GetADMHostAppContextProcs)(ADMHostAppContextProcs* outAppContextProcs);
	
	void ADMAPI (*SetADMHostAppName)(const char* inHostName);
	void ADMAPI (*GetADMHostAppName)(char* outHostName, ADMInt16 inMaxLength);

	void ADMAPI (*SetADMResourceAccessProcs)(const ADMResourceAccessProcs* inResProcs);
	void ADMAPI (*GetADMResourceAccessProcs)(ADMResourceAccessProcs* outResProcs);

	// ADM build version

	ADMUInt32 ADMAPI (*GetADMVersion)();
	
	// text behaviors
	
	void ADMAPI (*SetADMDefaultTextInfo)(const ADMDefaultTextInfo* inDefaultTextInfo);
	void ADMAPI (*GetADMDefaultTextInfo)(ADMDefaultTextInfo* outDefaultTextInfo);

	void ADMAPI (*SetADMLanguageCode)(const char* inLanguageCode);
	void ADMAPI (*GetADMLanguageCode)(char* outLanguageCode);
										// max length is kADMMaxLanguageCode

	// modal dialog mode (currently unimplemented)

	void ADMAPI (*SetADMModalMode)(ADMBoolean inModalMode);
	ADMBoolean ADMAPI (*GetADMModalMode)();

}
ADMHostSuite3;	


// =============================================================================
//		* ADM Host Suite, version 4
// =============================================================================

#define kADMHostSuiteVersion4 4

// -----------------------------------------------------------------------------

typedef struct ADMHostSuite4
{
	// *** This suite is FROZEN.
	// *** It shipped with Illustrator 9.0.

	// AGM calibration

	void ADMAPI (*SetAGMCalibrationProc)(ADMAGMCalibrationProc inCalibrationProc);
	ADMAGMCalibrationProc ADMAPI (*GetAGMCalibrationProc)();
	
	// mouse information accessors
	
	ADMBoolean ADMAPI (*PointerInUse)();
	
	// palette layout bounds modifiers
	
	void ADMAPI (*SetModifyPaletteLayoutBoundsProc)(ModifyPaletteLayoutBoundsProc inModifyBoundsProc);
	ModifyPaletteLayoutBoundsProc ADMAPI (*GetModifyPaletteLayoutBoundsProc)();

	// host information accessors

	void ADMAPI (*SetADMHostAppContextProcs)(const ADMHostAppContextProcs* inAppContextProcs);
	void ADMAPI (*GetADMHostAppContextProcs)(ADMHostAppContextProcs* outAppContextProcs);
	
	void ADMAPI (*SetADMHostAppName)(const char* inHostName);
	void ADMAPI (*GetADMHostAppName)(char* outHostName, ADMInt16 inMaxLength);

	void ADMAPI (*SetADMResourceAccessProcs)(const ADMResourceAccessProcs* inResProcs);
	void ADMAPI (*GetADMResourceAccessProcs)(ADMResourceAccessProcs* outResProcs);

	// ADM build version

	ADMUInt32 ADMAPI (*GetADMVersion)();
	
	// text behaviors
	
	void ADMAPI (*SetADMDefaultTextInfo)(const ADMDefaultTextInfo* inDefaultTextInfo);
	void ADMAPI (*GetADMDefaultTextInfo)(ADMDefaultTextInfo* outDefaultTextInfo);

	void ADMAPI (*SetADMLanguageCode)(const char* inLanguageCode);
	void ADMAPI (*GetADMLanguageCode)(char* outLanguageCode);
										// max length is kADMMaxLanguageCode

	// modal dialog mode (currently unimplemented)

	void ADMAPI (*SetADMModalMode)(ADMBoolean inModalMode);
	ADMBoolean ADMAPI (*GetADMModalMode)();

	// ADM-handled keys

	ADMBoolean ADMAPI (*IsADMHandledKey)(const char inKeyCode);

}
ADMHostSuite4;	


// =============================================================================
//		* ADM Mac Host Suite, version 1
// =============================================================================

#ifdef MAC_ENV

#define kADMMacHostSuiteVersion1 1

// -----------------------------------------------------------------------------

typedef struct ADMMacHostSuite1 
{

	// event hand-off to ADM

	ADMBoolean ADMAPI (*HandleADMEvent)(struct EventRecord* inEvent);
	
	// modal dialog event callback

	void ADMAPI (*SetModalEventProc)(ADMModalEventProc inModalEventProc);
	ADMModalEventProc ADMAPI (*GetModalEventProc)();
	
	// window activation

	void ADMAPI (*ActivateWindows)(ADMBoolean inActivate);

}
ADMMacHostSuite1;

#endif


// =============================================================================
//		* ADM Win Host Suite, version 1
// =============================================================================

#ifdef WIN_ENV

#define kADMWinHostSuiteVersion1 1

// -----------------------------------------------------------------------------

typedef struct ADMWinHostSuite1 
{

	ADMBoolean ADMAPI (*HandleADMMessage)(ADMWindowRef inFrameWnd, ADMUInt16 inMessage,
				ADMUInt16 inWParam, ADMInt32 inLParam);

	ADMWindowRef ADMAPI (*GetCurrentOwnerWindow)();

	ADMBoolean ADMAPI (*IsADMMessage)(const struct tagMSG* inMessage);

}
ADMWinHostSuite1;

#endif	// WIN_ENV


// =============================================================================
//		* ADM Win Host Suite, version 2
// =============================================================================

#ifdef WIN_ENV

#define kADMWinHostSuiteVersion2 2
#define kADMWinHostSuiteVersion kADMWinHostSuiteVersion2

// -----------------------------------------------------------------------------

typedef struct ADMWinHostSuite2
{

	ADMBoolean ADMAPI (*HandleADMMessage)(ADMWindowRef inFrameWnd, ADMUInt16 inMessage,
				ADMUInt16 inWParam, ADMInt32 inLParam);

	ADMWindowRef ADMAPI (*GetCurrentOwnerWindow)();

	ADMBoolean ADMAPI (*IsADMMessage)(const struct tagMSG* inMessage);

	ADMWindowRef ADMAPI (*GetPlatformAppWindow)();
	void ADMAPI (*SetPlatformAppWindow) (ADMWindowRef inAppWindow);

	ADMModalMessageProc ADMAPI (*GetModalMessageProc)();							
	void ADMAPI (*SetModalMessageProc)(ADMModalMessageProc inModalMessageProc);	

}
ADMWinHostSuite2;	

typedef ADMWinHostSuite2 ADMWinHostSuite;

#endif	// WIN_ENV

// =============================================================================
//		* ADM Win Host Suite, version 3
// =============================================================================

#ifdef WIN_ENV

#define kADMWinHostSuiteVersion3 3

// -----------------------------------------------------------------------------

typedef struct ADMWinHostSuite3
{

	// *** This suite is FROZEN.
	// *** It shipped with Illustrator 9.0.

	ADMBoolean ADMAPI (*HandleADMMessage)(ADMWindowRef inFrameWnd, ADMUInt16 inMessage,
				ADMUInt16 inWParam, ADMInt32 inLParam);

	ADMWindowRef ADMAPI (*GetCurrentOwnerWindow)();

	ADMBoolean ADMAPI (*IsADMMessage)(const struct tagMSG* inMessage);

	ADMWindowRef ADMAPI (*GetPlatformAppWindow)();
	void ADMAPI (*SetPlatformAppWindow)(ADMWindowRef inAppWindow);

	ADMModalMessageProc ADMAPI (*GetModalMessageProc)();							
	void ADMAPI (*SetModalMessageProc)(ADMModalMessageProc inModalMessageProc);

	ADMTextFocusChangedProc ADMAPI (*GetTextFocusChangedProc)();						
	void ADMAPI (*SetTextFocusChangedProc)(ADMTextFocusChangedProc inFocusChangedProc);

}
ADMWinHostSuite3;

#endif	// WIN_ENV

// -----------------------------------------------------------------------------


#pragma ADM_PRAGMA_IMPORT_END
#pragma ADM_PRAGMA_ALIGN_END

#ifdef __cplusplus
}
#endif

#endif
