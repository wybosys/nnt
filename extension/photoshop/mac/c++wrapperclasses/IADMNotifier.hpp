/***********************************************************************/
/*                                                                     */
/* IADMNotifier.hpp                                                    */
/* Object wrapper for ADM Notifier suite                               */
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

#ifndef __IADMNotifier_hpp__
#define __IADMNotifier_hpp__

/*
 * Includes
 */
 
#ifndef __ADMNotifier__
#include "ADMNotifier.h"
#endif

/*
 * Global Suite Pointer
 */

extern "C" ADMNotifierSuite2* sADMNotifier;

/*
 * Wrapper Class
 */

class IADMNotifier
{
private:
	ADMNotifierRef fNotifier;

public:	
	IADMNotifier() 												{ fNotifier = NULL; }
	IADMNotifier(ADMNotifierRef notifier) 						{ fNotifier = notifier; }
	
	operator ADMNotifierRef() 									{ return fNotifier; }
	
	ADMItemRef GetItem()										{ return sADMNotifier->GetItem(fNotifier); }	
	ADMDialogRef GetDialog()									{ return sADMNotifier->GetDialog(fNotifier); }

	ASBoolean IsNotifierType(const char* notifierType)			{ return sADMNotifier->IsNotifierType(fNotifier, notifierType); }

	void GetNotifierType(char* notifierType, int maxLength = 0)	{ sADMNotifier->GetNotifierType(fNotifier, notifierType, maxLength); }

};

#endif
