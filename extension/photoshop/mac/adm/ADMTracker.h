/*******************************************************************************
*
* ADMTracker.h -- ADM Tracker Suite
*
* ADOBE SYSTEMS INCORPORATED
* Copyright 1996-2003 Adobe Systems Incorporated
* All Rights Reserved
*
* NOTICE: Adobe permits you to use, modify, and distribute this file in
* accordance with the terms of the Adobe license agreement accompanying it.
* If you have received this file from a source other than Adobe, then your use,
* modification, or distribution of it requires the prior written permission of
* Adobe.
*
* Started by Dave Lazarony, 25 Mar 1996
*
********************************************************************************/

/** @file ADMTracker.h ADM Tracker Suite */

#ifndef __ADMTracker__
#define __ADMTracker__

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
typedef enum {
	/** ... */
	kADMMouseNormal,
	/** ... */
	kADMMouseCaptured,
	/** ... */
	kADMMouseUncaptured
}
ADMMouseState;

/** ... */
typedef unsigned long ADMTime;


// -----------------------------------------------------------------------------
//	Tracker event codes

// 			     ADM General						        Macintosh Specific			                   Windows Specific	
//  -----------------------------------------   -----------------------------------------   ---------------------------------------------

/** ... */
typedef enum 
{
	/** ... */
	kADMMouseMoveAction			= 1,			// It is better to use the specific move down and up cases
	/** ... */
	kADMMouseMovedDownAction	= 1,
	
	/** ... */
	kADMButtonDownAction		= 2,														kWinLeftButtonDownAction		= 2,
																							kWinMiddleButtonDownAction		= 3,
																							kWinRightButtonDownAction		= 4,
	/** ... */
	kADMShiftKeyDownAction		= 5,
	/** ... */
	kADMMenuKeyDownAction		= 6,			kMacCommandKeyDownAction	= 6,			kWinControlKeyDownAction		= 6,
	/** ... */
	kADMModKeyDownAction		= 7,			kMacOptionKeyDownAction		= 7,			kWinAltKeyDownAction			= 7,
												kMacControlKeyDownAction	= 8,	
	/** ... */
	kADMSpaceKeyDownAction		= 9,	
	/** ... */
	kADMTabKeyDownAction		= 10,
	/** ... */
	kADMEnterAction				= 11,

	/** ... */
	kADMMouseMovedUpAction		= -1,
	/** ... */
	kADMButtonUpAction			= -2,														kWinLeftButtonUpAction			= -2,
																							kWinMiddleButtonUpAction		= -3,
																							kWinRightButtonUpAction			= -4,
	/** ... */
	kADMShiftKeyUpAction		= -5,
	/** ... */
	kADMMenuKeyUpAction			= -6,			kMacCommandKeyUpAction		= -6,			kWinControlKeyUpAction			= -6,
	/** ... */
	kADMModKeyUpAction			= -7,			kMacOptionKeyUpAction		= -7,			kWinAltKeyUpAction				= -7,
												kMacControlKeyUpAction		= -8,	
	/** ... */
	kADMSpaceKeyUpAction		= -9,	
	/** ... */
	kADMTabKeyUpAction			= -10,
	/** ... */
	kADMLeaveAction				= -11,
	/** ... */
	kADMUncapturedButtonUpAction= -12,														kWinUncapturedLeftButtonUpAction	= -12,
																							kWinUncapturedMiddleButtonUpAction	= -13,
																							kWinUncapturedRightButtonUpAction	= -14,
	/** ... */
	kADMKeyStrokeAction			= -15,

	/** ... */
	kADMDummyAction				= 0x7FFFFFFF
}
ADMAction;


// -----------------------------------------------------------------------------
//	Tracker event masks

// 			     ADM General						        Macintosh Specific			                   Windows Specific	
//  -----------------------------------------   -----------------------------------------   ---------------------------------------------

/** ... */
enum {
	/** ... */
	kADMNullMask				= 0x00000000,

	/** ... */
	kADMUncapturedActionMask	= 0x00000001,

	/** ... */
	kADMMouseMovedDownMask		= 0x00000002,
	
	/** ... */
	kADMButtonDownMask			= 0x00000004,												kWinLeftButtonDownMask		= 0x00000004,
																							kWinMiddleButtonDownMask	= 0x00000008,
																							kWinRightButtonDownMask		= 0x00000010,
	/** ... */
	kADMShiftKeyDownMask		= 0x00000020,
	/** ... */
	kADMMenuKeyDownMask			= 0x00000040,	kMacCommandKeyDownMask		= 0x00000040,	kWinControlKeyDownMask		= 0x00000040,
	/** ... */
	kADMModKeyDownMask			= 0x00000080,	kMacOptionKeyDownMask		= 0x00000080,	kWinAltKeyDownMask			= 0x00000080,
												kMacControlKeyDownMask		= 0x00000100,	
	/** ... */
	kADMSpaceKeyDownMask		= 0x00000200,	
	/** ... */
	kADMTabKeyDownMask			= 0x00000400,
	/** ... */
	kADMEnterMask				= 0x00000800,

