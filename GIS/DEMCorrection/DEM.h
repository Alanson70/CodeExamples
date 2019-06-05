
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
#include "dfi_RasterStream.h"
#include "dfi_RasterPROCS.h"

#include "demcorrection.h"

#include "Triangulator.h"
#include "XFunctions.h"



#define LEVEL_SOURCE_NONE   0
#define LEVEL_SOURCE_RASTER 1
#define LEVEL_SOURCE_VALUE  2

#define LEVEL_ACTION_NONE  0x00
#define LEVEL_ACTION_SET   0x10
#define LEVEL_ACTION_ADD   0x20
#define LEVEL_ACTION_SUB   0x30

#define LEVEL_FILL_NO	0
#define LEVEL_FILL_SET  1
#define LEVEL_FILL_INT  2
#define LEVEL_FILL_SUM  3
#define LEVEL_FILL_AUTO -32000

class PIXEL_ACCESS;

struct CDEM_ARGS
{
	//params-arguments
	BOOL m_rasterCut; // cutting destination new raster about object or selection
	BOOL m_rasterCopy; // do new raster
	int m_objectsSource; // 0 - all, 1 - choosen objects, 2 - selection 
	int m_levelSource; // 0 - level from z, 1 - level from attribure m_levelAttr, 2 - level from m_levelValue
	TCHAR m_levelAttr[50];
	TCHAR m_levelEditValue[50];
	//double m_level; // level 
	int m_reference; // 0 - absolute level, 1 - relative level
	BOOL m_zone; // use bufzone
	BOOL m_zoneGradient; // smouthing
	BOOL m_zoneRounding; // rounding - always true
	int m_zoneWidthSource; // 
	TCHAR m_zoneWidthAttr[50];
	TCHAR m_zoneWidthEditValue[50];
	BOOL m_optionZoneOnly;
	BOOL m_zoneFactor;// multiplier for full-width of rivers line			
	BOOL m_relief;
	int m_uom;
};


void DEM_ARGS_COPY(CDEM_ARGS *dst,CDEM_ARGS *src);






class CDEM : public CDEM_ARGS
{

private:

public : 
	CDEM(CDFI *m_pDfi);
	~CDEM();
	
	CDFI *m_pDfi;
	DEM_DATA *m_pData;
	Cdfi_Document* m_pDocument;

	// raster drawing single session structure
	PIXEL_ACCESS *m_pa; 
	
	// to restrict calls of UpdaTErASTER until the drawing is complete
	bool m_rasterUpdateLock;
	bool m_rasterUpdate;
	
	double m_zoneWidthGeo; // BUF ZONE RADIUS in choosen geo coodrs
	BOOL m_externInterpolation; // not use - for demostrations only

	double m_pixelOffsetX; // offset of pixels output
	double m_pixelOffsetY; // offset of pixels output

	int m_dialogLeft; // dialog start coordinates
	int m_dialogTop;

	CIC_Rect3DD m_selectedRect; // rect of active selection

	void  AccessAttributes(bool bWrite); // read-write init parameters
	bool SetDocument( Cdfi_Document* pDocument );
	void CheckLayersReady(bool &setFlag,bool &getFlag); // call to check ability to do correction
	virtual void OnChangeLayers()							{ }
	virtual int GetVectorLayerNum();
	virtual int GetRasterLayerNum();

	void UpdateRaster(int rasterLayerNum);
	void ClearRaster(); // for debug only
	BOOL CropRaster(CDFI *pDfi, Cdfi_Raster *pRaster, CIC_RegionCmx *pCropRegion, Cdfi_Raster *&pRasterOut); // copy to new raster with pCropRegion's size 
	void Rasterize(); // main function
	void ReadLevels();
	//void UndoRasterize();


	double ConvertUnitToGeo(DWORD sourceUom, double dRadius,  DWORD destUom);
	double ConvertUnitToGeo(DWORD sourceUom, double dRadius,CIC_Rect3DD *rcBoundObj,DWORD destUom);
	double GetBufferZoneWidth(__int64 objID); // from attribute

	bool GetAttribute(__int64 objID,CString attrStr,CString &value); // read to value
		
