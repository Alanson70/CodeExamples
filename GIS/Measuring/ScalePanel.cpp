

#include "StdAfx.h"
#include "ScalePanel.h"
#include "DFI.h"
#include "resource.h"
#include "afxdialogex.h"
#include "afxmsg_.h"
#include "afxtoolbar.h"
#include <math.h>
#include "DlgSetts.h"
#include "Polygon.h"


// automaticshen settings of ID, see also ReleaseComponents 
#define GET_ID (m_pDfi->GetApp()->GetID())


#define MIN_DIALOG_WIDTH 240
int MIN_DIALOG_HEIGHT=100;

IMPLEMENT_SERIAL(CScalePanel, CIC_Pane, VERSIONABLE_SCHEMA | 2)


////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CScalePanel, CIC_Pane)
ON_MESSAGE(WM_IDLEUPDATECMDUI, &CScalePanel::OnIdleUpdateCmdUI)
ON_WM_CREATE()
ON_WM_SIZE()
ON_WM_SETFOCUS()
ON_WM_ERASEBKGND()
ON_WM_CLOSE()
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////////////////////////
CScalePanel::CScalePanel() 	: CIC_Pane(), CScaleControl(), m_ToolBar(NULL)
{ 

	
}
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
CScalePanel::CScalePanel(CDFI *pDfi,SCALE_FUNC_DATA *pData) : CIC_Pane(), CScaleControl(pData), m_ToolBar(pDfi)
{
	m_pDfi = pDfi;

	//register temporary function
#ifndef PANEL_IS_OPTIONAL 	
	IC_FUNCTION_IDENTIFY fi;	
	memset(&fi, 0, sizeof(fi));
	_tcscpy_s(fi.Name, IC_MAX_FUNCTION_NAME, _T("ScalePanelMeasuring"));
	fi.fnStyle = FNSTYLE_CHECKGROUP;
	fi.pFunction = MeasuringFunction;
	fi.pCheckFunction = NULL;//CheckMeasuring;
	fi.pUpdateFunction = UpdateMeasuring;
	fi.pWndProc = MeasuringWndProc;
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		
		m_doMeasuring_ID= m_pDfi->GetApp()->GetFncFunctions()->RegisterFunction( AfxGetInstanceHandle(), &fi );
	}
#else
	m_doMeasuring_ID=GET_ID;
#endif
	m_doMeasuringImage_ID=0;

	m_ID=GET_ID;	
	CString strCaption;

	strCaption.LoadString(AfxGetStaticModuleState()->m_hCurrentResourceHandle, IDS_SCALE_PANEL);

	CWnd *pParentWnd = (CWnd*)pDfi->GetMainFrame();
	
	const DWORD dwStyle = WS_CHILD|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|CBRS_LEFT|CBRS_FLOATING|CBRS_FLOAT_MULTI;

	if (!Create(strCaption, pParentWnd, CRect(0, 0, 100, 100), TRUE, m_ID , dwStyle))
		return;

	EnableDocking(CBRS_ALIGN_ANY);

	((CMDIFrameWndEx*)pDfi->GetMainFrame())->DockPane(this);

	// установка минимального размера панели в пристыкованном состоянии
	SetMinSize(CSize(MIN_DIALOG_WIDTH, MIN_DIALOG_HEIGHT));
	

}
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
CScalePanel::~CScalePanel(void)
{
	ScaleDataDelete(true);
	
	GetCmdMgr()->SetCmdImage(m_doMeasuring_ID, -1, FALSE);

	DestroyComponents();

	if (m_hWnd)
		DestroyWindow();

}	
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

