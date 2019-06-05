#include "StdAfx.h"
#include "VectorInfo.h"
#include "VectorInfoDialog.h"
#include "dfi_vectorobjectstream.h"
#include "dfi_OverDraw.h"
#include "dfi_View.h"
#include "dfi_Layer.h"
#include "Resource.h"
#include "fn_vector.h"
#include "afxdialogex.h"
#include "ctype.h"
#include "math.h"
#include "dfi_ColorDialog.h"
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

// CVectorInfoDialog dialog

IMPLEMENT_DYNAMIC(CVectorInfoDialog, CDialog)


#define SPLITTER_MIN_POS 200


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

CVectorInfoDialog::CVectorInfoDialog(CDFI* pDfi /*=NULL*/) : 
	//CDialog(CVectorInfoDialog::IDD, pParent)
	CDialog(CVectorInfoDialog::IDD, (CWnd*)pDfi->GetMainFrame()), VECTOR_INFO(pDfi)		
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
		
	m_objDlg = NULL;
	
	m_objTreeLock = false;

	Create( IDD_VECTOR_INFO );
	
	m_hSplitterCursor = ::LoadCursor( AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_SPLITTER) );
	
	m_SplitterPos = SPLITTER_MIN_POS;

	
	ResizeBars();

	
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

CVectorInfoDialog::~CVectorInfoDialog()
{
	DeleteObject( m_hSplitterCursor );

}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

void CVectorInfoDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB2, m_tab1);
	DDX_Control(pDX, IDC_ATTR_LIST, m_attrList);
	DDX_Control(pDX, IDC_NODES_LIST, m_nodesList);
	DDX_Control(pDX, IDC_OBJ_TREE, m_objTree);
	DDX_Control(pDX, IDC_VINFO_OBJ_TITLE, m_objTitle);
	DDX_Control(pDX, IDC_VINFO_LEFT_PANEL, m_objPanel);
	DDX_Control(pDX, IDC_VINFO_RADIO1, m_objRadio1);
	DDX_Control(pDX, IDC_VINFO_RADIO2, m_objRadio2);
	DDX_Control(pDX, IDC_VINFO_OBJ_FIT_CHECK, m_objectFitCheck);
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CVectorInfoDialog, CDialog)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_NCPAINT()
	ON_WM_SIZING()
	ON_WM_NCHITTEST()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCACTIVATE()
	ON_WM_NCLBUTTONUP()
	ON_WM_NCMOUSEMOVE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()	
	ON_WM_ACTIVATE()
	ON_WM_SETFOCUS()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB2, &CVectorInfoDialog::OnTcnSelchangeTab2)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_NODES_LIST, &CVectorInfoDialog::OnLvnGetdispinfoList)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_ATTR_LIST, &CVectorInfoDialog::OnLvnGetdispinfoAttrList)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_NODES_LIST, &CVectorInfoDialog::OnLvnItemchangedNodesList)
	ON_NOTIFY(NM_DBLCLK, IDC_NODES_LIST, &CVectorInfoDialog::OnNMDblclkNodesList)
	ON_NOTIFY(NM_RCLICK, IDC_NODES_LIST, &CVectorInfoDialog::OnNMRClickNodesList)
	ON_NOTIFY(NM_RETURN, IDC_NODES_LIST, &CVectorInfoDialog::OnNMReturnNodesList)
	ON_NOTIFY(TVN_SELCHANGED, IDC_OBJ_TREE, &CVectorInfoDialog::OnTvnSelchangedObjTree)
	ON_BN_CLICKED(IDC_VINFO_RADIO1, &CVectorInfoDialog::OnBnClickedVinfoRadio1)
	ON_BN_CLICKED(IDC_VINFO_RADIO2, &CVectorInfoDialog::OnBnClickedVinfoRadio2)
	ON_NOTIFY(LVN_KEYDOWN, IDC_NODES_LIST, &CVectorInfoDialog::OnLvnKeydownNodesList)
	ON_EN_CHANGE(IDC_EDIT_TEST, &CVectorInfoDialog::OnEnChangeEditTest)
	ON_NOTIFY(NM_DBLCLK, IDC_ATTR_LIST, &CVectorInfoDialog::OnNMDblclkAttrList)
	ON_NOTIFY(NM_RETURN, IDC_ATTR_LIST, &CVectorInfoDialog::OnNMReturnAttrList)
	ON_BN_CLICKED(IDC_VINFO_OBJ_FIT_CHECK, &CVectorInfoDialog::OnBnClickedVinfoObjFitCheck)

END_MESSAGE_MAP()

// CVectorInfoDialog message handlers


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////


