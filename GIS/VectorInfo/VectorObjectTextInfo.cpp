// VectorObjectTextInfo.cpp : implementation file
//

#include "stdafx.h"

#include "VectorObjectTextInfo.h"
#include "afxdialogex.h"

#include "dfi_vector.h"
#include "fn_vector.h"
#include "vectorcomfunction.h"
#include "dfi_Layer.h"
#include "dfi_VectorObjectStream.h"

#include "Geography\geoinfo.h"
#include "Geography\ITransformerManager.h"

#include "VectorObjectTextInfo.h"


// CVectorObjectTextInfo dialog

IMPLEMENT_DYNAMIC(CVectorObjectTextInfo, CDialogEx)

CVectorObjectTextInfo::CVectorObjectTextInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVectorObjectTextInfo::IDD, pParent)
	, m_sCentreX(_T(""))
	, m_sCentreY(_T(""))
	, m_sReText(_T(""))
{
	m_pDfi = NULL;
	m_pView = NULL;
	m_pDocument = NULL;
	m_NumLayer = -1;
	m_pVectorObject = NULL;
	m_pVectorObjectNew = NULL;

	m_styleChanged = false;
}

CVectorObjectTextInfo::~CVectorObjectTextInfo()
{
}

void CVectorObjectTextInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CENTRE_X, m_sCentreX);
	DDX_Text(pDX, IDC_EDIT_CENTRE_Y, m_sCentreY);
	DDX_Text(pDX, IDC_RICHEDIT_TEXT, m_sReText);
}


BEGIN_MESSAGE_MAP(CVectorObjectTextInfo, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_STYLE, &CVectorObjectTextInfo::OnBnClickedButtonStyle)
	ON_BN_CLICKED(IDOK, &CVectorObjectTextInfo::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT_CENTRE_X, &CVectorObjectTextInfo::OnEnChangeEditCentreX)
	ON_EN_KILLFOCUS(IDC_EDIT_CENTRE_X, &CVectorObjectTextInfo::OnEnKillfocusEditCentreX)
	ON_EN_CHANGE(IDC_EDIT_CENTRE_Y, &CVectorObjectTextInfo::OnEnChangeEditCentreY)
	ON_EN_KILLFOCUS(IDC_EDIT_CENTRE_Y, &CVectorObjectTextInfo::OnEnKillfocusEditCentreY)
END_MESSAGE_MAP()


