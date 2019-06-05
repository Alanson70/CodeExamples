// XYZDialog.cpp : implementation file
//

#include "stdafx.h"
#include "fn_vector.h"
#include "XYZDialog.h"
#include "afxdialogex.h"
#include "resource.h"


CString GetResourceString(UINT resID);
// CXYZDialog dialog

IMPLEMENT_DYNAMIC(CXYZDialog, CDialogEx)

CXYZDialog::CXYZDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CXYZDialog::IDD, pParent)
{

}

CXYZDialog::~CXYZDialog()
{
}

void CXYZDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_X, m_editX);
	DDX_Control(pDX, IDC_EDIT_Y, m_editY);
	DDX_Control(pDX, IDC_EDIT_Z, m_editZ);
	DDX_Control(pDX, IDC_X_STATIC, m_staticX);
	DDX_Control(pDX, IDC_Y_STATIC, m_staticY);
	DDX_Control(pDX, IDC_Z_STATIC, m_staticZ);
	DDX_Control(pDX, IDC_VINFO_XYZ_EXCHANGE_BUTTON, m_exchangeButton);
}


BEGIN_MESSAGE_MAP(CXYZDialog, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_X, &CXYZDialog::OnEnChangeEditX)
	ON_EN_CHANGE(IDC_EDIT_Y, &CXYZDialog::OnEnChangeEditY)
	ON_EN_CHANGE(IDC_EDIT_Z, &CXYZDialog::OnEnChangeEditZ)
	ON_BN_CLICKED(IDC_VINFO_XYZ_EXCHANGE_BUTTON, &CXYZDialog::OnBnClickedVinfoXyzExchangeButton)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
BOOL CXYZDialog::OnInitDialog()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CDialog::OnInitDialog();

	m_editX.SetLimitText(14);
	m_editY.SetLimitText(14);
	m_editZ.SetLimitText(14);

	CString sx,sy,sz;

	sx.Format(_T("%lf"),m_point.x);
	sy.Format(_T("%lf"),m_point.y);
	sz.Format(_T("%lf"),m_point.z);
	
	m_editX.SetWindowTextW(sx);
	m_editY.SetWindowTextW(sy);
	m_editZ.SetWindowTextW(sz);

	CString str;
	CString pointsStr;

	if(this->m_count>1)
		pointsStr=GetResourceString(IDS_VINFO_XYZ_POINTS);
	else
		pointsStr=GetResourceString(IDS_VINFO_XYZ_POINT);

	GetDlgItem(IDOK)->SetWindowTextW(GetResourceString(m_mode));

	switch(m_mode)
	{
		case IDS_VINFO_XYZ_ADD		:						
			this->SetWindowTextW(GetResourceString(IDS_VINFO_XYZ_ADDING)+GetResourceString(IDS_VINFO_XYZ_POINT));
			break;
		case IDS_VINFO_XYZ_DEL		:
			this->SetWindowTextW(GetResourceString(IDS_VINFO_XYZ_DELETING)+pointsStr);
			m_editX.SetReadOnly(true);
			m_editY.SetReadOnly(true);
			m_editZ.SetReadOnly(true);
			if(m_count>1)
			{	
				m_editX.SetWindowTextW(_T(""));
				m_editY.SetWindowTextW(_T(""));
				m_editZ.SetWindowTextW(_T(""));
			}
			break;
		case IDS_VINFO_XYZ_MOVE		:
			this->SetWindowTextW(GetResourceString(IDS_VINFO_XYZ_MOVING)+pointsStr);	
			m_editX.SetWindowTextW(_T("0.0"));
			m_editY.SetWindowTextW(_T("0.0"));
			m_editZ.SetWindowTextW(_T("0.0"));
			break;
		case IDS_VINFO_XYZ_EDIT	:
			this->SetWindowTextW(GetResourceString(IDS_VINFO_XYZ_EDITING_SINGLE)+GetResourceString(IDS_VINFO_XYZ_POINT));
			break;
		case IDS_VINFO_XYZ_EDITX	:
			this->SetWindowTextW(GetResourceString(IDS_VINFO_XYZ_EDITING)+pointsStr);
			m_editY.SetReadOnly(true);
			m_editY.SetWindowTextW(_T(""));
			m_editZ.SetReadOnly(true);
			m_editZ.SetWindowTextW(_T(""));
			GetDlgItem(IDOK)->SetWindowTextW(GetResourceString(IDS_VINFO_XYZ_EDIT));
			break;
		case IDS_VINFO_XYZ_EDITY	:
			this->SetWindowTextW(GetResourceString(IDS_VINFO_XYZ_EDITING)+pointsStr);
			m_editX.SetReadOnly(true);
			m_editX.SetWindowTextW(_T(""));
			m_editZ.SetReadOnly(true);
			m_editZ.SetWindowTextW(_T(""));
			GetDlgItem(IDOK)->SetWindowTextW(GetResourceString(IDS_VINFO_XYZ_EDIT));
			break;
		case IDS_VINFO_XYZ_EDITZ	:			
			this->SetWindowTextW(GetResourceString(IDS_VINFO_XYZ_EDITING)+pointsStr);
			m_editX.SetReadOnly(true);
			m_editX.SetWindowTextW(_T(""));
			m_editY.SetReadOnly(true);
			m_editY.SetWindowTextW(_T(""));
			GetDlgItem(IDOK)->SetWindowTextW(GetResourceString(IDS_VINFO_XYZ_EDIT));
			break;
		case IDS_VINFO_XYZ_INTERPOL_STEPPED	:
		case IDS_VINFO_XYZ_INTERPOL_GRADUAL	:
		case IDS_VINFO_XYZ_INTERPOL_LINESMOUTH	:	
			GetDlgItem(IDOK)->SetWindowTextW(GetResourceString(IDS_VINFO_XYZ_INTERPOL));
			this->SetWindowTextW(GetResourceString(IDS_VINFO_XYZ_INTERPOLING)+pointsStr);
			m_staticX.SetWindowTextW(GetResourceString(m_mode));
			m_staticY.SetWindowTextW(GetResourceString(IDS_VINFO_XYZ_INTERPOL_FROM));
			m_staticZ.SetWindowTextW(GetResourceString(IDS_VINFO_XYZ_INTERPOL_TO));
			m_editX.ShowWindow(SW_HIDE);
			m_editY.SetReadOnly(true);
			m_editZ.SetReadOnly(true);
			m_editZ.SetReadOnly(true);	
			sy.Format(_T("%ld"),(int)m_point.y);
			sz.Format(_T("%ld"),(int)m_point.z);
			m_editY.SetWindowTextW(sy);
			m_editZ.SetWindowTextW(sz);		
			m_exchangeButton.ShowWindow(TRUE);			
		break;
		default:
			((CButton *)GetDlgItem(IDOK))->EnableWindow(FALSE);
		break;
		/*
		case IDS_VINFO_XYZ_INTERPOL	:			
			this->SetWindowTextW(GetResourceString(IDS_VINFO_XYZ_INTERPOLING)+pointsStr);
			m_staticX.SetWindowTextW(GetResourceString(IDS_VINFO_XYZ_BETWEEN));
			m_staticY.SetWindowTextW(_T("From"));
			m_staticZ.SetWindowTextW(_T("To"));
			m_editX.ShowWindow(SW_HIDE);
		break;
		*/
	}

	//CONTROL         "X",IDC_X_STATIC,"Static",SS_LEFTNOWORDWRAP | WS_GROUP,18,9,10,8
	//m_exchangeBitmap.LoadBitmap(IDC_VINFO_XYZ_EXCHANGE_BUTTON);
	//HBITMAP hBitmap = (HBITMAP)m_exchangeBitmap.GetSafeHandle();
	//m_exchangeButton.SetBitmap(hBitmap);

	//HBITMAP b = this->m_pDfi->GetMainFrame()->LoadResourceBitmap(AfxGetStaticModuleState()->m_hCurrentResourceHandle, IDC_VINFO_XYZ_EXCHANGE_BUTTON);
	//m_exchangeButton.SetBitmap(b);
	//::DeleteObject( b );

	this->UpdateWindow();

	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////



