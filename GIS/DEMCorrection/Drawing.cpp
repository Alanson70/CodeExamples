#include "stdafx.h"
#include "fn_demcorrection.h"
#include "afxdialogex.h"
#include "dfi_RasterStream.h"
#include "dfi_RasterPROCS.h"

#include "math.h"

#include "DEM.h"

// import most common Eigen types 
#define EIGEN_DONT_VECTORIZE
#include <Eigen/Core>
#include <Eigen/LU>
#include <Eigen/SVD>

// import most common Eigen types 
using namespace Eigen;

#define min4(a,b,c,d)  min(a,min(b,min(c,d)))
#define max4(a,b,c,d)  max(a,max(b,max(c,d)))

#define min3(a,b,c)  min(a,min(b,c))
#define max3(a,b,c)  max(a,max(b,c))

PIXEL_ACCESS::PIXEL_ACCESS(CDEM *dem,int sourceRasterLayerNum, int destRasterLayerNum, CIC_Rect3DD *imageRect)
{		
	m_DEM = dem;
	pGetValueProc = NULL;
	pSetValueProc = NULL;

	Init(sourceRasterLayerNum, destRasterLayerNum, imageRect);

	dem->m_pa = this;
}


void PIXEL_ACCESS::Init(int sourceRasterLayerNum,int destRasterLayerNum, CIC_Rect3DD *imageRect)
{
	m_sourceRasterLayerNum = sourceRasterLayerNum;	
	m_destRasterLayerNum = destRasterLayerNum;

	Cdfi_Layer* pLayer;
	Cdfi_Raster *pRaster;
	//int m_raster=dem.m_pDocument->GetLayers()->GetLayerActive(IC_RASTER_CLASS_NAME);
	pLayer =  m_DEM->m_pDocument->GetLayers()->GetLayer(destRasterLayerNum);
	if (!pLayer) return;

	pRaster = pLayer->GetRaster();
	m_pDestImageInfo = pRaster->GetImageInfo();
	if(!pRaster->IsModeEdit())
		pRaster->RasterToEditMode(false,false);
	pDestRasterStream = new Cdfi_RasterStream(pRaster, 1);
	pSetValueProc = NULL;
	pSetValueProc = CRasterPROCS::PointerSetValueProc(m_pDestImageInfo->GetBandInfo(0)->PixelType);

	bDestRect.top = 0;
	bDestRect.bottom = (double)m_pDestImageInfo->GetNumBlocksHeight(0);
	bDestRect.left = 0;
	bDestRect.right = (double)m_pDestImageInfo->GetNumBlocksWidth(0);

	m_destBlockWidth = pRaster->GetBlockWidth();
	m_destBlockHeight = pRaster->GetBlockHeight();
	m_destBlockSize = m_destBlockWidth*m_destBlockHeight;

	m_destRect = m_pDestImageInfo->GetGeoInfoW()->GetBoundRect();
	//m_destRect = imageRect;
	
	if(m_sourceRasterLayerNum == m_destRasterLayerNum)
	{
		m_pSourceImageInfo = m_pDestImageInfo;
		pSourceRasterStream = pDestRasterStream;
		bSourceRect = bDestRect;	
		m_sourceBlockWidth = m_destBlockWidth;
		m_sourceBlockHeight = m_destBlockHeight;
		m_sourceBlockSize = m_destBlockSize;
		m_sourceRect  = m_destRect;
	}
	else
	{
		pLayer =  m_DEM->m_pDocument->GetLayers()->GetLayer(sourceRasterLayerNum);
		pRaster = pLayer->GetRaster();		
		if (!pLayer) return;
		pSourceRasterStream = new Cdfi_RasterStream(pRaster, 1);
		m_pSourceImageInfo = pRaster->GetImageInfo();
		bSourceRect.top = 0;
		bSourceRect.bottom = (double)m_pSourceImageInfo->GetNumBlocksHeight(0);
		bSourceRect.left = 0;
		bSourceRect.right = (double)m_pSourceImageInfo->GetNumBlocksWidth(0);

		m_sourceBlockWidth = pRaster->GetBlockWidth();
		m_sourceBlockHeight = pRaster->GetBlockHeight();
		m_sourceBlockSize = m_sourceBlockWidth * m_sourceBlockHeight;
		m_sourceRect = m_pSourceImageInfo->GetGeoInfoW()->GetBoundRect();
	}
	pGetValueProc = CRasterPROCS::PointerGetValueProc(m_pSourceImageInfo->GetBandInfo(0)->PixelType);
	//m_pSourceImageInfo->GetPixelRect(&m_sourceRect, &m_destOffset);
	m_pSourceImageInfo->GetPixelRect(&m_destRect,&m_destOffset); 
		
	m_uom = m_pSourceImageInfo->GetGeoInfoW()->GetGeoProjection()->GetUnit();

	if(imageRect == NULL)
		imageRect = &m_sourceRect;
	CIC_Rect64 newRect;
	m_pDestImageInfo->GetPixelRect(imageRect,&newRect); // window mode  - if m_sourceObj = 2 and full raster

	m_imageRect.left =		(double)max( newRect.left, 0);	
	m_imageRect.right =		(double)min( newRect.right, (m_pDestImageInfo->GetNumBlocksWidth()*m_destBlockWidth)-1);
	m_imageRect.top =		(double)max( newRect.top, 0);
	m_imageRect.bottom =	(double)min( newRect.bottom, (m_pDestImageInfo->GetNumBlocksHeight()*m_destBlockHeight)-1);

	switch(pRaster->GetPixelType(0))
	{
		case RE_SAMPLE_TYPE_UCHAR :
			maxColor = 255; 
			minColor = 0;
		break;
		case RE_SAMPLE_TYPE_CHAR :
			maxColor = 127; 
			minColor = -128;
		break;
		case RE_SAMPLE_TYPE_USHORT :
		case RE_SAMPLE_TYPE_ULONG :
			maxColor = 32000; 
			minColor = 0;
		break;
		default:
			maxColor = 32000;
			minColor = -32000;
		break;
	}
	
	ok = false;

	destXBlock = -1;
	destYBlock = -1;
	
	sourceXBlock = -1;
	sourceYBlock = -1;
}

