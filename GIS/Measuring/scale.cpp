#include "stdafx.h"
#include "scale.h"
#include "ScalePanel.h"

#include "windowsx.h"
#include "dfi_OverDraw.h"
#include "dfi_View.h"
#include "dfi_Layer.h"
#include "dfi_VectorObject.h"
#include "dfi_VectorPolygon.h"
#include "dfi_VectorLine.h"
#include "IC_ManagerVectorStyle.h"
#include "VectorStyle\\IC_StylePolygon.h"
#include "polygon.h"


///////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////
CString GetResourceString(UINT resID)
{
	HINSTANCE  hInstance = AfxGetStaticModuleState()->m_hCurrentResourceHandle;
	CString str;
	str.LoadString( hInstance, resID);
	return str;
}
//////////////////////////////////////////////////////////////////////////////////////
CScaleControl::CScaleControl()
{
	m_pData = NULL;
}
//////////////////////////////////////////////////////////////////////////////////////
CScaleControl::CScaleControl(SCALE_FUNC_DATA *pData) : SCALE_DATA_STRUCT()
{
	m_pData = pData;
	m_pView = NULL;
	m_pDocument = NULL;

	m_pPolygon = NULL;
	//m_pRegion = NULL;

	m_showDistance=TRUE;
	m_closeCurve=TRUE;
	
	m_Distance1=0;
	m_LastStep1=0;
	m_Square1=0;
	
	m_Distance2=0;
	m_LastStep2=0;
	m_Square2=0;
	
	m_unitCode2=0;

	m_lineWidth=4;	
	m_lineColorNum=7;
	m_lineStyle=0;
	m_textBacklight=0;

	m_precisionTypeD=0;
	m_precisionTypeS=0;

	m_linearAlways = false;
	//m_Mode=0;
}

//////////////////////////////////////////////////////////////////////////////////////

CScaleControl::~CScaleControl()
{
}
//////////////////////////////////////////////////////
void CScaleControl::ScaleDataDelete(bool bRedraw)
{
	//if(!pData) return;
	CScaleControl *pData=this;

	CDFI *pDfi=pData->m_pDfi;

	if(!pDfi) return;

	// unregister overdrawfunc
	Cdfi_Document* pDocument;
	POSITION pos;
	CWnd* pWnd = NULL;

	pDocument = pDfi->GetApp()->GetFirstDocument();
	while (pDocument)
	{
		pos = pDocument->GetFirstViewPosition();
		while ( pWnd = pDocument->GetNextView(pos) )
		{
			Cdfi_View* pView = (Cdfi_View*)pWnd;
			//if(Cdfi_View* pView = dynamic_cast<Cdfi_View*>(pWnd))
			{
				int iPos = (int)pView->GetOverDraw()->Find(OverdrawFunction);
				if (iPos != -1)
				{
					pView->GetOverDraw()->Remove(iPos);
					if (bRedraw)
						pView->InvalidateView(NULL, TRUE, VIEW_UPDATE_OVERDRAW);
				}
			}
		}
		pDocument = pDfi->GetApp()->GetNextDocument(pDocument);
	}
	
	if(pData->m_pPolygon) 
		delete pData->m_pPolygon;
	pData->m_pPolygon = NULL;

	//if(pData->m_pRegion) 
	//	delete pData->m_pRegion;
	//pData->m_pRegion = NULL;
		
	pData->m_Distance1=0;
	pData->m_LastStep1=0;
	pData->m_Square1=0;

	pData->m_Distance2=0;
	pData->m_LastStep2=0;
	pData->m_Square2=0;	

	PrintResults(); 
	
	//if(pData->pPanel) pData->pPanel->PrintResults();
}


//////////////////////////////////////////////////////

