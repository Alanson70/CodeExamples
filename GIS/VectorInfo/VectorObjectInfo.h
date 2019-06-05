#pragma once

#include "dfi.h"
#include "dfi_VectorObject.h"
#include "dfi_Document.h"
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
// CVectorObjectInfo dialog

class CVectorObjectInfo : public CDialog
{
	DECLARE_DYNAMIC(CVectorObjectInfo)

public:
	CVectorObjectInfo(CWnd* pParent = NULL);   // standard constructor
	virtual ~CVectorObjectInfo();

// Dialog Data
	enum { IDD = IDD_OBJECT_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void SetParam( CDFI *pDfi, Cdfi_Document *pDoc, int numLayer, Cdfi_VectorObject *pVectorObject );
	void SetInfo(void);
	double GetSquareLin( CDFI *pDfi, Cdfi_Document *pDoc, int numLayer, Cdfi_VectorObject *pVectorObject );

	CDFI *m_pDfi;
	Cdfi_Document *m_pDocument;
	int m_NumLayer;
	bool m_styleChanged;
	Cdfi_VectorObject *m_pVectorObject;
	Cdfi_VectorObject *m_pVectorObjectNew;

	CIC_Rect3DD m_rcBound;
	double  m_dCentreX;
	double  m_dCentreY;
	CString m_sFormat;

	CString m_sLeft;
	CString m_sRight;
	CString m_sTop;
	CString m_sBottom;
	CString m_sCentreX;
	CString m_sCentreY;
	CString m_sType;
	CString m_sSectionCount;
	CString m_sLength;
	CString m_sSquare;

	afx_msg void OnBnClickedButtonStyle();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEditCentreX();
	afx_msg void OnEnKillfocusEditCentreX();
	afx_msg void OnEnChangeEditCentreY();
	afx_msg void OnEnKillfocusEditCentreY();
	afx_msg void OnEnChangeEditLeft();
	afx_msg void OnEnKillfocusEditLeft();
	afx_msg void OnEnChangeEditRight();
	afx_msg void OnEnKillfocusEditRight();
	afx_msg void OnEnChangeEditTop();
	afx_msg void OnEnKillfocusEditTop();
	afx_msg void OnEnChangeEditBottom();
	afx_msg void OnEnKillfocusEditBottom();
	CString m_sSquareLin;
	CString m_sLengthSphere;
};
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////



INT_PTR SelVectorInfo( CDFI *pDfi, Cdfi_View* pView, Cdfi_Document *pDoc, int numLayer, Cdfi_VectorObject *pVOSrc, Cdfi_VectorObject **pVONew, bool *pbStyleChanged );