PIXEL_ACCESS::~PIXEL_ACCESS()
{
	pDestRasterStream->Clear();
	delete pDestRasterStream;
	
	if(m_sourceRasterLayerNum != m_destRasterLayerNum)
	{
		pSourceRasterStream->Clear();
		delete pSourceRasterStream;
	}

	m_DEM->m_pa = NULL;
}

void PIXEL_ACCESS::init_interpolation(CIC_Point3DD point1, CIC_Point3DD point2)
{
	CIC_Point3DD point0;
	point0 = (point1 + point2);

	point0.x/=2;
	point0.y/=2;
	point0.z/=2;

	init_interpolation(point1,point0,point2);
}

void PIXEL_ACCESS::init_interpolation(CIC_Point3DD point0, CIC_Point3DD point1, CIC_Point3DD point2)
{
// interpolation coefficients calculation
	
	Matrix3d mA;
	Vector3d vX, vB;
	mA <<	point0.x, point0.y, 1,
			point1.x, point1.y, 1,
			point2.x, point2.y, 1;
	vB << point0.z, point1.z, point2.z;
	vX = mA.inverse() * vB;
	dInterA = vX[0];
	dInterB = vX[1];
	dInterC = vX[2];

	minInterColor = min(point0.z, min(point1.z, point2.z));
	maxInterColor = max(point0.z, max(point1.z, point2.z));
}

#ifdef _DEBUG
double minCompColor=-20000;
double maxCompColor=32000;
#endif

void PIXEL_ACCESS::put_pixel_in_block ( __int64 x, __int64 y,int fillFlag, double color) // need set_block before
{
	if(!ok) return;

	DWORD destPix = (DWORD)((m_destBlockWidth*(y-m_destBlockHeight*destYBlock)) +  ( x - m_destBlockWidth * destXBlock));
	if(destPix>= (DWORD)m_destBlockSize)
		destPix=0;	


	//double sourceColor = get_pixel_in(x, y);
	
	if(color <= LEVEL_FILL_AUTO) // > no change 
	{
		/*if(m_DEM->m_externInterpolation)
			m_DEM->ExternInterpolation((double)x, (double)y, color);
		else*/
		color = dInterA*x + dInterB*y + dInterC;	


		color = max(min(color, maxInterColor), minInterColor);
	}

	if(fillFlag == LEVEL_FILL_SET) // as is
		;
	else
	if (fillFlag == LEVEL_FILL_SUM) // // add
	{
		color = (color + get_pixel_in(x, y));//pGetValueProc((BYTE*)pSourceIBlock, srcPix));
	}
	else
	if (fillFlag == LEVEL_FILL_INT) // integrate
	{
		color = (color + get_pixel_in(x, y)) / 2;//pGetValueProc((BYTE*)pSourceIBlock, srcPix)) / 2;
	}
	else
	if (fillFlag == LEVEL_FILL_NO) // no-fill
	{
		return;
	}
#ifdef _DEBUG
	if(color<minCompColor || color>maxCompColor) // temp
	{
		int cc=0;
	}
#endif

	pSetValueProc((BYTE*)pDestIBlock, destPix, max(min(color,maxColor),minColor));		

};


void PIXEL_ACCESS::put_pixel ( __int64 x, __int64 y,int fillFlag, double color) // slow function - calculate block, set and write pixel in
{
	__int64 bX = (int)(x/m_destBlockWidth);
	__int64 bY = (int)(y/m_destBlockHeight);

	if(bY >= bDestRect.top && bY <= bDestRect.bottom && bX >= bDestRect.left && bX <= bDestRect.right);

	else return;

	if(destXBlock!=bX && destYBlock !=bY)
	{
		pDestIBlock = pDestRasterStream->Get_lpBlock(0, 0, 0, bX, bY);
		destXBlock = bX;
		destYBlock = bY;
	}	
		
	DWORD destPix = (DWORD)((m_destBlockWidth*(y-m_destBlockHeight*destYBlock)) +  ( x - m_destBlockWidth * destXBlock));
	if(destPix>= (DWORD)m_destBlockSize)
		destPix=0;	

	//double sourceColor = get_pixel_in(x, y);
	
	if(color <= LEVEL_FILL_AUTO) // > no change 
	{
		//if(m_DEM->m_externInterpolation)
		//	m_DEM->ExternInterpolation((double)x, (double)y, color);
		//else
			color = dInterA*x + dInterB*y + dInterC;
			color = max(min(color, maxInterColor), minInterColor);
	}

	if(fillFlag == LEVEL_FILL_SET) // as is
		;
	else
	if(fillFlag == LEVEL_FILL_SUM) // // add
		color = (color + get_pixel_in(x, y));//pGetValueProc((BYTE*)pSourceIBlock, srcPix));
	else
	if(fillFlag == LEVEL_FILL_INT) // integrate
		color = (color + get_pixel_in(x, y))/2;//pGetValueProc((BYTE*)pSourceIBlock, srcPix)) / 2;
	else
	if(fillFlag == LEVEL_FILL_NO) // no-fill
		return;	
	
	pSetValueProc((BYTE*)pDestIBlock, destPix, max(min(color,maxColor),minColor));		

};


bool PIXEL_ACCESS::set_block_in(__int64 x, __int64 y) // prepare block by kootdinates of pixel
{	
	__int64 bX,bY;

	bX = x/m_destBlockWidth;
	bY = y/m_destBlockHeight;

	if(destXBlock == bX && destYBlock == bY) return ok;
		
	destXBlock = bX;
	destYBlock = bY;
	ok = false;

	if(bY >= bDestRect.top && bY  <= bDestRect.bottom && bX >= bDestRect.left && bX <= bDestRect.right)

		ok = true;

	else return false;
	
	pDestIBlock = pDestRasterStream->Get_lpBlock(0, 0, 0, bX, bY);
	
	return ok;
	
}