void CScaleControl::TransformToVector()
{	
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CScaleControl *pData=this;

	CDFI *pDfi=pData->m_pDfi;

	if(!pDfi) return;

	if(!m_pPolygon) return;

	if(m_pPolygon->GetSize()<2) return;

	Cdfi_Layers *layers;
	Cdfi_Layer* pLayer;
	Cdfi_Vector* pVectorLayer;
	Cdfi_VectorObject *pNewObject = NULL;

	if (!m_pDocument->LockDocument(MODE_ACCESS_WRITE))
				return;	

	layers = m_pDocument->GetLayers();

	int nLayer = layers->GetLayerActive(IC_VECTOR_CLASS_NAME);

	//if(nLayer >= 0)
	{
		pLayer = layers->GetLayer( nLayer );

		if(!pLayer)
		{
			CString sLayerName = _T("");

			CIC_VectorInfo VectorInfo( m_pDfi->fnc_pApplication );

			nLayer = layers->AddLayer(&VectorInfo, TRUE );

			// Set layer name
			sLayerName = layers->GenerateNewName();

			layers->GetLayer( nLayer )->SetName( sLayerName, FALSE );

			pLayer = layers->GetLayer(nLayer);

			pVectorLayer = pLayer->GetVector();

			// history of creating layer
			int iHistoryItem = m_pDocument->GetHistory()->AddItem((LPTSTR)(LPCTSTR)::GetResourceString(IDS_MEASURING), TRUE, AfxGetInstanceHandle(), IDB_SCALE);

			m_pDocument->GetHistory()->GetItem(iHistoryItem)->AddAction(HISTORY_ACTION_CREATE, nLayer, pLayer);

			// Set Mode EDIT
			layers->SetLayerEdit(nLayer, TRUE, TRUE );
		}

		if(pLayer)
		{
			pVectorLayer = pLayer->GetVector(); // 

			Cdfi_VectorObjectStream voStream( pVectorLayer, VMEM_READWRITE);

			if(m_closeCurve)
			{
				pNewObject = pVectorLayer->CreateObject(VE_POLYGON);

				m_pPolygon->SetExternal( TRUE );

				pNewObject->GetObjPolygon()->AddPolygon( m_pPolygon );

				VECTOR_POLYGON_STYLE polygon_style;

				CIC_ManagerVectorStyle *ms=pDfi->GetApp()->GetStyleManager();

				polygon_style.ColorOutline = pDfi->GetApp()->GetStyleManager()->GetCurrentPolygonOutlineColor();
				polygon_style.WidthOutline = pDfi->GetApp()->GetStyleManager()->GetCurrentPolygonOutlinePixel();
				polygon_style.WidthGeoOutline= pDfi->GetApp()->GetStyleManager()->GetCurrentPolygonOutlineWidth();
				polygon_style.Zooming = pDfi->GetApp()->GetStyleManager()->GetCurrentPolygonZoom();

				CIC_StylePolygon *curStyle = pDfi->GetApp()->GetStyleManager()->GetCurrentPolygonStyle();
				polygon_style.pStylePolygon = pVectorLayer->GetStyleSet()->AddStyle(curStyle)->GetPolygonObject();
				if (curStyle)
					curStyle->Release();
		
				pNewObject->GetObjPolygon()->SetStyle(&polygon_style);


				//((Cdfi_VectorPolygon *)pNewObject)->AddPoints(0,m_pPolygon->GetSize()-1,m_pPolygon->GetData());

			}
			else
			{
				pNewObject = pVectorLayer->CreateObject(VE_LINE);

				((Cdfi_VectorLine *)pNewObject)->AddPoints(0,m_pPolygon->GetSize(),m_pPolygon->GetData());
			}
				
			__int64 id = voStream.AddObject(pNewObject);

			pNewObject->DeleteObject();

			pNewObject = NULL;

			 ////  Set History	of adding object			

			if ( id >= 0 )
			{	                  
				CString str=::GetResourceString(IDS_TRANSFORM);	
										
				pNewObject = voStream.GetVectorObject(id);

				m_pDocument->GetHistory()->AddItem( (LPTSTR)(LPCTSTR)str, HISTORY_ACTION_CREATE, nLayer, pNewObject, TRUE, &id, AfxGetInstanceHandle(), 0 );
			}
			
			voStream.Stop();

			ClearPolygon();
	
			
			m_pDocument->RedrawViews(TRUE, nLayer);
		}
	}


	m_pDocument->UnlockDocument(MODE_ACCESS_WRITE);

}

