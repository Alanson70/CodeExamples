#pragma once
#include "afxwin.h"
#include "resource.h"
#include "afxbutton.h"


// CXYZDialog dialog

class CXYZDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CXYZDialog)
public:
	CXYZDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CXYZDialog();
	virtual BOOL OnInitDialog();
	CDFI *m_pDfi;

// Dialog Data
	enum { IDD = IDD_XYZ_EDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditX();
	afx_msg void OnEnChangeEditY();
	afx_msg void OnEnChangeEditZ();
	void OnEnChangeEdit(CEdit *pEdit);
	afx_msg void OnBnClickedVinfoXyzExchangeButton();
	CEdit m_editX;
	CEdit m_editY;
	CEdit m_editZ;
	CStatic m_staticX;
	CStatic m_staticY;
	CStatic m_staticZ;
	//CButton m_exchangeButton;
	CBitmap m_exchangeBitmap;


	IC_POINT3DD m_point;
	int m_mode;
	int m_count;



	CMFCButton m_exchangeButton;
};
