/***********************************************************************/
/*                                                                     */
/* IADMTracker.hpp                                                     */
/* Object wrapper for ADM Tracker Suite                                */
/*                                                                     */
/* Copyright 1996-1999 Adobe Systems Incorporated.                     */
/* All Rights Reserved.                                                */
/*                                                                     */
/* Patents Pending                                                     */
/*                                                                     */
/* NOTICE: All information contained herein is the property of Adobe   */
/* Systems Incorporated. Many of the intellectual and technical        */
/* concepts contained herein are proprietary to Adobe, are protected   */
/* as trade secrets, and are made available only to Adobe licensees    */
/* for their internal use. Any reproduction or dissemination of this   */
/* software is strictly forbidden unless prior written permission is   */
/* obtained from Adobe.                                                */
/*                                                                     */
/* Started by Dave Lazarony, 03/06/1996                                */
/*                                                                     */
/***********************************************************************/

#ifndef __IADMTracker_hpp__
#define __IADMTracker_hpp__

/*
 * Includes
 */
 
#ifndef __ADMTracker__
#include "ADMTracker.h"
#endif

#ifndef __IASPoint_hpp__
#include "IASPoint.hpp"
#endif

/*
 * Global Suite Pointer
 */

extern "C" ADMTrackerSuite* sADMTracker;

/*
 * Wrapper Class
 */

class IADMTracker
{
private:
	ADMTrackerRef fTracker;

public:	
	IADMTracker() 									{ fTracker = NULL; }
	IADMTracker(ADMTrackerRef tracker) 				{ fTracker = tracker; }
	
	operator ADMTrackerRef(void) 					{ return fTracker; }

	void Abort()									{ sADMTracker->Abort(fTracker); }
	
	void GetPoint(IASPoint& point) 					{ sADMTracker->GetPoint(fTracker, &point); }
	
	ADMAction GetAction() 							{ return sADMTracker->GetAction(fTracker); }
	ADMModifiers GetModifiers()						{ return sADMTracker->GetModifiers(fTracker); }
	
	ASBoolean TestAction(ADMAction action) 			{ return sADMTracker->TestAction(fTracker, action); }
	ASBoolean TestModifier(ADMModifiers modifier)	{ return sADMTracker->TestModifier(fTracker, modifier); }
	
	ADMTime GetTime()								{ return sADMTracker->GetTime(fTracker); }

	ADMMouseState GetMouseState()					{ return sADMTracker->GetMouseState(fTracker); }
	void ReleaseMouseCapture()						{ sADMTracker->ReleaseMouseCapture(fTracker); }

	ADMChar GetVirtualKey()							{ return sADMTracker->GetVirtualKey(fTracker); }
	ADMChar GetCharacter()							{ return sADMTracker->GetCharacter(fTracker); }


	/*
	 * Action Testers
	 */
	ASBoolean DidMouseMove()						{ return TestAction(kADMMouseMoveAction); }		/**** Get rid of this  FIX ME pja****/

	ASBoolean DidMouseMoveWhileDown()				{ return TestAction(kADMMouseMovedDownAction); }
	ASBoolean DidMouseMoveWhileUp()					{ return TestAction(kADMMouseMovedUpAction); }
	ASBoolean DidButtonGoDown() 					{ return TestAction(kADMButtonDownAction); }
	ASBoolean DidButtonGoUp() 						{ return TestAction(kADMButtonUpAction); }
	ASBoolean DidShiftKeyGoDown() 					{ return TestAction(kADMShiftKeyDownAction); }
	ASBoolean DidShiftKeyGoUp() 					{ return TestAction(kADMShiftKeyUpAction); }
	ASBoolean DidMenuKeyGoDown() 					{ return TestAction(kADMMenuKeyDownAction); }
	ASBoolean DidMenuKeyGoUp() 						{ return TestAction(kADMMenuKeyUpAction); }
	ASBoolean DidModKeyGoDown() 					{ return TestAction(kADMModKeyDownAction); }
	ASBoolean DidModKeyGoUp() 						{ return TestAction(kADMModKeyUpAction); }
	ASBoolean DidSpaceKeyGoDown() 					{ return TestAction(kADMSpaceKeyDownAction); }
	ASBoolean DidSpaceKeyGoUp() 					{ return TestAction(kADMSpaceKeyUpAction); }
	ASBoolean DidTabKeyGoDown() 					{ return TestAction(kADMTabKeyDownAction); }
	ASBoolean DidTabKeyGoUp() 						{ return TestAction(kADMTabKeyUpAction); }
	ASBoolean DidEnter()							{ return TestAction(kADMEnterAction); }
	ASBoolean DidLeave()							{ return TestAction(kADMLeaveAction); }
	ASBoolean DidUncapturedButtonGoUp()				{ return TestAction(kADMUncapturedButtonUpAction); }
	
