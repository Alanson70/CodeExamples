
#include "StdAfx.h"
#include "VectorInfoClass.h"
#include "VectorInfo.h"
#include "math.h"
#include "dfi_VectorPolygon.h"
#include "dfi_VectorLine.h"
#include "IC_ManagerVectorStyle.h"
#include "VectorStyle\\IC_StylePolygon.h"
#include "XYZDialog.h"
#include "VectorInfoDialog.h"
#include "vectorcomfunction.h"



VECTOR_INFO::VECTOR_INFO(CDFI *pDfi)
{
AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_pDfi = pDfi;
	m_pDocument = NULL;
	//m_pView = NULL;
	m_pLayer = NULL;
	m_LayerNum = -1;
	m_ObjectID = -1;


	m_mode=0;
	m_highlightMode=false;
	m_nodesDrawLock=false;
	m_tempNodeNumber = -1;

	m_pSelNodes = NULL;
	m_pActivePolygon = NULL;
	m_objType = VE_NULL;

	m_updateOverdraw = false;

	m_layersToSearchType = 0;
	m_startSearchingObject = 0;
	m_canAddDelete = false;
	m_doRotateAndInflate = false;
	m_fitObjectToRect = FALSE;
	m_searchInLayers = SEARCH_ALL_VISIBLE;

	m_pSelNodes = new CIC_PolygonD();

	hCursorArrow = ::LoadCursor( AfxGetInstanceHandle(), MAKEINTRESOURCE( IDC_VECTOR_INFO ) );
	hCursorHand = AfxGetApp()->LoadStandardCursor(IDC_HAND);



}

////////////////////////////////////////////////////////////////////////
VECTOR_INFO::~VECTOR_INFO()
{	
	if(m_pSelNodes) 
		delete m_pSelNodes;
	m_pSelNodes = NULL;

	if(m_pActivePolygon)
		delete m_pActivePolygon;
	m_pActivePolygon = NULL;

	OverdrawDelete();

	
	DeleteObject( hCursorArrow );
	DeleteObject( hCursorHand );
}
////////////////////////////////////////////////////////////////////////

void VECTOR_INFO::SetParams(CDFI* pDFI, VECTOR_INFO_DATA* pData)
{
	m_pDfi = pDFI;
	m_pData = pData;
}
////////////////////////////////////////////////////////////////////////

bool VECTOR_INFO::Commander(UINT pMessage,IC_PARAM * pParam)	
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );

	VECTOR_INFO_DATA *pData = NULL;
	Cdfi_View *pView=NULL;
	Cdfi_Document* pDocument;
	CIC_Point64 ptClient;
	CIC_Point3DD ptGeo;
	CIC_Rect64 rcClient;
	CIC_Rect3DD rcGeo;

	if(!m_pDfi) return false;

	pData = GetVectorInfoFunctionData( m_pDfi );

	if(!pData) return false;

	int objType = m_pDfi->GetApp()->GetObjectType( pParam->pObject );
	
	if ( objType == OBJECT_MAINFRAME )
	{	
		Cdfi_MainFrame *pMain;
		pMain = (Cdfi_MainFrame *)pParam->pObject;
		if(!pMain) return false;
		pDocument = pMain->GetActiveDocument();
		if(!pDocument) return false;
		pView = (Cdfi_View *)pDocument->GetActiveView( OBJECT_VIEW );		
	}
	else	
	if ( objType == OBJECT_VIEW )
	{	
		pView = (Cdfi_View *)pParam->pObject;
		if(!pView) return false;
		pDocument = pView->GetDocument();
	}
	else	
	if ( objType == OBJECT_DOCUMENT )
	{
		pDocument = (Cdfi_Document*)pParam->pObject;
		if(!pDocument) return false;
		pView = (Cdfi_View *)pDocument->GetActiveView( OBJECT_VIEW );
	}
	else return false;
		
		
	// Document control
	
	switch(pMessage)
	{	
		case FM_DEFAULT:		

			UpdateCursor();
			//		SetDocument(NULL);			
		return true;

		case FM_END_FUNCTION:			
			//????????????????  called when DEM macros begins to work
			//if (pParam->FunctionID == m_pDfi->GetApp()->GetFncFunctions()->GetFunctionID(VectorInfo))
				//SetDocument(NULL);	
#ifdef _DEBUG
		{
			int b = 0;
		}
#endif

		return true;

		case FM_CLOSED_DOCUMENT:
		case FM_CLOSE_DOCUMENT:	

			SetDocument(NULL);		

		return true;
		
		case WM_LBUTTONDOWN:

			SetDocument(pDocument);
			//UpdateCursor();
		break;

		case FM_CALL_FUNCTION:

			//SetDocument(pDocument);
			UpdateCursor();

		return true;

		case WM_SETFOCUS : 

			SetDocument(pDocument);			

		return true;		
					
		case FM_VIEW_ACTIVATE :
		case FM_VIEW_DEACTIVATE :

		return true;

		case FM_NEW_DOCUMENT:
		case FM_OPEN_DOCUMENT:
		case FM_SHOW_DOCUMENT:
		case FM_CREATE_DOCUMENT:
			//SetDocument(pDocument);
		return true;	

		//case FM_LAYER_CLEAR_SELECT:
		case FM_LAYER_CHANGE_MODEL:
		case FM_REMOVE_ALL_LAYERS:
		case FM_LAYER_CLEAR_EDIT:
		//case FM_LAYER_SET_SELECT:
		case FM_LAYER_SET_EDIT:
		case FM_UPDATE_LAYER :
		case FM_REMOVE_LAYER:
		case FM_INSERT_LAYER:
		case FM_LAYER_DOWN:
		case FM_ADD_LAYER:
		case FM_LAYER_UP:
			if(!SetDocument(NULL))
				m_pendingMessage.push_back(*pParam);	

		return true;	
				
	}		
	

	if(pDocument != m_pDocument) return true;

	SetView(pView);
		
	// Objects Control

	switch (pMessage)
	{
		case FM_OBJECT_UNLOCK :
		{					
			std::vector<IC_PARAM>::iterator it;
			IC_PARAM param;

			for(it = m_pendingMessage.begin();it!=m_pendingMessage.end();it++)
			{
				param = *it;

				Commander(param.message,&param);

			}
			m_pendingMessage.clear();
		}
		break;

		//	case FM_VECTOR_OBJ_ACTIVE :
		case FM_VECTOR_OBJ_CHANGE:
		{
			if (this->m_LayerNum == pParam->wParam && m_ObjectID == pParam->lParam)
			{
				if (m_pDocument->IsLockDocument(MODE_ACCESS_WRITE))
				{
					m_pendingMessage.push_back(*pParam);
				}
				else
				{
					if (pDocument->LockDocument(MODE_ACCESS_READ))
					{
						UpdateActiveObject();
						pDocument->UnlockDocument(MODE_ACCESS_READ);
					}
				}
			}
		}
		break;

		case FM_UPDATE_LAYER :
		//wParam = номер слоя, lParam = номер объекта

			if(!SetDocument(NULL))						
				m_pendingMessage.push_back(*pParam);		

		return false;

		default :	
			
			if(pMessage < WM_USER) return true;

			if (pDocument->LockDocument(MODE_ACCESS_READ))
			{
				ModeCommander(pMessage, pParam->wParam, pParam->lParam);

				pDocument->UnlockDocument(MODE_ACCESS_READ);
			}

		break;		

		case WM_KEYDOWN :

			if (pDocument->LockDocument(MODE_ACCESS_READ))
			{
				ModeCommander(pMessage, pParam->wParam, pParam->lParam);

				pDocument->UnlockDocument(MODE_ACCESS_READ);
			}
		break;
				
		case WM_MOUSEMOVE:
			UpdateCursor();
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP :
		case WM_LBUTTONUP:
		case WM_LBUTTONDBLCLK:			
		{
			//if(GetAsyncKeyState(VK_LBUTTON) == 0); // not pressed
			if (!pDocument->LockDocument(MODE_ACCESS_READ))
				return false;
		
			///// get client and geo coordinates mouse
			ptClient.x = GET_X_LPARAM( pParam->lParam );
			ptClient.y = GET_Y_LPARAM( pParam->lParam );
			pView->GetCoordView()->ClientPointToGeo( &ptClient, &ptGeo );
		
			rcClient.SetRect( ptClient, ptClient );
			rcClient.InflateRect( TOLERANCE, TOLERANCE );
			pView->GetCoordView()->ClientRectToGeo( &rcClient, &rcGeo );

			m_ptGeo=ptGeo;
			m_rcGeo=rcGeo;

			RECT rect;
			GetWindowRect(pView->GetHWND(),&rect);
			if(ptClient.x<0 || ptClient.y<0 || (ptClient.x>(rect.right-rect.left)) || (ptClient.y>(rect.bottom-rect.top)))
			{
				//ModeCommander(WM_KEYDOWN, VK_ESCAPE, 0); do not work
			}
			else
			{
				ModeCommander(pMessage, pParam->wParam, pParam->lParam);
			}

			if(pDocument->IsLockDocument(MODE_ACCESS_READ))
				pDocument->UnlockDocument(MODE_ACCESS_READ);
		}
		break;
	}
	
	if(m_updateOverdraw==true)
	
		OverdrawUpdate();
	

	return true;	 

}



	
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void VECTOR_INFO::SetView(Cdfi_View *pView)
{
	static Cdfi_View *m_pView = 0;

	pView = (Cdfi_View *)m_pDocument->GetActiveView(OBJECT_VIEW);

	if(pView != m_pView)
	{
		if (pView)
		{
			if (!pView->IsPreview())
			{
				m_pView = pView;

				OverdrawInit();

				UpdateCursor();
			}
			else
			{

				OverdrawDelete();
				pView = m_pView;
			}
		}
		else
			m_pView = NULL;
	}
}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

bool VECTOR_INFO::SetDocument( Cdfi_Document* pDocument )
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );

	if ( m_pDocument != pDocument )
	{		

		if(m_pDocument)
		{				
			if (m_pDocument->IsLockDocument(MODE_ACCESS_WRITE)) return false;
			
			if (!m_pDocument->LockDocument(MODE_ACCESS_READ)) return false;
			
			m_mode = MODE_COMMON;
					
			//if(pDocument) // temp
			
			ClearAllSelections();
			
			OverdrawDelete();
					
			m_pDocument->UnlockDocument(MODE_ACCESS_READ);

			UpdateCursor();
		}					
				
		if(pDocument)
		{
			if (pDocument->IsLockDocument(MODE_ACCESS_WRITE)) return false;

			if (!pDocument->LockDocument(MODE_ACCESS_READ)) return false;
			
			m_pDocument = pDocument;		

			pDocument->UnlockDocument(MODE_ACCESS_READ);

			OverdrawInit();	
		}
		else
			m_pDocument = NULL;
		
						
		
	}
	return true;
}


///////////////////////////////////////////////////////////////////




