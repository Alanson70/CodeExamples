// fnc_scale.h : main header file for the fnc_scale DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// Cfnc_scaleApp
// See fnc_scale.cpp for the implementation of this class
//

class Cfnc_scaleApp : public CWinApp
{
public:
	Cfnc_scaleApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
