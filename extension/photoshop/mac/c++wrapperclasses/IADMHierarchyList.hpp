/***********************************************************************/
/*                                                                     */
/* IADMHierarchyList.hpp                                               */
/* Object wrapper for ADM Hierarchy List Suite                         */
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

#ifndef __IADMHierarchyList_hpp__
#define __IADMHierarchyList_hpp__

/*
 * Includes
 */
 
#ifndef __ADMHierarchyList__
#include "ADMHierarchyList.h"
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

extern "C" ADMHierarchyListSuite2* sADMHierarchyList;


/*
 * Interface Wrapper Class
 */

class IADMHierarchyList
{
protected:
	ADMHierarchyListRef fList;

public:	
	IADMHierarchyList();
	IADMHierarchyList(ADMHierarchyListRef list);
	IADMHierarchyList(int nilList);

	operator ADMHierarchyListRef(void);
		
	void SetMenuID(SPPluginRef menuResPlugin, int menuResID, char* menuResName);
	int GetMenuID();
	
	ADMItemRef GetItem();
	
	void SetEntryWidth(int width);
	void SetEntryWidthRecursive(int width);
	int GetEntryWidth();
	int GetNonLeafEntryWidth();
	
	void SetEntryHeight(int height);
	void SetEntryHeightRecursive(int height);
	int GetEntryHeight();
	
	void SetEntryTextRect(const IASRect& rect);
	void SetEntryTextRectRecursive(const IASRect& rect);
	void GetEntryTextRect(IASRect& rect);

	void SetNonLeafEntryTextRect(const IASRect& rect);
	void SetNonLeafEntryTextRectRecursive(const IASRect& rect);
	void GetNonLeafEntryTextRect(IASRect& rect);
	
	ADMListEntryRef InsertEntry(int index);
	void RemoveEntry(int index);
	
	ADMListEntryRef GetEntry(int entryID);
	
	ADMListEntryRef IndexEntry(int index);
	
	ADMListEntryRef FindEntry(const char* text);
	
	ADMListEntryRef PickEntry(const ADMPoint& point);
	ADMListEntryRef PickLeafEntry(const ADMPoint& point);
	
	ADMListEntryRef GetActiveEntry();
	ADMListEntryRef GetActiveLeafEntry();
	
	int NumberOfEntries();
	
	// Number of selected entries in the current hierarchical level
	int NumberOfSelectedEntries();

	// Number of all selected entries in the hierarchy.
	// If b is a's child, and both are selected, then both will count.
	int NumberOfAllSelectedEntriesInHierarchy();

	// If b is a's child, and both are selected, only a will count.
	int NumberOfUnNestedSelectedEntriesInHierarchy();

	// Find the selected entry in the current hierarchical level
	// Correspond to NumberOfSelectedEntries().
	ADMListEntryRef IndexSelectedEntry(int selectionIndex);

	// Find the selected entry in the entire hierarchy.
	// Correspond to NumberOfAllSelectedEntriesInHierarchy().
	ADMListEntryRef IndexAllSelectedEntriesInHierarchy(int selectionIndex);
	
	// Correspond to NumberOfUnNestedSelectedEntriesInHierarchy().
	ADMListEntryRef IndexUnNestedSelectedEntriesInHierarchy(int selectionIndex);
	
	void SetMask(ADMActionMask mask);
	void SetMaskRecursive(ADMActionMask mask);
	ADMActionMask GetMask();

	void SetNotifierData(ADMUserData data);
	ADMUserData GetNotifierData();

	ADMListEntryRef GetParentEntry();
	void GetLocalRect(IASRect& rect);

	void LocalToScreenPoint(IASPoint& point);
	void ScreenToLocalPoint(IASPoint& point);

	void LocalToGlobalPoint(IASPoint& point);
	void GlobalToLocalPoint(IASPoint& point);

	void LocalToGlobalRect(IASRect& rect);
	void GlobalToLocalRect(IASRect& rect);

