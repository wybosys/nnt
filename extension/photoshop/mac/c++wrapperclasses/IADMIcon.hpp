/***********************************************************************/
/*                                                                     */
/* IADMIcon.hpp                                                        */
/* Object wrapper for ADM Icon Suite                                   */
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
/* Started by Paul Asente, 06/15/1996                                  */
/*                                                                     */
/***********************************************************************/

#ifndef __IADMIcon_hpp__
#define __IADMIcon_hpp__

/*
 * Includes
 */
 
#ifndef __ADMIcon__
#include "ADMIcon.h"
#endif

/*
 * Global Suite Pointer
 */

extern "C" ADMIconSuite* sADMIcon;

/*
 * Wrapper Class
 */

class IADMIcon
{
private:
	ADMIconRef fIcon;

public:	
	IADMIcon(ADMIconType type, int width, int height, void* data)
		{ fIcon = sADMIcon->Create(type, width, height, data); }

	IADMIcon(SPPluginRef pluginRef, int iconID, int iconIndex)
		{ fIcon = sADMIcon->GetFromResource(pluginRef, iconID, iconIndex); }

	~IADMIcon()						{ sADMIcon->Destroy(fIcon); }

	IADMIcon(ADMIconRef icon)		{ fIcon = icon; }

	operator ADMIconRef()			{ return fIcon; }

	ADMIconType GetType()			{ return sADMIcon->GetType(fIcon); }
	int GetWidth()					{ return sADMIcon->GetWidth(fIcon); }
	int GetHeight()					{ return sADMIcon->GetHeight(fIcon); }
	void* GetData()					{ return sADMIcon->GetData(fIcon); }
	ASBoolean IsFromResource()		{ return sADMIcon->IsFromResource(fIcon); }
};

#endif
