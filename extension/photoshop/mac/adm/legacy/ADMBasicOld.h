/***********************************************************************/
/*                                                                     */
/* ADMBasicOld.h                                                       */
/* Old versions of ADM Basic Suite                                     */
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

#ifndef __ADMBasicOld__
#define __ADMBasicOld__

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
//		* ADM Basic Suite, version 2
// =============================================================================

#define kADMBasicSuiteVersion2 2
#define kADMBasicSuiteVersion kADMBasicSuiteVersion2
#define kADMBasicVersion kADMBasicSuiteVersion

// -----------------------------------------------------------------------------

typedef struct ADMBasicSuite2
{

	ADMErr ADMAPI (*GetIndexString)(SPPluginRef inPluginRef, ADMInt32 inStringID,
				ADMInt32 inStringIndex, char* outString, ADMInt32 inMaxLength);

	void ADMAPI (*Beep)();
	
	void ADMAPI (*ErrorAlert)(const char* inErrorString);
	void ADMAPI (*MessageAlert)(const char* inMessageString);
	ADMAnswer ADMAPI (*QuestionAlert)(const char* inQuestionString);

	ADMBoolean ADMAPI (*GetScreenDimensions)(const ADMPoint* inPoint, ADMRect* outDimensions);

	void ADMAPI (*EnableToolTips)(ADMBoolean inEnable);
	ADMBoolean ADMAPI (*AreToolTipsEnabled)();
	
	void ADMAPI (*ValueToString)(float inValue, char* outText, ADMInt32 inMaxLength,
				ADMUnits inUnits, ADMInt32 inPrecision, ADMBoolean inAlwaysAppendUnits);

	ADMBoolean ADMAPI (*StringToValue)(const char* inText, float* outValue, ADMUnits inUnits);

	ADMBoolean ADMAPI (*StandardGetFileDialog)(const char* inMessage,
				const ADMPlatformFileTypesSpecification* inFilter,
				const SPPlatformFileSpecification* inStartingDir, const char* inStartingFile,
				SPPlatformFileSpecification* outResult);

	ADMBoolean ADMAPI (*StandardGetDirectoryDialog)(const char* inMessage,
				const SPPlatformFileSpecification* inStartingDir,
				SPPlatformFileSpecification* outResult);

	ADMBoolean ADMAPI (*StandardPutFileDialog)(const char* inMessage,
				const SPPlatformFileSpecification* inStartingDir, const char* inStartingFile,
				SPPlatformFileSpecification* outResult);

	ADMBoolean ADMAPI (*ChooseColor)(ADMPoint inWhere, const ADMRGBColor* inColor,
				ADMRGBColor* outColor);	

	void ADMAPI (*SetAppUnits)(ADMUnits inAppUnits, ADMUnits inActualUnits);
	ADMUnits ADMAPI (*GetAppUnits)(ADMUnits inAppUnits);
	void ADMAPI (*SetNumbersArePoints)(ADMBoolean inPoints);
	ADMBoolean ADMAPI (*GetNumbersArePoints)();

	void ADMAPI (*SetDefaultIncrements)(ADMUnits inUnits, float inSmallIncrement,
				float inLargeIncrement);

	void ADMAPI (*GetDefaultIncrements)(ADMUnits inUnits, float* outSmallIncrement,
				float* outLargeIncrement);

	void ADMAPI (*AboutBox)(SPPluginRef inPluginRef, const char* inText1, const char* inText2);

	ADMBoolean ADMAPI (*AreToolTipsSticky)(ADMDialogRef inDialog);
	void ADMAPI (*GetToolTipDelays)(ADMInt32* outPopupDelay, ADMInt32* outPopdownDelay);

	ADMBoolean ADMAPI (*GetWorkspaceBounds)(ADMRect* outDimensions);
				// main screen less system menus, task bars, etc

	ADMBoolean ADMAPI (*GetPaletteLayoutBounds)(ADMRect* outDimensions);
				// inset of standard application window
	
}
ADMBasicSuite2;

typedef ADMBasicSuite2 ADMBasicSuite;


// =============================================================================
//		* ADM Basic Suite, version 3
// =============================================================================

#define kADMBasicSuiteVersion3 3

// -----------------------------------------------------------------------------