	ASBoolean DidWinLeftButtonGoDown() 				{ return TestAction(kWinLeftButtonDownAction); }
	ASBoolean DidWinLeftButtonGoUp() 				{ return TestAction(kWinLeftButtonUpAction); }
	ASBoolean DidWinMiddleButtonGoDown()			{ return TestAction(kWinMiddleButtonDownAction); }
	ASBoolean DidWinMiddleButtonGoUp() 				{ return TestAction(kWinMiddleButtonUpAction); }
	ASBoolean DidWinRightButtonGoDown() 			{ return TestAction(kWinRightButtonDownAction); }
	ASBoolean DidWinRightButtonGoUp() 				{ return TestAction(kWinRightButtonUpAction); }
	ASBoolean DidWinAltKeyGoDown() 					{ return TestAction(kWinAltKeyDownAction); }
	ASBoolean DidWinAltKeyGoUp() 					{ return TestAction(kWinAltKeyUpAction); }
	ASBoolean DidWinControlKeyGoDown() 				{ return TestAction(kWinControlKeyDownAction); }
	ASBoolean DidWinControlKeyGoUp() 				{ return TestAction(kWinControlKeyUpAction); }
	ASBoolean DidWinUncapturedLeftButtonGoUp()		{ return TestAction(kWinUncapturedLeftButtonUpAction); }
	ASBoolean DidWinUncapturedMiddleButtonGoUp()	{ return TestAction(kWinUncapturedMiddleButtonUpAction); }
	ASBoolean DidWinUncapturedRightButtonGoUp()		{ return TestAction(kWinUncapturedRightButtonUpAction); }

	
	ASBoolean DidMacCommandKeyGoDown() 				{ return TestAction(kMacCommandKeyDownAction); }
	ASBoolean DidMacCommandKeyGoUp() 				{ return TestAction(kMacCommandKeyUpAction); }
	ASBoolean DidMacOptionKeyGoDown() 				{ return TestAction(kMacOptionKeyDownAction); }
	ASBoolean DidMacOptionKeyGoUp() 				{ return TestAction(kMacOptionKeyUpAction); }
	ASBoolean DidMacControlKeyGoDown() 				{ return TestAction(kMacControlKeyDownAction); }
	ASBoolean DidMacControlKeyGoUp() 				{ return TestAction(kMacControlKeyUpAction); }
		
	/*
	 * Modifier Testers
	 */
	ASBoolean IsButtonDown() 						{ return TestModifier(kADMButtonDownModifier); }
	ASBoolean IsShiftKeyDown() 						{ return TestModifier(kADMShiftKeyDownModifier); }
	ASBoolean IsMenuKeyDown() 						{ return TestModifier(kADMMenuKeyDownModifier); }
	ASBoolean IsModKeyDown() 						{ return TestModifier(kADMModKeyDownModifier); }
	ASBoolean IsSpaceKeyDown() 						{ return TestModifier(kADMSpaceKeyDownModifier); }
	ASBoolean IsTabKeyDown() 						{ return TestModifier(kADMTabKeyDownModifier); }
	ASBoolean IsDoubleClick() 						{ return TestModifier(kADMDoubleClickModifier); }
		
	ASBoolean IsWinLeftButtonDown() 				{ return TestModifier(kWinLeftButtonDownModifier); }
	ASBoolean IsWinMiddleButtonDown()				{ return TestModifier(kWinMiddleButtonDownModifier); }
	ASBoolean IsWinRightButtonDown() 				{ return TestModifier(kWinRightButtonDownModifier); }
	ASBoolean IsWinAltKeyDown() 					{ return TestModifier(kWinAltKeyDownModifier); }
	ASBoolean IsWinControlKeyDown() 				{ return TestModifier(kWinControlKeyDownModifier); }
		
	ASBoolean IsMacCommandKeyDown() 				{ return TestModifier(kMacCommandKeyDownModifier); }
	ASBoolean IsMacOptionKeyDown() 					{ return TestModifier(kMacOptionKeyDownModifier); }
	ASBoolean IsMacControlKeyDown() 				{ return TestModifier(kMacControlKeyDownModifier); }
};

#endif