void VECTOR_INFO::ModeCommander(UINT pMessage,WPARAM wParam,LPARAM lParam)
{		
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );

	int nLayer;
	__int64 nObj;
	int nSection;
	int ctrlButton=0;
	int shiftButton=0;
	int altButton=0;
	int nodeIndex=-1;

	if(pMessage==WM_USER_SELECT_OBJ)
	{
		VECTOR_OBJ_INFO *voi=(VECTOR_OBJ_INFO *)wParam;
		if(voi)
		{
			nLayer=voi->nLayer;
			nObj=voi->nObj;
			nSection=voi->nSect;
		}
	}
	else
	{
		int iKeyStatus = GetKeyState( VK_CONTROL );  // VK_MENU VK_CONTROL VK_SHIFT
			if ( iKeyStatus&0x80 )	ctrlButton=1;  
		iKeyStatus = GetKeyState( VK_SHIFT );  // VK_MENU VK_CONTROL VK_SHIFT
			if ( iKeyStatus&0x80 )	shiftButton=2;
		iKeyStatus = GetKeyState( VK_MENU );  // VK_MENU VK_CONTROL VK_SHIFT
			if ( iKeyStatus&0x80 )	
				altButton=4;
	}



	switch(m_mode)
	{

		case MODE_COMMON :
		
			if(pMessage==WM_USER_SELECT_OBJ) // message from dialog
			{
				if(SetActiveObject(nLayer,nObj,nSection))
					
					FitActiveObject();

				else
					this->ClearActiveObject();//SelectedObjects();
					//m_mode=MODE_OBJ_EDITING;
			}
			else

			if(pMessage==WM_KEYDOWN )
			{			
				if(wParam == VK_ESCAPE)
				{
					this->ClearSelectedObjects();// ClearAllSelected();
				}
				else	
				if(wParam == VK_DELETE)
				{
					if(m_canAddDelete==true)
						if((GetNodesCount() - this->GetSelectedNodesCount()) >3)
							RunXYZDialog(IDS_VINFO_XYZ_DEL);
				}
				else
				if(wParam == VK_INSERT)
				{
					if(m_canAddDelete==true)// && GetSelectedNodesCount()>0)
						RunXYZDialog(IDS_VINFO_XYZ_ADD);
				}	
				else
				if(wParam == VK_RETURN)
				{
					if(m_canAddDelete==true) 
						if(GetSelectedNodesCount()==1)
							RunXYZDialog(IDS_VINFO_XYZ_EDIT);
						else
						if(GetSelectedNodesCount()>1)
							RunXYZDialog(IDS_VINFO_XYZ_MOVE);
				}	
				else
				if(wParam == 65 && ctrlButton>0)
				{
					m_nLastSelected = GetNodesCount()-1;

					SetNodeSelected(0,true,2);
				}
			}/*
			else
			if(pMessage == WM_LBUTTONDBLCLK)
			{
				if(GetSelectedNodesCount()==1)
					RunXYZDialog(IDS_VINFO_XYZ_EDIT);
			}*/
			else
			if(pMessage == WM_RBUTTONUP)
			{
				if(GetNodeUnderMouse(nodeIndex)  )
				{
					
					if(IsItSelectedNode(nodeIndex)) // IsActiveObjectUnderMouse())
					{								
						int mode = RunContextMenu();

						if(mode<1) return;

						if(mode == IDS_VINFO_XYZ_SELECT_ALL)
						{	
							this->m_nLastSelected = GetNodesCount()-1;

							SetNodeSelected(0,true,2);

							return;
						}
					
						m_pDocument->UnlockDocument(MODE_ACCESS_READ);

						
						RunXYZDialog(mode);

						if (!m_pDocument->LockDocument(MODE_ACCESS_READ))
							return;
					}
				}
			}	

			else
			if(pMessage==WM_MOUSEMOVE)
			{				
				if(GetNodeUnderMouse(nodeIndex)  || IsLineUnderMouse())				
					m_highlightMode=true;			
				
				else
					m_highlightMode=false;
			}
			else
			if(pMessage == WM_RBUTTONDOWN)
			{
				if( ctrlButton) return;

				if(GetNodeUnderMouse(nodeIndex))
					
					if(!IsItSelectedNode(nodeIndex)) //					
					
						SetNodeSelected(nodeIndex, true, 0 );
					
			}
			else
			if(pMessage==WM_LBUTTONDOWN || pMessage == WM_LBUTTONDBLCLK )
			{
									
				if(GetNodeUnderMouse(nodeIndex)  )
				{					
					if(shiftButton) 
					{
						m_mode = MODE_CHOOSE_NODES;
						return;
					}

					if(IsItSelectedNode(nodeIndex)) //					
					{						

						if( ctrlButton)
							SetNodeSelected(nodeIndex, false, ctrlButton);						
					}
					else
					{
						
						SetNodeSelected(nodeIndex, true, ctrlButton );
					}
				
					if( ctrlButton) return;
						
					
					//else	// select another node in current addmode
					
					if( ctrlButton == shiftButton ) // no both of them 
					{					
						m_doRotateAndInflate=altButton?true:false;

						if(m_pActivePolygon)
							m_ptCenter = m_pActivePolygon->GetCenterPolygon();
						else
							m_doRotateAndInflate = false;
					
						m_mode=MODE_MOVE_NODES;
						m_ptBase = m_ptGeo;
						m_ptPrev = m_ptGeo;
					}
					//DeleteTempNode();
					
					return;
				}
						
				if(m_canAddDelete)
				{
					if(IsLineUnderMouse())
					{

						if(AddTempNodeOnLine())
						{
							m_mode=MODE_MOVE_NODES;

							SetNodeSelected(m_tempNodeNumber, true, ctrlButton|shiftButton);

							m_ptBase.x=m_ptGeo.x;
							m_ptBase.y=m_ptGeo.y;
							m_ptBase.z=m_ptGeo.z;
							m_ptPrev.x=m_ptGeo.x;
							m_ptPrev.y=m_ptGeo.y;
							m_ptPrev.z=m_ptGeo.z;
						
						}
						return;
					}
				}					
						
			// selecting objects = mouse down

			
				if(shiftButton)
				{
					m_mode = MODE_SELECT_OBJECTS;
						return;
				}


				SelectObjectsUnderMouse(ctrlButton?true:false,ctrlButton?true:false);

				if(GetActiveObject(nLayer,nObj,nSection) == true)
				{
					if(IsObjectSelected(nLayer,nObj) == false || altButton>0)
					{
						ClearActiveObject();
					}
				}

				if(GetActiveObject(nLayer,nObj,nSection) == false)
				{
					if(GetSelectedObjectUnderMouse(nLayer,nObj,nSection,altButton?-1:0)) // get first selected object under mouse, -1 - from end
					{
						SetActiveObject(nLayer,nObj,nSection);
					}
					else
					{
						for(int i=0;i<this->GetSelectedObjectsCount();i++)
							if(GetSelectedObject(i,nLayer,nObj,nSection))
								if(SetActiveObject(nLayer,nObj,nSection)) break;
					}
				}
				
			}// end of mouse down
			
			

		break;

		//////////////////////////////////////////////////////////

		case MODE_SELECT_OBJECTS :			

			if(pMessage==WM_LBUTTONUP)
			{
				m_mode=MODE_COMMON;

				SelectObjectsUnderMouse(true,false);

				if(GetSelectedObjectUnderMouse(nLayer,nObj,nSection)) // find any selected object under mouse
				{
					SetActiveObject(nLayer,nObj,nSection);
				}

				if(GetActiveObject(nLayer,nObj,nSection) == false)					// select any
				{
					for(int i=0;i<this->GetSelectedObjectsCount();i++)
						if(GetSelectedObject(i,nLayer,nObj,nSection))
							if(SetActiveObject(nLayer,nObj,nSection)) break;
				}
				
				/*
				if(GetSelectedObjectsCount()>0)
				{
					if(GetObjectUnderMouse(nLayer,nObj,nSection)) // is any object under mouse and not create list of all objects

						if(SetActiveObject(nLayer,nObj,nSection)) 
						
							m_mode=MODE_OBJ_EDITING;  // is new active object
				}
				*/
			}			
			else
			if(pMessage==WM_MOUSEMOVE)
			{
				if(GetAsyncKeyState(VK_LBUTTON) == 0) // not pressed
				{
				//	m_mode=MODE_OBJ_SELECTION;
					break;
				}
				SelectObjectsUnderRect(m_ptBase,m_ptGeo);	
			}
		break;

		///////////////////////////////////////////////////////
		case MODE_CHOOSE_NODES :

			if(pMessage==WM_LBUTTONUP)
			{
				m_mode = MODE_COMMON;

				if(m_wasMoving) m_wasMoving=false;

				else
				if(shiftButton == 0)	return;

				if(GetNodeUnderMouse(nodeIndex)  )
				{					
					m_nodesDrawLock=true; // prevents multiply redraws
					
					SetNodeSelected(nodeIndex, true, shiftButton);
						
					m_nodesDrawLock=false;
					
				}

			}
			else
			if(pMessage==WM_MOUSEMOVE)
			{				
				if(GetNodeUnderMouse(nodeIndex)  || IsLineUnderMouse())				
					m_highlightMode=true;			
				
				else
					m_highlightMode=false;
			}
		break;

		///////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////

		case MODE_MOVE_NODES :
			
			if(pMessage==WM_KEYDOWN )
			{			
				if(wParam == VK_ESCAPE)
				{
					DeleteTempNode();
					m_wasMoving=false;
			
					m_tempNodeNumber = -1; 
					m_doRotateAndInflate = false;
					m_mode=MODE_COMMON;

					this->ClearSelectedNodes();
					this->ShowActiveObject();
					//UpdateSelectedNodes();
				}
			}
			else
			if(pMessage==WM_LBUTTONUP)
			{
				if(IsNodeUnderNode(m_ptBase, m_ptGeo)==false)
				{
					StoreActiveObject(); // fixing changes					
					m_wasMoving=true;					
				}
				else
				{
					DeleteTempNode();
					m_wasMoving=false;
				}

				m_tempNodeNumber = -1; 
				m_doRotateAndInflate = false;
				m_mode=MODE_COMMON;
				//ModeCommander(pMessage,wParam,lParam);
			}
			
			else
			if(pMessage==WM_MOUSEMOVE)
			{				

				if(IsNodeUnderNode(m_ptBase, m_ptGeo)==false)	// test we are not so far from start point
				{
					IC_POINT3DD dpt;

					dpt.x=m_ptGeo.x-m_ptPrev.x; 
					dpt.y=m_ptGeo.y-m_ptPrev.y;
					dpt.z=0;//m_ptGeo.z-m_ptPrev.z;
															
					if(m_doRotateAndInflate)
						RotateAndInflateNodesOn(dpt);
					else
						MoveSelectedNodesOn(dpt);

					m_ptPrev=m_ptGeo;
				}
			}
			
		break;

	}

	
}
///////////////////////////////////////////////////////
void VECTOR_INFO::UpdateCursor() // hightlight point if it on polygon contour
{

	if(m_highlightMode)
	{
		if(::GetCursor() != hCursorHand)
			::SetCursor(hCursorHand  );
	}
	else
	{
		if(::GetCursor() != hCursorArrow)
		{		
			::SetCursor(hCursorArrow );
		}
	}
	
}
///////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////







//////////////////  OBJECTS ////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
int VECTOR_INFO::SelectObjectsUnderRect(CIC_Point3DD &firstPoint, CIC_Point3DD &secPoint)
{
	//OnChangeSelectedObjects();
	return 0;
}


