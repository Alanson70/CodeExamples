#include "StdAfx.h"
#include "demcorrection.h"

#include "DEMDialog.h"
#include "ArgsDemcorrection.h"
#include "Macros\dfi_ManagerMacros.h"

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
bool UpdateDEMCorrection(CDFI* pDfi, CCmdUI * pExtra)
{
	return true;
}
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
bool DEMCorrection(CDFI* pDfi, IC_PARAM *pParam)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	DEM_DATA *pData = NULL;
	Cdfi_Document *pDoc = NULL;
	Cdfi_ManagerMacros* pManager;
	CArgsDemcorrection *pArgs;
	bool bRes = false;
	static BOOL bDoSerialize = FALSE;
	
	if (!pDfi)
		return false;

	if (!pParam)
		return false;
	
	if ( ( pParam->message != FM_DEFAULT )&&(pParam->message != FM_DESTROY_ALL)&&( pParam->message != FM_END_FUNCTION ) )
		return false;


	pData = GetDEMData( pDfi );

	if (!pData)
		return false;	

	if(pParam->message == FM_DESTROY_ALL)
			if ( pData->pDialog == NULL )
				return true;
	//get params
	if (pParam->pArguments)	
		pArgs = (CArgsDemcorrection *)pParam->pArguments;

	

	pManager = pDfi->GetApp()->GetManagerMacros();
	
	pDoc = pDfi->GetMainFrame()->GetActiveDocument();
	////////////////////////////////////////
	// exit handling
	if (pParam->message == FM_DESTROY_ALL)
		pData->pDialog->m_bExitFlag = true;

	if (pParam->message == FM_END_FUNCTION || pParam->message == FM_DESTROY_ALL)
	{
		if (pData->pDialog)
		{
			AFX_MANAGE_STATE(AfxGetStaticModuleState());

			if (pData->pDialog->m_bExitFlag)
			{
				CRect rcDialog;
				pData->pDialog->GetWindowRect(rcDialog);

				pData->pDialog->m_dialogLeft = rcDialog.left;
				pData->pDialog->m_dialogTop = rcDialog.top;

				if (pData->pDialog->GetSafeHwnd())
					pData->pDialog->DestroyWindow();

				delete pData->pDialog;

				pData->pDialog = NULL;

				return false;
			}
		}
	}

	// macros record
	if (!pArgs)
		return false;

	if (pParam->message == FM_END_FUNCTION)
	{
		if (pData->pDialog)
		{
			//сохранение при записи/воспроизведении
			if (pManager->IsRecording()
				|| (pManager->IsPaused() && pData->m_pCurrentItem && pData->m_pCurrentItem == pManager->GetCurrentMacrosItem()))
			{
				pArgs->SetSaveMacros(TRUE);
				if (pData->m_pCurrentItem)
				{
					//макрос поспроизведен успешно, сохранить изменения
					pData->m_pCurrentItem->SetArguments(pArgs);
					pDfi->GetApp()->SendMessageToFunctions(FM_MACROS_ITEM_PLAYED, (WPARAM)pManager->GetCurrentMacrosItem(), NULL, NULL);
					pManager->StopPlaying();//сбросить флаг паузы
				}
				if (pManager->IsRecording())
				{
					//сохранить аргументы с помощью рекурсивного вызова, затем перейти к очистке
					if (bDoSerialize)
					{
						bDoSerialize = FALSE;
						return true;//сериализация произойдет после выхода из метода
					}
					else
					{				

						bDoSerialize = TRUE;
						int id = pDfi->GetApp()->GetFncFunctions()->GetFuncIndex((void *)DEMCorrection);
						if (id > -1)
						{
							pDfi->GetApp()->GetFncFunctions()->DoFunction(id, pParam, FALSE);
						}
						//после сериализации возможен переход к освобождению ресурсов
					}
				}
			}

			IC_PARAM Param;

			if (pDoc)
			{
				memset(&Param, 0, sizeof(IC_PARAM));
				Param.message = FM_DEFAULT;
				Param.pArguments = pArgs;

				Rasterize(pDfi, &Param);
			}

		}
		return bRes;
	}
	
	// create dialog
	if (pParam->iInterface & FUNCTION_CALL_INTERFACE)
	{
		if (!pData->pDialog)		
		{
			CDEMDialog* pDialog = new CDEMDialog(pDfi);// (CWnd*)pDfi->GetMainFrame() );

			if (pData->rcLast.IsRectNull())
			{
				IC_RECT64 rcFrameWindow, rcFrameClient;
				CRect rcDialog;
				pDfi->GetMainFrame()->GetClientRect(&rcFrameClient);
				pDfi->GetMainFrame()->GetWindowRect(&rcFrameWindow);
				pDialog->GetWindowRect(rcDialog);				
									 
				if (pDialog->m_dialogLeft == 0 || pDialog->m_dialogTop == 0)
				{
					pDialog->m_dialogLeft = (int)rcFrameWindow.left + (int)rcFrameClient.right / 2 - RIGHT_OFFSET - rcDialog.Width();
					pDialog->m_dialogTop = (int)rcFrameWindow.top + (int)rcFrameClient.bottom * TOP_POSITION / 100;
				}
				else // for any case
				{
					pDialog->m_dialogLeft = min(pDialog->m_dialogLeft, (int)rcFrameWindow.left + (int)rcFrameClient.right - RIGHT_OFFSET - rcDialog.Width());
					pDialog->m_dialogTop = min(pDialog->m_dialogTop, (int)rcFrameWindow.top + (int)rcFrameClient.bottom * TOP_POSITION / 100);
				}
				pDialog->MoveWindow(pDialog->m_dialogLeft, pDialog->m_dialogTop,rcDialog.Width(), rcDialog.Height(), FALSE);
			}
			else
			{
				pDialog->MoveWindow(pData->rcLast, FALSE);
			}
			
			pData->pDialog = pDialog;
			pDialog->ShowWindow(SW_SHOW);

			
			if (pDoc)
			{
				pDialog->SetDocument(pDfi->GetMainFrame()->GetActiveDocument());

				if (pDoc->LockDocument(MODE_ACCESS_READ))
				{

					pDoc->UnlockDocument(MODE_ACCESS_READ);
				}
			}
			else
				;//pDialog->SetDocument( NULL );
		}
		else			// this old code not tested because it's never call
		{
			int id = pDfi->GetApp()->GetFncFunctions()->GetFunctionID(DEMCorrection);

			if (pParam->FunctionID == id) // what for???
			{
				if (pParam->message == FM_END_FUNCTION || pParam->message == FM_DESTROY_ALL || pParam->message == FM_DEFAULT)
				{
					CRect rcDialog;
					pData->pDialog->GetWindowRect(rcDialog);

					pData->pDialog->m_dialogLeft = rcDialog.left;
					pData->pDialog->m_dialogTop = rcDialog.top;

					if (pData->pDialog->GetSafeHwnd())
						pData->pDialog->DestroyWindow();

					delete pData->pDialog;

					pData->pDialog = NULL;
				}
				else
				if (pParam->message == FM_DEFAULT)
				{
					//pData->pDialog->SetDocument(NULL);
				}
			}
		}


		//Ставим на паузу и запоминаем указатель на операцию
		if (pData->pDialog && pArgs->IsCalledFromMacros() && pManager->IsPlaying())
		{
			pData->m_pCurrentItem = pManager->GetCurrentMacrosItem(); 
			pManager->PausePlaying();
			bRes = false;
		}

	}
	else
	if(pParam->iInterface & FUNCTION_CALL_DEFAULT) //macros mode without interface
	{
		IC_PARAM Param;

		if (pDoc)
		{						
			memset(&Param, 0, sizeof(IC_PARAM));
			Param.message = FM_DEFAULT;
			Param.pArguments = pArgs;

			pArgs->m_pDialog = NULL;

			Rasterize(pDfi, &Param);			
		}
	}
	else
	if (pParam->iInterface & FUNCTION_CALL_CUSTOM) // whoose theese boots?
	{
		IC_PARAM Param;
		CArgsDemcorrection Args;

		memset(&Param, 0, sizeof(IC_PARAM));
		Param.message = FM_DEFAULT;
		Param.pArguments = &Args;

		Args.m_pDialog = NULL;

		Rasterize(pDfi, &Param);
	}
	else
	{
		if (pData->pDialog)
		{
			CRect rcDialog;
			pData->pDialog->GetWindowRect(rcDialog);

			pData->pDialog->m_dialogLeft = rcDialog.left;
			pData->pDialog->m_dialogTop = rcDialog.top;

			if (pData->pDialog->GetSafeHwnd())
				pData->pDialog->DestroyWindow();

			delete pData->pDialog;

			pData->pDialog = NULL;
		}
	}
	// Запрещаем запись макроса
	if (pArgs)
		pArgs->SetSaveMacros(FALSE);
	
	
	return true;
}
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

