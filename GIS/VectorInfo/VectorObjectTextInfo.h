#pragma once

#include "dfi.h"
#include "dfi_VectorObject.h"
#include "dfi_Document.h"
#include "resource.h"


//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

// CVectorObjectTextInfo dialog

class CVectorObjectTextInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CVectorObjectTextInfo)

public:
	CVectorObjectTextInfo(CWnd* pParent = NULL);   // standard constructor
	virtual ~CVectorObjectTextInfo();

// Dialog Data
	enum { IDD = IDD_OBJECT_TEXT_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:

	virtual BOOL OnInitDialog();
	void SetParam( CDFI *pDfi, Cdfi_View* pView, Cdfi_Document *pDoc, int numLayer, Cdfi_VectorObject *pVectorObject );
	void SetInfo(void);

	CDFI *m_pDfi;
	Cdfi_View* m_pView;
	Cdfi_Document *m_pDocument;
	int m_NumLayer;
	bool m_styleChanged;
	Cdfi_VectorObject *m_pVectorObject;
	Cdfi_VectorObject *m_pVectorObjectNew;

public:

	CString m_sText;
	CString m_sReText;
	CString m_sFormat;

	CIC_Rect3DD m_rcBound;
	double  m_dCentreX;
	double  m_dCentreY;

	CString m_sCentreX;
	CString m_sCentreY;

	CString m_sType;

	afx_msg void OnBnClickedButtonStyle();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEditCentreX();
	afx_msg void OnEnKillfocusEditCentreX();
	afx_msg void OnEnChangeEditCentreY();
	afx_msg void OnEnKillfocusEditCentreY();
};
