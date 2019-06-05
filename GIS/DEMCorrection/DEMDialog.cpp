#include "stdafx.h"
#include "fn_demcorrection.h"
#include "ArgsDemcorrection.h"
#include "DEMDialog.h"
#include "afxdialogex.h"

#include "dfi_vectortable.h"
#include "dfi_vectorobject.h"

#include "XFunctions.h"
// CDEMDialog dialog

IMPLEMENT_DYNAMIC(CDEMDialog, CDialogEx)



CDEMDialog::~CDEMDialog()
{
}

void CDEMDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//DDX_Control(pDX, IDC_DEM_OBJECTS_GROUP, m_objectsSourceGroup);
	DDX_Control(pDX, IDC_DEM_OBJ_ALL_RADIO, m_objectsSourceRadio);
	DDX_Radio(pDX, IDC_DEM_OBJ_ALL_RADIO, m_objectsSource);

	DDX_Control(pDX, IDC_DEM_LEVELS_GROUP, m_levelsSourceGroup);
	DDX_Control(pDX, IDC_DEM_LEVEL_Z_RADIO, m_levelsSourceRadio);
	DDX_Radio(pDX, IDC_DEM_LEVEL_Z_RADIO, m_levelSource);
	DDX_Control(pDX, IDC_DEM_LEVEL_COMBO, m_levelAttrCombo);
	//DDX_CBString(pDX, IDC_DEM_LEVEL_COMBO, m_levelAttr);
	DDX_Control(pDX, IDC_DEM_LEVEL_EDIT, m_levelEdit);
	//DDX_Text(pDX, IDC_DEM_LEVEL_EDIT, m_level);

	DDX_Control(pDX, IDC_DEM_REF_ABS_RADIO, m_refRadio);
	DDX_Radio(pDX, IDC_DEM_REF_ABS_RADIO, m_reference);

	DDX_Control(pDX, IDC_DEM_ZONE_GROUP, m_zoneGroup);
	DDX_Control(pDX, IDC_DEM_ZONE_CHECK, m_zoneCheck);
	DDX_Check(pDX, IDC_DEM_ZONE_CHECK, m_zone);

	//DDX_Control(pDX, IDC_DEM_ZONE_SMOUTH_NONE_RADIO, m_zoneGradientRadio);
	DDX_Control(pDX, IDC_DEM_ZONE_LINEAR_CHECK, m_zoneLinearCheck);
	DDX_Check(pDX, IDC_DEM_ZONE_LINEAR_CHECK, m_zoneGradient);
	//DDX_Control(pDX, IDC_DEM_ZONE_ROUND_CHECK, m_zoneRoundingCheck);
	//DDX_Check(pDX, IDC_DEM_ZONE_ROUND_CHECK, m_zoneRounding);
	DDX_Control(pDX, IDC_DEM_ZONE_WIDTH_STATIC, m_zoneWidthStatic);
	DDX_Control(pDX, IDC_DEM_ZONE_WIDTH_EDIT, m_zoneWidthEdit);

	DDX_Control(pDX, IDC_DEM_RASTERIZE_BUTTON, m_rasterizeButton);
	DDX_Control(pDX, IDC_DEM_READ_LEVEL_BUTTON, m_readLevelsButton);
	DDX_Control(pDX, IDC_DEM_RELIEF_CHECK, m_reliefCheck);
	DDX_Check(pDX, IDC_DEM_RELIEF_CHECK, m_relief);

	DDX_Control(pDX, IDC_DEM_RASTER_CUT_CHECK, m_rasterCutCheck);
	DDX_Check(pDX, IDC_DEM_RASTER_CUT_CHECK, m_rasterCut);
	DDX_Control(pDX, IDC_DEM_UOM_COMBO, m_uomCombo);
	DDX_CBIndex(pDX, IDC_DEM_UOM_COMBO, m_uom);
	DDX_Control(pDX, IDC_DEM_ZONE_WIDTH_ATTR_RADIO, m_zoneWidthSourceRadio);
	DDX_Radio(pDX, IDC_DEM_ZONE_WIDTH_ATTR_RADIO, m_zoneWidthSource);
	DDX_Control(pDX, IDC_DEM_ZONE_WIDTH_ATTR_COMBO, m_zoneWidthAttrCombo);
	DDX_Control(pDX, IDC_DEM_VECTOR_COMBO, m_vectorCombo);
	DDX_Control(pDX, IDC_DEM_CLEAR_BUTTON, m_clearButton);
	DDX_Control(pDX, IDC_DEM_RASTER_COMBO, m_rasterCombo);
	DDX_Control(pDX, IDC_DEM_RASTER_COPY_CHECK, m_rasterCopyCheck);
	DDX_Check(pDX, IDC_DEM_RASTER_COPY_CHECK, m_rasterCopy);
	DDX_Control(pDX, IDC_DEM_ZONE_FACTOR_CHECK, m_zoneFactorCheck);
	DDX_Check(pDX, IDC_DEM_ZONE_FACTOR_CHECK, m_zoneFactor);
	DDX_Control(pDX, IDC_DEM_OPTION_ZONEONLY_CHECK, m_optionZoneOnlyCheck);
	DDX_Check(pDX, IDC_DEM_OPTION_ZONEONLY_CHECK, m_optionZoneOnly);


	DDX_Control(pDX, IDC_DEM_DRAW_SCELET_CHECK, m_drawSceletCheck);
}