bool PIXEL_ACCESS::set_block(__int64 bX, __int64 bY) // prepare block for writing pixel by blocks number
{	
	if(destXBlock == bX && destYBlock == bY) return ok;
		
	destXBlock = bX;
	destYBlock = bY;

	ok = false;

	if(bY >= bDestRect.top && bY <= bDestRect.bottom && bX >= bDestRect.left && bX <= bDestRect.right)

		ok = true;

	else 
		return false;
	
	pDestIBlock = pDestRasterStream->Get_lpBlock(0, 0, 0, bX, bY);
	
	return true;
}



double PIXEL_ACCESS::get_pixel_in(__int64 x, __int64 y) // first variant
{
	if (m_sourceRasterLayerNum != m_destRasterLayerNum)
	{
		__int64 bX, bY;

		x += m_destOffset.left;
		y += m_destOffset.top;

		bX = x / m_sourceBlockWidth;
		bY = y / m_sourceBlockHeight;

		if (sourceXBlock == bX && sourceYBlock == bY);
		else   // it have change block
		{
			sourceXBlock = bX;
			sourceYBlock = bY;

			if (sourceYBlock >= bSourceRect.top && sourceYBlock <= bSourceRect.bottom && sourceXBlock >= bSourceRect.left && sourceXBlock <= bSourceRect.right)

				pSourceIBlock = pSourceRasterStream->Get_lpBlock(0, 0, 0, sourceXBlock, sourceYBlock);
			else
				return 0;
		}
	}
	else
	{
		sourceXBlock = destXBlock; 
		sourceYBlock = destYBlock;

		pSourceIBlock = pDestIBlock;
	}
	
	DWORD srcPix = (DWORD)((m_sourceBlockWidth*(y - m_sourceBlockHeight * sourceYBlock)) + (x - m_sourceBlockWidth * sourceXBlock));
	if (srcPix >= (DWORD)m_sourceBlockSize)
		srcPix = 0;
		
	//double color = pSourceIBlock[srcPix];
	double color = pGetValueProc((BYTE*)pSourceIBlock, srcPix);

	return color;
	
}



bool PIXEL_ACCESS::get_pixel ( __int64 x, __int64 y,  double &color) // another variant of get_pixel
{
	x += m_destOffset.left;
	y += m_destOffset.top;

	int bX = (int)(x/m_sourceBlockWidth);
	int bY = (int)(y/m_sourceBlockHeight);

	if (sourceXBlock == bX && sourceYBlock == bY);
	else // it have change block
	{
		if (bY >= bSourceRect.top && bY <= bSourceRect.bottom && bX >= bSourceRect.left && bX <= bSourceRect.right);
		else
			return false;

		pSourceIBlock = pSourceRasterStream->Get_lpBlock(0, 0, 0, bX, bY);
	}

	DWORD iPix = (DWORD)((m_sourceBlockWidth*(y-m_sourceBlockHeight*bY)) +  ( x - m_sourceBlockWidth * bX));
	if(iPix>= (DWORD)m_sourceBlockSize)
		iPix=0;	

	color = pGetValueProc((BYTE*)pSourceIBlock, iPix);

	return true;

};
///////////////////////////////////////////////////////////////////////////



























///////////////////////////////////////////////////////////////////////////////////////
void CDEM::DrawLine(IC_POINT3DD point1, IC_POINT3DD point2, int fillFlag)
{		
	ConvertToPixels(point1);
	ConvertToPixels(point2);

	DrawLineP(point1,point2,fillFlag);

	return;


}
///////////////////////////////////////////////////////////////////////////////////////


