// fn_demcorrection.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "fn_demcorrection.h"
#include "demcorrection.h"
#include "resource.h"
#include "ArgsDemcorrection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// Cfn_demcorrectionApp

BEGIN_MESSAGE_MAP(Cfn_demcorrectionApp, CWinApp)
END_MESSAGE_MAP()


// Cfn_demcorrectionApp construction

Cfn_demcorrectionApp::Cfn_demcorrectionApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only Cfn_demcorrectionApp object

Cfn_demcorrectionApp theApp;


// Cfn_demcorrectionApp initialization

BOOL Cfn_demcorrectionApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
BOOL DLLEXPORT CALLCONV IC_Identify( CDFI* pDfi, IC_IDENTIFY *pIdentify )
{
	static IC_IDENTIFY s_Identify = {
			FANCY_ID,
			FANCY_VER,
			IC_FUNCTION_ID,
			_T("demcorrection")
		};

  	 memcpy(pIdentify, &s_Identify, sizeof(IC_IDENTIFY));

return TRUE;
}
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
BOOL DLLEXPORT CALLCONV IC_IdentifyFunction( CDFI* pDfi, IC_FUNCTIONS_IDENTIFY* pFunctionsIdentify )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString str;
	HINSTANCE hInstance;
	IC_FUNCTION_IDENTIFY funcIdentify;
	int iCount = 0;

	hInstance = AfxGetInstanceHandle();

	///// Set number functions in DLL
	pFunctionsIdentify->NumFunctions = 0;

	//////////////////////////////////////////////////////////////////////////////////////
	//// Set 0 function param
	memset( &funcIdentify, 0, sizeof(IC_FUNCTION_IDENTIFY) );

	///  menu and  toolbar
	_tcscpy_s( funcIdentify.Name, IC_MAX_FUNCTION_NAME, _T("demcorrection") );
	LoadString( hInstance, IDS_DEMCORRECTION, funcIdentify.Description, IC_MAX_FUNCTION_NAME - 1 );
	LoadString( hInstance, IDS_MENU_DEMCORRECTION, funcIdentify.Menu, IC_MAX_FUNCTION_MENU - 1 );
	funcIdentify.fnStyle = FNSTYLE_CHECK; 
	funcIdentify.fnState = FNSTATE_ENABLED;
	funcIdentify.fnType = FUNCTION_TYPE_COMPLETE;//FUNCTION_TYPE_DEFAULT | FUNCTION_TYPE_MACROS;//
	funcIdentify.pWndProc = DEMCorrectionProc;
	funcIdentify.pFunction = DEMCorrection;
	funcIdentify.pCheckFunction = NULL;
	funcIdentify.pUpdateFunction = UpdateDEMCorrection;
	funcIdentify.SizeOfProcInfo = sizeof(DEM_DATA);
	funcIdentify.pCreateArgs = CreateArgsDemcorrection;

	funcIdentify.iEdition = EDITION_ENTERPRISE;

	memmove( &pFunctionsIdentify->function[iCount], &funcIdentify, sizeof(IC_FUNCTION_IDENTIFY)  );
	++iCount;

	///// Set number functions in DLL
	pFunctionsIdentify->NumFunctions = iCount;

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////