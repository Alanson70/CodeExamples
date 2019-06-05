#pragma once

#include "resource.h"
#include "dfi.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "dfi_vector.h"
#include "dfi_vectortable.h"
#include "dfi_Layer.h"
#include "dfi_vectorobject.h"
#include "VectorInfo.h"
#include "VectorInfoClass.h"
#include "afxmaskededit.h"

#define MIN_DIALOG_WIDTH 450
#define MIN_DIALOG_HEIGHT 300
#define RIGHT_OFFSET 5
#define TOP_POSITION 60

#define TOLERANCE 5 

bool CheckFloat(TCHAR *ss,int width,int prec, bool isSigned = true);

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

class CVectorInfoDialog;

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

///////////////////////////////////////////////////////////////////////////
// CPolygonInfo dialog


class CPolygonInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CPolygonInfo)
	CDFI *m_pDfi;
public:
	CPolygonInfo(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPolygonInfo();

	void Update();

// Dialog Data
	enum { IDD = IDD_VINFO_POLYGON_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_widthStatic;
	CColorButton m_colorStatic;
	CButton m_colorButton;
	CButton m_zoomCheck;
	CStatic m_decreaseStatic;
	CButton m_decreaseButton;
	CButton m_decreaseSelectButton;
	CButton m_dirCheck;
	CButton m_externalCheck;
	int m_width;
	COLORREF m_color;
	BOOL m_zoom;
	double m_decrease;
	BOOL m_dir;
	int m_external;
	CStatic m_sectionGroup;
	int m_section;
	afx_msg void OnBnClickedVinfoDecreaseButton();
	afx_msg void OnBnClickedVinfoPolygonColorSelectButton();
};

/////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
// CVectorInfoDialog dialog

class CVectorInfoDialog : public CDialog, public VECTOR_INFO
{
	DECLARE_DYNAMIC(CVectorInfoDialog)

public:
	

public:
	// redefined
	int  GetNodesCount();
	bool IsNodeUnderMouse(int &numPoint);
	bool IsItSelectedNode(int numPoint);
	void SetNodeSelected(int numPoint, bool selflag=true, int addMode=0);
	void DeleteNodeFromSelected(int n);
	int GetNodesSelectedCount();
	void ClearSelectedNodes();
	int  GetSelectedNodesCount();
	int GetSelectedNodeIndex(int pos);
	void UpdateSelectedNodes();

	//virtual int GetSelectionMode();
	//virtual bool FitObjectToRect();

	/////
	void UpdateSelectedNodesList();
	void SetNodesCount(int count);

	void SetAttrCount(int num);
	void OnUpdateSelectedObjects();
	void OnUpdateActiveObject();
	void UpdateObjectInfo();

//ool FindObjectsUnderMouse(int &nLayer,__int64 &nObj);
//oid SearchObjectsAtLayer( int nLayer);//, CIC_Point3DD pptGeo, CIC_Rect3DD pGeoBoundRect );
	void SetColumnValueAsString(  int nColumn, const CString str );
	//void Update();
	
	void ResizeBars(void);
	virtual BOOL OnInitDialog();

	CVectorInfoDialog(CDFI *pDfi);//CWnd* pParent = NULL);   // standard constructor

	virtual ~CVectorInfoDialog();

// Dialog Data
	enum { IDD = IDD_VECTOR_INFO };

protected:
	virtual void OnCancel();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	
	afx_msg void OnDestroy();

	afx_msg void OnSetFocus(CWnd *obj);	

	afx_msg void OnActivate(UINT id, CWnd *obj,BOOL flag);

	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);

	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	
	afx_msg void OnTcnSelchangeTab2(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnLbnDblclkNodesList();

	afx_msg void OnLvnGetdispinfoList(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnLbnDblclkList1();

	afx_msg void OnLvnItemchangedNodesList(NMHDR *pNMHDR, LRESULT *pResult); 
	
	afx_msg void OnTreeDown(UINT nFlags, CPoint point);


	  
public:
	int m_SplitterPos;

	CTabCtrl m_tab1;
	
	CTreeCtrl m_objTree;

	CListCtrl m_attrList;

	CListCtrl m_nodesList;

	CPolygonInfo m_polygonDlg;

	CDialog *m_objDlg;
	
	CStatic m_objTitle;
	CStatic m_objPanel;
	CButton m_objRadio1;
	CButton m_objRadio2;
	//int m_objRadio;

	bool m_objTreeLock;
		
	std::vector<int> m_nodesSelectedPositions;// myVector1

	HCURSOR m_hSplitterCursor;
	
	afx_msg void OnLvnGetdispinfoAttrList(NMHDR *pNMHDR, LRESULT *pResult);	
	afx_msg void OnNMDblclkNodesList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickNodesList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReturnNodesList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangedObjTree(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnNMClickObjTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedVinfoRadio1();
	afx_msg void OnBnClickedVinfoRadio2();


	afx_msg void OnLvnKeydownNodesList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEditTest();
	afx_msg void OnNMDblclkAttrList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReturnAttrList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedVinfoObjFitCheck();
	CButton m_objectFitCheck;
};


#pragma once


// CAttrEditDialog dialog

class CAttrEditDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CAttrEditDialog)

public:
	CAttrEditDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAttrEditDialog();
	
	BOOL OnInitDialog();
	void SetSizes();

// Dialog Data
	enum { IDD = IDD_VINFO_ATTR_EDIT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	int m_type;
	int m_width;
	int m_prec;
	int m_size;

	CString m_fieldName;
	CString m_fieldValue;
	CEdit m_valueEdit;

	bool EditFloat(TCHAR *ss,int width=24,int prec=6);
	bool EditInt(TCHAR *ss,int digits,bool sign=true);

	CMFCMaskedEdit m_valueMaskEdit;
	afx_msg void OnEnChangeVinfoAttrMask();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEnChangeVinfoAttrValueEdit();	
	afx_msg void OnBnClickedOk();
};
#pragma once