BOOL CVectorInfoDialog::OnInitDialog()
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );
	
	this->SetWindowTextW(GetResourceString(IDS_VINFO_DIALOG_TITLE));

	CDialog::OnInitDialog();
			
	m_tab1.SetParent(this);	
	m_tab1.InsertItem(0,GetResourceString(IDS_VINFO_METRIC_INFO),0);
	m_tab1.InsertItem(1,GetResourceString(IDS_VINFO_ATTR_INFO),0);
	//m_tab1.InsertItem(2,_T("Description"),0);	
	
	m_attrList.SetParent(&m_tab1);
	m_attrList.SetExtendedStyle( LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_attrList.InsertColumn(0,GetResourceString(IDS_VINFO_ATTR_PP), LVCFMT_LEFT, 40 );
	m_attrList.InsertColumn(1, GetResourceString(IDS_VINFO_ATTR_COLUMN), LVCFMT_LEFT, 100 );
	m_attrList.InsertColumn(2, GetResourceString(IDS_VINFO_ATTR_VALUE), LVCFMT_LEFT, 150 );
	m_attrList.SetItemCountEx(0);
	
	m_nodesList.SetParent(&m_tab1);
	m_nodesList.SetExtendedStyle( LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_nodesList.InsertColumn(0, _T("n/n"), LVCFMT_LEFT, 40 );
	m_nodesList.InsertColumn(1, _T("X"), LVCFMT_LEFT, 70 );
	m_nodesList.InsertColumn(2, _T("Y"), LVCFMT_LEFT, 70 );
	m_nodesList.InsertColumn(3, _T("Z"), LVCFMT_LEFT, 70 );
	m_nodesList.SetItemCountEx(0);		
		
	m_objPanel.SetParent(this);
	DWORD style = m_objPanel.GetStyle();
	
	m_objTitle.SetWindowTextW(GetResourceString(IDC_VINFO_OBJ_TITLE));
	m_objTitle.SetParent(&m_objPanel);
	m_objTree.SetParent(&m_objPanel);
	m_objectFitCheck.SetParent(&m_objPanel);

	m_objRadio1.SetWindowTextW(GetResourceString(IDS_VINFO_OBJ_ALL_SHOWED));
	m_objRadio2.SetWindowTextW(GetResourceString(IDS_VINFO_OBJ_EDIT));
	m_objRadio1.SetCheck(1);
	
	m_objectFitCheck.SetWindowTextW(GetResourceString(IDC_VINFO_OBJ_FIT_CHECK));
	m_objectFitCheck.SetCheck(m_fitObjectToRect);
		
	//m_polygonDlg.
#ifdef POLYGON_DIALOG
	m_polygonDlg.Create(IDD_DIALOG_POLYGON,this);
	m_polygonDlg.SetParent(&m_tab1);
	m_objDlg=(CDialog *)&m_polygonDlg;
#endif
	
	Cdfi_Attributes *pAttributes = m_pDfi->GetApp()->GetAttributes();

	Attr(m_fitObjectToRect, GetResourceString(IDS_VINFO_FIT_OBJECT), GetResourceString(IDS_VINFO_DIALOG_TITLE), pAttributes, FALSE);

	m_objectFitCheck.SetCheck(m_fitObjectToRect);
	//m_polygonDlg.ShowWindow(SW_HIDE);

	OnTcnSelchangeTab2(NULL,NULL);

	ResizeBars();
	
	this->UpdateData(FALSE);
		
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
#include "VectorInfo.h"

void CVectorInfoDialog::OnDestroy()
{
	Cdfi_Attributes *pAttributes = m_pDfi->GetApp()->GetAttributes();
	CRect rcDialog;
	GetWindowRect(rcDialog);

	Attr(rcDialog.left, GetResourceString(IDS_VINFO_DIALOG_LEFT), GetResourceString(IDS_VINFO_DIALOG_TITLE), pAttributes, TRUE);
	Attr(rcDialog.top, GetResourceString(IDS_VINFO_DIALOG_TOP), GetResourceString(IDS_VINFO_DIALOG_TITLE), pAttributes, TRUE);
	Attr((m_fitObjectToRect), GetResourceString(IDS_VINFO_FIT_OBJECT), GetResourceString(IDS_VINFO_DIALOG_TITLE), pAttributes, TRUE);

//	pDfi->GetApp()->GetFncFunctions()->SendMessage(FM_ATTRIBUTE_CHANGE, 0, NULL, pDfi->GetMainFrame()->GetActiveDocument());


	if ( !IsIconic() )
		GetWindowRect( &m_pData->rcLast );

	CDialog::OnDestroy();
}

////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

void CVectorInfoDialog::OnCancel()
{
	EndFunction(m_pDfi);
}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

void CVectorInfoDialog::OnSetFocus(CWnd *obj)
{
	DoFunction(m_pDfi);
}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

void CVectorInfoDialog::OnActivate(UINT id, CWnd *obj,BOOL flag)
{
}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

void CVectorInfoDialog::OnSizing(UINT fwSide, LPRECT pRect)
{
	if ( pRect->right - pRect->left < MIN_DIALOG_WIDTH)
		pRect->right = pRect->left + MIN_DIALOG_WIDTH;
	
	if (pRect->bottom - pRect->top < MIN_DIALOG_HEIGHT)
		pRect->bottom = pRect->top + MIN_DIALOG_HEIGHT;

	CDialog::OnSizing(fwSide, pRect);

}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void CVectorInfoDialog::OnTcnSelchangeTab2(NMHDR *pNMHDR, LRESULT *pResult)
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );	

	if(pResult) *pResult = 0;
	int nTab = m_tab1.GetCurSel();

	if(nTab==0)
	{
		m_attrList.ShowWindow(SW_HIDE);
		if(m_objDlg) m_objDlg->ShowWindow(SW_HIDE);
		m_nodesList.ShowWindow(SW_SHOW);
		m_nodesList.SetFocus();
	}	
	else
	if(nTab==1)
	{
		m_nodesList.ShowWindow(SW_HIDE);
		if(m_objDlg) m_objDlg->ShowWindow(SW_HIDE);
		m_attrList.ShowWindow(SW_SHOW);
	}
	else
	if(nTab==2)
	{
		m_nodesList.ShowWindow(SW_HIDE);
		m_attrList.ShowWindow(SW_HIDE);
		if(m_objDlg) m_objDlg->ShowWindow(SW_SHOW);		

	}
	
	ResizeBars();

}


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

void CVectorInfoDialog::ResizeBars(void)
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );	
//AFX_MANAGE_STATE(m_pDfi->GetMainFrame()->GetModuleState());

	int TOP=4;////50;

	if ( m_tab1.m_hWnd && m_objTree.m_hWnd && m_objPanel && m_objectFitCheck)
	{
		CRect rcClient, rcTree, rcTab,rcList;

		GetClientRect( &rcClient );

		m_SplitterPos = max( SPLITTER_MIN_POS, min( m_SplitterPos, rcClient.right - 10 ));
		
		//  panel
		rcTree.SetRect( 2, TOP, m_SplitterPos - 1, rcClient.bottom - 3);
		m_objPanel.MoveWindow(&rcTree);
		
		// obj title
		rcTree.SetRect( 4, 6, m_SplitterPos - 16, 20);
		if(m_objTitle)
			m_objTitle.MoveWindow( &rcTree );

		// radio1
		rcTree.SetRect( 14, 10+24, m_SplitterPos - 16, 2+24+20);		
		m_objRadio1.MoveWindow(&rcTree);		

		// radio2
		rcTree.SetRect( 14, 10+24+22, m_SplitterPos - 16, 2+24+22+20);
		m_objRadio2.MoveWindow(&rcTree);

		// tree
		rcTree.SetRect( 4, 6+22+22+22, m_SplitterPos - 12, rcClient.bottom - (16+24));	
		m_objTree.MoveWindow( &rcTree );

		// fitCheck		
		rcTree.SetRect( 14, rcClient.bottom - (16+16), m_SplitterPos - 12, rcClient.bottom-18);	
		m_objectFitCheck.MoveWindow( &rcTree );
		
		
		// tabs
		rcTab.SetRect( m_SplitterPos + 1, TOP, rcClient.right - 2, rcClient.bottom - 3 );
				
		m_tab1.MoveWindow( &rcTab);
		
		m_tab1.GetClientRect( &rcTab );
		
		//CRect rOUT;
		m_tab1.AdjustRect( FALSE,&rcTab ); // commonly case
	
		if(m_objDlg) m_objDlg->MoveWindow( &rcTab );
		if(m_attrList) m_attrList.MoveWindow( &rcTab );
		if(m_nodesList.m_hWnd) m_nodesList.MoveWindow( &rcTab );
	}
		
		
	
}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

void CVectorInfoDialog::OnSize(UINT nType, int cx, int cy)
{
	SetFocus();

	CDialog::OnSize(nType, cx, cy);

	ResizeBars();
}


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////


void CVectorInfoDialog::SetAttrCount(int num)
{
	m_attrList.SetItemCountEx(num);
}


