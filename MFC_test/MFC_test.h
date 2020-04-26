
// MFC_test.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCtestApp:
// See MFC_test.cpp for the implementation of this class
//

class CMFCtestApp : public CWinApp
{
public:
	CMFCtestApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCtestApp theApp;