/////////////////////////////////////////////////////////////////
int VECTOR_INFO::SelectObjectsUnderMouse(bool addFlag, bool inverseFlag)
{
	int nLayer, N;	
	__int64 nObj;
	bool update=false;

	//ClearSelectedObjects();

	if ( !m_pDocument ) return 0;

	::SetCursor( AfxGetApp()->LoadStandardCursor(IDC_WAIT) );  // IDC_NO


	if(!addFlag) ClearSelectedObjects();
	else	UnhighlightSelectedObjects();

	N = m_pDocument->GetLayers()->GetNumberLayers();
		
	for ( nLayer = 0; nLayer < N; nLayer++ )
	{
		if ( m_pDocument->GetLayers()->GetLayer( nLayer )->GetRegisterClass()->IsClass(IC_VECTOR_CLASS_NAME) )
		{
		//	if(SearchObjectsAtLayer( i)) return true;//, m_ptGeo, pGeoBoundRect );

			if(this->m_searchInLayers == SEARCH_EDIT_LAYER)
			{
				//if ( m_pDocument->GetLayers()->IsLayerEdit( nLayer ) == false  && false == m_pDocument->GetLayers()->IsLayerSelected(nLayer) ) continue;
				if (!m_pDocument->GetLayers()->GetLayer(nLayer)->IsActive()) continue;

			}
			else
			{
				if ( ! m_pDocument->GetLayers()->IsLayerVisible( nLayer ) ) continue;
			}

			CIC_Point3DD pptGeo=m_ptGeo;
			CIC_Rect3DD pGeoBoundRect=m_rcGeo;

			Cdfi_Layer* pLayer;
			Cdfi_Vector* pVectorLayer;
			Cdfi_SearchVectorObject SearchVectorObject;
			CIC_Rect3DD rcSel;
			Cdfi_VectorObject* pVectorObject = NULL;
			CIC_Rect3DD rect;

			pLayer = m_pDocument->GetLayers()->GetLayer(nLayer);

			if ( !pLayer ) 	return 0;

			pVectorLayer = pLayer->GetVector();
			
			rcSel.SetRect( pGeoBoundRect.TopLeft(), pGeoBoundRect.BottomRight() );
			SearchVectorObject.SetArea( &rcSel );
			double A; 
			A = sqrt( pGeoBoundRect.Width()/TOLERANCE*pGeoBoundRect.Width()/TOLERANCE + pGeoBoundRect.Height()/TOLERANCE*pGeoBoundRect.Height()/TOLERANCE ); 
			SearchVectorObject.SetMinObjSize( A );
			
			// stream
			Cdfi_VectorObjectStream voStream( pVectorLayer, VMEM_READ );

			pVectorObject = voStream.GetFirstObjectBound( &SearchVectorObject );
			
			while ( pVectorObject )
			{
				if(pVectorObject->GetType() == VE_TEXT)
				{
					nObj=pVectorObject->GetID();	

					AddObjectToSelectionList(nLayer,nObj,-1,rect);							
							
				}
				else
				if ( pVectorObject->IsPointBelong( &pptGeo, pGeoBoundRect.Width() / 2 ) )
				{
					nObj=pVectorObject->GetID();
					
					pVectorObject->GetBoundRect(&rect);	
										

					if(this->IsObjectSelected(nLayer,nObj,-1)==true && inverseFlag == true)
					{
						RemoveObjectFromSelectionList(nLayer,nObj);
					}
					else
					{
						AddObjectToSelectionList(nLayer,nObj,-1,rect);

						if(pVectorObject->GetType() == VE_POLYGON)
						{
						
							CIC_RegionCmx *pReg=((Cdfi_VectorPolygon *)pVectorObject->GetObjPolygon())->GetRegion();
							for(int i=0;i<pReg->GetPolygonsCount();i++)							
								AddObjectToSelectionList(nLayer,nObj,i,rect);
						}
						else
						if(pVectorObject->GetType() == VE_LINE)
						{
							CIC_RegionCmx *pReg=((Cdfi_VectorPolygon *)pVectorObject->GetObjLine())->GetRegion();							
							for(int i=0;i<pReg->GetPolygonsCount();i++)							
								AddObjectToSelectionList(nLayer,nObj,i,rect);							
							
						}
					}
										
					
					update=true;
				}
				pVectorObject = voStream.GetNextObjectBound( &SearchVectorObject );				
			}					

		}
	}

	ArrangeSelectionList();

	HighlightSelectedObjects();	

	OnUpdateSelectedObjects();

	UpdateCursor();

	return GetSelectedObjectsCount();
}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

bool VECTOR_INFO::GetSelectedObjectUnderMouse(int &res_nLayer,__int64 &res_nObj, int &res_nSect, int order) // order = 0 - first founded, >0 - look over 
{
	if ( !m_pDocument ) return false;

	CIC_Point3DD pptGeo=m_ptGeo;
	CIC_Rect3DD pGeoBoundRect=m_rcGeo;

	Cdfi_Layer* pLayer = NULL;
	Cdfi_Vector* pVectorLayer = NULL;
	Cdfi_VectorObject* pVectorObject = NULL;

	int nLayer = -1;	
	__int64 nObj = -1; 
	int nSect = -1;

	int foundIndex = -1;

	std::vector<VECTOR_OBJ_INFO> objList(m_objList); // make copy
	
	/*
	bool order = true;
	if(index == -1) 
	{
		std::reverse(objList.begin(),objList.end());
		order = false;
		index = abs(index)-1;
	}
	*/

	m_startSearchingObject--;
	
	std::vector<VECTOR_OBJ_INFO>::iterator it;

	for(it=objList.begin();it<objList.end();++it)
	{	
		if(it->nSect >= 0) continue;
		
		if(it->nLayer != nLayer)
		{

			nLayer = it->nLayer;
			
			pLayer = m_pDocument->GetLayers()->GetLayer( nLayer );	
			
			if ( !pLayer ) 	continue;
			
			pVectorLayer = pLayer->GetVector();
			
		}

		if(it->nObj != nObj)
		{
			nObj = it->nObj;

			Cdfi_VectorObjectStream voStream( pVectorLayer, VMEM_READ);//WRITE ); 

			pVectorObject=voStream.GetVectorObject( nObj); 

			if(!pVectorObject) continue;

			//if ( pVectorObject->IsPointBelong( &pptGeo, pGeoBoundRect.Width() / 2 ) )
			{
				if(pVectorObject->GetType() == VE_POLYGON)
				{
						
					CIC_RegionCmx *pReg=((Cdfi_VectorPolygon *)pVectorObject->GetObjPolygon())->GetRegion();

					int count = pReg->GetPolygonsCount();										

					nSect=count;

					for(int i=0;i<count;i++)
					{
						if(order == false) 							nSect --;
						else							nSect = i;
						nSect=i;

						if(pReg->GetPolygon(nSect)->PointLaysOnPolygon(&pptGeo, FALSE, pGeoBoundRect.Width() / 2)!=POINT_OUTSIDE)
						{
							foundIndex++;
							res_nLayer = nLayer;
							res_nObj = nObj;
							res_nSect = nSect;

							if(foundIndex == m_startSearchingObject)

								return true;
						}
					}
					// ??? polygon is fits but sections arn't

				}
				else
				if(pVectorObject->GetType() == VE_LINE)
				{
						
					CIC_RegionCmx *pReg=((Cdfi_VectorPolygon *)pVectorObject->GetObjLine())->GetRegion();

					int count = pReg->GetPolygonsCount();				

					nSect=count;

					for(int i=0;i<count;i++)
					{
						//if(order == false) 							nSect --;
						//else							nSect = i;
						nSect=i;

						if(pReg->GetPolygon(nSect)->PointLaysOnPolygon(&pptGeo, FALSE, pGeoBoundRect.Width() / 2)!=POINT_OUTSIDE)
						{			
							foundIndex++;
							res_nLayer = nLayer;
							res_nObj = nObj;
							res_nSect = nSect;

							if(foundIndex == m_startSearchingObject)

								return true;
						}
					}
					// ??? polygon is fits but sections arn't
				}
				else // other objects
				{					
					nSect=0;
					
					foundIndex++;
					res_nLayer = nLayer;
					res_nObj = nObj;
					res_nSect = nSect;

					if(foundIndex == m_startSearchingObject)					
						
						return true;					
				}
			}
		}
		nObj = -1;
	}

	if(m_startSearchingObject<0) 
		m_startSearchingObject=foundIndex;

	if(foundIndex !=-1)

		return true; // return last found object

	return false;		

}


/////////////////////////////////////////////////////////////////
int VECTOR_INFO::GetSelectedObjectsCount()
{
	return (int)m_objList.size();
}
/////////////////////////////////////////////////////////////////
bool VECTOR_INFO::GetSelectedObject(int n, int &nLayer,__int64 &nObj, int &nSect)
{
	if(n>=m_objList.size()) return false;

	nLayer=m_objList.at(n).nLayer;
	nObj=m_objList.at(n).nObj;
	nSect=m_objList.at(n).nSect;

	return true;//;
}
////////////////////////////////////////////////////////////////////////
bool VECTOR_INFO::IsObjectSelected(int nLayer,__int64 nObj)
{
	std::vector<VECTOR_OBJ_INFO>::iterator it;

	for(it=m_objList.begin();it<m_objList.end();++it)
	{		
		if(it->nLayer == nLayer && it->nObj == nObj ) return true;
	}
	return false;
}
////////////////////////////////////////////////////////////////////////
bool VECTOR_INFO::IsObjectSelected(int nLayer,__int64 nObj, int nSect)
{
	std::vector<VECTOR_OBJ_INFO>::iterator it;

	for(it=m_objList.begin();it<m_objList.end();++it)
	{		
		if(it->nLayer == nLayer && it->nObj == nObj && it->nSect == nSect) return true;
	}
	return false;
}
/////////////////////////////////////////////////////////////////
void VECTOR_INFO::ClearAllSelections()
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );

	ClearActiveObject();
		
	m_objList.clear();

	int nLayer;
	int count;

	count = m_pDocument->GetLayers()->GetNumberLayers();
		
	for ( nLayer = 0; nLayer < count; nLayer++ )
	{
		if ( m_pDocument->GetLayers()->GetLayer( nLayer )->GetRegisterClass()->IsClass(IC_VECTOR_CLASS_NAME) )
		{
			Cdfi_Layer* pLayer;
			Cdfi_Vector* pVectorLayer;

			pLayer = m_pDocument->GetLayers()->GetLayer(nLayer);
			
			if(pLayer)
			{
				pVectorLayer = pLayer->GetVector();
				if(pVectorLayer) 
					//if(!m_pDocument->IsLockDocument(MODE_ACCESS_WRITE))
						
					//if(m_pDocument->IsLockDocument(MODE_ACCESS_READ))
					{
						//m_pDocument->UnlockDocument(MODE_ACCESS_READ);
						pVectorLayer->DisactiveAll();
					}
					
					//if(!m_pDocument->IsLockDocument(MODE_ACCESS_READ))
						//break;

			}
		}
	}			
	
	m_pDocument->RedrawViews(TRUE,-1);

	OnUpdateSelectedObjects();
}
/////////////////////////////////////////////////////////////////
void VECTOR_INFO::ClearSelectedObjects()
{
	ClearActiveObject();

	UnhighlightSelectedObjects();
	
	m_objList.clear();

	OnUpdateSelectedObjects();
}


///////////////////////////////////////////////////////////
void VECTOR_INFO::UnhighlightSelectedObjects()
{
	int nLayer = -1;
	__int64 nObj = -1;;
	Cdfi_Layer* pLayer;
	Cdfi_Vector* pVectorLayer;
	RECT r;
	Cdfi_View *pView;
	
	if(!m_pDocument) return;
	
	std::vector<VECTOR_OBJ_INFO>::iterator it;

	POSITION pos=m_pDocument->GetFirstViewPosition();

	while(pos)
	{
		pView = (Cdfi_View*)m_pDocument->GetNextView(pos);//OBJECT_VIEW, (Cdfi_View *)pView);// >GetActiveView( OBJECT_VIEW );
		
		for(it=m_objList.begin();it!=m_objList.end();it++)
		{
			if( it->nLayer != nLayer || it->nObj != nObj )
			{
				nObj=it->nObj;
				nLayer=it->nLayer;

				pLayer = m_pDocument->GetLayers()->GetLayer(nLayer);
				if(nObj != -1 && pLayer!=NULL)
				{
					pVectorLayer = pLayer->GetVector();
					if(pVectorLayer)					
						pVectorLayer->SetActiveMode( it->nObj, IC_OBJ_DEFAULT, TRUE );

					pView->GetCoordView()->GeoRectsToClient (&it->Rect, &r, 1);
					pView->InvalidateView( &r , TRUE, m_LayerNum );	
				}					
			}
		}
	}
			
}
///////////////////////////////////////////////////////////
void VECTOR_INFO::HighlightSelectedObjects()
{
	// activate objectes

	int nLayer = -1;
	__int64 nObj = -1;
	Cdfi_Layer* pLayer;
	Cdfi_Vector* pVectorLayer;
	RECT r;
	Cdfi_View *pView;
	
	if(!m_pDocument) return;

	std::vector<VECTOR_OBJ_INFO>::iterator it;

	POSITION pos=m_pDocument->GetFirstViewPosition();

	while(pos)
	{
		pView = (Cdfi_View*)m_pDocument->GetNextView(pos);
		
		for(it=m_objList.begin();it!=m_objList.end();it++)
		{
			if( it->nLayer != nLayer || it->nObj != nObj )
			{
				nObj=it->nObj;
				nLayer=it->nLayer;

				pLayer = m_pDocument->GetLayers()->GetLayer(nLayer);
				if(nObj != -1 && pLayer!=NULL)
				{
					pVectorLayer = pLayer->GetVector();
					pVectorLayer->SetActiveMode( it->nObj, IC_OBJ_ACTIVE_OBJECT, TRUE );

					pView->GetCoordView()->GeoRectsToClient (&it->Rect, &r, 1);
					pView->InvalidateView( &r , TRUE, m_LayerNum );	
				}	
			}
		}
	}
}
////////////////////////////////////////////////////////////////
void VECTOR_INFO::ArrangeSelectionList()
{
	std::sort(m_objList.begin(),m_objList.end(),VECTOR_OBJ_INFO_COMPARE());
		
//	VECTOR_OBJ_INFO info;
	int nSec = -1;
	int nLayer = -1;
	__int64 nObj = -1;

	// sort
	std::sort(m_objList.begin(),m_objList.end(),VECTOR_OBJ_INFO_COMPARE());
	// remove dublicatos
	std::vector<VECTOR_OBJ_INFO>::iterator it;
	for(it=m_objList.begin();it!=m_objList.end();)
	{
		if(it->nLayer==nLayer && it->nObj == nObj && it->nSect == nSec)
		{			
			it=m_objList.erase(it);				
		}
		else
		{
			nLayer=it->nLayer;
			nObj=it->nObj;
			nSec=it->nSect;
			it++;
		}
	}
	
}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

