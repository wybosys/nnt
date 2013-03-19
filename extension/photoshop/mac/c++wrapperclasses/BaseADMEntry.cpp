/***********************************************************************/
/*                                                                     */
/* BaseADMEntry.cpp                                                    */
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

#include "BaseADMEntry.hpp"
#include "IADMDrawer.hpp"
#include "IADMNotifier.hpp"
#include "IADMTracker.hpp"
#include "IADMList.hpp"
#include "IADMItem.hpp"

/*
 * Constructor
 */

BaseADMEntry::BaseADMEntry(IADMEntry entry, ADMUserData data)
: IADMEntry(entry),
  fUserData(data),
  fList(GetList())
{
	if (fEntry && fList)
	{
		sADMEntry->SetUserData(fEntry, this);
		sADMList->SetDrawProc(fList, DrawProc);
		sADMList->SetTrackProc(fList, TrackProc);
		sADMList->SetNotifyProc(fList, NotifyProc);
		sADMList->SetDestroyProc(fList, DestroyProc);
	}
}

BaseADMEntry::BaseADMEntry(IADMList list, ADMUserData entryUserData)
: IADMEntry((ADMEntryRef) NULL),
  fUserData(entryUserData),
  fList(list)
{
	if (fList){
		fEntry = sADMEntry->Create( fList );

		if (fEntry)
		{
			sADMEntry->SetUserData(fEntry, this);
			sADMList->SetDrawProc(fList, DrawProc);
			sADMList->SetTrackProc(fList, TrackProc);
			sADMList->SetNotifyProc(fList, NotifyProc);
			sADMList->SetDestroyProc(fList, DestroyProc);
		}
	}
}

/*
 * Destructor
 */

BaseADMEntry::~BaseADMEntry()
{
	if (sADMEntry)
	{
		SetUserData(NULL);

		/* We can't do this since other entries depend on these
		   procs.

		sADMList->SetDrawProc(fList, NULL);
		sADMList->SetTrackProc(fList, NULL);
		sADMList->SetNotifyProc(fList, NULL);
		sADMList->SetDestroyProc(fList, NULL);
		*/

		sADMEntry->Destroy(*this);
	}
			
//	fEntry = NULL;
}


ADMEntryRef BaseADMEntry::Create(ADMListRef list, ADMUserData data)								
{
	fList = list;
	fUserData = data;

	if (fList)
	{
		fEntry = sADMEntry->Create( fList );

		if (fEntry)
		{
			SetUserData(this);
			sADMList->SetDrawProc(fList, DrawProc);
			sADMList->SetTrackProc(fList, TrackProc);
			sADMList->SetNotifyProc(fList, NotifyProc);
			sADMList->SetDestroyProc(fList, DestroyProc);
		}
	}

	return fEntry;	
}


/*
 * Virtual Functions that call Defaults.
 */
	
ASErr BaseADMEntry::Init()
{
	return kNoErr;
}

void BaseADMEntry::Draw(IADMDrawer drawer)
{
	sADMEntry->DefaultDraw(fEntry, drawer);
}

ASBoolean BaseADMEntry::Track(IADMTracker tracker)
{
	return 	sADMEntry->DefaultTrack(fEntry, tracker);
}

void BaseADMEntry::Notify(IADMNotifier notifier)
{
	sADMEntry->DefaultNotify(fEntry, notifier);
}



/*
 * Static Procs that call Virtual Functions.
 */
	
ASErr ASAPI BaseADMEntry::InitProc(ADMEntryRef entry)
{
	BaseADMEntry* admEntry = (BaseADMEntry*) sADMEntry->GetUserData(entry);
	
	admEntry->fEntry = entry;

	if (admEntry)
		return admEntry->Init();
	else
		return kBadParameterErr;
}

void ASAPI BaseADMEntry::DrawProc(ADMEntryRef entry, ADMDrawerRef drawer)
{
	BaseADMEntry* admEntry = (BaseADMEntry*) sADMEntry->GetUserData(entry);
	
	if (admEntry)
		admEntry->BaseDraw(drawer);
}

ASBoolean ASAPI BaseADMEntry::TrackProc(ADMEntryRef entry, ADMTrackerRef tracker)
{
	BaseADMEntry* admEntry = (BaseADMEntry*) sADMEntry->GetUserData(entry);
	
	if (admEntry)
		return admEntry->Track(tracker);
	else
		return false;
}

void ASAPI BaseADMEntry::NotifyProc(ADMEntryRef entry, ADMNotifierRef notifier)
{
	BaseADMEntry* admEntry = (BaseADMEntry*) sADMEntry->GetUserData(entry);
	
	if (admEntry)
		admEntry->Notify(notifier);
}

void ASAPI BaseADMEntry::DestroyProc(ADMEntryRef entry)
{
	BaseADMEntry* admEntry = (BaseADMEntry*) sADMEntry->GetUserData(entry);
	
	if (admEntry)
		delete admEntry;
}


void BaseADMEntry::BaseDraw(IADMDrawer drawer)
{
	Draw(drawer);
}

