#include "stdafx.h"
#include "fn_demcorrection.h"
#include "DEMDialog.h"
#include "afxdialogex.h"
#include "dfi_RasterStream.h"
#include "dfi_RasterPROCS.h"
#include "dfi_selection.h"
#include "dfi_selectionItem.h"
#include "IC_SelectionInfo.h"

#include "math.h"
#include "DEM.h"
/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////

#include "math.h"
#include "MathSpace\\IC_Buffer.h"

#include "ANN.h"
#include "Arguments\fn_stitching\ICarg_Stitching.h"
#include "Arguments\fnc_CopyImage\ICarg_CopyRaster.h"

//////////////////////////////////////////////////////////////////////////////////////////////

CDEM::CDEM(CDFI *pDfi) : CDEM_ARGS()
{	
	m_pDfi = pDfi;

	m_pDocument = NULL;


	// attr
	m_rasterCut = 0;
	m_rasterCopy = 0;
	m_objectsSource = 1;
	m_levelSource = 0;
	m_levelAttr[0] = 0;// = _T("");
	m_levelEditValue[0] = 0;// = _T("0");
	//m_level = 0;
	m_reference = 0;
	m_zone = FALSE;
	m_zoneGradient = 0;
	m_zoneRounding = FALSE;
	m_zoneWidthGeo = 0;
	m_zoneWidthSource = 0;
	m_zoneWidthAttr[0] = 0;// = _T("");
	m_zoneWidthEditValue[0] = 0;// = _T("0");
	m_zoneFactor = 0;
	m_uom = 0;
	m_relief = FALSE;
	m_optionZoneOnly = 0;

	//////////////
	m_pixelOffsetX = 0;
	m_pixelOffsetY = 0;

	m_dialogLeft = 0;
	m_dialogTop = 0;

	m_externInterpolation = FALSE;

	//m_undoEnable = FALSE;
	//m_canUndo = FALSE;
	//m_pSavedRaster = NULL;
	//m_pUndoRaster = NULL;
	
	AccessAttributes(false);	
	
	m_rasterUpdateLock = false;
	m_rasterUpdate = false;

	// debug
	m_oneColor = FALSE;
	
	m_drawType = 0;
	m_triangleDrawType = 2;
	m_drawScelet = FALSE;	

	m_iterateDraw = false;
	m_iterateCount = 0;	

}

///////////////////////////////
CDEM::~CDEM()
{
	AccessAttributes(true);
	
	//if (m_pSavedRaster)

	//	::DeleteObject(m_pSavedRaster);


}

///////////////////////////////
void DEM_ARGS_COPY(CDEM_ARGS *dst, CDEM_ARGS *src)
{
	memcpy(dst, src, sizeof(CDEM_ARGS));//
	//dst->m_level = src->m_level;
	/*
	wcsncpy(dst->m_levelAttr, src->m_levelAttr, 50);
	wcsncpy(dst->m_levelEditValue, src->m_levelEditValue, 50);
	dst->m_levelSource = src->m_levelSource;
	dst->m_objectsSource = src->m_objectsSource;
	dst->m_optionZoneOnly = src->m_optionZoneOnly;
	dst->m_rasterCopy = src->m_rasterCopy;
	dst->m_rasterCut = src->m_rasterCut;
	dst->m_reference = src->m_reference;
	dst->m_relief = src->m_relief;
	dst->m_uom = src->m_uom;
	dst->m_zone = src->m_zone;
	dst->m_zoneFactor = src->m_zoneFactor;
	dst->m_zoneGradient = src->m_zoneGradient;
	dst->m_zoneRounding = src->m_zoneRounding;
	wcsncpy(dst->m_zoneWidthAttr, src->m_zoneWidthAttr, 50);
	wcsncpy(dst->m_zoneWidthEditValue, src->m_zoneWidthEditValue, 50);
	dst->m_zoneWidthSource = src->m_zoneWidthSource;
	*/
}
///////////////////////////////

void  CDEM::AccessAttributes(bool bWrite)
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );

	Cdfi_Attributes *pAttributes;

	pAttributes = m_pDfi->GetApp()->GetAttributes();


	CString  sSection=_T("");
	
	sSection.LoadString( IDS_MENU_DEMCORRECTION );	
	Attr(m_dialogLeft, GetResourceString(IDS_DEM_ATTR_DIALOG_LEFT),sSection,pAttributes,bWrite);
	Attr(m_dialogTop, GetResourceString(IDS_DEM_ATTR_DIALOG_TOP),sSection,pAttributes,bWrite);
	//Attr(m_undoEnable, GetResourceString(IDS_DEM_ATTR_UNDO_ENABLE), sSection, pAttributes, bWrite);


	
	Attr(m_rasterCut,GetResourceString(IDS_DEM_ATTR_RASTER_CUT),sSection,pAttributes,bWrite,TRUE);
	Attr(m_rasterCopy, GetResourceString(IDS_DEM_ATTR_RASTER_COPY), sSection,pAttributes,bWrite,TRUE);
	Attr(m_objectsSource, GetResourceString(IDS_DEM_ATTR_OBJECT_SOURCE), sSection,pAttributes,bWrite,TRUE);
	Attr(m_levelSource, GetResourceString(IDS_DEM_ATTR_LEVEL_SOURCE), sSection,pAttributes,bWrite,TRUE);
	Attr(m_levelAttr, GetResourceString(IDS_DEM_ATTR_LEVEL_ATTR), sSection,pAttributes,50,bWrite,TRUE);
	Attr(m_levelEditValue, GetResourceString(IDS_DEM_ATTR_LEVEL_EDIT), sSection,pAttributes,50,bWrite,TRUE);
	Attr(m_reference, GetResourceString(IDS_DEM_ATTR_REFERENCE), sSection,pAttributes,bWrite,TRUE);
	Attr(m_zone, GetResourceString(IDS_DEM_ATTR_ZONE), sSection,pAttributes,bWrite,TRUE);
	Attr(m_zoneFactor, GetResourceString(IDS_DEM_ATTR_ZONE_FACTOR),  sSection, pAttributes, bWrite,TRUE);
	Attr(m_optionZoneOnly, GetResourceString(IDS_DEM_ATTR_ZONE_ONLY), sSection, pAttributes, bWrite,TRUE);
	Attr(m_zoneRounding, GetResourceString(IDS_DEM_ATTR_ROUNDING), sSection,pAttributes,bWrite,TRUE);
	Attr(m_zoneGradient, GetResourceString(IDS_DEM_ATTR_GRADIENT), sSection,pAttributes,bWrite,TRUE);
	Attr(m_zoneWidthAttr, GetResourceString(IDS_DEM_ATTR_WIDTH_ATTR), sSection,pAttributes,50,bWrite,TRUE);
	Attr(m_zoneWidthEditValue, GetResourceString(IDS_DEM_ATTR_WIDTH_EDIT), sSection,pAttributes,50,bWrite,TRUE);
	Attr(m_zoneWidthSource, GetResourceString(IDS_DEM_ATTR_WIDTH_SOURCE), sSection,pAttributes,bWrite,TRUE);
	Attr(m_uom, GetResourceString(IDS_DEM_ATTR_UOM), sSection, pAttributes,bWrite,TRUE);
	Attr(m_relief, GetResourceString(IDS_DEM_ATTR_RELIEF), sSection,pAttributes,bWrite,TRUE);

	
		
}

///////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