///////////////////////////////////////////////////////////////////////////////////
// Filling out attributes list
void CVectorInfoDialog::OnLvnGetdispinfoAttrList(NMHDR *pNMHDR, LRESULT *pResult)
{	
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );	


	if(!m_pDocument) return;


	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);

	int iItemIndx= pDispInfo->item.iItem;
	CString str;
	void* pValue;
	
	*pResult = 0;

	if(pDispInfo->item.mask & LVIF_TEXT);
	else return;

	if(pDispInfo->item.iSubItem==0)
	{			
		str.Format(_T("%5d"),iItemIndx);
		lstrcpy(pDispInfo->item.pszText, str);
		*pResult = 0;
		return;
	}
 
	Cdfi_Document* pDocument = m_pDocument;

	if(!pDocument) return;
	 
	if( !pDocument->LockDocument( MODE_ACCESS_READ ) )
			return;

	if ( m_LayerNum != -1 )
	{
		Cdfi_Document* pDocument = m_pDocument;
		Cdfi_Layer* pLayerObject = NULL;
		Cdfi_Vector* pVectorLayer = NULL;
		Cdfi_VectorColumn* pVectorColumn = NULL;

		pLayerObject = pDocument->GetLayers()->GetLayer( m_LayerNum );

		if (m_ObjectID != -1 )
		{
			pVectorLayer = pLayerObject->GetVector(); 
			pVectorColumn = pVectorLayer->GetVectorTable()->GetVectorColumns()->Get( iItemIndx );


			if(pDispInfo->item.iSubItem==1)
			{				
				str.Format(_T("%s"),pVectorColumn->name);
				lstrcpy(pDispInfo->item.pszText, str);
			}
			else
			if(pDispInfo->item.iSubItem==2)
			{
				pValue = pVectorLayer->GetVectorTable()->GetColumnValue( m_ObjectID, iItemIndx );
				str.Empty();
				switch ( pVectorColumn->type )
				{
					case COLUMN_TYPE_CHAR:				str = PCHAR2STRING((char*)pValue);				break;
					case COLUMN_TYPE_WCHAR:				str = (LPCTSTR)pValue;				break;
					case COLUMN_TYPE_BYTE:				str.Format( _T("%i"), *(BYTE*)pValue );				break;
					case COLUMN_TYPE_SUINT:				str.Format( _T("%i"), *(unsigned short*)pValue );				break;
					case COLUMN_TYPE_SINT:				str.Format( _T("%i"), *(short*)pValue );				break;
					case COLUMN_TYPE_UINT:				str.Format( _T("%i"), *(unsigned int*)pValue );				break;
					case COLUMN_TYPE_INT:				str.Format( _T("%i"), *(int*)pValue );				break;
					case COLUMN_TYPE_FLOAT:				str.Format( _T("%f"), *(float*)pValue );				break;
					case COLUMN_TYPE_DOUBLE:				str.Format( _T("%f"), *(double*)pValue );				break;
					case COLUMN_TYPE_DECIMAL:
					{
						CString FormatString;
						FormatString.Format(_T("%i.%i"), pVectorColumn->width, pVectorColumn->decimal_precision);
						FormatString.Insert( 0, _T("%") );
						FormatString.AppendChar( 'f' );
						str.Format(FormatString, *(double*)pValue);
						str.Trim();
					}
					break;
					case COLUMN_TYPE_DATE:
						str.Format(_T("%02i.%02i.%04i"), ((IC_DATE*)pValue)->Day, ((IC_DATE*)pValue)->Month, ((IC_DATE*)pValue)->Year);
					break;
					case COLUMN_TYPE_LOGICAL:
						str = *(BOOL*)pValue ? _T("TRUE") : _T("FALSE");
					break;
				}
				//s.Format(_T("%s"),pVectorColumn->name);
				lstrcpy(pDispInfo->item.pszText, str);
			}
		}
	 }
	 
	pDocument->UnlockDocument( MODE_ACCESS_READ );
	*pResult = 0;

}


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

void CVectorInfoDialog::SetColumnValueAsString(  int nColumn, const CString str )
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );	

	if(!m_pDocument) return;

	
	if (!m_pDocument->LockDocument(MODE_ACCESS_READ)) return;
						

	Cdfi_Vector* pVectorLayer;

	Cdfi_VectorColumn* pVectorColumn = NULL;
	
	pVectorLayer = (Cdfi_Vector *)m_pDocument->GetLayers()->GetLayer( m_LayerNum )->GetVector();

	void *pValue = NULL;

	CString sYear, sMonth, sDay;
	
	__int64 nObjID = m_ObjectID;
	
	pVectorColumn = pVectorLayer->GetVectorTable()->GetVectorColumns()->Get( nColumn );
	pValue = new BYTE[ pVectorColumn->GetSize() ];

	switch ( pVectorColumn->type )
	{
		case COLUMN_TYPE_CHAR:
			strncpy_s( (char*)pValue, pVectorColumn->GetSize(), STRING2PCHAR(str), min(str.GetLength(), pVectorColumn->width) );
			pVectorLayer->GetVectorTable()->SetColumnValue( nObjID, nColumn, pValue );
			break;
		case COLUMN_TYPE_WCHAR:
			_tcsncpy_s( (LPTSTR)pValue, pVectorColumn->GetSize() / sizeof(TCHAR), (LPCTSTR)str, min(str.GetLength(), pVectorColumn->width) );
			pVectorLayer->GetVectorTable()->SetColumnValue( nObjID, nColumn, pValue );
			break;
		case COLUMN_TYPE_BYTE:
			*(BYTE*)pValue = (BYTE)_ttoi( str );
			pVectorLayer->GetVectorTable()->SetColumnValue( nObjID, nColumn, pValue );
			break;
		case COLUMN_TYPE_SUINT:
			*(unsigned short*)pValue = (unsigned short)_ttoi( str );
			pVectorLayer->GetVectorTable()->SetColumnValue( nObjID, nColumn, pValue );
			break;
		case COLUMN_TYPE_SINT:
			*(short*)pValue = (short)_ttoi( str );
			pVectorLayer->GetVectorTable()->SetColumnValue( nObjID, nColumn, pValue );
			break;
		case COLUMN_TYPE_UINT:
			*(unsigned int*)pValue = (unsigned int)_ttoi( str );
			pVectorLayer->GetVectorTable()->SetColumnValue( nObjID, nColumn, pValue );
			break;
		case COLUMN_TYPE_INT:
			*(int*)pValue = _ttoi( str );
			pVectorLayer->GetVectorTable()->SetColumnValue( nObjID, nColumn, pValue );
			break;
		case COLUMN_TYPE_FLOAT:
			*(float*)pValue = (float)_ttof( str );
			pVectorLayer->GetVectorTable()->SetColumnValue( nObjID, nColumn, pValue );
			break;
		case COLUMN_TYPE_DOUBLE:;
		case COLUMN_TYPE_DECIMAL:
			*(double*)pValue = _ttof( str );
			pVectorLayer->GetVectorTable()->SetColumnValue( nObjID, nColumn, pValue );
			break;
		case COLUMN_TYPE_DATE:
			if (str.GetLength() == 8)
			{
				sDay = str.Left( 2 );
				sMonth = str.Mid( 2, 2 );
				sYear = str.Mid( 4, 4 );
				((IC_DATE*)pValue)->Year = _ttoi( sYear );
				((IC_DATE*)pValue)->Month = _ttoi( sMonth );
				((IC_DATE*)pValue)->Day = _ttoi( sDay );
				pVectorLayer->GetVectorTable()->SetColumnValue( nObjID, nColumn, pValue );
			}
			break;
		case COLUMN_TYPE_LOGICAL:
			*(BOOL*)pValue = str == "TRUE" ? TRUE : FALSE;
			pVectorLayer->GetVectorTable()->SetColumnValue( nObjID, nColumn, pValue );
			break;
	}
	
	if ( pValue )
		delete [] pValue;
	
	m_pDocument->SetModified();

	m_pDocument->UnlockDocument(MODE_ACCESS_READ);
	
	
}