////////////////////////////////////////////////////////////////////////////
void CScaleControl::ClearPolygon()
{
	if(m_pPolygon) 
		delete m_pPolygon;

	m_pPolygon = NULL;

	//if(pData->m_pRegion) 
	//	delete pData->m_pRegion;
	//pData->m_pRegion = NULL;
		
	m_Distance1=0;
	m_LastStep1=0;
	m_Square1=0;

	m_Distance2=0;
	m_LastStep2=0;
	m_Square2=0;	

	PrintResults(); 

	if(m_pView)		m_pView->RedrawView( NULL, TRUE, VIEW_UPDATE_OVERDRAW );
}
////////////////////////////////////////////////////////////////////////////
// Attr  - use for write or read parameters by ID with config file
void Attr(COLORREF & value, int resID, CString &sSection,Cdfi_Attributes *pAttributes,bool bWrite=false );
//void Attr(CString & value, int resID, CString &sSection,Cdfi_Attributes *pAttributes,bool bWrite=false );
void Attr(bool & value,  int resID, CString &sSection,Cdfi_Attributes *pAttributes,bool bWrite=false);
void Attr(int & value,  int resID, CString &sSection,Cdfi_Attributes *pAttributes,bool bWrite=false,int minValue=0, int maxValue=0xFFFFFFFF );

void  GetAttributesScale( Cdfi_Attributes *pAttributes, SCALE_DATA *pData, bool bWrite )
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );

	CString  str, sSection=_T("");
	
	bool bMainAttr=true;
	if( bMainAttr )
	{
		sSection.LoadString( IDS_TOOLBAR  );
		str.LoadString( IDS_FUNCTION_DEFAULT );
		sSection += _T("\\");
		sSection += str;
	}
	else
	{
		sSection.LoadString( IDS_FUNCTION_DEFAULT );
	}
	
	Attr(pData->m_precisionTypeD,IDS_SELECT_PRECISION_D,sSection,pAttributes,bWrite,0,7);
	Attr(pData->m_precisionTypeS,IDS_SELECT_PRECISION_S,sSection,pAttributes,bWrite,0,7);
	Attr(pData->m_lineWidth,IDC_LINE_WIDTH,sSection,pAttributes,bWrite,0,7);	
	Attr(pData->m_lineStyle,IDC_LINE_STYLE,sSection,pAttributes,bWrite,0,4);
	Attr(pData->m_textBacklight,IDC_TEXT_FON,sSection,pAttributes,bWrite);
	Attr(pData->m_showDistance,IDS_SHOW_DISTANCE,sSection,pAttributes,bWrite);
	Attr(pData->m_showSquare,IDS_SHOW_SQUARE,sSection,pAttributes,bWrite);
	Attr(pData->m_closeCurve,IDS_CLOSE_CURVE,sSection,pAttributes,bWrite);	
	Attr(pData->m_lineColor,IDC_LINE_COLOR,sSection,pAttributes,bWrite);
	Attr(pData->m_linearAlways, IDC_ALWAYS_LINEAR_STATIC, sSection, pAttributes, bWrite);
	
}

