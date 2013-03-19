/*******************************************************************************
*
* ADMResource.h -- ADM Resource IDs
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
* Started by Dave Lazarony, 12 May 1996
*
********************************************************************************/

/** @file ADMResource.h ADM Resource IDs */

#ifndef __ADMResource__
#define __ADMResource__


// -----------------------------------------------------------------------------
//	ADM picture IDs

/** ... */
#define kADMAttentionPictureID					-1000
/** ... */
#define kADMErrorPictureID						-1001

/** ... */
#define kADMSliderPictureID						-16000
/** ... */
#define kADMSliderSelectedPictureID				-16001
/** ... */
#define kADMSliderDisabledPictureID				-16002
/** ... */
#define kADMXPSliderPictureID					-16003		// majones 10/25/2001 - XP Slider
/** ... */
#define kADMNewEntryPictureID					-16010
/** ... */
#define kADMNewEntryColorPictureID				-16011
/** ... */
#define kADMNewEntryDisabledPictureID			-16012
/** ... */
#define kADMDeleteEntryPictureID				-16020
/** ... */
#define kADMDeleteEntryColorPictureID			-16021
/** ... */
#define kADMDeleteEntryDisabledPictureID		-16022
/** ... */
#define kADMUpSpinArrowPictureID				-16040
/** ... */
#define kADMUpSpinArrowDisabledPictureID		-16042
/** ... */
#define kADMDownSpinArrowPictureID				-16050
/** ... */
#define kADMDownSpinArrowDisabledPictureID		-16052
/** ... */
#define kADMLeftSpinArrowPictureID				-16060
/** ... */
#define kADMLeftSpinArrowDisabledPictureID		-16062
/** ... */
#define kADMRightSpinArrowPictureID				-16070
/** ... */
#define kADMRightSpinArrowDisabledPictureID		-16072
/** ... */
#define kADMRightPopupArrowPictureID			-16080
/** ... */
#define kADMRightPopupArrowDisabledPictureID	-16082
/** ... */
#define kADMDownPopupArrowPictureID				-16090
/** ... */
#define kADMDownPopupArrowDisabledPictureID		-16092
/** ... */
#define kADMHierarchyListExpandPictureID		-16094
/** ... */
#define kADMHierarchyListCollapsePictureID		-16095
/** ... */
#define kADMXPHierarchyListExpandPictureID		-16098		// majones 10/29/2001 - XP Discolsure Triangles
/** ... */
#define kADMXPHierarchyListCollapsePictureID	-16099		// majones 10/29/2001 - XP Discolsure Triangles

#if qWR 
/** ... */
#define kADMHierarchyListCollapseLeftPictureID		-16200
/** ... */
#define kADMXPHierarchyListCollapseLeftPictureID	-16201
#endif

// [cpaduan] 7/16/01 - Picture IDs for icons only needed for Mac OS X.
#if Platform_Carbon
/** ... */
#define kADMHierarchyListExpandMacOSXPictureID	-16096
/** ... */
#define kADMHierarchyListCollapseMacOSXPictureID -16097
/** ... */
#define kADMMacOSXResizePictureID				-16110
#endif
// majones 10/4/2001 - Windows XP PNG Icons
/** ... */
#define kADMNormalDialPictureID					-16030
/** ... */
#define kADMResizePictureID						-16100

// -----------------------------------------------------------------------------
//	ADM cursor IDs

/** ... */
#define kADMIBeamCursorID						-1
/** ... */
#define kADMCrossCursorID						-2
/** ... */
#define kADMWaitCursorID						-3
/** ... */
#define kADMArrowCursorID						-4
/** ... */
#define kADMCancelCursorID						-5
/** ... */
#define kADMFingerCursorID						-6
/** ... */
#define kADMFistCursorID						-7
/** ... */
#define kADMFistPlusCursorID					-8
/** ... */
#define kADMHostControlsCursorID				-9

/** ... */
#define kADMSmallestCursorID					kADMHostControlsCursorID
/** ... */
#define kADMLargestCursorID						kADMIBeamCursorID


// -----------------------------------------------------------------------------
//	OR this flag with the dialog style of a Windows dialog resource and the
//	dialog's units are read as Pixel Units instead of Dialog Units.

/** ... */
#define kADMPixelUnitsDialogStyle				0x0020		


// -----------------------------------------------------------------------------
//	Popup Control Dialog IDs

/** ... */
#define kADMPopupSliderDialogID					-2000		//1900 - 2000 reserved for ADM Sliders
/** ... */
#define kADMPopupDialDialogID					-2010       //2001 - 2010 reserved for ADM Dials 


#endif	// __ADMResource__