///////////////////////////////////////////////////////////////
// On change Nodes list
void CVectorInfoDialog::OnLvnItemchangedNodesList(NMHDR *pNMHDR, LRESULT *pResult)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	UpdateSelectedNodesList();
	
}

///////////////////////////////////////////////////////////////
// Filling out Nodes list
void CVectorInfoDialog::OnLvnGetdispinfoList(NMHDR *pNMHDR, LRESULT *pResult)
{
	//m_nodesList.OnLvnGetdispinfoList(pNMHDR,pResult);
	//return;
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
 //Ёта структура содержит запрос от списка. —юда же мы помещаем данные, которые надо отображать.
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
 
	int iItemIndx= pDispInfo->item.iItem;
	IC_POINT3DD pt; 
	CString s;

	GetNodeByNumber(iItemIndx,pt);
	//CString s=m_vData[iItemIndx];
 
	if(pDispInfo->item.mask & LVIF_TEXT)
	{
		switch(pDispInfo->item.iSubItem)
		{
			case 0: //заполн€ем основной текст					
				s.Format(_T("%05.5d"),iItemIndx+1);
				lstrcpy(pDispInfo->item.pszText, s);
			break;

			case 1 :
				s.Format(_T(" %f"),(float)pt.x);
				lstrcpy(pDispInfo->item.pszText, s);
			break;

			case 2 :
				s.Format(_T(" %f"),(float)pt.y);
				lstrcpy(pDispInfo->item.pszText, s);
			break;

			case 3 :
				s.Format(_T(" %f"),(float)pt.z);
				lstrcpy(pDispInfo->item.pszText, s);
			break;
		}
 
	}
	*pResult = 0;
	
}



