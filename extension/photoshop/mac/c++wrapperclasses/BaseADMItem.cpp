/***********************************************************************/
/*                                                                     */
/* BaseADMItem.cpp                                                     */
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
/* Started by Dave Lazarony, 03/11/1996                                */
/*                                                                     */
/***********************************************************************/

/*
 * Includes
 */

#include "BaseADMItem.hpp"
#include "IADMDrawer.hpp"
#include "IADMNotifier.hpp"
#include "IADMTracker.hpp"

/*
 * Constructor
 */

BaseADMItem::BaseADMItem(IADMItem item, ADMUserData data)	
: IADMItem(item)							
{
	fUserData = data;

	if (fItem)
	{
		sADMItem->SetUserData(fItem, this);
		sADMItem->SetDrawProc(fItem, DrawProc);
		sADMItem->SetTrackProc(fItem, TrackProc);
		sADMItem->SetNotifyProc(fItem, NotifyProc);
		sADMItem->SetDestroyProc(fItem, DestroyProc);
		sADMItem->SetTextToFloatProc(fItem, TextToFloatProc);
		sADMItem->SetFloatToTextProc(fItem, FloatToTextProc);
	}
}


/*
 * Destructor
 */

BaseADMItem::~BaseADMItem()
{
	if (sADMItem)
	{
		sADMItem->SetUserData(fItem, NULL);
			
		sADMItem->SetUserData(fItem, NULL);
		sADMItem->SetDrawProc(fItem, NULL);
		sADMItem->SetNotifyProc(fItem, NULL);
		sADMItem->SetDestroyProc(fItem, NULL);
		sADMItem->SetTextToFloatProc(fItem, NULL);
		sADMItem->SetFloatToTextProc(fItem, NULL);
		
		sADMItem->Destroy(fItem);
	}
			
	fItem = NULL;
}


ADMItemRef BaseADMItem::Create(ADMDialogRef dialog, const IASRect& boundsRect, ADMItemType itemType, int itemID)								
{
	fItem = sADMItem->Create(dialog, itemID, itemType, &boundsRect, InitProc, this);
	
	if (fItem)
	{
		sADMItem->SetDrawProc(fItem, DrawProc);
		sADMItem->SetTrackProc(fItem, TrackProc);
		sADMItem->SetNotifyProc(fItem, NotifyProc);
		sADMItem->SetDestroyProc(fItem, DestroyProc);
		sADMItem->SetTextToFloatProc(fItem, TextToFloatProc);
		sADMItem->SetFloatToTextProc(fItem, FloatToTextProc);
	}

	return fItem;	
}


/*
 * Virtual Functions that call Defaults.
 */
	
ASErr BaseADMItem::Init()
{
	return kNoErr;
}

void BaseADMItem::Draw(IADMDrawer drawer)
{
	sADMItem->DefaultDraw(fItem, drawer);
}

ASBoolean BaseADMItem::Track(IADMTracker tracker)
{
	return sADMItem->DefaultTrack(fItem, tracker);
}

void BaseADMItem::Notify(IADMNotifier notifier)
{
	sADMItem->DefaultNotify(fItem, notifier);
}

ASBoolean BaseADMItem::TextToFloat(const char* text, float& value)
{
	return sADMItem->DefaultTextToFloat(fItem, text, &value);
}

ASBoolean BaseADMItem::FloatToText(float value, char* text, int textLength)
{
	return sADMItem->DefaultFloatToText(fItem, value, text, textLength);
}


/*
 * Static Procs that call Virtual Functions.
 */
	
ASErr ASAPI BaseADMItem::InitProc(ADMItemRef item)
{
	BaseADMItem* admItem = (BaseADMItem*) sADMItem->GetUserData(item);
	
	admItem->fItem = item;

	if (admItem)
		return admItem->Init();
	else
		return kBadParameterErr;
}

void ASAPI BaseADMItem::DrawProc(ADMItemRef item, ADMDrawerRef drawer)
{
	BaseADMItem* admItem = (BaseADMItem*) sADMItem->GetUserData(item);
	
	if (admItem)
		admItem->BaseDraw(drawer);
}

ASBoolean ASAPI BaseADMItem::TrackProc(ADMItemRef item, ADMTrackerRef tracker)
{
	BaseADMItem* admItem = (BaseADMItem*) sADMItem->GetUserData(item);
	
	if (admItem)
		return admItem->Track(tracker);
	else
		return false;
}

void ASAPI BaseADMItem::NotifyProc(ADMItemRef item, ADMNotifierRef notifier)
{
	BaseADMItem* admItem = (BaseADMItem*) sADMItem->GetUserData(item);
	
	if (admItem)
		admItem->Notify(notifier);
}

void ASAPI BaseADMItem::DestroyProc(ADMItemRef item)
{
	BaseADMItem* admItem = (BaseADMItem*) sADMItem->GetUserData(item);
	
	if (admItem)
		delete admItem;
}

ASBoolean ASAPI BaseADMItem::TextToFloatProc(ADMItemRef item, const char* text, float* value)
{
	BaseADMItem* admItem = (BaseADMItem*) sADMItem->GetUserData(item);
	
	if (admItem)
		return admItem->TextToFloat(text,* value);
	else
		return false;
}

ASBoolean ASAPI BaseADMItem::FloatToTextProc(ADMItemRef item, float value, char* text, long textLength)
{
	BaseADMItem* admItem = (BaseADMItem*) sADMItem->GetUserData(item);
	
	if (admItem)
		return admItem->FloatToText(value, text, textLength);
	else
		return false;
}

void BaseADMItem::BaseDraw(IADMDrawer drawer)
{
	Draw(drawer);
}