void VECTOR_INFO::AddObjectToSelectionList(int nLayer, __int64 nObj, int nSect,CIC_Rect3DD rect)
{	
	VECTOR_OBJ_INFO info;
	info.nLayer=nLayer;
	info.nObj=nObj;
	info.nSect=nSect;
	info.Rect=rect;
	
	m_objList.push_back(info);
}

/////////////////////////////////////////////////////////////////
// change rect
void VECTOR_INFO::UpdateObjectInSelectionList(int nLayer, __int64 nObj, int nSect,CIC_Rect3DD rect)
{	
	VECTOR_OBJ_INFO info;

	std::vector<VECTOR_OBJ_INFO>::iterator it;

	for(it=m_objList.begin();it!=m_objList.end();++it)
	{
		if(it->nLayer==nLayer && it->nObj == nObj)
					
			it->Rect=rect;							
	}
}


/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
void VECTOR_INFO::RemoveObjectFromSelectionList(int nLayer, __int64 nObj)
{
	VECTOR_OBJ_INFO info;
	info.nLayer=nLayer;
	info.nObj=nObj;

	std::vector<VECTOR_OBJ_INFO>::iterator it;
	for(it=m_objList.begin();it!=m_objList.end();)
	{
		if(it->nLayer==nLayer && it->nObj == nObj)
		{			
			it=m_objList.erase(it);				
		}
		else
			it++;
	}
	
}
/////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////



void VECTOR_INFO::ClearActiveObject()
{	
//	if(m_pLayer) m_pLayer->GetVector()->DisactiveAll();

	m_pLayer = NULL;
	m_LayerNum = -1;
	m_ObjectID = -1;
	m_objType = VE_NULL;
	m_tempNodeNumber = -1;

	ClearSelectedNodes();

	UpdateActiveObject();
	
}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
bool VECTOR_INFO::GetActiveObject(int &nLayer, __int64 &nObj, int &nSect)
{
	nLayer=m_LayerNum;
	nObj=m_ObjectID;
	nSect=m_sectionNum;
	if(m_LayerNum == -1 || m_ObjectID == -1) return false;
	return true;
}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
bool VECTOR_INFO::IsActiveObjectUnderMouse() // not used
{					
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );

	if(!m_pActivePolygon) return false;
	
	//CIC_Point3DD ptFound;
	double dTolerance = m_rcGeo.Width()*2 /3;
	//int numPoint=0;
	
	//int count = m_pActivePolygon->GetSize();
		
	//if(m_pActivePolygon->HitTestPoint( &m_ptGeo,  dTolerance,  &numPoint, &ptFound ));
	
	//if(GetNodeUnderMouse(numPoint)) return true;

	if(m_pActivePolygon->PointLaysOnPolygon(&m_ptGeo, FALSE, dTolerance)!=POINT_OUTSIDE) return true;

	//if(m_pActivePolygon->PointBelongPolygon (m_ptGeo.x,m_ptGeo.y,TRUE)!=POINT_OUTSIDE) return true;
	//if(m_pActivePolygon->Point3DBelongPolygon(&m_ptGeo,TRUE)!=POINT_OUTSIDE) return true;
	//if(m_pActivePolygon->PointLaysOnPolygon(m_ptGeo.x,m_ptGeo.y,TRUE,0)!=POINT_OUTSIDE) return true;
				
	return false;
}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
bool VECTOR_INFO::SetActiveObject( int nLayer,__int64 nObjID,int nSect)
{
	if(nLayer != this->m_LayerNum || m_ObjectID != nObjID || m_sectionNum != nSect)
	{				
		m_pLayer = m_pDocument->GetLayers()->GetLayer( nLayer );
		
		if ( m_pLayer && nObjID>=0 && nSect!= -1)
		{
			m_LayerNum = nLayer;
			m_ObjectID = nObjID;
			m_sectionNum=nSect;
			
			UpdateActiveObject();

			return true;
		}
		else
		{
			m_LayerNum = -1;
			m_ObjectID = -1;
			m_sectionNum=-1;
			m_objType=VE_NULL;

			ClearActiveObject();
			
		}
	}
	else
	{
		 // no changes - no actions
		return true;
	}
	return false;
}
///////////////////////////////////////////////////////////////
void VECTOR_INFO::FitActiveObject()
{
	if(m_fitObjectToRect == FALSE) return;

	Cdfi_Document * pDoc = m_pDocument;
	Cdfi_Vector *pVectorLayer = NULL;
	//int iCount = 0;
	CIC_Rect3DD rcBound;
	double dw, dh;
	int iLayer = -1;
	
	POSITION pos=m_pDocument->GetFirstViewPosition();

	if(!pos)	return;
	
	Cdfi_View *pView = (Cdfi_View*)m_pDocument->GetNextView(pos);

	iLayer = pDoc->GetLayers()->GetLayerActive( IC_VECTOR_CLASS_NAME );

	if(iLayer<0) return;

	pVectorLayer = pDoc->GetLayers()->GetLayer( iLayer )->GetVector();

	if(!pVectorLayer) return;

	//pVectorLayer->GetBoundRect( &rcBound );
	rcBound = this->m_objBaseRect;
	rcBound.NormalizeGeoRect();

	if( rcBound.IsRectEmpty() )
	{		
		CIC_Rect3DD rcGeo;
		pView->GetCoordView()->ClientToGeo( &rcGeo );

		CIC_Point3DD ptCenter, ptOffset;
		ptCenter = rcGeo.CenterPoint();
		ptOffset.x = rcBound.left - ptCenter.x;
		ptOffset.y = rcBound.top - ptCenter.y;
		
		rcBound = rcGeo;
		rcBound.OffsetRect( ptOffset.x, ptOffset.y ); 
	}
	else
	{
		dw = rcBound.WidthGeo();///2;
		dh = rcBound.HeightGeo();///2;

		rcBound.left -=dw;
		rcBound.right +=dw;
		rcBound.top +=dh;
		rcBound.bottom -=dh;
	}

	pView->FitGeoRect( rcBound, TRUE, TRUE );
	m_pDocument->RedrawViews(TRUE,this->m_LayerNum);
}
///////////////////////////////////////////////////////////////
void VECTOR_INFO::UpdateActiveObject()
{
	ClearSelectedNodes();

	ShowActiveObject();

	OnUpdateActiveObject();
}

/////////////////////////////////////////////////////////////////


void VECTOR_INFO::DrawSelectedNodes()
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );

	if(m_nodesDrawLock==true) return;

	IC_POINT3DD pt;
	
	if(m_pSelNodes)
		m_pSelNodes->RemoveAll();
	else
		return;

	int count=0;
	
	count=GetSelectedNodesCount();
		
	for(int i=0;i<count;i++)
	{
		GetNodeByNumber(GetSelectedNodeIndex(i),pt);
	 
		m_pSelNodes->AddPoints(&pt);
	}
	
	OverdrawUpdate();
}

///////////////////////////////////////////////////////////////////
bool VECTOR_INFO::GetNodeByIndex(DWORD num, IC_POINT3DD &pt)
{
	return GetNodeByNumber(num,pt);
}

bool VECTOR_INFO::GetNodeByNumber(DWORD num, IC_POINT3DD &pt) // delete later
{	
	
	CIC_PolygonD * pPolygon=m_pActivePolygon;
	
	if(num<m_pActivePolygon->GetSize()) 						
		pt=m_pActivePolygon->GetData()[num];
	else 
		return false;

	return true;
}
/////////////////////////////////////////////////////////////


//Delete temp node
void VECTOR_INFO::DeleteTempNode()
{
	if(m_tempNodeNumber==-1) return;

	DWORD numSection=0;
	DWORD numPoint=0; 
	CIC_Point3DD ptFound;
		
	numPoint=m_tempNodeNumber;

	DeleteNodeFromSelected(m_tempNodeNumber);
	
	int nPoints=0;

	int section = 0;
	
	if(numPoint<m_pActivePolygon->GetSize())
		
		m_pActivePolygon->DeleteAt(numPoint);
	
	SetNodesCount(m_pActivePolygon->GetSize());
		
	m_tempNodeNumber=-1;

	DrawSelectedNodes();		
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
bool VECTOR_INFO::GetNodeUnderMouse(int &numPoint)
{
	////// Проверяем попадание в узел активного векторного объекта////////
	
	CIC_Point3DD ptFound;
	double dTolerance = m_rcGeo.Width()*2 /3;

	numPoint=0;

	if(!m_pActivePolygon) return false;

	
	if(m_pActivePolygon->HitTestPoint( &m_ptGeo,  dTolerance,  &numPoint, &ptFound ))
			return true;

	return false;

}


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
// test if ptNew is near ptBase
bool VECTOR_INFO::IsNodeUnderNode(CIC_Point3DD &ptBase, CIC_Point3DD &ptNew)
{
	double dTolerance = m_rcGeo.Width()*2 /3;
	CIC_Point3DD ptFound;
	int numPoint1,numPoint2;

	if(m_pActivePolygon->HitTestPoint( &ptBase,  dTolerance,  &numPoint1, &ptFound )) 						
	{
		if(!m_pActivePolygon->HitTestPoint( &ptNew,  dTolerance,  &numPoint2, &ptFound )) return false;
		else							
		if(numPoint1 == numPoint2)
			return true;
		else 
			return false;
	}
	
	return false;

	
}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
// test if there is line new mouse coords
bool VECTOR_INFO::IsLineUnderMouse()
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );

	double dTolerance = m_rcGeo.Width()*2 /3;
	int numSection=0;
	int numPoint=0; 
	CIC_Point3DD ptFound;
	
	if(!m_pActivePolygon) return false;

	//m_pActivePolygon->UpdateBoundRect();
	
	if(m_pActivePolygon->HitTestLine(&m_ptGeo,  dTolerance, &ptFound )<0) return false; 
	
	return true;
}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
// Add Temp Node on Line
bool VECTOR_INFO::AddTempNodeOnLine()
{

	double dTolerance = m_rcGeo.Width()*2 /3;
	int numSection=0;
	int numPoint=0; 
	CIC_Point3DD ptFound;
	
	numPoint=m_pActivePolygon->HitTestLine(&m_ptGeo,  dTolerance, &ptFound );
	if(numPoint < 0) return false;
		
	m_tempNodeNumber=numPoint+1;
	
	IC_POINT3DD pt1,pt2;

	GetNodeByNumber((m_tempNodeNumber-1)%GetNodesCount(), pt1);	
	GetNodeByNumber((m_tempNodeNumber+1)%GetNodesCount(), pt2);
			
	m_ptGeo.z = pt1.z + (distanceBetweenNodes(m_ptGeo,pt2)/distanceBetweenNodes(pt2,pt1))*(pt2.z-pt1.z);	

	m_pActivePolygon->InsertPoints(&m_ptGeo,1,m_tempNodeNumber);

	pt1 = m_pActivePolygon->GetData()[m_tempNodeNumber];
	
	SetNodesCount(m_pActivePolygon->GetSize());

	return true;

}

