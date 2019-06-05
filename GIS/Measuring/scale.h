#pragma once

#define CONTEXT_MENU
//#define PANEL_IS_OPTIONAL
#define INCPOT

#include "dfi_View.h"


class Cdfi_Selection;
class CScaleControl;

#define SCALE_DATA CScaleControl

struct SCALE_FUNC_DATA
{

public:
	CScaleControl *pControl;
	
	int tempLayer;

	int iHistoryItem;
};

struct SCALE_DATA_STRUCT
{
public:
	int m_precisionTypeD;
	int m_precisionTypeS;
	bool m_showDistance;
	bool m_showSquare;
	TCHAR m_Distance[50];
	TCHAR m_Square[50];

	bool m_closeCurve;

	double m_Distance1;
	double m_LastStep1;
	double m_Square1;

	double m_Distance2;
	double m_LastStep2;
	double m_Square2;
		
	int m_unitCode2;

	int m_lineWidth;
	int m_lineColorNum;
	int m_lineStyle;
	bool m_textBacklight;
	COLORREF m_lineColor;
	int m_linearAlways;

};

class CScaleControl : public SCALE_DATA_STRUCT
{
protected :
public :

#ifdef PANEL_IS_OPTIONAL 	
	bool m_isVisible;
#endif

	CIC_PolygonD *m_pPolygon;
	//CIC_RegionCmx *m_pRegion;
	IC_POINT3DD  ptCurrent;	

	
	CDFI * m_pDfi;
	Cdfi_Document * m_pDocument;
	Cdfi_View * m_pView;
	int m_pLayer;

	CRect rcLast;
	SCALE_FUNC_DATA *m_pData;

	CScaleControl();
	CScaleControl(SCALE_FUNC_DATA *pData);
	~CScaleControl();
		
	virtual void ScaleDataDelete(bool bRedraw=false);

	virtual void ClearPolygon();
	virtual void TransformToVector();	
	virtual bool DoFunction()=0;
	virtual bool EndFunction()=0;
	virtual void Show()=0;
	virtual void Hide()=0;
	
	virtual void CloseCurve()=0;
	//virtual void ShowDistance()=0;
	//virtual void ShowSquare()=0;

public:
		
	virtual void OnDocumentChange()=0;
	virtual void OnChangeMeasuring()=0;
	virtual void OnStopMeasuring()=0;
	virtual void OnLoadInits()=0;
	virtual void PrintResults()=0;

	virtual void OnCommand( UINT nID, UINT nCode )=0;
	virtual void OnDraw( UINT nID, UINT nCode )=0;
	
	
};

CString GetResourceString(UINT resID);

bool ScaleFunction(CDFI* pDFInterface, IC_PARAM *pParam);
bool UpdateScaleFunction(CDFI * pDFInterface, CCmdUI * pExtra);
bool DoFunction(CDFI *m_pDfi);
bool EndFunction(CDFI *m_pDfi);
SCALE_FUNC_DATA *GetScaleBaseData( CDFI *pDfi );
SCALE_DATA *GetScaleData( CDFI *pDfi );

bool WindowProc(CDFI * pDFInterface, IC_PARAM * pParam);

bool ScaleWindowProc(CDFI * pDFInterface, IC_PARAM * pParam);// Common WindowProc Function for all variants


void  GetAttributesScale(Cdfi_Attributes *pAttributes,  SCALE_DATA * pData, bool bWrite=false);
int GetFunctionID(CDFI *pDfi);

int StartContextMenu(SCALE_DATA *pData);