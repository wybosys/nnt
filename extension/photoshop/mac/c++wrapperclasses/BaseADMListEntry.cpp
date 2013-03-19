/***********************************************************************/
/*                                                                     */
/* BaseADMListEntry.cpp                                                */
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

#include "BaseADMListEntry.hpp"
#include "IADMDrawer.hpp"
#include "IADMNotifier.hpp"
#include "IADMTracker.hpp"
#include "IADMList.hpp"
#include "IADMItem.hpp"

/*
 * Constructor
 */

BaseADMListEntry::BaseADMListEntry(IADMListEntry entry, ADMUserData data)
: IADMListEntry(entry),
  fUserData(data),
  fHierarchyList(GetList())
{
	if (fEntry && fHierarchyList)
	{
		sADMListEntry->SetUserData(fEntry, this);
		sADMHierarchyList->SetDrawProc(fHierarchyList, DrawProc);
		sADMHierarchyList->SetTrackProc(fHierarchyList, TrackProc);
		sADMHierarchyList->SetNotifyProc(fHierarchyList, NotifyProc);
		sADMHierarchyList->SetDestroyProc(fHierarchyList, DestroyProc);
	}
}

BaseADMListEntry::BaseADMListEntry(IADMHierarchyList list, ADMUserData entryUserData)
: IADMListEntry((ADMListEntryRef) NULL),
  fUserData(entryUserData),
  fHierarchyList(list)
{
	if (fHierarchyList){
		fEntry = sADMListEntry->Create( fHierarchyList );

		if (fEntry)
		{
			sADMListEntry->SetUserData(fEntry, this);
			sADMHierarchyList->SetDrawProc(fHierarchyList, DrawProc);
			sADMHierarchyList->SetTrackProc(fHierarchyList, TrackProc);
			sADMHierarchyList->SetNotifyProc(fHierarchyList, NotifyProc);
			sADMHierarchyList->SetDestroyProc(fHierarchyList, DestroyProc);
		}
	}
}

/*
 * Destructor
 */

BaseADMListEntry::~BaseADMListEntry()
{
	if (sADMListEntry)
	{
		SetUserData(NULL);

		/* We can't do this since other entries depend on these
		   procs.

		sADMHierarchyList->SetDrawProc(fHierarchyList, NULL);
		sADMHierarchyList->SetTrackProc(fHierarchyList, NULL);
		sADMHierarchyList->SetNotifyProc(fHierarchyList, NULL);
		sADMHierarchyList->SetDestroyProc(fHierarchyList, NULL);
		*/

		sADMListEntry->Destroy(*this);
	}
			
//	fEntry = NULL;
}


ADMListEntryRef BaseADMListEntry::Create(ADMHierarchyListRef list, ADMUserData data)								
{
	fHierarchyList = list;
	fUserData = data;

	if (fHierarchyList)
	{
		fEntry = sADMListEntry->Create( fHierarchyList );

		if (fEntry)
		{
			SetUserData(this);
			sADMHierarchyList->SetDrawProc(fHierarchyList, DrawProc);
			sADMHierarchyList->SetTrackProc(fHierarchyList, TrackProc);
			sADMHierarchyList->SetNotifyProc(fHierarchyList, NotifyProc);
			sADMHierarchyList->SetDestroyProc(fHierarchyList, DestroyProc);
		}
	}

	return fEntry;	
}


/*
 * Virtual Functions that call Defaults.
 */
	
ASErr BaseADMListEntry::Init()
{
	return kNoErr;
}

void BaseADMListEntry::Draw(IADMDrawer drawer)
{
	sADMListEntry->DefaultDraw(fEntry, drawer);
}

ASBoolean BaseADMListEntry::Track(IADMTracker tracker)
{
	return 	sADMListEntry->DefaultTrack(fEntry, tracker);
}

void BaseADMListEntry::Notify(IADMNotifier notifier)
{
	sADMListEntry->DefaultNotify(fEntry, notifier);
}



/*
 * Static Procs that call Virtual Functions.
 */
	
ASErr ASAPI BaseADMListEntry::InitProc(ADMListEntryRef entry)
{
	BaseADMListEntry* admEntry = (BaseADMListEntry*) sADMListEntry->GetUserData(entry);
	
	admEntry->fEntry = entry;

	if (admEntry)
		return admEntry->Init();
	else
		return kBadParameterErr;
}

void ASAPI BaseADMListEntry::DrawProc(ADMListEntryRef entry, ADMDrawerRef drawer)
{
	BaseADMListEntry* admEntry = (BaseADMListEntry*) sADMListEntry->GetUserData(entry);
	
	if (admEntry)
		admEntry->BaseDraw(drawer);
}

ASBoolean ASAPI BaseADMListEntry::TrackProc(ADMListEntryRef entry, ADMTrackerRef tracker)
{
	BaseADMListEntry* admEntry = (BaseADMListEntry*) sADMListEntry->GetUserData(entry);
	
	if (admEntry)
		return admEntry->Track(tracker);
	else
		return false;
}

void ASAPI BaseADMListEntry::NotifyProc(ADMListEntryRef entry, ADMNotifierRef notifier)
{
	BaseADMListEntry* admEntry = (BaseADMListEntry*) sADMListEntry->GetUserData(entry);
	
	if (admEntry)
		admEntry->Notify(notifier);
}

void ASAPI BaseADMListEntry::DestroyProc(ADMListEntryRef entry)
{
	BaseADMListEntry* admEntry = (BaseADMListEntry*) sADMListEntry->GetUserData(entry);
	
	if (admEntry)
		delete admEntry;
}


void BaseADMListEntry::BaseDraw(IADMDrawer drawer)
{
	Draw(drawer);
}