////////////////////////////////////////////////////////////////////////
void VECTOR_INFO::MoveSelectedNodesOn(CIC_Point3DD dpt) // offset
{

	CIC_Point3DD pt;
	int index=0;
	
	// change selected points
	if(!m_pSelNodes) return;
	
	for(DWORD i=0;i<m_pSelNodes->GetSize();i++)// if(m_pSelNodes->GetSize()>0)		
	{
		pt=m_pSelNodes->GetData()[i];
		pt.x+=dpt.x;
		pt.y+=dpt.y;
		pt.z+=dpt.z;
		m_pSelNodes->GetData()[i]=pt;
	}
	
	UpdateSelectedNodes();
	// change active objects
	

	// search for positions to change
	int count=GetSelectedNodesCount();
		
	for(int i=0;i<count;i++)
	{
		index=GetSelectedNodeIndex(i);
		if(index==-1) break;

		CIC_PolygonD *pPolygon;
		int size=0;
		int nPoints=0;// delete!!!

		pPolygon = m_pActivePolygon;//pVectorObject->GetObjPolygon()->GetRegion()->GetPolygon(i);

		size=pPolygon->GetSize();

		pt=m_pActivePolygon->GetData()[index-nPoints];
		pt.x+=dpt.x;
		pt.y+=dpt.y;
		pt.z+=dpt.z;
		m_pActivePolygon->GetData()[index-nPoints]=pt;
				
	}

	OverdrawUpdate();
	
}
/////////////////////////////////////////////////////////////////////////
void VECTOR_INFO::RotateAndInflateNodesOn(CIC_Point3DD dpt) // offset
{
	if(m_ptPrev.x == m_ptGeo.x && m_ptPrev.y == m_ptGeo.y) return;
	
	
	double Angle, Gamma;
	double     dx, dy, Radius;
	CIC_Point3DD   *pptSrc;
	int   numPoints;
	CIC_Rect3DD  rcBound;
	double  PI = 3.14159265358979323846;
	double scale =1.0;
	
	//pptSrc = (CIC_Point3DD *)m_pActivePolygon->GetData();
	//numPoints = m_pActivePolygon->GetSize();

	pptSrc = (CIC_Point3DD *)m_pSelNodes->GetData();
	numPoints = GetSelectedNodesCount();

	IC_POINT3DD Center=m_ptCenter;//ActivePolygon->GetCenterPolygon();

	////////////////////////////////////
	dx = m_ptPrev.x - Center.x;
	dy = m_ptPrev.y - Center.y;
	double Radius1 = sqrt( dx*dx + dy*dy );
	double Gamma1;

	double beta = acos(abs(dx) / Radius1);
	if (dx > 0)
		if (dy < 0)    	Gamma1 = PI*1.5 + beta;
		else    		Gamma1 = PI*1.5 - beta;    
	else
		if (dy < 0)    	Gamma1 = PI*0.5 - beta;
		else    		Gamma1 = PI*0.5 + beta;

	dx = m_ptGeo.x - Center.x;
	dy = m_ptGeo.y - Center.y;
	double Radius2 = sqrt( dx*dx + dy*dy );
	double Gamma2;

	beta = acos(abs(dx) / Radius2);
	if (dx > 0)
		if (dy < 0)    	Gamma2 = PI*1.5 + beta;
		else    		Gamma2 = PI*1.5 - beta;    
	else
		if (dy < 0)    	Gamma2 = PI*0.5 - beta;
		else    		Gamma2 = PI*0.5 + beta;

	Angle =  Gamma1 - Gamma2;
	scale = Radius2/Radius1; 
		
	int n;

	for ( int i = 0; i < numPoints; i++ )
	{
		dx = pptSrc[i].x - Center.x;
		dy = pptSrc[i].y - Center.y;
		Radius = sqrt( dx*dx + dy*dy );

		if ( dx == 0.0 )			
		{
			Gamma = PI / 2;
			if(dy < 0) 		Gamma*=-1.0;
		}
		else
			Gamma = atan( dy/dx );

		if ( pptSrc[i].x < Center.x )			
			Gamma += PI;
			
		Gamma = Gamma + Angle;

		n = this->GetSelectedNodeIndex(i);

		m_pActivePolygon->GetData()[ n ].x = Center.x + scale*Radius*cos( Gamma );
		m_pActivePolygon->GetData()[ n ].y = Center.y + scale*Radius*sin( Gamma );
	}		

	// change selected points
	
	CIC_Point3DD pt;

	int index=0;
	if(!m_pSelNodes) return;
	
	for(DWORD i=0;i<m_pSelNodes->GetSize();i++)// if(m_pSelNodes->GetSize()>0)		
	{
		this->GetNodeByNumber(this->GetSelectedNodeIndex(i),pt);
		m_pSelNodes->GetData()[i]=pt;
	}
	
	UpdateSelectedNodes();


	OverdrawUpdate();
	
}

///////////////////////////////////////////////////////
// mode - by context menu
// newPoint - point or offset
void VECTOR_INFO::ModifyNodes(int mode, IC_POINT3DD newPoint) 
{
	// make changes

	int nPoint=0;
	int selCount=GetSelectedNodesCount();

	CIC_PolygonD *pPolygon;
	
	pPolygon=m_pActivePolygon;

	if(nPoint == -1) return;

	switch(mode)
	{
		case IDS_VINFO_XYZ_ADD :
		{
			if(!m_canAddDelete) return;

			
			DWORD n=GetSelectedNodeIndex(0);				
			

			if((n+1)>=pPolygon->GetSize())
				pPolygon->AddPoints(&newPoint,1);
			else
				pPolygon->InsertPoints(&newPoint,1,n+1);
						
		}
		break;

		case IDS_VINFO_XYZ_DEL :
		{
			if(!m_canAddDelete) return;

			if((GetNodesCount() - this->GetSelectedNodesCount()) <3) return;

			int del=0;
			for(int i=0;i<selCount;i++)
			{
				pPolygon->DeleteAt(GetSelectedNodeIndex(i)-del);	
				del++;				
			}		
			ClearSelectedNodes();

		}
		break;

		case IDS_VINFO_XYZ_EDIT :
		{
			
			for(int i=0;i<selCount;i++)
			{
				pPolygon->GetData()[GetSelectedNodeIndex(i)]=newPoint;
			}
		}
		break;
			
		case IDS_VINFO_XYZ_EDITX :
		{
			for(int i=0;i<selCount;i++)
			{
				pPolygon->GetData()[GetSelectedNodeIndex(i)].x=newPoint.x;				
			}			
		}
		break;

		case IDS_VINFO_XYZ_EDITY :
		{
			for(int i=0;i<selCount;i++)
			{
				pPolygon->GetData()[GetSelectedNodeIndex(i)].y=newPoint.y;				
			}
		}
		break;

		case IDS_VINFO_XYZ_EDITZ :
		{
			for(int i=0;i<selCount;i++)
			{
				pPolygon->GetData()[GetSelectedNodeIndex(i)].z=newPoint.z;				
			}
		}
		break;

		case IDS_VINFO_XYZ_MOVE :
		{
			for(int i=0;i<selCount;i++)
			{
				pPolygon->GetData()[GetSelectedNodeIndex(i)].x+=newPoint.x;	
				pPolygon->GetData()[GetSelectedNodeIndex(i)].y+=newPoint.y;	
				pPolygon->GetData()[GetSelectedNodeIndex(i)].z+=newPoint.z;		
			}
		}
		break;	

		case IDS_VINFO_XYZ_INTERPOL_STEPPED :
		case IDS_VINFO_XYZ_INTERPOL_GRADUAL :
		case IDS_VINFO_XYZ_INTERPOL_LINESMOUTH :
			Interpolation(pPolygon,newPoint.y-1,newPoint.z-1,mode);
		break;	
	}

	SetNodesCount(m_pActivePolygon->GetSize());

	UpdateSelectedNodes();

	DrawSelectedNodes();

	StoreActiveObject(mode);

	return;
}
//////////////////////////////////////////////////////////////////////////

void VECTOR_INFO::Interpolation(CIC_PolygonD *pPolygon,__int64 index0,__int64 indexN, int mode)
{
	double z0; 
	double zN; 
	double z1;
	double dz;
	int count;
	__int64 size;
			
	size = pPolygon->GetSize();
	z0 = pPolygon->GetData()[index0].z;
	zN = pPolygon->GetData()[indexN].z;
	count=((size + indexN-index0)%size)+1;
	dz = (zN-z0)/(count-1);

	auto integrate = [&](__int64 i0,__int64 iN)
	{
		if(i0==iN)  return;
		double dx = (pPolygon->GetData()[iN].z-pPolygon->GetData()[i0].z)/(iN-i0);
		int c=((size + iN-i0)%size)+1;

		for(int i=(i0+1)%size ; i!=iN;i++)
			pPolygon->GetData()[i%size].z=pPolygon->GetData()[(i-1)%size].z+dx;
	};
			
	switch(mode)
	{
		case IDS_VINFO_XYZ_INTERPOL_STEPPED : // line
		{
			for(int i=1;i<(count-1);i++)			
				pPolygon->GetData()[(index0+i)%size].z=z0 + i*dz;			
		}
		break;	
		
		case IDS_VINFO_XYZ_INTERPOL_GRADUAL :
		{
			// calc horizontal length			
			double hlen=0;
			double dx,dy,dlen;
			__int64 index1,index2;
			for(__int64 i=1;i<count;i++)
			{
				index1 = (index0+i)%size;
				index2 = ((index0-1)+i)%size;
				pPolygon->GetData()[index1].z=dlen=distanceBetweenNodes(pPolygon->GetData()[index1],pPolygon->GetData()[index2]); //sqrt(dx*dx+dy*dy); 			
				hlen+=dlen;
			}
			// calc tg
			double tg=hlen/(zN - z0);
			// calc z
			for(int i=1;i<(count-1);i++)
			{			
				index1 = (index0+i)%size;
				z0=z0+pPolygon->GetData()[index1].z/tg;
				pPolygon->GetData()[index1].z=z0;
			}
			pPolygon->GetData()[(index0+(count-1))%size].z=zN;
		}
		break;	

		case IDS_VINFO_XYZ_INTERPOL_LINESMOUTH :
		{			
			// calc gradient
			int nCur,nPrev,nNext;

			if(zN > z0)
			{
				for (int i=1;i<count;i++)
				{
					nCur=	(index0+i)%size;
					nPrev = (index0+i-1)%size;

				//	z0 = pPolygon->GetData()[nCur].z;
				//	z1 = pPolygon->GetData()[nPrev].z;

					if(pPolygon->GetData()[nCur].z < pPolygon->GetData()[nPrev].z )
					{
						for(int n=nPrev;;n--)
						{
							nPrev=n%size;											

						////	z0 = pPolygon->GetData()[nCur].z;
						////	z1 = pPolygon->GetData()[nPrev].z;

							if(pPolygon->GetData()[nPrev].z <= pPolygon->GetData()[nCur].z )
							{
								integrate(nPrev,nCur);
								break;
							}
							if(nPrev == index0) break;
						}
					}
				}
			}
			else
			{
				for (int i=1;i<count;i++)
				{
					nCur=	(index0+i)%size;
					nPrev = (index0+i-1)%size;	

					if(pPolygon->GetData()[nCur].z > pPolygon->GetData()[nPrev].z )
					{
						for(int n=(nCur+1);;n++)
						{
							nNext=n%size;
							
							if(pPolygon->GetData()[nNext].z < pPolygon->GetData()[nPrev].z )
							{
								integrate(nPrev,nNext);
								break;
							}
							if(nNext == indexN) break;
						}
					}
				}
			}					
		}
		break;	
	}


		/*
		case IDS_VINFO_XYZ_INTERPOL_STEPPED :
		{			
			double z0; 
			double zN; 
			double dz;
			__int64 index0,indexN;
			int count;

			index0 = GetSelectedNodeIndex(0);
			indexN = GetSelectedNodeIndex(1);
			z0 = pPolygon->GetData()[index0].z;
			zN = pPolygon->GetData()[indexN].z;
			count = (indexN-index0)+1;
			dz = (zN-z0)/(count-1);
			
			for(int i=1;i<(count-1);i++)			
				pPolygon->GetData()[index0+i].z=z0 + i*dz;			
		}
		break;	
		
		case IDS_VINFO_XYZ_INTERPOL_GRADUAL :
		{
			// calc horizontal length
			double z0; 
			double zN; 
			__int64 index0,indexN;
			int count;

			index0 = GetSelectedNodeIndex(0);
			indexN = GetSelectedNodeIndex(1);
			z0 = pPolygon->GetData()[index0].z;
			zN = pPolygon->GetData()[indexN].z;
			count = (indexN-index0)+1;

			double hlen=0;
			double dx,dy,dlen;
			for(int i=1;i<count;i++)
			{
				dx=pPolygon->GetData()[index0+i].x-pPolygon->GetData()[(index0+i)-1].x;
				dy=pPolygon->GetData()[index0+i].y-pPolygon->GetData()[(index0+i)-1].y;
				pPolygon->GetData()[index0+i].z=dlen=sqrt(dx*dx+dy*dy); // temporary				
				hlen+=dlen;
			}
			// calc tg
			double tg=hlen/(zN - z0);
			// calc z
			for(int i=1;i<(count-1);i++)
			{				
				z0=z0+pPolygon->GetData()[index0+i].z/tg;
				pPolygon->GetData()[index0+i].z=z0;
			}
			pPolygon->GetData()[index0+(count-1)].z=zN;
		}
		break;	
		*/
		/* among selected
		case IDS_VINFO_XYZ_INTERPOL:
		{
			// calc horizontal length
			double hlen=0;
			double dx,dy,dlen,z0;
			for(int i=1;i<selCount;i++)
			{
				dx=pPolygon->GetData()[GetSelectedNodeIndex(i)].x-pPolygon->GetData()[GetSelectedNodeIndex(i-1)].x;
				dy=pPolygon->GetData()[GetSelectedNodeIndex(i)].y-pPolygon->GetData()[GetSelectedNodeIndex(i-1)].y;
				pPolygon->GetData()[GetSelectedNodeIndex(i)].z=dlen=sqrt(dx*dx+dy*dy); // temporary				
				hlen+=dlen;
			}
			// calc tg
			double tg=hlen/(newPoint.z - newPoint.y);
			// calc z
			//pPolygon->GetData()[GetSelectedNodeIndex(0)].z=newPoint.y;
			z0=newPoint.y;
			for(int i=1;i<(selCount-1);i++)
			{				
				z0=z0+pPolygon->GetData()[GetSelectedNodeIndex(i)].z/tg;
				pPolygon->GetData()[GetSelectedNodeIndex(i)].z=z0;
			}
			//pPolygon->GetData()[GetSelectedNodeIndex(selCount-1)].z=newPoint.z;
		}
		*/

}