///////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// On select object in obj list
void CVectorInfoDialog::OnTvnSelchangedObjTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
		
	if(m_objTreeLock) return;

	m_objTreeLock = true;

	NMTREEVIEW* pnmtv = reinterpret_cast<NMTREEVIEW*>(pNMHDR);
    HTREEITEM hItem = pnmtv->itemNew.hItem;
	
	HTREEITEM layerItem=NULL, objItem=NULL, sectItem=NULL;

	layerItem=hItem;

	if(hItem = m_objTree.GetParentItem( hItem )) // is it not layer
	{
		objItem = layerItem;
		layerItem = hItem;
	}

	if(hItem = m_objTree.GetParentItem( hItem )) // is it not layer too
	{	
		sectItem = objItem;
		objItem = layerItem;
		layerItem = hItem;
	}

	__int64 nObj = -1; 
	int nLayer=-1;	
	int nSect=-1;

	if(layerItem) nLayer = (int)m_objTree.GetItemData( layerItem );
	if(objItem)   nObj = (__int64)m_objTree.GetItemData( objItem );
	if(sectItem)  
		nSect = (int)m_objTree.GetItemData( sectItem );
	else
		if( !m_objTree.GetChildItem( objItem )) // havn't childs - it's single object
			nSect = 0;

	if (layerItem != NULL)
	{		
		//if(sectItem)			m_objTree.Select(sectItem, TVGN_CARET);

		VECTOR_OBJ_INFO vi;
		LPARAM lp=nObj;
		WPARAM wp=nLayer;

		vi.nLayer=nLayer;
		vi.nObj=nObj;
		vi.nSect=nSect;// nSection

		if(nSect == -1)
			vi.nSect = 0;

		//IC_PARAM param;
		//param.wParam=(WPARAM)&vi;
		//param.message=WM_USER_SELECT_OBJ;
		wp=(WPARAM)&vi;
		lp=0;

					
		m_pDfi->GetApp()->GetFncFunctions()->SendMessageW(WM_USER_SELECT_OBJ, wp, lp, m_pDocument); // the best way
		/*	1 way
		if(m_pDocument->LockDocument(MODE_ACCESS_READ)) 
		{

			SetActiveObject(nLayer,nObj,nSect); // no redraw!!!

			m_pDocument->UnlockDocument(MODE_ACCESS_READ);
		}
		*/
		// 3 way
		//Commander(WM_USER_SELECT_OBJ, &param); no!!!!
	}

	m_objTreeLock = false;

	*pResult = 0;
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
// Update obj list
void CVectorInfoDialog::OnUpdateSelectedObjects()
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );
	//VECTOR_INFO::UpdateSelectedObjects();

	if(!m_pDocument) return;

	if(m_objTreeLock) return;

	m_objTreeLock = true;


	int nLayer=-1, newLayer;
	int nSect=-1;
	__int64 nObj=-1, newObj;
	
	
	HTREEITEM layerItem=NULL;	
	HTREEITEM objItem=NULL;	
	HTREEITEM sectItem=NULL;

	CString sLName;
	Cdfi_Layer* pLayer;
	Cdfi_Vector* pVectorLayer;
	int nIdentifyColumn = -1;
	CString sObjectIdentify, sPrefix;

	m_objTree.DeleteAllItems();
	sPrefix.LoadString( IDS_OBJECT_IDENTIFY );	

	for(int i=0;i<GetSelectedObjectsCount();i++)
	{
		GetSelectedObject(i, newLayer, newObj, nSect);
			
		if(nLayer!=newLayer)
		{			
			nLayer=newLayer;	

			pLayer = m_pDocument->GetLayers()->GetLayer( nLayer );
			
			if ( !pLayer ) continue;
			
			pVectorLayer = pLayer->GetVector();
					//помещаем название сло€ в дерево
			sLName = pLayer->GetLayerName();

			//parentObject=m_Tree.AddObjectInfo(NULL,nLayer,,-1);
			layerItem = m_objTree.InsertItem( sLName, TVI_ROOT, TVI_LAST );
			m_objTree.SetItemData( layerItem, (DWORD_PTR)nLayer );	
			
			nObj = -1;
				
		}

		if(newObj != nObj)
		{
			nObj = newObj;
			//помещаем название объекта в дерево
			sObjectIdentify.Empty();
			
			if ( nIdentifyColumn != -1 )
			{
				switch (pVectorLayer->GetVectorTable()->GetVectorColumns()->Get(nIdentifyColumn)->type)
				{
				case COLUMN_TYPE_CHAR:
					sObjectIdentify = PCHAR2STRING((char*)pVectorLayer->GetVectorTable()->GetColumnValue( nObj, nIdentifyColumn ));
					break;
				case COLUMN_TYPE_WCHAR:
					sObjectIdentify = (LPCTSTR)pVectorLayer->GetVectorTable()->GetColumnValue( nObj, nIdentifyColumn );
					break;
				}
			}	


			sObjectIdentify.Trim();

			if ( sObjectIdentify.IsEmpty() )
				sObjectIdentify.Format(_T("%s %i"), sPrefix, nObj);		
		
			//m_objTree.hLayerItem=(HTREEITEM)parentObject;
			objItem = m_objTree.InsertItem( sObjectIdentify, layerItem, TVI_LAST );
			m_objTree.SetItemData( objItem, (DWORD_PTR)nObj );

			m_objTree.Expand( layerItem, TVE_EXPAND );
		}

		if(nSect != -1)
		{
			sObjectIdentify.Format(_T("%s %d"),GetResourceString(IDS_VINFO_OBJ_SECTION),nSect+1);
			sectItem = m_objTree.InsertItem( sObjectIdentify, objItem, TVI_LAST );
			m_objTree.SetItemData( sectItem, (DWORD_PTR)nSect );

			m_objTree.Expand( objItem, TVE_EXPAND );	
			
			//m_objTree.SetItemState (sectItem, TVIS_SELECTED, TVIS_SELECTED);
				//Select(objItem, TVGN_CARET);

		}

					
	}
	
	m_objTreeLock = false;
}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void CVectorInfoDialog::OnUpdateActiveObject()
{		
	UpdateObjectInfo();

	if(m_objTreeLock) return;

	m_objTreeLock = true;
		
	UpdateSelectedNodesList();

	int nLayer;
	__int64 nObj;
	int nSect;
		
	HTREEITEM layerItem;
	HTREEITEM objItem;
	HTREEITEM sectItem;

	GetActiveObject(nLayer,nObj,nSect);

	layerItem = m_objTree.GetChildItem( TVI_ROOT );

	while ( layerItem )
	{
		//HTREEITEM hParentItem = hItem;
				
		objItem = m_objTree.GetChildItem( layerItem );
		//m_bProcessSelchanged = FALSE;

		while(objItem)
		{			

			if(nLayer == (int)m_objTree.GetItemData( layerItem ) &&
					nObj == (__int64)m_objTree.GetItemData( objItem ) &&
					nSect == -1)
			{
				m_objTree.SelectItem( objItem );
								
				m_objTreeLock = false;

				return;
			}


			sectItem = m_objTree.GetChildItem( objItem );
						
			while ( sectItem )
			{
				if(nLayer == (int)m_objTree.GetItemData( layerItem ) &&
					nObj == (__int64)m_objTree.GetItemData( objItem ) &&
					nSect == (__int64)m_objTree.GetItemData( sectItem ))
				{
					m_objTree.SelectItem( sectItem );
										
					m_objTreeLock = false;

					return;
				}
				
				sectItem=m_objTree.GetNextItem(sectItem,TVGN_NEXT );
				//GetActiveObject(hItem,layerNum,objNum);

				//m_bProcessSelchanged = TRUE;			
			}
			objItem=m_objTree.GetNextItem(objItem,TVGN_NEXT );
		}

		layerItem=m_objTree.GetNextItem(layerItem,TVGN_NEXT );
		//return false;
	}

	m_objTreeLock = false;


	return;
}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
void CVectorInfoDialog::UpdateSelectedNodesList()
{
	m_nodesSelectedPositions.clear();
		
	POSITION pos=m_nodesList.GetFirstSelectedItemPosition();

	int i=0;
		
	while(pos)				
		m_nodesSelectedPositions.push_back(m_nodesList.GetNextSelectedItem(pos));

	if(i==0) m_nodesSelectedPositions.push_back(m_nodesList.GetItemCount());

	m_nodesSelectedPositions.push_back(-1); // last position
		
	DrawSelectedNodes();
}
///////////////////////////////////////////////////////////////
void CVectorInfoDialog::SetNodesCount(int count)
{
	m_nodesList.SetItemCountEx(count); 

	UpdateSelectedNodesList(); // because it related on nodes count
}
/////////////////////////////////////////////////////////////////////////////////
bool CVectorInfoDialog::IsItSelectedNode(int numPoint)
{
	for(int i=0;i<m_nodesSelectedPositions.size();i++) 
		if(m_nodesSelectedPositions[i]==numPoint) return true;
	
	return false;
}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void CVectorInfoDialog::DeleteNodeFromSelected(int n)
{
	m_nodesList.SetItemState(n, 0, LVIS_SELECTED);
}
/////////////////////////////////////////////////////////////////////
int CVectorInfoDialog::GetSelectedNodesCount()
{
	return m_nodesList.GetSelectedCount();
}
/////////////////////////////////////////////////////////////////////
int CVectorInfoDialog::GetNodesCount()
{
	return m_nodesList.GetItemCount();
}
/////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
// addMode 0 - single,  1 -  multiply in any place, 2 - multiply from m_nLastSelected To numPoint
void CVectorInfoDialog::SetNodeSelected(int numPoint, bool selFlag, int addMode) 
{	
	switch(addMode)
	{
		case 1 :
			if(!selFlag)
				m_nodesList.SetItemState(numPoint, 0, LVIS_SELECTED);
			else
				m_nodesList.SetItemState(numPoint, LVIS_SELECTED, LVIS_SELECTED);
			m_nLastSelected=numPoint;
			m_nodesList.Update(numPoint);
			

		break;

		case 0 :				
			m_nodesList.SetItemState(-1, 0, LVIS_SELECTED);
			m_nodesList.SetItemState(numPoint, LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING, LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING);//LVIS_ACTIVATING
			m_nLastSelected=numPoint;
			m_nodesList.Update(numPoint);		
		break;

		case 2 :
			m_nodesDrawLock=true;
			if(m_nLastSelected==-1) m_nLastSelected=numPoint;
			m_nodesList.SetItemState(-1, 0, LVIS_SELECTED);
			if(m_nLastSelected>numPoint)
				for(int i=numPoint;i<=m_nLastSelected;i++)
					m_nodesList.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);			
			else
				for(int i=m_nLastSelected;i<=numPoint;i++)
					m_nodesList.SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
			
			m_nodesDrawLock=false;
		break;
	}
	
	m_nodesList.UpdateWindow();// .Invalidate();

	m_nodesList.EnsureVisible(numPoint,FALSE);

	DrawSelectedNodes();

	CString s;
	/*
	s.Format(_T("mode=%d sc=%d num=%d"),m_mode,GetSelectedNodesCount(),numPoint);

	m_objTitle.SetWindowTextW(s);
	*/

}
/////////////////////////////////////////////////////////////////////////////////
void CVectorInfoDialog::UpdateSelectedNodes()
{
	//DrawSelectedNodes();
	//	m_nodesList.Invalidate();
	int count=GetSelectedNodesCount();
		
	for(int i=0;i<count;i++)
	{
		m_nodesList.Update(GetSelectedNodeIndex(i));
	}
	
}
/////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
void CVectorInfoDialog::ClearSelectedNodes()
{
	m_nodesList.SetItemState(-1, 0, LVIS_SELECTED);
	m_nodesList.Invalidate();  
	m_nLastSelected=-1;
}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
int CVectorInfoDialog::GetSelectedNodeIndex(int pos)
{
	if(pos<m_nodesSelectedPositions.size())
		return m_nodesSelectedPositions.at(pos);
	else 
		return -1;
}
////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

