/***********************************************************************/
/*                                                                     */
/* BaseADMList.hpp                                                     */
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

#ifndef __BaseADMList_hpp__
#define __BaseADMList_hpp__

/*
 * Includes
 */
 
#ifndef __IADMList_hpp__
#include "IADMList.hpp"
#endif

class IADMDrawer;
class IADMNotifier;
class IADMTracker;


/*
 * Base Class
 */

class BaseADMList : public IADMList
{
protected:
//	IADMList fList;
	ADMUserData fUserData;

public:	
	BaseADMList(IADMList list, ADMUserData data = NULL);
	virtual ~BaseADMList();

	void SetUserData(ADMUserData userData);
	ADMUserData GetUserData();
	
//	IADMList GetList();
};


inline void BaseADMList::SetUserData(ADMUserData userData)
{
	fUserData = userData;
}

inline ADMUserData BaseADMList::GetUserData()
{
	return fUserData;
}

/*
inline IADMList BaseADMList::GetList()
{
	return fList;
}
*/
#endif