///////////////////////////////////////////////////////////////////////////
void VECTOR_INFO::StoreActiveObject(int mode)
{
	int lockRead = false;

	if(m_pDocument->IsLockDocument(MODE_ACCESS_READ))
	{
		m_pDocument->UnlockDocument(MODE_ACCESS_READ);

		lockRead = true;
	}	
	if(!m_pDocument->IsLockDocument(MODE_ACCESS_WRITE))
		
		if(!m_pDocument->LockDocument(MODE_ACCESS_WRITE)) return;
	
	Cdfi_VectorObject *pNewObject = NULL;
	Cdfi_VectorObject *pVectorObject;
	Cdfi_Layer* pLayer;
	int NumPoints=0;	
	
	CIC_Rect3DD newRect;
	newRect = m_pActivePolygon->GetBoundRect();

	Cdfi_View *pView = (Cdfi_View *)m_pDocument->GetActiveView( OBJECT_VIEW );	
	
	if ( m_LayerNum != -1 ) 
	{
		pLayer = m_pDocument->GetLayers()->GetLayer( m_LayerNum );

		if ( pLayer == m_pLayer )
		{

			if ( m_ObjectID != -1 )
			{	
									
				Cdfi_Vector *pVectorLayer = pLayer->GetVector(); // 

				Cdfi_VectorObjectStream voStream( pVectorLayer, VMEM_READWRITE);//WRITE ); 

				pVectorObject=voStream.GetVectorObject( m_ObjectID ); // source object

				if( !pVectorObject ) return;

				int type = pVectorObject->GetType();

 				switch( type )
				{
					case VE_NULL: return;

					case VE_TEXT: 
					{
						pNewObject = pVectorLayer->CreateObject(pVectorObject);//VE_TEXT);
			
						//pNewObject->GetObjText()->SetStyle(&m_textStyle);

						(( Cdfi_VectorText *)pNewObject)->SetTextPoint( m_pActivePolygon->GetData()[0]);
						(( Cdfi_VectorText *)pNewObject)->SetText(m_Text, m_Text.GetLength());

						pNewObject->GetBoundRect(&newRect);	
			
					} 
					break;
		
					case VE_POINT:
					{
						pNewObject = pVectorLayer->CreateObject(VE_POINT);
			
						pNewObject->GetObjPoint()->SetStyle(&m_pointStyle);
						//(( Cdfi_VectorPoint *)pNewObject)->
						int n=m_pActivePolygon->GetSize();
						(( Cdfi_VectorPoint *)pNewObject)->AddPoints(m_pActivePolygon->GetSize(), m_pActivePolygon->GetData());

						pNewObject->GetBoundRect(&newRect);				
			
					} 
					break;

					case VE_ELLIPSE: 
						if(m_pActivePolygon->GetSize()==2)
						{			
							pNewObject = pVectorLayer->CreateObject(pVectorObject);//VE_ELLIPSE);

							//(pNewObject->GetObjEllipse())->SetStyle(&m_ellipseStyle);
							
							CIC_Point3DD gp[2];			
							IC_RECT3DD r;
		
							gp[0].x=m_pActivePolygon->GetData()[0].x;
							gp[0].y=m_pActivePolygon->GetData()[0].y;
							gp[1].x=m_pActivePolygon->GetData()[1].x;
							gp[1].y=m_pActivePolygon->GetData()[1].y;
								
							r.left = gp[0].x;
							r.top =  gp[1].y;
							r.right = gp[0].x + 2*(gp[1].x-gp[0].x);
							r.bottom = gp[1].y - 2*(gp[1].y-gp[0].y);
							r.up=gp[0].z;
							r.down=gp[0].z;

							(( Cdfi_VectorEllipse *)pNewObject)->SetRect(&r);

							pNewObject->GetBoundRect(&newRect);
						}
					break;

					case VE_LINE: 
					{
						pNewObject = pVectorLayer->CreateObject(pVectorObject);

						int sectionCount=(( Cdfi_VectorLine *)pNewObject)->GetRegion()->GetPolygonsCount();
			
						if(sectionCount>m_sectionNum)
						{
							(( Cdfi_VectorLine *)pNewObject)->GetRegion()->GetPolygon(m_sectionNum)->RemoveAll();
							(( Cdfi_VectorLine *)pNewObject)->GetRegion()->GetPolygon(m_sectionNum)->AddPoints(m_pActivePolygon->GetData(),m_pActivePolygon->GetSize());	
							
							(( Cdfi_VectorLine *)pNewObject)->GetRegion()->DefineExternal(m_pDfi);
						}
						else
						{
							delete pNewObject;
							pNewObject = NULL;
						}
					}
					break;

					case VE_POLYGON: 
					{
						pNewObject = pVectorLayer->CreateObject(pVectorObject);
			
						//pNewObject->GetObjPolygon()->SetStyle(&m_polygonStyle);

						int sectionCount=(( Cdfi_VectorPolygon *)pNewObject)->GetRegion()->GetPolygonsCount();
			
						if(sectionCount>m_sectionNum)
						{
							(( Cdfi_VectorPolygon *)pNewObject)->GetRegion()->GetPolygon(m_sectionNum)->RemoveAll();
							(( Cdfi_VectorPolygon *)pNewObject)->GetRegion()->GetPolygon(m_sectionNum)->AddPoints(m_pActivePolygon->GetData(),m_pActivePolygon->GetSize());	

							(( Cdfi_VectorPolygon *)pNewObject)->GetRegion()->DefineExternal(m_pDfi);
						}
						else
						{
							delete pNewObject;
							pNewObject = NULL;
						}

					}
					break;
				}
				
				if(pNewObject) 
				{
				
					 ////  Set History	
					if ( pVectorObject )
					{	                  
						CString str=::GetResourceString(mode);			
						//str.LoadString( AfxGetStaticModuleState()->m_hCurrentResourceHandle, IDS_FUNCTION_DEL_NODE );	
						pView->GetDocument()->GetHistory()->AddItem( (LPTSTR)(LPCTSTR)str, HISTORY_ACTION_MODIFY, m_LayerNum, pVectorObject, TRUE, &m_ObjectID, AfxGetInstanceHandle(), mode );
					}				

					voStream.ReplaceObject(m_ObjectID, pNewObject);
				
					//// Set document modified flag
					pView->GetDocument()->SetModified();

					//Redraw

					CRect rClient;
					CRect rObject;
					CRect rInter;
															
					POSITION pos=m_pDocument->GetFirstViewPosition();

					while(pos)
					{
						pView = (Cdfi_View*)m_pDocument->GetNextView(pos);
						pView->GetClientRect(&rClient);
						// previous rect
						m_objBaseRect.NormalizeGeoRect();
						pView->GetCoordView()->GeoRectsToClient (&m_objBaseRect, &rObject, 1);
						if(rInter.IntersectRect(&rClient,&rObject)==false)
							rInter=rObject;
						pView->InvalidateView( &rInter , TRUE, m_LayerNum );											
						// new rect
						newRect.NormalizeGeoRect();
						pView->GetCoordView()->GeoRectsToClient (&newRect, &rObject, 1);
						if(rInter.IntersectRect(&rClient,&rObject)==false)
							rInter=rObject;
						pView->InvalidateView( &rInter , TRUE, m_LayerNum );
					}
					m_objBaseRect=newRect;

					UpdateObjectInSelectionList(m_LayerNum ,m_ObjectID,-1,m_objBaseRect);
						/// Delete Temp object
					pNewObject->DeleteObject();
					
				}
			}
		}
	}

	m_pDocument->UnlockDocument(MODE_ACCESS_WRITE);

	if(lockRead)
		if(!m_pDocument->LockDocument(MODE_ACCESS_READ)) return;
}
	
