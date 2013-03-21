// libNNT.h : main header file for the libNNT DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// ClibNNTApp
// See libNNT.cpp for the implementation of this class
//

class ClibNNTApp : public CWinApp
{
public:
	ClibNNTApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
