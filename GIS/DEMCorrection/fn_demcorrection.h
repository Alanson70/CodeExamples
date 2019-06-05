// fn_demcorrection.h : main header file for the fn_demcorrection DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#include "DFI.h"

#define DLLEXPORT  _declspec(dllexport)

// Cfn_demcorrectionApp
// See fn_demcorrection.cpp for the implementation of this class
//

class Cfn_demcorrectionApp : public CWinApp
{
public:
	Cfn_demcorrectionApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