BEGIN_MESSAGE_MAP(CDEMDialog, CDialog)
	ON_BN_CLICKED(IDCANCEL, &CDEMDialog::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_DEM_RASTERIZE_BUTTON, &CDEMDialog::OnBnClickedDemRasterizeButton)
	ON_BN_CLICKED(IDC_DEM_READ_LEVEL_BUTTON, &CDEMDialog::OnBnClickedDemReadLevelButton)
	ON_EN_CHANGE(IDC_DEM_LEVEL_EDIT, &CDEMDialog::OnEnChangeDemLevelEdit)
	ON_EN_CHANGE(IDC_DEM_ZONE_WIDTH_EDIT, &CDEMDialog::OnEnChangeDemZoneWidthEdit)
	ON_BN_CLICKED(IDC_DEM_ZONE_CHECK, &CDEMDialog::OnBnClickedDemZoneCheck)
	//	ON_BN_CLICKED(IDC_DEM_ZONE_SMOUTH_CHECK, &CDEMDialog::OnBnClickedDemZoneSmouthCheck)
	//ON_BN_CLICKED(IDC_DEM_ZONE_ROUND_CHECK, &CDEMDialog::OnBnClickedDemZoneRoundCheck)

	ON_BN_CLICKED(IDC_DEM_OBJ_ALL_RADIO, &CDEMDialog::OnBnClickedDemObjAllRadio)
	ON_BN_CLICKED(IDC_DEM_OBJ_SELECTED_RADIO, &CDEMDialog::OnBnClickedDemObjSelectedRadio)
	ON_BN_CLICKED(IDC_DEM_OBJ_MARKED_RADIO, &CDEMDialog::OnBnClickedDemObjMarkedRadio)

	ON_BN_CLICKED(IDC_DEM_LEVEL_Z_RADIO, &CDEMDialog::OnBnClickedDemLevelZRadio)
	ON_BN_CLICKED(IDC_DEM_LEVEL_ATTR_RADIO, &CDEMDialog::OnBnClickedDemLevelAttrRadio)
	ON_BN_CLICKED(IDC_DEM_LEVEL_EDIT_RADIO, &CDEMDialog::OnBnClickedDemLevelEditRadio)
	ON_CBN_SELCHANGE(IDC_DEM_LEVEL_COMBO, &CDEMDialog::OnCbnSelchangeDemLevelCombo)
	ON_BN_CLICKED(IDC_DEM_REF_ABS_RADIO, &CDEMDialog::OnBnClickedDemRefAbsRadio)
	ON_BN_CLICKED(IDC_DEM_REF_REL_RADIO, &CDEMDialog::OnBnClickedDemRefRelRadio)
	//ON_BN_CLICKED(IDC_DEM_ZONE_SMOUTH_NONE_RADIO, &CDEMDialog::OnBnClickedDemZoneSmouthNoneRadio)
	//ON_BN_CLICKED(IDC_DEM_ZONE_SMOUTH_LINE_RADIO, &CDEMDialog::OnBnClickedDemZoneSmouthLineRadio)
	ON_BN_CLICKED(IDC_DEM_RELIEF_CHECK, &CDEMDialog::OnBnClickedDemReliefCheck)
	ON_BN_CLICKED(IDC_DEM_CLEAR_BUTTON, &CDEMDialog::OnBnClickedClearButton)
	//	ON_BN_CLICKED(IDC_DEM_RASTER_CURRENT, &CDEMDialog::OnBnClickedDemRastrCurrent)
	//ON_BN_CLICKED(IDC_DEM_RASTER_NEW, &CDEMDialog::OnBnClickedDemRastrNew)
	ON_BN_CLICKED(IDC_DEM_RASTER_CUT_CHECK, &CDEMDialog::OnBnClickedDemRastrCutCheck)
	ON_CBN_SELCHANGE(IDC_DEM_UOM_COMBO, &CDEMDialog::OnCbnSelchangeDemUomCombo)
	ON_BN_CLICKED(IDC_DEM_ZONE_WIDTH_ATTR_RADIO, &CDEMDialog::OnBnClickedDemZoneWidthAttrRadio)
	ON_BN_CLICKED(IDC_DEM_ZONE_WIDTH_EDIT_RADIO, &CDEMDialog::OnBnClickedDemZoneWidthEditRadio)
	ON_CBN_SELCHANGE(IDC_DEM_ZONE_WIDTH_ATTR_COMBO, &CDEMDialog::OnCbnSelchangeDemZoneWidthAttrCombo)
	ON_CBN_SELCHANGE(IDC_DEM_VECTOR_COMBO, &CDEMDialog::OnCbnSelchangeDemVectorCombo)
	ON_CBN_SELCHANGE(IDC_DEM_RASTER_COMBO, &CDEMDialog::OnCbnSelchangeDemRastrCombo)
	ON_BN_CLICKED(IDC_DEM_RASTER_COPY_CHECK, &CDEMDialog::OnBnClickedDemRastrCopyCheck)
	ON_BN_CLICKED(IDC_DEM_ZONE_FACTOR_CHECK, &CDEMDialog::OnBnClickedDemZoneFactorCheck)
	ON_BN_CLICKED(IDC_DEM_OPTION_ZONEONLY_CHECK, &CDEMDialog::OnBnClickedDemOptionZoneonlyCheck)
	ON_BN_CLICKED(IDC_DEM_ZONE_LINEAR_CHECK, &CDEMDialog::OnBnClickedDemZoneLinearCheck)
	ON_BN_CLICKED(IDC_DEM_DRAW_SCELET_CHECK, &CDEMDialog::OnBnClickedSceletCheck)
	//ON_BN_CLICKED(IDC_DEM_ZONE_POINTS_STATIC, &CDEMDialog::OnBnClickedDemZonePointsStatic)
	//ON_BN_CLICKED(IDC_DEM_UNDO_BUTTON, &CDEMDialog::OnBnClickedDemUndoButton)