void CDEM::DrawLineP(IC_POINT3DD point1, IC_POINT3DD point2, int fillFlag) // in clients RECT
{		
	// draw out points from first to last pixel!!!!
	
	m_pa->init_interpolation(point1,point2);

			
	if(point1.x > point2.x)
		std::swap(point1,point2);

//	point1.x = floor(point1.x);
//	point2.x = floor(point2.x);	
		
//	point1.y = floor(point1.y);
//	point2.y = floor(point2.y);

	double colorValue;
	double colorGrad; 
	double TAN;
	__int64 x,y,xN;	


	if(point1.x == point2.x && point1.y == point2.y) // !!!!!!!!!!!!! no width!!!
	{
		// is not width
	}
	else
	if(abs(point2.x-point1.x)<=1.0  && point1.y != point2.y) // vertical line strongly
	{		
		if(point2.y<point1.y) 

			std::swap(point1,point2);

		colorValue = point1.z;

		colorGrad = (point2.z - point1.z) / (double)(point2.y-point1.y);

		x = (__int64)point1.x;
		
		for(int y=(int)point1.y;y<=(int)point2.y; y++) 
		{
			if(x >= m_pa->m_imageRect.left && x <= m_pa->m_imageRect.right && y >= m_pa->m_imageRect.top && y<= m_pa->m_imageRect.bottom)
			{
				if(m_pa->set_block_in(x,y))
				{
#ifdef _DEBUG
					if(m_oneColor) colorValue = 255;
#endif

					m_pa->put_pixel(x,y,fillFlag,colorValue);
				}
			}

			colorValue+=colorGrad;

		}
	}
	else
	if(abs(point2.x-point1.x)>=abs(point2.y-point1.y))  // horizontal draw is prefered ok!!!
	{				
		if(point1.x > point2.x)
			std::swap(point1,point2);

		TAN = (point2.y-point1.y) / (point2.x-point1.x);

		point1.x = floor(point1.x);
		point2.x = floor(point2.x);	
		
		colorValue = point1.z;


		colorGrad = (point2.z - point1.z) / (point2.x-point1.x);
				
		xN = (__int64)(point2.x-point1.x);
		
		for(__int64 i=0;i<=xN; i++) 
		{
			x = (__int64)(point1.x + i);				
			
			y = (int)floor(point1.y + (i * TAN ));
			
			if(x >= m_pa->m_imageRect.left && x <= m_pa->m_imageRect.right && y >= m_pa->m_imageRect.top && y<= m_pa->m_imageRect.bottom)
			{			
				if(m_pa->set_block_in(x,y))
				{			
#ifdef _DEBUG
					if(m_oneColor) colorValue = 255;
#endif

					m_pa->put_pixel_in_block(x,y,fillFlag,colorValue);
				}
			}

			colorValue=point2.z - (point2.x-x)*colorGrad;
			

		}
		
	}		
	else // vertical draw prefered
	if(abs(point2.y-point1.y)>=abs(point2.x-point1.x))  // horizontal draw is prefered ok!!!
	{				
		if(point1.y > point2.y)
			std::swap(point1,point2);
		

		colorValue = point1.z;

		TAN = (point2.x-point1.x) / (point2.y-point1.y);

		point1.y = floor(point1.y);
		point2.y = floor(point2.y);

		colorGrad = (point2.z - point1.z) / (point2.y-point1.y);
				
		xN = (__int64)(point2.y-point1.y);
		
		for(__int64 i=0;i<=xN; i++) 
		{
			y = (__int64)(point1.y + i);				
			
			x = (int)floor(point1.x + (i * TAN ));
			
			if(x >= m_pa->m_imageRect.left && x <= m_pa->m_imageRect.right && y >= m_pa->m_imageRect.top && y<= m_pa->m_imageRect.bottom)
			{			
				if(m_pa->set_block_in(x,y))
				{			
#ifdef _DEBUG
					if(m_oneColor) colorValue = 255;
#endif

					m_pa->put_pixel_in_block(x,y,fillFlag,colorValue);
				}
			}

			colorValue=point2.z - (point2.y-y)*colorGrad;
			

		}
		
	}		
		/*
	if(abs(point2.y-point1.y)>=1.0)  
	{
		TAN = (point2.y-point1.y) / (point2.x-point1.x);

		colorGrad = (point2.z - point1.z) / (point2.y-point1.y);
		
		xN = (__int64)(point2.x-point1.x);
		
		for(__int64 i=0;i<=xN; i++) 
		{
			x = (__int64)(point1.x + i);				

			//yN = (int)(point1.y + (int)(i * TAN ));

			//sign=(yN>y0)?1:-1;

			//y = y0;

			for(int j = 0; j<abs(yN-y0); j++)
			{		
				if(x >= m_pa->m_imageRect.left && x <= m_pa->m_imageRect.right && y >= m_pa->m_imageRect.top && y<= m_pa->m_imageRect.bottom)
				{
					if(m_pa->set_block_in(x,y))
					{				
						if(m_oneColor) colorValue = 255;

						m_pa->put_pixel_in_block(x,y,fillFlag,colorValue);
					}
				}
				
				colorValue=point2.z - (point2.y-y)*colorGrad;

				y += sign;
			}
			y0 = yN;



		}
		*/
		// remained nodrawed part sometime
		/*
		yN = (int)point2.y;

		for(int j = 0; j<= abs(yN-y0); j++)
		{	
			if(x >= m_pa->m_imageRect.left && x <= m_pa->m_imageRect.right && y >= m_pa->m_imageRect.top && y<= m_pa->m_imageRect.bottom)
			{
				if(m_pa->set_block_in(x,y))
				{

					if(m_oneColor) colorValue = 255;			

					m_pa->put_pixel(x,y,fillFlag,colorValue);
				}
			}

			colorValue=point2.z - (point2.y-y)*colorGrad;

			y += sign;
		}*/
		
	
	this->UpdateRaster(m_pa->m_destRasterLayerNum);
	

}

/////////////////////////////////////////////////////////////////////////////////

















///////////////////////////////////////////////////////////////////////////////////////
void CDEM::FillTriangle(CIC_PolygonD *mPol)
{
	FillTriangle(mPol->GetData()[0],mPol->GetData()[1],mPol->GetData()[2]);
}
///////////////////////////////////////////////////////////////////////////////////////

void CDEM::FillTriangle(IC_POINT3DD point0, IC_POINT3DD point1, IC_POINT3DD point2, int fillFlag)
{
	ConvertToPixels(point0);
	ConvertToPixels(point1);
	ConvertToPixels(point2);

	FillTriangleP(point0,point1,point2,fillFlag);		

}

///////////////////////////////////////////////////////////////////////////////////////

void CDEM::FillTriangleP(IC_POINT3DD point0, IC_POINT3DD point1, IC_POINT3DD point2, int fillFlag)
{
	
	if(m_drawScelet) 
	{	
		DrawTriangleP(point0,point1,point2);
		return;
	}

	if(m_relief)
		fillFlag = LEVEL_FILL_SUM; // summ

	switch(m_triangleDrawType)
	{
		case 0 :
			FillTriangleByOblique(point0,point1,point2,fillFlag);
		break;
		case 1 :
			FillTriangleByLines(point0,point1,point2,fillFlag);
		break;
		case 2 :
			FillTriangleOptimized(point0,point1,point2,fillFlag);
		break;

	}

}
///////////////////////////////////////////////////////////////////////////////////////

void CDEM::DrawTriangle(IC_POINT3DD geoPoint0, IC_POINT3DD geoPoint1, IC_POINT3DD geoPoint2)
{
	// convert to client
	//CIC_ImageInfo * pImageInfo = NULL;
	//Cdfi_Layer* pLayer;
	//Cdfi_Raster *pRaster;

	//int m_raster=m_pDocument->GetLayers()->GetLayerActive(IC_RASTER_CLASS_NAME);
	//pLayer = m_pDocument->GetLayers()->GetLayer(m_rasterLayerNum);

	//pRaster = pLayer->GetRaster();
	//pImageInfo = pRaster->GetImageInfo();
	
	CIC_Point3DD point0,point1,point2;	
	CIC_Point3DD newPoint1,newPoint2;
	
	m_pa->m_pDestImageInfo->GetPixelXY((CIC_Point3DD *)&geoPoint0,&point0);
	m_pa->m_pDestImageInfo->GetPixelXY((CIC_Point3DD *)&geoPoint1,&point1);
	m_pa->m_pDestImageInfo->GetPixelXY((CIC_Point3DD *)&geoPoint2,&point2);
	point0.z=geoPoint0.z;
	point1.z=geoPoint1.z;
	point2.z=geoPoint2.z;

	DrawTriangleP(point0,point1,point2);

	
	
}

