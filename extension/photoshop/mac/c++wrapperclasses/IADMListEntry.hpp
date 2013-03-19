/***********************************************************************/
/*                                                                     */
/* IADMListEntry.hpp                                                   */
/* Object wrapper for ADM List Entry Suite                             */
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
/* Started by Wei Huang, 07/07/1998                                    */
/*                                                                     */
/***********************************************************************/

#ifndef __IADMListEntry_hpp__
#define __IADMListEntry_hpp__

/*
 * Includes
 */
 
#ifndef __ADMListEntry__
#include "ADMListEntry.h" 
#endif

#ifndef __IASTypes_hpp__
#include "IASTypes.hpp"
#endif

#ifdef USING_ZADM
	#ifndef __ZADM__
	#include "ZADM.h"
	#endif
#endif


/*
 * Global Suite Pointer
 */

extern "C" ADMListEntrySuite* sADMListEntry;

#ifdef USING_ZADM
extern "C" ZADMSuite* sZADM;
#endif


/*
 * Interface Wrapper Class
 */

class IADMListEntry
{
protected:
	ADMListEntryRef fEntry;

public:	
	IADMListEntry();
	IADMListEntry(ADMListEntryRef entry);
	IADMListEntry(int nilEntry);

	operator ADMListEntryRef(void);
		
	void SendNotify(const char* notifierType = NULL);
	
	int GetIndex();
	
	ADMItemRef GetItem();

	ADMHierarchyListRef GetList();
	
	ADMHierarchyListRef GetChildList();

	ADMHierarchyListRef CreateChildList();
	void DeleteChildList();

	void ExpandHierarchy(ASBoolean flag);
	ASBoolean IsHierarchyExpanded();

	void HideEntryName(ASBoolean flag);
	ASBoolean IsEntryNameHidden();

	void EnableChildSelection(ASBoolean flag);
	ASBoolean IsChildSelectable();

	int GetHierarchyDepth();
	int GetVisualHierarchyDepth();

	void SetID(int entryID);
	int GetID();
	
	void SetUserData(ADMUserData data);
	ADMUserData GetUserData();

	void Select(ASBoolean show = true);
	void Deselect();
	ASBoolean IsSelected();
	ASBoolean IsChildrenSelected();

	void MakeInBounds();
	ASBoolean IsInBounds();
	
	void Enable(ASBoolean enable = true);
	void Disable();
	ASBoolean IsEnabled();
	
	void Activate(ASBoolean activate = true);
	void Deactivate();
	ASBoolean IsActive();
	
	void Check(ASBoolean check = true);
	void Uncheck();
	ASBoolean IsChecked();
	
	void MakeSeparator(ASBoolean separator);
	ASBoolean IsSeparator();

	void GetLocalRect(IASRect& localRect);
	
	void GetExpandArrowLocalRect(IASRect& expandArrowLocalRect);

	void GetBoundsRect(IASRect& boundsRect);
	
	void LocalToScreenPoint(IASPoint& point);
	void ScreenToLocalPoint(IASPoint& point);
	
	void LocalToScreenRect(IASRect& rect);
	void ScreenToLocalRect(IASRect& rect);
	
	void Invalidate();
	void Update();
	
	void SetPictureID(int pictureResID);
	int GetPictureID();
	
	void SetSelectedPictureID(int pictureResID);
	int GetSelectedPictureID();
	
	void SetDisabledPictureID(int pictureResID);
	int GetDisabledPictureID();

#ifdef USING_ZADM
	void SetText( const ASZString text);
	void GetText( ASZString* text );
#else	
	void SetText(const char* text);
	void GetText(char* text, int maxLength = 0);
#endif
	int GetTextLength();

	ADMTimerRef CreateTimer(unsigned long milliseconds,
							ADMActionMask abortMask,
							ADMListEntryTimerProc timerProc,
							ADMListEntryTimerAbortProc abortProc);

	void AbortTimer(ADMTimerRef timer);
};

inline IADMListEntry::IADMListEntry()								
{
	fEntry = NULL;
}

inline IADMListEntry::IADMListEntry(ADMListEntryRef entry)	
{
	fEntry = entry;
}