	void SetIndentationWidth(int width);
	void SetIndentationWidthRecursive(int width);
	int GetIndentationWidth();

	void SetLocalLeftMargin(int margin);
	int GetLocalLeftMargin();
	int GetGlobalLeftMargin();

	void SetDivided(ASBoolean divided);
	void SetDividedRecursive(ASBoolean divided);
	ASBoolean GetDivided();

	void SetFlags(int flags);
	void SetFlagsRecursive(int flags);
	ASBoolean GetFlags();

	void Invalidate();

	int GetLeafIndex(ADMListEntryRef entry);
	ADMListEntryRef IndexLeafEntry( int index );
	int NumberOfLeafEntries();

	void SwapEntries( int ifrom, int ito );
	ADMListEntryRef InsertEntry(ADMListEntryRef entry, int index);

	ADMListEntryRef UnlinkEntry(int index);


	void SetInitProc(ADMListEntryInitProc initProc);
	void SetInitProcRecursive(ADMListEntryInitProc initProc);
	ADMListEntryInitProc GetInitProc();

	void SetDrawProc(ADMListEntryDrawProc drawProc);
	void SetDrawProcRecursive(ADMListEntryDrawProc drawProc);
	ADMListEntryDrawProc GetDrawProc();

	void SetTrackProc(ADMListEntryTrackProc trackProc);
	void SetTrackProcRecursive(ADMListEntryTrackProc trackProc);
	ADMListEntryTrackProc GetTrackProc();

	void SetNotifyProc(ADMListEntryNotifyProc notifyProc);
	void SetNotifyProcRecursive(ADMListEntryNotifyProc notifyProc);
	ADMListEntryNotifyProc GetNotifyProc();

	void SetDestroyProc(ADMListEntryDestroyProc destroyProc);
	void SetDestroyProcRecursive(ADMListEntryDestroyProc destroyProc);
	ADMListEntryDestroyProc GetDestroyProc();

	void DeselectAll();
};

inline IADMHierarchyList::IADMHierarchyList()								
{
	fList = NULL;
}

inline IADMHierarchyList::IADMHierarchyList(ADMHierarchyListRef list)	
{
	fList = list;
}

inline IADMHierarchyList::IADMHierarchyList(int)
{
	fList = NULL;
}

inline IADMHierarchyList::operator ADMHierarchyListRef(void)
{
	return fList;
}

inline void IADMHierarchyList::SetMenuID(SPPluginRef menuResPlugin, int menuResID, char* menuResName)
{
	sADMHierarchyList->SetMenuID(fList, menuResPlugin, menuResID, menuResName);
}

inline int IADMHierarchyList::GetMenuID()
{
	return sADMHierarchyList->GetMenuID(fList);
}

inline ADMItemRef IADMHierarchyList::GetItem()
{
	return sADMHierarchyList->GetItem(fList);
}

inline void IADMHierarchyList::SetEntryWidth(int width)
{
	sADMHierarchyList->SetEntryWidth(fList, width);
}

inline void IADMHierarchyList::SetEntryWidthRecursive(int width)
{
	sADMHierarchyList->SetEntryWidthRecursive(fList, width);
}

inline int IADMHierarchyList::GetEntryWidth()
{
	return sADMHierarchyList->GetEntryWidth(fList);
}

inline int IADMHierarchyList::GetNonLeafEntryWidth()
{
	return sADMHierarchyList->GetNonLeafEntryWidth(fList);
}

inline void IADMHierarchyList::SetEntryHeight(int height)
{
	sADMHierarchyList->SetEntryHeight(fList, height);
}

inline void IADMHierarchyList::SetEntryHeightRecursive(int height)
{
	sADMHierarchyList->SetEntryHeightRecursive(fList, height);
}

inline int IADMHierarchyList::GetEntryHeight()
{
	return sADMHierarchyList->GetEntryHeight(fList);
}