bool CDEM::SetDocument( Cdfi_Document* pDocument )
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );

	if ( m_pDocument != pDocument )
	{		

		if(m_pDocument)
		{				
			//if (m_pDocument->IsLockDocument(MODE_ACCESS_WRITE)) return false;
			
			if (!m_pDocument->LockDocument(MODE_ACCESS_READ)) return false;

								
			m_pDocument->UnlockDocument(MODE_ACCESS_READ);

			
			OnChangeLayers();
		}					
				
		if(pDocument)
		{
		//	if (pDocument->IsLockDocument(MODE_ACCESS_WRITE)) return false;

			if (!pDocument->LockDocument(MODE_ACCESS_READ)) return false;
			
			m_pDocument = pDocument;	

			pDocument->UnlockDocument(MODE_ACCESS_READ);

			OnChangeLayers();


		}
		else
			m_pDocument = NULL;
					
		
	}
	
	return true;
}
///////////////////////////////////////////////////////////////////////////////////////
void CDEM::CheckLayersReady(bool &setReady,bool &getReady)
{		
	setReady = false;
	getReady = false;
	
	if (!m_pDocument) return;
	/*{
		m_vectorLayerNum = -1;
		m_rasterLayerNum = -1;
		return;
	}
	*/

	if (!m_pDocument->LockDocument(MODE_ACCESS_READ)) return;

	//::SetCursor( AfxGetApp()->LoadStandardCursor(IDC_WAIT) );  // IDC_NO
	
	Cdfi_Layer* pLayer;
	Cdfi_Layers* pLayers = NULL;
	Cdfi_Vector* pVectorLayer = NULL;
	Cdfi_VectorObject *pVectorObject = NULL;
	
	__int64 objCount = 0;

	pLayers = m_pDocument->GetLayers();

	int vectorLayerNum = GetVectorLayerNum();
	int rasterLayerNum = GetRasterLayerNum();
		
	if(vectorLayerNum>=0)
	{
		pLayer = pLayers->GetLayer(vectorLayerNum);
		if(pLayer>=0)
		{
			pVectorLayer = pLayer->GetVector();

			if(pVectorLayer)
				objCount = pVectorLayer->GetVectorInfo()->GetObjectsCount();
		}
	}


	// get flag check 
	if(pVectorLayer)	
	{	
		// set flag check
		if(vectorLayerNum >= 0 &&  rasterLayerNum >= 0)
		{
			if(this->m_objectsSource == 0) // all
			{
				//Ready(true,getReady);
				setReady = true;
				getReady = true;
			}
			else
			if(this->m_objectsSource == 1) // active
			{
				if (pVectorLayer->GetActiveCount() > 0)
				{
					getReady = true;
					setReady = true;
				}
				//getReady = true;
					//Ready(true,true);
			}
			else	
			if(m_objectsSource == 2) // selected
			{
			
				int selLayerNum = pLayers->GetLayerActive(IC_SELECTION_CLASS_NAME);
				Cdfi_Selection *pSelLayer; 
				Cdfi_SelectionItem *pSelItem;
				CIC_Rect3DD selRect,objRect;

				if(selLayerNum>=0)
				{
					pLayer = pLayers->GetLayer(selLayerNum);

					if(pLayer) 
					{
						pSelLayer = pLayer->GetSelection();

						int itemNum = (int)pSelLayer->GetActiveItem();

						if(itemNum>=0)
						{

							pSelItem = pSelLayer->GetItem(itemNum);

							pSelItem->GetBoundRect(&selRect);
					
							selRect.NormalizeRectGeo();

							Cdfi_VectorObjectStream voStream(pVectorLayer);
					
							for(int nObj = 0; nObj < objCount; nObj++)
							{			
								pVectorObject = voStream.GetVectorObject(nObj);											

								if(pVectorObject)
								{
									pVectorObject->GetBoundRect(&objRect);

									if( objRect.IntersectGeoRect( &selRect, &objRect ) )
									{		
										setReady = true;
										getReady = true;

										m_selectedRect = selRect;
										//Ready(true,getReady);	

										break;
									}
								}
							}

						}
					}
				}
			}
		
		}
	}
	
	m_pDocument->UnlockDocument(MODE_ACCESS_READ);


	return;

}

////////////////////////////////////////////////////////////////////////////////////
int CDEM::GetVectorLayerNum()
{
	int vectorLayerNum = -1;

	if (!m_pDocument) return -1;

	Cdfi_Layer* pLayer;
	Cdfi_Layers * pLayers = m_pDocument->GetLayers();

	vectorLayerNum = pLayers->GetLayerActive(IC_VECTOR_CLASS_NAME);

	return vectorLayerNum;
}

