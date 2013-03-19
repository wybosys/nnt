/*******************************************************************************
*
* ADMTypes.h -- ADM standard interface types
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
* Started by Dave Lazarony, 10 Mar 1996
*
********************************************************************************/

/** @file ADMTypes.h ADM standard interface types */

#ifndef __ADMTypes__
#define __ADMTypes__

#ifndef __ADMStandardTypes__
#include "ADMStandardTypes.h"
#endif

#ifndef __SPPlugs__
#include "SPPlugs.h"
#endif


// -----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

#pragma ADM_PRAGMA_ALIGN_BEGIN
#pragma ADM_PRAGMA_IMPORT_BEGIN

// -----------------------------------------------------------------------------

#define kADMMaxTextLength 256

// -----------------------------------------------------------------------------
//	References to ADM types

/** ... */
typedef struct _Opaque_ADMDialog* ADMDialogRef;
/** ... */
typedef struct _Opaque_ADMDrawer* ADMDrawerRef;
/** ... */
typedef struct _Opaque_ADMItem* ADMItemRef;
/** ... */
typedef struct _Opaque_ADMList* ADMListRef;
/** ... */
typedef struct _Opaque_ADMHierarchyList* ADMHierarchyListRef;
/** ... */
typedef struct _Opaque_ADMEntry* ADMEntryRef;
/** ... */
typedef struct _Opaque_ADMListEntry* ADMListEntryRef;
/** ... */
typedef struct _Opaque_ADMNotifier* ADMNotifierRef;
/** ... */
typedef struct _Opaque_ADMTracker* ADMTrackerRef;
/** ... */
typedef struct _Opaque_ADMIcon* ADMIconRef;
/** ... */
typedef struct _Opaque_ADMImage* ADMImageRef;
/** ... */
typedef struct _Opaque_ADMRadioGroup* ADMRadioGroupRef;

/** ... */
typedef void* ADMUserData;
/** ... */
typedef unsigned long ADMTimerRef;
/** ... */
typedef unsigned long ADMActionMask;
/** ... */
typedef unsigned short ADMChar;

/** ... */
typedef void* ADMRsrcInfo;

/** ... */
typedef SPPluginRef ADMPluginRef;

#ifndef _t_AGMPortPtr
/** ... */
typedef struct _t_AGMPort* _t_AGMPortPtr;
#endif


// -----------------------------------------------------------------------------
//	Measurement units

/** ... */
typedef enum
{

		// If you add new units, do not insert them into the list. Instead, add
		// them to the end of the "normal" units, and adjust kADMMaxNormalUnits.
		// (The actual values of these constants are used in STR# 4300, the
		// unit input strings, to associate units with input strings.)

	/** ... */
	kADMNoUnits = 0,
	/** ... */
	kADMPointUnits = 1,
	/** ... */
	kADMInchUnits = 2,
	/** ... */
	kADMMillimeterUnits = 3,
	/** ... */
	kADMCentimeterUnits = 4,
	/** ... */
	kADMPicaUnits = 5,
	/** ... */
	kADMPercentUnits = 6,
	/** ... */
	kADMDegreeUnits = 7,
	/** ... */
	kADMQUnits = 8,
	/** ... */
	kADMBase16Units = 9,
	/** ... */
	kADMPixelUnits = 10,
	/** ... */
	kADMTimeUnits = 11,
	/** ... */
	kADMMinNormalUnits = kADMPointUnits,
	/** ... */
	kADMMaxNormalUnits = kADMTimeUnits,
	
	/** ... */
	kADMAppUnits1 = 101,
	/** ... */
	kADMAppUnits2 = 102,
	/** ... */
	kADMAppUnits3 = 103,
	/** ... */
	kADMAppUnits4 = 104,
	/** ... */
	kADMAppUnits5 = 105,
	/** ... */
	kADMAppUnits6 = 106,
	/** ... */
	kADMAppUnits7 = 107,
	/** ... */
	kADMAppUnits8 = 108,
	/** ... */
	kADMAppUnits9 = 109,
	/** ... */
	kADMAppUnits10 = 110,
	/** ... */
	kADMMaxAppUnits = kADMAppUnits10,
	
	/** ... */
	kADMDummyUnits = 0xFFFFFFFF

}
ADMUnits;


// -----------------------------------------------------------------------------
//	Fonts