inline void IADMHierarchyList::SetEntryTextRect(const IASRect& rect)
{
	sADMHierarchyList->SetEntryTextRect(fList, &rect);
}

inline void IADMHierarchyList::SetEntryTextRectRecursive(const IASRect& rect)
{
	sADMHierarchyList->SetEntryTextRectRecursive(fList, &rect);
}

inline void IADMHierarchyList::GetEntryTextRect(IASRect& rect)
{
	sADMHierarchyList->GetEntryTextRect(fList, &rect);
}
		
inline void IADMHierarchyList::SetNonLeafEntryTextRect(const IASRect& rect)
{
	sADMHierarchyList->SetNonLeafEntryTextRect(fList, &rect);
}

inline void IADMHierarchyList::SetNonLeafEntryTextRectRecursive(const IASRect& rect)
{
	sADMHierarchyList->SetNonLeafEntryTextRectRecursive(fList, &rect);
}

inline void IADMHierarchyList::GetNonLeafEntryTextRect(IASRect& rect)
{
	sADMHierarchyList->GetNonLeafEntryTextRect(fList, &rect);
}

inline ADMListEntryRef IADMHierarchyList::InsertEntry(int index)
{
	return sADMHierarchyList->InsertEntry(fList, index);
}

inline void IADMHierarchyList::RemoveEntry(int index)
{
	sADMHierarchyList->RemoveEntry(fList, index);
}

inline ADMListEntryRef IADMHierarchyList::GetEntry(int entryID)
{
	return sADMHierarchyList->GetEntry(fList, entryID);
}

inline ADMListEntryRef IADMHierarchyList::IndexEntry(int index)
{
	return sADMHierarchyList->IndexEntry(fList, index);
}

inline ADMListEntryRef IADMHierarchyList::FindEntry(const char* text)
{
	return sADMHierarchyList->FindEntry(fList, text);
}

inline ADMListEntryRef IADMHierarchyList::PickEntry(const ADMPoint& point)
{
	return sADMHierarchyList->PickEntry(fList, &point);
}

inline ADMListEntryRef IADMHierarchyList::PickLeafEntry(const ADMPoint& point)
{
	return sADMHierarchyList->PickLeafEntry(fList, &point);
}

inline ADMListEntryRef IADMHierarchyList::GetActiveEntry()
{
	return sADMHierarchyList->GetActiveEntry(fList);
}

inline ADMListEntryRef IADMHierarchyList::GetActiveLeafEntry()
{
	return sADMHierarchyList->GetActiveLeafEntry(fList);
}

inline int IADMHierarchyList::NumberOfEntries()
{
	return sADMHierarchyList->NumberOfEntries(fList);
}

inline int IADMHierarchyList::NumberOfSelectedEntries()
{
	return sADMHierarchyList->NumberOfSelectedEntries(fList);
}

inline int IADMHierarchyList::NumberOfAllSelectedEntriesInHierarchy()
{
	return sADMHierarchyList->NumberOfAllSelectedEntriesInHierarchy(fList);
}

inline int IADMHierarchyList::NumberOfUnNestedSelectedEntriesInHierarchy()
{
	return sADMHierarchyList->NumberOfUnNestedSelectedEntriesInHierarchy(fList);
}

inline ADMListEntryRef IADMHierarchyList::IndexSelectedEntry(int selectionIndex)
{
	return sADMHierarchyList->IndexSelectedEntry(fList, selectionIndex);
}

inline ADMListEntryRef IADMHierarchyList::IndexAllSelectedEntriesInHierarchy(int selectionIndex)
{
	return sADMHierarchyList->IndexAllSelectedEntriesInHierarchy(fList, selectionIndex);
}

inline ADMListEntryRef IADMHierarchyList::IndexUnNestedSelectedEntriesInHierarchy(int selectionIndex)
{
	return sADMHierarchyList->IndexUnNestedSelectedEntriesInHierarchy(fList, selectionIndex);
}

