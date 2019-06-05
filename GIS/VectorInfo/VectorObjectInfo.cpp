// VectorObjectInfo.cpp : implementation file
//

#include "stdafx.h"

#include "dfi_vector.h"
#include "fn_vector.h"
#include "VectorObjectInfo.h"
#include "vectorcomfunction.h"
#include "dfi_Layer.h"
#include "dfi_VectorObjectStream.h"

#include "Geography\geoinfo.h"
#include "Geography\ITransformerManager.h"

#include "VectorObjectTextInfo.h"


///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
INT_PTR SelVectorInfo( CDFI *pDfi, Cdfi_View* pView, Cdfi_Document *pDoc, int numLayer, Cdfi_VectorObject *pVOSrc, Cdfi_VectorObject **pVONew, bool *pbStyleChanged )
{
INT_PTR iRet = 0;

	AFX_MANAGE_STATE( AfxGetStaticModuleState() );

	if( pVOSrc->GetType() == VE_TEXT )
	{
		CVectorObjectTextInfo voInfo;		
		voInfo.SetParam( pDfi, pView, pDoc, numLayer, pVOSrc );

		iRet = voInfo.DoModal();

		if(iRet==IDOK)		
			*pVONew = voInfo.m_pVectorObjectNew;		
		else
		{
			if(voInfo.m_pVectorObjectNew)
				voInfo.m_pVectorObjectNew->DeleteObject();
		}

		*pbStyleChanged = voInfo.m_styleChanged;
	}
	else
	{
		CVectorObjectInfo voInfo;
		voInfo.SetParam( pDfi, pDoc, numLayer, pVOSrc );

		iRet = voInfo.DoModal();
		
		if(iRet==IDOK)
			*pVONew = voInfo.m_pVectorObjectNew;
		else
		{
			if(voInfo.m_pVectorObjectNew)
				voInfo.m_pVectorObjectNew->DeleteObject();
		}

		*pbStyleChanged = voInfo.m_styleChanged;
	}

return iRet;
}
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////





// CVectorObjectInfo dialog
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CVectorObjectInfo, CDialog)

CVectorObjectInfo::CVectorObjectInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CVectorObjectInfo::IDD, pParent)
	, m_sLeft(_T(""))
	, m_sRight(_T(""))
	, m_sTop(_T(""))
	, m_sBottom(_T(""))
	, m_sCentreX(_T(""))
	, m_sCentreY(_T(""))
	, m_sType(_T(""))
	, m_sSectionCount(_T(""))
	, m_sLength(_T(""))
	, m_sSquare(_T(""))
	, m_sSquareLin(_T(""))
	, m_sLengthSphere(_T(""))
{
	m_pVectorObject = NULL;
	m_pVectorObjectNew = NULL;

	m_styleChanged = false;
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
CVectorObjectInfo::~CVectorObjectInfo()
{
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void CVectorObjectInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LEFT, m_sLeft);
	DDX_Text(pDX, IDC_EDIT_RIGHT, m_sRight);
	DDX_Text(pDX, IDC_EDIT_TOP, m_sTop);
	DDX_Text(pDX, IDC_EDIT_BOTTOM, m_sBottom);
	DDX_Text(pDX, IDC_EDIT_CENTRE_X, m_sCentreX);
	DDX_Text(pDX, IDC_EDIT_CENTRE_Y, m_sCentreY);
	DDX_Text(pDX, IDC_STATIC_TYPE, m_sType);
	DDX_Text(pDX, IDC_STATIC_SECTION_COUNT, m_sSectionCount);
	DDX_Text(pDX, IDC_STATIC_LENGTH, m_sLength);
	DDX_Text(pDX, IDC_STATIC_SQUARE, m_sSquare);
	DDX_Text(pDX, IDC_STATIC_SQUARE_LIN, m_sSquareLin);
	DDX_Text(pDX, IDC_STATIC_LENGTH_LIN, m_sLengthSphere);
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CVectorObjectInfo, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_STYLE, &CVectorObjectInfo::OnBnClickedButtonStyle)
	ON_BN_CLICKED(IDOK, &CVectorObjectInfo::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT_CENTRE_X, &CVectorObjectInfo::OnEnChangeEditCentreX)
	ON_EN_KILLFOCUS(IDC_EDIT_CENTRE_X, &CVectorObjectInfo::OnEnKillfocusEditCentreX)
	ON_EN_CHANGE(IDC_EDIT_CENTRE_Y, &CVectorObjectInfo::OnEnChangeEditCentreY)
	ON_EN_KILLFOCUS(IDC_EDIT_CENTRE_Y, &CVectorObjectInfo::OnEnKillfocusEditCentreY)
	ON_EN_CHANGE(IDC_EDIT_LEFT, &CVectorObjectInfo::OnEnChangeEditLeft)
	ON_EN_KILLFOCUS(IDC_EDIT_LEFT, &CVectorObjectInfo::OnEnKillfocusEditLeft)
	ON_EN_CHANGE(IDC_EDIT_RIGHT, &CVectorObjectInfo::OnEnChangeEditRight)
	ON_EN_KILLFOCUS(IDC_EDIT_RIGHT, &CVectorObjectInfo::OnEnKillfocusEditRight)
	ON_EN_CHANGE(IDC_EDIT_TOP, &CVectorObjectInfo::OnEnChangeEditTop)
	ON_EN_KILLFOCUS(IDC_EDIT_TOP, &CVectorObjectInfo::OnEnKillfocusEditTop)
	ON_EN_CHANGE(IDC_EDIT_BOTTOM, &CVectorObjectInfo::OnEnChangeEditBottom)
	ON_EN_KILLFOCUS(IDC_EDIT_BOTTOM, &CVectorObjectInfo::OnEnKillfocusEditBottom)