END_MESSAGE_MAP()



// CDEMDialog message handlers










CDEMDialog::CDEMDialog(CDFI* pDfi ) : 	CDEM(pDfi),CDialog(CDEMDialog::IDD, (CWnd*)pDfi->GetMainFrame())
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	m_pDfi = pDfi;

	m_bExitFlag = false;

	m_curRasterLayer = NULL;
	m_curVectorLayer = NULL;

	m_pendingMessage.message = 0;

	Create( IDD_DEM_DIALOG );
			
	SetText(this,GetResourceString(IDD_DEM_DIALOG));

	SetText(GetDlgItem(IDCANCEL), GetResourceString(IDS_DEM_CLOSE_BUTTON));

	
	SetTextByID(this,IDC_DEM_RASTER_GROUP);
	SetTextByID(this,IDC_DEM_LEVELS_GROUP);
	SetTextByID(this,IDC_DEM_ZONE_GROUP);
	SetTextByID(this,IDC_DEM_DRAW_GROUP);

	SetTextByID(this,IDC_DEM_OBJ_ALL_RADIO);		
	SetTextByID(this,IDC_DEM_OBJ_SELECTED_RADIO);		
	SetTextByID(this,IDC_DEM_OBJ_MARKED_RADIO);	

	SetTextByID(this,IDC_DEM_LEVEL_Z_RADIO);
	SetTextByID(this,IDC_DEM_LEVEL_ATTR_RADIO);	
	//SetTextByID(this,IDC_DEM_LEVEL_RELIEF_RADIO);
	SetTextByID(this,IDC_DEM_LEVEL_EDIT_RADIO);		
	
	SetTextByID(this,IDC_DEM_REF_ABS_RADIO);
	//SetTextByID(this,IDC_DEM_REF_ATTR_RADIO);	
	SetTextByID(this,IDC_DEM_REF_REL_RADIO);
		
	SetTextByID(this, IDC_DEM_ZONE_LINEAR_CHECK);
	//SetTextByID(this,IDC_DEM_ZONE_SMOUTH_NONE_RADIO);
	//SetTextByID(this,IDC_DEM_ZONE_SMOUTH_LINE_RADIO);
	//SetTextByID(this,IDC_DEM_ZONE_SMOUTH_EXP_RADIO);
	//SetTextByID(this,IDC_DEM_ZONE_SMOUTH_LOG_RADIO);

	SetTextByID(this,IDC_DEM_ZONE_CHECK);
	//SetTextByID(this,IDC_DEM_ZONE_ROUND_CHECK);
	SetTextByID(this,IDC_DEM_ZONE_WIDTH_STATIC);
	//SetTextByID(this,IDC_DEM_ZONE_GRADIENT_STATIC);
	SetTextByID(this, IDC_DEM_ZONE_FACTOR_CHECK);
		
	SetTextByID(this,IDC_DEM_ZONE_WIDTH_EDIT_RADIO);
	SetTextByID(this,IDC_DEM_ZONE_WIDTH_ATTR_RADIO);

	SetTextByID(this,IDC_DEM_RASTERIZE_BUTTON);
	SetTextByID(this,IDC_DEM_READ_LEVEL_BUTTON);
	SetTextByID(this,IDC_DEM_RELIEF_CHECK);

	SetTextByID(this,IDC_DEM_RASTER_CUT_CHECK);

	SetTextByID(this,IDC_DEM_UOM_COMBO);
	SetTextByID(this,IDC_DEM_UOM_STATIC);

	SetTextByID(this,IDC_DEM_VECTOR_STATIC);
	SetTextByID(this,IDC_DEM_RASTER_STATIC);
	SetTextByID(this,IDC_DEM_RASTER_COPY_CHECK);	
	SetTextByID(this,IDC_DEM_LEVEL_SOURCE_STATIC);
	SetTextByID(this,IDC_DEM_LEVEL_REF_STATIC);

	SetTextByID(this, IDC_DEM_OPTION_ZONEONLY_CHECK);

	OnAnyChange();

	this->UpdateData(FALSE);
		
	SetText(&m_levelEdit,m_levelEditValue);
	SetText(&m_zoneWidthEdit,m_zoneWidthEditValue);

#ifdef _DEBUG
	m_clearButton.ShowWindow(SW_SHOW);
	m_drawSceletCheck.ShowWindow(SW_SHOW);