inline void IADMHierarchyList::SetMask(ADMActionMask mask)
{
	sADMHierarchyList->SetMask(fList, mask);
}

inline void IADMHierarchyList::SetMaskRecursive(ADMActionMask mask)
{
	sADMHierarchyList->SetMaskRecursive(fList, mask);
}

inline ADMActionMask IADMHierarchyList::GetMask()
{
	return sADMHierarchyList->GetMask(fList);
}

inline void IADMHierarchyList::SetNotifierData(ADMUserData data)
{
	sADMHierarchyList->SetNotifierData(fList, data);
}

inline ADMUserData IADMHierarchyList::GetNotifierData()
{
	return sADMHierarchyList->GetNotifierData(fList);
}

inline ADMListEntryRef IADMHierarchyList::GetParentEntry()
{
	return sADMHierarchyList->GetParentEntry(fList);
}

inline void IADMHierarchyList::GetLocalRect(IASRect& rect)
{
	sADMHierarchyList->GetLocalRect(fList, &rect);
}

inline void IADMHierarchyList::LocalToScreenPoint(IASPoint& point)
{
	sADMHierarchyList->LocalToScreenPoint(fList, &point);
}

inline void IADMHierarchyList::ScreenToLocalPoint(IASPoint& point)
{
	sADMHierarchyList->ScreenToLocalPoint(fList, &point);
}

inline void IADMHierarchyList::LocalToGlobalPoint(IASPoint& point)
{
	sADMHierarchyList->LocalToGlobalPoint(fList, &point);
}

inline void IADMHierarchyList::GlobalToLocalPoint(IASPoint& point)
{
	sADMHierarchyList->GlobalToLocalPoint(fList, &point);
}

inline void IADMHierarchyList::LocalToGlobalRect(IASRect& rect)
{
	sADMHierarchyList->LocalToGlobalRect(fList, &rect);
}

inline void IADMHierarchyList::GlobalToLocalRect(IASRect& rect)
{
	sADMHierarchyList->GlobalToLocalRect(fList, &rect);
}

inline void IADMHierarchyList::SetIndentationWidth(int width)
{
	sADMHierarchyList->SetIndentationWidth(fList, width);
}

inline void IADMHierarchyList::SetIndentationWidthRecursive(int width)
{
	sADMHierarchyList->SetIndentationWidthRecursive(fList, width);
}

inline int IADMHierarchyList::GetIndentationWidth()
{
	return sADMHierarchyList->GetIndentationWidth(fList);
}

inline void IADMHierarchyList::SetLocalLeftMargin(int margin)
{
	sADMHierarchyList->SetLocalLeftMargin(fList, margin);
}

inline int IADMHierarchyList::GetLocalLeftMargin()
{
	return sADMHierarchyList->GetLocalLeftMargin(fList);
}

inline int IADMHierarchyList::GetGlobalLeftMargin()
{
	return sADMHierarchyList->GetGlobalLeftMargin(fList);
}

inline void IADMHierarchyList::SetDivided(ASBoolean divided)
{
	sADMHierarchyList->SetDivided(fList, divided);
}

inline void IADMHierarchyList::SetDividedRecursive(ASBoolean divided)
{
	sADMHierarchyList->SetDividedRecursive(fList, divided);
}

inline ASBoolean IADMHierarchyList::GetDivided()
{
	return sADMHierarchyList->GetDivided(fList);
}

inline void IADMHierarchyList::SetFlags(int flags)
{
	sADMHierarchyList->SetFlags(fList, flags);
}

inline void IADMHierarchyList::SetFlagsRecursive(int flags)
{
	sADMHierarchyList->SetFlagsRecursive(fList, flags);
}

inline ASBoolean IADMHierarchyList::GetFlags()
{
	return sADMHierarchyList->GetFlags(fList);
}