///////////////////////////////////////////////////////////////////////////////////////

void CDEM::DrawTriangleP(IC_POINT3DD point0, IC_POINT3DD point1, IC_POINT3DD point2)
{

	DrawLineP(point0,point1);
	DrawLineP(point1,point2);
	DrawLineP(point2,point0);	
	
}

///////////////////////////////////////////////////////////////////////////////////////
void CDEM::FillTriangleByOblique(IC_POINT3DD point0, IC_POINT3DD point1, IC_POINT3DD point2, int fillFlag) // filling lines are oblique
{
	/*CIC_ImageInfo * pImageInfo = NULL;
	Cdfi_Layer* pLayer;
	Cdfi_Raster *pRaster;
		
	int m_raster=m_pDocument->GetLayers()->GetLayerActive(IC_RASTER_CLASS_NAME);
	pLayer = m_pDocument->GetLayers()->GetLayer(m_raster);

	pRaster = pLayer->GetRaster();
	pImageInfo = pRaster->GetImageInfo();
	*/
	
	//CIC_Point3DD point0,point1,point2;	
	CIC_Point3DD newPoint;

	// search for wide side	
	double wideSide = sqrt (pow(point1.x-point2.x,2)+pow(point1.y-point2.y,2));
	double side = 0;
	int topPoint=0;
	
	side = sqrt (pow(point0.x-point2.x,2)+pow(point0.y-point2.y,2));

	if(side > wideSide)
	{
		wideSide = side;
		topPoint = 1;
	}
	side = sqrt (pow(point0.x-point1.x,2)+pow(point0.y-point1.y,2));
	if(side > wideSide)	
		topPoint = 2;

	if(topPoint==1)
	{
		newPoint = point0;
		point0 = point1;
		point1 = newPoint;
	}
	else
	if(topPoint==2)
	{
		newPoint = point0;
		point0 = point2;
		point2 = newPoint;
	}
	
	double TAN;
	double dxColor;
		
	if(abs(point2.x - point1.x) >= abs(point2.y - point1.y))
	{
		TAN = (point2.y - point1.y) / (point2.x - point1.x);

		dxColor = (point2.z - point1.z) / abs(point2.x - point1.x);

		int sign=(point2.x > point1.x)?1:-1;

		for(int i=0;i<=abs(point2.x - point1.x);i++)
		{
			newPoint.x = point1.x + i*sign;
			newPoint.y = point1.y + TAN * (i)*sign;
			newPoint.z = point1.z + dxColor*i;

			DrawLineP(point0,newPoint);
		}
	}
	else
	{		
		TAN = (point2.x - point1.x) / (point2.y - point1.y);

		dxColor = (point2.z - point1.z) / abs(point2.y - point1.y);

		int sign=(point2.y > point1.y)?1:-1;

		for(int i=0;i<=abs(point2.y - point1.y);i++)			
		{
			newPoint.y = point1.y + i*sign;
			newPoint.x = point1.x + TAN * (i)*sign;
			newPoint.z = point1.z + dxColor*i;

			DrawLineP(point0,newPoint);
		}
	}
	
	
}
///////////////////////////////////////////////////////////////////////////////////////
void CDEM::FillTriangleByLines(IC_POINT3DD point0, IC_POINT3DD point1, IC_POINT3DD point2, int fillFlag)
{	
	point0.x = floor(point0.x);
	point1.x = floor(point1.x);
	point2.x = floor(point2.x);
	point0.y = floor(point0.y);
	point1.y = floor(point1.y);
	point2.y = floor(point2.y);
	// horizontal building - maybe quickly
	// search for left and right point - p0 - p2
	if(point1.y < point0.y ) std::swap(point1,point0);
	if(point2.y < point0.y ) std::swap(point2,point0);
	if(point1.y > point2.y ) std::swap(point1,point2);
		
	double TAN0 = 0;
	bool noTAN=0;
	double colorGrad0 = 0;
	double TAN = 0;
	double colorGrad = 0;
	IC_POINT3DD newPoint1,newPoint2;

	//int temp = -1;

	if(abs(point2.y - point0.y) <1.0 ) 
	{
		//DrawLineP(point0,point1);
		return;
	}
	
	TAN0 = (point2.x - point0.x) / (point2.y - point0.y);
	colorGrad0 = (point2.z - point0.z) / (point2.y - point0.y);
	// circle for interval point0-point1
	if(abs(point1.y - point0.y) >=1.0)
	{
		TAN = (point1.x - point0.x) / (point1.y - point0.y);
		colorGrad = (point1.z - point0.z) / (point1.y - point0.y);

		for(int i=0;i<=(point1.y - point0.y);i++)
		{		
			newPoint1.y = point0.y +i;
			newPoint1.x = point0.x + TAN0 * i;
			newPoint1.z = point0.z + i*colorGrad0;

			newPoint2.y = point0.y +i;
			newPoint2.x = point0.x + TAN * i;
			newPoint2.z = point0.z + i*colorGrad;

			if(newPoint1.x > newPoint2.x)
				std::swap(newPoint1,newPoint2);
			newPoint2.x-=1;

			newPoint1.x = floor(newPoint1.x);
			newPoint2.x = floor(newPoint2.x);

			if(newPoint2.x >= newPoint1.x)
				DrawLineP(newPoint1,newPoint2,fillFlag);

		}
	}
	//else	
	//	DrawLineP(point0,point1);
	
	
	// circle for interval point1-point2
	
	if(abs((1+point1.y) - point2.y) >= 1.0)
	{
		TAN = (point2.x - point1.x) / (point2.y - point1.y);
		colorGrad = (point2.z - point1.z) / (point2.y - point1.y);
		int i0 = (int)(point1.y - point0.y);
		for(int i=1;i<=(point2.y - point1.y);i++) // 1 - because this line was print in previous circle
		{	
			newPoint1.y = point1.y +i;
			newPoint1.x = (point0.x + TAN0 * (i + i0));
			newPoint1.z = point0.z + (i + i0)*colorGrad0;

			newPoint2.y = point1.y +i;
			newPoint2.x = point1.x + TAN * i;
			newPoint2.z = point1.z + i*colorGrad;

			if(newPoint1.x > newPoint2.x)
				std::swap(newPoint1,newPoint2);
			newPoint2.x-=1;
			
			newPoint1.x = floor(newPoint1.x);
			newPoint2.x = floor(newPoint2.x);

			if(newPoint2.x >= newPoint1.x)
				DrawLineP(newPoint1,newPoint2,fillFlag);

		}
	}
	//else		
		//DrawLineP(point1,point2);
	
	
}