inline IADMListEntry::IADMListEntry(int)
{
	fEntry = NULL;
}

inline IADMListEntry::operator ADMListEntryRef(void)
{
	return fEntry;
}

inline void IADMListEntry::SendNotify(const char* notifierType)
{
	sADMListEntry->SendNotify(fEntry, notifierType);
}
	
inline int IADMListEntry::GetIndex()
{
	return sADMListEntry->GetIndex(fEntry);
}

inline ADMItemRef IADMListEntry::GetItem()
{
	return sADMListEntry->GetItem(fEntry);
}

inline ADMHierarchyListRef IADMListEntry::GetList()
{
	return sADMListEntry->GetList(fEntry);
}

inline ADMHierarchyListRef IADMListEntry::GetChildList()
{
	return sADMListEntry->GetChildList(fEntry);
}

inline ADMHierarchyListRef IADMListEntry::CreateChildList()
{
	return sADMListEntry->CreateChildList(fEntry);
}

inline void IADMListEntry::DeleteChildList()
{
	sADMListEntry->DeleteChildList(fEntry);
}

inline void IADMListEntry::ExpandHierarchy(ASBoolean flag)
{
	sADMListEntry->ExpandHierarchy(fEntry, flag);
}

inline ASBoolean IADMListEntry::IsHierarchyExpanded()
{
	return sADMListEntry->IsHierarchyExpanded(fEntry);
}

inline void IADMListEntry::HideEntryName(ASBoolean flag)
{
	sADMListEntry->HideEntryName(fEntry, flag);
}

inline ASBoolean IADMListEntry::IsEntryNameHidden()
{
	return sADMListEntry->IsEntryNameHidden(fEntry);
}

inline void IADMListEntry::EnableChildSelection(ASBoolean flag)
{
	sADMListEntry->EnableChildSelection(fEntry, flag);
}

inline ASBoolean IADMListEntry::IsChildSelectable()
{
	return sADMListEntry->IsChildSelectable(fEntry);
}

inline int IADMListEntry::GetHierarchyDepth()
{
	return sADMListEntry->GetHierarchyDepth(fEntry);
}

inline int IADMListEntry::GetVisualHierarchyDepth()
{
	return sADMListEntry->GetVisualHierarchyDepth(fEntry);
}

inline void IADMListEntry::SetID(int entryID)
{
	sADMListEntry->SetID(fEntry, entryID);
}

inline int IADMListEntry::GetID()
{
	return sADMListEntry->GetID(fEntry);
}

inline void IADMListEntry::SetUserData(ADMUserData data)
{
	sADMListEntry->SetUserData(fEntry, data);
}

inline ADMUserData IADMListEntry::GetUserData()
{
	return sADMListEntry->GetUserData(fEntry);
}

inline void IADMListEntry::Select(ASBoolean show)
{
	sADMListEntry->Select(fEntry, show);
}

inline void IADMListEntry::Deselect()
{
	sADMListEntry->Select(fEntry, false);
}

inline ASBoolean IADMListEntry::IsSelected()
{
	return sADMListEntry->IsSelected(fEntry);
}

inline ASBoolean IADMListEntry::IsChildrenSelected()
{
	return sADMListEntry->AreChildrenSelected(fEntry);
}

inline void IADMListEntry::MakeInBounds()
{
	sADMListEntry->MakeInBounds(fEntry);
}

inline ASBoolean IADMListEntry::IsInBounds()
{
	return sADMListEntry->IsInBounds(fEntry);
}

inline void IADMListEntry::Enable(ASBoolean enable)
{
	sADMListEntry->Enable(fEntry, enable);
}

inline void IADMListEntry::Disable()
{
	sADMListEntry->Enable(fEntry, false);
}

inline ASBoolean IADMListEntry::IsEnabled()
{
	return sADMListEntry->IsEnabled(fEntry);
}

inline void IADMListEntry::Activate(ASBoolean activate)
{
	sADMListEntry->Activate(fEntry, activate);
}

inline void IADMListEntry::Deactivate()
{
	sADMListEntry->Activate(fEntry, false);
}

inline ASBoolean IADMListEntry::IsActive()
{
	return sADMListEntry->IsActive(fEntry);
}

