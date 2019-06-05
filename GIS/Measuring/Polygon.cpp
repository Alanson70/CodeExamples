//////////////////////////////////////////////////////////////////////////////////////
//shaposhnikov a.a.
// Module for choosing points in window and drawing polygon between them
//////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "windowsx.h"
#include "dfi_OverDraw.h"
#include "dfi_View.h"
#include "dfi_Layer.h"
#include "scale.h"
#include "polygon.h"
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////




bool ScaleDataWindowProc(CDFI * pDfi, IC_PARAM * pParam,SCALE_DATA * pData)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	pData->m_pDfi = pDfi;

	if ((pDfi->GetApp()->GetObjectType(pParam->pObject))!= OBJECT_VIEW)
		return false;
		
	if (pParam->message == WM_SETCURSOR)
		::SetCursor(AfxGetApp()->LoadCursor(IDC_TARGET));

	if ((pParam->message != WM_LBUTTONDOWN) && (pParam->message != WM_KEYDOWN))
		return false; 
	

	// test if pDoc changed,  assign it to proc structure and call Dialog change 
	
	Cdfi_Document *pActDoc = NULL;
	Cdfi_View * pView;
	
	pView = (Cdfi_View *)pParam->pObject;	

	pActDoc = pDfi->GetMainFrame()->GetActiveDocument();
	
	if(pData->m_pDocument != pActDoc  || pData->m_pView == NULL)
	{		
		pData->m_pView = pView;	

		if(pData->m_pDocument)
		{						
			if( !pData->m_pDocument->LockDocument( MODE_ACCESS_WRITE, NULL, SENDMESSAGE_OFF, TRUE ) )		return false;	

			pData->m_pDocument->UnlockDocument( MODE_ACCESS_WRITE );
		
		}
		pData->m_pDocument = pActDoc;
		
		pData->OnDocumentChange();		
		// delete and register overdraw

		pData->ScaleDataDelete(true);

		pView->GetOverDraw()->Register( OverdrawFunction, pData );
	
	}
	
	if(!pData->m_pPolygon) 
		pData->m_pPolygon = new CIC_PolygonD();
	else
		pData->m_pPolygon->RemoveAll();
		
	//if(!pData->m_pRegion) 
	//	pData->m_pRegion = new CIC_RegionCmx(pData->m_pPolygon);

	
	// process DELETE key
	/*
	if(pData->m_pDocument->IsLockDocument())
		return false;

	if (pParam->message == WM_KEYDOWN)
	{
		if (pParam->wParam==VK_DELETE)
		{
			if( !pView->GetDocument()->LockDocument( MODE_ACCESS_WRITE, NULL, SENDMESSAGE_OFF, TRUE ) )
				return false;

			pView->InvalidateView( FALSE );

			pView->GetDocument()->UnlockDocument( MODE_ACCESS_WRITE );
		}		
		return true;
	}
	*/
	

	/////////////
	CIC_Point64 ptClient;
	CIC_Point3DD  ptGeoPrev, ptGeo;
	BOOL KS = FALSE, bExit, bAbort;
	MSG msg;

	ptClient.x = GET_X_LPARAM( pParam->lParam );
	ptClient.y = GET_Y_LPARAM( pParam->lParam );

	pView->GetCoordView()->ClientPointToGeo(&ptClient, (CIC_Point3DD *)&ptGeo);
	//pData->m_pPolygon->AddPoints( (IC_POINT3DD *)&ptGeo, 1);
	pData->ptCurrent.x = ptGeo.x;
	pData->ptCurrent.y = ptGeo.y;
	pData->ptCurrent.z = ptGeo.z;
	AddPointToPolygon(pData);
	ptGeoPrev = ptGeo;

	/////////////////////////////////////////////////////////
	//// Init Selection layer
	
	
	if( !pView->GetDocument()->LockDocument( MODE_ACCESS_WRITE, NULL, SENDMESSAGE_OFF, TRUE ) )
		return false;
	
	AfxLockTempMaps();

	::SetCapture(pView->GetHWND());

	if (::GetCapture() != pView->GetHWND())
	{
		pView->GetDocument()->UnlockDocument( MODE_ACCESS_WRITE );
		return false;
	}

	bAbort = FALSE;

	bool mouseInWindow=true;

	for(bExit = FALSE;!bExit;)
	{
		BOOL bMouseDown;

		::GetMessage(&msg, NULL, 0, 0); 

		
		switch(msg.message)
		{
			case WM_MOUSEMOVE	:
			case WM_LBUTTONDOWN :
			case WM_RBUTTONDOWN :
			case WM_LBUTTONUP :
			case WM_RBUTTONUP :
			case WM_LBUTTONDBLCLK :
		
			ptClient.x = GET_X_LPARAM(msg.lParam);
			ptClient.y = GET_Y_LPARAM(msg.lParam);
		
			// test mouse on window
			RECT rect;
			GetWindowRect(pView->GetHWND(),&rect);
				
			if(ptClient.x<0 || ptClient.y<0 || (ptClient.x>(rect.right-rect.left)) || (ptClient.y>(rect.bottom-rect.top)))
			{
				if(mouseInWindow==true)									
				{					
					mouseInWindow=false;
					::SetCursor( AfxGetApp()->LoadStandardCursor(IDC_NO) );  // IDC_WAIT					
				}
				continue;
			}	
			else
				mouseInWindow=true;			
		
		}

		switch( msg.message )
		{
			case WM_SETCURSOR:  
				
				::SetCursor(AfxGetApp()->LoadCursor(IDC_TARGET));  
			
			break;

			case WM_KEYDOWN :
				if(msg.wParam == VK_DELETE || msg.wParam == VK_BACK)
				{
					DeleteLastPointFromPolygon(pData);
				} // exit anywhere
				else
				if (msg.wParam == VK_ESCAPE)
					
				{  
					bExit = TRUE;  
					bAbort = TRUE; 
					break;
				}
		//	break;

			case WM_MOUSEMOVE:
			{						
				TryDraw(pData); // clear old line							

		  		pView->GetCoordView()->ClientPointToGeo(&ptClient , (CIC_Point3DD *)&ptGeo);

				pData->ptCurrent.x = ptGeo.x;
				pData->ptCurrent.y = ptGeo.y;
				pData->ptCurrent.z = ptGeo.z;								

				ReplaceLastPointInPolygon(pData);

				TryDraw(pData); // draw new line

				CheckNearPoint3D(pData,&pData->ptCurrent, &pData->m_pPolygon->GetData()[0]);
				
				if (msg.wParam & MK_LBUTTON)
				{
					//if (ptGeo != ptGeoPrev )
					if (!ptGeo.IsEqualXY( ptGeoPrev ) )
					{
						AddPointToPolygon(pData);
						ptGeoPrev = ptGeo;
					}
					bMouseDown = TRUE;
				}
				else
					bMouseDown = FALSE;

				for(;;)
				{
					KS = pView->CheckScrollView();
					if (!KS)
						break;

					if (msg.message == WM_LBUTTONDOWN)
						bMouseDown = TRUE;

					if (msg.message == WM_LBUTTONUP)
						bMouseDown = FALSE;

					POINT Point;
					GetCursorPos(&Point);
					ScreenToClient(pView->GetHWND(), &Point);

					ptClient.x = Point.x;
					ptClient.y = Point.y;
	  				pView->GetCoordView()->ClientPointToGeo(&ptClient , &ptGeo);
					pData->ptCurrent.x = ptGeo.x;
					pData->ptCurrent.y = ptGeo.y;

					if ((bMouseDown) && (ptGeo != ptGeoPrev))
					{
						AddPointToPolygon(pData);
						ptGeoPrev = ptGeo;
					}				

					if (msg.message == WM_KEYDOWN)
						if (msg.wParam == VK_ESCAPE)
						{
							bExit = TRUE;
							bAbort = TRUE;
						}

					::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
				
					if(bExit)
						break;
				}
				
				//CalcPolygon(pData);

			} 
			break;

			case WM_LBUTTONDOWN: // set point and prepare to draw free curve
			{
				
				if (ptGeo != ptGeoPrev)
				{
					CheckNearPoint3D(pData,&pData->ptCurrent, &pData->m_pPolygon->GetData()[0]);
					AddPointToPolygon(pData);
					ptGeoPrev = ptGeo;
					//CalcPolygon(pData);
				}
			} 
			break;


			case WM_LBUTTONUP: // check if last point near first - set first as last and exit
			{
				if (CheckAllNearFirstPoint(pData)) // to exclode first click of mouse or all point near first
					break;

				if (pData->m_pPolygon->GetSize() < 3)			break;				

				if (CheckNearPoint3D(pData,&pData->ptCurrent, &pData->m_pPolygon->GetData()[0])) 
				{
					bExit = TRUE;
					//pData->m_pPolygon->DeleteAt(pData->m_pPolygon->GetSize() - 1);
					pData->ptCurrent=pData->m_pPolygon->GetData()[0];
					ReplaceLastPointInPolygon(pData);

					//ptGeoPrev = ptGeo;

					//CalcPolygon(pData);
				}
			} 
			break;
			case WM_RBUTTONUP:
			case WM_LBUTTONDBLCLK: 
			 // right button or left double - connect to first point and exit
				{
					if(pData->m_closeCurve)
					{
						pData->ptCurrent=pData->m_pPolygon->GetData()[0];
						ReplaceLastPointInPolygon(pData);
					}
					else
					{
						//DeleteLastPointFromPolygon(pData);
					}
					//CalcPolygon(pData);
				}
				bExit = TRUE; 
			break;

			

			default:   
			if (msg.message != WM_KICKIDLE && !AfxPreTranslateMessage(&msg))
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
			break;
		}
		//////// end switch
	} // end for(;;)
	/////////////////////////////////////////////////
	/*
	if (ptGeo != ptGeoPrev) // what for????
	{
		AddPointToContour(pView, pData);
		ptGeoPrev = ptGeo;
	}*/
	
	if( bExit )
	{
		::ReleaseCapture();
		AfxUnlockTempMaps(FALSE);

#ifndef DIRECT_DRAW
	pView->RedrawView( NULL, TRUE, VIEW_UPDATE_OVERDRAW );
#endif
		pView->RedrawView( NULL, TRUE, VIEW_UPDATE_OVERDRAW );
		// add selection poligon
		if (!bAbort )
		{	
			CalcPolygon(pData);
		}
		else
		{
			pView->GetDocument()->RedrawViews(FALSE);
		}
	
	}


	pView->GetDocument()->UnlockDocument( MODE_ACCESS_WRITE );
