#pragma once


#define DIRECT_DRAW
#define CONTEXT_MENU

#include "dfi_View.h"
class SCALE_DATA;

bool ScaleDataWindowProc(CDFI * pDfi, IC_PARAM * pParam,SCALE_DATA * pData);
BOOL OverdrawFunction( Cdfi_View *pView, Cdfi_MemoryDC *pMemDC, LPVOID pParam); // drawing polygon
BOOL ReplaceLastPointInPolygon(SCALE_DATA *pData, bool recalc=true); 
BOOL AddPointToPolygon(SCALE_DATA *pData, bool recalc=true);
BOOL DeleteLastPointFromPolygon(SCALE_DATA *pData, bool recalc=true);
BOOL TryDraw(SCALE_DATA *pData); // simple draw
bool  CheckAllNearFirstPoint(SCALE_DATA *pData); // test if all points in DELTA around first
int CheckNearPoint(SCALE_DATA *pData,PARE *ppt1, PARE *ppt2);
int  CheckNearPoint3D(SCALE_DATA *pData,IC_POINT3DD *ppt1, IC_POINT3DD *ppt2); // test if point near first and set same cursor
void CalcPolygon(SCALE_DATA *pData); // recalc length and square of polygon 
void DoCloseCurve(SCALE_DATA * pData);