	/** ... */
	kADMMouseMovedUpMask		= 0x00020000,
	/** ... */
	kADMButtonUpMask			= 0x00040000,												kWinLeftButtonUpMask		= 0x00040000,
																							kWinMiddleButtonUpMask		= 0x00080000,
																							kWinRightButtonUpMask		= 0x00100000,
	/** ... */
	kADMShiftKeyUpMask			= 0x00200000,
	/** ... */
	kADMMenuKeyUpMask			= 0x00400000,	kMacCommandKeyUpMask		= 0x00400000,	kWinControlKeyUpMask		= 0x00400000,
	/** ... */
	kADMModKeyUpMask			= 0x00800000,	kMacOptionKeyUpMask			= 0x00800000,	kWinAltKeyUpMask			= 0x00800000,
												kMacControlKeyUpMask		= 0x01000000,	
	/** ... */
	kADMSpaceKeyUpMask			= 0x02000000,	
	/** ... */
	kADMTabKeyUpMask			= 0x04000000,
	/** ... */
	kADMLeaveMask				= 0x08000000,
	/** ... */
	kADMUncapturedButtonUpMask	= 0x10000000,	/* Applies to all UncapturedButtonUpActions on Windows */
	
	/** ... */
	kADMKeyStrokeMask			= 0x80000000
};
	
/** ... */
#define kADMAllActionsMask ((unsigned long) 0xFFFFFFFF)


// -----------------------------------------------------------------------------
//	Tracker modifier key masks

// 			     ADM General						        Macintosh Specific			                   Windows Specific	
//  -----------------------------------------   -----------------------------------------   ---------------------------------------------

/** ... */
typedef enum 
{
	/** ... */
	kADMNullModifier			= 0x00000000,
	
	/** ... */
	kADMButtonDownModifier		= 0x00000004,												kWinLeftButtonDownModifier		= 0x00000004,
																							kWinMiddleButtonDownModifier	= 0x00000008,
																							kWinRightButtonDownModifier		= 0x00000010,
	/** ... */
	kADMShiftKeyDownModifier	= 0x00000020,
	/** ... */
	kADMMenuKeyDownModifier		= 0x00000040,	kMacCommandKeyDownModifier	= 0x00000040,	kWinControlKeyDownModifier		= 0x00000040,
	/** ... */
	kADMModKeyDownModifier		= 0x00000080,	kMacOptionKeyDownModifier	= 0x00000080,	kWinAltKeyDownModifier			= 0x00000080,
												kMacControlKeyDownModifier	= 0x00000100,	
	/** ... */
	kADMSpaceKeyDownModifier	= 0x00000200,	
	/** ... */
	kADMTabKeyDownModifier		= 0x00000400,
	/** ... */
	kADMDoubleClickModifier		= 0x00000800,

	/** ... */
	kADMCapsLockOnModifier		= 0x00001000,
	
	/** ... */
	kADMTripleClickModifier		= 0x00002000,

	/** ... */
	kADMDummyModifier			= 0xFFFFFFFF
}
ADMModifiers;


// -----------------------------------------------------------------------------
//	Virtual keys

/** ... */
enum {
	
	/** ... */
	kADMUnknownKey			= 0x0000,
	/** ... */
	kADMCancelKey			= 0x0001,
	/** ... */
	kADMEnterKey			= 0x0003,
	/** ... */
	kADMHomeKey				= 0x0004,
	/** ... */
	kADMEndKey				= 0x0005,
	/** ... */
	kADMPageUpKey			= 0x0006,
	/** ... */
	kADMPageDownKey			= 0x0007,
	/** ... */
	kADMBackspaceKey		= 0x0008,
	/** ... */
	kADMTabKey				= 0x0009,
	/** ... */
	kADMInsertKey			= 0x000A,
	/** ... */
	kADMReturnKey			= 0x000D,
	/** ... */
	kADMF1Key				= 0x000E,
	/** ... */
	kADMF2Key				= 0x000F,
	/** ... */
	kADMF3Key				= 0x0010,
	/** ... */
	kADMF4Key				= 0x0011,
	/** ... */
	kADMF5Key				= 0x0012,
	/** ... */
	kADMF6Key				= 0x0013,
	/** ... */
	kADMF7Key				= 0x0014,
	/** ... */
	kADMF8Key				= 0x0015,
	/** ... */
	kADMF9Key				= 0x0016,
	/** ... */
	kADMF10Key				= 0x0017,
	/** ... */
	kADMF11Key				= 0x0018,
	/** ... */
	kADMF12Key				= 0x0019,
	/** ... */
	kADMClearKey			= 0x001A,
	/** ... */
	kADMEscapeKey			= 0x001B,
	/** ... */
	kADMLeftKey				= 0x001C,
	/** ... */
	kADMRightKey			= 0x001D,
	/** ... */
	kADMUpKey				= 0x001E,
	/** ... */
	kADMDownKey				= 0x001F,
	/** ... */
	kADMSpaceKey			= 0x0020,
	
