// fnc_scale.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "fnc_scale.h"
#include "scale.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
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

// Cfnc_scaleApp

BEGIN_MESSAGE_MAP(Cfnc_scaleApp, CWinApp)
END_MESSAGE_MAP()


// Cfnc_scaleApp construction

Cfnc_scaleApp::Cfnc_scaleApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only Cfnc_scaleApp object

Cfnc_scaleApp theApp;


// Cfnc_scaleApp initialization

BOOL Cfnc_scaleApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

BOOL _IC_DFINTERFACE CALLCONV IC_Identify(CDFI* pDfi, IC_IDENTIFY *pIdentify)
{
   //AFX_MANAGE_STATE(AfxGetStaticModuleState());

static IC_IDENTIFY s_Identify = {
	     FANCY_ID,
	     FANCY_VER,
	     IC_FUNCTION_ID,
	     _T("Editions image functions")
};

  memcpy( pIdentify,&s_Identify,sizeof( IC_IDENTIFY ) );

return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////




BOOL _IC_DFINTERFACE CALLCONV  IC_IdentifyFunction( CDFI *pDfi, IC_FUNCTIONS_IDENTIFY* pFunctionsIdentify )
{
AFX_MANAGE_STATE(AfxGetStaticModuleState());

CString   str;
HINSTANCE hInstance;
IC_FUNCTION_IDENTIFY  funcIdentify;

	     hInstance = AfxGetInstanceHandle( );

		 ///// Set number functions in DLL
         pFunctionsIdentify->NumFunctions = 1;
		 //////////////////////////////////////////////////////////////////////////////////////
#ifndef PANEL_IS_OPTIONAL 
		 //////////////////////////////////////////////////////////////////////////////////////
		//// Set 0-st function paramm		 
		 memset( &funcIdentify, 0, sizeof(IC_FUNCTION_IDENTIFY) );
		 _tcscpy_s( funcIdentify.Name, IC_MAX_FUNCTION_NAME, _T("ScalePanel") );
		 LoadString( hInstance, IDS_FUNCTION_DEFAULT, funcIdentify.Description, IC_MAX_FUNCTION_NAME - 1 );
		 /// Menu and  toolbar
		 LoadString( hInstance, IDS_MENU, funcIdentify.Menu, IC_MAX_FUNCTION_MENU - 1 );
		 LoadString( hInstance, IDS_TOOLBAR, funcIdentify.ToolBarName, IC_MAX_FUNCTION_MENU - 1 );
		 funcIdentify.BitmapID= IDB_SCALE;

		 funcIdentify.fnStyle = FNSTYLE_CHECK;//GROUP;
		 funcIdentify.fnState = FNSTATE_ENABLED;// | FNSTATE_CHECKED | FNSTATE_PRESSED;
		 funcIdentify.fnType = FUNCTION_TYPE_DEFAULT;
		 
		 funcIdentify.pFunction = ScaleFunction;
		 funcIdentify.pUpdateFunction = UpdateScaleFunction;
		 funcIdentify.pCheckFunction = NULL;
		 funcIdentify.pWndProc = ScaleWindowProc;//ScaleDialogWindowProc;
		 funcIdentify.SizeOfProcInfo = sizeof(SCALE_DATA);

		 funcIdentify.iEdition = EDITION_LIGHT;

		 memcpy( &pFunctionsIdentify->function[ 0 ], &funcIdentify, sizeof(IC_FUNCTION_IDENTIFY)  );

#else
		//// Set 0-st function paramm		 
		 memset( &funcIdentify, 0, sizeof(IC_FUNCTION_IDENTIFY) );
		 _tcscpy_s( funcIdentify.Name, IC_MAX_FUNCTION_NAME, _T("ScalePanel") );
		 LoadString( hInstance, IDS_FUNCTION_DEFAULT, funcIdentify.Description, IC_MAX_FUNCTION_NAME - 1 );
		 /// Menu and  toolbar
		 LoadString( hInstance, IDS_MENU, funcIdentify.Menu, IC_MAX_FUNCTION_MENU - 1 );
		 LoadString( hInstance, IDS_TOOLBAR, funcIdentify.ToolBarName, IC_MAX_FUNCTION_MENU - 1 );
		 funcIdentify.BitmapID= IDB_SCALE;

		 funcIdentify.fnStyle = FNSTYLE_CHECKGROUP;
		 funcIdentify.fnState = FNSTATE_ENABLED;// | FNSTATE_CHECKED | FNSTATE_PRESSED;
		 funcIdentify.fnType = FUNCTION_TYPE_DEFAULT;
		 
		 funcIdentify.pFunction = ScaleFunction;
		 funcIdentify.pUpdateFunction = UpdateScaleFunction;
		 funcIdentify.pCheckFunction = NULL;
		 funcIdentify.pWndProc = WindowProc;//ScaleDialogWindowProc;
		 funcIdentify.SizeOfProcInfo = sizeof(SCALE_DATA);

		 funcIdentify.iEdition = EDITION_LIGHT;

		 memcpy( &pFunctionsIdentify->function[ 0 ], &funcIdentify, sizeof(IC_FUNCTION_IDENTIFY)  );
#endif
		 //////////////////////////////////////////////////////////////////////////////////////
		 //////////////////////////////////////////////////////////////////////////////////////
		

		 //////////////////////////////////////////////////////////////////////////////////////
		 //////////////////////////////////////////////////////////////////////////////////////
		 //////////////////////////////////////////////////////////////////////////////////////
		
return TRUE;
}
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