/*
	if (pData->m_pPolygon)
 		delete pData->m_pPolygon;
	pData->m_pPolygon = NULL;
	*/
	
#ifdef INCPOT
	pData->EndFunction();
#endif	

	return true;
}


////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

int CheckNearPoint(SCALE_DATA *pData,PARE *ppt1, PARE *ppt2)
{
	if(!pData->m_pView)				return FALSE;
	
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CPoint ptCur, ptFirst;

	pData->m_pView->GetCoordView()->GeoPointsToClient((CPare *)ppt1, &ptCur, 1);
	pData->m_pView->GetCoordView()->GeoPointsToClient((CPare *)ppt2, &ptFirst, 1);

	if ((abs(ptCur.x - ptFirst.x) < DELTA) && (abs(ptCur.y - ptFirst.y) < DELTA))
	{   
		::SetCursor(AfxGetApp()->LoadCursor(IDC_TARGET_FIN));
		return TRUE;
	}
	else ::SetCursor(AfxGetApp()->LoadCursor(IDC_TARGET));

	return FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
int  CheckNearPoint3D(SCALE_DATA *pData,IC_POINT3DD *ppt1, IC_POINT3DD *ppt2)
{
	if(!pData->m_pView)				return FALSE;

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CPoint ptCur, ptFirst;

	pData->m_pView->GetCoordView()->GeoPointsToClient((CIC_Point3DD *)ppt1, &ptCur, 1);
	pData->m_pView->GetCoordView()->GeoPointsToClient((CIC_Point3DD *)ppt2, &ptFirst, 1);

	if ((abs(ptCur.x - ptFirst.x) < DELTA) && (abs(ptCur.y - ptFirst.y) < DELTA))
	{   
		::SetCursor(AfxGetApp()->LoadCursor(IDC_TARGET_FIN));
		return TRUE;
	}
	else ::SetCursor(AfxGetApp()->LoadCursor(IDC_TARGET));

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
bool  CheckAllNearFirstPoint(SCALE_DATA *pData)
{
	if(!pData->m_pView)				return FALSE;

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CPoint ptCur, ptFirst;


	for(int i=1;i<(int)pData->m_pPolygon->GetSize();i++)
	{
		CIC_Point3DD *ppt1=(CIC_Point3DD *)&pData->m_pPolygon->GetData()[0];
		CIC_Point3DD *ppt2=(CIC_Point3DD *)&pData->m_pPolygon->GetData()[i];

		pData->m_pView->GetCoordView()->GeoPointsToClient(ppt1, &ptCur, 1);
		pData->m_pView->GetCoordView()->GeoPointsToClient(ppt2, &ptFirst, 1);
		if ((abs(ptCur.x - ptFirst.x) < DELTA) && (abs(ptCur.y - ptFirst.y) >= DELTA))
		{   
			return false;
		}
	}

	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////



BOOL AddPointToPolygon(SCALE_DATA *pData, bool recalc)
{
	Cdfi_View * pView=pData->m_pView;

	ReplaceLastPointInPolygon(pData,false);

    if (pData->m_pPolygon)
	{
		pData->m_pPolygon->AddPoints(&pData->ptCurrent);
	}
	else
		return FALSE;

	if(recalc) CalcPolygon(pData);

#ifdef DIRECT_DRAW
	pView->RedrawView( NULL, TRUE, VIEW_UPDATE_OVERDRAW );
#endif	
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

BOOL ReplaceLastPointInPolygon(SCALE_DATA *pData, bool recalc)
{
	Cdfi_View * pView=pData->m_pView;

    if (pData->m_pPolygon)
	{	
		int last=pData->m_pPolygon->GetSize()-1;
		if(last>0)
			pData->m_pPolygon->DeleteAt(last);

		pData->m_pPolygon->AddPoints(&pData->ptCurrent);
	}
	else
		return FALSE;

	if(recalc) CalcPolygon(pData);

#ifdef DIRECT_DRAW
	pView->RedrawView( NULL, TRUE, VIEW_UPDATE_OVERDRAW );
#endif
	
	return TRUE;
}
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
BOOL DeleteLastPointFromPolygon(SCALE_DATA *pData, bool recalc)
{
	Cdfi_View * pView=pData->m_pView;

    if (pData->m_pPolygon)
	{	
		int last=pData->m_pPolygon->GetSize()-1;
		if(last>0)		
			pData->m_pPolygon->DeleteAt(last);
		
		else return FALSE;
		
	}
	else
		return FALSE;

	if(recalc) CalcPolygon(pData);

#ifdef DIRECT_DRAW
	pView->RedrawView( NULL, TRUE, VIEW_UPDATE_OVERDRAW );
#endif
	
	return TRUE;
}
//////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

void DoCloseCurve(SCALE_DATA * pData)
{
	if(!pData)						return;
	if(!pData->m_pPolygon)			return;
	if(!pData->m_pView)				return;
	if(!pData->m_pDocument)			return;
	
	CIC_PolygonD *pPolygon=pData->m_pPolygon;

	DWORD count = pPolygon->GetSize();

	if(count<3) return;

	if(pPolygon->GetData()[0].x==pPolygon->GetData()[count-1].x && pPolygon->GetData()[0].y==pPolygon->GetData()[count-1].y)
	{
		if(pData->m_closeCurve==false)
			pPolygon->DeleteAt(count-1);
	}
	else
	{
		if(pData->m_closeCurve==true)
			pPolygon->AddPoints(&pPolygon->GetData()[0],1);
	}
	CalcPolygon(pData);
}

double nv = 1000;

//////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
void CalcPolygon(SCALE_DATA * pData)
{	
//	CScaleControl *pControl;

	if(!pData)						return;
	if(!pData->m_pPolygon)			return;
	if(!pData->m_pView)				return;
	if(!pData->m_pDocument)			return;

	//pControl=pData;
		
				
	// measures
	// m - in base units
	// p - in pixels
	// c - in custom units

	double fLm, fLmz, fLp, fLpz; // length and last step
	double fConerC, fDiv;
	double SquareP, SquareM;
	CString sConerC;

	// custom values
	
	double fLc=0, fLcz=0;
	double SquareC=0;
	CIC_Point3DD ptCustom[2];
	CIC_PolygonD *pPolygon=pData->m_pPolygon;
	
	CGeoInfo *pGeoInfoDoc=pData->m_pDocument->GetDocGeoInfo(); 
	int baseUom = pGeoInfoDoc->GetGeoProjection()->GetUnit();
		
	CIC_Point3DD * ptGeo[2], Vector[2];
	CPoint ptClient[2];

	SquareM = SquareP = fLm = fLmz = fLp = fLpz = 0;

	// transform units
	
	double dVScale = 1;
	int newUom = pData->m_unitCode2;

	{
		CIC_Rect3DD rcBoundObj;				
		
		rcBoundObj = pData->m_pDocument->GetDocGeoInfo()->GetBoundRect();
		rcBoundObj.NormalizeGeoRect();
		//rcBoundObj.right = rcBoundObj.left + (rcBoundObj.right - rcBoundObj.left) ;
		//rcBoundObj.top = rcBoundObj.bottom + (rcBoundObj.top - rcBoundObj.bottom) ;
				
		// отдельный случай нулевой протяженности объекта
		// создаем искусственную протяженность для оценивания пропорции
		if (rcBoundObj.left == rcBoundObj.right)
			rcBoundObj.right++;
		if (rcBoundObj.top == rcBoundObj.bottom)
			rcBoundObj.bottom++;
						
				// переводим в радианы
		double long1 = fnc_UOM::AngleToDegree(baseUom, rcBoundObj.left) * M_PI / 180.0;
		double lat1 = fnc_UOM::AngleToDegree(baseUom, rcBoundObj.top) * M_PI / 180.0;
		double long2 = fnc_UOM::AngleToDegree(baseUom, rcBoundObj.right) * M_PI / 180.0;
		double lat2 = fnc_UOM::AngleToDegree(baseUom, rcBoundObj.bottom) * M_PI / 180.0;
		// линейный размер в единицах входного размера радиуса(буфера)
		double dVSizeM = fnc_UOM::SphericalLenAzimutEarth(lat1, long1, lat2, long2, NULL, newUom);
		// линейный размер в единицах слоя
		dVScale = sqrt(pow((rcBoundObj.top - rcBoundObj.bottom), 2.0) + pow((rcBoundObj.left - rcBoundObj.right), 2.0));
		// считеся масштабный коэффициент
		// ( dVScale == dVSizeM ) эта проверка на случай нулевой протяженности объектов чтобы не получать деления на ноль
		dVScale = (dVScale == dVSizeM) ? 1.0 : dVScale / dVSizeM;
	}

	auto transform_unit=[&](double v)
	{
		if (CGeoInfo::IsLinearUnit(newUom) == CGeoInfo::IsLinearUnit(baseUom))
			return CGeoInfo::TransformUnit(baseUom, newUom, v);
		
		// !считется новое значение в единицах слоя (объекта)
		v = v / dVScale;
		
		return v;
	};


	
	DWORD dCount = pPolygon->GetSize();

	if(dCount<2) return;

	for(DWORD i = 0;i < dCount;i++)
	{
		if (i == 0)
		{
			ptGeo[0] = (CIC_Point3DD *)pPolygon->GetData();
			pData->m_pView->GetCoordView()->GeoPointsToClient( ptGeo[0], &ptClient[0] );

			ptCustom[0].x = transform_unit(ptGeo[0]->x);
			ptCustom[0].y = transform_unit(ptGeo[0]->y);

		/*	ptCustom[0].x = pGeoInfoDoc->TransformUnit (pData->m_unitCode2, ptGeo[0]->x);
			ptCustom[0].y = pGeoInfoDoc->TransformUnit (pData->m_unitCode2, ptGeo[0]->y);	*/					
			
			continue;
		}
		
		ptGeo[1] = (CIC_Point3DD *)((i != dCount) ? &pPolygon->GetData()[i] : &pData->ptCurrent);
		pData->m_pView->GetCoordView()->GeoPointsToClient( ptGeo[1], &ptClient[1] );

		ptCustom[1].x = transform_unit(ptGeo[1]->x);
		ptCustom[1].y = transform_unit(ptGeo[1]->y);
		/*ptCustom[1].x = pGeoInfoDoc->TransformUnit (pData->m_unitCode2, ptGeo[1]->x);
		ptCustom[1].y = pGeoInfoDoc->TransformUnit (pData->m_unitCode2, ptGeo[1]->y);
		*/
		fLmz = sqrt((ptGeo[1]->x - ptGeo[0]->x) * (ptGeo[1]->x - ptGeo[0]->x) + (ptGeo[1]->y - ptGeo[0]->y) * (ptGeo[1]->y - ptGeo[0]->y));
		fLpz = sqrt((double)(ptClient[1].x - ptClient[0].x) * (ptClient[1].x - ptClient[0].x) + (ptClient[1].y - ptClient[0].y) * (ptClient[1].y - ptClient[0].y));
		fLcz = sqrt((double)(ptCustom[1].x - ptCustom[0].x) * (ptCustom[1].x - ptCustom[0].x) + (ptCustom[1].y - ptCustom[0].y) * (ptCustom[1].y - ptCustom[0].y));
		
		fLm += fLmz;
		fLp += fLpz;
		fLc += fLcz;
		
		SquareM += (ptGeo[0]->x + ptGeo[1]->x) * (ptGeo[0]->y - ptGeo[1]->y);
		SquareP += (ptClient[0].x + ptClient[1].x) * (ptClient[0].y - ptClient[1].y);
		SquareC += (ptCustom[0].x + ptCustom[1].x) * (ptCustom[0].y - ptCustom[1].y);

		ptGeo[0] = ptGeo[1];
		ptClient[0] = ptClient[1];		
		ptCustom[0] = ptCustom[1];
		
	}

	ptGeo[1] = (CIC_Point3DD *)pPolygon->GetData();
	pData->m_pView->GetCoordView()->GeoPointsToClient(ptGeo[1], &ptClient[1]);

	ptCustom[1].x = transform_unit(ptGeo[1]->x);
	ptCustom[1].y = transform_unit(ptGeo[1]->y);
	/*ptCustom[1].x = pGeoInfoDoc->TransformUnit (pData->m_unitCode2, ptGeo[1]->x);
	ptCustom[1].y = pGeoInfoDoc->TransformUnit (pData->m_unitCode2, ptGeo[1]->y);
*/
	SquareM += (ptGeo[0]->x + ptGeo[1]->x) * (ptGeo[0]->y - ptGeo[1]->y);
	SquareP += (ptClient[0].x + ptClient[1].x) * (ptClient[0].y - ptClient[1].y);
	SquareC += (ptCustom[0].x + ptCustom[1].x) * (ptCustom[0].y - ptCustom[1].y);

	SquareM = fabs(SquareM) / 2;
	SquareP = fabs(SquareP) / 2;
	SquareC = fabs(SquareC) / 2;
	
	if (dCount >= 2)
	{
		Vector[0].x = pPolygon->GetData()[dCount-2].x - pPolygon->GetData()[dCount-1].x;
		Vector[0].y = pPolygon->GetData()[dCount-2].y - pPolygon->GetData()[dCount-1].y;

		Vector[1].x = pData->ptCurrent.x - pPolygon->GetData()[dCount-1].x;
		Vector[1].y = pData->ptCurrent.y - pPolygon->GetData()[dCount-1].y;

		fDiv = sqrt(Vector[0].x * Vector[0].x + Vector[0].y * Vector[0].y) * sqrt(Vector[1].x * Vector[1].x + Vector[1].y * Vector[1].y);
		fConerC = acos((Vector[1].x * Vector[0].x + Vector[1].y * Vector[0].y) / fDiv);
		fConerC *= 180 / M_PI;

		if (fDiv == 0)
			sConerC = _T("-");
		else
			sConerC.Format(_T("%f"), fConerC);
		//this->GetDlgItem(IDC_SCALE_CONER_C)->SetWindowText(sConerC);
	}

	// fill struct to print then by form
	pData->m_Distance1=fLm;
	pData->m_LastStep1=fLmz;
	pData->m_Square1=SquareM;

	pData->m_Distance2=fLc;
	pData->m_LastStep2=fLcz;
	pData->m_Square2=SquareC;
	
	// print results

	pData->PrintResults(); 

	// prepare square value for output by overdraw
	
	
	CString str = _T("");	
	//CString strS = _T("");
	TCHAR uomName[100];
	CString fStr;
	

	pGeoInfoDoc->GetShortUnitName( pData->m_unitCode2, uomName );
	if(!pData->m_precisionTypeD)
	{
		if((SquareC>999999999999) || (SquareC<0.000001) && (SquareC != 0)) // choose vid by square
			str.Format(_T("%12.3g"),fLc);
		else
			str.Format(_T("%12lf"),fLc);
	}
	else
	{
		fStr.Format(_T("%%12.%dlf"),7-pData->m_precisionTypeD);
		str.Format(fStr,fLc);
	}
	wsprintf(pData->m_Distance,_T(" %13.13s %.11s    "),str,uomName);



	CString strQ;
	strQ.LoadString( AfxGetStaticModuleState()->m_hCurrentResourceHandle,IDS_QUADRATNO);
	
	if(!pData->m_precisionTypeS)
	{
		if((SquareC>999999999999) || (SquareC<0.000001) && (SquareC != 0)) 
			str.Format(_T("%12.3g "),SquareC);
		else
			str.Format(_T("%12lf"),SquareC);
	}
	else
	{
		fStr.Format(_T("%%12.%dlf"),7-pData->m_precisionTypeS);
		str.Format(fStr,SquareC);
	}


	wsprintf(pData->m_Square,_T(" %13.13s %s%s "),str,strQ,uomName);//.GetBuffer(),

	
	for(int i=0;i<wcslen(pData->m_Square);i++)
		if(pData->m_Square[i]!=' ' || pData->m_Distance[i]!=' ')
		{	
			int len=(int)wcslen(pData->m_Square);
			for(int j=0;j<=len;j++)
			{
				pData->m_Square[j]=pData->m_Square[j+i];
				pData->m_Distance[j]=pData->m_Distance[j+i];
			}
			break;
		}
	
	//strncpy((char *)pData->m_Square,LPCSTR(str.GetBuffer()),24);



	if(pData->m_pView)		pData->m_pView->RedrawView( NULL, TRUE, VIEW_UPDATE_OVERDRAW );
}



//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////



BOOL OverdrawFunction( Cdfi_View *pView, Cdfi_MemoryDC *pMemDC, LPVOID pParam)
{
	SCALE_DATA *pData=(SCALE_DATA *)pParam;

	if(!pData) return false;

	if(pData->m_pPolygon==NULL) return false;
	
	CRect rcUpdate;

	CDC *pDC = pMemDC->GetPtrDC();

	int iSize;

	int iCountPoints;
		
	CPoint *pPointsScreen = NULL;

	COLORREF Color;
	HPEN hPenDefault, hOldPen;

	pView->GetUpdateClientRect( &rcUpdate );

	int br=(pData->m_lineColorNum&0x8)?255:128;
	int r=(pData->m_lineColorNum&0x1)*br;
	int g=((pData->m_lineColorNum>>1)&0x1)*br;
	int b=((pData->m_lineColorNum>>2)&0x1)*br;

	
	r=GetRValue(pData->m_lineColor);
	g=GetGValue(pData->m_lineColor);
	b=GetBValue(pData->m_lineColor);
	if((r+g+b)>(127*3)) br=128;else br=255;

	/////
	pDC->SetROP2( R2_COPYPEN );
	pDC->SetBkColor( RGB(1,1,1) );

	// size screen points array   
	Color = RGB( r, g, b );  
  
	hPenDefault = ::CreatePen(pData->m_lineStyle, pData->m_lineWidth, Color );//PS_DOT
	hOldPen = (HPEN)::SelectObject( pDC->m_hDC, hPenDefault);

	//draw
	ASSERT(pData->m_pPolygon->GetSize() < INT_MAX);
	iSize = (int)pData->m_pPolygon->GetSize();

	iCountPoints = pData->m_pPolygon->GetSize();

	pPointsScreen = new CPoint[iCountPoints];

	pView->GetCoordView()->GeoPointsToClient( (CIC_Point3DD *)pData->m_pPolygon->GetData(), pPointsScreen, iCountPoints );
			
	pDC->Polyline( pPointsScreen, iCountPoints );

	int x=pPointsScreen[iCountPoints-1].x;
	int y=pPointsScreen[iCountPoints-1].y;
		
	delete [] pPointsScreen;
			
	
	if(pData->m_textBacklight)
	{
		br=(br==255?0:255);		
		pDC->SetTextColor(RGB(255-br,255-br,255-br));
		pDC->SetBkColor(RGB(br,br,br));
		pDC->SetBkMode(OPAQUE);
	}
	else
	{
		pDC->SetTextColor(RGB(r,g,b));			
		pDC->SetBkMode(TRANSPARENT);
	}
	// choose font
	LOGFONT lf;
    lf.lfHeight = 16; 
	lf.lfWidth = 0; 
    lf.lfEscapement = 0;
    lf.lfOrientation = 0; 
	lf.lfWeight = FW_NORMAL; 
    lf.lfItalic = 0;
    lf.lfUnderline = 0; 
	lf.lfStrikeOut = 0; 
	lf.lfCharSet = ANSI_CHARSET; 
    lf.lfOutPrecision = OUT_DEFAULT_PRECIS; 
	lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
    lf.lfQuality = PROOF_QUALITY; 
    lf.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;  
	wcscpy_s(lf.lfFaceName,_T("Courier New"));// 16
	//("Lucida Console")); - 14 
	// Fixedsys - 8

	CFont ft;
	ft.CreateFontIndirect(&lf);
	CFont* oldf=pDC->SelectObject(&ft);
	
	TEXTMETRIC tm;//=new LPTEXTMETRIC();
	pDC->GetTextMetrics(&tm);
	
	if(pData->m_showDistance)	
		pDC->TextOutW(x+4,y+4,pData->m_Distance),y+=(tm.tmHeight);
	if(pData->m_showSquare)	
		pDC->TextOutW(x+4,y+4,pData->m_Square);
	
	

	if(hPenDefault)
	   ::DeleteObject(hPenDefault);
	
	if(oldf)
	   pDC->SelectObject(oldf); 

	return true;
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
BOOL TryDraw(SCALE_DATA *pData)
{
#ifdef DIRECT_DRAW
	return false;
#endif
	if( !pData) return false;
	if( !pData->m_pView)				return FALSE;
	if( !pData->m_pPolygon )		return false;

	Cdfi_View * pView=pData->m_pView;

	HDC hDC;
	CPen pen;
	HGDIOBJ hOldPen;
	CIC_Point64 ptC1, ptC2;
	//POINT ptCur, 
	POINT *pScrPoints;
	int   count;
	
	count = pData->m_pPolygon->GetSize();

	if(count<2) return false;

	pScrPoints = new POINT[count];

	//CGeoInfo *pGeoInfoDoc=pData->m_pDocument->GetDocGeoInfo();

	Cdfi_CoordView *cv=pView->GetCoordView();

	if(cv==NULL) return false;

	CIC_Point3DD *pp=(CIC_Point3DD *)pData->m_pPolygon->GetData();

	cv->GeoPointsToClient(pp, (CPoint *)pScrPoints, count);

	hDC=pView->GetDC();   

	SetROP2(hDC, R2_XORPEN);

	SetBkColor( hDC, RGB(0,0,0));
	//SetTextColor(hDC, RGB(255,255,255));

	pen.CreatePen(PS_SOLID, 1, pData->m_lineColor);// RGB(255,255,255));
	hOldPen = SelectObject(hDC, pen.m_hObject);

			
	MoveToEx( hDC, pScrPoints[count-2].x, pScrPoints[count-2].y, NULL);
	LineTo( hDC, pScrPoints[count-1].x, pScrPoints[count-1].y);

	SelectObject(hDC, hOldPen);
	pen.DeleteObject();

	pView->ReleaseDC(hDC);

	if ( pScrPoints )
		delete pScrPoints;

	return true;
}
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////