//////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
void VECTOR_INFO::ShowActiveObject()
{
	//AFX_MANAGE_STATE( AfxGetStaticModuleState() );
	
	Cdfi_Document* pDocument;
	Cdfi_VectorObject *pVectorObject;
	int NumPoints=0;
	Cdfi_HistoryItem *pHistItem = NULL;


	SetNodesCount(0);	
	
	pDocument = m_pDocument;
		
	if ( m_LayerNum != -1 )
	{
		if ( m_ObjectID != -1 )
		{					
			Cdfi_Vector *pVectorLayer = m_pLayer->GetVector();
						
			Cdfi_Layer *pLayer = pDocument->GetLayers()->GetLayer( m_LayerNum );

			if (!pLayer) return;

			pVectorLayer = pLayer->GetVector();

			int ColumnsNumber = pLayer->GetVector()->GetVectorTable()->GetVectorColumns()->GetSize();
			
			// attrib list
			SetAttrCount(ColumnsNumber);

			// Nodes list
			
			Cdfi_VectorObjectStream voStream( pVectorLayer, VMEM_READ ); 

			pVectorObject = voStream.GetVectorObject( m_ObjectID );
			
			pVectorObject->GetBoundRect(&m_objBaseRect);

			m_objType=pVectorObject->GetType();	
			
			if(m_pActivePolygon) 

				m_pActivePolygon->RemoveAll();

			else
			{
				m_pActivePolygon = new CIC_PolygonD();								

				m_pActivePolygon->SetExternal( TRUE );

				//pNewObject->GetObjPolygon()->AddPolygon( m_pPolygon );
				/*
				VECTOR_POLYGON_STYLE polygon_style;

				CIC_ManagerVectorStyle *ms=m_pDfi->GetApp()->GetStyleManager();

				polygon_style.ColorOutline = ms->GetCurrentPolygonOutlineColor();
				polygon_style.WidthOutline = ms->GetCurrentPolygonOutlinePixel();
				polygon_style.WidthGeoOutline= ms->GetCurrentPolygonOutlineWidth();
				polygon_style.Zooming = ms->GetCurrentPolygonZoom();

				CIC_StylePolygon *curStyle = ms->GetCurrentPolygonStyle();
				polygon_style.pStylePolygon = pVectorLayer->GetStyleSet()->AddStyle(curStyle)->GetPolygonObject();
				if (curStyle)
					curStyle->Release();
		
				m_pActivePolygon->SetStyle(&polygon_style);*/

			}

 			switch( m_objType )
			{
				case VE_NULL: 
				break;

				case VE_TEXT: 
				{
					m_canAddDelete=false;

					Cdfi_VectorText *pText=pVectorObject->GetObjText();

					pText->GetStyle(&m_textStyle);	

					m_Text=pText->GetText();

					//m_pRegion->SetPolygonsCount(1,true);

					m_pActivePolygon->AddPoints(&pText->GetTextPoint(),1);

					SetNodesCount(m_pActivePolygon->GetSize());
				}
				break;

				case VE_POINT: 
				{										
					m_canAddDelete=true;
										
					Cdfi_VectorPoint *pPoint=pVectorObject->GetObjPoint();

					pPoint->GetStyle(&m_pointStyle);						

					m_pActivePolygon->AddPoints(pPoint->GetData(),pPoint->GetNumPoints());

					SetNodesCount(m_pActivePolygon->GetSize());

					pVectorObject->GetObjPoint()->GetStyle(&m_pointStyle);
				}
				break;

				case VE_ELLIPSE: 					
				{
					m_canAddDelete=false;

					Cdfi_VectorEllipse *ve=pVectorObject->GetObjEllipse();
					IC_RECT3DD *r;
					IC_POINT3DD pt1;
					IC_POINT3DD pt2;
						
					CIC_PolygonD * pPolygon = NULL;
					CIC_RegionCmx * pRegion = NULL;
												
					pVectorObject->GetObjEllipse()->GetStyle(&m_ellipseStyle);
																
					r=ve->GetRect();

					pPolygon=m_pActivePolygon;

					pt2.x=(r->left + r->right)/2.0; // left point
					pt2.y=r->top;					
					pt2.z=(r->up);
					
					pt1.x=r->left; // left point
					pt1.y=(r->top + r->bottom)/2.0;
					pt1.z=r->down;
					/*
					double fi= atan(((r->top - r->bottom)/(1.0*(r->right - r->left))));

					pt2.x=pt0.x - (r->right - r->left)*cos(fi)/2.0;
					pt2.y=pt0.y - (r->top - r->bottom)*sin(fi)/2.0;
					pt2.z=r->down;
					*/
					pPolygon->AddPoints(&pt1,1);
					pPolygon->AddPoints(&pt2,1);


					SetNodesCount(2);
					
					//m_nodesList.SetItemCountEx(8);
				}
				break;

				case VE_LINE: 
				{										
					m_canAddDelete=true;
										
					Cdfi_VectorLine *pLine=pVectorObject->GetObjLine();

					pVectorObject->GetObjLine()->GetStyle(&m_lineStyle);

					m_pActivePolygon->AddPoints(pLine->GetRegion()->GetPolygon(m_sectionNum)->GetData(),pLine->GetRegion()->GetPolygon(m_sectionNum)->GetSize());
										
					m_objBaseRect = m_pActivePolygon->GetBoundRect();
					
					SetNodesCount(m_pActivePolygon->GetSize());
				}
				break;

				case VE_POLYGON: 
				{					
					m_canAddDelete=true;

					Cdfi_VectorPolygon *pPolygon=pVectorObject->GetObjPolygon();										
					
					pVectorObject->GetObjPolygon()->GetStyle(&m_polygonStyle);

					m_pActivePolygon->SetDirection(pVectorObject->GetObjPolygon()->GetRegion()->GetPolygon(m_sectionNum)->GetDirection(FALSE));
					m_pActivePolygon->SetDecrease(pVectorObject->GetObjPolygon()->GetRegion()->GetPolygon(m_sectionNum)->GetDecrease());
					m_pActivePolygon->SetExternal(pVectorObject->GetObjPolygon()->GetRegion()->GetPolygon(m_sectionNum)->GetExternal());

					m_pActivePolygon->AddPoints(pPolygon->GetRegion()->GetPolygon(m_sectionNum)->GetData(),pPolygon->GetRegion()->GetPolygon(m_sectionNum)->GetSize());

					m_objBaseRect = m_pActivePolygon->GetBoundRect();

					SetNodesCount(m_pActivePolygon->GetSize());
				}
				

				break;

			}
			voStream.Stop();
		}
		
	}
	else
	{
		if(m_pActivePolygon) 
			delete m_pActivePolygon;
		m_pActivePolygon = NULL;

		m_objType = VE_NULL;

		if(m_pSelNodes)
			m_pSelNodes->RemoveAll();

		SetAttrCount(0);
	}	
	
	OverdrawUpdate();
		 

}
////////////////////////////////////////////
///////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////

int VECTOR_INFO::RunContextMenu()
{
// load menu
	
	if(GetNodesCount()<1) return 0;
	//if(m_nodesList.GetItemCount()<1) return 0;
		
	AFX_MANAGE_STATE(m_pDfi->GetMainFrame()->GetModuleState());
	
	CMenu Menu;
	CMenu MenuSet;
	CMenu MenuInter;
	CMenu MenuFile;
	CString str;

	int selCount=GetSelectedNodesCount();//m_nodesList.GetSelectedCount();
	
	Menu.CreatePopupMenu();

	if(m_canAddDelete)
	{
		Menu.AppendMenu(MF_STRING|MF_ENABLED, IDS_VINFO_XYZ_ADD, GetResourceString(IDS_VINFO_XYZ_ADD));
	}

	if(selCount>0 && m_canAddDelete==true)
	{
		if((GetNodesCount() - GetSelectedNodesCount()) >2) 

			Menu.AppendMenu(MF_STRING|(selCount>0?MF_ENABLED:MF_DISABLED), IDS_VINFO_XYZ_DEL, GetResourceString(IDS_VINFO_XYZ_DEL));
	}

	if(selCount>0)
	{
		Menu.AppendMenu(MF_STRING|MF_DISABLED, IDS_VINFO_XYZ_MOVE, GetResourceString(IDS_VINFO_XYZ_MOVE));
	}

	if(selCount==1)
	{
		Menu.AppendMenu(MF_STRING|(selCount==1?MF_ENABLED:MF_DISABLED), IDS_VINFO_XYZ_EDIT, GetResourceString(IDS_VINFO_XYZ_EDIT));
	}
	else
	if(selCount>1)
	{		
		MenuSet.CreatePopupMenu();
		MenuSet.AppendMenu(MF_STRING|MF_ENABLED, IDS_VINFO_XYZ_EDITX, GetResourceString(IDS_VINFO_XYZ_EDITX));		
		MenuSet.AppendMenu(MF_STRING|MF_ENABLED, IDS_VINFO_XYZ_EDITY, GetResourceString(IDS_VINFO_XYZ_EDITY));		
		MenuSet.AppendMenu(MF_STRING|MF_ENABLED, IDS_VINFO_XYZ_EDITZ, GetResourceString(IDS_VINFO_XYZ_EDITZ));		
		Menu.AppendMenu(MF_STRING|MF_ENABLED|MF_POPUP, (UINT_PTR)MenuSet.m_hMenu, GetResourceString(IDS_VINFO_XYZ_EDIT));		
	}

	if(selCount == 2)
	{
		
		MenuInter.CreatePopupMenu();		
		MenuInter.AppendMenu(MF_STRING|MF_ENABLED, IDS_VINFO_XYZ_INTERPOL_STEPPED, GetResourceString(IDS_VINFO_XYZ_INTERPOL_STEPPED));		
		MenuInter.AppendMenu(MF_STRING|MF_ENABLED, IDS_VINFO_XYZ_INTERPOL_GRADUAL, GetResourceString(IDS_VINFO_XYZ_INTERPOL_GRADUAL));		
		MenuInter.AppendMenu(MF_STRING|MF_ENABLED, IDS_VINFO_XYZ_INTERPOL_LINESMOUTH, GetResourceString(IDS_VINFO_XYZ_INTERPOL_LINESMOUTH));

		Menu.AppendMenu(MF_STRING|MF_ENABLED|MF_POPUP, (UINT_PTR)MenuInter.m_hMenu, GetResourceString(IDS_VINFO_XYZ_INTERPOL));		
	}

	if(selCount != GetNodesCount())
	{
		Menu.AppendMenu(MF_STRING|MF_ENABLED, IDS_VINFO_XYZ_SELECT_ALL, GetResourceString(IDS_VINFO_XYZ_SELECT_ALL));
	}

	// adding files opearations
	/*
	Menu.AppendMenu(MF_SEPARATOR | MF_ENABLED, 20000, _T("Save in CSV"));		
	MenuFile.CreatePopupMenu();

	if (selCount > 0)
	{
		MenuFile.AppendMenu(MF_STRING | MF_ENABLED, 20001, _T("Save in CSV"));
		MenuFile.AppendMenu(MF_STRING | MF_ENABLED, 20002, _T("Save as text"));
	}
	Menu.AppendMenu(MF_STRING | MF_ENABLED | MF_POPUP, (UINT_PTR)MenuFile.m_hMenu, _T("File operations"));
	*/
	
		
	// end of adding
	if(Menu.GetMenuItemCount()==0) return 0;

	// call popupMenu
	CPoint point;
	GetCursorPos(&point);
	
	UINT nID = ((CWinAppEx *)m_pDfi->GetApp())->GetContextMenuManager()->TrackPopupMenu( Menu.m_hMenu, point.x, point.y, (CWnd*)m_pDfi->GetMainFrame());
	return nID;
	
	
}

///////////////////////////////////////////////////////////////////////////////////////////////
void VECTOR_INFO::RunXYZDialog(int mode)
{
	if (mode == 20002)
	{
		AccessXYZFile(mode);

		return;
	}
	


	AFX_MANAGE_STATE( AfxGetStaticModuleState() );
	
	if(!m_pDocument) return;
		
	CXYZDialog dlg;

	dlg.m_pDfi = m_pDfi;
	
	IC_POINT3DD pt;

	int number1=0; // number of first selection point
	
	
	int count=GetSelectedNodesCount();//m_nodesList.GetSelectedCount();	

	if(count>0) number1=this->GetSelectedNodeIndex(0);// m_nodesList.GetNextSelectedItem(pos);

	GetNodeByNumber(number1, pt);

	if(mode == IDS_VINFO_XYZ_ADD) // for adding - calc next point
	{
		IC_POINT3DD pt1,pt2;
		if(GetNodeByNumber((number1+1)%GetNodesCount(), pt2))
		{	
			pt1 = pt;
			pt.x=(pt1.x+pt2.x)/2;
			pt.y=(pt1.y+pt2.y)/2;
			//pt.z=(pt.z+pt2.z)/2;
			pt.z = pt1.z + (distanceBetweenNodes(pt,pt2)/distanceBetweenNodes(pt1,pt2))*(pt2.z-pt1.z);
		}
	}	
	else
	if((mode == IDS_VINFO_XYZ_DEL) && (GetSelectedNodesCount()>1))
	{
		if (AfxMessageBox(GetResourceString(IDS_VINFO_XYZ_DELETING_PROMPT), MB_ICONQUESTION | MB_YESNO) == IDYES)
		{
			ModifyNodes(mode, pt);
			return;
		}
	}
	else	
	if((mode == IDS_VINFO_XYZ_INTERPOL_STEPPED) || (mode == IDS_VINFO_XYZ_INTERPOL_GRADUAL) || (mode == IDS_VINFO_XYZ_INTERPOL_LINESMOUTH)) // only by Z-koordinate
	{
		IC_POINT3DD pt2;
		if(GetNodeByNumber(GetSelectedNodeIndex(GetSelectedNodesCount()-1), pt2))
		{
			// pt.x - no use
			pt.y=GetSelectedNodeIndex(0)+1;//pt.z;
			pt.z=GetSelectedNodeIndex(1)+1;//pt2.z;				
		}
		else return;
	}
	dlg.m_count=this->GetSelectedNodesCount();
	dlg.m_point.x=pt.x;
	dlg.m_point.y=pt.y;
	dlg.m_point.z=pt.z;
	
	dlg.m_mode=mode;

	if(dlg.DoModal()!=IDOK) return;
			
	pt.x=dlg.m_point.x;
	pt.y=dlg.m_point.y;
	pt.z=dlg.m_point.z;
	
	ModifyNodes(mode, pt);
	
	
	m_pDocument->RedrawViews(TRUE,m_LayerNum);
		
	return;	
	
}


