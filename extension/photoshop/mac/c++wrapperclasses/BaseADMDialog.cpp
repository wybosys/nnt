/***********************************************************************/
/*                                                                     */
/* BaseADMDialog.cpp                                                   */
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

#include "BaseADMDialog.hpp"
#include "IADMDrawer.hpp"
#include "IADMItem.hpp"
#include "IADMNotifier.hpp"
#include "IADMTracker.hpp"

/*
 * Constructor
 */
 
BaseADMDialog::BaseADMDialog()	
: IADMDialog()							
{
	fDialog = NULL;
	fUserData = NULL;
	fIsModal = false;
}


/*
 * Destructor
 */

BaseADMDialog::~BaseADMDialog()
{
	if (fDialog && !fIsModal)
	{
		/*
		 * Because Destroy() will try to call use through the Destroy Proc
		 * we first have to remove ourselves from the ADM dialog so we cannot be 
		 * called again.
		 */
		sADMDialog->SetUserData(fDialog, NULL);
		sADMDialog->SetDrawProc(fDialog, NULL);
		sADMDialog->SetNotifyProc(fDialog, NULL);
		sADMDialog->SetDestroyProc(fDialog, NULL);
		
		/*
		 * Destroy the ADM dialog.
		 */	
		sADMDialog->Destroy(fDialog);
		
		fDialog = NULL;
	}
}

ADMDialogRef BaseADMDialog::Create(SPPluginRef pluginRef, char* name, int dialogID, ADMDialogStyle style, int options)								
{
	fDialog = sADMDialog->Create(pluginRef, name, dialogID, style, InitProc, this, options);
	
	return fDialog;	
}


int BaseADMDialog::Modal(SPPluginRef pluginRef, char* name, int dialogID, ADMDialogStyle style, int options)								
{
	fIsModal = true;

	int result = sADMDialog->Modal(pluginRef, name, dialogID, style, InitProc, this, options);

	// Used to set fDialog to NULL here, but the destroy method (below) deletes the dialog,
	// so it's gone by this point.
	
	return result;
}


/*
 * Virtual Functions that call Defaults.
 */
	
ASErr BaseADMDialog::Init()
{
	sADMDialog->SetDrawProc(fDialog, DrawProc);
	sADMDialog->SetTrackProc(fDialog, TrackProc);
	sADMDialog->SetNotifyProc(fDialog, NotifyProc);
	sADMDialog->SetDestroyProc(fDialog, DestroyProc);

	return kNoErr;
}

void BaseADMDialog::Draw(IADMDrawer drawer)
{
	sADMDialog->DefaultDraw(fDialog, drawer);
}

ASBoolean BaseADMDialog::Track(IADMTracker tracker)
{
	return sADMDialog->DefaultTrack(fDialog, tracker);
}

void BaseADMDialog::Notify(IADMNotifier notifier)
{
	sADMDialog->DefaultNotify(fDialog, notifier);
}

void BaseADMDialog::Destroy()
{
}

/*
 * Static Procs that call Virtual Functions.
 */
	
ASErr ASAPI BaseADMDialog::InitProc(ADMDialogRef dialog)
{
	BaseADMDialog* admDialog = (BaseADMDialog*) sADMDialog->GetUserData(dialog);
	
	admDialog->fDialog = dialog;
	
	if (admDialog)
		return admDialog->Init();
	else
		return kBadParameterErr;
}

void ASAPI BaseADMDialog::DrawProc(ADMDialogRef dialog, ADMDrawerRef drawer)
{
	BaseADMDialog* admDialog = (BaseADMDialog*) sADMDialog->GetUserData(dialog);
	
	if (admDialog)
		admDialog->Draw(drawer);
}

ASBoolean ASAPI BaseADMDialog::TrackProc(ADMDialogRef dialog, ADMTrackerRef tracker)
{
	BaseADMDialog* admDialog = (BaseADMDialog*) sADMDialog->GetUserData(dialog);
	
	if (admDialog)
		return admDialog->Track(tracker);
	else
		return false;
}

void ASAPI BaseADMDialog::NotifyProc(ADMDialogRef dialog, ADMNotifierRef notifier)
{
	BaseADMDialog* admDialog = (BaseADMDialog*) sADMDialog->GetUserData(dialog);
	
	if (admDialog)
		admDialog->Notify(notifier);
}

void ASAPI BaseADMDialog::DestroyProc(ADMDialogRef dialog)
{
	BaseADMDialog* admDialog = (BaseADMDialog*) sADMDialog->GetUserData(dialog);
	
	if (admDialog) {

		admDialog->Destroy();

		if (admDialog->fIsModal)
		{
			// If it is a modal dialog, we just want to set fDialog to NULL
			// so we don't try to reference through it in the BaseADMDialog destructor.
			// The dialog (inside ADM) is deleted right after the destroy proc. is called.
			// If we don't set it to NULL here we're hosed...
			// dtomack 1/16/98
			admDialog->fDialog = NULL;
		}
		else
		{
			delete admDialog;
		}
	}
}