void CVectorInfoDialog::OnMouseMove(UINT nFlags, CPoint point)
{
	
	if ( (point.x >= m_SplitterPos - 1) && (point.x <= m_SplitterPos + 1) )
	{
		if ( point.y >= 50 )
			SetCursor(  m_hSplitterCursor );
	}
	
	CDialog::OnMouseMove(nFlags, point);
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

void CVectorInfoDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
	return;


	//OnTreeDown(nFlags,point);


	if ( (point.x >= m_SplitterPos - 1) && (point.x <= m_SplitterPos + 1) )
	{
		MSG msg;
		BOOL bExitLoop = FALSE;
		int x, prevX = point.x;
		CRect rcClient;
		GetClientRect( &rcClient );

		SetFocus();
		SetCapture();
		SetCursor(  m_hSplitterCursor );

		for( ;!bExitLoop; )
		{		
			::GetMessage(&msg, NULL, 0, 0);
			switch (msg.message)
			{
			case WM_MOUSEMOVE:
				x = GET_X_LPARAM( msg.lParam );
				m_SplitterPos += x - prevX;
				m_SplitterPos = max( SPLITTER_MIN_POS, min( m_SplitterPos, rcClient.right - 220 ) );
				prevX = x;
				ResizeBars();
				break;
			case WM_LBUTTONUP:
				bExitLoop = TRUE;
				break;
			default:
				DispatchMessage(&msg);
			}
		}

		ReleaseCapture();
	}
	else
		CDialog::OnLButtonDown(nFlags, point);
		
}


///////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

void CVectorInfoDialog::OnNMDblclkNodesList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	RunXYZDialog(IDS_VINFO_XYZ_EDIT);

	*pResult = 0;
}
/////////////////////////////////////////////////////////////////////////

void CVectorInfoDialog::OnNMReturnNodesList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	if(m_nodesList.GetSelectedCount()==1)
		RunXYZDialog(IDS_VINFO_XYZ_EDIT);
	else
	if(m_nodesList.GetSelectedCount()>1)
		RunXYZDialog(IDS_VINFO_XYZ_MOVE);
	

	*pResult = 0;

}
///////////////////////////////////////////////////////////////////////
void CVectorInfoDialog::OnNMRClickNodesList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	int mode=RunContextMenu();

	if(mode<1) return;

	if(mode == IDS_VINFO_XYZ_SELECT_ALL)
	{	
		this->m_nLastSelected = GetNodesCount()-1;

		SetNodeSelected(0,true,2);

		return;
	}
		
	RunXYZDialog(mode);

}

///////////////////////////////////////////////////////////////////////

void CVectorInfoDialog::OnBnClickedVinfoRadio1()
{
	m_searchInLayers=SEARCH_ALL_VISIBLE;
	
}

///////////////////////////////////////////////////////////////////////

void CVectorInfoDialog::OnBnClickedVinfoRadio2()
{	
	m_searchInLayers=SEARCH_EDIT_LAYER;
}
//////////////////////////////////////////////////////////////////////
void CVectorInfoDialog::OnBnClickedVinfoObjFitCheck()
{
	// TODO: Add your control notification handler code here
	m_fitObjectToRect = m_objectFitCheck.GetCheck();
}
///////////////////////////////////////////////////////////////////////

void CVectorInfoDialog::OnLvnKeydownNodesList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

		if(pLVKeyDow->wVKey == VK_DELETE)
	{
		if(m_canAddDelete==true && GetSelectedNodesCount()>0)

			RunXYZDialog(IDS_VINFO_XYZ_DEL);
	}
	else
	if(pLVKeyDow->wVKey == VK_INSERT)
	{
		if(m_canAddDelete==true)// && GetSelectedNodesCount()>0)

			RunXYZDialog(IDS_VINFO_XYZ_ADD);
	}	
	else
	{
		if(pLVKeyDow->wVKey == 65)
		{
			int iKeyStatus = GetKeyState( VK_CONTROL );  // VK_MENU VK_CONTROL VK_SHIFT

			if ( iKeyStatus&0x80 )	
			{
				m_nLastSelected = GetNodesCount()-1;

				SetNodeSelected(0,true,2);
			}
		}
	}
	

}

///////////////////////////////////////////////////////////////////////

void CVectorInfoDialog::OnEnChangeEditTest()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the __super::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}



///////////////////////////////////////////////////////////////////////

void CVectorInfoDialog::OnNMDblclkAttrList(NMHDR *pNMHDR, LRESULT *pResult)
{
	
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	int number = 0;
	int fieldItem = pNMItemActivate->iItem;
	int valueItem = pNMItemActivate->iSubItem;
	
	POINT pt = pNMItemActivate->ptAction;
	
	CAttrEditDialog dlg;//IDD_ATTR_EDIT);

	CString str;
	TCHAR s[25];
	m_attrList.GetItemText(fieldItem,0,s,25);
	number = _wtoi(s);
	if(number<0) return;

	Cdfi_Layer* pLayerObject = NULL;
	Cdfi_Vector* pVectorLayer = NULL;
	Cdfi_VectorColumn* pVectorColumn = NULL;

	if (!m_pDocument->LockDocument(MODE_ACCESS_READ)) return;
	
	pLayerObject = m_pDocument->GetLayers()->GetLayer( m_LayerNum );
	m_pDocument->UnlockDocument(MODE_ACCESS_READ);
	
	if (m_ObjectID == -1 ) return;
	
	pVectorLayer = pLayerObject->GetVector(); 
	pVectorColumn = pVectorLayer->GetVectorTable()->GetVectorColumns()->Get( number );
	dlg.m_type=pVectorColumn->type;


	dlg.m_width= pVectorColumn->width;
	dlg.m_prec= pVectorColumn->decimal_precision;
	dlg.m_size= pVectorColumn->GetSize();
	
	m_attrList.GetItemText(fieldItem,1,s,25);
	str.Format(_T("є% d. %s"),number,s);
	dlg.m_fieldName = str;

	m_attrList.GetItemText(fieldItem,2,s,25);
	dlg.m_fieldValue = s;
	
	if(dlg.DoModal()!=IDOK) return;

	SetColumnValueAsString( number, dlg.m_fieldValue );

	m_attrList.RedrawWindow();// > Invalidate();
}


///////////////////////////////////////////////////////////////////////


