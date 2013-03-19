/***********************************************************************/
/*                                                                     */
/* IADMDialog.hpp                                                      */
/* Object wrapper for ADM Dialog Suite                                 */
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
/* Started by Dave Lazarony, 07/07/1998                                */
/*                                                                     */
/***********************************************************************/

#ifndef __IADMDialog_hpp__
#define __IADMDialog_hpp__

/*
 * Includes
 */
 
#ifndef __ADMDialog__
#include "ADMDialog.h"
#endif

#ifndef __IASTypes_hpp__
#include "IASTypes.hpp"
#endif

#ifdef USING_ZADM
	#ifndef __ZADM__
	#include "ZADM.h"
	#endif
#endif

// Stupid Macintosh Headers #define GetItem.
#ifdef GetItem
#undef GetItem
#endif


/*
 * Global Suite Pointer
 */

extern "C" ADMDialogSuite5* sADMDialog;

#ifdef USING_ZADM
extern "C" ZADMSuite* sZADM;
#endif


/*
 * Interface Wrapper Class
 */

class IADMDialog
{
protected:
	ADMDialogRef fDialog;
	
public:	
	IADMDialog();
	IADMDialog(ADMDialogRef dialog);
	IADMDialog(int nilDialog);
	
	operator ADMDialogRef(void);
	
	ADMDialogRef GetDialogRef(void);
	void SetDialogRef(ADMDialogRef);
	
	void SendNotify(const char* notifierType = NULL);
	void DefaultNotify(ADMNotifierRef notifier);
	
	int GetID();
	SPPluginRef GetPluginRef();
	ASWindowRef GetWindowRef();

	const char* GetName();
	
	void SetDialogStyle(ADMDialogStyle style);
	ADMDialogStyle GetDialogStyle();
	
	void Show(ASBoolean show = true);
	void Hide();
	ASBoolean IsVisible();
	
	void Enable(ASBoolean enable = true);
	void Disable();
	ASBoolean IsEnabled();
	
	void Activate(ASBoolean activate = true);
	void Deactivate();
	ASBoolean IsActive();
	
	void SetLocalRect(const IASRect& localRect);
	void GetLocalRect(IASRect& localRect);
	
	void SetBoundsRect(const IASRect& boundsRect);
	void GetBoundsRect(IASRect& boundsRect);
	
	void Move(int x, int y);
	void Size(int width, int height);
	
	void LocalToScreenPoint(IASPoint& point);
	void ScreenToLocalPoint(IASPoint& point);
	
	void LocalToScreenRect(IASRect& rect);
	void ScreenToLocalRect(IASRect& rect);
	
	void Invalidate();
	void Update();
	
	void SetCursorID(int cursorResID);
	int GetCursorID();

	void GetCursorID(SPPluginRef* plugin, ASInt32* cursorResID);

	ADMFont GetFont();
	void SetFont(ADMFont font);
	
#ifdef USING_ZADM
	void SetText(const ASZString text);
	void GetText(ASZString* text);
#else
	void SetText(const char* text);
	void GetText(char* text, int maxLength = 0);
#endif
	int GetTextLength();
	
	void SetMinWidth(int width);
	int GetMinWidth();
	
	void SetMinHeight(int height);
	int GetMinHeight();
	
	void SetMaxWidth(int width);
	int GetMaxWidth();
	
	void SetMaxHeight(int height);
	int GetMaxHeight();
	
	void SetHorizontalIncrement(int height);
	int GetHorizontalIncrement();
	
	void SetVerticalIncrement(int height);
	int GetVerticalIncrement();
	
	ADMItemRef GetItem(int itemID);
	
	ADMItemRef CreateItem(int itemID, ADMItemType itemType, const IASRect& boundsRect, ADMItemInitProc initProc = NULL, ADMUserData data = 0, int options = 0);
	void DestroyItem(ADMItemRef item);
	
