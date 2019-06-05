#include "StdAfx.h"
#include "VectorInfo.h"
#include "dfi_vectorobjectstream.h"
#include "dfi_OverDraw.h"
#include "dfi_View.h"
#include "dfi_Layer.h"
#include "VectorInfoDialog.h"
#include "resource.h"

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////
CString GetResourceString(UINT resID)
{
	HINSTANCE  hInstance = AfxGetStaticModuleState()->m_hCurrentResourceHandle;
	CString str;
	str.LoadString( hInstance, resID);
	return str;
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////






////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

VECTOR_INFO_DATA* GetVectorInfoFunctionData( CDFI* pDfi )
{
IC_FUNCTION_IDENTIFY fi;
VECTOR_INFO_DATA* pData = NULL;
int ifindex;

	if ( pDfi )
		if( pDfi->GetMainFrame() )
		{				  
			ifindex = pDfi->GetApp()->GetFncFunctions()->GetFuncIndex( (void *)VectorInfo );	 	                     
			if ( ifindex > -1 )	 
			{
				pDfi->GetApp()->GetFncFunctions()->GetFunctionInfo( ifindex, &fi );
				pData = (VECTOR_INFO_DATA*)fi.pProcInfo;
			}
		}
	
	return pData;
}




/////////////////////////////////////////////////////////////////////////////////
// clear old prameters
void AttrTest(CString & wsItem, CString &sSection, Cdfi_Attributes *pAttributes, bool bWrite)
{
	if (bWrite) return;
	CString str;
	Cdfi_AttributeValue *attr, *attrNext;

	if (pAttributes->FindAttribute(sSection, wsItem) == FALSE)
	{
		attr = pAttributes->GetFirstItem();
		while (attr)
		{
			attrNext = pAttributes->GetNextItem(attr);

			str = attr->GetSectionName();
			if (str.Find(sSection, 0) >= 0)
				pAttributes->Remove(attr->GetName());
			attr = attrNext;
		};

	}
}
////////////////////////////



////////////////////////////////////////////////////////
void Attr(BOOL &value,   CString &str, CString &sSection,Cdfi_Attributes *pAttributes,bool bWrite )
{	
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );
	//CString str;
	//str = s;

	AttrTest(str, sSection, pAttributes, bWrite);

	if (!pAttributes->FindAttribute(sSection, str) )
		pAttributes->Add( sSection, str, ATTRIBUTE_TYPE_CHECKBUTTON, 0,0  )->SetBool( value, FALSE );//ATTRIBUTE_NO_REMOVE
	
	if(!bWrite)
		value = pAttributes->Item( sSection, str )->GetBool();
	else
		pAttributes->Item( sSection, str )->SetBool( value, FALSE);		
}

///////////////////////////////////////////////////