typedef struct ADMBasicSuite3
{

	ADMErr ADMAPI (*GetIndexString)(SPPluginRef inPluginRef, ADMInt32 inStringID,
				ADMInt32 inStringIndex, char* outString, ADMInt32 inMaxLength);

	void ADMAPI (*Beep)();
	
	void ADMAPI (*ErrorAlert)(const char* inErrorString);
	void ADMAPI (*MessageAlert)(const char* inMessageString);
	ADMAnswer ADMAPI (*QuestionAlert)(const char* inQuestionString);

	ADMBoolean ADMAPI (*GetScreenDimensions)(const ADMPoint* inPoint, ADMRect* outDimensions);

	void ADMAPI (*EnableToolTips)(ADMBoolean inEnable);
	ADMBoolean ADMAPI (*AreToolTipsEnabled)();
	
	void ADMAPI (*ValueToString)(float inValue, char* outText, ADMInt32 inMaxLength,
				ADMUnits inUnits, ADMInt32 inPrecision, ADMBoolean inAlwaysAppendUnits);

	ADMBoolean ADMAPI (*StringToValue)(const char* inText, float* outValue, ADMUnits inUnits);

	ADMBoolean ADMAPI (*StandardGetFileDialog)(const char* inMessage,
				const ADMPlatformFileTypesSpecification3* inFilter,
				const SPPlatformFileSpecification* inStartingDir, const char* inStartingFile,
				SPPlatformFileSpecification* outResult);

	ADMBoolean ADMAPI (*StandardGetDirectoryDialog)(const char* inMessage,
				const SPPlatformFileSpecification* inStartingDir,
				SPPlatformFileSpecification* outResult);

	ADMBoolean ADMAPI (*StandardPutFileDialog)(const char* inMessage,
				const SPPlatformFileSpecification* inStartingDir, const char* inStartingFile,
				SPPlatformFileSpecification* outResult);

	ADMBoolean ADMAPI (*ChooseColor)(ADMPoint inWhere, const ADMRGBColor* inColor,
				ADMRGBColor* outColor);	

	void ADMAPI (*SetAppUnits)(ADMUnits inAppUnits, ADMUnits inActualUnits);
	ADMUnits ADMAPI (*GetAppUnits)(ADMUnits inAppUnits);
	void ADMAPI (*SetNumbersArePoints)(ADMBoolean inPoints);
	ADMBoolean ADMAPI (*GetNumbersArePoints)();

	void ADMAPI (*SetDefaultIncrements)(ADMUnits inUnits, float inSmallIncrement,
				float inLargeIncrement);

	void ADMAPI (*GetDefaultIncrements)(ADMUnits inUnits, float* outSmallIncrement,
				float* outLargeIncrement);

	void ADMAPI (*AboutBox)(SPPluginRef inPluginRef, const char* inText1, const char* inText2);

	ADMBoolean ADMAPI (*AreToolTipsSticky)(ADMDialogRef inDialog);
	void ADMAPI (*GetToolTipDelays)(ADMInt32* outPopupDelay, ADMInt32* outPopdownDelay);

	ADMBoolean ADMAPI (*GetWorkspaceBounds)(ADMRect* outDimensions);
				// main screen less system menus, task bars, etc

	ADMBoolean ADMAPI (*GetPaletteLayoutBounds)(ADMRect* outDimensions);
				// inset of standard application window

	void ADMAPI (*SetPlatformCursor)(SPPluginRef inPluginRef, ADMInt32 inCursorID);
	void ADMAPI (*PluginAboutBox)(const char* inTitle, const char* inText);
	
	void ADMAPI (*SetAlertButtonText)(const char* inLeftChoice, const char* inMiddleChoice,
				const char* inRightChoice);	
	
	void ADMAPI (*ShowToolTip)(const ADMPoint* inWhere, const char* inTipText);
	void ADMAPI (*HideToolTip)();
	
}
ADMBasicSuite3;


// =============================================================================
//		* ADM Basic Suite, version 4
// =============================================================================

#define kADMBasicSuiteVersion4 4

// -----------------------------------------------------------------------------