	ADMItemRef GetNextItem(ADMItemRef item);
	ADMItemRef GetPreviousItem(ADMItemRef item);

	void SetDefaultItemID(int itemID);
	int GetDefaultItemID();
	void SetCancelItemID(int itemID);
	int GetCancelItemID();
	
	void EndModal(int modalResultID, ASBoolean cancelling = false);

	void LoadToolTips(int stringID);
/*
	void SetHelpID(ASHelpID helpID);
	ASHelpID GetHelpID();
	void Help();
*/
	void SetMask(ADMActionMask mask);
	ADMActionMask GetMask();

	void SetNotifierData(ADMUserData data);
	ADMUserData GetNotifierData();

	ADMTimerRef CreateTimer(unsigned long milliseconds,
							ADMActionMask abortMask,
							ADMDialogTimerProc timerProc,
							ADMDialogTimerAbortProc abortProc,
							int options = 0);

	void AbortTimer(ADMTimerRef timer);

	ASBoolean IsCollapsed();
};


inline IADMDialog::IADMDialog()								
{
	fDialog = NULL;
}

inline IADMDialog::IADMDialog(ADMDialogRef dialog)	
{
	fDialog = dialog;
}

inline IADMDialog::IADMDialog(int)
{
	fDialog = NULL;
}

inline IADMDialog::operator ADMDialogRef(void)
{
	return fDialog;
}

inline ADMDialogRef IADMDialog::GetDialogRef(void)
{
	return fDialog;
}

inline void IADMDialog::SetDialogRef(ADMDialogRef dialog)
{
	fDialog = dialog;
}


inline void IADMDialog::SendNotify(const char* notifierType)
{
	sADMDialog->SendNotify(fDialog, notifierType);
}

inline void IADMDialog::DefaultNotify(ADMNotifierRef notifier)
{
	sADMDialog->DefaultNotify(fDialog, notifier);
}

inline int IADMDialog::GetID()
{
	return sADMDialog->GetID(fDialog);
}

inline struct SPPlugin* IADMDialog::GetPluginRef()
{
	return sADMDialog->GetPluginRef(fDialog);
}

inline ASWindowRef IADMDialog::GetWindowRef()
{
	return sADMDialog->GetWindowRef(fDialog);
}


inline const char* IADMDialog::GetName()
{
	return sADMDialog->GetDialogName(fDialog);
}


inline void IADMDialog::SetDialogStyle(ADMDialogStyle style)
{
	sADMDialog->SetDialogStyle(fDialog, style);
}

inline ADMDialogStyle IADMDialog::GetDialogStyle()
{
	return sADMDialog->GetDialogStyle(fDialog);
}

inline void IADMDialog::Show(ASBoolean show)
{
	sADMDialog->Show(fDialog, show);
}

inline void IADMDialog::Hide()
{
	sADMDialog->Show(fDialog, false);
}

inline ASBoolean IADMDialog::IsVisible()
{
	return sADMDialog->IsVisible(fDialog);
}

inline void IADMDialog::Enable(ASBoolean enable)
{
	sADMDialog->Enable(fDialog, enable);
}

inline void IADMDialog::Disable()
{
	sADMDialog->Enable(fDialog, false);
}

inline ASBoolean IADMDialog::IsEnabled()
{
	return sADMDialog->IsEnabled(fDialog);
}

inline void IADMDialog::Activate(ASBoolean activate)
{
	sADMDialog->Activate(fDialog, activate);
}

inline void IADMDialog::Deactivate()
{
	sADMDialog->Activate(fDialog, false);
}

inline ASBoolean IADMDialog::IsActive()
{
	return sADMDialog->IsActive(fDialog);
}

inline void IADMDialog::SetLocalRect(const IASRect& localRect)
{
	sADMDialog->SetLocalRect(fDialog, &localRect);
}

inline void IADMDialog::GetLocalRect(IASRect& localRect)
{
	sADMDialog->GetLocalRect(fDialog, &localRect);
}

