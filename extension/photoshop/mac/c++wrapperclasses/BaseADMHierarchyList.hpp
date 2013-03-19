/***********************************************************************/
/*                                                                     */
/* BaseADMHierarchyList.hpp                                            */
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

#ifndef __BaseADMHierarchyList_hpp__
#define __BaseADMHierarchyList_hpp__

/*
 * Includes
 */
 
#ifndef __IADMHierarchyList_hpp__
#include "IADMHierarchyList.hpp"
#endif

class IADMDrawer;
class IADMNotifier;
class IADMTracker;


/*
 * Base Class
 */

class BaseADMHierarchyList : public IADMHierarchyList
{
protected:
	ADMUserData fUserData;

public:	
	BaseADMHierarchyList(IADMHierarchyList list, ADMUserData data = NULL);
	virtual ~BaseADMHierarchyList();

	void SetUserData(ADMUserData userData);
	ADMUserData GetUserData();
};


inline void BaseADMHierarchyList::SetUserData(ADMUserData userData)
{
	fUserData = userData;
}

inline ADMUserData BaseADMHierarchyList::GetUserData()
{
	return fUserData;
}

#endif