typedef struct ADMBasicSuite4
{

	ADMErr ADMAPI (*GetIndexString)(SPPluginRef inPluginRef, ADMInt32 inStringID,
				ADMInt32 inStringIndex, char* outString, ADMInt32 inMaxLength);

	void ADMAPI (*Beep)();
	
	void ADMAPI (*ErrorAlert)(const char* inErrorString);
	void ADMAPI (*MessageAlert)(const char* inMessageString);
	ADMAnswer ADMAPI (*QuestionAlert)(const char* inQuestionString);

	ADMBoolean ADMAPI (*GetScreenDimensions)(const ADMPoint* inPoint, ADMRect* outDimensions);

	void ADMAPI (*EnableToolTips)(ADMBoolean inEnable);
	ADMBoolean ADMAPI (*AreToolTipsEnabled)();
	
	void ADMAPI (*ValueToString)(float inValue, char* outText, ADMInt32 inMaxLength,
				ADMUnits inUnits, ADMInt32 inPrecision, ADMBoolean inAlwaysAppendUnits);

	ADMBoolean ADMAPI (*StringToValue)(const char* inText, float* outValue, ADMUnits inUnits);

	ADMBoolean ADMAPI (*StandardGetFileDialog)(const char* inMessage,
				const ADMPlatformFileTypesSpecification3* inFilter,
				const SPPlatformFileSpecification* inStartingDir, const char* inStartingFile,
				SPPlatformFileSpecification* outResult);

	ADMBoolean ADMAPI (*StandardGetDirectoryDialog)(const char* inMessage,
				const SPPlatformFileSpecification* inStartingDir,
				SPPlatformFileSpecification* outResult);

	ADMBoolean ADMAPI (*StandardPutFileDialog)(const char* inMessage,
				const SPPlatformFileSpecification* inStartingDir, const char* inStartingFile,
				SPPlatformFileSpecification* outResult);

	ADMBoolean ADMAPI (*ChooseColor)(ADMPoint inWhere, const ADMRGBColor* inColor,
				ADMRGBColor* outColor);	

	void ADMAPI (*SetAppUnits)(ADMUnits inAppUnits, ADMUnits inActualUnits);
	ADMUnits ADMAPI (*GetAppUnits)(ADMUnits inAppUnits);
	void ADMAPI (*SetNumbersArePoints)(ADMBoolean inPoints);
	ADMBoolean ADMAPI (*GetNumbersArePoints)();

	void ADMAPI (*SetDefaultIncrements)(ADMUnits inUnits, float inSmallIncrement,
				float inLargeIncrement);

	void ADMAPI (*GetDefaultIncrements)(ADMUnits inUnits, float* outSmallIncrement,
				float* outLargeIncrement);

	void ADMAPI (*AboutBox)(SPPluginRef inPluginRef, const char* inText1, const char* inText2);

	ADMBoolean ADMAPI (*AreToolTipsSticky)(ADMDialogRef inDialog);
	void ADMAPI (*GetToolTipDelays)(ADMInt32* outPopupDelay, ADMInt32* outPopdownDelay);

	ADMBoolean ADMAPI (*GetWorkspaceBounds)(ADMRect* outDimensions);
				// main screen less system menus, task bars, etc

	ADMBoolean ADMAPI (*GetPaletteLayoutBounds)(ADMRect* outDimensions);
				// inset of standard application window

	void ADMAPI (*SetPlatformCursor)(SPPluginRef inPluginRef, ADMInt32 inCursorID);
	void ADMAPI (*PluginAboutBox)(const char* inTitle, const char* inText);
	
	void ADMAPI (*SetAlertButtonText)(const char* inLeftChoice, const char* inMiddleChoice,
				const char* inRightChoice);
	
	void ADMAPI (*ShowToolTip)(const ADMPoint* inWhere, const char* inTipText);
	void ADMAPI (*HideToolTip)();
	
	ADMErr ADMAPI (*CreateMenu)(ADMListRef* outMenu);
	ADMErr ADMAPI (*DisplayMenu)(ADMListRef inMenu, ADMDialogRef inDialog, ADMPoint inDialogPoint);
	ADMErr ADMAPI (*DestroyMenu)(ADMListRef inMenu);

	ADMBoolean ADMAPI (*GetLastADMError)(ADMInt32* outErrorCode, ADMInt32* outErrorData);
	ADMBoolean ADMAPI (*ADMColorToRGBColor)(ADMColor inADMColor, ADMRGBColor* outRGBColor);

	ADMAnswer ADMAPI (*YesNoAlert)(const char* inQuestionString);

}
ADMBasicSuite4;

// =============================================================================
//		* ADM Basic Suite, version 5
// =============================================================================

#define kADMBasicSuiteVersion5 5

// -----------------------------------------------------------------------------