///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////



void CDEM::FillTriangleOptimized(IC_POINT3DD point0, IC_POINT3DD point1, IC_POINT3DD point2, int fillFlag)
{

	CIC_Rect64 rcBlocks;
	
	point0.x = floor(point0.x)+1;
	point1.x = floor(point1.x)+1;
	point2.x = floor(point2.x)+1;
	point0.y = floor(point0.y);
	point1.y = floor(point1.y);
	point2.y = floor(point2.y);

	m_pa->init_interpolation(point1,point0,point2);
	
	// search for left and right point - p0 - p2
	if(point1.y < point0.y ) std::swap(point1,point0);
	if(point2.y < point0.y ) std::swap(point2,point0);
	if(point1.y > point2.y ) std::swap(point1,point2);
	
		
	// client
		/*
	rcBlocks.top = (int)max(min(min(point0.y,min(point1.y,point2.y))/m_pa->m_destBlockHeight,m_pa->m_pDestImageInfo->GetNumBlocksHeight()-1),0);
	rcBlocks.bottom = (int)max(min(max(point0.y,max(point1.y,point2.y))/m_pa->m_destBlockHeight,m_pa->m_pDestImageInfo->GetNumBlocksHeight()-1),0);
	rcBlocks.left = (int)max(min(min(point0.x,min(point1.x,point2.x))/m_pa->m_destBlockWidth,m_pa->m_pDestImageInfo->GetNumBlocksWidth()-1),0);
	rcBlocks.right = (int)max(min(max(point0.x,max(point1.x,point2.x))/m_pa->m_destBlockWidth,m_pa->m_pDestImageInfo->GetNumBlocksWidth()-1),0);
	*/
	/*
	rcBlocks.top =	  (int)max(0,	min(	max(min3(point0.y,point1.y,point2.y),m_pa->m_imageRect.top)/   m_pa->m_destBlockHeight,m_pa->m_pDestImageInfo->GetNumBlocksHeight()-1));
	rcBlocks.bottom = (int)max(0,	min(	min(max3(point0.y,point1.y,point2.y),m_pa->m_imageRect.bottom)/m_pa->m_destBlockHeight,m_pa->m_pDestImageInfo->GetNumBlocksHeight()-1));
	rcBlocks.left =   (int)max(0,	min(	max(min3(point0.x,point1.x,point2.x),m_pa->m_imageRect.left)/  m_pa->m_destBlockWidth,m_pa->m_pDestImageInfo->GetNumBlocksWidth()-1));
	rcBlocks.right =  (int)max(0,	min(	min(max3(point0.x,point1.x,point2.x),m_pa->m_imageRect.right)/ m_pa->m_destBlockWidth,m_pa->m_pDestImageInfo->GetNumBlocksWidth()-1));
	*/
	rcBlocks.top =	  (int)max(min3(point0.y,point1.y,point2.y),m_pa->m_imageRect.top)/   m_pa->m_destBlockHeight;
	rcBlocks.bottom = (int)min(max3(point0.y,point1.y,point2.y),m_pa->m_imageRect.bottom)/m_pa->m_destBlockHeight;
	rcBlocks.left =   (int)max(min3(point0.x,point1.x,point2.x),m_pa->m_imageRect.left)/  m_pa->m_destBlockWidth;
	rcBlocks.right =  (int)min(max3(point0.x,point1.x,point2.x),m_pa->m_imageRect.right)/ m_pa->m_destBlockWidth;
	


// Drawing
	int bw0,bwN,bh0,bhN; // numbers of blocks
	int h,w; // block iterators
	double xMin,xMax;//,yMin,yMax; // limits
	double y0,yN;  // start koordinates

	double x1,x2,x,y;
	double TAN0 = 0; // of longest side
	double TAN = 0;   // another sides	
	double color=0;
	//double colorGrad = 0; // another sides
	/*
	if(point2.y == point0.y) // de-facto line 
	{
		DrawLineP(point1,point2);
		return; // 
	}
	*/
		
	bw0 = (int)(rcBlocks.left);///m_destBlockWidth);
	bwN = (int)(rcBlocks.right);///m_destBlockWidth);
	bh0 = (int)(rcBlocks.top);///m_destBlockHeight);
	bhN = (int)(rcBlocks.bottom);///m_destBlockHeight);
	
	TAN0 = (point2.x - point0.x) / (point2.y - point0.y);	

	// circle for interval point0-point1	
	if(abs(point1.y - point0.y) >= 1.0)
	{
		TAN = (point1.x - point0.x) / (point1.y - point0.y);

		for( h = bh0; h <= bhN ; h ++)	
		{
			y0 = h*m_pa->m_destBlockHeight;
			yN = (h+1)*m_pa->m_destBlockHeight-1; // included

			y0 = (int) max(y0,point0.y);			
			yN = (int) min(yN,point1.y);

			y0 = max(y0,m_pa->m_imageRect.top);
			yN = min(yN,m_pa->m_imageRect.bottom);


			for( w = bw0; w <= bwN ; w++)
			{	
				m_pa->set_block(w,h);//pIBlock = pa.pRasterStream->Get_lpBlock(0, 0, 0, w, h);
							
				xMin = w*m_pa->m_destBlockWidth;
				xMax = (w+1)*m_pa->m_destBlockWidth;

				xMin = max(xMin,m_pa->m_imageRect.left);
				xMax = min(xMax,m_pa->m_imageRect.right);

				for(y = y0; y <= yN; y++)
				{					
					x1 = (point0.x + TAN0 * (y - point0.y)); 
					x2 = (point0.x + TAN * (y - point0.y));

					x1 = floor(x1);//min(xMax, max (xMin, x1))); // blocks limits
					x2 = floor(x2);//min(xMax, max (xMin, x2)));					

					if((x1<xMin && x2<xMin) || (x1>xMax && x2>xMax))  continue;

					x1 = min(xMax, max (xMin, x1)); // blocks limits
					x2 = min(xMax, max (xMin, x2));					

					if(x2 > x1)
					{
						x2-=1;
						if(x2 >= x1)
							for( x = x1;x<= x2 ; x++)
							{							
								m_pa->put_pixel_in_block((__int64)x,(__int64)y,fillFlag);
							}										
					}
					else
					{
						x1-=1;
						if(x1 >= x2)
							for( x = x2;x<= x1 ; x++)
							{
								m_pa->put_pixel_in_block((__int64)x,(__int64)y,fillFlag);					
							}										
					}
					
				}
			}
		}
	}


	if(abs(point1.y - point2.y) >= 1.0)
	{
		TAN = (point1.x - point2.x) / (point1.y - point2.y);

		for( h = bh0; h <= bhN ; h ++)	
		{
			y0 = h*m_pa->m_destBlockHeight;
			yN = (h+1)*m_pa->m_destBlockHeight-1; // included

			y0 = (int) max(y0,point1.y+1);			
			yN = (int) min(yN,point2.y);

			y0 = max(y0,m_pa->m_imageRect.top);
			yN = min(yN,m_pa->m_imageRect.bottom);

			for( w = bw0; w <= bwN ; w++)
			{	
				//pa.pIBlock = pa.pRasterStream->Get_lpBlock(0, 0, 0, w, h);
				m_pa->set_block(w,h);
							
				xMin = w*m_pa->m_destBlockWidth;
				xMax = (w+1)*m_pa->m_destBlockWidth;

				xMin = max(xMin,m_pa->m_imageRect.left);
				xMax = min(xMax,m_pa->m_imageRect.right);

				for(y = y0; y <= yN; y++)
				{					
					x1 = (point0.x + TAN0 * (y - point0.y)); 
					x2 = (point1.x + TAN * (y - point1.y));
										
					x1 = floor(x1);//min(xMax, max (xMin, x1))); // blocks limits
					x2 = floor(x2);//min(xMax, max (xMin, x2)));					

					if((x1<xMin && x2<xMin) || (x1>xMax && x2>xMax))  continue;

					x1 = min(xMax, max (xMin, x1)); // blocks limits
					x2 = min(xMax, max (xMin, x2));	

					if(x2 > x1)
					{
						
						x2-=1;
						if(x2 >= x1)
							for( x = x1;x<= x2 ; x++)
							{							
								m_pa->put_pixel_in_block((__int64)x,(__int64)y,fillFlag);
							}										
					}
					else
					{						
						x1-=1;
						if(x1 >= x2)
							for( x = x2;x<= x1 ; x++)
							{
								m_pa->put_pixel_in_block((__int64)x,(__int64)y,fillFlag);					
							}										
					}
					
				}
			}
		}
	}

		
	
	UpdateRaster(m_pa->m_destRasterLayerNum);

	
	
}