DEM_DATA* GetDEMData( CDFI* pDfi )
{
IC_FUNCTION_IDENTIFY fi;
DEM_DATA* pData = NULL;
int ifindex;

	if ( pDfi )
		if( pDfi->GetMainFrame() )
		{				  
			ifindex = pDfi->GetApp()->GetFncFunctions()->GetFuncIndex( (void *)DEMCorrection );	 	                     
			if ( ifindex > -1 )	 
			{
				pDfi->GetApp()->GetFncFunctions()->GetFunctionInfo( ifindex, &fi );
				pData = (DEM_DATA*)fi.pProcInfo;
			}
		}
	
	return pData;
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

bool DEMCorrectionProc( CDFI * pDfi, IC_PARAM * pParam )
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );
	DEM_DATA *pData = NULL;
	CIC_Point64 ptClient;
	CIC_Point3DD ptGeo;
	CIC_Rect64 rcClient;
	CIC_Rect3DD rcGeo;

	if ( pParam->message == WM_KEYDOWN)//WM_USER_SELECT_OBJ)
	{
		pData=NULL;
	}


	if( !pDfi )
		return false;

	pData = GetDEMData( pDfi );

	if ( !pData->pDialog )
		return false;
	
	if(pParam->message >= 2000000)
	{
		if(pParam->message != FM_VIEW_ACTIVATE && pParam->message != FM_VIEW_DEACTIVATE)
		{
			int p=0;//temp
		}
	}
	
	return pData->pDialog->WndProc(pParam->message,pParam);
}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

void EndFunction(CDFI *pDfi) 
{
int ifindex;
IC_PARAM param;
          
	memset( &param, 0, sizeof(IC_PARAM) );
	param.message = FM_END_FUNCTION;

	if( pDfi->GetMainFrame() )
	{				  
		ifindex = pDfi->GetApp()->GetFncFunctions()->GetFuncIndex( (void *)DEMCorrection );

		if ( ifindex>-1 )	 
			pDfi->GetApp()->GetFncFunctions()->DoFunction( ifindex, &param, FALSE );
	}
}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////