////////////////////////////////////////////////////////////////////////////////////
int CDEM::GetRasterLayerNum()
{
	int rasterLayerNum = -1;
	
	if (!m_pDocument) return -1;

	Cdfi_Layer* pLayer;
	Cdfi_Layers * pLayers = m_pDocument->GetLayers();

	rasterLayerNum = pLayers->GetLayerActive(IC_RASTER_CLASS_NAME);
	
	return rasterLayerNum;
}
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
double CDEM::ConvertUnitToGeo(DWORD sourceUom, double dRadius, DWORD destUom)
{
	CIC_Rect3DD rc;

	rc = m_pDocument->GetDocGeoInfo()->GetBoundRect();
	rc.NormalizeGeoRect();
	//rcBoundObj.right = rcBoundObj.left + (rcBoundObj.right - rcBoundObj.left) ;
	//rcBoundObj.top = rcBoundObj.bottom + (rcBoundObj.top - rcBoundObj.bottom) ;

	// отдельный случай нулевой протяженности объекта
	// создаем искусственную протяженность для оценивания пропорции
	if (rc.left == rc.right)
		rc.right++;
	if (rc.top == rc.bottom)
		rc.bottom++;

	return ConvertUnitToGeo(sourceUom, dRadius, &rc, destUom);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
double CDEM::ConvertUnitToGeo(DWORD sourceUom,double dRadius,CIC_Rect3DD *rcBoundObj, DWORD destUom)
{
	//int iUomLayer = sourceUom;
	
	double dValueIn = dRadius;

	if( CGeoInfo::IsLinearUnit(sourceUom) == CGeoInfo::IsLinearUnit(destUom) )
		dValueIn = CGeoInfo::TransformUnit( destUom, sourceUom, dRadius );
	else //Если требуется перевести линейные координаты в угловые (зависит от широты)
	{
		
		//pVectorObject->GetBoundRect( &rcBoundObj );

		// отдельный случай нулевой протяженности объекта
		// создаем искусственную протяженность для оценивания пропорции
		if(rcBoundObj->left == rcBoundObj->right)
			rcBoundObj->right++;
		if(rcBoundObj->top == rcBoundObj->bottom)
			rcBoundObj->bottom++;

		// переводим в радианы
		double long1 = fnc_UOM::AngleToDegree( destUom, rcBoundObj->left ) * M_PI/180.0;
		double lat1 = fnc_UOM::AngleToDegree( destUom, rcBoundObj->top ) * M_PI/180.0;
		double long2 = fnc_UOM::AngleToDegree( destUom, rcBoundObj->right ) * M_PI/180.0;
		double lat2 = fnc_UOM::AngleToDegree( destUom, rcBoundObj->bottom ) * M_PI/180.0;
		// линейный размер в единицах входного размера радиуса(буфера)
		double dVSizeM = fnc_UOM::SphericalLenAzimutEarth( lat1, long1, lat2, long2, NULL, m_uom );
		// линейный размер в единицах слоя
		double dVScale = sqrt( pow( (rcBoundObj->top - rcBoundObj->bottom), 2.0) + pow( (rcBoundObj->left - rcBoundObj->right), 2.0 ) );
		// считеся масштабный коэффициент
		// ( dVScale == dVSizeM ) эта проверка на случай нулевой протяженности объектов чтобы не получать деления на ноль
		dVScale = ( dVScale == dVSizeM ) ? 1.0 : dVScale / dVSizeM;
		// считется новое значение радиуса(буфера) в единицах слоя (объекта)
		dValueIn = dValueIn * dVScale;	
		//dValueIn = CGeoInfo::TransformUnit( destUom, sourceUom, dValueIn);
	}
	return dValueIn;

}



/////////////////////////////////////////////////////////////////

bool CDEM::ConvertToPixels(CIC_Point3DD &pt)
{
	
	double z = pt.z;

	if(m_pa) m_pa->m_pDestImageInfo->GetPixelXY( (CIC_Point3DD *)&pt,(CIC_Point3DD *)&pt);

	pt.z = z;
			
	return true;
}
/////////////////////////////////////////////////////////////////

bool CDEM::ConvertToPixels(IC_POINT3DD &pt)
{	
	double z = pt.z;

	IC_POINT3DD ptn;

	if(m_pa) m_pa->m_pDestImageInfo->GetPixelXY( (CIC_Point3DD *)&pt,(CIC_Point3DD *)&ptn);

	pt = ptn;

	pt.x+=m_pixelOffsetX;
	pt.y+=m_pixelOffsetY;
	pt.z = z;
			
	return true;
}
////////////////////////
bool CDEM::ConvertToPixels(CIC_PolygonD &pPolygon)
{
	
	double z;

	for(DWORD i = 0; i< pPolygon.GetSize(); i++)
	{
		z = pPolygon.GetData()[i].z;

		if(m_pa) m_pa->m_pDestImageInfo->GetPixelXY((CIC_Point3DD *)&(pPolygon.GetData()[i]),(CIC_Point3DD *)&(pPolygon.GetData()[i]));
		
		pPolygon.GetData()[i].x+=m_pixelOffsetX;
		pPolygon.GetData()[i].y+=m_pixelOffsetY;
		pPolygon.GetData()[i].z = z;

	}
	pPolygon.UpdateBoundRect();

	return true;
}
/////////////////////
bool CDEM::ConvertToPixels(CIC_RegionCmx &reg)
{
		
	for(int section = 0;section<reg.GetPolygonsCount();section++)
	{
		ConvertToPixels(*reg.GetPolygon(section));
	}

	reg.UpdateBoundRect();

	return true;
}














///////////////////////////////////////////////////////////////////////////////////////
void CDEM::UpdateRaster(int rasterLayerNum)
{
	if (rasterLayerNum < 0) return;

	if(!m_pDocument) return;

	if(m_pDocument->IsLockDocument(MODE_ACCESS_WRITE))
	{
		m_rasterUpdate = true;
		return;
	}
	
	if (!m_pDocument->LockDocument(MODE_ACCESS_WRITE)) return;

	m_rasterUpdate = false;

	Cdfi_Layer* pLayer;
	Cdfi_Raster *pRaster;
		
	//int m_raster=m_pDocument->GetLayers()->GetLayerActive(IC_RASTER_CLASS_NAME);
	pLayer = m_pDocument->GetLayers()->GetLayer(rasterLayerNum);

	if(pLayer)
	{
		pRaster = pLayer->GetRaster();
		
		if(pRaster) 
			pRaster->UpdateImage(0, true, UPDATE_PYRAMIDS_ALWAYS);


	// history of drawing layer	
	
		//int iHistoryItem = m_pDocument->GetHistory()->AddItem((LPTSTR)(LPCTSTR)::GetResourceString(IDS_DEMCORRECTION), TRUE, AfxGetInstanceHandle());
		//m_pDocument->GetHistory()->GetItem(iHistoryItem)->AddAction(HISTORY_ACTION_CREATE, m_raster, pRaster);
	}
	
	m_pDocument->UnlockDocument(MODE_ACCESS_WRITE);

	m_pDocument->RedrawViews(TRUE, rasterLayerNum);

}


////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////


BOOL CDEM::CropRaster(CDFI *pDfi, Cdfi_Raster *pRaster, CIC_RegionCmx *pCropRegion, Cdfi_Raster *&pRasterOut)
{
int index;
IC_FUNCTION_IDENTIFY fi;
IC_PARAM param = {0};

BOOL bRes;

	if(!pDfi || !pRaster)
		return FALSE;

	param.message = FM_DEFAULT;
	param.iInterface = FUNCTION_CALL_CUSTOM;
	index = pDfi->GetApp()->GetFncFunctions()->GetFuncIndexByName(_T("CopyRasterSimple"));
	pDfi->GetApp()->GetFncFunctions()->GetFunctionInfo(index, &fi);
	
	ICarg_CopyRaster *pArgs = (ICarg_CopyRaster *)fi.pCreateArgs(pDfi, NULL);

	if(!pArgs)
		return FALSE;

	pArgs->SetRaster(pRaster);
	pArgs->SetRegion(*pCropRegion);

	param.pArguments = pArgs;

	bRes = pDfi->GetApp()->GetFncFunctions()->DoFunction(index, &param, FALSE);

	if(bRes)
		pRasterOut = pArgs->GetResultRaster();

	//cleanup
	delete pArgs;

	return bRes;
}
////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
void CDEM::ClearRaster()
{
	bool update=false;
	
	if ( !m_pDocument ) return;

	if (!m_pDocument->LockDocument(MODE_ACCESS_WRITE)) return;

	//int m_raster=m_pDocument->GetLayers()->GetLayerActive(IC_RASTER_CLASS_NAME);

	int vectorLayerNum = GetVectorLayerNum();
	int rasterLayerNum = GetRasterLayerNum();

	
	if(rasterLayerNum >= 0 )
	{
		
		CIC_ImageInfo * pImageInfo = NULL;
		Cdfi_Layer* pLayer;
		Cdfi_Raster *pRaster;
		
		//m_raster=m_pDocument->GetLayers()->GetLayerActive(IC_RASTER_CLASS_NAME);
		pLayer = m_pDocument->GetLayers()->GetLayer(rasterLayerNum);
		pRaster = pLayer->GetRaster();
		if(!pRaster->IsModeEdit())
			pRaster->RasterToEditMode(false,false);
		pImageInfo = pRaster->GetImageInfo();

		DWORD iBlockWidth, iBlockHeight, iBlockSize, L, iPix;
		CIC_Rect64 rcBlocks;

		GETVALUEPROC pGetValueProc = NULL;
		pGetValueProc = CRasterPROCS::PointerGetValueProc(pImageInfo->GetBandInfo(0)->PixelType);
	
		SETVALUEPROC pSetValueProc = NULL;
		pSetValueProc = CRasterPROCS::PointerSetValueProc(pImageInfo->GetBandInfo(0)->PixelType);
		
		iBlockWidth = pRaster->GetBlockWidth();
		iBlockHeight = pRaster->GetBlockHeight();
		iBlockSize = iBlockWidth*iBlockHeight;
	
		rcBlocks.top = 0;
		rcBlocks.bottom = pImageInfo->GetHeight(0)/iBlockHeight;
		rcBlocks.left = 0;
		rcBlocks.right = pImageInfo->GetWidth(0)/iBlockWidth;
		
		BOOL bCanceled = FALSE;
		LPBYTE pIBlock;

		double z=100;

		Cdfi_RasterStream rasterStream(pRaster, 1);
		
		for(long long yBlock = rcBlocks.top; yBlock <= rcBlocks.bottom; yBlock++)
		{
			for (long long xBlock = rcBlocks.left; xBlock <= rcBlocks.right; xBlock++)
			{
							
				pIBlock = rasterStream.Get_lpBlock(0, 0, 0, xBlock, yBlock);
				
				for(DWORD h = 0; h < iBlockHeight; h++)
				{

					L = (DWORD)(iBlockWidth*h);

					for(DWORD w = 0; w < iBlockWidth; w++)
					{					

						iPix = (DWORD)(L + w);					
							
						pSetValueProc((BYTE*)pIBlock, iPix, z);
												
					}
					
				}			
			}
		}
	
		UpdateRaster(rasterLayerNum);

		rasterStream.Clear();
	}
	
	m_pDocument->UnlockDocument(MODE_ACCESS_WRITE);

	if(m_rasterUpdate)
		UpdateRaster(rasterLayerNum);
	
	m_pDocument->RedrawViews(TRUE,rasterLayerNum);

}
///////////////////////////////////////////////////////////////////////////////////////
bool IsIntersection(Cdfi_VectorObject *pVectorObject, CIC_Rect3DD *selRect)
{
	CIC_RegionCmx reg;
	CIC_PolygonD polygon;
	CIC_Rect3DD objRect;
	CIC_RegionCmx *objReg;

	polygon.CreateRectPolygon(selRect);
	polygon.SetExternal(TRUE);
	reg.AddPolygon(&polygon);

	pVectorObject->GetBoundRect(&objRect);

	if (objRect.IntersectGeoRect(selRect, &objRect))
	{
		switch (pVectorObject->GetType())
		{
			case VE_POLYGON:
				objReg = pVectorObject->GetObjPolygon()->GetRegion();
				if (reg.IsIntersect(objReg) == INTERSECT_EMPTY) return false;
			break;

			case VE_LINE:
				objReg = pVectorObject->GetObjLine()->GetRegion();
				if (reg.IsIntersect(objReg) == INTERSECT_EMPTY) return false;
			break;
		}
		return true;
	}
	return false;

};
////////////////////////////////////////////////////////////////



void CDEM::CheckPolygonInRect(CIC_RegionCmx &reg, CIC_Rect3DD vRect) // be careful - it makes z=0
{
	CIC_RegionCmx regSource = reg;
	CIC_RegionCmx regRect;
	CIC_PolygonD polRect;

	vRect.NormalizeGeoRect();
	polRect.CreateRectPolygon(&vRect);
	polRect.SetExternal(TRUE);
	regRect.AddPolygon(&polRect);
	reg.UpdateBoundRectGeo();
		
	bool isIntersect = false;

	for(int section = 0;section < reg.GetPolygonsCount();section++)
		if(regRect.IsIntersect(reg.GetPolygon(section))== INTERSECT_PARTIALLY)
	{
			isIntersect = true;
			break;
		}

		
	if(isIntersect== INTERSECT_PARTIALLY)
	{
		reg.Add_GPC(&polRect, IC_COMMODE_AND);
		InitPolygonBy(&reg,&regSource);
	}
	/* init boarder points by 2 neiboarhoods - no need 
	for(int section = 0; section < reg.GetPolygonsCount();section++)
	{
		CIC_PolygonD *polP = reg.GetPolygon(section);
		for(int i=0;i< polP->GetSize();i++)
		{
			IC_POINT3DD pt = polP->GetData()[i];
			if(polRect.PointLaysOnPolygon(pt.x, pt.y,0,0))
			{
				InitPointByPolygons(pt,&regSource,2);
			}
		}
	}
	*/
	
}

////////////////////////////////////////////////////////////////



void CDEM::CheckPolylineInRect(CIC_RegionCmx &reg, CIC_Rect3DD vRect) 
{	
	CIC_PolygonD *pol; 
	CIC_Point3DD pt;

	for(int section = 0;section < reg.GetPolygonsCount();section++)
	{
		pol = reg.GetPolygon(section);
		
		for(DWORD i=pol->GetSize();i>0;i--)
		{
			pt = pol->GetData()[i-1];					

			if(pt.x<vRect.left || pt.x>vRect.right || pt.y<vRect.bottom || pt.y>vRect.top)
				pol->DeleteAt(i-1);

		}
	}	
	
	reg.UpdateBoundRectGeo();
}
/////////////////////////////////////////////////






/////////////////////////////////////////////////
double CDEM::GetBufferZoneWidth(__int64 objID)
{
	double bzw = 0;
	CString str;

	if(m_zone)
	{
		if(m_zoneWidthSource == 0)
		{		
			if(GetAttribute(objID,m_zoneWidthAttr,str))

				bzw = _wtof(str.GetString());
		}
		else
			bzw = _wtof(m_zoneWidthEditValue);
	}

	return bzw;
}

//////////////////////////////////

bool CDEM::GetAttribute(__int64 objID,CString attrStr,CString &value)
{
	Cdfi_Layer* pLayer;
	Cdfi_Vector* pVectorLayer;	
	Cdfi_VectorColumns* pVectorColumns = NULL;
	Cdfi_VectorColumn* pVectorColumn = NULL;

	//int m_vector = m_pDocument->GetLayers()->GetLayerActive(IC_VECTOR_CLASS_NAME);
	//m_rasterLayerNum = m_pDocument->GetLayers()->GetLayerActive(IC_RASTER_CLASS_NAME);


	int vectorLayerNum = GetVectorLayerNum();
	//int rasterLayerNum = GetRasterLayerNum();


	if(vectorLayerNum < 0) return false;

	pLayer = m_pDocument->GetLayers()->GetLayer(vectorLayerNum);

	pVectorLayer = pLayer->GetVector();

	pVectorColumns = pVectorLayer->GetVectorTable()->GetVectorColumns();
	int index;

	for(index = 0 ; index < pVectorColumns->GetSize(); index ++)
	{
		pVectorColumn = pVectorColumns->Get(index);

		if(pVectorColumn->name == attrStr)
		{
			void *pValue = pVectorLayer->GetVectorTable()->GetColumnValue( objID, index);
			CString str;
			str.Empty();
			switch ( pVectorColumn->type )
			{
				case COLUMN_TYPE_CHAR:				str = PCHAR2STRING((char*)pValue);break;
				case COLUMN_TYPE_WCHAR:				str = (LPCTSTR)pValue;break;
				case COLUMN_TYPE_BYTE:				str.Format( _T("%i"), *(BYTE*)pValue );break;
				case COLUMN_TYPE_SUINT:				str.Format( _T("%i"), *(unsigned short*)pValue );break;
				case COLUMN_TYPE_SINT:				str.Format( _T("%i"), *(short*)pValue );break;
				case COLUMN_TYPE_UINT:				str.Format( _T("%i"), *(unsigned int*)pValue );break;
				case COLUMN_TYPE_INT:				str.Format( _T("%i"), *(int*)pValue );break;
				case COLUMN_TYPE_FLOAT:				str.Format( _T("%f"), *(float*)pValue );break;
				case COLUMN_TYPE_DOUBLE:			str.Format( _T("%f"), *(double*)pValue );break;
				case COLUMN_TYPE_DECIMAL:
				{
					CString FormatString;
					FormatString.Format(_T("%i.%i"), pVectorColumn->width, pVectorColumn->decimal_precision);
					FormatString.Insert( 0, _T("%") );
					FormatString.AppendChar( 'f' );
					str.Format(FormatString, *(double*)pValue);
					str.Trim();
				}
			}
			
			value = str;
					
			return true;
		}
	}
	return false;
}


////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////
//////////////////////////// ADDITION FUNCTIONS ///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////














///////////////////////////////////////////////////////////////////////////////////
//////////////////////////// INIT OBJECT  - READ LEVEL ///////////////////////////
///////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
void CDEM::ReadLevels()
{
	auto exit=[&]()
	{
		m_pDocument->UnlockDocument(MODE_ACCESS_WRITE);
	};

	if ( !m_pDocument ) return;

	if (!m_pDocument->LockDocument(MODE_ACCESS_WRITE)) return;
	
	Cdfi_Layer* pLayer;
	Cdfi_Vector* pVectorLayer;
	Cdfi_Layers* pLayers;	
	__int64 objectID;
	int objCount = 0;

	int vectorLayerNum = GetVectorLayerNum();
	int rasterLayerNum = GetRasterLayerNum();

	pLayers = m_pDocument->GetLayers();
		
	if (vectorLayerNum < 0 || rasterLayerNum < 0)
		exit();

	
	PIXEL_ACCESS pa(this,rasterLayerNum, rasterLayerNum, NULL);

	pLayer = m_pDocument->GetLayers()->GetLayer(vectorLayerNum);

	if (!pLayer)
		exit();

	pVectorLayer = pLayer->GetVector();

	Cdfi_VectorObject *  pVectorObjectSource = NULL;
	Cdfi_VectorObjectStream voStream(pVectorLayer, VMEM_READWRITE);


	
	if (m_objectsSource == 1) // active
	{

		objCount = pVectorLayer->GetActiveCount();

		SetProgress(m_pDfi, 0, (TCHAR *)GetResourceString(IDS_DEM_PROGRESS_LABEL).GetString(), objCount);

		for (int nObj = 0; nObj < objCount; nObj++)
		{
			objectID = pVectorLayer->GetActiveObjectID(nObj);

			if (objectID >= 0)
			{
				pVectorObjectSource = voStream.GetVectorObject(objectID);

				Cdfi_VectorObject *pVectorObject = pVectorObjectSource->Duplicate();

				if (pVectorObject)
				{
					InitObject(pVectorObject);
					voStream.ReplaceObject(objectID, pVectorObject);
					pVectorObject->DeleteObject();
					m_pDfi->GetApp()->GetFncFunctions()->SendMessage(FM_VECTOR_OBJ_CHANGE, vectorLayerNum, objectID, m_pDocument);
				}

			}

			if (IncProgress()) break;
		}
	}
	else // all or selected
		
	if (m_objectsSource == 0 || m_objectsSource == 2)
	{
		CIC_Rect3DD objRect, selRect;

		if (m_objectsSource == 2)

			selRect = m_selectedRect;
		
		else
		
			selRect = m_pa->m_destRect;					

		objCount = pVectorLayer->GetVectorInfo()->GetObjectsCount();

		SetProgress(m_pDfi, 0, (TCHAR *)GetResourceString(IDS_DEM_PROGRESS_LABEL).GetString(), objCount);

		for(int nObj = 0; nObj < objCount; nObj++)
		{
			objectID = nObj;

			pVectorObjectSource = voStream.GetVectorObject(objectID);

			pVectorObjectSource->GetBoundRect(&objRect);

			if (objRect.IntersectGeoRect(&selRect, &objRect))
			{
				Cdfi_VectorObject *pVectorObject = pVectorObjectSource->Duplicate();

				if (pVectorObject)
				{
					InitObject(pVectorObject);
					voStream.ReplaceObject(objectID, pVectorObject);
					pVectorObject->DeleteObject();
					m_pDfi->GetApp()->GetFncFunctions()->SendMessage(FM_VECTOR_OBJ_CHANGE, vectorLayerNum, objectID,  m_pDocument);
				}
			}

			if (IncProgress()) break;
		}
	}
	EndProgress();

	voStream.Stop();

	exit();
		
}
////////////////////////////////////////////////////////
void CDEM::InitObject(Cdfi_VectorObject *pVectorObject, double level)
{
		
	int initFlag = LEVEL_SOURCE_RASTER | LEVEL_ACTION_SET;
		
	if( pVectorObject->GetType() == VE_POINT )	
	{	
		InitPoint(pVectorObject->GetObjPoint(),initFlag,level);		
	}		
	else
	if( pVectorObject->GetType() == VE_LINE )
	{
		
		InitPolyline(pVectorObject->GetObjLine(),initFlag,level);
	}
	else
	if( pVectorObject->GetType() == VE_POLYGON )
	{
				
		InitPolygon(pVectorObject->GetObjPolygon(),initFlag,level);	

	}
	

}
///////////////////////////////////////////////////////////////////////////////////////
void CDEM::InitPoint(Cdfi_VectorPoint *obj, int flag, double level)
{
	IC_POINT3DD ptGeo=obj->GetData()[0];
		
	InitPointGeo(ptGeo,flag,level);

	obj->SetPoints(1,&ptGeo);

}
///////////////////////////////////////////////////////////////////////////////////////
void CDEM::InitPointGeo(IC_POINT3DD &geoPt, int flag, double level)
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );
	
	if(flag == 0) return;
	
	IC_POINT3DD pt=geoPt;

	ConvertToPixels(pt);

	InitPointP(pt,flag,level);

	geoPt.z = pt.z;

			
}