#endif

	OnChangeLayers();
	//CheckLayersReady();
}







void CDEMDialog::OnAnyChange()
{	
	GetDlgItem(IDC_DEM_LEVEL_COMBO)->EnableWindow(m_levelSource==1?TRUE:FALSE);
	m_rasterCutCheck.EnableWindow((BOOL)m_rasterCopy);
	
	GetDlgItem(IDC_DEM_ZONE_LINEAR_CHECK)->EnableWindow(m_zone);
	GetDlgItem(IDC_DEM_ZONE_WIDTH_ATTR_RADIO)->EnableWindow(m_zone);
	GetDlgItem(IDC_DEM_ZONE_WIDTH_EDIT_RADIO)->EnableWindow(m_zone);
	GetDlgItem(IDC_DEM_UOM_COMBO)->EnableWindow(m_zone);
	GetDlgItem(IDC_DEM_ZONE_WIDTH_EDIT)->EnableWindow(m_zone & (m_zoneWidthSource == 1));
	GetDlgItem(IDC_DEM_ZONE_FACTOR_CHECK)->EnableWindow(m_zone & (m_zoneWidthSource == 0));
	GetDlgItem(IDC_DEM_ZONE_WIDTH_ATTR_COMBO)->EnableWindow(m_zone & (m_zoneWidthSource == 0));
		
	this->m_levelEdit.EnableWindow(m_levelSource == 2?TRUE:FALSE);
}

////////////////////////////////////////////////////////////////////////

