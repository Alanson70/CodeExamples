#pragma once

#include "dfi.h"
#include "dfi_vector.h"
#include "dfi_vectorObject.h"
#include "Attributes\\dfi_attributes.h"
#include "dfi_historyItem.h"

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
class CVectorSel
{
public:
	CVectorSel(void);
	~CVectorSel(void);

	int   m_NumCursors;
	HCURSOR  hCursor[10];	
	Cdfi_HistoryItem   *pHistoryItem;

};
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

struct VECTOR_STYLE_INFO
{
	double angle;
	COLORREF color;
	double geo;
	int pixel;
	CIC_StyleObject* styleObject;
	BOOL zooming;
};

struct VECTOR_SEL_STRUCT
{
   CDFI      *pDfi;
   LPOBJECT  pObject;
   IC_POINT3DD  ptGeoStart;       // Geo
   IC_POINT3DD  ptGeoCurrent;     // Geo

   int       numLayer;   
   CVectorSel *pClass;
};
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

bool VectorSelect( CDFI* pDfi, IC_PARAM *pParam );
bool UpdateVectorSelect( CDFI* pDfi, CCmdUI * pExtra );
bool VectorSelectProc( CDFI * pDfi, IC_PARAM * pParam );

bool SetActiveObject( Cdfi_Vector *pVectorLayer, __int64 ObjID, BOOL bFlag, BOOL bSendMessage);
void GetVectorStyleInfo(Cdfi_VectorObject* pVectorObject, VECTOR_STYLE_INFO* info);
void SetVectorStyleInfo(Cdfi_VectorObject* pVectorObject, VECTOR_STYLE_INFO* info);

int InitContextMenu(CDFI *pDfi, Cdfi_Document *pDoc );