///////////////////////////////////////////////////////////////////////////








///////////////////////////////////////////////////////////////////////////////////////
void CDEM::FillRect(CIC_Rect3DD rcGeo) // filling by extern Extrapolation
{
	//IC_POINT3DD *pp=obj->GetData();
		
	CIC_ImageInfo * pImageInfo = NULL;
	Cdfi_Layer* pLayer;
	Cdfi_Raster *pRaster;
		
	//int m_raster=m_pDocument->GetLayers()->GetLayerActive(IC_RASTER_CLASS_NAME);
	pLayer = m_pDocument->GetLayers()->GetLayer(m_pa->m_destRasterLayerNum);

	pRaster = pLayer->GetRaster();

	if(!pRaster->IsModeEdit())
		pRaster->RasterToEditMode(false,false);

	pImageInfo = pRaster->GetImageInfo();

	// pixeltype	
	DWORD iBlockWidth, iBlockHeight, iBlockSize, L, iPix;
	CIC_Rect64 rcImage, rcBlocks;
	CIC_Point64 ptBlock;

	GETVALUEPROC pGetValueProc = NULL;
	pGetValueProc = CRasterPROCS::PointerGetValueProc(pImageInfo->GetBandInfo(0)->PixelType);
	
	SETVALUEPROC pSetValueProc = NULL;
	pSetValueProc = CRasterPROCS::PointerSetValueProc(pImageInfo->GetBandInfo(0)->PixelType);

	int pixType=pImageInfo->GetBandInfo(0)->PixelType;

	rcGeo.NormalizeGeoRect();

	iBlockWidth = pRaster->GetBlockWidth();
	iBlockHeight = pRaster->GetBlockHeight();
	iBlockSize = iBlockWidth*iBlockHeight;

	pImageInfo->GetPixelRect(&rcGeo, &rcImage);

	Cdfi_RasterStream rasterStream(pRaster, 1);
	// calc blocks under rect
	rcBlocks.top = rcImage.top/iBlockHeight;
	rcBlocks.bottom = rcImage.bottom/iBlockHeight;
	rcBlocks.left = rcImage.left/iBlockWidth;
	rcBlocks.right = rcImage.right/iBlockWidth;

	LPBYTE pIBlock;
	double pValue;

	
	CIC_Point64 pt;

	pValue = rcGeo.up;

	for(__int64 hb = rcBlocks.top;  (hb <= rcBlocks.bottom); hb++)
	{
		for (__int64 wb = rcBlocks.left;  (wb <= rcBlocks.right); wb++)
		{
			ptBlock.x = wb;
			ptBlock.y = hb;
							
			pIBlock = rasterStream.Get_lpBlock(0, 0, 0, wb, hb);
							
			__int64 hMin = max(0,(rcImage.top - hb*iBlockHeight));
			__int64 hMax = min(iBlockHeight, (rcImage.bottom - hb*iBlockHeight));
			//for(int h = 0; h < iBlockHeight; h++)
			for(__int64 h = hMin; h < hMax; h++)
			{
				L = (DWORD)(iBlockWidth*h);
				
				__int64 wMin = max(0,(rcImage.left - wb*iBlockWidth));
				__int64 wMax = min(iBlockWidth, (rcImage.right - wb*iBlockWidth));
				//for(int w = 0; w < iBlockWidth; w++)
				for(__int64 w = wMin; w < wMax; w++)
				{
					pt.y = hb*iBlockHeight + h;
					pt.x = wb*iBlockWidth + w;

					//if(HIT_TEST(rcImage,pt))
					{
						iPix = (DWORD)(L + w);

						if(ExternInterpolation((double)pt.x, (double)pt.y, pValue))
						//pValue = pGetValueProc((BYTE*)pIBlock, iPix);
							pSetValueProc((BYTE*)pIBlock, iPix, pValue);
					}
				}
					
			}

		}
	}
	
	UpdateRaster(m_pa->m_destRasterLayerNum);

	rasterStream.Clear();
	
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////






///////////////////////////////////////////////////////////////////////////////////////
void CDEM::FillRectP(CIC_Rect3DD rcImage) // filling by extern Extrapolation
{

	CIC_ImageInfo * pImageInfo = NULL;
	Cdfi_Layer* pLayer;
	Cdfi_Raster *pRaster;
		
	//int m_raster=m_pDocument->GetLayers()->GetLayerActive(IC_RASTER_CLASS_NAME);
	pLayer = m_pDocument->GetLayers()->GetLayer(m_pa->m_destRasterLayerNum);

	pRaster = pLayer->GetRaster();

	if(!pRaster->IsModeEdit())
		pRaster->RasterToEditMode(false,false);

	pImageInfo = pRaster->GetImageInfo();

	// pixeltype	
	DWORD iBlockWidth, iBlockHeight, iBlockSize, L, iPix;
	CIC_Rect64 rcBlocks;
	CIC_Point64 ptBlock;

	GETVALUEPROC pGetValueProc = NULL;
	pGetValueProc = CRasterPROCS::PointerGetValueProc(pImageInfo->GetBandInfo(0)->PixelType);
	
	SETVALUEPROC pSetValueProc = NULL;
	pSetValueProc = CRasterPROCS::PointerSetValueProc(pImageInfo->GetBandInfo(0)->PixelType);

	//int pixType=pImageInfo->GetBandInfo(0)->PixelType;

	iBlockWidth = pRaster->GetBlockWidth();
	iBlockHeight = pRaster->GetBlockHeight();
	iBlockSize = iBlockWidth*iBlockHeight;
	
	Cdfi_RasterStream rasterStream(pRaster, 1);
	// calc blocks under rect

	rcImage.NormalizeRect();

	rcBlocks.top = (__int64)(rcImage.top/iBlockHeight);
	rcBlocks.bottom = (__int64)(rcImage.bottom/iBlockHeight);
	rcBlocks.left = (__int64)(rcImage.left/iBlockWidth);
	rcBlocks.right = (__int64)(rcImage.right/iBlockWidth);
	/*
	rcBlocks.top = (int)max(min(min(point0.y,min(point1.y,point2.y))/pa.iBlockHeight,this->m_pImageInfo->GetNumBlocksHeight()),0);
	rcBlocks.bottom = (int)max(min(max(point0.y,max(point1.y,point2.y))/pa.iBlockHeight,this->m_pImageInfo->GetNumBlocksHeight()),0);
	rcBlocks.left = (int)max(min(min(point0.x,min(point1.x,point2.x))/pa.iBlockWidth,this->m_pImageInfo->GetNumBlocksWidth()),0);
	rcBlocks.right = (int)max(min(max(point0.x,max(point1.x,point2.x))/pa.iBlockWidth,this->m_pImageInfo->GetNumBlocksWidth()),0);
	*/
	LPBYTE pIBlock;
	double pValue;
	
	CIC_Point64 pt;

	pValue = rcImage.up;

	for(__int64 hb = rcBlocks.top;  (hb <= rcBlocks.bottom); hb++)
	{
		for (__int64 wb = rcBlocks.left;  (wb <= rcBlocks.right); wb++)
		{
			ptBlock.x = wb;
			ptBlock.y = hb;
							
			pIBlock = rasterStream.Get_lpBlock(0, 0, 0, wb, hb);
							
			__int64 hMin = (__int64)max(0,(rcImage.top - hb*iBlockHeight));
			__int64 hMax = (__int64)min(iBlockHeight, (rcImage.bottom - hb*iBlockHeight));
			//for(int h = 0; h < iBlockHeight; h++)
			for(__int64 h = hMin; h < hMax; h++)
			{
				L = (DWORD)(iBlockWidth*h);
				
				__int64 wMin = (__int64)max(0,(rcImage.left - wb*iBlockWidth));
				__int64 wMax = (__int64)min(iBlockWidth, (rcImage.right - wb*iBlockWidth));
				//for(int w = 0; w < iBlockWidth; w++)
				for(__int64 w = wMin; w < wMax; w++)
				{
					pt.y = hb*iBlockHeight + h;
					pt.x = wb*iBlockWidth + w;

					//if(HIT_TEST(rcImage,pt))
					{
						iPix = (DWORD)(L + w);

						if(ExternInterpolation((double)pt.x, (double)pt.y, pValue))
						//pValue = pGetValueProc((BYTE*)pIBlock, iPix);
							pSetValueProc((BYTE*)pIBlock, iPix, pValue);
					}
				}
					
			}

		}
	}
	
	UpdateRaster(m_pa->m_destRasterLayerNum);

	rasterStream.Clear();
	
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