///////////////////////////////////////////////////
void Attr(int & value, int resID, CString &sSection, Cdfi_Attributes *pAttributes, bool bWrite, int minValue, int maxValue  )
{
	CString str;
	str.LoadString( resID );

	//if (typeid(int)==typeid(T) | typeid(COLORREF)==typeid(T))	
			
	if (!pAttributes->FindAttribute(sSection, str) ) 
		pAttributes->Add( sSection, str, ATTRIBUTE_TYPE_INT	, 0, ATTRIBUTE_NO_REMOVE )->SetInt( value, FALSE );
	if(!bWrite)
		value = pAttributes->Item( sSection, str )->GetInt();
	else
		pAttributes->Item( sSection, str )->SetInt( value, FALSE);

	value = min(maxValue, max(minValue, value));
}		
/////////////////////////////////////////////////
void Attr(COLORREF & color, int resID, CString &sSection, Cdfi_Attributes *pAttributes, bool bWrite )
{
	int value = (int)color;
	CString str;
	str.LoadString( resID );	
			
	if (!pAttributes->FindAttribute(sSection, str) ) 
		pAttributes->Add( sSection, str, ATTRIBUTE_TYPE_COLOR	, 0, ATTRIBUTE_NO_REMOVE )->SetInt( value, FALSE );
	if(!bWrite)
	{
		value = pAttributes->Item( sSection, str )->GetInt();
		color = value;
	}
	else
		pAttributes->Item( sSection, str )->SetInt( value, FALSE);	
}		
////////////////////////////////////////////////////////
void Attr(bool & value,   int resID, CString &sSection,Cdfi_Attributes *pAttributes,bool bWrite )
{
	BOOL v=value;
	CString str;
	str.LoadString( resID );

	if (!pAttributes->FindAttribute(sSection, str) )
		pAttributes->Add( sSection, str, ATTRIBUTE_TYPE_BOOL	, 0, ATTRIBUTE_NO_REMOVE )->SetBool( value, FALSE );
		
	//if (typeid(std::string)==typeid(value))
	{
		if(!bWrite)
			v = pAttributes->Item( sSection, str )->GetBool();
		else
			pAttributes->Item( sSection, str )->SetBool( value, FALSE);
	}
	
	value=(v==TRUE)?true:false;
}

