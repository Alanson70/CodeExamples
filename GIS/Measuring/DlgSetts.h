#pragma once
#include "Resource.h"
#include "scale.h"
#include "dfi_ColorDialog.h"
#include "dfi_overdraw.h"
#include "afxwin.h"

#define LINE_STYLE_SOLID 0
#define LINE_STYLE_DASH 1
#define LINE_STYLE_DOT 2
#define LINE_STYLE_DASHDOT 3
#define LINE_STYLE_DASHDOTDOT 4
// DlgSetts dialog


// CColorButton

class CColorButton : public CButton
{
	DECLARE_DYNAMIC(CColorButton)

	COLORREF m_Color;

public:
	CColorButton();
	virtual ~CColorButton();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	void SetColor(COLORREF color, BOOL bRedraw = FALSE);
	COLORREF GetColor(void);
};
////////////////////////////////////////////////////////
/*
class CColorLabel : public CStatic
{
	DECLARE_DYNAMIC(CColorLabel)

	COLORREF m_Color;

public:
	CColorLabel();
	virtual ~CColorLabel();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT );
	void SetColor(COLORREF color, BOOL bRedraw = FALSE);
	COLORREF GetColor(void);
};


*/

class CDlgSetts : public CDialog
{
	DECLARE_DYNAMIC(CDlgSetts)

public:
	//CDlgSetts(SCALE_DATA_STRUCT *pData, CWnd* pParent = NULL);   // standard constructor
	CDlgSetts(CWnd* pParent = NULL); 
	virtual ~CDlgSetts();

	void Init();

	
// Dialog Data
	enum { IDD = IDD_DIALOG_SETTS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV supportBOOL 
	BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CColorButton m_ColorButton;
	//CColorLabel m_ColorLabel;
	
	CImage* GetLineBitmap(CSize& size, int style, int width);
	CImage* GetColorBitmap(CSize& size, int colorNum);


	HIMAGELIST m_hColorImageList;
	HIMAGELIST m_hLineStyleImageList;
	HIMAGELIST m_hLineWidthImageList;
	/*
	void LineWidth(int width);
	void LineStyle(int style);
	void LineColorNum(int num);
	void TextBacklight(int bl);

	int LineWidth();
	int LineStyle();
	int LineColorNum();
	int TextBacklight();	
	*/
	CDFI *m_pDfi;

	int m_lineWidth;
	int m_lineColorNum;
	int m_lineStyle;
	bool m_textBacklight;
	COLORREF m_lineColor;
	bool m_showDistance;
	bool m_showSquare;
	int m_precisionTypeD;
	int m_precisionTypeS;

	int m_linearAlways;

	afx_msg void OnCbnSelchangeWidthCombobox();
	afx_msg void OnCbnSelchangeStyleCombobox();
	afx_msg void OnCbnSelchangeColorCombobox();
	afx_msg void OnBnClickedCheckBacklight();
	afx_msg void OnBnClickedColorButton();
	afx_msg void OnBnClickedGetcolorButton();
	afx_msg void OnCbnSelchangePrecisionDistanceCombobox();
	afx_msg void OnCbnSelchangePrecisionSquareCombobox();
	afx_msg void OnBnClickedDistanceShowCheck();
	afx_msg void OnBnClickedSquareShowCheck();	
	afx_msg void OnBnClickedAlwaysLinearCheck();
};