///////////////////////////////////////////////////////////////////////////////////////

void CDEM::InitPointP(IC_POINT3DD &pt, int flag, double level)
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );
	
	if(flag == 0) return;

	int init = flag&0xF;
	int action = flag&0xF0;
	double rasterValue = 0;
	double z = 0;
		
	m_pa->get_pixel((__int64)pt.x,(__int64)pt.y,rasterValue);
	
	switch(init) 
	{		
		case LEVEL_SOURCE_RASTER:	
			z = rasterValue;
		break;

		case LEVEL_SOURCE_VALUE:
			z = level;
		break;

		case LEVEL_SOURCE_NONE:
		default:
			z = pt.z;
		break;

	}
		
	switch(action)
	{
		case LEVEL_ACTION_SET:
			pt.z = z; // absolute 
		break;

		case LEVEL_ACTION_ADD:	// adding to get absolute values fron lelative	 
			pt.z = z + rasterValue;
		break;

		case LEVEL_ACTION_SUB:  // subtracting to get relative level or difference level in relief mode (in fact  - the same)
			pt.z = z - rasterValue;
		break;
	}
	
}

///////////////////////////////////////////////////////////////////////////////////////

void CDEM::InitPolyline(Cdfi_VectorLine *pObj, int flag, double level)
{
	CIC_PolygonD *polygon;

	for(int section=0;section<pObj->GetRegion()->GetPolygonsCount();section++)
	{
		polygon = pObj->GetRegion()->GetPolygon(section);

		InitPolygon(polygon,flag,level);
					
	}
}

