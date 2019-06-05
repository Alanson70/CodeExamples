// DlgSetts.cpp : implementation file
//

#include "stdafx.h"
#include "fnc_scale.h"
#include "DlgSetts.h"
#include "afxdialogex.h"




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


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////





// DlgSetts dialog

IMPLEMENT_DYNAMIC(CDlgSetts, CDialog)

BEGIN_MESSAGE_MAP(CDlgSetts, CDialog)

	ON_CBN_SELCHANGE(IDC_LINE_WIDTH_COMBO, &CDlgSetts::OnCbnSelchangeWidthCombobox)
	ON_CBN_SELCHANGE(IDC_LINE_STYLE_COMBO, &CDlgSetts::OnCbnSelchangeStyleCombobox)
	//ON_CBN_SELCHANGE(IDC_LINE_COLOR_COMBO, &CDlgSetts::OnCbnSelchangeColorCombobox)
	ON_BN_CLICKED(IDC_TEXT_FON_CHECK, &CDlgSetts::OnBnClickedCheckBacklight)
	ON_BN_CLICKED(IDC_LINE_COLOR_BUTTON, &CDlgSetts::OnBnClickedGetcolorButton)
	ON_CBN_SELCHANGE(IDC_DISTANCE_PRECISION_COMBO, &CDlgSetts::OnCbnSelchangePrecisionDistanceCombobox)
	ON_CBN_SELCHANGE(IDC_SQUARE_PRECISION_COMBO, &CDlgSetts::OnCbnSelchangePrecisionSquareCombobox)
	ON_BN_CLICKED(IDC_DISTANCE_SHOW_CHECK, &CDlgSetts::OnBnClickedDistanceShowCheck)
	ON_BN_CLICKED(IDC_SQUARE_SHOW_CHECK, &CDlgSetts::OnBnClickedSquareShowCheck)
	ON_BN_CLICKED(IDC_ALWAYS_LINEAR_CHECK, &CDlgSetts::OnBnClickedAlwaysLinearCheck)
END_MESSAGE_MAP()

	
CDlgSetts::CDlgSetts(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSetts::IDD, pParent)
{	
	m_hColorImageList = NULL;
	
	m_hLineStyleImageList = NULL;
		
	m_hLineWidthImageList = NULL;
}

CDlgSetts::~CDlgSetts()
{
	if (m_hColorImageList)
		::ImageList_Destroy(m_hColorImageList); 
	if (m_hLineStyleImageList)
		::ImageList_Destroy(m_hLineStyleImageList); 
	if (m_hLineWidthImageList)
		::ImageList_Destroy(m_hLineWidthImageList); 
}

void CDlgSetts::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_LINE_COLOR_BUTTON, m_ColorButton);
	//DDX_Control(pDX, IDC_LINES_COMBOBOXEX, m_LineCombo);
	DDX_Control(pDX, IDC_LINE_COLOR_BOX, m_ColorButton);
//	DDX_Control(pDX, IDC_STATIC55, m_ColorLabel);
}

BOOL CDlgSetts::OnInitDialog()
{
	CDialog::OnInitDialog();

	Init();

	return true;
}

