/***********************************************************************/
/*                                                                     */
/* BaseADMHierarchyList.cpp                                            */
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

#include "BaseADMHierarchyList.hpp"

/*
 * Constructor
 */

BaseADMHierarchyList::BaseADMHierarchyList(IADMHierarchyList list, ADMUserData data)								
{
	fList = list;
	fUserData = data;

	if (fList)
	{
		sADMHierarchyList->SetUserData(fList, this);
	}
}


/*
 * Destructor
 */

BaseADMHierarchyList::~BaseADMHierarchyList()
{
	if (sADMHierarchyList)
	{
		sADMHierarchyList->SetUserData(fList, NULL);
			
		/* Don't touch these. If this list class object
		   is deleted in the plug-in before associated ADMList
		   object is deleted in ADM, we'll need these procs
		   still set on that side of ADM to make sure any entry
		   data on this side is cleaned up.

		sADMHierarchyList->SetUserData(fList, NULL);
		sADMHierarchyList->SetDrawProc(fList, NULL);
		sADMHierarchyList->SetNotifyProc(fList, NULL);
		sADMHierarchyList->SetDestroyProc(fList, NULL);

		*/
	}
			
	fList = NULL;
}