void CXYZDialog::OnEnChangeEditX()
{
	OnEnChangeEdit(&m_editX);
		
	TCHAR s[25];

	m_editX.GetWindowTextW(s,25);
	
	m_point.x = _wtof(s);
}


void CXYZDialog::OnEnChangeEditY()
{
	OnEnChangeEdit(&m_editY);
		
	TCHAR s[25];

	m_editY.GetWindowTextW(s,25);
	
	m_point.y = _wtof(s);
}

void CXYZDialog::OnEnChangeEditZ()
{
	OnEnChangeEdit(&m_editZ);
		
	TCHAR s[25];

	m_editZ.GetWindowTextW(s,25);
	
	m_point.z = _wtof(s);
}	

void CXYZDialog::OnEnChangeEdit(CEdit *pEdit)
{
	bool isPoint=false; 
	static bool isChange=false;

	if(isChange==true) return;

	TCHAR ss[50];

	CString s;
	pEdit->GetWindowTextW(ss,49);

	s=ss;
	

	for(int i=0;i<s.GetLength();i++)
	{
		if(s[i]=='.')
		{			
			if(isPoint==false && i!=0) { isPoint=true; continue; }
		}
		else
		if(i==0 && s[i]==L'-') continue;
		else
		if(s[i]>=L'0' && s[i]<=L'9') continue;
		s.Delete(i,1);
		isChange=true;
	}

	if(s.GetLength()>14) { s.Truncate(14);isChange=true; }

	if(isChange==true)
	{
		pEdit->SetWindowTextW(s);
		pEdit->SetFocus();
		pEdit->SetSel(s.GetLength(),s.GetLength());		
	
	}
	isChange=false;
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void CXYZDialog::OnBnClickedVinfoXyzExchangeButton()
{
	CString sy,sz;
	
	std::swap(m_point.z,m_point.y);

	sy.Format(_T("%ld"),(int)m_point.y);
	sz.Format(_T("%ld"),(int)m_point.z);

	m_editY.SetWindowTextW(sy);
	m_editZ.SetWindowTextW(sz);

	this->UpdateWindow();
}
/////////////////////////////////////