void CVectorInfoDialog::OnNMReturnAttrList(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

////////////////////////////////////
void CVectorInfoDialog::UpdateObjectInfo()
{
#ifdef POLYGON_DIALOG
	switch(m_objType)
	{
		case VE_POLYGON :
			m_polygonDlg.ShowWindow(SW_SHOW);
			m_polygonDlg.m_pDfi=m_pDfi;
			m_polygonDlg.m_width=this->m_polygonStyle.WidthOutline;
			m_polygonDlg.m_color=this->m_polygonStyle.ColorOutline;
			m_polygonDlg.m_zoom=this->m_polygonStyle.Zooming;
			m_polygonDlg.m_section=this->m_sectionNum;
			m_polygonDlg.m_decrease=this->m_pActivePolygon->GetDecrease();
			m_polygonDlg.m_dir=(this->m_pActivePolygon->GetDirection(FALSE)==-1?true:false);
			m_polygonDlg.m_external=(this->m_pActivePolygon->GetExternal()==0)?false:true;
			m_polygonDlg.Update();
		break;

		default :
			m_polygonDlg.ShowWindow(SW_HIDE);
		break;

	}
	OnTcnSelchangeTab2(NULL,NULL);
#endif
}



///////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////


//


// CAttrEditDialog dialog

IMPLEMENT_DYNAMIC(CAttrEditDialog, CDialogEx)

CAttrEditDialog::CAttrEditDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAttrEditDialog::IDD, pParent)
{

}

CAttrEditDialog::~CAttrEditDialog()
{
}

void CAttrEditDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VINFO_ATTR_VALUE_EDIT, m_valueEdit);
	DDX_Control(pDX, IDC_VINFO_ATTR_MASK, m_valueMaskEdit);
}


BEGIN_MESSAGE_MAP(CAttrEditDialog, CDialogEx)
	ON_WM_SIZE()
	ON_EN_CHANGE(IDC_VINFO_ATTR_VALUE_EDIT, &CAttrEditDialog::OnEnChangeVinfoAttrValueEdit)
	ON_EN_CHANGE(IDC_VINFO_ATTR_MASK, &CAttrEditDialog::OnEnChangeVinfoAttrMask)	
	ON_BN_CLICKED(IDOK, &CAttrEditDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CAttrEditDialog message handlers
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////


BOOL CAttrEditDialog::OnInitDialog()
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );
	
	CDialog::OnInitDialog();
	
	this->SetWindowTextW(GetResourceString(IDD_VINFO_ATTR_EDIT_DIALOG));
	//this->SetWindowTextW(GetResourceString(IDS_VINFO_DIALOG_TITLE));
	this->GetDlgItem(IDC_VINFO_ATTR_FIELD_STATIC)->SetWindowText(m_fieldName);

	if(m_type == COLUMN_TYPE_DATE)
	{
		m_valueMaskEdit.EnableMask(_T("dd dd dddd"), // The mask string
			_T("__.__.____"), // Literal, "_" char = character entry
			_T('1'),_T("1234567890")); // Backspace replace char
		m_valueMaskEdit.SetValidChars(_T("1234567890"));
		m_valueMaskEdit.ShowWindow(SW_SHOW);
		m_valueMaskEdit.SetWindowText(m_fieldValue);
		m_valueEdit.ShowWindow(SW_HIDE);
		
	}
	else
	{
		m_valueMaskEdit.ShowWindow(SW_HIDE);
		m_valueEdit.ShowWindow(SW_SHOW);
	}
	m_valueEdit.SetWindowText(m_fieldValue);

	CPoint point;
	GetCursorPos(&point);
	RECT r;
	this->GetWindowRect(&r);
	this->MoveWindow(point.x,point.y,r.right-r.left,r.bottom-r.top);
	
	//SetSizes();

	return TRUE;
}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

void CAttrEditDialog::OnSize(UINT nType, int cx, int cy)
{
	SetFocus();

	CDialog::OnSize(nType, cx, cy);

	SetSizes();
}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void CAttrEditDialog::SetSizes()
{
	RECT r;
	if(m_valueEdit.m_hWnd && m_valueMaskEdit.m_hWnd)
	{
		m_valueEdit.GetRect(&r);
		m_valueMaskEdit.MoveWindow(&r,TRUE);//.left,r.top,right.);
	}
}
///////////////////////////////////////////////////


void CAttrEditDialog::OnEnChangeVinfoAttrValueEdit()
{
	if(!m_valueEdit.m_hWnd) return;

	static bool lockChanging=false;

	if(lockChanging==true) return;

	lockChanging=true;

	TCHAR ss[1000];

	CString s0;

	m_valueEdit.GetWindowTextW(ss,999);
	int selStart,selEnd;
	
	m_valueEdit.GetSel(selStart,selEnd);

	s0=ss;
		
	switch(m_type )
	{
		case COLUMN_TYPE_CHAR:	
		case COLUMN_TYPE_WCHAR:			
		{
			ss[m_width]=0;
			for(int i=0;i<wcslen(ss);i++)
				//if(! isprint (ss[i]))
				if(ss[i]<20)
				{
				 ss[i]=0;
				 break;
				}
		}
		break;
				
		case COLUMN_TYPE_BYTE:				EditInt(ss,1);					break;
		case COLUMN_TYPE_SUINT:				EditInt(ss,2,false);			break;
		case COLUMN_TYPE_SINT:				EditInt(ss,2);					break;
		case COLUMN_TYPE_UINT:				EditInt(ss,4,false);			break;
		case COLUMN_TYPE_INT:				EditInt(ss,4);break;
		case COLUMN_TYPE_FLOAT:				EditFloat(ss);	break;
		case COLUMN_TYPE_DOUBLE:			EditFloat(ss);					break;
		case COLUMN_TYPE_DECIMAL:			EditFloat(ss,m_width,m_prec);				break;
		case COLUMN_TYPE_LOGICAL:
		{
			ss[1]=0;
			if(ss[0] !='0' || ss[0] !='1')
				ss[0]='0';
			
		}
		break;
		default :	break;
	}
		
	CString s=ss;

	if(s!=s0)
	{
		m_valueEdit.SetWindowText(m_fieldValue);
		m_valueEdit.SetFocus();
		m_valueEdit.SetSel(selStart-1,selEnd-1);//m_fieldValue.GetLength(),m_fieldValue.GetLength());
	}
	else
	{
		m_valueEdit.SetWindowTextW(s);
		m_valueEdit.SetSel(selStart,selEnd);//m_fieldValue.GetLength(),m_fieldValue.GetLength());
		m_valueEdit.SetFocus();
		//m_valueEdit.SetSel(s.GetLength(),s.GetLength());
		m_fieldValue = ss;			
	}	

	lockChanging=false;
}

///////////////////
//bool CheckFloat(TCHAR *ss,int width,int prec, bool isSigned);




bool CAttrEditDialog::EditFloat(TCHAR *ss,int width,int prec)
{
	return CheckFloat(ss,width,prec);
}