	bool ConvertToPixels(IC_POINT3DD &pt); // from geo to pixels
	bool ConvertToPixels(CIC_Point3DD &pt);
	bool ConvertToPixels(CIC_RegionCmx &reg);
	bool ConvertToPixels(CIC_PolygonD &pPolygon);
	
	void CheckPolygonInRect(CIC_RegionCmx &reg, CIC_Rect3DD vRect); // cut less parts of polygon
	void CheckPolylineInRect(CIC_RegionCmx &reg, CIC_Rect3DD vRect);// cut less parts of polyline
		// read level from raster or set from level argument
	void InitObject(Cdfi_VectorObject *pVectorObj, double level=0);
	void InitPoint(Cdfi_VectorPoint *, int flag, double level=0); // 0 - no init, 1 - from raster, 2 - summ with raster, 3 - subtract raster from value
	void InitPointGeo(IC_POINT3DD &point1, int flag, double level=0);
	void InitPointP(IC_POINT3DD &point1, int flag, double level=0); // in pixels
	void InitPolyline(Cdfi_VectorLine *pObj, int flag, double level=0);
	void InitPolygon(Cdfi_VectorPolygon *pObj, int flag, double level=0);
	void InitPolygon(CIC_PolygonD *pPol, int flag, double level=0); // geo
	void InitPolygonP(CIC_PolygonD *pPol, int flag, double level=0); // pixels
		// init polygons by neighbourhood figure
	void InitPolygonBy(CIC_RegionCmx *regTo, CIC_RegionCmx *regFrom, int nNearestPoints = 1);
	void InitPolygonBy(CIC_PolygonD *pZone, CIC_RegionCmx *reg, int nNearestPoints = 1);
	void InitPointBy(IC_POINT3DD &pt, CIC_RegionCmx *reg, int nNearestPoints = 2);
	
	void DrawObject(Cdfi_VectorObject *pVectorObj); // main drawing function

	void DrawPoint(Cdfi_VectorPoint *);
	void DrawPoint(IC_POINT3DD gpoint);
	void DrawPointP(IC_POINT3DD point);
	void DrawPolyline(Cdfi_VectorLine *pObj);
	void DrawPolygonContour(CIC_PolygonD *pPolygon);
	void DrawPolygon(Cdfi_VectorPolygon *pObj);
	// 
	void FillObject(CIC_RegionCmx &rgPolygon1);
	void FillObject(CIC_RegionCmx &rgPolygon1, CIC_RegionCmx &rgPolygon2, CIC_Point3DD *pt=NULL);
	void FillObject(CIC_RegionCmx &rgPolygon1, CIC_Point3DD *pt);

	void ZonePoint(CIC_Point3DD pt0);
	void ZonePolyline(CIC_RegionCmx *pRegBase);
	void ZonePolygonObject(CIC_RegionCmx *pRegBase);
	void ZonePolygon(CIC_RegionCmx *pRegBase);
	// Drawing.cpp of simple objects
	void DrawLine(IC_POINT3DD point1, IC_POINT3DD point2, int fillFlag = LEVEL_FILL_SET);
	void DrawLineP(IC_POINT3DD point1, IC_POINT3DD point2, int fillFlag = LEVEL_FILL_SET);
	void FillTriangle(CIC_PolygonD *mPol); 
	void FillTriangle(IC_POINT3DD point1, IC_POINT3DD point2, IC_POINT3DD point3, int fillFlag = LEVEL_FILL_SET); // 0 - No Draw, 1 - simple, 2 - integral,3 - adding, 4 - cutting
	void FillTriangleP(IC_POINT3DD point1, IC_POINT3DD point2, IC_POINT3DD point3, int fillFlag = LEVEL_FILL_SET); // 0 - No Draw, 1 - simple, 2 - integral
	void DrawTriangle(IC_POINT3DD point1, IC_POINT3DD point2, IC_POINT3DD point3);
	void DrawTriangleP(IC_POINT3DD point1, IC_POINT3DD point2, IC_POINT3DD point3);

	void FillTriangleByOblique(IC_POINT3DD point0, IC_POINT3DD point1, IC_POINT3DD point2, int fillFlag = 1);
	void FillTriangleByLines(IC_POINT3DD point0, IC_POINT3DD point1, IC_POINT3DD point2, int fillFlag = 1);
	void FillTriangleOptimized(IC_POINT3DD point1, IC_POINT3DD point2, IC_POINT3DD point3, int fillFlag);
	