///////////////////////////////////////////////////////////////////////////////////////

void CDEM::InitPolygon(Cdfi_VectorPolygon *pObj, int flag, double level)
{
	CIC_PolygonD *polygon;

	for(int section=0;section<pObj->GetRegion()->GetPolygonsCount();section++)
	{
		polygon = pObj->GetRegion()->GetPolygon(section);

		InitPolygon(polygon,flag,level);
					
	}
}
///////////////////////////////////////////////////////////////////////////////////////

void CDEM::InitPolygon(CIC_PolygonD *pPolygon, int flag, double level) 
{	
	CIC_Point3DD pt;

	for(DWORD i = 0; i < pPolygon->GetSize(); i++)
	{	
		pt = pPolygon->GetData()[i];
		InitPointGeo(pt,flag,level);
		pPolygon->GetData()[i] = pt;
	}
}
///////////////////////////////////////////////////////////////////////////////////////

void CDEM::InitPolygonP(CIC_PolygonD *pPolygon, int flag, double level) 
{	
	CIC_Point3DD pt;

	for(DWORD i = 0; i < pPolygon->GetSize(); i++)
	{	
		pt = pPolygon->GetData()[i];
		InitPointP(pt,flag,level);
		pPolygon->GetData()[i] = pt;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////

void CDEM::InitPolygonBy(CIC_RegionCmx *regTo, CIC_RegionCmx *regFrom, int nNearestPoints)
{
	CIC_PolygonD *polygon;

	for(int section=0;section<regTo->GetPolygonsCount();section++)
	{
		polygon = regTo->GetPolygon(section);

		InitPolygonBy(polygon,regFrom,nNearestPoints);

	}
}

//////////////////////////////////////////////////////////////////////////////


void CDEM::InitPolygonBy(CIC_PolygonD *pZone, CIC_RegionCmx *reg, int nNearestPoints)
{
	//int iPointsCount, 
	//int iDimension;	
	// Создаем kd-дерево по существующим точкам	 
	//iDimension = 2;
	//CIC_Point3DD pt;
	int ptCount = reg->GetPointsCount();

	ANNpointArray pointArray = annAllocPts((size_t)ptCount, 2);

	double *pz = new double[ptCount];

	for(int section = 0; section < reg->GetPolygonsCount(); section++)
	{
		CIC_PolygonD *pPol = reg->GetPolygon(section);
		for(DWORD i = 0; i < pPol->GetSize(); i++)
		{
			pointArray[i][0] = pPol->GetData()[i].x;
			pointArray[i][1] = pPol->GetData()[i].y;
			pz[i] = pPol->GetData()[i].z;
		}
	}
		
	ANNkd_tree *tree = new ANNkd_tree(pointArray, (int)reg->GetPointsCount(), 2);
	ANNpoint point = new ANNcoord[2];
	ANNidxArray idArray = new ANNidx[nNearestPoints];
	ANNdistArray distArray = new ANNdist[nNearestPoints];

	for(DWORD i = 0; i < pZone->GetSize(); i++)
	{
		point[0] = pZone->GetData()[i].x;
		point[1] = pZone->GetData()[i].y;

		tree->annkSearch(point, nNearestPoints, idArray, distArray);

		int n = idArray[0] % ptCount;

		pZone->GetData()[i].z = pz[n];
	}
	delete []pz;
	delete []idArray;
	delete []distArray;
	delete []point;
	delete tree;
	
	annDeallocPts(pointArray);
	annClose();
}

///////////////////////////////////////////////////////////////////////////

void CDEM::InitPointBy(IC_POINT3DD &pt, CIC_RegionCmx *reg, int nNearestPoints)
{
	//int iPointsCount, iDimension;	
	// Создаем kd-дерево по существующим точкам	 
	//iDimension = 2;
	//CIC_Point3DD pt;
	int ptCount = reg->GetPointsCount();

	ANNpointArray pointArray = annAllocPts((size_t)ptCount, 2);
	
	nNearestPoints = min(nNearestPoints, ptCount);

	double *pz = new double[ptCount];

	for(int section = 0; section < reg->GetPolygonsCount(); section++)
	{
		CIC_PolygonD *pPol = reg->GetPolygon(section);
		for(DWORD i = 0; i < pPol->GetSize(); i++)
		{
			pointArray[i][0] = pPol->GetData()[i].x;
			pointArray[i][1] = pPol->GetData()[i].y;
			pz[i] = (pPol->GetData()[i]).z;
		}
	}
		
	ANNkd_tree *tree = new ANNkd_tree(pointArray, (int)reg->GetPointsCount(), 2);
	ANNpoint point = new ANNcoord[2];
	ANNidxArray idArray = new ANNidx[nNearestPoints];
	ANNdistArray distArray = new ANNdist[nNearestPoints];

	
	point[0] = pt.x;
	point[1] = pt.y;

	tree->annkSearch(point, nNearestPoints, idArray, distArray);
	
	pt.z = 0;
	
	for(int i = 0; i< nNearestPoints; i++)		
		pt.z += pz[idArray[i] % ptCount];
	
	pt.z = pt.z / nNearestPoints;

	delete []pz;
	delete []idArray;
	delete []distArray;
	delete []point;
	delete tree;
	
	annDeallocPts(pointArray);
	annClose();
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////
//////////////////////////// INIT OBJECT ///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

































///////////////////////////////////////////////////////////////////////////////////
//////////////////////////// RASTRIZE ///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
void CDEM::Rasterize()
{
auto exit = [&]()	
{
	m_pDocument->UnlockDocument(MODE_ACCESS_WRITE);

	return;
};	
	
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );
		
	bool addLayerFlag = false;
	int vectorLayerNum = -1;
	int rasterLayerNum = -1;

	Cdfi_History *pHist;
	Cdfi_Raster *pNewRasterLayer;
	Cdfi_Raster *pRasterLayer;
	Cdfi_Vector* pVectorLayer;	
	Cdfi_Layer* pLayer;
	Cdfi_Layers* pLayers;
	Cdfi_VectorObject *  pVectorObject = NULL;
	__int64 objCount = 0;
	bool update=false;
	CString rasterName;
	__int64 objectID;
	
	if ( !m_pDocument ) return;

	if (!m_pDocument->LockDocument(MODE_ACCESS_WRITE)) return;

	pHist = m_pDocument->GetHistory();
	
	pLayers = m_pDocument->GetLayers();
	

	// init vector	
	vectorLayerNum = GetVectorLayerNum();
	rasterLayerNum = GetRasterLayerNum();

	if(vectorLayerNum < 0)
		
		return exit();
	
	pLayer = pLayers->GetLayer(vectorLayerNum);

	if(!pLayer)
		return exit();
		
	pVectorLayer = pLayer->GetVector();

	if(!pVectorLayer) 
		return exit();

	objCount = pVectorLayer->GetVectorInfo()->GetObjectsCount();

	Cdfi_VectorObjectStream voStream( pVectorLayer, VMEM_READ );


	// rasters calulations

	if(rasterLayerNum < 0 )
		
		return exit();

	int destRasterLayerNum = rasterLayerNum;
	int sourceRasterLayerNum = rasterLayerNum;

	pLayer = pLayers->GetLayer(rasterLayerNum);

	if (!pLayer)

		return exit();

	pRasterLayer = pLayer->GetRaster();	
	
	if (!pRasterLayer)

		return exit();

	rasterName = pLayer->GetLayerName();
	
	CIC_Rect3DD sourceRect,destRect,selRect,objRect;

	DWORD uom= pRasterLayer->GetImageInfo()->GetGeoInfoW()->GetGeoProjection()->GetUnit();

	// calc Pixel size	
	sourceRect = pRasterLayer->GetImageInfo()->GetGeoInfoW()->GetBoundRect(); 
	selRect = sourceRect; // rect equals base raster by default
	destRect = selRect;
	
	//int pSize = pRasterLayer->GetImageInfo()->GetPixelSize(0);


	// calc rect of dest raster
	if(m_objectsSource == 1) // active
	{		

		objCount = pVectorLayer->GetActiveCount();
		
		if( m_rasterCopy == 1 && m_rasterCut == 1) // new and cutted
		{
			selRect.SetRectEmpty();

			for(int nObj = 0; nObj < objCount; nObj++)
			{			
				objectID = pVectorLayer->GetActiveObjectID(nObj);

				if(objectID >= 0)
				{							
					pVectorObject = voStream.GetVectorObject(objectID);							
			
					if ( pVectorObject )
					{					
						double bzw = 0;	
						pVectorObject->GetBoundRect(&objRect,TRUE);
						// add buffer zone
						bzw = GetBufferZoneWidth(pVectorObject->GetID());
						bzw = ConvertUnitToGeo(m_uom,bzw,&selRect,uom);
						//bzw *= unit2geo; 
						
						objRect.left-=bzw;						
						objRect.bottom-=bzw;
						objRect.top+=bzw;
						objRect.right+=bzw;
						//objRect.NormalizeGeoRect();
						//objRect.InflateRect(bzw,bzw,bzw,bzw); // not work correct!!!!
						if(nObj>0) selRect.UnionGeoRect(&selRect,&objRect);
						else selRect = objRect;
					}
				}
			}
			
			// or(and) inflate	on 10%
			selRect.NormalizeGeoRect();
			double dx = (selRect.right - selRect.left)/10;
			double dy = (selRect.top - selRect.bottom)/10;
			selRect.left-=dx;						
			selRect.bottom-=dy;
			selRect.top+=dy;
			selRect.right+=dx;
			//selRect.InflateRect(dx,dx,dx,dx); // not correct
			destRect = selRect;
		}
	}
	else
	if(m_objectsSource == 2) // selected
	{		
		selRect = m_selectedRect;
		destRect = selRect;

	
	}
	else
	if(m_objectsSource == 0) // all objects	
	{
		
	}

	// if it was early - delete saved copy for unding
	//if (m_pSavedRaster)
	//	::DeleteObject(m_pSavedRaster);
	//m_canUndo = false;
	//	

	// do destination copy or saved copy for undo

	if(m_rasterCopy==1 )  // if new raster
	{					
		CIC_RegionCmx reg;
		CIC_PolygonD polygon;

		polygon.CreateRectPolygon(&destRect);
		polygon.SetExternal(TRUE);
		reg.AddPolygon(&polygon);
		
		if(CropRaster(m_pDfi,pRasterLayer,&reg,pNewRasterLayer))
		{
			///  set history
			//pLayer = m_pDocument->GetLayers()->GetLayer(destRasterLayerNum);
			//pHist->AddItem((LPCTSTR)GetResourceString(IDS_DEMCORRECTION), HISTORY_ACTION_MODIFY, 0, pLayers, TRUE, NULL, AfxGetInstanceHandle());

			destRasterLayerNum = pLayers->AddLayer((Cdfi_LayerObject*)pNewRasterLayer, TRUE);
			
			//pLayers->SetLayerPos(destRasterLayerNum, 0,TRUE,TRUE);
			pLayer = pLayers->GetLayer(destRasterLayerNum);

			rasterName = CString("Copy of ") + rasterName;
			rasterName = pLayers->GenerateNewName(rasterName);
			pLayer->SetName(rasterName,TRUE);

			pLayers->SetLayerEdit(destRasterLayerNum,FALSE,TRUE);
			pLayers->UpdateLayer(destRasterLayerNum);

			addLayerFlag = true;
			
			destRect = pLayer->GetGeoInfo()->GetBoundRect();

			selRect = destRect;
			
			
			pHist->AddItem((LPTSTR)(LPCTSTR)pLayer->GetLayerName(), HISTORY_ACTION_CREATE, destRasterLayerNum, pLayer, TRUE);

		}
		else
		{
			//m_rasterLayerNum = -1;
			AfxMessageBox(GetResourceString(IDS_DEM_CANNOT_COPY_RASTER),MB_OK);// MB_ICONQUESTION | );
			
			m_pDocument->UnlockDocument(MODE_ACCESS_WRITE);
			
			return;
			
		}
	}
	/*
	else
	{
		if (m_undoEnable)
		{
			CIC_RegionCmx reg;
			CIC_PolygonD polygon;

			polygon.CreateRectPolygon(&sourceRect);
			polygon.SetExternal(TRUE);
			reg.AddPolygon(&polygon);			

			if (CropRaster(m_pDfi, pRasterLayer, &reg, m_pSavedRaster))
			{
				m_pUndoRaster = pRasterLayer;
				m_canUndo = true;
			}
			
		}
	}
	*/

	if(destRasterLayerNum<0)
		return exit();

		
	//init for drawing functions
	
	PIXEL_ACCESS pa(this,sourceRasterLayerNum,destRasterLayerNum,&selRect);
	

	


	// draw yet	
	//int iHistoryItem = m_pDocument->GetHistory()->AddItem((LPTSTR)(LPCTSTR)::GetResourceString(IDS_DEMCORRECTION), TRUE, AfxGetInstanceHandle());
	//m_pDocument->GetHistory()->GetItem(iHistoryItem)->AddAction(HISTORY_ACTION_CREATE, m_raster, pLayers->GetLayer(m_raster));

	///  set history
	pLayer = m_pDocument->GetLayers()->GetLayer(destRasterLayerNum);
	pHist->AddItem((LPCTSTR)GetResourceString(IDS_DEMCORRECTION), HISTORY_ACTION_MODIFY, destRasterLayerNum, pLayer,TRUE, NULL, AfxGetInstanceHandle());

	
	SetProgress(m_pDfi,0,(TCHAR *)GetResourceString(IDS_DEM_PROGRESS_LABEL).GetString(),objCount);

	if(m_objectsSource == 1) // active
	{
		for(int nObj = 0; nObj < objCount; nObj++)
		{			
			objectID = pVectorLayer->GetActiveObjectID(nObj);

			if(objectID >= 0)
			{
							
				pVectorObject = voStream.GetVectorObject(objectID);							
			
				if ( pVectorObject )
				{

					DrawObject(pVectorObject);	

					//Sleep(3000);// temp

					if(IncProgress()) break;
							
				}
							
			}							
		}
	}
	else // all or selected

	if(m_objectsSource == 0 || m_objectsSource == 2)
	{
		Cdfi_VectorObjectStream voStream(pVectorLayer);
					
		for(int nObj = 0; nObj < objCount; nObj++)
		{			
			pVectorObject = voStream.GetVectorObject(nObj);											
			if (pVectorObject)
			{
								
				if (IsIntersection(pVectorObject,&selRect))
				{
					DrawObject(pVectorObject);

						//Sleep(3000);// temp

					if (IncProgress()) break;
			
				}

			}
		}
	}
	else
	if (m_objectsSource == 2) // selected
	{

		// need to do drawing only in selected region of any form - do it when free time will be
		/*
		int selLayerNum = pLayers->GetLayerActive(IC_SELECTION_CLASS_NAME);
		Cdfi_Selection *pSelLayer;
		Cdfi_SelectionItem *pSelItem;
		CIC_Rect3DD selRect, objRect;

		if (selLayerNum >= 0)
		{
			pLayer = pLayers->GetLayer(selLayerNum);

			if (pLayer)
			{
				pSelLayer = pLayer->GetSelection();

				int count = pSelLayer->GetSize();
				Cdfi_SelectionItem *item;

				for (int i = 0;i < count;i++)
				{
					item = pSelLayer->GetItem(i)

					item->

				}
				int itemNum = (int) > GetActiveItem();

				if (itemNum >= 0)
				{

					pSelItem = pSelLayer->GetItem(itemNum);

					pSelItem->GetBoundRect(&selRect);

					selRect.NormalizeRectGeo();
				}
			}
		}
		



		Cdfi_VectorObjectStream voStream(pVectorLayer);

		for (int nObj = 0; nObj < objCount; nObj++)
		{
			pVectorObject = voStream.GetVectorObject(nObj);
			if (pVectorObject)
			{

				if (IsIntersection(pVectorObject, &selRect))
				{
					DrawObject(pVectorObject);

					//Sleep(3000);// temp

					if (IncProgress()) break;

				}

			}
		}*/
	}
		
	EndProgress();	
	
	//m_pa = NULL;
	
	m_rasterUpdate = true;

	voStream.Stop();

	m_pDocument->SetModified();
	
	m_pDocument->UnlockDocument(MODE_ACCESS_WRITE);
	
	if(m_rasterUpdate)
	{
		UpdateRaster(destRasterLayerNum);
	}
	if(addLayerFlag)
	{
		m_pDfi->GetApp()->GetFncFunctions()->SendMessage(FM_ADD_LAYER, destRasterLayerNum, NULL, m_pDocument);
	}

}






///////////////////////////////////////////////////////////////////////////////////
//////////////////////////// DRAW OBJECT ///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
/*
void CDEM::UndoRasterize()
{
	m_canUndo = false;
	
	
	if (!m_pSavedRaster) return;
	
	if (!m_pUndoRaster) return;
	
	if (!m_pDocument) return;

	if (!m_pDocument->LockDocument(MODE_ACCESS_WRITE)) return;

	Cdfi_Layers *pLayers = m_pDocument->GetLayers();
	Cdfi_Layer *pLayer;
	int nLayer = -1;

	for (int i = 0; i < pLayers->GetNumberLayers();i++)
	{
		pLayer = pLayers->GetLayer(i);

		if (!pLayer) break;

		if (pLayer->GetRegisterClass()->IsClass(IC_RASTER_CLASS_NAME))
		{
			if (pLayer->GetRaster() == m_pUndoRaster)
			{
				nLayer = i;
				break;
			}
		}
	}


	if (nLayer>=0)
	{
		m_pUndoRaster->SetRaster(m_pSavedRaster);

		m_pUndoRaster = NULL;
	}
	
	m_pDocument->UnlockDocument(MODE_ACCESS_WRITE);

	UpdateRaster(nLayer);

	::DeleteObject(m_pSavedRaster);

	m_pSavedRaster = NULL;
}
*/
//////////////////////////////////////////////////////////////////////////////////






///////////////////////////////////////////////////////////////////////////////////
//////////////////////////// DRAW OBJECT ///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
void CDEM::DrawObject(Cdfi_VectorObject *pVectorObjectSource)
{
	CString str;

	int initFlag = 0;
	double level = 0;
	bool errLevel = false;
	__int64 objectID = pVectorObjectSource->GetID();
	
	// check level
	if(this->m_levelSource == 1)
	{
		if(GetAttribute(objectID,m_levelAttr,str))

			level = _wtof(str.GetString());

		else errLevel = true;
	}
	else
	if(m_levelSource == 2)
	{
		if(m_levelEditValue[0]!=0)
			level = _wtof(m_levelEditValue);
		else
			errLevel = true;
	}

	if(errLevel)
	{
		if(AfxMessageBox(GetResourceString(IDS_DEM_REF_NO_SET), MB_ICONQUESTION | MB_YESNO) != IDYES)
		
			return; 
		
		else level = 0;
	}
		

	double zoneWidth = 0;
	
	// check zone width
	if(m_zone)
	{
		if(m_zoneWidthSource == 0)
		{
		
			if(GetAttribute(objectID,m_zoneWidthAttr,str))

				zoneWidth = _wtof(str.GetString());

			else
			
				zoneWidth = 0;			
		}
		else
			zoneWidth = _wtof(m_zoneWidthEditValue);

		if(zoneWidth == 0) 
		{
			if (AfxMessageBox(GetResourceString(IDS_DEM_ZONE_WIDTH_NO_SET), MB_ICONQUESTION | MB_YESNO) != IDYES)
			{
				return; // temp Afx-Dialog
			}
		}
	}
	m_zoneWidthGeo = ConvertUnitToGeo(m_uom,zoneWidth,&m_pa->m_sourceRect,m_pa->m_uom);
	
	if (m_zoneFactor)
		m_zoneWidthGeo /= 2;

	// check flag of set-get level
		
		
	initFlag = LEVEL_ACTION_SET;
	
	if(m_relief==1 && m_reference == 0)// draw with relief - all points must be relative
		initFlag = LEVEL_ACTION_SUB;
	else
	if(m_relief==0 && m_reference == 1)
		initFlag = LEVEL_ACTION_ADD; // add or set
	
	if(m_levelSource > 0) initFlag |= LEVEL_SOURCE_VALUE;
	//else
		//if(initFlag) initFlag = 0; // why???
	
	///// do work copy

	Cdfi_VectorObject *pVectorObject=pVectorObjectSource->Duplicate();
	
	
	
	// play

	if( pVectorObject->GetType() == VE_POINT )	
	{	

		if(initFlag) InitPoint(pVectorObject->GetObjPoint(),initFlag,level);

		DrawPoint(pVectorObject->GetObjPoint());					
	}
		
	else
	if( pVectorObject->GetType() == VE_LINE )
	{
		
		if(initFlag) 
			InitPolyline(pVectorObject->GetObjLine(),initFlag,level);		

		DrawPolyline(pVectorObject->GetObjLine());			
		
	}
	else
	if( pVectorObject->GetType() == VE_POLYGON )
	{
				
		if(initFlag) 
			InitPolygon(pVectorObject->GetObjPolygon(),initFlag,level);

		CheckPolygonInRect(*pVectorObject->GetObjPolygon()->GetRegion(),m_pa->m_destRect); 

	//	InitPolygonByPolygons(pVectorObject->GetObjPolygon()->GetRegion(),pVectorObjectSource->GetObjPolygon()->GetRegion());

		DrawPolygon(pVectorObject->GetObjPolygon());												

	}
	
	pVectorObject->DeleteObject();

	pVectorObject = NULL;

}

///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////
//////////////////////////// DRAW OBJECTS ///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////









///////////////////////////////////////////////////////////////////////////////////
//////////////////////////// DRAW POINT ///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////


void CDEM::DrawPoint(Cdfi_VectorPoint *pObj)
{
	IC_POINT3DD *pp=pObj->GetData();

	if( m_zone == TRUE )

		ZonePoint(pp[0]);

	if (!(m_zone & m_optionZoneOnly))

		DrawPoint(pp[0]);
}
///////////////////////////////////////////////////////////////////////////////////////
void CDEM::DrawPoint(IC_POINT3DD gpoint)
{	
	ConvertToPixels(gpoint);

	DrawPointP(gpoint);
}
///////////////////////////////////////////////////////////////////////////////////////
void CDEM::DrawPointP(IC_POINT3DD pt)
{
	m_pa->put_pixel((__int64)pt.x,(__int64)pt.y,pt.z);	
}
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////
//////////////////////////// DRAW POINT ///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////













///////////////////////////////////////////////////////////////////////////////////
//////////////////////////// DRAW POLYGON & POLYLINE ///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
void CDEM::DrawPolyline(Cdfi_VectorLine *pObj)
{
	CIC_RegionCmx *reg = pObj->GetRegion();

	//ConvertToPixels(reg);

	CIC_RegionCmx regZone(reg);

	if( m_zone == TRUE )

		ZonePolyline(&regZone);

	if (!(m_zone & m_optionZoneOnly))
	{
		int fillFlag = LEVEL_FILL_SET;

		if (m_relief)
			fillFlag = LEVEL_FILL_SUM; // summ

		ConvertToPixels(*reg);

		for(int section = 0;section<reg->GetPolygonsCount(); section++)
		{
			CIC_PolygonD *pPolygon = reg->GetPolygon(section);
	
			for(DWORD i=0;i<(pPolygon->GetSize()-1);i++)
			{
				DrawLineP(pPolygon->GetData()[i],pPolygon->GetData()[i+1],fillFlag);
			}	
		}
	}
	
	
}
///////////////////////////////////////////////////////////////////////////////////////
void CDEM::DrawPolygonContour(CIC_PolygonD *pPolygon)
{

	for(DWORD i=0;i<(pPolygon->GetSize()-1);i++)
	{
		DrawLine(pPolygon->GetData()[i],pPolygon->GetData()[i+1]);
	}	
	DrawLine(pPolygon->GetData()[0],pPolygon->GetData()[pPolygon->GetSize()-1]);	
		
	
}
///////////////////////////////////////////////////////////////////////////////////////
void CDEM::DrawPolygon(Cdfi_VectorPolygon *pObj)
{
	CIC_RegionCmx *pReg = pObj->GetRegion();
	
	DeleteAutoIntersections(*pReg);

	if( m_zone == TRUE )

		ZonePolygonObject(pReg);
	
	if (!(m_zone & m_optionZoneOnly))
	

		FillObject(*pReg);	
	
}

///////////////////////////////////////////////////////////////////////////////////
//////////////////////////// DRAW POLYGON ///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////






///////////////////////////////////////////////////////////////////////////////////
//////////////////////////// DRAW ZONES ///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
void CDEM::ZonePoint(CIC_Point3DD pt0)
{
	CIC_RegionCmx rgZone;
	CIC_PolygonD plZone;	
	CIC_PolygonD *pol;

	if (m_zoneWidthGeo <= 0) return;

	// calc points for circle building
	CIC_Point3DD pt2,pt0p,pt2p;

	pt2 = pt0;pt2.x += m_zoneWidthGeo;
	m_pa->m_pDestImageInfo->GetPixelXY(&pt0, &pt0p);
	m_pa->m_pDestImageInfo->GetPixelXY(&pt2, &pt2p);
	int nPoints = max(4, sqrt(abs(pt0p.x - pt2p.x))); // >5 
			
	if(pt0.CreateBufferZoneSimplePoint(&plZone,m_zoneWidthGeo,nPoints) == TRUE) //m_zoneRoundPoints
	{			
		rgZone.Add_GPC(&plZone, IC_COMMODE_OR);

		pol = rgZone.GetPolygon(0);
				
		if(m_zoneGradient)
		{
			if(m_relief==1)
				InitPolygonP(pol,LEVEL_SOURCE_RASTER | LEVEL_ACTION_SUB); // or init by 0
			else
				InitPolygonP(pol,LEVEL_SOURCE_RASTER | LEVEL_ACTION_SET);
		}
		else
		
		for(DWORD i = 0; i < pol->GetSize() ; i++)
		{
			pol->GetData()[i].z = pt0.z;
		}		

		rgZone.DefineExternal();

		FillObject(rgZone,&pt0);
	}
	
}




/////////////////////////////////////////////////////////////////////////
void CDEM::ZonePolyline(CIC_RegionCmx *pRegBase)
{	
	CIC_RegionCmx *rgZone;
	
	if (m_zoneWidthGeo <= 0) return;

	// calc points for ends rounding
	CIC_Point3DD pt0,pt2, pt0p, pt2p;
	
	pt0 = pRegBase->GetPolygon(0)->GetData()[0];
	pt2 = pRegBase->GetPolygon(0)->GetData()[0];
	pt2.x += m_zoneWidthGeo;
	m_pa->m_pDestImageInfo->GetPixelXY(&pt0, &pt0p);
	m_pa->m_pDestImageInfo->GetPixelXY(&pt2, &pt2p);
	int nPoints = max(4, sqrt(abs(pt0p.x - pt2p.x))/2); // >5 
	
	rgZone = CIC_Buffer::CreateBufferZoneLine(pRegBase, m_zoneWidthGeo, nPoints, 1);//m_zoneRounding ? 1 : 2 );
	
	CheckPolygonInRect(*rgZone,m_pa->m_destRect); 

	DeleteAutoIntersections(*rgZone);

	for(int section = 0; section < rgZone->GetPolygonsCount(); section++)
	{
		CIC_PolygonD *pZone=rgZone->GetPolygon(section);

		if(m_zoneGradient)
		{		
			if(m_relief==1)
				InitPolygon(pZone,LEVEL_SOURCE_RASTER | LEVEL_ACTION_SUB); // or init by 0
			else
				InitPolygon(pZone,LEVEL_SOURCE_RASTER | LEVEL_ACTION_SET);	
		}
		else
		{
			InitPolygonBy(pZone,pRegBase);
		}
	}
			
	CheckPolylineInRect(*pRegBase,m_pa->m_destRect);  // get back when is no longer reset

	//DeleteAutoIntersections(*pRegBase);
			
	FillObject(*rgZone, *pRegBase);

	delete rgZone;
	
}
/////////////////////////////////////////////////////////////////////////
void CDEM::ZonePolygonObject(CIC_RegionCmx *rgPolygon)
{	
	//CIC_PolygonD *pPolygon;
	CIC_RegionCmx rgBase=rgPolygon;
		
	ZonePolygon(&rgBase);

	return;
	
}
/////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////

void CDEM::ZonePolygon(CIC_RegionCmx *pRegBase)
{	
	CIC_RegionCmx *rgZone;

	if (m_zoneWidthGeo <= 0) return;

	// calc points for circle building
	CIC_Point3DD pt0, pt2, pt0p, pt2p;

	pt0 = pRegBase->GetPolygon(0)->GetData()[0];
	pt2 = pRegBase->GetPolygon(0)->GetData()[0];
	pt2.x += m_zoneWidthGeo;
	m_pa->m_pDestImageInfo->GetPixelXY(&pt0, &pt0p);
	m_pa->m_pDestImageInfo->GetPixelXY(&pt2, &pt2p);
	int nPoints = max(4, sqrt(abs(pt0p.x - pt2p.x))/2); // >5 

	rgZone = CIC_Buffer::CreateBufferZonePolygon(pRegBase, m_zoneWidthGeo, nPoints, 2 );

	CheckPolygonInRect(*rgZone,m_pa->m_destRect);

	DeleteAutoIntersections(*rgZone);
	
	for(int section = 0; section < rgZone->GetPolygonsCount(); section++)
	{
		CIC_PolygonD *pZone=rgZone->GetPolygon(section);
		
		if(m_zoneGradient)
		{		
			if(m_relief==1)
				InitPolygon(pZone,LEVEL_SOURCE_RASTER | LEVEL_ACTION_SUB); // or init by 0
			else
				InitPolygon(pZone,LEVEL_SOURCE_RASTER | LEVEL_ACTION_SET);	
		}
		else
		{
			InitPolygonBy(pZone,pRegBase);//->GetPolygon(section));
		}
	}	
	
	// check if last point == first
	/*
	pt0 = pBase->GetData()[0];
	for(DWORD i = pBase->GetSize();i>0;i--)
	{
		pt1 = pBase->GetData()[i-1];
		if(pt0 == pt1)		
			pBase->DeleteAt(i-1);
		else break;
	}*/
	//CheckInRaster(*pRegBase,m_pa->m_destRect);//get back when z is no longer reset
	
	for(int n = 0; n< pRegBase->GetPolygonsCount(); n++)
	{
		rgZone->AddPolygon(pRegBase->GetPolygon(n));	
	}
	rgZone->SortBySquare(FALSE);	
	
	std::vector<CIC_Point3DD> vPoints;

	CIC_RegionCmx rgPolyline;

	FillObject(*rgZone, rgPolyline);

	delete rgZone;
	
}
///////////////////////////////////////////////////////////////////////////////////
//////////////////////////// DRAW ZONE ///////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////////
//////////////       FILL OBJECT ////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
void CDEM::FillObject(CIC_RegionCmx &rgPolygon1, CIC_RegionCmx &rgPolygon2, CIC_Point3DD *pt)
{

	ConvertToPixels(rgPolygon1);
	ConvertToPixels(rgPolygon2);

	std::vector<CIC_Point3DD> points;

	if (pt)
	{
		ConvertToPixels(*pt);
		points.push_back(*pt);
	}

	FillObjectCGAL(rgPolygon1, rgPolygon2, points);
}
/////////////////////////////////////////////////////////////////////////////
void CDEM::FillObject(CIC_RegionCmx &rgPolygon1)
{
	CIC_RegionCmx rgPolygon2;
	//tor<CIC_Point3DD> points;

	FillObject(rgPolygon1, rgPolygon2, NULL);
}
/////////////////////////////////////////////////////////////////////////////
void CDEM::FillObject(CIC_RegionCmx &rgPolygon1, CIC_Point3DD *pt)
{
	CIC_RegionCmx rgPolygon2;

	FillObject(rgPolygon1, rgPolygon2, pt);
}
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////


bool CDEM::ExternInterpolation(double dX, double dY, double &dZ)
{
	if(pINT) return pINT->Interpolate(dX,dY,dZ);
	return false;
}

///////////////////////////////////////////////////
void CDEM::FillObjectCGAL(CIC_RegionCmx &rgPolygon1, CIC_RegionCmx &rgPolygon2, std::vector<CIC_Point3DD> &vPoints)
{
	CTriangulator INT;
	IC_POINT3DD points[3];
		
	pINT = &INT; 

#ifdef _DEBUG
	if(this->m_iterateDraw) 	// for dedug purposes
		m_iterateCount++;
#endif
	/*
	std::vector<CIC_Point3DD> vPoints1,vPoints2;
	for(int sec=0;sec<rgPolygon1.GetPolygonsCount();sec++)
		for(int i = 0;i<rgPolygon1.GetPolygon(sec)->GetSize();i++)
			vPoints1.push_back(rgPolygon1.GetPolygon(sec)->GetData()[i]);

	for(int sec=0;sec<rgPolygon2.GetPolygonsCount();sec++)
		for(int i = 0;i<rgPolygon2.GetPolygon(sec)->GetSize();i++)
			vPoints2.push_back(rgPolygon2.GetPolygon(sec)->GetData()[i]);
			*/

	INT.CreatePolygonTriangulation(rgPolygon1, rgPolygon2, vPoints);//, rgPolyline, vPoints);

	if(m_drawType == 0)
	{
		__int64 count = 0;
		for(CDT::Finite_faces_iterator fit = INT.GetTriangulation().finite_faces_begin(); fit != INT.GetTriangulation().finite_faces_end(); ++fit)		
			if(fit->info().in_domain()) count++;
				
		//SetProgress(1,_T("Drawing..."),count);		

		for(CDT::Finite_faces_iterator fit = INT.GetTriangulation().finite_faces_begin(); fit != INT.GetTriangulation().finite_faces_end(); ++fit)
		{
			if(!fit->info().in_domain())
				continue;

			points[0].x = fit->vertex(0)->point().x() - I_OFFSET;
			points[0].y = fit->vertex(0)->point().y() - I_OFFSET;
		
			points[1].x = fit->vertex(1)->point().x() - I_OFFSET;
			points[1].y = fit->vertex(1)->point().y() - I_OFFSET;

			points[2].x = fit->vertex(2)->point().x() - I_OFFSET;
			points[2].y = fit->vertex(2)->point().y() - I_OFFSET;

			if(!m_externInterpolation) 
			{
				points[0].z = fit->vertex(0)->info();	
				points[1].z = fit->vertex(1)->info();	
				points[2].z = fit->vertex(2)->info();
			}
			/*
			if(points[0].z < 50 || points[1].z < 50  || points[2].z < 50) // temp
			{
				int b=0;
			}*/
						 
			this->FillTriangleP(points[0],points[1],points[2]);

			//Sleep(300);//temp

			//if(IncProgress()) break;
		}
	}
	else
	{	
		this->FillRectP(rgPolygon1.GetBoundRect());
	}
	pINT = NULL;
}

////////////////////////////////////////////////////////////////////////////////////////