inline void IADMDialog::SetBoundsRect(const IASRect& boundsRect)
{
	sADMDialog->SetBoundsRect(fDialog, &boundsRect);
}

inline void IADMDialog::GetBoundsRect(IASRect& boundsRect)
{
	sADMDialog->GetBoundsRect(fDialog, &boundsRect);
}

inline void IADMDialog::Move(int x, int y)
{
	sADMDialog->Move(fDialog, x, y);
}

inline void IADMDialog::Size(int width, int height)
{
	sADMDialog->Size(fDialog, width, height);
}

inline void IADMDialog::LocalToScreenPoint(IASPoint& point)
{
	sADMDialog->LocalToScreenPoint(fDialog, &point);
}

inline void IADMDialog::ScreenToLocalPoint(IASPoint& point)
{
	sADMDialog->ScreenToLocalPoint(fDialog, &point);
}

inline void IADMDialog::LocalToScreenRect(IASRect& rect)
{
	sADMDialog->LocalToScreenRect(fDialog, &rect);
}

inline void IADMDialog::ScreenToLocalRect(IASRect& rect)
{
	sADMDialog->ScreenToLocalRect(fDialog, &rect);
}
		
inline void IADMDialog::Invalidate()
{
	sADMDialog->Invalidate(fDialog);
}

inline void IADMDialog::Update()
{
	sADMDialog->Update(fDialog);
}



inline void IADMDialog::SetCursorID(int cursorResID)
{
	sADMDialog->SetCursorID(fDialog, sADMDialog->GetPluginRef(fDialog), cursorResID);
}

inline int IADMDialog::GetCursorID()
{
	ASInt32 cursorID = 0;
	SPPluginRef itsPlugin;
	sADMDialog->GetCursorID(fDialog, &itsPlugin, &cursorID);
	return cursorID;
}

inline void IADMDialog::GetCursorID(SPPluginRef* plugin, ASInt32* cursorResID)
{
	*cursorResID = 0;
	sADMDialog->GetCursorID(fDialog, plugin, cursorResID);
}

inline ADMFont IADMDialog::GetFont()
{
	return sADMDialog->GetFont(fDialog);
}

inline void IADMDialog::SetFont(ADMFont font)
{
	sADMDialog->SetFont(fDialog, font);
}
	
#ifdef USING_ZADM
inline void IADMDialog::SetText( const ASZString text )
{
	sZADM->DialogSetText( fDialog, const_cast< ASZString >( text ) );
}
#else
inline void IADMDialog::SetText(const char* text)
{
	sADMDialog->SetText(fDialog, text);
}
#endif

#ifdef USING_ZADM
inline void IADMDialog::GetText( ASZString* text )
{
	sZADM->DialogGetText( fDialog, text );
}
#else
inline void IADMDialog::GetText(char* text, int maxLength)
{
	sADMDialog->GetText(fDialog, text, maxLength);
}
#endif

inline int IADMDialog::GetTextLength()
{
	return sADMDialog->GetTextLength(fDialog);
}

inline void IADMDialog::SetMinWidth(int width)
{
	sADMDialog->SetMinWidth(fDialog, width);
}

inline int IADMDialog::GetMinWidth()
{
	return sADMDialog->GetMinWidth(fDialog);
}

inline void IADMDialog::SetMinHeight(int height)
{
	sADMDialog->SetMinHeight(fDialog, height);
}

inline int IADMDialog::GetMinHeight()
{
	return sADMDialog->GetMinHeight(fDialog);
}

inline void IADMDialog::SetMaxWidth(int width)
{
	sADMDialog->SetMaxWidth(fDialog, width);
}

inline int IADMDialog::GetMaxWidth()
{
	return sADMDialog->GetMaxWidth(fDialog);
}

inline void IADMDialog::SetMaxHeight(int height)
{
	sADMDialog->SetMaxHeight(fDialog, height);
}

