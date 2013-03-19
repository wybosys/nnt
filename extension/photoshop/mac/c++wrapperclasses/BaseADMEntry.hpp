/***********************************************************************/
/*                                                                     */
/* BaseADMEntry.hpp                                                    */
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

#ifndef __BaseADMEntry_hpp__
#define __BaseADMEntry_hpp__

/*
 * Includes
 */
 
#ifndef __IADMEntry_hpp__
#include "IADMEntry.hpp"
#endif

#include "IADMList.hpp"

class IADMDrawer;
class IADMNotifier;
class IADMTracker;


/*
 * Base Class
 */

class BaseADMEntry : public IADMEntry
{
private:
	static ASErr ASAPI InitProc(ADMEntryRef entry);
	static void ASAPI DrawProc(ADMEntryRef entry, ADMDrawerRef drawer);
	static ASBoolean ASAPI TrackProc(ADMEntryRef entry, ADMTrackerRef tracker);
	static void ASAPI NotifyProc(ADMEntryRef entry, ADMNotifierRef notifier);
	static void ASAPI DestroyProc(ADMEntryRef entry);

protected:
//	IADMEntry fEntry;
	IADMList fList;
	ADMUserData fUserData;
	
	virtual ASErr Init();
	virtual void Draw(IADMDrawer drawer);
	virtual ASBoolean Track(IADMTracker tracker);
	virtual void Notify(IADMNotifier notifier);

	virtual void BaseDraw(IADMDrawer drawer);

public:	
	BaseADMEntry(IADMEntry entry, ADMUserData data = NULL);
	BaseADMEntry(IADMList list, ADMUserData entryUserData = NULL);
	virtual ~BaseADMEntry();

	virtual ADMEntryRef Create(ADMListRef list, ADMUserData data = NULL);

	void SetUserData(ADMUserData userData);
	ADMUserData GetUserData();
	
//	IADMEntry GetEntry();

	ASErr DoInit();
};


inline void BaseADMEntry::SetUserData(ADMUserData userData)
{
	fUserData = userData;
}

inline ADMUserData BaseADMEntry::GetUserData()
{
	return fUserData;
}

/*
inline IADMEntry BaseADMEntry::GetEntry()
{
	return fEntry;
}
*/
inline ASErr BaseADMEntry::DoInit()
{ 
	return Init(); 
}

#endif