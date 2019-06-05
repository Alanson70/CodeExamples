#pragma once

#include "StdAfx.h"
#include "dfi_vectorobjectstream.h"
#include "dfi_OverDraw.h"
#include "dfi_View.h"
#include "dfi_Layer.h"
#include "ctype.h"
#include "math.h"

void EndProgress();
BOOL IncProgress();
void SetProgress(CDFI *pDfi,int level,TCHAR *s, __int64 count);

struct CHECK_VALUE_DATA
{
	TCHAR s[250];
	int width;
	int prec;
	bool isSigned;
	int digits;
	bool result;
};

bool CheckFloatEdit(CEdit *edit,int fullWidth=14, int precision=6, bool isSign=true);

bool CheckFloatValue(CDFI *pDfi, IC_PARAM *pParam);
bool CheckFloat(TCHAR *ss,int width=14,int prec=6, bool isSigned = true);
bool CheckInt(TCHAR *ss,int digits=32,bool sign=true);

CString GetResourceString(UINT resID);
// access to visual objects texts
void SetText(CWnd *c, double v);
void SetText(CWnd *c, TCHAR *s);
void SetText(CWnd *c, CString s);
void SetTextByID(CWnd *obj,UINT id);
WCHAR *GetText(CWnd *c);
////////////////////////////////////////////////////////////////////////////
// Attr  - use for write or read parameters by ID with config file
void Attr(TCHAR *value, CString & wsItem, CString &sSection, Cdfi_Attributes *pAttributes, int maxLen, bool bWrite = false, BOOL bHide = false);
void AttrUnit(int & value, CString & wsItem, CString &sSection, CDFI *pDfi, bool bWrite = false, BOOL bHide = false);
void Attr(double & value, CString & wsItem, CString &sSection,Cdfi_Attributes *pAttributes,bool bWrite=false, BOOL bHide = false);
void Attr(CString & value, CString & wsItem, CString &sSection,Cdfi_Attributes *pAttributes,bool bWrite=false, BOOL bHide = false);
void Attr(bool & value, CString & wsItem, CString &sSection,Cdfi_Attributes *pAttributes,bool bWrite=false, BOOL bHide = false);
void Attr(int & value, CString & wsItem, CString &sSection, Cdfi_Attributes *pAttributes, bool bWrite = false, BOOL bHide = false);//, int minValue = std::numeric_limits<int>::lowest(), int maxValue = (std::numeric_limits<int>::max)() );
void Attr(__int64 & value, CString &wsItem, CString &sSection, Cdfi_Attributes *pAttributes, bool bWrite = false, BOOL bHide = false);//, __int64 minValue = std::numeric_limits<__int64>::lowest(), __int64 maxValue = (std::numeric_limits<__int64>::max)() );
void AttrTest(CString & wsItem, CString &sSection, Cdfi_Attributes *pAttributes, bool bWrite);
// calculations
double DISTANCE(IC_POINT3DD a, IC_POINT3DD b);
double ANGLE (IC_POINT3DD a, IC_POINT3DD center, IC_POINT3DD c);
double ANGLE (IC_POINT3DD a, IC_POINT3DD center);
double GRADUS (IC_POINT3DD a, IC_POINT3DD center, IC_POINT3DD c);
double GRADUS (IC_POINT3DD a, IC_POINT3DD center);
bool IsPointOnTriangle(IC_POINT3DD pt,IC_POINT3DD a, IC_POINT3DD b, IC_POINT3DD c);
bool IsPointInTriangle(IC_POINT3DD pt,IC_POINT3DD a, IC_POINT3DD b, IC_POINT3DD c);
double round(double x);
void DeleteAutoIntersections(CIC_PolygonD *p);
void DeleteAutoIntersections(CIC_RegionCmx &rgPolygon);
void DeleteRectIntersections(CIC_PolygonD *p, CIC_Rect3DD vRect );
void DeleteRectIntersections(CIC_RegionCmx &rgPolygon, CIC_Rect3DD vRect);


/////////////////////////////////
#include <vector>



///////////////////////////////////////////////////////

// debug time measurings
// use:
// call StartTimeMeasuring(_T("TestedFunctionName")); before function TestedFunctionName
// call StopTimeMeasuring(_T("TestedFunctionName")); after function TestedFunctionName
// in any time them pause programm and see global structer pTM
// to reset results -  pause programm and set pTM->m_resetFlag to 1
struct CTimeObject
{
public:
	TCHAR name[25];
	double average; // average time of function name
	double maximum; // maximum time
	double minimum; // minimum time
	double last; // last time
	int count;
	double sum;
	LARGE_INTEGER time1;
	LARGE_INTEGER time2;
	double freq;
};

class CTimeMeasuring
{
public:
	std::vector <CTimeObject> timeObjects;
	CTimeMeasuring(CDFI *pDfi);
	~CTimeMeasuring();
	void Start(TCHAR *name);
	void Stop(TCHAR *name);
	double GetLastTime(TCHAR *name);
	void Reset();
	void Save();

	int m_resetFlag;
	int m_saveFlag;
	
	CDFI *pDfi;

};

void CreateTimeMeasuring(CDFI *pDfi);
void StartTimeMeasuring(TCHAR *name);
void StopTimeMeasuring(TCHAR *name);
void SaveTimeMeasuring();
void ResetTimeMeasuring();
double GetLastTime(TCHAR *name);
//extern CTimeMeasuring *pTM;

void WriteToLog(CString &s);