inline int IADMDialog::GetMaxHeight()
{
	return sADMDialog->GetMaxHeight(fDialog);
}

inline void IADMDialog::SetHorizontalIncrement(int increment)
{
	sADMDialog->SetHorizontalIncrement(fDialog, increment);
}

inline int IADMDialog::GetHorizontalIncrement()
{
	return sADMDialog->GetHorizontalIncrement(fDialog);
}

inline void IADMDialog::SetVerticalIncrement(int increment)
{
	sADMDialog->SetVerticalIncrement(fDialog, increment);
}

inline int IADMDialog::GetVerticalIncrement()
{
	return sADMDialog->GetVerticalIncrement(fDialog);
}

inline ADMItemRef IADMDialog::GetItem(int itemID)
{
	return sADMDialog->GetItem(fDialog, itemID);
}

inline ADMItemRef IADMDialog::CreateItem(int itemID, ADMItemType itemType, const IASRect& boundsRect, ADMItemInitProc initProc, ADMUserData data, int options)
{
	return sADMDialog->CreateItem(fDialog, itemID, itemType, &boundsRect, initProc, data, options);
}

inline void IADMDialog::DestroyItem(ADMItemRef item)	
{
	sADMDialog->DestroyItem(fDialog, item);
}

inline ADMItemRef IADMDialog::GetNextItem(ADMItemRef item)
{
	return sADMDialog->GetNextItem(fDialog, item);
}

inline ADMItemRef IADMDialog::GetPreviousItem(ADMItemRef item)
{
	return sADMDialog->GetPreviousItem(fDialog, item);
}

inline void IADMDialog::SetDefaultItemID(int itemID)
{
	sADMDialog->SetDefaultItemID(fDialog, itemID);
}

inline int IADMDialog::GetDefaultItemID()
{
	return sADMDialog->GetDefaultItemID(fDialog);
}

inline void IADMDialog::SetCancelItemID(int itemID)
{
	sADMDialog->SetCancelItemID(fDialog, itemID);
}

inline int IADMDialog::GetCancelItemID()
{
	return sADMDialog->GetCancelItemID(fDialog);
}

inline void IADMDialog::EndModal(int modalResultID, ASBoolean cancelling)
{
	sADMDialog->EndModal(fDialog, modalResultID, cancelling);
}
	
inline void IADMDialog::LoadToolTips(int stringID)
{
	sADMDialog->LoadToolTips(fDialog, stringID);
}
/*
inline void IADMDialog::SetHelpID(ASHelpID helpID)
{
	sADMDialog->SetHelpID(fDialog, helpID);
}

inline ASHelpID IADMDialog::GetHelpID()
{
	return sADMDialog->GetHelpID(fDialog);
}

inline void IADMDialog::Help()
{
	sADMDialog->Help(fDialog);
}
*/
inline void IADMDialog::SetMask(ADMActionMask mask)
{
	sADMDialog->SetMask(fDialog, mask);
}

inline ADMActionMask IADMDialog::GetMask()
{
	return sADMDialog->GetMask(fDialog);
}

inline void IADMDialog::SetNotifierData(ADMUserData data)
{
	sADMDialog->SetNotifierData(fDialog, data);
}

inline ADMUserData IADMDialog::GetNotifierData()
{
	return sADMDialog->GetNotifierData(fDialog);
}

inline ADMTimerRef IADMDialog::CreateTimer(unsigned long milliseconds,
		ADMActionMask abortMask, ADMDialogTimerProc timerProc,
		ADMDialogTimerAbortProc abortProc, int options)
{
	return sADMDialog->CreateTimer(fDialog, milliseconds,
		abortMask, timerProc, abortProc, options);
}

inline void IADMDialog::AbortTimer(ADMTimerRef timer)
{
	sADMDialog->AbortTimer(fDialog, timer);
}

inline ASBoolean IADMDialog::IsCollapsed()
{
	return sADMDialog->IsCollapsed(fDialog);
}

#endif
