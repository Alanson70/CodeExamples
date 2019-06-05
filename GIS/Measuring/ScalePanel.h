#pragma once

#include "stdafx.h"
#include "Interface/IC_Pane.h"
#include "Interface/IC_ToolBar.h"
#include "Scale.h"


// forward declarations
class CDFI;
struct IC_PARAM;


class CScaleToolBar;
class CScaleToolBar : public CIC_ToolBar // MFCToolBar
{

public:
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	virtual INT_PTR OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
	virtual BOOL AllowShowOnList() const { return FALSE; }

	CScaleToolBar(CDFI *pDfi) : CIC_ToolBar(pDfi, TRUE) {}
	
	int LoadImage(int resID);
};




/////////////////////////////////////////////////////////////////////////////////

// panel shows specified location within current document
class CScalePanel: public CIC_Pane, public CScaleControl
{
	DECLARE_SERIAL(CScalePanel);
protected:	
	CScaleToolBar m_ToolBar;
	CStatic border[8];

	CEdit DistEdit2,StepEdit2,SquareEdit2;

		
	CStatic DistLabel, StepLabel, SquareLabel;
	CStatic TextLabel;
			
public:	
	
	UINT m_toolBar_ID;
	UINT m_uomComboBox_ID;
	UINT m_precComboBox_ID;
	UINT m_doMeasuring_ID;
	UINT m_clear_ID;
	UINT m_transform_ID;
	UINT m_showDistance_ID;
	UINT m_showSquare_ID;
	UINT m_closeCurve_ID;
	UINT m_settings_ID;

	UINT m_doMeasuringImage_ID;
	UINT m_clearImage_ID;
	UINT m_transformImage_ID;
	UINT m_showDistanceImage_ID;
	UINT m_showSquareImage_ID;
	UINT m_closeCurveImage_ID;
	UINT m_discloseCurveImage_ID;
	UINT m_settingsImage_ID;
	
	UINT m_ID;


	CFont m_font;	
	

	CScalePanel();
	CScalePanel(CDFI *pDfi,SCALE_FUNC_DATA *pData);
	~CScalePanel();

	int CreateComponents();
	void DestroyComponents();

	int  LoadImage(int resID);
	bool InitToolBar();

	void ReinitUom();	
	void SetUomOfDoc();

	BOOL GetString(UINT nID, CString& strText);
	void Hide();
	void Show();
	void AdjustLayout();
	bool ButtonsCheckEnable();

	
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnCbnSelChange();
	afx_msg void OnCbnSelChangePrec();
	afx_msg void OnBnClickedClearButton();
	afx_msg void OnBnClickedTransformButton();
	afx_msg void OnBnClickedShowDistanceCheck();
	afx_msg void OnBnClickedShowSquareCheck();
	afx_msg void OnBnClickedCloseCurveCheck();
	afx_msg void OnBnClickedSettsButton();
	afx_msg void OnSetFocus(CWnd *pOldWnd);	
	afx_msg void OnClose();	
	afx_msg LRESULT OnIdleUpdateCmdUI(WPARAM wParam, LPARAM);
	virtual BOOL OnShowPane(BOOL bShow);		
	virtual void OnSizingPane(UINT fwSide, LPRECT pRect);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	void OnCommand( UINT nID, UINT nCode ) {}
	void OnDraw( UINT nID, UINT nCode ) { }

	void OnDocumentChange(); 
	void OnChangeMeasuring();
	void OnStopMeasuring();
	void OnLoadInits();
	void PrintResults();

	void CloseCurve();
	
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	int InitContextMenu( CDFI *pDfi );

	bool DoFunction()  { return DoPanelFunction(); }
	bool EndFunction() { return EndPanelFunction(); }
	bool DoPanelFunction();
	bool EndPanelFunction();

protected:

	DECLARE_MESSAGE_MAP()


};

	
bool MeasuringFunction(CDFI* pDfi, IC_PARAM* pParam);
bool UpdateMeasuring(CDFI * pDfi, CCmdUI * pExtra);
bool MeasuringWndProc(CDFI* pdfi, IC_PARAM* pParam);
bool CheckMeasuring(CDFI *pDfi, CCmdUI *pExtra);