inline void IADMHierarchyList::Invalidate()
{
	sADMHierarchyList->Invalidate(fList);
}

inline int IADMHierarchyList::GetLeafIndex(ADMListEntryRef entry)
{
	return sADMHierarchyList->GetLeafIndex( fList, entry );
}

inline ADMListEntryRef IADMHierarchyList::IndexLeafEntry( int index )
{
	return sADMHierarchyList->IndexLeafEntry( fList, index );
}

inline int IADMHierarchyList::NumberOfLeafEntries()
{
	return sADMHierarchyList->NumberOfLeafEntries( fList );
}

inline void IADMHierarchyList::SwapEntries( int ifrom, int ito )
{
	sADMHierarchyList->SwapEntries( fList, ifrom, ito );
}

inline ADMListEntryRef IADMHierarchyList::InsertEntry( ADMListEntryRef entry, int index )
{
	return sADMHierarchyList->InsertGivenEntry( fList, entry, index );
}

inline ADMListEntryRef IADMHierarchyList::UnlinkEntry( int index)
{
	return sADMHierarchyList->UnlinkEntry( fList, index );
}

inline void IADMHierarchyList::SetInitProc(ADMListEntryInitProc initProc)
{
	sADMHierarchyList->SetInitProc(fList, initProc);
}

inline void IADMHierarchyList::SetInitProcRecursive(ADMListEntryInitProc initProc)
{
	sADMHierarchyList->SetInitProcRecursive(fList, initProc);
}

inline ADMListEntryInitProc IADMHierarchyList::GetInitProc()
{
	return sADMHierarchyList->GetInitProc(fList);
}

inline void IADMHierarchyList::SetDrawProc(ADMListEntryDrawProc drawProc)
{
	sADMHierarchyList->SetDrawProc(fList, drawProc);
}

inline void IADMHierarchyList::SetDrawProcRecursive(ADMListEntryDrawProc drawProc)
{
	sADMHierarchyList->SetDrawProcRecursive(fList, drawProc);
}

inline ADMListEntryDrawProc IADMHierarchyList::GetDrawProc()
{
	return sADMHierarchyList->GetDrawProc(fList);
}

inline void IADMHierarchyList::SetTrackProc(ADMListEntryTrackProc trackProc)
{
	sADMHierarchyList->SetTrackProc(fList, trackProc);
}

inline void IADMHierarchyList::SetTrackProcRecursive(ADMListEntryTrackProc trackProc)
{
	sADMHierarchyList->SetTrackProcRecursive(fList, trackProc);
}

inline ADMListEntryTrackProc IADMHierarchyList::GetTrackProc()
{
	return sADMHierarchyList->GetTrackProc(fList);
}

inline void IADMHierarchyList::SetNotifyProc(ADMListEntryNotifyProc notifyProc)
{
	sADMHierarchyList->SetNotifyProc(fList, notifyProc);
}

inline void IADMHierarchyList::SetNotifyProcRecursive(ADMListEntryNotifyProc notifyProc)
{
	sADMHierarchyList->SetNotifyProcRecursive(fList, notifyProc);
}

inline ADMListEntryNotifyProc IADMHierarchyList::GetNotifyProc()
{
	return sADMHierarchyList->GetNotifyProc(fList);
}

inline void IADMHierarchyList::SetDestroyProc(ADMListEntryDestroyProc destroyProc)
{
	sADMHierarchyList->SetDestroyProc(fList, destroyProc);
}

inline void IADMHierarchyList::SetDestroyProcRecursive(ADMListEntryDestroyProc destroyProc)
{
	sADMHierarchyList->SetDestroyProc(fList, destroyProc);
}

inline ADMListEntryDestroyProc IADMHierarchyList::GetDestroyProc()
{
	return sADMHierarchyList->GetDestroyProc(fList);
}

inline void IADMHierarchyList::DeselectAll()
{
	sADMHierarchyList->DeselectAll(fList);
}


#endif