bool CDEMDialog::WndProc(UINT pMessage,IC_PARAM * pParam)	
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );

	DEM_DATA *pData = NULL;
	Cdfi_View *pView=NULL;
	Cdfi_Document* pDocument;
	CIC_Point64 ptClient;
	Cdfi_Attributes *pAttributes;

	if(!m_pDfi) return false;

	pData = GetDEMData( m_pDfi );

	if(!pData) return false;
	
	if(m_pDocument)
	{		
		if (m_pDocument->IsLockDocument(MODE_ACCESS_WRITE))
		{
			if(pMessage >= 2000000)
			{
				m_pendingMessage=*pParam;

				m_pendingMessage.message=pMessage;
			}

			return false;
		}
		else
		if(pMessage == FM_OBJECT_UNLOCK)
		{
			if(m_pendingMessage.message)
			{
				pMessage = m_pendingMessage.message;
			
				m_pendingMessage.message = 0;
			}
		}		
	}


	int objType = m_pDfi->GetApp()->GetObjectType( pParam->pObject );
	
	if ( objType == OBJECT_MAINFRAME )
	{	
		Cdfi_MainFrame *pMain;
		pMain = (Cdfi_MainFrame *)pParam->pObject;
		if(!pMain) return false;
		pDocument = pMain->GetActiveDocument();
		if(!pDocument) return false;
		pView = (Cdfi_View *)pDocument->GetActiveView( OBJECT_VIEW );		
	}
	else	
	if ( objType == OBJECT_VIEW )
	{	
		pView = (Cdfi_View *)pParam->pObject;
		if(!pView) return false;
		pDocument = pView->GetDocument();
	}
	else	
	if ( objType == OBJECT_DOCUMENT )
	{
		pDocument = (Cdfi_Document*)pParam->pObject;
		if(!pDocument) return false;
		pView = (Cdfi_View *)pDocument->GetActiveView( OBJECT_VIEW );
	}
	else
	if ( objType = OBJECT_ATTRIBUTES )
	{
		bool ok = false;
		pAttributes = (Cdfi_Attributes *)pParam->pObject;

		if (!m_pDocument)
			return false;
		
		if (!m_pDocument->LockDocument(MODE_ACCESS_READ))
			return false;

		Cdfi_Layers *pLayers = m_pDocument->GetLayers();		

		int n = pLayers->GetNumberLayers();

		for ( ; n > 0; n-- )
		{
			if ( pAttributes == pLayers->GetLayer( n-1)->GetAttributes() )			
			{				
				break;
			}
		}
		m_pDocument->UnlockDocument(MODE_ACCESS_READ);

		if(!n) return false;
		
		pDocument = m_pDocument;
		
		pView = (Cdfi_View *)pDocument->GetActiveView( OBJECT_VIEW );
	}
	else
		return false;
	


	switch(pMessage)
	{	
		case FM_DEFAULT:		
			//UpdateCursor();						
		return true;

		case FM_END_FUNCTION:
		return true;

		case FM_CLOSED_DOCUMENT:
		case FM_CLOSE_DOCUMENT:	
			SetDocument(NULL);	
		return true;
		
		case WM_LBUTTONDOWN:
			SetDocument(pDocument);
		break;

		case FM_CALL_FUNCTION:
		return true;

		case WM_SETFOCUS :
			SetDocument(pDocument); 
		return true;		

		case FM_REMOVE_ALL_LAYERS:
		case FM_REMOVE_LAYER:
			OnChangeLayers();			
		return true;
			
		case FM_VIEW_ACTIVATE :
		case FM_VIEW_DEACTIVATE :

		return true;

		case FM_NEW_DOCUMENT:
		case FM_OPEN_DOCUMENT:
		case FM_SHOW_DOCUMENT:
		case FM_CREATE_DOCUMENT:
			SetDocument(pDocument);
		return true;		
		
		case FM_ATTRIBUTE_CHANGING: // too many times (6) sends  - 30
			break;
		case FM_ATTRIBUTE_CHANGE:	  // too many times (6) sends  - 31
			OnChangeLayers();
			break;
		case FM_LAYER_CLEAR_SELECT:// change edit or active
		//	OnChangeLayers();
			break;
		case FM_LAYER_SET_SELECT:// // change edit or active
			OnChangeLayers();
			break;
		case FM_LAYER_CLEAR_EDIT:// 11
			//OnChangeLayers();
			break;
		case FM_ATTRIBUTE_COMMAND:
			//OnChangeLayers();
			break;
		case FM_LAYER_CHANGE_MODEL:
			OnChangeLayers();
			break;
		case FM_LAYER_SET_EDIT:// 10
			OnChangeLayers();
			break;
		case FM_ADD_LAYER:
		case FM_INSERT_LAYER:
			OnChangeLayers();
		break;	

		case FM_MOVE_LAYERS_TREE_ITEM: // moving layer
			OnChangeLayers();
		break;
		case FM_LAYER_SETPOS:
			//OnChangeLayers();
		return true;

		case FM_LAYER_UP: // no actions
		case FM_LAYER_DOWN:
			//OnChangeLayers();
		return true;	

		case FM_VECTOR_OBJ_ACTIVE :
			OnChangeLayers(); // better OnChangeObject
		return true;
		
		case FM_UPDATE_LAYER :	//wParam = номер слоя, lParam = номер объекта
			OnChangeLayers();
		return false;
		/*
		case FM_OBJECT_UNLOCK :
			if(pDocument->LockDocument(MODE_ACCESS_READ))
			{					
				if(m_pendingMessage.message)
							
					OnChangeLayers();

				m_pendingMessage.message = 0;

				pDocument->UnlockDocument(MODE_ACCESS_READ);
			}
		break;
		*/
				
	}		

	if(pDocument != m_pDocument) return true;
	
	// Objects Control

	switch(pMessage)
	{		
		default :				
			if(pMessage < WM_USER) return true;
			if (pDocument->LockDocument(MODE_ACCESS_READ))				
				pDocument->UnlockDocument(MODE_ACCESS_READ);
		break;		

		case WM_KEYDOWN :
			if (pDocument->LockDocument(MODE_ACCESS_READ))
				pDocument->UnlockDocument(MODE_ACCESS_READ);
		break;
				
		case WM_MOUSEMOVE:
			//UpdateCursor();
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP :
		case WM_LBUTTONUP:
		case WM_LBUTTONDBLCLK:					
			if (!pDocument->LockDocument(MODE_ACCESS_READ))
				return false;		
			pDocument->UnlockDocument(MODE_ACCESS_READ);		
		break;
	}
		

	return true;	 

}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void CDEMDialog::SetView(Cdfi_View *pView)
{
	/*static Cdfi_View *m_pView = 0;

	pView = (Cdfi_View *)m_pDocument->GetActiveView(OBJECT_VIEW);

	if(pView != m_pView)
	{
		if(!pView->IsPreview())
		{
			m_pView = pView;

			OverdrawInit();
			
			UpdateCursor();
		}
		else
			pView = m_pView;
	}*/
}
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
/*
void CDEMDialog::Ready(bool setFlag, bool getFlag)
{	
	m_rasterizeButton.EnableWindow(setFlag);
	m_readLevelsButton.EnableWindow(getFlag);
	
}
*/
////////////////////////////////////////////////////////////////////////////////////
int CDEMDialog::GetVectorLayerNum()
{
	int index = m_vectorCombo.GetCurSel();
	if (index < 0) return -1;
	return m_vectorCombo.GetItemData(index);
}