inline void IADMListEntry::Check(ASBoolean check)
{
	sADMListEntry->Check(fEntry, check);
}

inline void IADMListEntry::Uncheck()
{
	sADMListEntry->Check(fEntry, false);
}

inline ASBoolean IADMListEntry::IsChecked()
{
	return sADMListEntry->IsChecked(fEntry);
}

inline void IADMListEntry::MakeSeparator(ASBoolean separator)
{
	sADMListEntry->MakeSeparator(fEntry, separator);
}

inline ASBoolean IADMListEntry::IsSeparator()
{
	return sADMListEntry->IsSeparator(fEntry);
}

inline void IADMListEntry::GetLocalRect(IASRect& localRect)
{
	sADMListEntry->GetLocalRect(fEntry, &localRect);
}

inline void IADMListEntry::GetExpandArrowLocalRect(IASRect& expandArrowLocalRect)
{
	sADMListEntry->GetExpandArrowLocalRect(fEntry, &expandArrowLocalRect);
}

inline void IADMListEntry::GetBoundsRect(IASRect& boundsRect)
{
	sADMListEntry->GetBoundsRect(fEntry, &boundsRect);
}

inline void IADMListEntry::LocalToScreenPoint(IASPoint& point)
{
	sADMListEntry->LocalToScreenPoint(fEntry, &point);
}

inline void IADMListEntry::ScreenToLocalPoint(IASPoint& point)
{
	sADMListEntry->ScreenToLocalPoint(fEntry, &point);
}

inline void IADMListEntry::LocalToScreenRect(IASRect& rect)
{
	sADMListEntry->LocalToScreenRect(fEntry, &rect);
}

inline void IADMListEntry::ScreenToLocalRect(IASRect& rect)
{
	sADMListEntry->ScreenToLocalRect(fEntry, &rect);
}

inline void IADMListEntry::Invalidate()
{
	sADMListEntry->Invalidate(fEntry);
}

inline void IADMListEntry::Update()
{
	sADMListEntry->Update(fEntry);
}

inline void IADMListEntry::SetPictureID(int pictureResID)
{
	sADMListEntry->SetPictureID(fEntry, pictureResID);
}

inline int IADMListEntry::GetPictureID()
{
	return sADMListEntry->GetPictureID(fEntry);
}

inline void IADMListEntry::SetSelectedPictureID(int pictureResID)
{
	sADMListEntry->SetSelectedPictureID(fEntry, pictureResID);
}

inline int IADMListEntry::GetSelectedPictureID()
{
	return sADMListEntry->GetSelectedPictureID(fEntry);
}

inline void IADMListEntry::SetDisabledPictureID(int pictureResID)
{
	sADMListEntry->SetDisabledPictureID(fEntry, pictureResID);
}

inline int IADMListEntry::GetDisabledPictureID()
{
	return sADMListEntry->GetDisabledPictureID(fEntry);
}

#ifdef USING_ZADM
inline void IADMListEntry::SetText( const ASZString text )
{
	sZADM->ListEntrySetText( fEntry, const_cast< ASZString >( text ) );
}
#else
inline void IADMListEntry::SetText(const char* text)
{
	sADMListEntry->SetText(fEntry, text);
}
#endif

#ifdef USING_ZADM
inline void IADMListEntry::GetText( ASZString* text )
{
	sZADM->ListEntryGetText( fEntry, text );
}
#else
inline void IADMListEntry::GetText(char* text, int maxLength)
{
	sADMListEntry->GetText(fEntry, text, maxLength);
}
#endif

inline int IADMListEntry::GetTextLength()
{
	return sADMListEntry->GetTextLength(fEntry);
}


inline ADMTimerRef IADMListEntry::CreateTimer(unsigned long milliseconds,
		ADMActionMask abortMask, ADMListEntryTimerProc timerProc,
		ADMListEntryTimerAbortProc abortProc)
{
	return sADMListEntry->CreateTimer(fEntry, milliseconds,
		abortMask, timerProc, abortProc);
}

inline void IADMListEntry::AbortTimer(ADMTimerRef timer)
{
	sADMListEntry->AbortTimer(fEntry, timer);
}

#endif