/** ... */
typedef enum
{
	/** ... */
	kADMDefaultFont = 0,
	/** ... */
	kADMDialogFont,
	/** ... */
	kADMPaletteFont,
	/** ... */
	kADMItalicDialogFont,
	/** ... */
	kADMItalicPaletteFont,
	/** ... */
	kADMBoldDialogFont,
	/** ... */
	kADMBoldPaletteFont,
	/** ... */
	kADMBoldItalicDialogFont,
	/** ... */
	kADMBoldItalicPaletteFont,
	/** ... */
	kADMFixedWidthFont,
	/** ... */
	kADMItalicFixedWidthFont,
	/** ... */
	kADMBoldFixedWidthFont,
	/** ... */
	kADMBoldItalicFixedWidthFont,
	/** A bogus one added by Acrobat: */
	kADMJavaScriptEditorFont,
	kADMDummyFont = 0xFFFFFFFF
}
ADMFont;

#ifdef WIN_ENV

typedef void* ADMPlatformFontRef;
#endif

#ifdef MAC_ENV

/** Macintosh definition */
typedef struct
{
	
	/** ... */
	ADMInt32 textFont;			// font number
	/** ... */
	ADMInt32 textStyle;
	/** ... */
	ADMInt32 textSize;
	
} ADMPlatformFontRef;

#endif


// -----------------------------------------------------------------------------
//	Justify

/** ... */
typedef enum
{
	/** ... */
	kADMLeftJustify = 0,
	/** ... */
	kADMCenterJustify = 1,
	/** ... */
	kADMRightJustify = 2,
	/** ... */
	kADMDummyJustify = 0xFFFFFFFF
}
ADMJustify;


// -----------------------------------------------------------------------------
//	Color
//  kADMDummyColor = 0x000000fe, and an ADMColor > 0x000000fe specifies
//  an RGB value.  Shift off the lower 8 bits, and you have the RGB value.
//  using the high 24 bits.  The low 8 bits should be ignored, but should
//  be set to FF.  The format for the color is 0xRRGGBBFF.
//   black would be ADMColor color = (ADMColor)0x000000FF,
//     red would be ADMColor color = (ADMColor)0xFF0000FF,
//   green would be ADMColor color = (ADMColor)0x00FF00FF,
//    blue would be ADMColor color = (ADMColor)0x0000FFFF,
//   white would be ADMColor color = (ADMColor)0xFFFFFFFF

/** ... */
typedef enum 
{
	/** ... */
	kADMBlackColor = 0,
	/** ... */
	kADMWhiteColor,
	/** ... */
	kADMHiliteColor,
	/** ... */
	kADMHiliteTextColor,
	/** ... */
	kADMLightColor,
	/** ... */
	kADMBackgroundColor,
	/** ... */
	kADMShadowColor,
	/** ... */
	kADMDisabledColor,
	/** ... */
	kADMButtonUpColor,
	/** ... */
	kADMButtonDownColor,
	/** ... */
	kADMButtonDownShadowColor,
	/** ... */
	kADMToolTipBackgroundColor,
	/** ... */
	kADMToolTipForegroundColor,
	/** ... */
	kADMWindowColor,
	/** ... */
	kADMForegroundColor,
	/** ... */
	kADMTextColor,
	/** ... */
	kADMRedColor,
	/** ... */
	kADMTabBackgroundColor,
	/** ... */
	kADMActiveTabColor,
	/** ... */
	kADMInactiveTabColor,
	/** ... */
	kADMDummyColor = 0x000000FE,	// Probably ought to be renamed to kADMUnspecifiedColor
	/** ... */
	kActuallyRGBWhiteButSpecifiedToForceEnumTo32Bits = 0xFFFFFFFF
}
ADMColor;


// -----------------------------------------------------------------------------
//	"Create" function option flags common across object types.

/** ... */
enum
{
	/** ... */
	kADMIgnoreRomanFontForcing = (1L<<16)	/* Override kADMForceRomanFont host option for a particular object. */
};

// -----------------------------------------------------------------------------

#pragma ADM_PRAGMA_IMPORT_END
#pragma ADM_PRAGMA_ALIGN_END

#ifdef __cplusplus
}
#endif

// -----------------------------------------------------------------------------

#endif	// __ADMTypes__