int CDEMDialog::GetRasterLayerNum()
{
	int index = m_rasterCombo.GetCurSel();
	if (index < 0) return -1;
	return m_rasterCombo.GetItemData(index);
}
////////////////////////////////////////////////////////////////////////////////////
void CDEMDialog::OnChangeLayers()
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );
			
	if(!m_pDocument)
	{
		m_levelAttrCombo.ResetContent();
		m_zoneWidthAttrCombo.ResetContent();
		m_vectorCombo.ResetContent();
		m_rasterCombo.ResetContent();
		m_curVectorLayer = NULL;
		m_curRasterLayer = NULL;
		return;
	}
	
	if (!m_pDocument->LockDocument(MODE_ACCESS_READ)) return;
	
	//////////////	
	
		


	Cdfi_Layer* pLayer;	
	Cdfi_Layers * pLayers = m_pDocument->GetLayers();
	Cdfi_Vector* pVectorLayer = NULL;
	Cdfi_VectorColumn* pVectorColumn = NULL;
	int vectorLayerNum = GetVectorLayerNum();
	int rasterLayerNum = GetRasterLayerNum();


	if (vectorLayerNum<0) vectorLayerNum = pLayers->GetLayerActive(IC_VECTOR_CLASS_NAME);
	if (rasterLayerNum<0) rasterLayerNum = pLayers->GetLayerActive(IC_RASTER_CLASS_NAME);
			


	// init vector layers combo

	//int curIndex = -1;
	//int curLayer = -1;
	int j = 0;	

	m_vectorCombo.ResetContent();
	
	for(int i=0;i<pLayers->GetNumberLayers();i++)
	{
		pLayer = pLayers->GetLayer(i);

		if(pLayer->GetRegisterClass()->IsClass(IC_VECTOR_CLASS_NAME) )
		{
			if(pLayer->GetObject() == m_curVectorLayer)
			
				vectorLayerNum = i;

			m_vectorCombo.AddString(pLayer->GetLayerName());
			m_vectorCombo.SetItemData(j,i);
			j++;
		}
	}	
	
	//SetVectorLayer(curLayer);
	if(!m_curVectorLayer) vectorLayerNum=pLayers->GetLayerActive(IC_VECTOR_CLASS_NAME);

	for(int i = 0; i<m_vectorCombo.GetCount(); i++)
	{
		if(m_vectorCombo.GetItemData(i) == vectorLayerNum)
		{
			m_vectorCombo.SetCurSel(i);
			break;
		}
	}
	// init raster layers combo

	//curLayer = -1;
	j = 0;

	m_rasterCombo.ResetContent();

	for(int i=0;i<pLayers->GetNumberLayers();i++)
	{
		pLayer = pLayers->GetLayer(i);

		if(pLayer->GetRegisterClass()->IsClass(IC_RASTER_CLASS_NAME) )
		{
			if(pLayer->GetObject() == m_curRasterLayer)				
				rasterLayerNum = i;

			m_rasterCombo.AddString(pLayers->GetLayer(i)->GetLayerName());
			m_rasterCombo.SetItemData(j,i);
			j++;
		}
	}
	
	//SetRasterLayer(curLayer);

	if (!m_curRasterLayer) rasterLayerNum = pLayers->GetLayerActive(IC_RASTER_CLASS_NAME);

	for(int i = 0; i<m_rasterCombo.GetCount(); i++)
	{
		if(m_rasterCombo.GetItemData(i) == rasterLayerNum)
		{
			m_rasterCombo.SetCurSel(i);
			break;
		}
	}
	//


	// init Units
	
	TCHAR cUnitName[255];
	CString str;
	CGeoInfo *gInfo=m_pDocument->GetDocGeoInfo();
	int curUomCode=gInfo->GetGeoProjection()->GetUnit();

	gInfo->GetUnitName( curUomCode, cUnitName);

	this->m_zoneWidthStatic.SetWindowTextW(GetResourceString(IDC_DEM_ZONE_WIDTH_STATIC));
	
	// uom
	SetUomCombo();
	
// Init uom combo
	for( int i=0; i<m_uomCombo.GetCount(); i++)			
		if( m_uom == (int)m_uomCombo.GetItemData(i))
		{
			m_uomCombo.SetCurSel(i);
			break;
		}

	if(m_uomCombo.GetCurSel()<0)
		m_uom = curUomCode;

	for( int i=0; i<m_uomCombo.GetCount(); i++)			
		if( m_uom == (int)m_uomCombo.GetItemData(i))
		{
			m_uomCombo.SetCurSel(i);
			break;
		} 

	

	// init attribs
	if (vectorLayerNum >= 0)
	{
		pLayer = pLayers->GetLayer(vectorLayerNum);

		if (pLayer>0)
		{
			pVectorLayer = pLayer->GetVector();

			if (pVectorLayer)
			{
				m_levelAttrCombo.ResetContent();
				m_zoneWidthAttrCombo.ResetContent();

				int size = pVectorLayer->GetVectorTable()->GetVectorColumns()->GetSize();
				CString str;

				for (int i = 0;i<size;i++)
				{
					pVectorColumn = pVectorLayer->GetVectorTable()->GetVectorColumns()->Get(i);
					str = pVectorColumn->name;

					m_levelAttrCombo.AddString(str);
					m_zoneWidthAttrCombo.AddString(str);
				}
			}
		}
	}

	int index = m_levelAttrCombo.FindStringExact(0, m_levelAttr);
	if (index >= 0) m_levelAttrCombo.SetCurSel(index);

	index = m_zoneWidthAttrCombo.FindStringExact(0, m_zoneWidthAttr);
	if (index >= 0) m_zoneWidthAttrCombo.SetCurSel(index);

	
	
	m_pDocument->UnlockDocument(MODE_ACCESS_READ);


	// set buttons
	OnSelectLayers();
}

//////////////////////////////////////////////
void CDEMDialog::OnSelectLayers()
{
	bool setFlag,getFlag;

	CheckLayersReady(setFlag,getFlag);

	m_rasterizeButton.EnableWindow(setFlag);

	m_readLevelsButton.EnableWindow(getFlag);

}
/////////////////////////////////////////////////////////
void CDEMDialog::OnBnClickedCancel()
{
	m_bExitFlag = true;
	EndFunction(m_pDfi);
	//CDialog::OnCancel();
}
///////////////////////////////////////////////////////////////