////////////////////////////////////////////////////////////////////////
void VECTOR_INFO::AccessXYZFile(int mode)
{
	CFileDialog fileDialog(FALSE, _T("txt"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Text Files (*.txt)|*.txt||"));
	int result = fileDialog.DoModal();	//запустить диалоговое окно
	if (result == IDOK)	//если файл выбран
	{
		FILE* f;
		errno_t err;
		CString str;

		str = fileDialog.GetPathName();

		err = _wfopen_s(&f, str, _T("wt"));
		if (err || !f)
		{
			AfxMessageBox(_T("Error opening file")); // показать полный путь
		}
		else
		{
			int count = GetSelectedNodesCount();

			for (int i = 0;i < count;i++)
			{
				IC_POINT3DD pt;
				if (GetNodeByIndex(GetSelectedNodeIndex(i), pt))
				{
					str.Format(_T("%lf %lf %lf\n"),pt.x,pt.y,pt.z);
					fputws(str, f);
				}
			}
			AfxMessageBox(fileDialog.GetPathName()); // показать полный путь
		}


		fclose(f);
	}
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
/////////////          OVERDRAW       //////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////


BOOL OverdrawFunction( Cdfi_View *pView, Cdfi_MemoryDC *pMemDC, LPVOID pParam)
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );

	//VECTOR_INFO_DATA *pData=(VECTOR_INFO_DATA *)pParam;

	VECTOR_INFO *pDlg=(VECTOR_INFO *)pParam;// pData->pDialog;
	
	//CVectorInfoDialog *pDlg=pData->pDialog;

	if(!pDlg) return FALSE;

	if(pDlg->m_pActivePolygon==NULL) return TRUE;
	
	
	CRect rcUpdate;

	CDC *pDC = pMemDC->GetPtrDC();
				

	pDC->SetROP2( R2_COPYPEN );

	pDC->SetBkColor( RGB(1,1,1) );


//	COLORREF Color;

	HPEN hPen, hOldPen;

	pView->GetUpdateClientRect( &rcUpdate );

	/////
	//pDC->SetROP2( R2_COPYPEN );

	//pDC->SetBkColor( RGB(1,1,1) );
  
	hPen = ::CreatePen(0, 2, RGB( 200, 10, 10 ) );//PS_DOT

	hOldPen = (HPEN)::SelectObject( pDC->m_hDC, hPen);

	pDC->SetPolyFillMode(0);
	
	CBrush hBrush; 
	
	RECT r;

	//b.CreateStockObject(NULL_BRUSH);// .CreateHatchBrush(HS_DIAGCROSS) 
	hBrush.CreateSolidBrush(RGB( 255, 10, 10 ));

	DWORD iCountPoints;
	CIC_PolygonD *pPolygon;	
	CPoint *pPointsScreen = NULL;	

	if(pDlg->m_objType==VE_ELLIPSE)
	{
		CIC_Point3DD gp[2];
		CIC_Point3DD cp[2];
			
		pPolygon = pDlg->m_pActivePolygon;

		if(pPolygon->GetSize()==2)
		{
			gp[0].x=pPolygon->GetData()[0].x;
			gp[0].y=pPolygon->GetData()[0].y;

			gp[1].x=pPolygon->GetData()[1].x;
			gp[1].y=pPolygon->GetData()[1].y;

			pView->GetCoordView()->GeoPointsToClient((CIC_Point3DD *)&gp, (CIC_Point3DD *)&cp, 2);

			r.left = (int)ceil(cp[0].x);
			r.top = (int)ceil(cp[1].y);
			r.right = (int)ceil(cp[0].x + 2*(cp[1].x-cp[0].x));
			r.bottom = (int)ceil(cp[1].y - 2*(cp[1].y-cp[0].y));

			POINT p1;//,p2;
			p1.x = (int)ceil(cp[0].x);
			p1.y = (int)ceil(cp[0].y);
			//p2.x = cp[0].x;
			//p2.y = cp[0].y;
			//pDC->Ellipse(&r);

			pDC->MoveTo(p1);
			pDC->ArcTo(&r,p1,p1);
			
			CIC_Point3DD *pp=cp;
			
			for(DWORD i=0;i<2;i++,pp++)
			{	

				r.left=(int)pp->x-4;		r.right=(int)pp->x+4;		r.top=(int)pp->y-4;		r.bottom=(int)pp->y+4;		//pDC->Rectangle(&r);
				pDC->FrameRect(&r,&hBrush);
			}			
			
		}
				
	}

	else
	{
		//draw polygons and their points
		
		int section = 0;//pDlg->m_sectionNum;
		

		pPolygon=pDlg->m_pActivePolygon;

		ASSERT(pPolygon->GetSize() < INT_MAX);
		
		iCountPoints = pPolygon->GetSize();

		pPointsScreen = new CPoint[iCountPoints+1];

		pView->GetCoordView()->GeoPointsToClient( (CIC_Point3DD *)pPolygon->GetData(), pPointsScreen, iCountPoints );
		
		if(pDlg->m_objType==VE_LINE)
		{
			pDC->Polyline( pPointsScreen, iCountPoints );
		}
		else
		if(pDlg->m_objType==VE_POLYGON)
		{
			pPointsScreen[iCountPoints]=pPointsScreen[0];
					
			pDC->Polyline( pPointsScreen, iCountPoints+1 );//>Polyline
		}	
		
		CPoint *pp=pPointsScreen;

		/*
		inner lines
		CPoint pp0;

		pp0.x=pPointsScreen[iCountPoints-1].x;
		pp0.y=pPointsScreen[iCountPoints-1].y;
		
		double tg1=(pp0.x-pp->x)/(1.0*(0.00001,pp0.y-pp->y));
		double tg2;
		double an;

		pp0.x=pp->x;
		pp0.y=pp->y;

		for(DWORD i=0;i<(iCountPoints-1);i++,pp++)
		{
			tg2=(pp->x-(pp+1)->x)/(1.0*(0.00001,pp->y-(pp+1)->y));

			an=(atan(tg1)+atan(tg2))/2;

			tg1=tan(an);

			pp0.x=pp->x+(tg1)*8;
			pp0.y=pp->y+8/(tg1);

			pDC->MoveTo(pp->x,pp->y);
			pDC->LineTo(pp0.x+8,pp0.y+8);

			//pp0.x=pp->x;
			//pp0.x=pp->y;
			tg1=tg2;
		}
		*/
			
		for(DWORD i=0;i<iCountPoints;i++,pp++)
		{						
			r.left=pp->x-4;		r.right=pp->x+4;		r.top=pp->y-4;		r.bottom=pp->y+4;		//pDC->Rectangle(&r);
			pDC->FrameRect(&r,&hBrush);
		}
							
		delete [] pPointsScreen;	

		//if(hPenDefault)	   ::DeleteObject(hPenDefault);	
						
	}

	::DeleteObject(hPen);	

	::DeleteObject(hBrush);

	HPEN hPenSel;
	CBrush hBrushSel;
	
	//


			// selected points	
	if(pDlg->m_pSelNodes==NULL) return false;

	hPenSel = ::CreatePen(0, 1, RGB( 10, 250, 10 ) );//PS_DOT

	hOldPen = (HPEN)::SelectObject( pDC->m_hDC, hPenSel);

	hBrushSel.CreateSolidBrush(RGB( 250, 250, 10 ));		

	iCountPoints = pDlg->m_pSelNodes->GetSize();

	pPointsScreen = new CPoint[iCountPoints];

	pView->GetCoordView()->GeoPointsToClient( (CIC_Point3DD *)pDlg->m_pSelNodes->GetData(), pPointsScreen, iCountPoints );
			 
	// size screen points array   

	CPoint *pp=pPointsScreen;
	
	//pDC->SetBkMode(TRANSPARENT);
	
	for(DWORD i=0;i<(pDlg->m_pSelNodes->GetSize());i++,pp++)
	{
		//POINT p;		//pDC->SetPixel(p,Color);
		//pDC->Ellipse(pp->x-4,pp->y-4,pp->x+4,pp->y+4);		
		r.left=pp->x-5;		r.right=pp->x+5;		r.top=pp->y-5;		r.bottom=pp->y+5;		//pDC->Rectangle(&r);
		pDC->FrameRect(&r,&hBrushSel);
		r.left=pp->x-6;		r.right=pp->x+6;		r.top=pp->y-6;		r.bottom=pp->y+6;		//pDC->Rectangle(&r);
		pDC->FrameRect(&r,&hBrushSel);	
	}

	delete [] pPointsScreen;	
			
	::DeleteObject(hBrushSel); 

	::DeleteObject(hPenSel);	

	
	
	return TRUE;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void VECTOR_INFO::OverdrawDelete()
{
	//AFX_MANAGE_STATE( AfxGetStaticModuleState() );

// unregister overdrawfunc
	Cdfi_Document* pDocument;
	POSITION pos;
	CWnd* pWnd = NULL;

	if(!m_pDfi) return;
	
	pDocument = m_pDfi->GetApp()->GetFirstDocument();

	while (pDocument)
	{
		pos = pDocument->GetFirstViewPosition();

		while ( pWnd = pDocument->GetNextView(pos) )
		{
			Cdfi_View *pView = (Cdfi_View*)pWnd;

			if (!pView) break;
						
			int iPos = (int)(pView->GetOverDraw()->Find(OverdrawFunction));

				if (iPos != -1)
				{
					pView->GetOverDraw()->Remove(iPos);
					//if (bRedraw)
						pView->InvalidateView(NULL, TRUE, VIEW_UPDATE_OVERDRAW);
				}
		//	}
		}
		pDocument = m_pDfi->GetApp()->GetNextDocument(pDocument);
	}
		
}
//////////////////////////////////////////////////////////////////////

void VECTOR_INFO::OverdrawInit()
{
	OverdrawDelete();

	if(!m_pDocument) return;

	Cdfi_View *pView = (Cdfi_View *)m_pDocument->GetActiveView( OBJECT_VIEW );

	if(!pView) return;
	
	Cdfi_OverDraw *od =pView->GetOverDraw();
	
	od->Register( OverdrawFunction, this);//m_pData );	
	
	
}

//////////////////////////////////////////////////////////////
void VECTOR_INFO::OverdrawUpdate()
{
	if(!m_pDocument) return;

	//if(!m_lockUpdateOverdraw)
	if(!m_pDocument->IsLockDocument(MODE_ACCESS_READ))
	{		

		Cdfi_View *pView = (Cdfi_View *)m_pDocument->GetActiveView( OBJECT_VIEW );

		if(!pView) return;
				
		m_updateOverdraw=false;		
		
		pView->RedrawView( NULL, TRUE, VIEW_UPDATE_OVERDRAW );
		//pView->InvalidateView( NULL, TRUE, VIEW_UPDATE_OVERDRAW );

	}
	else		
		m_updateOverdraw=true;
	
}
//////////////////////////////////////////////////////////////