////////////////////////////////////////////////////////
/*
void Attr(CString & value,   int resID, CString &sSection,Cdfi_Attributes *pAttributes,bool bWrite, int attType )
{
	CString str;
	str.LoadString( resID );

	if (!pAttributes->FindAttribute(sSection, str) )
		pAttributes->Add( sSection, str, ATTRIBUTE_TYPE_STRING	, 0, ATTRIBUTE_NO_REMOVE )->SetString( value, FALSE );

	
	if (typeid(std::string)==typeid(value))
	{

		if(!bWrite)
			value = pAttributes->Item( sSection, str )->GetString();
		else
			pAttributes->Item( sSection, str )->SetString( value, FALSE);
	}
	

}
*/
//////////////////////////////////////////////////////////
// Turn On Function
bool DoFunction(CDFI *m_pDfi)  
{
	int numFunction = m_pDfi->GetApp()->GetFncFunctions()->GetFuncIndex((void*)ScaleFunction);

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
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
//Turn Off Function
bool EndFunction(CDFI *m_pDfi)
{
	int numFunction = m_pDfi->GetApp()->GetFncFunctions()->GetFuncIndex((void*)ScaleFunction);

	if (numFunction != -1)
	{
		IC_FUNCTION_IDENTIFY fi;
		m_pDfi->GetApp()->GetFncFunctions()->GetFunctionInfo(numFunction, &fi);
		if (fi.fnState & FNSTATE_CHECKED)
		{
			IC_PARAM param = {0};
			param.message = FM_END_FUNCTION;
			m_pDfi->GetApp()->GetFncFunctions()->DoFunction(numFunction, &param, FALSE);

			return true;
		}
	}

	return false;
}






//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
// Enter point of Function
bool ScaleFunction(CDFI* pDfi, IC_PARAM *pParam)
{
	AFX_MANAGE_STATE(pDfi->GetMainFrame()->GetModuleState());
	SCALE_DATA *pData = GetScaleData(pDfi);
	SCALE_FUNC_DATA *pBaseData = GetScaleBaseData(pDfi);
	Cdfi_Attributes *pAttributes;

	if (pParam)
	{
		if ((pParam->message != FM_INIT_APP) && (pParam->message != FM_LOAD_STATE) && 
			(pParam->message != FM_DESTROY_ALL) && (pParam->message != FM_DEFAULT) &&
			(pParam->message != FM_END_FUNCTION))
			return false;

		if (pParam->message == FM_INIT_APP)
		{
			// create panel		
			CScalePanel * pPanel = new CScalePanel(pDfi,pBaseData);
			pData = pBaseData->pControl = (CScaleControl *)pPanel;//new CScaleControl(pData);
			//pData->m_pDfi = pDfi;
			pAttributes = pDfi->GetApp()->GetAttributes();
			GetAttributesScale(pAttributes, pData);
			pPanel->OnLoadInits();
			return true;
		}
		
		if (pParam->message == FM_LOAD_STATE)
		{
			CScalePanel *pPanel=(CScalePanel *)pData;
			//show panel after load state
			if (pPanel)
			{
				if (!pPanel->IsRestoredFromRegistry())
				{					
					/// ????????????????????????????????????????????????????????????????
					pPanel->DockPane(FALSE, pDfi->GetApp(), CBRS_ALIGN_RIGHT, CBRS_ALIGN_ANY, NULL );
				}
				else
					//check panel visibility and set function's state
					if (pPanel->GetRecentVisibleState())
						pPanel->DoPanelFunction();
			}

			return true;
		}
		

		if (pParam->message == FM_END_FUNCTION)
		{ 
			CScalePanel *pPanel=(CScalePanel *)pData;
#ifndef PANEL_IS_OPTIONAL			
			pPanel->Hide(); 
			
#endif
			pData->ScaleDataDelete(true);		
			pData->m_pDocument = NULL;
			pData->m_pView = NULL;
			

			return true;
		}

		if (pParam->message == FM_DESTROY_ALL)
		{
			CScalePanel *pPanel=(CScalePanel *)pData;
			pAttributes = pDfi->GetApp()->GetAttributes();
			GetAttributesScale(pAttributes, pData,true);

#ifndef PANEL_IS_OPTIONAL	
			pPanel->Hide(); 			
#endif
			pData->ScaleDataDelete(true);		
			pData->m_pDocument = NULL;
			pData->m_pView = NULL;
			delete pPanel;
			pBaseData->pControl = NULL;
			
			return true;
		}

	}
	else
		return false;

	////////////////////////////////////////
	// Default action
	////////////////////////////////////////
	CScalePanel *pPanel=(CScalePanel *)pData;
	if (pPanel)
	{
		IC_FUNCTION_IDENTIFY fi;
		BOOL bShow = FALSE;

		//get function state
		int numFunction = pDfi->GetApp()->GetFncFunctions()->GetFuncIndex((void*)ScaleFunction);
		if (numFunction != -1)
		{
			pDfi->GetApp()->GetFncFunctions()->GetFunctionInfo(numFunction, &fi);
			bShow = (fi.fnState & FNSTATE_CHECKED) != 0;
		}
#ifndef PANEL_IS_OPTIONAL
		if (!bShow)
		{
			//hide panel
			
			//pPanel->CDockablePane::ShowPane(FALSE, FALSE, FALSE);//Hide();
			pPanel->Hide();

			pData->ScaleDataDelete(true);		
			pData->m_pDocument = NULL;
			pData->m_pView = NULL;
		}
		else
		{
			//show panel		
			pPanel->Show();
		}
#else
		if (bShow)
			pPanel->DoFunction();
		else
		{
			pPanel->EndFunction();
			pData->ScaleDataDelete(true);		
			pData->m_pDocument = NULL;
			pData->m_pView = NULL;

		}

		if(pPanel->m_isVisible)
			pPanel->Show();//CDockablePane::ShowPane(TRUE, FALSE, TRUE); 
		else
			pPanel->Hide();
#endif

	}
	else
	{
		pData->m_pDfi = pDfi;
	}	

	return true;	
	
}
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
bool UpdateScaleFunction(CDFI * pDFInterface, CCmdUI * pExtra)
{
Cdfi_Document *pDoc;

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (!pDFInterface)
		return false;

	pDoc = pDFInterface->GetMainFrame()->GetActiveDocument();
	if (!pDoc)
	   return false;

return true;
}
////////////////////////////////////////////////////////////////////////////////////////
SCALE_FUNC_DATA *GetScaleBaseData( CDFI *pDfi )
{
	SCALE_FUNC_DATA* pData = NULL;
	IC_FUNCTION_IDENTIFY fi;
	int numFunction;

	if (pDfi && pDfi->GetMainFrame() )
	{	
		numFunction = pDfi->GetApp()->GetFncFunctions()->GetFuncIndex( (void*)ScaleFunction );

		if (numFunction != -1)
		{
			pDfi->GetApp()->GetFncFunctions()->GetFunctionInfo(numFunction, &fi);
			pData = (SCALE_FUNC_DATA*)fi.pProcInfo;
		}
	}
	

	return pData;
}
////////////////////////////////////////////////////////////////////////////////////////
int GetFunctionID(CDFI *pDfi)
{
	return pDfi->GetApp()->GetFncFunctions()->GetFunctionID( (void*)ScaleFunction );
	
}

////////////////////////////////////////////////////////////////////////////////////////
SCALE_DATA *GetScaleData( CDFI *pDfi )
{	
	SCALE_FUNC_DATA *pData=GetScaleBaseData(pDfi);

	if(!pData) return NULL;

	return pData->pControl;
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
bool ScaleWindowProc(CDFI *pDfi, IC_PARAM* pParam)
{		
	AFX_MANAGE_STATE(pDfi->GetMainFrame()->GetModuleState());

	if(!pParam)
		return false;

	// get pointer to the CPositionPanel class
	SCALE_DATA * pData;
	
	pData = GetScaleData(pDfi);

	if(!pData)
		return false;

	// handle messages
	switch(pParam->message)
	{
		/*
		case WM_CLOSE :
			
		break;
		case WM_SETFOCUS :
		
		break;
		*/
		case FM_NEW_DOCUMENT:
		case FM_OPEN_DOCUMENT:
		case FM_SHOW_DOCUMENT:
		case FM_CREATE_DOCUMENT:

			pData->OnDocumentChange();

		return true;

		case FM_CLOSE_DOCUMENT:
			pData->m_pDocument=NULL;
			pData->m_pView=NULL;
		break;
		
		case WM_RBUTTONUP :
			StartContextMenu(pData);
		break;

		default:

		if(pParam->message==WM_COMMAND)
		{
			pData->OnCommand( LOWORD(pParam->wParam), HIWORD(pParam->wParam) );
		}
		else
		if(pParam->message==WM_DRAWITEM)
		{
		//	pData->OnDraw( LOWORD(pParam->wParam), HIWORD(pParam->wParam) );
		}
		else
		if(pParam->message==WM_MEASUREITEM)
		{
		//pData->OnDraw( LOWORD(pParam->wParam), HIWORD(pParam->wParam) );

		}
		else
		if (pParam->message == WM_SETFOCUS)
		{
			//pData->OnDocumentChange();
		}
		else
		if (pParam->message == WM_ACTIVATE)
		{
			//pData->OnDocumentChange();
		}
		
	}

	
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
// 
bool WindowProc(CDFI * pDfi, IC_PARAM * pParam)
{	
	SCALE_DATA *pData = GetScaleData(pDfi);

	return ScaleDataWindowProc(pDfi,pParam,pData);
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////





int StartContextMenu(SCALE_DATA *pData )
{
	CDFI *pDfi=pData->m_pDfi;
	Cdfi_Document *pDoc=pData->m_pDocument;
// load menu
	CMenu Menu;

	Menu.CreatePopupMenu();
	Menu.AppendMenuW(MF_STRING|MF_ENABLED,1,GetResourceString(IDS_START));
	Menu.AppendMenu(MF_STRING|MF_ENABLED, 2,GetResourceString(IDS_CLEAR));
	Menu.AppendMenu(MF_STRING|MF_ENABLED, 3,GetResourceString(IDS_TRANSFORM));
	Menu.AppendMenu(MF_SEPARATOR);
	Menu.AppendMenu(MF_STRING|MF_ENABLED, 4,GetResourceString(IDS_END));
	Menu.AppendMenu(MF_SEPARATOR);
	Menu.AppendMenuW(MF_STRING|MF_ENABLED,5,GetResourceString(IDS_SHOW_DISTANCE));
	Menu.CheckMenuItem(5, pData->m_showDistance?MF_CHECKED:MF_UNCHECKED);
	Menu.AppendMenuW(MF_STRING|MF_ENABLED,6,GetResourceString(IDS_SHOW_SQUARE));
	Menu.CheckMenuItem(6, pData->m_showSquare?MF_CHECKED:MF_UNCHECKED);
	Menu.AppendMenuW(MF_STRING|MF_ENABLED,7,GetResourceString(IDS_CLOSE_CURVE));
	Menu.CheckMenuItem(7, pData->m_closeCurve?MF_CHECKED:MF_UNCHECKED);
		
	/*
	CMenu menuW;
	CString strLineWidths[8]={_T("1"),_T("2"),_T("3"),_T("4"),_T("5"),_T("6"),_T("7"),_T("8")};
	int m_menuLineWidths_ID[8];
	menuW.CreatePopupMenu();
	for(int i=0;i<8;i++)
		menuW.AppendMenuW(MF_STRING|MF_ENABLED|MF_CHECKED, m_menuLineWidths_ID[i]=pData->m_pDfi->GetApp()->GetID(),strLineWidths[i]);
	menuW.CheckMenuItem(m_menuLineWidths_ID[pData->m_lineWidth],MF_CHECKED );
	Menu.AppendMenuW(MF_STRING|MF_ENABLED|MF_POPUP, (UINT_PTR)menuW.m_hMenu,_T("Widths"));
	*/

	AFX_MANAGE_STATE( pDfi->GetMainFrame()->GetModuleState() );
	CPoint point;
	GetCursorPos(&point);
	GetFocus();
	UINT nID = ((CWinAppEx *)pDfi->GetApp())->GetContextMenuManager()->TrackPopupMenu( Menu.m_hMenu, point.x, point.y, (CWnd*)pDfi->GetMainFrame());
	switch(nID)
	{
		case 1 : // go !!!!
			//return 1;
			pData->DoFunction();
		break;

		case 2 :
			pData->ClearPolygon();
		break;

		case 3 :
			pData->TransformToVector();
		break;

		case 4 : // stop!!!
			EndFunction(pData->m_pDfi);
			//return 0;
		break;
		case 5 :
			pData->m_showDistance = ! pData->m_showDistance;
		break;
		case 6 :
			pData->m_showSquare = ! pData->m_showSquare;
		break;
		case 7 :
			pData->CloseCurve();//pData->m_closeCurve = ! pData->m_closeCurve;
		break;
	}
	return -1;




//	UINT RemoveID, DeselectAllID ;
//	CString strRemove, strDeselectAll ;


	/// init menu
	/*
	Menu.CreatePopupMenu();

	Menu.AppendMenuW(MF_STRING|MF_ENABLED,1,_T("Остановить измерение"));
	Menu.AppendMenu(MF_STRING|MF_ENABLED, 2,_T("Продолжить"));
	Menu.AppendMenu(MF_STRING|MF_ENABLED, 3,_T("Поставить точку"));
	Menu.AppendMenu(MF_SEPARATOR);
	Menu.AppendMenuW(MF_STRING|MF_ENABLED,4,_T("Выйти из функции измерений"));
#ifdef PANEL_IS_OPTIONAL 	
	Menu.CheckMenuItem(4, pData->m_isVisible?MF_CHECKED:MF_UNCHECKED);
	Menu.AppendMenu(MF_SEPARATOR);
	Menu.AppendMenu(MF_STRING|MF_ENABLED, 4,_T("Панель"));
#endif
	// call popupMenu
	CPoint point;
	GetCursorPos(&point);
	GetFocus();

	AFX_MANAGE_STATE( pDfi->GetMainFrame()->GetModuleState() );
	UINT nID = ((CWinAppEx *)pDfi->GetApp())->GetContextMenuManager()->TrackPopupMenu( Menu.m_hMenu, point.x, point.y, (CWnd*)pDfi->GetMainFrame());
	if (nID != 0)		
		return nID;
		//((CWnd*)pDfi->GetMainFrame())->SendMessage(WM_COMMAND, (WPARAM)nID, 0);

	return 0;*/
}