void Attr(long &value, CString &s, CString &sSection, Cdfi_Attributes *pAttributes, bool bWrite )
{
	CString str;
	str = s;

	AttrTest(str, sSection, pAttributes, bWrite);
				
	if (!pAttributes->FindAttribute(sSection, str) ) 
		pAttributes->Add( sSection, str, ATTRIBUTE_TYPE_INT	, 0, 0 )->SetInt( (int)value, FALSE );
	if(!bWrite)
		value = pAttributes->Item( sSection, str )->GetInt();
	else
		pAttributes->Item( sSection, str )->SetInt( value, FALSE);
	
}


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
bool VectorInfo( CDFI* pDfi, IC_PARAM *pParam )
{
AFX_MANAGE_STATE( AfxGetStaticModuleState() );

VECTOR_INFO_DATA *pData = NULL;
Cdfi_Document *pDoc = NULL;

	pData = GetVectorInfoFunctionData( pDfi );
	
	//// Check function type
	if ( pParam )
	{
		if ( ( pParam->message != FM_DEFAULT )&&(pParam->message != FM_DESTROY_ALL)&&( pParam->message != FM_END_FUNCTION ) )
			return false;

		if(pParam->message == FM_DESTROY_ALL)
			if ( pData->pDialog == NULL )
				return true;
	}
	////////////////////////////////////////

	if (pData->pDialog)
	{
		int id = pDfi->GetApp()->GetFncFunctions()->GetFunctionID( VectorInfo );
		
		if( pParam->FunctionID == id )
		{
			if(pParam->message == FM_END_FUNCTION || pParam->message == FM_DESTROY_ALL )
			{
				pData->pDialog->SetDocument(NULL);

				CRect rcDialog;
				pData->pDialog->GetWindowRect( rcDialog );
				/*
				Cdfi_Attributes *pAttributes = pDfi->GetApp()->GetAttributes();

				Attr(rcDialog.left, GetResourceString(IDS_VINFO_DIALOG_LEFT),GetResourceString(IDS_VINFO_DIALOG_TITLE),pAttributes,TRUE);
				Attr(rcDialog.top, GetResourceString(IDS_VINFO_DIALOG_TOP),GetResourceString(IDS_VINFO_DIALOG_TITLE),pAttributes,TRUE);
				Attr((pData->pDialog->m_fitObjectToRect),GetResourceString(IDS_VINFO_FIT_OBJECT),GetResourceString(IDS_VINFO_DIALOG_TITLE),pAttributes,TRUE);
				pDfi->GetApp()->GetFncFunctions()->SendMessage(FM_ATTRIBUTE_CHANGE, 0, NULL, pDfi->GetMainFrame()->GetActiveDocument());
				*/
				if (pData->pDialog->GetSafeHwnd())
					pData->pDialog->DestroyWindow();

				delete pData->pDialog;

				pData->pDialog = NULL;
			}
			else
			if(pParam->message == FM_DEFAULT)
			{
				pData->pDialog->SetDocument(NULL);
			}
		}
	}
	else	
	{

		CVectorInfoDialog* pDialog = new CVectorInfoDialog(pDfi);// (CWnd*)pDfi->GetMainFrame() );
		Cdfi_Attributes *pAttributes = pDfi->GetApp()->GetAttributes();

		if (pData->rcLast.IsRectNull())
		{
			IC_RECT64 rcFrameWindow, rcFrameClient;
			CRect rcDialog;
			pDfi->GetMainFrame()->GetClientRect( &rcFrameClient );
			pDfi->GetMainFrame()->GetWindowRect( &rcFrameWindow );
			pDialog->GetWindowRect( rcDialog );
			long left = 0;
			long top = 0;


			Attr(left, GetResourceString(IDS_VINFO_DIALOG_LEFT), GetResourceString(IDS_VINFO_DIALOG_TITLE),pAttributes,FALSE);
			Attr(top, GetResourceString(IDS_VINFO_DIALOG_TOP), GetResourceString(IDS_VINFO_DIALOG_TITLE),pAttributes,FALSE);

			if(left == 0 || top == 0)
			{
				left = (int)rcFrameWindow.left + (int)rcFrameClient.right - RIGHT_OFFSET - rcDialog.Width();
				top = (int)rcFrameWindow.top + (int)rcFrameClient.bottom * TOP_POSITION / 100;
			}
			else // for any case
			{
				left = min(left,(int)rcFrameWindow.left + (int)rcFrameClient.right - RIGHT_OFFSET - rcDialog.Width());
				top = min(top,(int)rcFrameWindow.top + (int)rcFrameClient.bottom * TOP_POSITION / 100);
			}
			pDialog->MoveWindow(left, top,
								 rcDialog.Width(), rcDialog.Height(), FALSE );	

			
			/*pDialog->MoveWindow( (int)rcFrameWindow.left + (int)rcFrameClient.right - RIGHT_OFFSET - rcDialog.Width(), 
								 (int)rcFrameWindow.top + (int)rcFrameClient.bottom * TOP_POSITION / 100,
								 rcDialog.Width(), rcDialog.Height(), FALSE );
								 */
			/*
			pDialog->MoveWindow( (int)rcFrameWindow.left + (int)rcFrameClient.right/2 - RIGHT_OFFSET - rcDialog.Width(), 
								 (int)rcFrameWindow.top + (int)rcFrameClient.bottom * TOP_POSITION / 100,
								 rcDialog.Width(), rcDialog.Height(), FALSE );
								 */
		}
		else
		{
			pDialog->MoveWindow( pData->rcLast, FALSE );
			//pDialog->m_SplitterPos = pData->SplitterPos;
			pDialog->ResizeBars();
		}
		
		pDialog->SetParams( pDfi, pData );
		pData->pDialog = pDialog;
		pDialog->ShowWindow( SW_SHOW );

		pDoc = pDfi->GetMainFrame()->GetActiveDocument();
		if( pDoc )
		{
			if( pDoc->LockDocument( MODE_ACCESS_READ ) )
			{
				pDialog->SetDocument( pDfi->GetMainFrame()->GetActiveDocument() );
				pDoc->UnlockDocument( MODE_ACCESS_READ );
			}
		}
		else
			pDialog->SetDocument( NULL );
	}

	return true;
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

bool UpdateVectorInfo(CDFI *pdfi, CCmdUI * pExtra)
{
Cdfi_Document* pDocument = pdfi->GetMainFrame()->GetActiveDocument();

	if ( pDocument ) 
	{
		if (!pDocument->LockDocument(MODE_ACCESS_READ) )
			return false;

		if ( pDocument->GetLayers()->GetLayerActive( IC_VECTOR_CLASS_NAME ) >= 0 )
		{
			pDocument->UnlockDocument(MODE_ACCESS_READ);
			return true;
		}

		pDocument->UnlockDocument(MODE_ACCESS_READ);
	}

return false;
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

bool VectorInfoProc( CDFI * pDfi, IC_PARAM * pParam )
{
AFX_MANAGE_STATE( AfxGetStaticModuleState() );
VECTOR_INFO_DATA *pData = NULL;
CIC_Point64 ptClient;
CIC_Point3DD ptGeo;
CIC_Rect64 rcClient;
CIC_Rect3DD rcGeo;

	if ( pParam->message == WM_KEYDOWN)//WM_USER_SELECT_OBJ)
	{
		pData=NULL;
	}


	if( !pDfi )
		return false;

	pData = GetVectorInfoFunctionData( pDfi );

	if ( !pData->pDialog )
		return false;
	
	if(pParam->message >= 2000000)
	{
		if(pParam->message != FM_VIEW_ACTIVATE && pParam->message != FM_VIEW_DEACTIVATE)
		{
			int p=0;
		}
	}
	
	return pData->pDialog->Commander(pParam->message,pParam);



	return true;
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

void EndFunction(CDFI *pDfi) 
{
int ifindex;
IC_PARAM param;
          
	memset( &param, 0, sizeof(IC_PARAM) );
	param.message = FM_END_FUNCTION;

	if( pDfi->GetMainFrame() )
	{				  
		ifindex = pDfi->GetApp()->GetFncFunctions()->GetFuncIndex( (void *)VectorInfo );

		if ( ifindex>-1 )	 
			pDfi->GetApp()->GetFncFunctions()->DoFunction( ifindex, &param, FALSE );
	}
}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// Turn On Function
bool DoFunction(CDFI *m_pDfi)  
{
	int numFunction = m_pDfi->GetApp()->GetFncFunctions()->GetFuncIndex((void*)VectorInfo);

	if (numFunction != -1)
	{
		IC_FUNCTION_IDENTIFY fi;
		m_pDfi->GetApp()->GetFncFunctions()->GetFunctionInfo(numFunction, &fi);
		if ((fi.fnState & FNSTATE_CHECKED) == 0)
		{
			m_pDfi->GetApp()->GetFncFunctions()->DoFunction(numFunction, NULL, FALSE);

			return true;
		}
	}

	return false;
}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////