void CDEMDialog::OnBnClickedDemRasterizeButton()
{
	IC_PARAM Param;
	CArgsDemcorrection Args;
	Cdfi_Document *pDoc;
	CDEM_ARGS *pDemArgs;

	memset(&Param, 0, sizeof(IC_PARAM));
	Param.message = FM_DEFAULT;
	Param.pArguments = &Args;
	
	Args.m_pDialog = this;

	pDemArgs = (CDEM_ARGS *)this;


	DEM_ARGS_COPY(&(Args.m_Args), pDemArgs); // from dialog to args
	{
		int id;
		Param.message = FM_END_FUNCTION;

		if (m_pDfi->GetMainFrame())
		{
			id = m_pDfi->GetApp()->GetFncFunctions()->GetFuncIndex((void *)DEMCorrection);
			if (id > -1)
			{
				m_pDfi->GetApp()->GetFncFunctions()->DoFunction(id, &Param, FALSE);
			}
		}
	}


//	::Rasterize(m_pDfi, &Param);

	OnAnyChange();		
}
/////////////////////////////////////////////////////////////////
bool Rasterize(CDFI* pDFInterface, IC_PARAM *pParam)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CArgsDemcorrection *pArgs;

	CDEM_ARGS *pDemArgs;

	CDEM *pDEM;

	pArgs = (CArgsDemcorrection *)pParam->pArguments;
	
	if (pArgs->m_pDialog) // from dialog
	{
		pDEM = pArgs->m_pDialog;

		pDemArgs = (CDEM_ARGS *)pDEM;

		DEM_ARGS_COPY(&(pArgs->m_Args), pDemArgs); // from dialog to arguments - only needs if serialize is after rasterization

		pDEM->Rasterize();


		//memcpy( (void *)&(pArgs->m_Args), (void *)pDemArgs,sizeof(CDEM_ARGS));
	}
	else // from macros
	{
		pDEM = new CDEM(pDFInterface);

		pDemArgs = (CDEM_ARGS *)pDEM;

		DEM_ARGS_COPY( pDemArgs, &(pArgs->m_Args)); // from argument to class


		pDEM->SetDocument(pDFInterface->GetMainFrame()->GetActiveDocument());

		pDEM->Rasterize();

		delete pDEM;

	}

	return true;
}

/////////////////////////////////////////////////////////////////
void CDEMDialog::OnBnClickedDemReadLevelButton()
{		
	ReadLevels();
}



/////////////////////////////////////////////////////////////////
void CDEMDialog::OnEnChangeDemLevelEdit()
{	
	if(CheckFloatEdit(&m_levelEdit))
		wcsncpy(m_levelEditValue,GetText(&m_levelEdit),50);
	
}



////////////////////////////////////////////////////
void CDEMDialog::OnBnClickedDemZoneCheck()
{
	// TODO: Add your control notification handler code here
	m_zone = m_zoneCheck.GetCheck();

	OnAnyChange();

	
}

////////////////////////////////////////////////////


////////////////////////////////////////////////////

////////////////////////////////////////////////////

void CDEMDialog::OnEnChangeDemZoneWidthEdit()
{

	if(CheckFloatEdit(&m_zoneWidthEdit))
		wcsncpy(m_zoneWidthEditValue, GetText(&m_zoneWidthEdit),50);

}


///////////////////////////////////////////////////////


void CDEMDialog::OnBnClickedDemObjSelectedRadio()
{
	this->m_objectsSource = 2;
	
	OnChangeLayers();
}


///////////////////////////////////////////////////////////
void CDEMDialog::OnBnClickedDemObjMarkedRadio()
{
	this->m_objectsSource = 1;
	
	OnChangeLayers();
}
///////////////////////////////////////////////////////////

void CDEMDialog::OnBnClickedDemObjAllRadio()
{	
	this->m_objectsSource = 0;

	OnChangeLayers();
}

///////////////////////////////////////////////////////////

void CDEMDialog::OnBnClickedDemLevelZRadio()
{
	this->m_levelSource = 0;
	
	OnAnyChange();
}

///////////////////////////////////////////////////////////

void CDEMDialog::OnBnClickedDemLevelAttrRadio()
{
	this->m_levelSource = 1;
	
	OnAnyChange();
}
///////////////////////////////////////////////
///////////////////////////////////////////////////////////

void CDEMDialog::OnBnClickedDemLevelEditRadio()
{	
	this->m_levelSource = 2;
	
	OnAnyChange();
}
///////////////////////////////////////////////////////////

void CDEMDialog::OnCbnSelchangeDemLevelCombo()
{
	
	m_levelAttrCombo.GetLBText(m_levelAttrCombo.GetCurSel(),m_levelAttr);
	

}

///////////////////////////////////////////////////////////
void CDEMDialog::OnBnClickedDemRefAbsRadio()
{
	this->m_reference = 0;
	
	OnAnyChange();
}
///////////////////////////////////////////////////////////


void CDEMDialog::OnBnClickedDemRefRelRadio()
{
	this->m_reference = 1;

	OnAnyChange();

}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

void CDEMDialog::OnBnClickedDemZoneLinearCheck()
{
	m_zoneGradient = m_zoneLinearCheck.GetCheck();
}
///////////////////////////////////////////////////////////

void CDEMDialog::OnBnClickedDemReliefCheck()
{
	m_relief = m_reliefCheck.GetCheck();
}