///////////////////////
bool CheckFloat(TCHAR *ss,int width,int prec, bool isSigned)
{
	int pointPos=-1; 

	CString s;

	s=ss;	

	for(int i=0;i<s.GetLength();i++)
	{ 
		if(pointPos!=-1 && ((i-pointPos)>prec)) 
		{
			s.Delete(i,1);
			continue;
		}

		if(i > width) 
		{
			s.Delete(i,1);
			continue;
		}

		if(s[i]=='.')
		{			
			if(prec == 0) 
			{
				s.Delete(i,1);
				continue;
			}
			if(pointPos==-1 && i!=-1) { pointPos=i; continue; }
		}
		else
		if(i==0 && (s[i]==L'-') && isSigned==true) continue;		
		else
		if((s[i]>=L'0') && (s[i]<=L'9')) continue;
		

		s.Delete(i,1);
	}

	if(s.GetLength()>14) { s.Truncate(14);}

	if(CString(ss) == s)

		return true;
	
	wcsncpy(ss,s.GetString(),20);

	return false;
}
///////////////////////
bool CAttrEditDialog::EditInt(TCHAR *ss,int digits,bool sign)
{	
	//CString s;
	for(int i=0;i<wcslen(ss);i++)	
		if(i==0 && ss[i]=='-') continue;
		else
		if(!isdigit(ss[i])) { ss[i]=0;break; }
		

	double maxVal=powl((long)2, (long)(digits*8))-1;

	if(sign) maxVal/=2;

	long v=_wtol(ss);

	if(v<0) maxVal++;
	
	v=abs(v);

	if(abs(v)>maxVal) ss[0]=0;

	/*
	
	
	if(sign == true && v < 0)  v=abs(v);
	else sign = false;

	v = v & (long));

	if(sign) v *= -1;

	s.Format(_T("%ld"),v);

	wcsncpy(ss,s.GetString(),20);
	*/
	return true; 

	
}
///////////////////////////////
void CAttrEditDialog::OnEnChangeVinfoAttrMask() // !!! returns previous text
{

	if(!m_valueMaskEdit.m_hWnd) return;
	
	if(!m_valueMaskEdit.IsWindowVisible()) return;
	
	TCHAR ss[50];

	m_valueMaskEdit.GetWindowTextW(ss,49);
	
	m_fieldValue=ss;

}
////////////////////////////////////

void CAttrEditDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	
	OnEnChangeVinfoAttrMask();

	CDialogEx::OnOK();
}













// CPolygonInfo dialog
//////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CPolygonInfo, CDialogEx)

CPolygonInfo::CPolygonInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPolygonInfo::IDD, pParent)
	, m_width(0)
	, m_color(0)
	, m_zoom(FALSE)
	, m_decrease(0)
	, m_dir(FALSE)
	, m_external(0)
	, m_section(0)
{

}

CPolygonInfo::~CPolygonInfo()
{
}

void CPolygonInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VINFO_POLYGON_WIDTH_STATIC, m_widthStatic);
	DDX_Control(pDX, IDC_VINFO_POLYGON_ZOOM_CHECK, m_zoomCheck);
	DDX_Control(pDX, IDC_VINFO_POLYGON_DECREASE_STATIC, m_decreaseStatic);
	DDX_Control(pDX, IDC_VINFO_DECREASE_BUTTON, m_decreaseButton);
	DDX_Control(pDX, IDC_VINFO_POLYGON_DECREASE_SELECT_BUTTON2, m_decreaseSelectButton);
	DDX_Control(pDX, IDC_VINFO_POLYGON_DIRECTION_CHECK2, m_dirCheck);
	DDX_Control(pDX, IDC_CHECK3, m_externalCheck);
	DDX_Text(pDX, IDC_VINFO_POLYGON_WIDTH_STATIC, m_width);
	DDX_Text(pDX, IDC_VINFO_POLYGON_COLOR_STATIC, m_color);
	DDX_Check(pDX, IDC_VINFO_POLYGON_ZOOM_CHECK, m_zoom);
	DDX_Text(pDX, IDC_VINFO_POLYGON_DECREASE_STATIC, m_decrease);
	DDX_Check(pDX, IDC_VINFO_POLYGON_DIRECTION_CHECK2, m_dir);
	DDX_Check(pDX, IDC_CHECK3, m_external);
	DDX_Control(pDX, IDC_VINFO_POLYGON_COLOR_SELECT_BUTTON, m_colorButton);
	DDX_Control(pDX, IDC_VINFO_POLYGON_SECTION_GROUP, m_sectionGroup);
	DDX_Text(pDX, IDC_VINFO_POLYGON_SECTION_GROUP, m_section);
}


BEGIN_MESSAGE_MAP(CPolygonInfo, CDialogEx)
	ON_BN_CLICKED(IDC_VINFO_DECREASE_BUTTON, &CPolygonInfo::OnBnClickedVinfoDecreaseButton)
	ON_BN_CLICKED(IDC_VINFO_POLYGON_COLOR_SELECT_BUTTON, &CPolygonInfo::OnBnClickedVinfoPolygonColorSelectButton)
END_MESSAGE_MAP()


// CPolygonInfo message handlers

void CPolygonInfo::Update()
{	
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );

	CString str;
	str.Format(_T("%d"),m_width);
	m_widthStatic.SetWindowText(str);
	m_colorStatic.SetColor(m_color);
	m_zoomCheck.SetCheck(m_zoom);
	str.Format(_T(" %s є%d "),GetResourceString(IDS_VINFO_OBJ_SECTION),m_section);
	m_sectionGroup.SetWindowTextW(str);	
	str.Format(_T("%d"),m_decrease);
	m_decreaseStatic.SetWindowTextW(str);
	m_dirCheck.SetCheck(m_dir);
	m_externalCheck.SetCheck((BOOL)m_external);

	//str.Format(_T("%d"),m_color);
	//m_widthStatic.SetWindowText(CString(m_width));
}
////////////////////////////////////////////////////
void CPolygonInfo::OnBnClickedVinfoDecreaseButton()
{
	// TODO: Add your control notification handler code here
}
////////////////////////////////////////////////////////////////////

void CPolygonInfo::OnBnClickedVinfoPolygonColorSelectButton()
{
	// TODO: Add your control notification handler code here
	Cdfi_ColorDialog dlg( m_pDfi->GetMainFrame() );
	COLORREF color;

	dlg.SetRGBColor( m_colorStatic.GetColor() );
    
	if (dlg.DoModal() == IDOK)
	{
		color = dlg.GetRGBColor();
		m_colorStatic.SetColor( color , TRUE);
		Invalidate();
		m_color=color;
	}
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////









/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

// CColorButton

IMPLEMENT_DYNAMIC(CColorButton, CButton)

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

CColorButton::CColorButton()
{
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

CColorButton::~CColorButton()
{
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CColorButton, CButton)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void CColorButton::SetColor(COLORREF color, BOOL bRedraw)
{
	m_Color = color;
	if (bRedraw)
		RedrawWindow();	
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

COLORREF CColorButton::GetColor(void)
{
	return m_Color;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
	
void CColorButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
CDC dc;
CRect rect;
CBrush brush(m_Color);
CBrush* pOldBrush;
CPen pen( PS_SOLID, 1, RGB(0, 0, 0) );
CPen* pOldPen;

	dc.Attach(lpDrawItemStruct->hDC);

	GetClientRect( &rect );
				
	pOldBrush = dc.SelectObject( &brush );
	pOldPen = dc.SelectObject( &pen );
				
	dc.Rectangle( &rect );
			
	dc.SelectObject( pOldBrush );
	dc.SelectObject( pOldPen );

	dc.Detach();
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////