typedef struct ADMBasicSuite5
{

	// *** Shipped with Photoshop 5.5 and ImageReady 2.0.

	ADMErr ADMAPI (*GetIndexString)(SPPluginRef inPluginRef, ADMInt32 inStringID,
				ADMInt32 inStringIndex, char* outString, ADMInt32 inMaxLen);

	void ADMAPI (*Beep)();
	void ADMAPI (*ErrorAlert)(const char* inErrorString);
	void ADMAPI (*MessageAlert)(const char* inMessageString);
	ADMAnswer ADMAPI (*QuestionAlert)(const char* inQuestionString);

	ADMBoolean ADMAPI (*GetScreenDimensions)(const ADMPoint* inPoint, ADMRect* outDimensions);

	void ADMAPI (*EnableToolTips)(ADMBoolean inEnable);
	ADMBoolean ADMAPI (*AreToolTipsEnabled)();

	void ADMAPI (*ValueToString)(float inValue, char* outText, ADMInt32 inMaxLen,
				ADMUnits inUnits, ADMInt32 inPrecision, ADMBoolean inAlwaysAppendUnits);

	ADMBoolean ADMAPI (*StringToValue)(const char* inText, float* outValue, ADMUnits inUnits);

	ADMBoolean ADMAPI (*StandardGetFileDialog)(const char* inMessage,
				const ADMPlatformFileTypesSpecification3* inFilter,
				const SPPlatformFileSpecification* inStartingDir,
				const char* inStartingFile, SPPlatformFileSpecification* outResult);

	ADMBoolean ADMAPI (*StandardGetDirectoryDialog)(const char* inMessage,
				const SPPlatformFileSpecification* inStartingDir,
				SPPlatformFileSpecification* outResult);

	ADMBoolean ADMAPI (*StandardPutFileDialog)(const char* inMessage,
				const ADMPlatformFileTypesSpecification3* inFilter,
				const SPPlatformFileSpecification* inStartingDir,
				const char* inStartingFile, SPPlatformFileSpecification* outResult);

	ADMBoolean ADMAPI (*ChooseColor)(ADMPoint inWhere, const ADMRGBColor* inColor,
				ADMRGBColor* outColor);

	void ADMAPI (*SetAppUnits)(ADMUnits inAppUnits, ADMUnits inActualUnits);
	ADMUnits ADMAPI (*GetAppUnits)(ADMUnits inAppUnits);
	
	void ADMAPI (*SetNumbersArePoints)(ADMBoolean inPoints);
	ADMBoolean ADMAPI (*GetNumbersArePoints)();

	void ADMAPI (*SetDefaultIncrements)(ADMUnits inUnits, float inSmallIncrement,
				float inLargeIncrement);

	void ADMAPI (*GetDefaultIncrements)(ADMUnits inUnits, float* outSmallIncrement,
				float* outLargeIncrement);

	void ADMAPI (*AboutBox)(SPPluginRef inPlugin, const char* inText1, const char* inText2);

	ADMBoolean ADMAPI (*AreToolTipsSticky)(ADMDialogRef inDialog);
	void ADMAPI (*GetToolTipDelays)(ADMInt32* outPopupDelay, ADMInt32* outPopdownDelay);

	ADMBoolean ADMAPI (*GetWorkspaceBounds)(ADMRect* outDimensions);
				// main screen less system menus, task bars, etc

	ADMBoolean ADMAPI (*GetPaletteLayoutBounds)(ADMRect* outDimensions);
				// inset of standard application window

	void ADMAPI (*SetPlatformCursor)(SPPluginRef inPluginRef, ADMInt32 inCursorID);

	void ADMAPI (*PluginAboutBox)(const char* inTitle, const char* inText);
	
	void ADMAPI (*SetAlertButtonText)(const char* inLeftChoice, const char* inMiddleChoice,
				const char* inRightChoice);

	void ADMAPI (*ShowToolTip)(const ADMPoint* inWhere, const char* inTip);
	void ADMAPI (*HideToolTip)();
	
	ADMErr ADMAPI (*CreateMenu)(ADMListRef* outMenu);
	ADMErr ADMAPI (*DisplayMenu)(ADMListRef inMenu, ADMDialogRef inDialog, ADMPoint inDialogPoint);
	ADMErr ADMAPI (*DestroyMenu)(ADMListRef inMenu);

	ADMBoolean ADMAPI (*GetLastADMError)(ADMInt32* outError, ADMInt32* outErrorData);
	ADMBoolean ADMAPI (*ADMColorToRGBColor)(ADMColor inADMColor, ADMRGBColor* outRGBColor);

	ADMAnswer ADMAPI (*YesNoAlert)(const char* inQuestionString);

}
ADMBasicSuite5;