//#include "winuser.h"
int CScalePanel::CreateComponents()
{	
	int col[4]={5,120,124,MIN_DIALOG_WIDTH};
	int row[10];
	int h=22; // height of element

	row[0]=35;

	for(int i=1;i<10;i++) row[i]=row[0]+(4+h)*(i-1);

	// create static text
	int dwStaticStyle = WS_VISIBLE | WS_CHILD;//|  SS_SUNKEN;//WS_BORDER |
	
	if (!DistLabel.Create(GetResourceString(IDC_PANEL_DISTANCE), dwStaticStyle,   CRect(col[0],row[1]+2,col[1],row[1]+h), this,GET_ID)) return -1;
	if (!StepLabel.Create(GetResourceString(IDC_PANEL_STEP), dwStaticStyle,  CRect(col[0],row[2]+2,col[1],row[2]+h), this,GET_ID)) return -1;
	if (!SquareLabel.Create(GetResourceString(IDC_PANEL_SQUARE),	 dwStaticStyle,		CRect(col[0],row[3]+2,col[1],row[3]+h), this,GET_ID)) return -1;

	const int dwStyle = WS_VISIBLE | WS_CHILD |  WS_TABSTOP;//  | WS_THICKFRAME;
	dwStaticStyle = WS_VISIBLE | WS_CHILD|  SS_SUNKEN;

	if(!border[2].Create(_T(""), dwStaticStyle, CRect(col[2]+2,row[1]+0,col[3]-0,row[1]+h), this,GET_ID)) return -1;
	if (!DistEdit2.Create(dwStyle,				CRect(col[2]+4,row[1]+2,col[3]-2,row[1]+h-2), this,GET_ID)) return -1;
	DistEdit2.SetReadOnly(true);
	DistEdit2.SetWindowTextW(_T("0"));

	if(!border[4].Create(_T(""), dwStaticStyle, CRect(col[2]+2,row[2]+0,col[3]-0,row[2]+h), this,GET_ID)) return -1;
	if (!StepEdit2.Create(dwStyle,				CRect(col[2]+4,row[2]+2,col[3]-2,row[2]+h-2), this,GET_ID)) return -1;
	StepEdit2.SetReadOnly(true);
	StepEdit2.SetWindowTextW(_T("0"));

	if(!border[6].Create(_T(""), dwStaticStyle, CRect(col[2]+2,row[3]+0,col[3]-0,row[3]+h), this,GET_ID)) return -1;
	if (!SquareEdit2.Create(dwStyle,			CRect(col[2]+4,row[3]+2,col[3]-2,row[3]+h-2), this,GET_ID)) return -1;
	SquareEdit2.SetReadOnly(true);
	SquareEdit2.SetWindowTextW(_T("0"));

	MIN_DIALOG_HEIGHT=row[3]+h+4;
	//dwStaticStyle = WS_VISIBLE | WS_CHILD|  SS_BITMAP|SS_REALSIZECONTROL|WS_THICKFRAME;//|WS_BORDER;//|SS_CENTERIMAGE
			
	VERIFY(m_font.CreatePointFont(90, _T("Arial"), DistLabel.GetDC()) );
	SendMessageToDescendants(WM_SETFONT,
        (WPARAM)m_font.m_hObject,  //handle to font
       MAKELONG ((WORD) FALSE, 0), 
       FALSE);


	InitToolBar();

	OnChangeMeasuring();
	
	return 0;
}


////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

void CScalePanel:: ReinitUom()
{
	AFX_MANAGE_STATE(m_pDfi->GetMainFrame()->GetModuleState());

	CMFCToolBarComboBoxButton * comboBox =
		(CMFCToolBarComboBoxButton *)m_ToolBar.GetButton(m_ToolBar.CommandToIndex(m_uomComboBox_ID));
	

	Cdfi_Document *pDoc=m_pDfi->GetMainFrame()->GetActiveDocument();
	if(!pDoc) return;

	comboBox->RemoveAllItems();// ->ClearData();

	if(comboBox->GetCount()>0) return;
	
	CGeoInfo *gInfo=pDoc->GetDocGeoInfo();
	int count = fnc_UOM::GetCountUom();	
	IC_MAPINFO  *mInfo=gInfo->GetMapinfo();


	int index,iUomCode,curSel=0;
	TCHAR cUnitName[255];
	int curUomCode=gInfo->GetGeoProjection()->GetUnit();
	bool linear= gInfo->IsLinearUnit(curUomCode)?true:false;
	bool angle= gInfo->IsAngleUnit(curUomCode)?true:false;
		
	CString str;
	
	//if(m_unitCode2==0)		
	m_unitCode2=gInfo->GetGeoProjection()->GetUnit();
		
	// meters anyway
	if (linear || m_linearAlways)
	{
		for (int i = 0; i < count; i++)
		{
			iUomCode = fnc_UOM::GetCodeUom(i);
			if (CGeoInfo::IsLinearUnit(iUomCode))
			{
				gInfo->GetUnitName(iUomCode, cUnitName);
				if (angle)
					str.Format(_T("~%s"), cUnitName);
				else
					str = cUnitName;
				index = (int)comboBox->AddItem(str, iUomCode);
				if (curUomCode == iUomCode) 						curSel = index;
			}
		}
	}
	if (angle)
	{
		for (int i = 0; i < count; i++)
		{		
			iUomCode = fnc_UOM::GetCodeUom(i);
			if(CGeoInfo::IsAngleUnit(iUomCode))
			{
				gInfo->GetUnitName(iUomCode, cUnitName);
				str = cUnitName;
				index = (int)comboBox->AddItem(str, iUomCode);
				if (curUomCode == iUomCode) 						curSel = index;
			}
		}
	}
	if(comboBox->GetCount()==0)
	{
		gInfo->GetShortUnitName( curUomCode, cUnitName );
		str = cUnitName;
		index=(int)comboBox->AddItem(str,iUomCode);				
			if(curUomCode==iUomCode) 						curSel=index;
	}
	
	comboBox->SelectItem(curSel);	

	m_ToolBar.InvalidateButton(m_ToolBar.CommandToIndex(m_uomComboBox_ID));
	m_ToolBar.UpdateButton(m_ToolBar.CommandToIndex(m_uomComboBox_ID));

	m_ToolBar.RedrawWindow();

	this->RedrawWindow();
	//m_unitCode2=comboBox->GetItemData(comboBox->GetCurSel());


}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