//////////////////////////////
void CDlgSetts::Init()
{
	// Labels
	this->SetWindowTextW(GetResourceString(IDC_DIALOG_SETTS));
	GetDlgItem(IDC_LINE_BOX)->SetWindowTextW(GetResourceString(IDC_LINE_BOX));
	GetDlgItem(IDC_LINE_WIDTH)->SetWindowTextW(GetResourceString(IDC_LINE_WIDTH));
	GetDlgItem(IDC_LINE_STYLE)->SetWindowTextW(GetResourceString(IDC_LINE_STYLE));
	GetDlgItem(IDC_LINE_COLOR)->SetWindowTextW(GetResourceString(IDC_LINE_COLOR));
	GetDlgItem(IDC_TEXT_FON)->SetWindowTextW(GetResourceString(IDC_TEXT_FON));
	GetDlgItem(IDC_DISTANCE_BOX)->SetWindowTextW(GetResourceString(IDC_DISTANCE_BOX));
	GetDlgItem(IDC_DISTANCE_SHOW)->SetWindowTextW(GetResourceString(IDC_SHOW));
	GetDlgItem(IDC_DISTANCE_PRECISION)->SetWindowTextW(GetResourceString(IDC_PRECISION));
	GetDlgItem(IDC_SQUARE_BOX)->SetWindowTextW(GetResourceString(IDC_SQUARE_BOX));
	GetDlgItem(IDC_SQUARE_SHOW)->SetWindowTextW(GetResourceString(IDC_SHOW));
	GetDlgItem(IDC_SQUARE_PRECISION)->SetWindowTextW(GetResourceString(IDC_PRECISION));
	
	//////////////////

	CImage* pImage;
	int i, N;
	CString S;
	CSize size(68,16);
	AFX_MODULE_STATE* m_pModuleState = AfxGetModuleState();
	COMBOBOXEXITEM cbItem;


	/////.////////////////////////
	// width combo - not uses
	/*
	CComboBox *wc=(CComboBox *)GetDlgItem(IDC_WIDTH_COMBOBOX_SIMPLE);

	N=wc->GetCount();
	if(N)
	 wc->ResetContent();

	for ( i = 0; i < 8; i++ )
	{
		S.Format(_T("%i точек"), i + 1 );	
		wc->AddString(S);
		//wc->InsertString(-1,S);
	}
	wc->SetCurSel(m_lineWidth);
*/	
	//////////////////////////////////////////////
	// width combo
	//create line type image list
	
	m_hLineWidthImageList = ::ImageList_Create( size.cx, size.cy, ILC_COLORDDB, 0, 1 );
	
	//add line type images to image list
	for(int i=0;i<8;i++)
	{
		pImage = GetLineBitmap( size, PS_SOLID, i );
		if ( pImage )
		{
			::ImageList_Add( m_hLineWidthImageList, (HBITMAP)*pImage, NULL );
			delete pImage;
		}
	}	
	
	CComboBoxEx *wcb=(CComboBoxEx *)GetDlgItem(IDC_LINE_WIDTH_COMBO);
	wcb->SendMessage( CBEM_SETIMAGELIST, 0, (LPARAM)(HIMAGELIST)m_hLineWidthImageList );
	
	//fill line width combo
	memset( &cbItem, 0, sizeof(COMBOBOXEXITEM) );
	cbItem.mask = CBEIF_TEXT|CBEIF_IMAGE|CBEIF_SELECTEDIMAGE;
	
	N = ::ImageList_GetImageCount(m_hLineWidthImageList);
	for ( i = 0; i < N; i++ )
	{
		S.Format(_T("%i"), i + 1);
		
		cbItem.iItem = i;
		cbItem.iImage = i;
		cbItem.iSelectedImage = i;
		cbItem.pszText = (LPTSTR)(LPCTSTR)S;
		wcb->InsertItem(&cbItem);
	}


	wcb->SetCurSel(m_lineWidth);
	

	// style combo
	//create line type image list
		
	int lineStyles[5]={ PS_SOLID,PS_DASH,PS_DOT,PS_DASHDOT, PS_DASHDOTDOT};
	
	m_hLineStyleImageList = ::ImageList_Create( size.cx, size.cy, ILC_COLORDDB, 0, 1 );
	
	//add line type images to image list
	for(int i=0;i<5;i++)
	{
		pImage = GetLineBitmap( size,lineStyles[i], 1 );
		if ( pImage )
		{
			::ImageList_Add( m_hLineStyleImageList, (HBITMAP)*pImage, NULL );
			delete pImage;
		}
	}
	
	
	CComboBoxEx *lc=(CComboBoxEx *)GetDlgItem(IDC_LINE_STYLE_COMBO);
	lc->SendMessage( CBEM_SETIMAGELIST, 0, (LPARAM)(HIMAGELIST)m_hLineStyleImageList );
	
	//fill line combo
	memset( &cbItem, 0, sizeof(COMBOBOXEXITEM) );
	cbItem.mask = CBEIF_TEXT|CBEIF_IMAGE|CBEIF_SELECTEDIMAGE;
	
	N = ::ImageList_GetImageCount(m_hLineStyleImageList);
	for ( i = 0; i < N; i++ )
	{
		S.Format(_T("%i"), i + 1);
		
		cbItem.iItem = i;
		cbItem.iImage = i;
		cbItem.iSelectedImage = i;
		cbItem.pszText = (LPTSTR)(LPCTSTR)S;
		lc->InsertItem(&cbItem);
	}
	
	lc->SetCurSel(m_lineStyle);
	

	// color box
		//add color images to image list
	// not uses
	/*
	size.cx=80;
	m_hColorImageList = ::ImageList_Create( size.cx, size.cy, ILC_COLORDDB, 0, 1 );

	for(int i=0;i<16;i++)
	{
		pImage = GetColorBitmap( size, i );
		if ( pImage )
		{
			::ImageList_Add( m_hColorImageList, (HBITMAP)*pImage, NULL );
			delete pImage;
		}
	}
	

	CComboBoxEx *cc=(CComboBoxEx *)GetDlgItem(IDC_COLORNUM_COMBOBOX);
	cc->SendMessage( CBEM_SETIMAGELIST, 0, (LPARAM)(HIMAGELIST)m_hColorImageList );
	
	//fill line combo
	memset( &cbItem, 0, sizeof(COMBOBOXEXITEM) );
	cbItem.mask = CBEIF_TEXT|CBEIF_IMAGE|CBEIF_SELECTEDIMAGE;
	
	N = ::ImageList_GetImageCount(m_hColorImageList);
	S=_T("");
	for ( i = 0; i < N; i++ )
	{
		//S.Format(_T("%i"), i + 1);
		
		cbItem.iItem = i;
		cbItem.iImage = i;
		cbItem.iSelectedImage = i;
		cbItem.pszText = (LPTSTR)(LPCTSTR)S;
		cc->InsertItem(&cbItem);	
	}
	cc->SetCurSel(m_lineColorNum);
	*/
	
	
	/////////////

	CButton *cb=(CButton *)GetDlgItem(IDC_TEXT_FON_CHECK);
	cb->SetCheck(m_textBacklight?BST_CHECKED:BST_UNCHECKED);

	//////////////////////////////////////////
	m_ColorButton.SetColor( m_lineColor );
	
	/////////////

	cb=(CButton *)GetDlgItem(IDC_DISTANCE_SHOW_CHECK);
	cb->SetCheck(m_showDistance?BST_CHECKED:BST_UNCHECKED);

	/////////////

	cb=(CButton *)GetDlgItem(IDC_SQUARE_SHOW_CHECK);
	cb->SetCheck(m_showSquare?BST_CHECKED:BST_UNCHECKED);

	//////////////////////////////////////////////////
	CComboBox *pc=(CComboBox *)GetDlgItem(IDC_DISTANCE_PRECISION_COMBO);
	CString str;

	pc->AddString(_T("auto"));

	for(int i=0; i<6; ++i)
	{
		str.Format(_T("%.*lf"), 6-i,pow(10.0,i-6.0));
		pc->AddString(str);
	}
	pc->SetCurSel(m_precisionTypeD);

	//////////////////////////////////////////////////
	pc=(CComboBox *)GetDlgItem(IDC_SQUARE_PRECISION_COMBO);
	

	pc->AddString(_T("auto"));

	for(int i=0; i<6; ++i)
	{
		str.Format(_T("%.*lf"), 6-i,pow(10.0,i-6.0));
		pc->AddString(str);
	}
	pc->SetCurSel(m_precisionTypeS);
	
	///////////////////////
	cb = (CButton *)GetDlgItem(IDC_ALWAYS_LINEAR_CHECK);
	cb->SetCheck(m_linearAlways? BST_CHECKED : BST_UNCHECKED);
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

CImage* CDlgSetts::GetLineBitmap(CSize& size, int PenStyle, int width)
{
	CImage* pImage = NULL;
	COLORREF ColorWhite = RGB( 255, 255, 255 );
	//int PenStyle;
	int iPixelSize = 3;
	int w, h;
	BYTE *pBits, *pBitsFirst;
	HDC hDC;
/*
	switch (style)
	{
		case LINE_STYLE_SOLID:
			PenStyle = PS_SOLID;
			break;
		case LINE_STYLE_DASH:
			PenStyle = PS_DASH;
			break;
		case LINE_STYLE_DOT:
			PenStyle = PS_DOT;
			break;
		case LINE_STYLE_DASHDOT:
			PenStyle = PS_DASHDOT;
			break;
		case LINE_STYLE_DASHDOTDOT:
			PenStyle = PS_DASHDOTDOT;
			break;
		default:
			PenStyle = PS_SOLID;
	}
	*/
	CPen Pen(PenStyle, width, RGB(0, 0, 0));

	pImage = new CImage();
	pImage->Create( size.cx, size.cy, iPixelSize*8 );
	
	/// Set White background
	pBitsFirst = (BYTE*)pImage->GetPixelAddress(0,0);
	for(w=0; w<size.cx; w++)
	   memcpy( &pBitsFirst[ w*iPixelSize ], &ColorWhite, iPixelSize*sizeof(BYTE) );
	for( h=1; h<size.cy; h++)
	{		 
	   pBits = (BYTE*)pImage->GetPixelAddress(0,h);
	   memcpy( pBits, pBitsFirst, size.cx*iPixelSize*sizeof(BYTE) );
	}

	hDC = pImage->GetDC();
	::SetROP2( hDC, R2_COPYPEN );
	::SelectObject( hDC, Pen );

	::MoveToEx( hDC, size.cx / 10, size.cy / 2 - width / 2, NULL );
	::LineTo( hDC, size.cx * 9 / 10, size.cy / 2 - width / 2 ); 

	pImage->ReleaseDC();

	return pImage;
}
////////////////////////////////////////////////////////////



CImage* CDlgSetts::GetColorBitmap(CSize& size, int colorNum)
{
	CImage* pImage = NULL;

	int br=(colorNum&0x8)?255:128;
	int r=(colorNum&0x1)*br;
	int g=((colorNum>>1)&0x1)*br;
	int b=((colorNum>>2)&0x1)*br;

	COLORREF ColorFill = RGB( b, g, r );
	int PenStyle= PS_SOLID;;
	int iPixelSize = 3;
	int w, h;
	BYTE *pBits, *pBitsFirst;
	HDC hDC;
	

	CPen Pen(PenStyle, 1, RGB(0, 0, 0));

	pImage = new CImage();
	pImage->Create( size.cx, size.cy, iPixelSize*8 );
	
	/// Set White background
	pBitsFirst = (BYTE*)pImage->GetPixelAddress(0,0);
	for(w=0; w<size.cx; w++)
	   memcpy( &pBitsFirst[ w*iPixelSize ], &ColorFill, iPixelSize*sizeof(BYTE) );
	for( h=1; h<size.cy; h++)
	{		 
	   pBits = (BYTE*)pImage->GetPixelAddress(0,h);
	   memcpy( pBits, pBitsFirst, size.cx*iPixelSize*sizeof(BYTE) );
	}

	hDC = pImage->GetDC();
	::SetROP2( hDC, R2_COPYPEN );
	::SelectObject( hDC, Pen );
	
	//::MoveToEx( hDC, size.cx / 10, size.cy / 2 - 1 / 2, NULL );
	//::LineTo( hDC, size.cx * 9 / 10, size.cy / 2 - 1 / 2 ); 

	pImage->ReleaseDC();

	return pImage;
}


void CDlgSetts::OnCbnSelchangeWidthCombobox()
{
	// TODO: Add your control notification handler code here
	CComboBoxEx *lc=(CComboBoxEx *)GetDlgItem(IDC_LINE_WIDTH_COMBO);
	m_lineWidth=lc->GetCurSel();	

	if(m_lineWidth>0)
	{
		((CComboBoxEx *)GetDlgItem(IDC_LINE_STYLE_COMBO))->SetCurSel(0);
		m_lineStyle=0;
	}

}


void CDlgSetts::OnCbnSelchangeStyleCombobox()
{
	// TODO: Add your control notification handler code here
	CComboBoxEx *cb=(CComboBoxEx *)GetDlgItem(IDC_LINE_STYLE_COMBO);
	m_lineStyle=cb->GetCurSel();
	if(m_lineStyle>0)
	{
		((CComboBoxEx *)GetDlgItem(IDC_LINE_WIDTH_COMBO))->SetCurSel(0);
		m_lineWidth=0;
	}

}


void CDlgSetts::OnCbnSelchangeColorCombobox()
{
	// TODO: Add your control notification handler code here
	//CComboBoxEx *cb=(CComboBoxEx *)GetDlgItem(IDC_LINE_COLOR_BUTTON);
	//m_lineColorNum=cb->GetCurSel();
}

void CDlgSetts::OnCbnSelchangePrecisionDistanceCombobox()
{
	// TODO: Add your control notification handler code here
	CComboBoxEx *cb=(CComboBoxEx *)GetDlgItem(IDC_DISTANCE_PRECISION_COMBO);
	m_precisionTypeD=cb->GetCurSel();
}

void CDlgSetts::OnCbnSelchangePrecisionSquareCombobox()
{
	// TODO: Add your control notification handler code here
	CComboBoxEx *cb=(CComboBoxEx *)GetDlgItem(IDC_SQUARE_PRECISION_COMBO);
	m_precisionTypeS=cb->GetCurSel();
}

void CDlgSetts::OnBnClickedCheckBacklight()
{
	// TODO: Add your control notification handler code here
	CButton *cb=(CButton *)GetDlgItem(IDC_TEXT_FON_CHECK);
	m_textBacklight=(cb->GetCheck()==BST_CHECKED)?true:false;
}


void CDlgSetts::OnBnClickedColorButton()
{
	// TODO: Add your control notification handler code here
	Cdfi_ColorDialog dlg( m_pDfi->GetMainFrame() );

	COLORREF color;

	dlg.SetRGBColor( m_ColorButton.GetColor() );
    
	if (dlg.DoModal() == IDOK)
	{
		color = dlg.GetRGBColor();
		m_ColorButton.SetColor( color );
		//m_ColorLabel.SetColor( color );
		m_lineColor=color;
	}
}


void CDlgSetts::OnBnClickedGetcolorButton()
{
	// TODO: Add your control notification handler code hereCdfi_ColorDialog dlg( m_pDfi->GetMainFrame() );
	Cdfi_ColorDialog dlg( m_pDfi->GetMainFrame() );
	COLORREF color;

	dlg.SetRGBColor( m_ColorButton.GetColor() );
    
	if (dlg.DoModal() == IDOK)
	{
		color = dlg.GetRGBColor();
		m_ColorButton.SetColor( color , TRUE);
		Invalidate();
		m_lineColor=color;
	}
}


void CDlgSetts::OnBnClickedDistanceShowCheck()
{
	// TODO: Add your control notification handler code here
	CButton *cb=(CButton *)GetDlgItem(IDC_DISTANCE_SHOW_CHECK);
	m_showDistance=(cb->GetCheck()==BST_CHECKED)?true:false;
}


void CDlgSetts::OnBnClickedSquareShowCheck()
{
	// TODO: Add your control notification handler code here
	CButton *cb=(CButton *)GetDlgItem(IDC_SQUARE_SHOW_CHECK);
	m_showSquare=(cb->GetCheck()==BST_CHECKED)?true:false;
}


void CDlgSetts::OnBnClickedAlwaysLinearCheck()
{
	CButton *cb = (CButton *)GetDlgItem(IDC_ALWAYS_LINEAR_CHECK);
	m_linearAlways = (cb->GetCheck() == BST_CHECKED) ? true : false;
}