// =============================================================================
//		* ADM Basic Suite, version 6
// =============================================================================

#define kADMBasicSuiteVersion6 6

// -----------------------------------------------------------------------------

typedef struct ADMBasicSuite6
{

	// *** Shipped with Illustrator 9.0.

	ADMErr ADMAPI (*GetIndexString)(SPPluginRef inPluginRef, ADMInt32 inStringID,
				ADMInt32 inStringIndex, char* outString, ADMInt32 inMaxLen);

	void ADMAPI (*Beep)();
	void ADMAPI (*ErrorAlert)(const char* inErrorString);
	void ADMAPI (*MessageAlert)(const char* inMessageString);
	ADMAnswer ADMAPI (*QuestionAlert)(const char* inQuestionString);

	ADMBoolean ADMAPI (*GetScreenDimensions)(const ADMPoint* inPoint, ADMRect* outDimensions);

	void ADMAPI (*EnableToolTips)(ADMBoolean inEnable);
	ADMBoolean ADMAPI (*AreToolTipsEnabled)();

	void ADMAPI (*ValueToString)(float inValue, char* outText, ADMInt32 inMaxLen,
				ADMUnits inUnits, ADMInt32 inPrecision, ADMBoolean inAlwaysAppendUnits);

	ADMBoolean ADMAPI (*StringToValue)(const char* inText, float* outValue, ADMUnits inUnits);

	ADMBoolean ADMAPI (*StandardGetFileDialog)(const char* inMessage,
				const ADMPlatformFileTypesSpecification3* inFilter,
				const SPPlatformFileSpecification* inStartingDir,
				const char* inStartingFile, SPPlatformFileSpecification* outResult);

	ADMBoolean ADMAPI (*StandardGetDirectoryDialog)(const char* inMessage,
				const SPPlatformFileSpecification* inStartingDir,
				SPPlatformFileSpecification* outResult);

	ADMBoolean ADMAPI (*StandardPutFileDialog)(const char* inMessage,
				const ADMPlatformFileTypesSpecification3* inFilter,
				const SPPlatformFileSpecification* inStartingDir,
				const char* inStartingFile, SPPlatformFileSpecification* outResult);

	ADMBoolean ADMAPI (*ChooseColor)(ADMPoint inWhere, const ADMRGBColor* inColor,
				ADMRGBColor* outColor);

	void ADMAPI (*SetAppUnits)(ADMUnits inAppUnits, ADMUnits inActualUnits);
	ADMUnits ADMAPI (*GetAppUnits)(ADMUnits inAppUnits);
	
	void ADMAPI (*SetNumbersArePoints)(ADMBoolean inPoints);
	ADMBoolean ADMAPI (*GetNumbersArePoints)();

	void ADMAPI (*SetDefaultIncrements)(ADMUnits inUnits, float inSmallIncrement,
				float inLargeIncrement);

	void ADMAPI (*GetDefaultIncrements)(ADMUnits inUnits, float* outSmallIncrement,
				float* outLargeIncrement);

	void ADMAPI (*AboutBox)(SPPluginRef inPlugin, const char* inText1, const char* inText2);

	ADMBoolean ADMAPI (*AreToolTipsSticky)(ADMDialogRef inDialog);
	void ADMAPI (*GetToolTipDelays)(ADMInt32* outPopupDelay, ADMInt32* outPopdownDelay);

	ADMBoolean ADMAPI (*GetWorkspaceBounds)(ADMRect* outDimensions);
				// main screen less system menus, task bars, etc

	ADMBoolean ADMAPI (*GetPaletteLayoutBounds)(ADMRect* outDimensions);
				// inset of standard application window

	void ADMAPI (*SetPlatformCursor)(SPPluginRef inPluginRef, ADMInt32 inCursorID);

	void ADMAPI (*PluginAboutBox)(const char* inTitle, const char* inText);
	
	void ADMAPI (*SetAlertButtonText)(const char* inLeftChoice, const char* inMiddleChoice,
				const char* inRightChoice);

	void ADMAPI (*ShowToolTip)(const ADMPoint* inWhere, const char* inTip);
	void ADMAPI (*HideToolTip)();
	
	ADMErr ADMAPI (*CreateMenu)(ADMListRef* outMenu);
	ADMErr ADMAPI (*DisplayMenu)(ADMListRef inMenu, ADMDialogRef inDialog, ADMPoint inDialogPoint);
	ADMErr ADMAPI (*DestroyMenu)(ADMListRef inMenu);

	ADMBoolean ADMAPI (*GetLastADMError)(ADMInt32* outError, ADMInt32* outErrorData);
	ADMBoolean ADMAPI (*ADMColorToRGBColor)(ADMColor inADMColor, ADMRGBColor* outRGBColor);

	ADMAnswer ADMAPI (*YesNoAlert)(const char* inQuestionString);

	void ADMAPI (*SetAppFPS)(float inFPS);
	float ADMAPI (*GetAppFPS)();

	void ADMAPI (*LightweightErrorAlert)(const char* inErrorString);

}
ADMBasicSuite6;