void CScalePanel::SetUomOfDoc()
{
	AFX_MANAGE_STATE(m_pDfi->GetMainFrame()->GetModuleState());

	Cdfi_Document* pDoc = m_pDfi->GetMainFrame()->GetActiveDocument();
	if(!pDoc)	return;	

	ReinitUom();

	DWORD unit = pDoc->GetDocGeoInfo()->GetGeoProjection()->GetUnit();

	// retrieve uom chosen by the user	

	CMFCToolBarComboBoxButton * pComboBox =	(CMFCToolBarComboBoxButton *)m_ToolBar.GetButton(m_ToolBar.CommandToIndex(m_uomComboBox_ID));	

	int uom = fnc_UOM::GetUomIndex(unit);
	if (pComboBox)
	{
		for(int i=0;i<pComboBox->GetCount();i++)
			if (pComboBox->GetItemData(i) == uom)
			{
				pComboBox->SelectItem(i);
				break;
			}
	}
}
////////////////////////////////////////////////////////////////////////
bool CScalePanel::InitToolBar()
{		
	//AFX_MANAGE_STATE(AfxGetStaticModuleState());
	AFX_MANAGE_STATE(m_pDfi->GetMainFrame()->GetModuleState());

	if (!m_ToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, m_toolBar_ID=GET_ID))		return false;

	m_ToolBar.SetParent((CWnd*)this);

	UINT uiLoadImageFlags = LR_CREATEDIBSECTION|LR_LOADMAP3DCOLORS;

	SIZE szButton, szImage;
	szImage.cx = szImage.cy = 20;
	szButton.cx = szImage.cx + 5;
	szButton.cy = szImage.cy + 5;	

	m_ToolBar.SetLockedSizes(szButton, szImage);
	
	m_doMeasuringImage_ID=m_ToolBar.LoadImage(IDB_START_MEASURING);//IDB_RULERS);
	m_clearImage_ID=m_ToolBar.LoadImage(IDB_CLEAR);//IDB_RULERS);
	m_transformImage_ID=m_ToolBar.LoadImage(IDB_TRANSFORM);//IDB_RULERS);
	m_showDistanceImage_ID=m_ToolBar.LoadImage(IDB_DISTANCE);
	m_showSquareImage_ID=m_ToolBar.LoadImage(IDB_SQUARE);
	m_closeCurveImage_ID=m_ToolBar.LoadImage(IDB_CLOSED);
	m_discloseCurveImage_ID=m_ToolBar.LoadImage(IDB_DISCLOSED);
	m_settingsImage_ID=m_ToolBar.LoadImage(IDB_SETTINGS);
			

	// start button
	CMFCToolBarButton button1(0, 0, NULL, FALSE, TRUE);
	button1.m_nID = m_doMeasuring_ID;
	button1.SetStyle( TBBS_CHECKGROUP);//TBBS_BUTTON );	
	button1.SetImage(m_doMeasuringImage_ID);
	m_ToolBar.InsertButton(button1);

	// stop button
	CMFCToolBarButton button2(0, 0, NULL, FALSE, TRUE);
	button2.m_nID = m_clear_ID=GET_ID;
	button2.SetStyle( TBBS_BUTTON );	
	button2.SetImage(m_clearImage_ID);
	m_ToolBar.InsertButton(button2);	
	
	// transform button
	CMFCToolBarButton button3(0, 0, NULL, FALSE, TRUE);
	button3.m_nID = m_transform_ID=GET_ID;
	button3.SetStyle( TBBS_BUTTON );	
	button3.SetImage(m_transformImage_ID);
	m_ToolBar.InsertButton(button3);	
		
	// dist button
	/*
	CMFCToolBarButton button2(0, 0, NULL, FALSE, TRUE);
	button2.SetImage(m_showDistanceImage_ID);
	//button2.m_strText = "dist";
	button2.m_nID = m_showDistance_ID=GET_ID;
	button2.SetStyle(TBBS_CHECKBOX);
	m_ToolBar.InsertButton(button2);
	
	
	// sq button
	
	CMFCToolBarButton button3(0, 0, NULL, FALSE, TRUE);
	button3.SetImage(m_showSquareImage_ID);
	//button3.m_strText = "sq";
	button3.m_nID = m_showSquare_ID=GET_ID;
	button3.SetStyle(TBBS_CHECKBOX);
	m_ToolBar.InsertButton(button3);
	*/
	
	// close curve button
	
	CMFCToolBarButton button4(0, 0, NULL, FALSE, TRUE);
	
	button4.m_nID = m_closeCurve_ID=GET_ID;
	//button4.SetStyle(TBBS_CHECKBOX);
	m_ToolBar.InsertButton(button4);

	// disclose button
	/*
	CMFCToolBarButton button4a(0, 0, NULL, FALSE, TRUE);
	button4a.SetImage(m_discloseCurveImage_ID);
	//button4.m_strText = "dist";
	button4a.m_nID = m_discloseCurve_ID=GET_ID;
	//button4a.SetStyle(TBBS_CHECKBOX);
	m_ToolBar.InsertButton(button4a);
	*/
	// ...and CMFCToolBarComboBoxButton

	button1.SetImage(-1);
	button1.m_nID = m_uomComboBox_ID=GET_ID;
	m_ToolBar.InsertButton(button1);
	
	CMFCToolBarComboBoxButton uomComboBox(m_uomComboBox_ID, 
	-1 /// * no image 
	, CBS_DROPDOWNLIST //| CBS_NOINTEGRALHEIGHT // default style 
	, MIN_DIALOG_WIDTH-124 // pixels wide 
	);	
	
	// load list of all uoms
	//InitUom();
	int iUomCode;
	TCHAR cUnitName[2024];	
	CString str;

	int count = fnc_UOM::GetCountUom();
	for(int i=0; i<count; ++i)
	{
		iUomCode = fnc_UOM::GetCodeUom( i ); 
		if(!CGeoInfo::IsLinearUnit(iUomCode)) continue;
		fnc_UOM::GetUomName(iUomCode, cUnitName);
		str = cUnitName;
		uomComboBox.AddItem(str,iUomCode);	
		//uomComboBox.AddItem(fnc_UOM::GetUomNameByIndex(i));
	}
	uomComboBox.SelectItem(fnc_UOM::GetUomNameByIndex( fnc_UOM::GetUomIndex(fnc_UOM::Uom_Linear_Metre) ));
	
	// finish adding CMFCToolBarComboBoxButton
	m_ToolBar.ReplaceButton(m_uomComboBox_ID, uomComboBox);
	// setts button
	
	CMFCToolBarButton button5(0, 0, NULL, FALSE, TRUE);
	button5.SetImage(m_settingsImage_ID);
	//button4.m_strText = "dist";
	button5.m_nID = m_settings_ID=GET_ID;
	//button5.SetStyle(TBBS_CHECKBOX);
	m_ToolBar.InsertButton(button5);
	////////////////////
	///precision combo box
	/*
	button1.SetImage(-1);
	button1.m_nID = m_precComboBox_ID=GET_ID;
	m_ToolBar.InsertButton(button1);
	
	CMFCToolBarComboBoxButton precComboBox(m_precComboBox_ID, 
	-1 /// * no image 
	, CBS_DROPDOWNLIST// | CBS_NOINTEGRALHEIGHT// default style 
	, 70 // pixels wide 
	);	
	

	str;
	str.Format(_T("auto"));
	precComboBox.AddItem(str,0);	
	for(int i=0; i<6; ++i)
	{
		str.Format(_T("%.*lf"), 6-i,pow(10.0,i-6.0));
		precComboBox.AddItem(str,i+1);
	}
	precComboBox.SelectItem(m_precisionType);
		
	// finish adding CMFCToolBarComboBoxButton
	m_ToolBar.ReplaceButton(m_precComboBox_ID, precComboBox);
	

/// */

	m_ToolBar.SetPaneStyle(m_ToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_ToolBar.SetPaneStyle(m_ToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | 
													CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_ToolBar.SetOwner(this);
	m_ToolBar.SetRouteCommandsViaFrame(FALSE);
	//m_ToolBar.EnableQuickCustomization(FALSE);

	return true;
	
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void CScalePanel::OnLoadInits() // after loading attributes
{
	UINT imageID;
	if(m_closeCurve)	
		imageID=m_closeCurveImage_ID;	
	else	
		imageID=m_discloseCurveImage_ID;	
	
	CMFCToolBarButton *cb=((CMFCToolBarButton *)m_ToolBar.GetButton(m_ToolBar.CommandToIndex(m_closeCurve_ID)));
	if(cb) cb->SetImage(imageID);
}
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////



BOOL CScalePanel::GetString(UINT nID, CString& strText)
{
	HINSTANCE  hInstance = AfxGetStaticModuleState()->m_hCurrentResourceHandle;
	UINT resID=0;

	int id=(int)nID;	
	
	if(nID == m_doMeasuring_ID ) resID=IDS_START; 
	else
	if(nID == m_clear_ID ) resID=IDS_CLEAR; 
	else
	if(nID == m_transform_ID ) resID=IDS_TRANSFORM; 
	else
	if(nID == m_showDistance_ID ) resID=IDS_SHOW_DISTANCE; 
	else
	if(nID == m_showSquare_ID ) resID=IDS_SHOW_SQUARE; 
	else
	if(nID == m_uomComboBox_ID ) resID=IDS_SELECT_UNIT; 
	else
	if(nID == m_precComboBox_ID ) resID=IDS_SELECT_PRECISION_D; 
	else
	if(nID == m_closeCurve_ID )
	{
		if(m_closeCurve)
			resID=IDS_CLOSE_CURVE; 
		else
			resID=IDS_DISCLOSE_CURVE; 
	}
	else
	if(nID == m_settings_ID ) resID=IDS_SETTINGS; 
	

	if(resID==0) return FALSE;
		strText.LoadString( hInstance, resID);
	return TRUE;
}



////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
// Automatikischen releases all dynamic allocated IDs of all components of this window
void CScalePanel::DestroyComponents()
{	
	Cdfi_MainApp *pApp = m_pDfi->GetApp();

	if(m_doMeasuring_ID) pApp->GetFncFunctions()->UnregisterFunction(m_doMeasuring_ID);
	
	CWnd* item = NULL;
	item = GetWindow(GW_CHILD);
	int id=0;
 
	while (item != NULL)
	{
		id=item->GetDlgCtrlID();
		pApp->ReleaseID(id);
		item = item->GetNextWindow();
	}	

}
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

void CScalePanel::Hide()
{
	CDockablePane::ShowPane(FALSE, FALSE, FALSE);

#ifdef PANEL_IS_OPTIONAL 	
	m_isVisible=false;
#else
	EndPanelFunction();	
#endif		

}////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

void CScalePanel::Show()
{
	CDockablePane::ShowPane(TRUE, FALSE, TRUE); //вызываем CDockablePane::ShowPane(), не CIC_Pane::ShowPane() - иначе сработает OnShowPane
	OnDocumentChange();
#ifdef PANEL_IS_OPTIONAL 	
	m_isVisible=true;	
#else
	DoPanelFunction();
#endif

}
////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
void CScalePanel::OnCbnSelChange()
{
	CMFCToolBarComboBoxButton * pComboBox =	(CMFCToolBarComboBoxButton *)m_ToolBar.GetButton(m_ToolBar.CommandToIndex(m_uomComboBox_ID));

	m_unitCode2=(int)pComboBox->GetItemData();

	CalcPolygon(this);		
}////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
void CScalePanel::OnCbnSelChangePrec()
{
	CMFCToolBarComboBoxButton * pComboBox =	(CMFCToolBarComboBoxButton *)m_ToolBar.GetButton(m_ToolBar.CommandToIndex(m_precComboBox_ID));

	m_precisionTypeD=(int)pComboBox->GetItemData();

	CalcPolygon(this);		
}
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
/**/
bool CScalePanel::DoPanelFunction()
{
	int numFunction = m_pDfi->GetApp()->GetFncFunctions()->GetFuncIndex((void*)MeasuringFunction);

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
bool CScalePanel::EndPanelFunction()
{
	int numFunction = m_pDfi->GetApp()->GetFncFunctions()->GetFuncIndex((void*)MeasuringFunction);

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
		
		ScaleDataDelete(true);		
		m_pDocument = NULL;
		m_pView = NULL;
	}



	return false;
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void CScalePanel::OnDocumentChange( )
{
	
	Cdfi_Document* pDoc =  m_pDfi->GetMainFrame()->GetActiveDocument();

	if(!pDoc)	return;

	SetUomOfDoc();
	
	/////
	CalcPolygon(this);
		
}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void CScalePanel::PrintResults()
{
	
//	if(!this->m_pData) return;

	CString sLm, sLmz, sLp, sLpz; 
	CString sLc, sLcz;
	CString sSP, sSM;
	CString sSC;

	sLc.Format(_T("%f"), m_Distance2);//fLc);
	sLcz.Format(_T("%f"), m_LastStep2);// fLcz);
	sSC.Format(_T("%f"), m_Square2);

	DistEdit2.SetWindowTextW(sLc);
	StepEdit2.SetWindowTextW(sLcz);
	SquareEdit2.SetWindowTextW(sSC);

	/// print default units type
	CString str = _T("");	
	//str = _T("");

	if(m_pDocument)
	{
		TCHAR uomName[1024];
		CGeoInfo *pGeoInfoDoc=m_pDocument->GetDocGeoInfo(); 
		pGeoInfoDoc->GetUnitName( uomName );	// ??????
		str = uomName;
	}	


} 

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
void CScalePanel::OnChangeMeasuring()
{  
	if(CheckMeasuring(m_pDfi,NULL)==true)
	{
		

	}
	else
		OnStopMeasuring();
	
	//OnDocumentChange();
}

void CScalePanel::OnStopMeasuring()
{  
	
}
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

void CScalePanel::AdjustLayout()
{
	
	static const int padding = 5;
	static const int staticTextWidth = 15;

	if (m_ToolBar.m_hWnd) //&& DistEdit1.m_hWnd && DistEdit2.m_hWnd)
	{
		CRect rcClient, rect;
		GetClientRect( &rcClient );
		int cyToolBar = m_ToolBar.CalcFixedLayout( FALSE, TRUE ).cy;
		
		rect.SetRect( rcClient.left, rcClient.top, rcClient.right, rcClient.top + cyToolBar );
		m_ToolBar.MoveWindow( rect );

		return;
		/*
		DistLabel.MoveWindow(rcClient.left + padding, rcClient.top + cyToolBar + 5,
			staticTextWidth, 20 );

		DistEdit1.MoveWindow(rcClient.left + padding + staticTextWidth, rcClient.top + cyToolBar + 2,
			rcClient.right/2 - 2*padding - staticTextWidth, 20 );
				
		DistEdit2.MoveWindow(rcClient.left+rcClient.right/2+padding+staticTextWidth, rcClient.top + cyToolBar + 2,
			rcClient.right/2 - 2*padding - staticTextWidth, 20 );\*/
	}
	
	
}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
int CScalePanel::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CIC_Pane::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return CreateComponents();
}

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

void CScalePanel::OnSize(UINT nType, int cx, int cy)
{
	//if (cx < MIN_DIALOG_WIDTH)
	//	cx = MIN_DIALOG_WIDTH;

	//if (cy < MIN_DIALOG_HEIGHT)
	//	cy = MIN_DIALOG_HEIGHT;

	CIC_Pane::OnSize(nType, cx, cy);

	AdjustLayout();
}

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

BOOL CScalePanel::OnShowPane(BOOL bShow)
{
#ifndef PANEL_IS_OPTIONAL
	return bShow ? DoPanelFunction() : EndPanelFunction(), ::EndFunction(m_pDfi);
#else
	return false;
#endif
}

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

void CScalePanel::OnClose()
{
}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void CScalePanel::OnSizingPane(UINT fwSide, LPRECT pRect)
{
	if ( pRect->right - pRect->left < MIN_DIALOG_WIDTH)
		pRect->right = pRect->left + MIN_DIALOG_WIDTH;	

	if ( pRect->bottom - pRect->top < MIN_DIALOG_HEIGHT)
		pRect->bottom = pRect->top + MIN_DIALOG_HEIGHT;
}


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
BOOL CScalePanel::OnEraseBkgnd(CDC* pDC)
{
	CPen pen(PS_SOLID, 0, ::GetSysColor(COLOR_3DFACE));
	CBrush brush(::GetSysColor(COLOR_3DFACE));
	
	CRect clientRect;
	GetClientRect(&clientRect);
	pDC->SelectObject(&pen);
	pDC->SelectObject(&brush);
	pDC->Rectangle(&clientRect);

	return CIC_Pane::OnEraseBkgnd(pDC);
}
/////////////////////////////////////////////////////////////////////////////
void CScalePanel::OnBnClickedShowDistanceCheck()
{	
	AFX_MANAGE_STATE(m_pDfi->GetMainFrame()->GetModuleState());

	CMFCToolBarButton * button =	(CMFCToolBarButton  *)m_ToolBar.GetButton(m_ToolBar.CommandToIndex(m_showDistance_ID));
	
	m_showDistance=!m_showDistance;//>IsPre  ShowDistanceCheck.GetCheck();

	CalcPolygon(this);
	
}
/////////////////////////////////////////////////////////////////////////////
void CScalePanel::OnBnClickedShowSquareCheck()
{	
	AFX_MANAGE_STATE(m_pDfi->GetMainFrame()->GetModuleState());

	CMFCToolBarButton * button =	(CMFCToolBarButton  *)m_ToolBar.GetButton(m_ToolBar.CommandToIndex(m_showSquare_ID));
	
	m_showSquare=!m_showSquare;//>IsPre  ShowDistanceCheck.GetCheck();

	CalcPolygon(this);
	
}
/////////////////////////////////////////////////////////////////////////////


void CScalePanel::OnBnClickedCloseCurveCheck()
{
	CMFCToolBarButton * button =	(CMFCToolBarButton  *)m_ToolBar.GetButton(m_ToolBar.CommandToIndex(m_closeCurve_ID));


	if(m_closeCurve)
	{
		button->SetImage(m_discloseCurveImage_ID);
	}
	else
	{
		button->SetImage(m_closeCurveImage_ID);
	}
	m_closeCurve=!m_closeCurve;

	m_ToolBar.UpdateButton(m_ToolBar.CommandToIndex(m_closeCurve_ID));
	
	m_ToolBar.InvalidateButton(m_ToolBar.CommandToIndex(m_closeCurve_ID));

	m_ToolBar.RedrawWindow();
	//button-> >GetParentWnd()->UpdateWindow();
	//CalcPolygon(this);
	DoCloseCurve(this);
	
}
/////////////////////////////////////////////////////////////////////////////
void CScalePanel::CloseCurve()
{
	OnBnClickedCloseCurveCheck();
}
/////////////////////////////////////////////////////////////////////////////
void CScalePanel::OnBnClickedSettsButton()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CDlgSetts  dlg;//IDD_DIALOG_SETTS);// = new CDlgSetts();//GetWindow(GW_CHILD));// m_pView->GetWnd());

	dlg.m_pDfi=m_pDfi;
	dlg.m_lineWidth=m_lineWidth;
	dlg.m_lineStyle=m_lineStyle;
	dlg.m_lineColorNum=m_lineColorNum;
	dlg.m_textBacklight=m_textBacklight;
	dlg.m_lineColor=m_lineColor;
	dlg.m_showDistance=m_showDistance;
	dlg.m_showSquare=m_showSquare;
	dlg.m_precisionTypeD=m_precisionTypeD;
	dlg.m_precisionTypeS=m_precisionTypeS;
	dlg.m_linearAlways = m_linearAlways;

	INT_PTR nRet;
	nRet = dlg.DoModal(); // Создание окна диалога
	DWORD er;
	switch (nRet) // Как было закрыто окно диалога
	{
	case -1 :
		er=GetLastError();
	//	 AfxMessageBox(_T("Dialog box could not be created!"));
		break;
		case IDOK: // Кнопкой OK			
			m_lineWidth=dlg.m_lineWidth;
			m_lineStyle=dlg.m_lineStyle;
			m_lineColorNum=dlg.m_lineColorNum;
			m_textBacklight=dlg.m_textBacklight;
			m_lineColor=dlg.m_lineColor;
			m_precisionTypeD=dlg.m_precisionTypeD;
			m_precisionTypeS=dlg.m_precisionTypeS;
			m_showDistance=dlg.m_showDistance;
			m_showSquare=dlg.m_showSquare;
			m_linearAlways = dlg.m_linearAlways;
			ReinitUom();
			CalcPolygon(this);
		break;

		case IDCANCEL: // Кнопкой Cancel			
		break;
	}


	//delete dlg;
}


////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////
void CScalePanel::OnBnClickedClearButton()
{
	ClearPolygon();
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////
void CScalePanel::OnBnClickedTransformButton()
{
	TransformToVector();
}




/////////////////////////////////////////////////////////////////////////////
/*
void CScalePanel::OnBnClickedStartButton()
{
	int numFunction;
	IC_PARAM param;
	IC_FUNCTION_IDENTIFY fi;
          
	memset( &param, 0, sizeof(IC_PARAM) );
		
	numFunction = m_pDfi->GetApp()->GetFncFunctions()->GetFuncIndex((void*)MeasuringFunction);

	if (numFunction != -1)
	{
		IC_FUNCTION_IDENTIFY fi;
		m_pDfi->GetApp()->GetFncFunctions()->GetFunctionInfo(numFunction, &fi);
		if ((fi.fnState & FNSTATE_CHECKED) == 0)
		{
			param.message = FM_CALL_FUNCTION;
			m_pDfi->GetApp()->GetFncFunctions()->DoFunction(numFunction, NULL, FALSE);

		}
		else
		{	
			param.message = FM_END_FUNCTION;
			m_pDfi->GetApp()->GetFncFunctions()->DoFunction( numFunction, &param, FALSE );
		}
		OnChangeMode();
	}

	
}
*/
/////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void OnCommand( UINT nID, UINT nCode )
{
	//if(nCode == IDC_START_BUTTON)
	{
		int n=0;
	}
}
/////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void CScalePanel::OnSetFocus(CWnd *pOldWnd)
{	
}
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////


bool CScalePanel::ButtonsCheckEnable()
{
	return m_pDfi->GetMainFrame()->GetActiveDocument() ? TRUE : FALSE;
	
	//return ((CCmdUI*)button)->IsWindowEnabled();
}



///////////////////////////////////////////////////////////////////////////////////////////
BOOL CScalePanel::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	AFX_MANAGE_STATE(m_pDfi->GetMainFrame()->GetModuleState());
	
	if (pHandlerInfo == NULL)
	{
		if(nID == m_doMeasuring_ID)//m_doMeasuring_ID)
		{
			//dispatch to mainframe
			return ((CFrameWnd*)m_pDfi->GetMainFrame())->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
			//return CIC_Pane::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
		}
		if( nCode ==  WM_CLOSE )
		{
			OnCommand(nCode,nCode);
		}
		else
		/*
		if( nCode == WM_SETFOCUS)
		{
			OnSetFocus(NULL);
			return TRUE;
		}
		else
		
				
		
		if( nCode == WM_COMMAND )
		{
			OnCommand(nCode,nCode);
		}
		else
		if( nCode == WM_UPDATEUISTATE )
		{
			OnCommand(nCode,nCode);	
		}
		else
		*/
		if( nCode == CN_COMMAND )
		{
			if (nID == m_clear_ID)
			{
				OnBnClickedClearButton();
			}
			else
			if (nID == m_transform_ID)
			{
				OnBnClickedTransformButton();
			}
			else
			if (nID == m_settings_ID)
			{
				OnBnClickedSettsButton();
			}
			else	
			if(nID == m_showDistance_ID)
			{
				OnBnClickedShowDistanceCheck();
				return TRUE;
			}
			else	
			if(nID == m_showSquare_ID)
			{
				OnBnClickedShowSquareCheck();
				return TRUE;
			}
			else
			if (nID == m_closeCurve_ID)
			{
				OnBnClickedCloseCurveCheck();
				return TRUE;
			}			
				
		}
		else
		if(nCode == CBN_SELCHANGE)
		{
			if(nID == m_uomComboBox_ID)
			{
				this->OnCbnSelChange();
				return TRUE;
			}
			else		
			if(nID == m_precComboBox_ID)
			{
				this->OnCbnSelChangePrec();
				return TRUE;
			}
		}
		else
		if( nCode == CN_UPDATE_COMMAND_UI )
		{			
			if (nID == m_ID)
			{				
				((CCmdUI*)pExtra)->Enable(TRUE);
				return TRUE;
			} 
			else
			if(nID == m_showDistance_ID)
			{
				((CCmdUI*)pExtra)->Enable(ButtonsCheckEnable());
				((CCmdUI*)pExtra)->SetCheck ( m_showDistance);
			}
			else
			if(nID == m_showSquare_ID)
			{
				((CCmdUI*)pExtra)->Enable(ButtonsCheckEnable());
				((CCmdUI*)pExtra)->SetCheck ( m_showSquare);
			}
			
			else
			{	
				((CCmdUI*)pExtra)->Enable(ButtonsCheckEnable());
				//CheckEnable((CCmdUI*)pExtra);
				//((CCmdUI*)pExtra)->Enable(StartButton.IsWindowEnabled());
				return true;
			}

			
			//CheckVisible((CCmdUI*)pExtra);
			return TRUE;
		}
		else
		{
			//dispatch to mainframe
			return ((CFrameWnd*)m_pDfi->GetMainFrame())->OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);		
		}
	}

	
	return CIC_Pane::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
afx_msg LRESULT CScalePanel::OnIdleUpdateCmdUI(WPARAM wParam, LPARAM)
{
	// Если снять комментарий, то все команды будут проходить через CCatalogizationPanel::OnCmdMsg();
	// без снятия комментария все команды проходят через CMainFrame::OnCmdMsg()
	 OnUpdateCmdUI((CFrameWnd *)this, (BOOL)wParam);

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////







////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

bool MeasuringFunction(CDFI* pDfi, IC_PARAM* pParam)
{
	// not correct way!!!!!!!!!!!!!!!!!
	//// Check function type
	if ( pParam )
	{
		switch(pParam->message)
		{
			case FM_CALL_FUNCTION : // no wait!
				GetScaleData(pDfi)->OnChangeMeasuring();
			return true;
			
			case FM_DEFAULT :
				GetScaleData(pDfi)->OnChangeMeasuring();
			return true;

			case FM_END_FUNCTION :
				GetScaleData(pDfi)->OnStopMeasuring();
			return true;

			default:
				return false;
		}		
	}
	return true;
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

bool CheckMeasuring(CDFI *pDfi, CCmdUI *pExtra)
{
	int numFunction;
	
	numFunction = pDfi->GetApp()->GetFncFunctions()->GetFuncIndex((void*)MeasuringFunction);

	if (numFunction != -1)
	{
		IC_FUNCTION_IDENTIFY fi;

		pDfi->GetApp()->GetFncFunctions()->GetFunctionInfo(numFunction, &fi);

		if ((fi.fnState & FNSTATE_CHECKED) == 1) return true;
	}
	return false;
}



////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

bool UpdateMeasuring(CDFI * pDfi, CCmdUI * pExtra)
{
	Cdfi_Document* pDocument;
	int iRasterCount = 0;
		

	if (pDocument = pDfi->GetMainFrame()->GetActiveDocument())
	{
		if (pDocument->LockDocument(MODE_ACCESS_READ))
		{
			iRasterCount = pDocument->GetLayers()->GetNumberLayers();
			
			pDocument->UnlockDocument(MODE_ACCESS_READ);
		}
	}

	return iRasterCount > 0;
}


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

bool MeasuringWndProc(CDFI* pdfi, IC_PARAM* pParam)
{
	return ScaleDataWindowProc(pdfi,pParam,GetScaleData(pdfi));
}


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
















///////////////                         TOOLBAR   ////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

void CScaleToolBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
	CIC_ToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
}

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

INT_PTR CScaleToolBar::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
{
	// check child windows first by calling CMFCBaseToolBar	
	INT_PTR nHit = (INT_PTR) CMFCBaseToolBar::OnToolHitTest(point, pTI);
	if (nHit != -1)
		return nHit;

	// now hit test against CMFCToolBar buttons
	nHit = ((CMFCToolBar*)this)->HitTest(point);
	if (nHit != -1)
	{
		CMFCToolBarButton* pButton = GetButton((int)nHit);
		if (pButton == NULL)
		{
			return -1;
		}

		if (pTI != NULL)
		{
			CScalePanel* pPanel = (CScalePanel*)GetParent();

			CString szFullText;
			CString strTipText;
			CString strDescr;

			pPanel->GetString(pButton->m_nID, szFullText);
			strTipText = szFullText;
			
			if (strTipText.IsEmpty())
			{
				return -1;
			}		
			
			CTooltipManager::SetTooltipText(pTI, m_pToolTip, AFX_TOOLTIP_TYPE_TOOLBAR, strTipText, strDescr );
									
			GetItemRect((int)nHit, &pTI->rect);
			pTI->uId = (pButton->m_nID == (UINT) -1) ? 0 : pButton->m_nID;
			pTI->hwnd = m_hWnd;
		}

		nHit = (pButton->m_nID == (UINT) -1) ? 0 : pButton->m_nID;
	}

	return nHit;
}
/////////////////////////////////////////////////////////////////
int CScaleToolBar::LoadImage(int resID)
{
	HBITMAP hBitmap;
	int id=0;

	CMFCToolBarImages* pToolBarImages = GetLockedImages();

	// load image for button
	if (resID)
	{
		hBitmap = this->m_pDfi->GetMainFrame()->LoadResourceBitmap(AfxGetStaticModuleState()->m_hCurrentResourceHandle, resID);
		if( hBitmap )
		{
			id = pToolBarImages->AddImage( hBitmap, TRUE );
			::DeleteObject( hBitmap );
		}
	}	
	return id;
}
////////////////////////////////////////////////////////////////////////////////////////




