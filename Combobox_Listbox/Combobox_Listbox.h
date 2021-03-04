
// Combobox_Listbox.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CComboboxListboxApp:
// See Combobox_Listbox.cpp for the implementation of this class
//

class CComboboxListboxApp : public CWinApp
{
public:
	CComboboxListboxApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CComboboxListboxApp theApp;
