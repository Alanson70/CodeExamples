#include "StdAfx.h"
#include "vectorsel.h"

#include "resource.h"
#include "vectorcomfunction.h"
#include "MathSpace\\ic_math.h"
#include "Windowsx.h"
#include "dfi_Layer.h"
#include "vectorObjectInfo.h"
#include "IC_ManagerVectorStyle.h"
#include "VectorStyle\\IC_StyleObject.h"
#include "VectorStyle\\IC_StyleLine.h"
#include "VectorStyle\\IC_StyleMarker.h"
#include "VectorStyle\\IC_StylePolygon.h"
#include "VectorStyle\\IC_StyleText.h"
#include "dfi_VectorObjectStream.h"
#include "remove.h"

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
CVectorSel::CVectorSel(void)
{
	pHistoryItem = NULL;

	m_NumCursors = 10;
	//hCursor[0] =  AfxGetApp()->LoadStandardCursor(IDC_ARROW );  //IC_HIT_NOTHING
	hCursor[0] = AfxGetApp()->LoadCursor(IDC_POINTER );  //IC_HIT_NOTHING
	hCursor[1] = AfxGetApp()->LoadStandardCursor(IDC_SIZENWSE );  //IC_HIT_TOPLEFT
	hCursor[2] = AfxGetApp()->LoadStandardCursor(IDC_SIZENS );   //IC_HIT_TOP
	hCursor[3] = AfxGetApp()->LoadStandardCursor(IDC_SIZENESW ); // IC_HIT_TOPRIGHT
	hCursor[4] = AfxGetApp()->LoadStandardCursor(IDC_SIZEWE );  // IC_HIT_RIGHT
	hCursor[5] = AfxGetApp()->LoadStandardCursor(IDC_SIZEALL );  // IC_HIT_MIDDLE

	hCursor[6]  = AfxGetApp()->LoadCursor( IDC_ROTATE_LEFT );  // 
	hCursor[7]  = AfxGetApp()->LoadCursor( IDC_ROTATE_UP );  // 
	hCursor[8]  = AfxGetApp()->LoadCursor( IDC_ROTATE_RIGHT );  // 
	hCursor[9]  = AfxGetApp()->LoadCursor( IDC_ROTATE_BOTTOM );  // 
}
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
CVectorSel::~CVectorSel(void)
{
	for(int i=0; i<m_NumCursors; i++)
	{
		if ( hCursor[ i ] )
		::DeleteObject( hCursor[ i ] );
	}
}
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
bool  VectorSelect( CDFI* pDfi, IC_PARAM *pParam )
{
AFX_MANAGE_STATE( AfxGetStaticModuleState() );
VECTOR_SEL_STRUCT   *pStruct;
IC_FUNCTION_IDENTIFY   fi;
int    numLayer, ifindex;
Cdfi_Document  *pDoc= NULL;
Cdfi_Vector *pVector;
Cdfi_VectorObject *pVObj;
__int64 ObjID;

	// this function is need for init first time attributes
	ifindex = pDfi->GetApp()->GetFncFunctions()->GetFuncIndex( (void *)VectorSelect );	
	if ( ifindex<0 )
		return false;

	pDfi->GetApp()->GetFncFunctions()->GetFunctionInfo( ifindex, &fi );
	pStruct = (VECTOR_SEL_STRUCT*)fi.pProcInfo;

	/// init enw class
	if( (pParam==NULL)||( pParam->message == FM_DEFAULT ))
	{

		if ( !pStruct->pClass )
		pStruct->pClass = new CVectorSel();

		if ( pDfi )
		{
			pDoc = pDfi->GetMainFrame()->GetActiveDocument();
			if ( pDoc )
			{
				// lock document
				if (!pDoc->LockDocument(MODE_ACCESS_READ) )
					return false;

				numLayer = pDoc->GetLayers()->GetLayerActive( IC_VECTOR_CLASS_NAME );
				if (  numLayer>= 0 )
				{
					pVector = pDoc->GetLayers()->GetLayer( numLayer )->GetVector();
					if (pVector)
					{
						Cdfi_VectorObjectStream voStream( pVector, VMEM_READ );

						if ( pVector->GetActiveCount()==1 )
						{
							ObjID = pVector->GetActiveObjectID( 0 );

							pVObj = voStream.GetVectorObject(ObjID);

							if (pVObj)
							{
								if ( pVector->GetActiveMode( ObjID ) != IC_OBJ_ACTIVE_EDIT_BOUND )
								{
									pVector->SetActiveMode( ObjID, IC_OBJ_ACTIVE_EDIT_BOUND, TRUE );
									pVector->UpdateActiveBoundRect();

									pDoc->RedrawViews(TRUE, numLayer );
								}
							}

						}
					}
				}

				// unlock document
				pDoc->UnlockDocument(MODE_ACCESS_READ);
			}
		}
	}

	//// delete class and memory 
	if ( pParam )
		if( pParam->message == FM_DESTROY_ALL )
		{
			if ( pStruct )
			{
				if ( pStruct->pClass )
				{
					delete pStruct->pClass;
					pStruct->pClass = NULL;
				}
			}
		}

/////////////////////////////////////////////////////

return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

bool UpdateVectorSelect( CDFI* pDfi, CCmdUI * pExtra )
{
/// do anything
Cdfi_Document  *pDoc= NULL;

	if ( pDfi )
	{
		pDoc = pDfi->GetMainFrame()->GetActiveDocument();

		if ( pDoc )
		{
			if(pDoc->IsLockDocument())
				return false;

			if ( !pDoc->LockDocument(MODE_ACCESS_READ) )
				return false;

			if ( pDoc->GetLayers()->GetLayerActive( IC_VECTOR_CLASS_NAME ) >= 0 )
			{
				pDoc->UnlockDocument(MODE_ACCESS_READ);
				return true;
			}

			pDoc->UnlockDocument(MODE_ACCESS_READ);
		}
	}
return false;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

bool VectorSelectProc( CDFI * pDfi, IC_PARAM * pParam )
{
AFX_MANAGE_STATE( AfxGetStaticModuleState() );

int          ifindex,  numLayer;
Cdfi_View    *pView;
Cdfi_Document   *pDoc;
Cdfi_Vector    *pVectorLayer;
Cdfi_VectorObject *pVectorObject = NULL;

VECTOR_SEL_STRUCT   *pStruct;
IC_FUNCTION_IDENTIFY   fi;
CPoint	ptClient;
CIC_Rect64		rcClient;
CIC_Rect3DD		rcGeo, rcABound;
CIC_Point3DD	ptGeo, ptPixelSize;
INT_PTR ret = 0;
int	hitTest, selNew;
unsigned int iKeyStatus;
bool   bShift,bRKey,bCtrl;
IC_HIT_TEST_POINT HitTestData;
__int64 objID = -1;
double dTolerance;
bool bModify = false;
CString str=_T("");

Cdfi_SearchVectorObject Search;

	/// do anything
	if( !pDfi )
		return false;
	
	/////////////////////////////
	if ( pParam->message != WM_LBUTTONDOWN )
	 if ( pParam->message != WM_LBUTTONDBLCLK )
	   if ( pParam->message != WM_RBUTTONDOWN )
		 if ( pParam->message != WM_MOUSEMOVE  )
		    if ( pParam->message != WM_KEYDOWN ) 
		       if( pParam->message != WM_KEYUP )
		           return false;

	///////////////////////////////////////////////////////////
	if ( pDfi->GetApp()->GetObjectType( pParam->pObject )!= OBJECT_VIEW )
		return false;
	///////////////////////////////////////////////////////////

	ifindex = pDfi->GetApp()->GetFncFunctions()->GetFuncIndex( (void *)VectorSelectProc );	
	if ( ifindex<0 )
		return false;

	pDfi->GetApp()->GetFncFunctions()->GetFunctionInfo( ifindex, &fi );
	pStruct = (VECTOR_SEL_STRUCT *)fi.pProcInfo;
	
	pStruct->pDfi = pDfi;

	pView = (Cdfi_View *)pParam->pObject;
	pStruct->pObject = pParam->pObject;
	pDoc = pView->GetDocument();

	// Context menu
	if(pParam->message ==WM_RBUTTONDOWN)
	{		
		InitContextMenu( pDfi, pView->GetDocument() );
		return true;
	}

	// lock document
	if ( !pDoc->LockDocument(MODE_ACCESS_READ) )
		return false;

	///// get client and geo coordinates mouse
	ptClient.x = GET_X_LPARAM( pParam->lParam );
	ptClient.y = GET_Y_LPARAM( pParam->lParam );
	pView->GetCoordView()->ClientPointToGeo( &ptClient, &ptGeo );
	pView->GetCoordView()->GetClientPixelSize( &ptPixelSize );
	dTolerance = max(ptPixelSize.x, ptPixelSize.y )*4;

	if ( pView->GetStatusSnap() )
	{
		if ( pView->GetFirstSnapHitTestPoint( &HitTestData ) )
			ptGeo = HitTestData.ptTarget;
	}

	pStruct->ptGeoStart = pStruct->ptGeoCurrent =ptGeo;

	////  find  selection and items
	numLayer =  pDoc->GetLayers()->GetLayerActive( IC_VECTOR_CLASS_NAME );
	if ( numLayer<0)
	{
		pDoc->UnlockDocument(MODE_ACCESS_READ);
		return false;
	}	

	pVectorLayer = pDoc->GetLayers()->GetLayer( numLayer )->GetVector();

	/// delete selection item
	if( pParam->message == WM_KEYDOWN )
	{
		if (pParam->wParam==VK_DELETE)  // Delete key
		{			
			// Delete key			
			
			pDoc->UnlockDocument(MODE_ACCESS_READ);

			//23.10.13 устранение warning C4800: BOOL: принудительно задано логическое значение "true" или "false" (предупреждение о производительности)
			//bModify = RemoveActiveVectorItemsInterface( pDfi, pDoc, pVectorLayer );
			if (RemoveActiveVectorItemsInterface( pDfi, pDoc, pVectorLayer ))
				bModify = true;
			else
				bModify = false;

			return bModify;
		}
	}	


	pVectorLayer->GetActiveBoundRect( &rcABound );

	selNew = VE_SELECT_NOTHING;  // 0
	hitTest = IC_HIT_NOTHING;

	pStruct->numLayer = numLayer;

	//// CTRL
	iKeyStatus = GetKeyState( VK_SHIFT );  // VK_MENU VK_CONTROL VK_SHIFT
	if ( iKeyStatus>>2 )
		bShift = true;  // Add object active 
	else
		bShift = false; // replace active object

	//// SHIFT
	iKeyStatus = GetKeyState('R'); //При нажатии клавиши 'R' поднимается флаг bRKey // VK_MENU VK_CONTROL VK_SHIFT
	if ( iKeyStatus>>2 )
		bRKey = true;  // Add object active 
	else
		bRKey = false;   // replace active object

	iKeyStatus = GetKeyState( VK_CONTROL ); 
	if(iKeyStatus>>2)
		bCtrl = true;
	else
		bCtrl = false;

	Cdfi_VectorObjectStream voStream( pVectorLayer, VMEM_READ );

	////////////////////////////////////////////////
	/// if WM_LBUTTONDBLCLK
	if ( pParam->message == WM_LBUTTONDBLCLK )
	{
		rcClient = CIC_Rect64( ptClient.x-20, ptClient.y-20, ptClient.x+20, ptClient.y+20 );
		pView->GetCoordView()->ClientRectToGeo( &rcClient, &rcGeo );
		Search.SetArea( &rcGeo );

		pVectorObject = voStream.GetFirstObjectBound(&Search);

		while(pVectorObject)
		{
			// Определяем попали мы в объект или нет
			if ( pVectorObject->IsPointBelongScreen( pView, &ptClient, 3 ) )
			{
				selNew = VE_SELECT_NEW;

				VECTOR_STYLE_INFO vsi = {0};				
				GetVectorStyleInfo( pVectorObject, &vsi );

				// Run Modal dialog
				//CVectorObjectInfo voInfo;
				//voInfo.SetParam( pDfi, pDoc, numLayer, pVectorObject );

				bool iStyleChanged;				
				Cdfi_VectorObject *pVectorObjectNew =NULL;

				ret = SelVectorInfo( pDfi, pView, pDoc, numLayer, pVectorObject, &pVectorObjectNew, &iStyleChanged );

				//ret = voInfo.DoModal();

				if ( ret == IDOK )
				{
					////  Set History
					str.LoadString( AfxGetStaticModuleState()->m_hCurrentResourceHandle, IDS_MODIFY_OBJECT );
					objID = pVectorObject->GetID();
					pDoc->GetHistory()->AddItem( (LPTSTR)(LPCTSTR)str, HISTORY_ACTION_MODIFY, numLayer, pVectorObject, TRUE, &objID, AfxGetInstanceHandle(), IDB_MOVE );

					voStream.Stop();
					voStream.Start( VMEM_READWRITE );

					//03.04.2015 После стрим стоп и старт указатель на векторный объект меняется!
					pVectorObject = voStream.GetVectorObject(objID);
					//voInfo.m_pVectorObjectNew->CopyTo( pVectorObject );
					voStream.ReplaceObject( pVectorObject->GetID(), pVectorObjectNew/*voInfo.m_pVectorObjectNew*/ );

					voStream.Stop();
					voStream.Start( VMEM_READ );

					//voInfo.m_pVectorObjectNew->DeleteObject();
					pVectorObjectNew->DeleteObject();

					pVectorLayer->UpdateGrid(&voStream);
					pDoc->RedrawViews(TRUE, numLayer );
				}
				else
				if (ret == IDCANCEL && iStyleChanged /*voInfo.m_styleChanged*/)
				{
					SetVectorStyleInfo(pVectorObject, &vsi);
					pDoc->RedrawViews(TRUE, numLayer );
				}

				if (vsi.styleObject)
					vsi.styleObject->Release();

				break;
			}

			pVectorObject = voStream.GetNextObjectBound(&Search);
		}
	}

	////////////////////////////////////////////////
	/// if WM_LBUTTONDOWN
	if ( pParam->message == WM_LBUTTONDOWN )
	{
		rcClient = CIC_Rect64( ptClient.x-30, ptClient.y-30, ptClient.x+30, ptClient.y+30 );
		pView->GetCoordView()->ClientRectToGeo( &rcClient, &rcGeo );				

		Search.SetArea( &rcGeo );

		hitTest = pView->GetCoordView()->HitTestBoundRect( &ptGeo, &rcGeo);		
		
		if( hitTest != IC_HIT_NOTHING )
		{
			// R key pressed
			if ( bRKey )
				selNew = VE_SELECT_ACTIVE;
			else
			{
				// Shift key pressed
				if ( bShift|bCtrl )   // add active/rem object object
					selNew = VE_SELECT_NOTHING;
				else   // transform
				{
					if (hitTest == IC_HIT_MIDDLE)
					{
						pVectorObject = voStream.GetFirstActiveObject(&Search);

						while(pVectorObject)
						{
							objID = pVectorObject->GetID();
							
							if ( pVectorObject->IsPointBelongScreen( pView, &ptClient, 3 ) )
							{
								if ( pVectorLayer->GetActiveMode( objID ) == IC_OBJ_ACTIVE_EDIT_BOUND  )
								{
									selNew = VE_SELECT_ACTIVE;
									break;
								}
							}

							pVectorObject = voStream.GetNextActiveObject(&Search);
						}

					}  /// end if (hitTest == IC_HIT_MIDDLE)
					else
						selNew = VE_SELECT_ACTIVE;
				}
			} //end else

		}  //end if ( hitTest>=0 )
		////////////////////////
		if ( selNew == VE_SELECT_NOTHING )
		{
			pVectorObject = voStream.GetFirstObjectBound(&Search);
			while(pVectorObject)
			{
				// Определяем попали мы в объект или нет
				if ( pVectorObject->IsPointBelongScreen( pView, &ptClient, 3 ) )
				{
					// Если выбрали новый объект
					selNew = VE_SELECT_NEW;
					break;
				}
				pVectorObject = voStream.GetNextObjectBound(&Search);
			}
		}
		
		// Если тащим за край BoundRect
		if(pVectorLayer->GetActiveCount() >0 )
		{
			pVectorLayer->GetActiveBoundRect( &rcGeo );		
			hitTest = pView->GetCoordView()->HitTestBoundRect( &ptGeo, &rcGeo);

			if(hitTest!=IC_HIT_NOTHING)
				selNew = VE_SELECT_ACTIVE;
		}

	} //end WM_LBUTTONDOWN
	////////////////////////////////////////////////

	////////////////////////////////////////////////
	//// set cursor
	if (( pParam->message == WM_MOUSEMOVE )||(pParam->message == WM_LBUTTONDOWN)||( pParam->message == WM_LBUTTONUP ))
		SetSelectCursor( pStruct, &rcABound, hitTest, pParam->wParam );

	////////////////////////////////////////////////
	if ( ( pParam->message == WM_LBUTTONDOWN )&&(numLayer>=0) )
	{
		if ( selNew != VE_SELECT_NOTHING )
		{			
			if ( selNew == VE_SELECT_ACTIVE )
			{
				/// Основная функция по изменению объекта 
				/// Transform
				bModify = TransformObject( pDfi, hitTest, (int)pParam->wParam, pStruct, &voStream );

				if (bModify)
				{
					pDoc->InvalidateViews( TRUE, numLayer );
				}
				else
				{
					// bModify == false and select new object
					pVectorObject = voStream.GetFirstActiveObject(&Search);
					while(pVectorObject)
					{						
						if ( pVectorObject->IsPointBelongScreen( pView, &ptClient, 3 ) )
						{
							if ( objID !=pVectorObject->GetID() )
							{
								selNew = VE_SELECT_NEW;
								break;
							}
						}
						pVectorObject = voStream.GetNextObjectBound(&Search);
						if (!pVectorObject)
						{
							pVectorObject = voStream.GetFirstObjectBound(&Search);
							break;
						}
					}

					if (pVectorObject==NULL)  /// Return back active object
						pVectorObject = voStream.GetVectorObject( objID );
					else
					{
						///  Set  selection item
						SetActiveObject( pVectorLayer, pVectorObject->GetID(), bShift|bCtrl, TRUE );

						pDoc->InvalidateViews( TRUE, numLayer );
					}
				}
			}
			else
			{
				///  Set  selection item
				if(pVectorObject)
					SetActiveObject( pVectorLayer, pVectorObject->GetID(), bShift|bCtrl, TRUE );
				pDoc->RedrawViews( TRUE, numLayer );
			}
		}
	}

	/// delete selection item
	/*
	if( pParam->message == WM_KEYDOWN )
	{
		if (pParam->wParam==VK_DELETE)  // Delete key
		{
			voStream.Stop();

			// Delete key
			numLayer = pView->GetDocument()->GetLayers()->GetNumFirstEditLayer( IC_VECTOR_CLASS_NAME );
			bModify = RemoveActiveVectorItemsInterface( pDfi, pView->GetDocument(), numLayer );

			voStream.Start(VMEM_READ);
		}
	}
	*/

	/// clear selection draw style
	if( pParam->message == WM_LBUTTONDOWN )
	{
		if ( ( selNew == VE_SELECT_NOTHING )&&( numLayer>=0 ) )
		{
			if (!(bShift|bCtrl))
			{ 
				pVectorLayer->DisactiveAll();
				pDoc->RedrawViews( TRUE, numLayer );
			}
		}
	}

	if(bModify)
	{
		pDoc->UpdateDocSize(FALSE, FALSE);
		pDoc->InvalidateViews( TRUE, numLayer );
	}

	pDoc->UnlockDocument(MODE_ACCESS_READ );	

return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

bool SetActiveObject( Cdfi_Vector *pVectorLayer, __int64 ObjID, BOOL bFlag, BOOL bSendMessage )
{
///  Set  selection item
int aMode;

	aMode = pVectorLayer->GetActiveMode( ObjID );
	if ( aMode == IC_OBJ_DEFAULT ) 
		aMode = IC_OBJ_ACTIVE_EDIT_BOUND;
	else
		aMode = IC_OBJ_DEFAULT;

	if ( !bFlag )
		pVectorLayer->DisactiveAll();

	pVectorLayer->SetActiveMode( ObjID, aMode, bSendMessage );

return true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
void GetVectorStyleInfo(Cdfi_VectorObject* pVectorObject, VECTOR_STYLE_INFO* info)
{
	if (!pVectorObject || !info)
		return;

	memset(info, 0, sizeof(info));

	// Не забывать делать Release для info->styleObject

	switch (pVectorObject->GetType())
	{
	case VE_ELLIPSE:
		{
			VECTOR_ELLIPSE_STYLE style;
			pVectorObject->GetObjEllipse()->GetStyle(&style);

			info->color = style.ColorOutline;
			info->geo = style.WidthGeoOutline;
			info->pixel = style.WidthOutline;
			info->styleObject = style.pStylePolygon;
			info->zooming = style.Zooming;

			break;
		}

	case VE_LINE:
		{
			VECTOR_LINE_STYLE style;
			pVectorObject->GetObjLine()->GetStyle(&style);

			info->color = style.ColorLine;
			info->geo = style.WidthGeoLine;
			info->pixel = style.WidthLine;
			info->styleObject = style.pStyleLine;
			info->zooming = style.Zooming;

			break;
		}
	case VE_POINT:
		{
			VECTOR_POINT_STYLE style;
			pVectorObject->GetObjPoint()->GetStyle(&style);

			info->angle = style.Angle;
			info->color = style.Color;
			info->geo = style.SizeGeo;
			info->pixel = style.SizePixel;
			info->styleObject = style.pStyleMarker;
			info->zooming = style.Zooming;

			break;
		}
	
	case VE_POLYGON:
		{
			VECTOR_POLYGON_STYLE style;
			pVectorObject->GetObjPolygon()->GetStyle(&style);

			info->color = style.ColorOutline;
			info->geo = style.WidthGeoOutline;
			info->pixel = style.WidthOutline;
			info->styleObject = style.pStylePolygon;
			info->zooming = style.Zooming;

			break;
		}
	case VE_TEXT:
		{
			VECTOR_TEXT_STYLE style;
			pVectorObject->GetObjText()->GetStyle(&style);

			info->angle = style.Angle;
			info->color = style.Color;
			info->geo = style.SizeGeo;
			info->pixel = style.SizePixel;
			info->styleObject = style.pStyleText;
			info->zooming = style.Zooming;

			break;
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
void SetVectorStyleInfo(Cdfi_VectorObject* pVectorObject, VECTOR_STYLE_INFO* info)
{
	if (!pVectorObject || !info)
		return;

	switch (pVectorObject->GetType())
	{
	case VE_ELLIPSE:
		{
			VECTOR_ELLIPSE_STYLE style;

			style.ColorOutline = info->color;
			style.WidthGeoOutline = info->geo;
			style.WidthOutline = info->pixel;
			style.pStylePolygon = info->styleObject->GetPolygonObject();
			style.Zooming = info->zooming;

			pVectorObject->GetObjEllipse()->SetStyle(&style);

			break;
		}
	case VE_LINE:
		{
			VECTOR_LINE_STYLE style;

			style.ColorLine = info->color;
			style.WidthGeoLine = info->geo;
			style.WidthLine = info->pixel;
			style.pStyleLine = info->styleObject->GetLineObject();
			style.Zooming = info->zooming;

			pVectorObject->GetObjLine()->SetStyle(&style);

			break;
		}
	case VE_POINT:
		{
			VECTOR_POINT_STYLE style;

			style.Angle = info->angle;
			style.Color = info->color;
			style.SizeGeo = info->geo;
			style.SizePixel = info->pixel;
			style.pStyleMarker = info->styleObject->GetMarkerObject();
			style.Zooming = info->zooming;

			pVectorObject->GetObjPoint()->SetStyle(&style);

			break;
		}
	case VE_POLYGON:
		{
			VECTOR_POLYGON_STYLE style;

			style.ColorOutline = info->color;
			style.WidthGeoOutline = info->geo;
			style.WidthOutline = info->pixel;
			style.pStylePolygon = info->styleObject->GetPolygonObject();
			style.Zooming = info->zooming;

			pVectorObject->GetObjPolygon()->SetStyle(&style);

			break;
		}
	case VE_TEXT:
		{
			VECTOR_TEXT_STYLE style;

			style.Angle = info->angle;
			style.Color = info->color;
			style.SizeGeo = info->geo;
			style.SizePixel = info->pixel;
			style.pStyleText = info->styleObject->GetTextObject();
			style.Zooming = info->zooming;

			pVectorObject->GetObjText()->SetStyle(&style);

			break;
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
int InitContextMenu(CDFI *pDfi, Cdfi_Document *pDoc )
{
// load menu
CMenu Menu;

UINT SelectID, RemoveID, AddNodeModifyPointID, DeselectAllID ;//AddNewPolygonID, AddNewPolylineID;
CString strSel, strModifyPoint, strAddNode, strRemove, strAddNodeModifyPoint, strDeselectAll ;//strNewPolygon, strNewPolyline;

	strSel = pDfi->GetApp()->GetFncFunctions()->GetFuncDescriptionByName( _T("SelectVObject") );
	SelectID = pDfi->GetApp()->GetFncFunctions()->GetFunctionIDByName( _T("SelectVObject") );

	strAddNodeModifyPoint = pDfi->GetApp()->GetFncFunctions()->GetFuncDescriptionByName( _T("VOAddModifyNode") );
	AddNodeModifyPointID = pDfi->GetApp()->GetFncFunctions()->GetFunctionIDByName( _T("VOAddModifyNode") );

	strRemove = pDfi->GetApp()->GetFncFunctions()->GetFuncDescriptionByName( _T("RemoveVectorObjects") );
	RemoveID = pDfi->GetApp()->GetFncFunctions()->GetFunctionIDByName( _T("RemoveVectorObjects") );

	CString strSelectAll = pDfi->GetApp()->GetFncFunctions()->GetFuncDescriptionByName( _T("VOSelectAll") );
	UINT SelectAllID = pDfi->GetApp()->GetFncFunctions()->GetFunctionIDByName( _T("VOSelectAll") );

	//23.01.2014. Азанов Георгий.В контекстное меню добавлена функция "Отменить выборку"
	strDeselectAll = pDfi->GetApp()->GetFncFunctions()->GetFuncDescriptionByName( _T("VODeselectAll") );
	DeselectAllID = pDfi->GetApp()->GetFncFunctions()->GetFunctionIDByName( _T("VODeselectAll") );

	CString strCut = pDfi->GetApp()->GetFncFunctions()->GetFuncDescriptionByName( _T("CutDocument") );
	UINT CutID = pDfi->GetApp()->GetFncFunctions()->GetFunctionIDByName( _T("CutDocument") );

	CString strCopy = pDfi->GetApp()->GetFncFunctions()->GetFuncDescriptionByName( _T("CopyDocument") );
	UINT CopyID = pDfi->GetApp()->GetFncFunctions()->GetFunctionIDByName( _T("CopyDocument") );

	CString strPaste = pDfi->GetApp()->GetFncFunctions()->GetFuncDescriptionByName( _T("PasteDocument") );
	UINT PasteID = pDfi->GetApp()->GetFncFunctions()->GetFunctionIDByName( _T("PasteDocument") );

	//22.01.2014. Азанов Георгий. Следующие 4 строки взяты в комментарии. Контекстное меню не содержит более строчек "Многоугольник" и "Составная линия"
	/*
	AddNewPolygonID = pDfi->GetApp()->GetFncFunctions()->GetFunctionIDByName( _T("AddVPolygon") );
	strNewPolygon = pDfi->GetApp()->GetFncFunctions()->GetFuncDescriptionByName( _T("AddVPolygon") );
	
	strNewPolyline = pDfi->GetApp()->GetFncFunctions()->GetFuncDescriptionByName( _T("AddVMultiLine") );
	AddNewPolylineID = pDfi->GetApp()->GetFncFunctions()->GetFunctionIDByName( _T("AddVMultiLine") );*/
	/// init menu

	Menu.CreatePopupMenu();

	Menu.AppendMenu(MF_STRING|MF_ENABLED, SelectID, strSel);

	Menu.AppendMenu(MF_STRING|MF_ENABLED, AddNodeModifyPointID, strAddNodeModifyPoint);

	Menu.AppendMenu(MF_STRING|MF_ENABLED,SelectAllID,strSelectAll);
	//23.01.2014. Азанов Георгий. В контекстное меню добавлена функция "Отменить выборку"
	Menu.AppendMenu(MF_STRING|MF_ENABLED,DeselectAllID,strDeselectAll);

	//22.01.2014. Азанов Георгий. Следующие 2 строки взяты в комментарии. Контекстное меню не содержит более строчек "Многоугольник" и "Составная линия"
	/*
	Menu.AppendMenu(MF_STRING|MF_ENABLED, AddNewPolygonID, strNewPolygon);
	Menu.AppendMenu(MF_STRING|MF_ENABLED, AddNewPolylineID, strNewPolyline);
	*/
	Menu.AppendMenu(MF_SEPARATOR);
	Menu.AppendMenu(MF_STRING|MF_ENABLED,CutID,strCut);
	Menu.AppendMenu(MF_STRING|MF_ENABLED,CopyID,strCopy);
	Menu.AppendMenu(MF_STRING|MF_ENABLED,PasteID,strPaste);
	Menu.AppendMenu(MF_STRING|MF_ENABLED, RemoveID, strRemove);


	
	// call popupMenu
	CPoint point;
	GetCursorPos(&point);

	AFX_MANAGE_STATE( pDfi->GetMainFrame()->GetModuleState() );
	UINT nID = ((CWinAppEx *)pDfi->GetApp())->GetContextMenuManager()->TrackPopupMenu( Menu.m_hMenu, point.x, point.y, (CWnd*)pDfi->GetMainFrame());
	if (nID != 0)
		((CWnd*)pDfi->GetMainFrame())->SendMessage(WM_COMMAND, (WPARAM)nID, 0);

	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