// =============================================================================
//		* ADM Basic Suite, version 7
// =============================================================================

#define kADMBasicSuiteVersion7 7

// -----------------------------------------------------------------------------

typedef struct ADMBasicSuite7
{

	// *** Shipped with Acrobat 5.0.

	ADMErr ADMAPI (*GetIndexString)(SPPluginRef inPluginRef, ADMInt32 inStringID,
				ADMInt32 inStringIndex, char* outString, ADMInt32 inMaxLen);

	ADMErr ADMAPI (*GetIndexStringW)(SPPluginRef inPluginRef, ADMInt32 inStringID,
				ADMInt32 inStringIndex, ADMUnicode* outString, ADMInt32 inMaxLen);

	void ADMAPI (*Beep)();

	void ADMAPI (*ErrorAlert)(const char* inErrorString);
	void ADMAPI (*ErrorAlertW)(const ADMUnicode* inErrorString);

	void ADMAPI (*MessageAlert)(const char* inMessageString);
	void ADMAPI (*MessageAlertW)(const ADMUnicode* inMessageString);

	ADMAnswer ADMAPI (*QuestionAlert)(const char* inQuestionString);
	ADMAnswer ADMAPI (*QuestionAlertW)(const ADMUnicode* inQuestionString);

	ADMAnswer ADMAPI (*YesNoAlert)(const char* inQuestionString);
	ADMAnswer ADMAPI (*YesNoAlertW)(const ADMUnicode* inQuestionString);

	ADMBoolean ADMAPI (*GetScreenDimensions)(const ADMPoint* inPoint, ADMRect* outDimensions);

	void ADMAPI (*EnableToolTips)(ADMBoolean inEnable);
	ADMBoolean ADMAPI (*AreToolTipsEnabled)();

	void ADMAPI (*ValueToString)(float inValue, char* outText, ADMInt32 inMaxLen,
				ADMUnits inUnits, ADMInt32 inPrecision, ADMBoolean inAlwaysAppendUnits);

	void ADMAPI (*ValueToStringW)(float inValue, ADMUnicode* outText, ADMInt32 inMaxLen,
				ADMUnits inUnits, ADMInt32 inPrecision, ADMBoolean inAlwaysAppendUnits);

	ADMBoolean ADMAPI (*StringToValue)(const char* inText, float* outValue, ADMUnits inUnits);
	ADMBoolean ADMAPI (*StringToValueW)(const ADMUnicode* inText, float* outValue, ADMUnits inUnits);

	ADMBoolean ADMAPI (*StandardGetFileDialog)(const char* inMessage,
				const ADMPlatformFileTypesSpecification3* inFilter,
				const SPPlatformFileSpecification* inStartingDir,
				const char* inStartingFile, SPPlatformFileSpecification* outResult);

	ADMBoolean ADMAPI (*StandardGetFileDialogW)(const ADMUnicode* inMessage,
				const ADMPlatformFileTypesSpecification3* inFilter,
				const SPPlatformFileSpecification* inStartingDir,
				const char* inStartingFile, SPPlatformFileSpecification* outResult);

	ADMBoolean ADMAPI (*StandardGetDirectoryDialog)(const char* inMessage,
				const SPPlatformFileSpecification* inStartingDir,
				SPPlatformFileSpecification* outResult);

	ADMBoolean ADMAPI (*StandardGetDirectoryDialogW)(const ADMUnicode* inMessage,
				const SPPlatformFileSpecification* inStartingDir,
				SPPlatformFileSpecification* outResult);

	ADMBoolean ADMAPI (*StandardPutFileDialog)(const char* inMessage,
				const ADMPlatformFileTypesSpecification3* inFilter,
				const SPPlatformFileSpecification* inStartingDir,
				const char* inStartingFile, SPPlatformFileSpecification* outResult);

	ADMBoolean ADMAPI (*StandardPutFileDialogW)(const ADMUnicode* inMessage,
				const ADMPlatformFileTypesSpecification3* inFilter,
				const SPPlatformFileSpecification* inStartingDir,
				const char* inStartingFile, SPPlatformFileSpecification* outResult);

	ADMBoolean ADMAPI (*ChooseColor)(ADMPoint inWhere, const ADMRGBColor* inColor,
				ADMRGBColor* outColor);

	void ADMAPI (*SetAppUnits)(ADMUnits inAppUnits, ADMUnits inActualUnits);
	ADMUnits ADMAPI (*GetAppUnits)(ADMUnits inAppUnits);
	
	void ADMAPI (*SetNumbersArePoints)(ADMBoolean inPoints);
	ADMBoolean ADMAPI (*GetNumbersArePoints)();

	void ADMAPI (*SetDefaultIncrements)(ADMUnits inUnits, float inSmallIncrement,
				float inLargeIncrement);

	void ADMAPI (*GetDefaultIncrements)(ADMUnits inUnits, float* outSmallIncrement,
				float* outLargeIncrement);

	void ADMAPI (*AboutBox)(SPPluginRef inPlugin, const char* inText1, const char* inText2);
	void ADMAPI (*AboutBoxW)(SPPluginRef inPlugin, const ADMUnicode* inText1, const ADMUnicode* inText2);

	ADMBoolean ADMAPI (*AreToolTipsSticky)(ADMDialogRef inDialog);
	void ADMAPI (*GetToolTipDelays)(ADMInt32* outPopupDelay, ADMInt32* outPopdownDelay);

	ADMBoolean ADMAPI (*GetWorkspaceBounds)(ADMRect* outDimensions);
				// main screen less system menus, task bars, etc

	ADMBoolean ADMAPI (*GetPaletteLayoutBounds)(ADMRect* outDimensions);
				// inset of standard application window

	void ADMAPI (*SetPlatformCursor)(SPPluginRef inPluginRef, ADMInt32 inCursorID);

	void ADMAPI (*PluginAboutBox)(const char* inTitle, const char* inText);
	void ADMAPI (*PluginAboutBoxW)(const ADMUnicode* inTitle, const ADMUnicode* inText);
	
	void ADMAPI (*SetAlertButtonText)(const char* inLeftChoice, const char* inMiddleChoice,
				const char* inRightChoice);

	void ADMAPI (*SetAlertButtonTextW)(const ADMUnicode* inLeftChoice, const ADMUnicode* inMiddleChoice,
				const ADMUnicode* inRightChoice);

	void ADMAPI (*ShowToolTip)(const ADMPoint* inWhere, const char* inTip);
	void ADMAPI (*ShowToolTipW)(const ADMPoint* inWhere, const ADMUnicode* inTip);
	void ADMAPI (*HideToolTip)();
	
	ADMErr ADMAPI (*CreateMenu)(ADMListRef* outMenu);
	ADMErr ADMAPI (*DisplayMenu)(ADMListRef inMenu, ADMDialogRef inDialog, ADMPoint inDialogPoint);
	ADMErr ADMAPI (*DestroyMenu)(ADMListRef inMenu);

	ADMBoolean ADMAPI (*GetLastADMError)(ADMInt32* outError, ADMInt32* outErrorData);
	ADMBoolean ADMAPI (*ADMColorToRGBColor)(ADMColor inADMColor, ADMRGBColor* outRGBColor);

	void ADMAPI (*SetAppFPS)(float inFPS);
	float ADMAPI (*GetAppFPS)();

	void ADMAPI (*LightweightErrorAlert)(const char* inErrorString);
	void ADMAPI (*LightweightErrorAlertW)(const ADMUnicode* inErrorString);
}
ADMBasicSuite7;

// -----------------------------------------------------------------------------

#pragma ADM_PRAGMA_IMPORT_END
#pragma ADM_PRAGMA_ALIGN_END

#ifdef __cplusplus
}
#endif

#endif