// CVectorObjectTextInfo message handlers
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void CVectorObjectTextInfo::SetParam( CDFI *pDfi, Cdfi_View* pView, Cdfi_Document *pDoc, int numLayer, Cdfi_VectorObject *pVectorObject )
{
	m_pDfi = pDfi;
	m_pView = pView;
	m_pDocument = pDoc;
	m_NumLayer = numLayer;
	m_pVectorObject = pVectorObject;
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void CVectorObjectTextInfo::SetInfo(void)
{
AFX_MANAGE_STATE( AfxGetStaticModuleState() );

int   n =3;
double Length, Square, SquareLin = 0, LengthSphere = 0;
Cdfi_AttributesConst * pAttrConst = NULL;
Cdfi_Attributes * pAttr = NULL;
TCHAR sUomName[MAX_GEOSTRING_SIZE];

	pAttr = m_pDfi->GetApp()->GetAttributes();
	pAttrConst = m_pDfi->GetApp()->GetAttrConst();

    /// set format    
	if ( pAttr->FindAttribute( pAttrConst->m_sGEO_PRECISION, pAttrConst->m_sGEO_PRECISION_UNIT) )	
		n = pAttr->Item( pAttrConst->m_sGEO_PRECISION, pAttrConst->m_sGEO_PRECISION_UNIT)->GetInt();

	if( ( n<0 )||(n>100) )
		n=3;

	m_sFormat.Format(_T("%%.%if"), n );	
	///////////////////

	if( m_pVectorObject->GetType() != VE_TEXT)
		return;

	m_pVectorObject->GetBoundRect( &m_rcBound );			
	//m_dCentreX = (m_rcBound.left + m_rcBound.right )/2.0;
	//m_dCentreY = (m_rcBound.top + m_rcBound.bottom )/2.0;

	m_dCentreX = m_pVectorObject->GetObjText()->GetTextPoint().x;
	m_dCentreY = m_pVectorObject->GetObjText()->GetTextPoint().y;

	m_sCentreX.Format( m_sFormat, m_dCentreX );
	m_sCentreY.Format( m_sFormat, m_dCentreY );

	m_pVectorObject->GetMeasures( &Length, &Square );
	
	// если угловые координаты - пересчитываем в линейные
	SquareLin = Square;
	LengthSphere = Length;
		
	int uom = m_pDocument->GetDocGeoInfo()->GetGeoProjection()->GetUnit();
	
	if( m_pDocument->GetDocGeoInfo()->IsAngleUnit(uom) )
	{
		SquareLin = m_pVectorObject->SphericalPolygonAreaEarth( uom, fnc_UOM::Uom_Linear_Kilometre );
		LengthSphere = m_pVectorObject->SphericalLenAzimutEarth( uom, NULL, fnc_UOM::Uom_Linear_Kilometre );
	}

	// uom name
	memset( sUomName, 0, MAX_GEOSTRING_SIZE * sizeof(TCHAR) );
	m_pDocument->GetDocGeoInfo()->GetShortUnitName( sUomName );

	/////////////////////////////
	switch ( m_pVectorObject->GetType() )
	{
	   case VE_NULL: 
		   {			   
			   m_sType.LoadString( IDS_OBJECT_TYPE_NULL );
		   }break;

	   case VE_TEXT:
		   {			   
			   m_sType.LoadString( IDS_OBJECT_TYPE_TEXT );
			   m_sReText = m_pVectorObject->GetObjText()->GetText();

		   }break;

	   

	      default:
			  {
				  m_sType = _T("");				  
			  }break;
	}
	
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
BOOL CVectorObjectTextInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  Add extra initialization here
	
	SetInfo();

	UpdateData(FALSE);

return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void CVectorObjectTextInfo::OnBnClickedOk()
{
MOVE_VE_BOUND_RECT Data;
CIC_Rect3DD rcBound;
Cdfi_Vector *pVectorLayer;
__int64 id;
CString str;

    pVectorLayer = m_pDocument->GetLayers()->GetLayer( m_NumLayer )->GetVector();
	
    m_pVectorObject->GetBoundRect( &rcBound );

	//// Set src bound rect
	Data.topLeftSrc.x = rcBound.left;
	Data.topLeftSrc.y = rcBound.top;

	Data.topRightSrc.x = rcBound.right;
	Data.topRightSrc.y = rcBound.top;

	Data.bottomRightSrc.x = rcBound.right;
	Data.bottomRightSrc.y = rcBound.bottom;
	
	Data.bottomLeftSrc.x = rcBound.left;
	Data.bottomLeftSrc.y = rcBound.bottom;

	//// Set dest bound rect
	Data.topLeftDest.x = m_rcBound.left;
	Data.topLeftDest.y = m_rcBound.top;

	Data.topRightDest.x = m_rcBound.right;
	Data.topRightDest.y = m_rcBound.top;

	Data.bottomRightDest.x = m_rcBound.right;
	Data.bottomRightDest.y = m_rcBound.bottom;

	Data.bottomLeftDest.x = m_rcBound.left;
	Data.bottomLeftDest.y = m_rcBound.bottom;
	//////////////////////////////
	Data.ptDelta.x =0.0;
	Data.ptDelta.y =0.0;

	Data.pDoc = m_pDocument;
	Data.pVectorObject = m_pVectorObject;
	Data.pVectorObjectNew = NULL;
	Data.numLayer = m_NumLayer;	

	MoveVectorObjBoundRect( m_pDfi, &Data );
	
	if ( Data.pVectorObjectNew )
	{
	   id = m_pVectorObject->GetID();
	   m_pVectorObjectNew = Data.pVectorObjectNew;

	   UpdateData( TRUE );

	   m_pVectorObjectNew->GetObjText()->SetText( m_sReText );

	   //update bound rect
	 	CRect drawRect;
		CIC_Rect3DD geoRect;

		Cdfi_MemoryDC *pMemoryDC = m_pView->GetLayerMemDC(m_NumLayer);
		if(!pMemoryDC)
			pMemoryDC = m_pView->GetScreenMemDC();
	    m_pVectorObjectNew->GetDrawItemRect(m_pView, pMemoryDC, &drawRect, FALSE);
	    m_pView->GetCoordView()->ClientToGeo(&drawRect, &geoRect);
	    m_pVectorObjectNew->SetBoundRect(geoRect);
	}

	// TODO: Add your control notification handler code here
	OnOK();
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

void CVectorObjectTextInfo::OnEnChangeEditCentreX()
{
double offset, CentreXPrev;

    UpdateData( TRUE );

    CentreXPrev = m_dCentreX;

	m_dCentreX = _ttof(m_sCentreX);
	//m_sCentreX.Format( m_sFormat, m_dCentreX );

	offset = m_dCentreX - CentreXPrev;
	m_rcBound.left += offset;
	m_rcBound.right += offset;		

	UpdateData( FALSE );
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void CVectorObjectTextInfo::OnEnKillfocusEditCentreX()
{
double offset, CentreXPrev;

    UpdateData( TRUE );

    CentreXPrev = m_dCentreX;

	m_dCentreX = _ttof(m_sCentreX);
	m_sCentreX.Format( m_sFormat, m_dCentreX );

	offset = m_dCentreX - CentreXPrev;
	m_rcBound.left += offset;
	m_rcBound.right += offset;

	UpdateData( FALSE );	
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void CVectorObjectTextInfo::OnEnChangeEditCentreY()
{
double offset, CentreYPrev;

    UpdateData( TRUE );

    CentreYPrev = m_dCentreY;

	m_dCentreY = _ttof(m_sCentreY);
	//m_sCentreY.Format( m_sFormat, m_dCentreY );

	offset = m_dCentreY - CentreYPrev;
	m_rcBound.top += offset;
	m_rcBound.bottom += offset;

	UpdateData( FALSE );	
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void CVectorObjectTextInfo::OnEnKillfocusEditCentreY()
{
double offset, CentreYPrev;

    UpdateData( TRUE );

    CentreYPrev = m_dCentreY;

	m_dCentreY = _ttof(m_sCentreY);
	m_sCentreY.Format( m_sFormat, m_dCentreY );

	offset = m_dCentreY - CentreYPrev;
	m_rcBound.top += offset;
	m_rcBound.bottom += offset;

	UpdateData( FALSE );	
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void CVectorObjectTextInfo::OnBnClickedButtonStyle()
{
	//ASSERT(FALSE);
	// Пытаемся найти индентификатор функции вызова диалога стиля
	long ifindex = m_pDfi->GetApp( )->GetFncFunctions( )->GetFuncIndexByName( _T( "StyleChooseCom" ) );

	// Если не нашли, завершаемся
	if ( ifindex < 0 )
		return;

	// Создаем структурку с параметрами вызова
	IC_PARAM param;
	memset( &param, 0, sizeof( param ) );
	param.message = FM_DEFAULT;
	param.lParam = (LPARAM)m_pVectorObject;

	// Вызываем диалог выбора стиля
	m_styleChanged = m_pDfi->GetApp( )->GetFncFunctions( )->DoFunction( ifindex, &param, FALSE );
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////