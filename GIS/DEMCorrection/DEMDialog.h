#pragma once

#include "Resource.h"
#include "StdAfx.h"
#include "dfi.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "dfi_vector.h"
#include "dfi_Layer.h"
#include "dfi_vectortable.h"
#include "dfi_vectorobject.h"

#include "demcorrection.h"

#include "DEM.h"

// CDEMDialog dialog

class CDEMDialog : public CDialog, public CDEM
{
	DECLARE_DYNAMIC(CDEMDialog)

public:
	CDEMDialog(CDFI *pDfi);   // standard constructor
	virtual ~CDEMDialog();

// Dialog Data
	enum { IDD = IDD_DEM_DIALOG };
	bool m_bExitFlag;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	IC_PARAM m_pendingMessage; // message if document under outer lock, issues after unlocking
public:
	

	bool WndProc(UINT pMessage,IC_PARAM * pParam);
	//bool MessageProc(UINT pMessage, Cdfi_Document* pDocument);
	void SetView(Cdfi_View *pView); // function to reset overdraw

	int GetVectorLayerNum();
	int GetRasterLayerNum();
	//void Ready(bool setFlag, bool getFlag);

	void OnChangeLayers();
	void OnSelectLayers();
	virtual void OnAnyChange();
	
	void SetUomCombo();

	//CStatic m_objectsSourceGroup;
	CStatic m_levelsSourceGroup;
	CStatic m_referenceGroup;
	CStatic m_zoneGroup;
	CButton m_objectsSourceRadio;
	CButton m_levelsSourceRadio;
	CComboBox m_levelAttrCombo;
	CEdit m_levelEdit;
	CButton m_refRadio;
	CButton m_zoneCheck;
	//CButton m_zoneRoundingCheck;
	CStatic m_zoneWidthStatic;
	CEdit m_zoneWidthEdit;
	CButton m_rasterizeButton;
	CButton m_readLevelsButton;
	//CButton m_zoneGradientRadio; // del
	CButton m_zoneLinearCheck;
	CButton m_reliefCheck;
	CButton m_rasterCurrentRadio;
	CButton m_rasterCutCheck;
	CComboBox m_uomCombo;
	CButton m_zoneWidthSourceRadio;
	CComboBox m_zoneWidthAttrCombo;
	CComboBox m_vectorCombo;
	CButton m_clearButton;
	CComboBox m_rasterCombo;
	CButton m_rasterCopyCheck;
	CButton m_zoneFactorCheck;
	CButton m_optionZoneOnlyCheck;
	
	CButton m_drawSceletCheck;

	afx_msg void OnBnClickedDemRasterizeButton();
	afx_msg void OnBnClickedDemReadLevelButton();
	afx_msg void OnEnChangeDemLevelEdit();
	afx_msg void OnEnChangeDemZoneWidthEdit();
	afx_msg void OnBnClickedDemZoneCheck();
	//afx_msg void OnBnClickedDemZoneSmouthCheck();
	//afx_msg void OnBnClickedDemZoneRoundCheck();
	afx_msg void OnBnClickedDemObjAllRadio();
	afx_msg void OnBnClickedDemObjMarkedRadio();
	afx_msg void OnBnClickedDemObjSelectedRadio();
	afx_msg void OnBnClickedDemLevelZRadio();
	afx_msg void OnBnClickedDemLevelAttrRadio();
	afx_msg void OnBnClickedDemLevelEditRadio();
	afx_msg void OnCbnSelchangeDemLevelCombo();
	afx_msg void OnBnClickedDemRefAbsRadio();
	afx_msg void OnBnClickedDemRefRelRadio();
	//afx_msg void OnBnClickedDemZoneSmouthNoneRadio();
	//afx_msg void OnBnClickedDemZoneSmouthLineRadio();
	afx_msg void OnBnClickedDemReliefCheck();
	afx_msg void OnBnClickedClearButton();
	afx_msg void OnBnClickedCancel();
	//afx_msg void OnBnClickedDemRastrCurrent();
	//afx_msg void OnBnClickedDemRastrNew();
	afx_msg void OnBnClickedDemRastrCutCheck();
	afx_msg void OnCbnSelchangeDemUomCombo();
	afx_msg void OnBnClickedDemZoneWidthAttrRadio();
	afx_msg void OnBnClickedDemZoneWidthEditRadio();
	afx_msg void OnCbnSelchangeDemZoneWidthAttrCombo();

	afx_msg void OnCbnSelchangeDemVectorCombo();
	afx_msg void OnCbnSelchangeDemRastrCombo();
	afx_msg void OnBnClickedDemRastrCopyCheck();
	afx_msg void OnBnClickedDemZoneFactorCheck();
	
	afx_msg void OnBnClickedDemOptionZoneonlyCheck();
	afx_msg void OnBnClickedDemZoneLinearCheck();
	afx_msg void OnBnClickedSceletCheck();

	afx_msg void OnBnClickedDemZonePointsStatic();
	//afx_msg void OnBnClickedDemUndoButton();

	Cdfi_LayerObject *m_curRasterLayer;
	Cdfi_LayerObject *m_curVectorLayer;
};

bool Rasterize(CDFI* pDFInterface, IC_PARAM *pParam);