	bool ExternInterpolation(double dX, double dY, double &dZ);
	// block filling - too slowly variant - in 30 times!!!
	void FillRect(CIC_Rect3DD rcGeo);
	void FillRectP(CIC_Rect3DD rcRastr);
	
	// filling region by cgal triangulation and our filling
	CTriangulator *pINT;
	void FillObjectCGAL(CIC_RegionCmx &rgPolygon1, CIC_RegionCmx &rgPolygon2, std::vector<CIC_Point3DD> &points);
	
	// for debug
	bool m_iterateDraw; // draw for m_iterate count which increments
	int m_iterateCount;

	int m_drawType; // 0 - by triangles, 1 - by blocks
	int m_triangleDrawType; // 0 - oblique lines, 1 - horizontal lines, 2 - pixels
	BOOL m_drawScelet; // draw scelet of polygon
	
	BOOL m_noFill; // no fill polygon - only sides	
	BOOL m_oneColor; // single color for all lines = 255


};

////////////////////////////////////////////////////////////////////////////////////////////


class PIXEL_ACCESS /* class for access to pixels of pair rasters - source and destination */
{
private:
	CDEM *m_DEM;

	bool ok;

	double dInterA;	// interpolation coefficients
	double dInterB;
	double dInterC;
	
	__int64 sourceXBlock; // current num of block for reading
	__int64 sourceYBlock;

	__int64 destXBlock; // current num of block for writing
	__int64 destYBlock;

	double maxColor; // for limiting calculated color
	double minColor;
	double minInterColor; // for check color after interpolation
	double maxInterColor;
public:
	int m_sourceRasterLayerNum;
	int m_destRasterLayerNum;
	int m_vectorLayerNum;

	CIC_ImageInfo * m_pSourceImageInfo;
	CIC_ImageInfo * m_pDestImageInfo;

	int m_destBlockWidth;
	int m_destBlockHeight;
	int m_destBlockSize; 	
	
	int m_sourceBlockWidth;
	int m_sourceBlockHeight;
	int m_sourceBlockSize;

	CIC_Rect64 m_destOffset;
	CIC_Rect3DD m_destRect;
	CIC_Rect3DD m_sourceRect;
	CIC_Rect3DD m_imageRect;
	int m_uom;
	
	
private:
	LPBYTE pSourceIBlock;
	LPBYTE pDestIBlock;
	
	CIC_Rect3DD bSourceRect;
	CIC_Rect3DD bDestRect;

	SETVALUEPROC pSetValueProc; 
	GETVALUEPROC pGetValueProc;


	Cdfi_RasterStream *pSourceRasterStream;
	Cdfi_RasterStream *pDestRasterStream;

//	double maxColor;//temp

	//double x1,x2,x3,y1,y2,y3,z1,z2,z3;

	void Init(int sourceRasterLayerNum,int destRasterLayerNum, CIC_Rect3DD *imageRect);
public:
	PIXEL_ACCESS(CDEM *dem, int sourceRasterLayerNum, int destRasterLayerNum, CIC_Rect3DD *imageRect);
	~PIXEL_ACCESS();


	void init_interpolation(CIC_Point3DD point1, CIC_Point3DD point2);
	void init_interpolation(CIC_Point3DD point1, CIC_Point3DD point2, CIC_Point3DD point3);
	//void put_pixel ( __int64 x, __int64 y, __int64 w, __int64 h, double &color,int fillFlag); // need set block before
	void put_pixel_in_block ( __int64 x, __int64 y,int fillFlag, double color = LEVEL_FILL_AUTO); // need set_block before
	void put_pixel ( __int64 x, __int64 y,int fillFlag,  double color = LEVEL_FILL_AUTO);// slow function
	bool get_pixel ( __int64 x, __int64 y, double &color);
	//void set_source_block(__int64 w, __int64 h);
	//void set_dest_block(__int64 w, __int64 h);
	bool set_block_in(__int64 x, __int64 y);
	bool set_block(__int64 w, __int64 h);
	double get_pixel_in(__int64 x, __int64 y);
};

// check if obj in rect
bool IsIntersection(Cdfi_VectorObject *pVectorObject, CIC_Rect3DD *selRect);