END_MESSAGE_MAP()


// CVectorObjectInfo message handlers
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void CVectorObjectInfo::SetParam( CDFI *pDfi, Cdfi_Document *pDoc, int numLayer, Cdfi_VectorObject *pVectorObject )
{
	m_pDfi = pDfi;
	m_pDocument = pDoc;
	m_NumLayer = numLayer;
	m_pVectorObject = pVectorObject;	
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void CVectorObjectInfo::SetInfo(void)
{
AFX_MANAGE_STATE( AfxGetStaticModuleState() );

CIC_Rect3DD rcBound;
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

	m_pVectorObject->GetBoundRect( &m_rcBound );
	
	m_sLeft.Format(m_sFormat, m_rcBound.left );
	m_sRight.Format(m_sFormat, m_rcBound.right );
	m_sTop.Format(m_sFormat, m_rcBound.top );
	m_sBottom.Format(m_sFormat, m_rcBound.bottom );

	m_dCentreX = (m_rcBound.left + m_rcBound.right )/2.0;
	m_dCentreY = (m_rcBound.top + m_rcBound.bottom )/2.0;
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
			   m_sSectionCount = _T("");
			   m_sLength = _T("");
			   m_sLengthSphere = _T("");
			   m_sSquare = _T("");
			   m_sSquareLin = _T("");
			   
		   }break;

	   case VE_POINT:
		   {			   
			   m_sType.LoadString( IDS_OBJECT_TYPE_POINT );
			   m_sSectionCount.Format(_T("%i"), m_pVectorObject->GetObjPoint()->GetNumPoints() );
			   m_sLength = _T("");
			   m_sLengthSphere = _T("");
			   m_sSquare = _T("");
			   m_sSquareLin = _T("");
		   }break;

	   case VE_LINE:
		   {			   
			   m_sType.LoadString( IDS_OBJECT_TYPE_LINE );
			   m_sSectionCount.Format(_T("%i"), m_pVectorObject->GetObjLine()->GetNumSection() );
			   
			   // length
			   m_sLength.Format(m_sFormat, Length );
			   m_sLength += _T(" "); m_sLength +=sUomName;

			   if( m_pDocument->GetDocGeoInfo()->IsAngleUnit(uom) )
			   {
				   m_sLengthSphere.Format(m_sFormat, LengthSphere );
				   m_sLengthSphere += _T(" km");
			   }
			   else
				   m_sLengthSphere = _T("");

			   m_sSquare = _T("");
			   m_sSquareLin = _T("");
		   }break;

	   case VE_POLYGON:
		   {			   
			   m_sType.LoadString( IDS_OBJECT_TYPE_POLYGON );
			   m_sSectionCount.Format(_T("%i"), m_pVectorObject->GetObjPolygon()->GetRegion()->GetPolygonsCount() );
			   
			   m_sLength.Format(m_sFormat, Length );
			   m_sLength += _T(" "); m_sLength +=sUomName;

			   m_sSquare.Format(m_sFormat, Square );
			   m_sSquare += _T(" "); m_sSquare +=sUomName; m_sSquare += _T("2");

			   if( m_pDocument->GetDocGeoInfo()->IsAngleUnit(uom) )
			   {
					m_sLengthSphere.Format(m_sFormat, LengthSphere );
					m_sLengthSphere += _T(" km");

					m_sSquareLin.Format(m_sFormat, SquareLin );
					m_sSquareLin +=_T(" km2");
			   }
			   else
			   {
				    m_sLengthSphere = _T("");
					m_sSquareLin = _T("");
			   }			   
			   
		   }break;

	   case VE_ELLIPSE:
		   {
			   m_sType.LoadString( IDS_OBJECT_TYPE_ELLIPSE );
			   m_sSectionCount.Format(_T("%i"), 1 );
			   
			   m_sLength.Format(m_sFormat, Length );
			   m_sLength += _T(" "); m_sLength +=sUomName;

			   m_sSquare.Format(m_sFormat, Square );
			   m_sSquare += _T(" "); m_sSquare +=sUomName; m_sSquare += _T("2");

			   if( m_pDocument->GetDocGeoInfo()->IsAngleUnit(uom) )
			   {
					m_sLengthSphere.Format(m_sFormat, LengthSphere );
					m_sLengthSphere += _T(" km");

					m_sSquareLin.Format(m_sFormat, SquareLin );
					m_sSquareLin +=_T(" km2");
			   }
			   else
			   {
				    m_sLengthSphere = _T("");
					m_sSquareLin = _T("");
			   }

		   }break;

	      default:
			  {
				  m_sType = _T("");
				  m_sSectionCount = _T("");
				  m_sLength = _T("");
			      m_sSquare = _T("");
				  m_sSquareLin = _T("");
			  }break;
	}
	///////////////////////////

}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
BOOL CVectorObjectInfo::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO:  Add extra initialization here
	
	SetInfo();

	UpdateData(FALSE);