		// Virtual keys from 0x0020 through the slash key (/) are their ASCII equivalents
	/** ... */
	kADMApostropheKey		= 0x0027,	// '
	/** ... */
	kADMCommaKey			= 0x002C,	// ,
	/** ... */
	kADMMinusKey			= 0x002D,	// -
	/** ... */
	kADMPeriodKey			= 0x002E,	// .
	/** ... */
	kADMSlashKey			= 0x002F,	// /

	// kADM0Key - kADM9Key are the same as ASCII '0' thru '9' (0x30 - 0x39)
	
	/** ... */
	kADMSemicolonKey		= 0x003B,	// ;
	/** ... */
	kADMEqualKey			= 0x003D,	// =

	// kADMAKey - kADMZKey are the same as ASCII 'A' thru 'Z' (0x41 - 0x5A)

// dhearst 3/30/00 - the left and right square brackets had their ASCII values reversed
//	kADMRightSqrBracketKey	= 0x005B,	// ]
	/** ... */
	kADMLeftSqrBracketKey	= 0x005B,	// [
	/** ... */
	kADMBackSlashKey		= 0x005C,	// "\"
// dhearst 3/30/00 - the left and right square brackets had their ASCII values reversed
//	kADMLeftSqrBracketKey	= 0x005D,	// [ (last ASCII value)
	/** ... */
	kADMRightSqrBracketKey	= 0x005D,	// ] (last ASCII value)

	/** ... */
	kADMDeleteKey			= 0x007F,

		// key pad keys
	/** ... */
	kADMKP0Key				= 0x00E0,
	/** ... */
	kADMKP1Key				= 0x00E1,
	/** ... */
	kADMKP2Key				= 0x00E2,
	/** ... */
	kADMKP3Key				= 0x00E3,
	/** ... */
	kADMKP4Key				= 0x00E4,
	/** ... */
	kADMKP5Key				= 0x00E5,
	/** ... */
	kADMKP6Key				= 0x00E6,
	/** ... */
	kADMKP7Key				= 0x00E7,
	/** ... */
	kADMKP8Key				= 0x00E8,
	/** ... */
	kADMKP9Key 				= 0x00E9,
	/** ... */
	kADMKPEqualKey 			= 0x00EA,
	/** ... */
	kADMKPMultiplyKey		= 0x00EB,
	/** ... */
	kADMKPMinusKey 			= 0x00EC,
	/** ... */
	kADMKPPlusKey 			= 0x00ED,
	/** ... */
	kADMKPDivideKey		 	= 0x00EE,
	/** ... */
	kADMKPDecimalKey		= 0x00EF,
	
		// kADMDoubleByteChar indicates that we have a double-byte character.
		// This occurs only if the kADMTrackerGetsDoubleByteInput host option is set.
	/** ... */
	kADMDoubleByteChar		= 0x8000,

	/** ... */
	kADMDummyKey			= 0xFFFF
	
};


// =============================================================================
//		* ADM Tracker Suite
// =============================================================================

/** ... */
#define kADMTrackerSuite "ADM Tracker Suite"
/** ... */
#define kADMTrackerSuiteVersion1 1
/** ... */
#define kADMTrackerSuiteVersion kADMTrackerSuiteVersion1

// -----------------------------------------------------------------------------

/** ... */
typedef struct ADMTrackerSuite1
{

	// *** This suite is FROZEN.
	// *** It shipped with Photoshop 5.5 and ImageReady 2.0.

	/** ... */
	void ADMAPI (*GetPoint)(ADMTrackerRef inTracker, ADMPoint* outPoint);
	
	/** ... */
	ADMAction ADMAPI (*GetAction)(ADMTrackerRef inTracker);
	/** ... */
	ADMModifiers ADMAPI (*GetModifiers)(ADMTrackerRef inTracker);
	
	/** ... */
	ADMBoolean ADMAPI (*TestAction)(ADMTrackerRef inTracker, ADMAction inAction);
	/** ... */
	ADMBoolean ADMAPI (*TestModifier)(ADMTrackerRef inTracker, ADMModifiers inModifier);
	
	/** ... */
	ADMTime ADMAPI (*GetTime)(ADMTrackerRef inTracker);

	/** ... */
	void ADMAPI (*Abort)(ADMTrackerRef inTracker);

	/** ... */
	ADMMouseState ADMAPI (*GetMouseState)(ADMTrackerRef inTracker);
	/** ... */
	void ADMAPI (*ReleaseMouseCapture)(ADMTrackerRef inTracker);
	
	/** ... */
	ADMChar ADMAPI (*GetVirtualKey)(ADMTrackerRef inTracker);
	/** ... */
	ADMChar ADMAPI (*GetCharacter)(ADMTrackerRef inTracker);
	
}
ADMTrackerSuite1;

/** ... */
typedef ADMTrackerSuite1 ADMTrackerSuite;

// -----------------------------------------------------------------------------

#pragma ADM_PRAGMA_IMPORT_END
#pragma ADM_PRAGMA_ALIGN_END

#ifdef __cplusplus
}
#endif

// -----------------------------------------------------------------------------

#endif	// __ADMTracker__
