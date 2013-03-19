// libwsi.h : main header file for the libwsi DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// ClibwsiApp
// See libwsi.cpp for the implementation of this class
//

class ClibwsiApp : public CWinApp
{
public:
	ClibwsiApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
