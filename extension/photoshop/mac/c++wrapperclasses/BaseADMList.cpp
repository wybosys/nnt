/***********************************************************************/
/*                                                                     */
/* BaseADMList.cpp                                                     */
/*                                                                     */
/* Copyright 1998-1999 Adobe Systems Incorporated.                     */
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
/* Started by Darin Tomack, 02/02/1998                                 */
/*                                                                     */
/***********************************************************************/

/*
 * Includes
 */

#include "BaseADMList.hpp"
#include "IADMDrawer.hpp"
#include "IADMNotifier.hpp"
#include "IADMTracker.hpp"

/*
 * Constructor
 */

BaseADMList::BaseADMList(IADMList list, ADMUserData /*data*/) 
: IADMList(list)
{
	// [jsass - 02/21/2000] commenting out the "data" variable
	// as it is not used and the UNREFERENCED macro doesn't work

	if (list)
	{
		sADMList->SetUserData(list, this);
	}
}


/*
 * Destructor
 */

BaseADMList::~BaseADMList()
{
	if (sADMList)
	{
		SetUserData(NULL);
			
		/* Don't touch these. If this list class object
		   is deleted in the plug-in before associated ADMList
		   object is deleted in ADM, we'll need these procs
		   still set on that side of ADM to make sure any entry
		   data on this side is cleaned up.

		sADMList->SetUserData(fList, NULL);
		sADMList->SetDrawProc(fList, NULL);
		sADMList->SetNotifyProc(fList, NULL);
		sADMList->SetDestroyProc(fList, NULL);

		*/
	}
			
//	fList = NULL;
}

