/***********************************************************************/
/*                                                                     */
/* BaseADMDialog.hpp                                                   */
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

#ifndef __BaseADMDialog_hpp__
#define __BaseADMDialog_hpp__

/*
 * Includes
 */
 
#ifndef __IADMDialog_hpp__
#include "IADMDialog.hpp"
#endif

#ifndef __IADMItem_hpp__
#include "IADMItem.hpp"
#endif

class IADMDrawer;
class IADMNotifier;
class IADMTracker;


/*
 * Base Class
 */

class BaseADMDialog : public IADMDialog
{
private:
	static ASErr ASAPI InitProc(ADMDialogRef dialog);
	static void ASAPI DrawProc(ADMDialogRef dialog, ADMDrawerRef drawer);
	static ASBoolean ASAPI TrackProc(ADMDialogRef dialog, ADMTrackerRef tracker);
	static void ASAPI NotifyProc(ADMDialogRef dialog, ADMNotifierRef notifier);
	static void ASAPI DestroyProc(ADMDialogRef dialog);

	ASBoolean fIsModal;

protected:
	ADMUserData fUserData;
	
	virtual ASErr Init();
	virtual void Draw(IADMDrawer drawer);
	virtual ASBoolean Track(IADMTracker tracker);
	virtual void Notify(IADMNotifier notifier);
	virtual void Destroy();
	
public:
	BaseADMDialog();
	
	virtual ~BaseADMDialog();	
	
	virtual ADMDialogRef Create(SPPluginRef pluginRef, char* name, int dialogID, ADMDialogStyle style, int options = 0);
	virtual int Modal(SPPluginRef pluginRef, char* name, int dialogID, ADMDialogStyle style = kADMModalDialogStyle, int options = 0);
	
	void SetUserData(ADMUserData userData);
	ADMUserData GetUserData();
	
	IADMDialog GetDialog();
};

	
inline void BaseADMDialog::SetUserData(ADMUserData userData)
{
	fUserData = userData;
}

inline ADMUserData BaseADMDialog::GetUserData()
{
	return fUserData;
}

inline IADMDialog BaseADMDialog::GetDialog()
{
	return IADMDialog::GetDialogRef(); //fDialog;
}


#endif
