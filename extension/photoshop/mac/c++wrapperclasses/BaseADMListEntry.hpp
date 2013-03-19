/***********************************************************************/
/*                                                                     */
/* BaseADMListEntry.hpp                                                */
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

#ifndef __BaseADMListEntry_hpp__
#define __BaseADMListEntry_hpp__

/*
 * Includes
 */
 
#ifndef __IADMListEntry_hpp__
#include "IADMListEntry.hpp"
#endif

#include "IADMHierarchyList.hpp"

class IADMDrawer;
class IADMNotifier;
class IADMTracker;


/*
 * Base Class
 */

class BaseADMListEntry : public IADMListEntry
{
private:
	static ASErr ASAPI InitProc(ADMListEntryRef entry);
	static void ASAPI DrawProc(ADMListEntryRef entry, ADMDrawerRef drawer);
	static ASBoolean ASAPI TrackProc(ADMListEntryRef entry, ADMTrackerRef tracker);
	static void ASAPI NotifyProc(ADMListEntryRef entry, ADMNotifierRef notifier);
	static void ASAPI DestroyProc(ADMListEntryRef entry);

protected:
	IADMHierarchyList fHierarchyList;
	ADMUserData fUserData;
	
	virtual ASErr Init();
	virtual void Draw(IADMDrawer drawer);
	virtual ASBoolean Track(IADMTracker tracker);
	virtual void Notify(IADMNotifier notifier);

	virtual void BaseDraw(IADMDrawer drawer);

public:	
	BaseADMListEntry(IADMListEntry entry, ADMUserData data = NULL);
	BaseADMListEntry(IADMHierarchyList list, ADMUserData entryUserData = NULL);
	virtual ~BaseADMListEntry();

	virtual ADMListEntryRef Create(ADMHierarchyListRef list, ADMUserData data = NULL);

	void SetUserData(ADMUserData userData);
	ADMUserData GetUserData();
	
	ASErr DoInit();
};


inline void BaseADMListEntry::SetUserData(ADMUserData userData)
{
	fUserData = userData;
}

inline ADMUserData BaseADMListEntry::GetUserData()
{
	return fUserData;
}

inline ASErr BaseADMListEntry::DoInit()
{ 
	return Init(); 
}

#endif // __BaseADMListEntry_hpp__