return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void CVectorObjectInfo::OnBnClickedButtonStyle()
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
void CVectorObjectInfo::OnBnClickedOk()
{
MOVE_VE_BOUND_RECT Data;
CIC_Rect3DD rcBound;
Cdfi_Vector *pVectorLayer;
__int64 id;
CString str;

    pVectorLayer = m_pDocument->GetLayers()->GetLayer( m_NumLayer )->GetVector();
	
	//Cdfi_VectorObjectStream voStream( pVectorLayer, VMEM_READWRITE );

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

	   /*
	   /////////////////////////////////
	   ////  Set History				 
       str.LoadString( IDS_MODIFY_OBJECT );
	   m_pDocument->GetHistory()->AddItem( (LPTSTR)(LPCTSTR)str, HISTORY_ACTION_MODIFY, m_NumLayer,m_pVectorObject, TRUE, &id, AfxGetInstanceHandle(), IDB_MOVE );
	   
	   voStream.ReplaceObject( id, Data.pVectorObjectNew );	   
	   Data.pVectorObjectNew->DeleteObject();

	   pVectorLayer->UpdateGrid();
	   m_pDocument->RedrawViews(TRUE, m_NumLayer );
	   */
	}

	// TODO: Add your control notification handler code here
	OnOK();
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

void CVectorObjectInfo::OnEnChangeEditCentreX()
{
double offset, CentreXPrev;

    UpdateData( TRUE );

    CentreXPrev = m_dCentreX;

	m_dCentreX = _ttof(m_sCentreX);
	//m_sCentreX.Format( m_sFormat, m_dCentreX );

	offset = m_dCentreX - CentreXPrev;
	m_rcBound.left += offset;
	m_rcBound.right += offset;

	m_sLeft.Format(m_sFormat, m_rcBound.left );
	m_sRight.Format(m_sFormat, m_rcBound.right );

	UpdateData( FALSE );
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void CVectorObjectInfo::OnEnKillfocusEditCentreX()
{
double offset, CentreXPrev;

    UpdateData( TRUE );

    CentreXPrev = m_dCentreX;

	m_dCentreX = _ttof(m_sCentreX);
	m_sCentreX.Format( m_sFormat, m_dCentreX );

	offset = m_dCentreX - CentreXPrev;
	m_rcBound.left += offset;
	m_rcBound.right += offset;

	m_sLeft.Format(m_sFormat, m_rcBound.left );
	m_sRight.Format(m_sFormat, m_rcBound.right );

	UpdateData( FALSE );	
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void CVectorObjectInfo::OnEnChangeEditCentreY()
{
double offset, CentreYPrev;

    UpdateData( TRUE );

    CentreYPrev = m_dCentreY;

	m_dCentreY = _ttof(m_sCentreY);
	//m_sCentreY.Format( m_sFormat, m_dCentreY );

	offset = m_dCentreY - CentreYPrev;
	m_rcBound.top += offset;
	m_rcBound.bottom += offset;

	m_sTop.Format( m_sFormat, m_rcBound.top );
	m_sBottom.Format( m_sFormat, m_rcBound.bottom );

	UpdateData( FALSE );	
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void CVectorObjectInfo::OnEnKillfocusEditCentreY()
{
double offset, CentreYPrev;

    UpdateData( TRUE );

    CentreYPrev = m_dCentreY;

	m_dCentreY = _ttof(m_sCentreY);
	m_sCentreY.Format( m_sFormat, m_dCentreY );

	offset = m_dCentreY - CentreYPrev;
	m_rcBound.top += offset;
	m_rcBound.bottom += offset;

	m_sTop.Format( m_sFormat, m_rcBound.top );
	m_sBottom.Format( m_sFormat, m_rcBound.bottom );

	UpdateData( FALSE );	
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void CVectorObjectInfo::OnEnChangeEditLeft()
{
double offset, LeftPrev;

    UpdateData( TRUE );

    LeftPrev = m_rcBound.left;

	m_rcBound.left = _ttof( m_sLeft );
	//m_sLeft.Format( m_sFormat, m_rcBound.left );

	offset = m_rcBound.left - LeftPrev;
	
	m_dCentreX += offset;
	m_rcBound.right += offset;

	m_sCentreX.Format(m_sFormat, m_dCentreX );
	m_sRight.Format(m_sFormat, m_rcBound.right );

	UpdateData( FALSE );
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void CVectorObjectInfo::OnEnKillfocusEditLeft()
{
double offset, LeftPrev;

    UpdateData( TRUE );

    LeftPrev = m_rcBound.left;

	m_rcBound.left = _ttof( m_sLeft );
	m_sLeft.Format( m_sFormat, m_rcBound.left );

	offset = m_rcBound.left - LeftPrev;
	
	m_dCentreX += offset;
	m_rcBound.right += offset;

	m_sCentreX.Format(m_sFormat, m_dCentreX );
	m_sRight.Format(m_sFormat, m_rcBound.right );

	UpdateData( FALSE );	
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void CVectorObjectInfo::OnEnChangeEditRight()
{
double RightPrev;

    UpdateData( TRUE );

    RightPrev = m_rcBound.right;

	m_rcBound.right = _ttof( m_sRight );
	//m_sRight.Format( m_sFormat, m_rcBound.right );
	
	m_dCentreX = (m_rcBound.left + m_rcBound.right )/2.0;	
	m_sCentreX.Format(m_sFormat, m_dCentreX );
	
	UpdateData( FALSE );	
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void CVectorObjectInfo::OnEnKillfocusEditRight()
{
double RightPrev;

    UpdateData( TRUE );

    RightPrev = m_rcBound.right;

	m_rcBound.right = _ttof( m_sRight );
	m_rcBound.right = max( m_rcBound.right, m_rcBound.left + 1E-10);

	m_sRight.Format( m_sFormat, m_rcBound.right );
	
	m_dCentreX = (m_rcBound.left + m_rcBound.right )/2.0;	
	m_sCentreX.Format(m_sFormat, m_dCentreX );
	
	UpdateData( FALSE );		
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void CVectorObjectInfo::OnEnChangeEditTop()
{
double offset, TopPrev;

    UpdateData( TRUE );

    TopPrev = m_rcBound.top;

	m_rcBound.top = _ttof( m_sTop );
	//m_sTop.Format( m_sFormat, m_rcBound.top );

	offset = m_rcBound.top - TopPrev;
	
	m_dCentreY += offset;
	m_rcBound.bottom += offset;

	m_sCentreY.Format(m_sFormat, m_dCentreY );
	m_sBottom.Format(m_sFormat, m_rcBound.bottom );

	UpdateData( FALSE );	
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void CVectorObjectInfo::OnEnKillfocusEditTop()
{
double offset, TopPrev;

    UpdateData( TRUE );

    TopPrev = m_rcBound.top;

	m_rcBound.top = _ttof( m_sTop );
	m_sTop.Format( m_sFormat, m_rcBound.top );

	offset = m_rcBound.top - TopPrev;
	
	m_dCentreY += offset;
	m_rcBound.bottom += offset;

	m_sCentreY.Format(m_sFormat, m_dCentreY );
	m_sBottom.Format(m_sFormat, m_rcBound.bottom );

	UpdateData( FALSE );	
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void CVectorObjectInfo::OnEnChangeEditBottom()
{
double BottomPrev;

    UpdateData( TRUE );

	BottomPrev = m_rcBound.bottom;

	m_rcBound.bottom = _ttof( m_sBottom );
	//m_sBottom.Format( m_sFormat, m_rcBound.bottom );
	
	m_dCentreY = ( m_rcBound.top + m_rcBound.bottom )/2.0;
	m_sCentreY.Format( m_sFormat, m_dCentreY );
	
	UpdateData( FALSE );
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
void CVectorObjectInfo::OnEnKillfocusEditBottom()
{
double BottomPrev;

    UpdateData( TRUE );

	BottomPrev = m_rcBound.bottom;

	m_rcBound.bottom = _ttof( m_sBottom );
	m_rcBound.bottom = min( m_rcBound.bottom, m_rcBound.top - 1E-10 );
	m_sBottom.Format( m_sFormat, m_rcBound.bottom );
	
	m_dCentreY = ( m_rcBound.top + m_rcBound.bottom )/2.0;
	m_sCentreY.Format( m_sFormat, m_dCentreY );
	
	UpdateData( FALSE );
}
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