///////////////////////////////////////////////////////////


void CDEMDialog::OnBnClickedClearButton()
{
	ClearRaster();
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void CDEMDialog::OnCbnSelchangeDemUomCombo()
{
	m_uom = (int)m_uomCombo.GetItemData(m_uomCombo.GetCurSel());
}




///////////////////////////////////////////////////////////////////////////////
void CDEMDialog::SetUomCombo() // for all types of uom except angle if it's not in our doc
{
	//CGeoInfo GeoInfo( m_pDfi->GetApp() );

	TCHAR cUnitName[MAX_GEOSTRING_SIZE];
	CString str;
	int uomCode;

	int uomCount, i;
	//BOOL bLenear = TRUE;
	int index;


	CGeoInfo *geoInfo = m_pDocument->GetDocGeoInfo();
	
	int curUomCode = geoInfo->GetGeoProjection()->GetUnit();
	bool angle = geoInfo->IsAngleUnit(curUomCode) ? true : false;
		

	m_uomCombo.ResetContent();
	
	uomCount = fnc_UOM::GetCountUom();
	// init metric system
	for (i = 0; i < uomCount; i++)
	{
		uomCode = fnc_UOM::GetCodeUom(i);

		if (fnc_UOM::IsLinearUom(uomCode))
		{
			geoInfo->GetUnitName(uomCode, cUnitName);

			if (angle)
				str.Format(_T("%s"), cUnitName);
			else
				str = cUnitName;

			index = (int)m_uomCombo.AddString(str);

			m_uomCombo.SetItemData(index, uomCode);

			++index;
		}
	}

	index = 0;

	if (angle)
	{
		for (i = 0; i < uomCount; i++)
		{
			uomCode = fnc_UOM::GetCodeUom(i);

			//if (CGeoInfo::IsAngleUnit(uomCode))
			if(geoInfo->IsAngleUnit(uomCode))
			{			
				geoInfo->GetUnitName(uomCode, cUnitName);

				index = (int)m_uomCombo.AddString(cUnitName);

				m_uomCombo.SetItemData(index, uomCode);

				++index;
			}
		}
	}

}
/////////////////////////////////////////////////////////


void CDEMDialog::OnBnClickedDemZoneWidthAttrRadio()
{
	m_zoneWidthSource = 0;

	OnAnyChange();
}

/////////////////////////////////////////////////////////

void CDEMDialog::OnBnClickedDemZoneWidthEditRadio()
{
	
	m_zoneWidthSource = 1;

	OnAnyChange();
}


/////////////////////////////////////////////////////////

void CDEMDialog::OnCbnSelchangeDemZoneWidthAttrCombo()
{
	m_zoneWidthAttrCombo.GetLBText(m_zoneWidthAttrCombo.GetCurSel(),m_zoneWidthAttr);
}


/////////////////////////////////////////////////////////

void CDEMDialog::OnCbnSelchangeDemVectorCombo()
{
	int index = m_vectorCombo.GetCurSel();

	index = (int)m_vectorCombo.GetItemData(index);

	if(!m_pDocument) return;

	if(!m_pDocument->LockDocument(MODE_ACCESS_READ)) return;

	if(m_pDocument->GetLayers()->GetLayer(index))

		m_curVectorLayer = m_pDocument->GetLayers()->GetLayer(index)->GetObject();

	else

		m_curVectorLayer = NULL;

	m_pDocument->UnlockDocument(MODE_ACCESS_READ);
	
	OnSelectLayers();
}


/////////////////////////////////////////////////////////


void CDEMDialog::OnCbnSelchangeDemRastrCombo()
{
	
	int index = m_rasterCombo.GetCurSel();
	
	if(!m_pDocument) return;

	if(!m_pDocument->LockDocument(MODE_ACCESS_READ)) return;

	index = (int)m_rasterCombo.GetItemData(index);

	if(m_pDocument->GetLayers()->GetLayer(index))

		m_curRasterLayer = m_pDocument->GetLayers()->GetLayer(index)->GetObject();	

	else

		m_curRasterLayer = NULL;

	m_pDocument->UnlockDocument(MODE_ACCESS_READ);
	
	OnSelectLayers();
}
///////////////////////////////////////////////////////////

void CDEMDialog::OnBnClickedDemRastrCutCheck()
{
	m_rasterCut = m_rasterCutCheck.GetCheck();
}
/////////////////////////////////////////////////////////

void CDEMDialog::OnBnClickedDemRastrCopyCheck()
{
	m_rasterCopy = m_rasterCopyCheck.GetCheck();

	OnAnyChange();
}

///////////////////////////////////////////////////

void CDEMDialog::OnBnClickedDemZoneFactorCheck()
{
	m_zoneFactor = m_zoneFactorCheck.GetCheck();
}


void CDEMDialog::OnBnClickedDemOptionZoneonlyCheck()
{
	m_optionZoneOnly = m_optionZoneOnlyCheck.GetCheck();

}


void CDEMDialog::OnBnClickedSceletCheck()
{
	m_drawScelet = m_drawSceletCheck.GetCheck();
}


void CDEMDialog::OnBnClickedDemZonePointsStatic()
{
	// TODO: Add your control notification handler code here
}


