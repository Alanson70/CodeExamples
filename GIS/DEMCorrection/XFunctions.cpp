
#include "StdAfx.h"
#include "XFunctions.h"

////////////////////////


WCHAR *GetText(CWnd *c)
{
	static WCHAR m_wndText[200];

	c->GetWindowTextW(m_wndText,199);

	return m_wndText;	
}

/////////////////////////////////////////////////////////////////////////////////

void SetText(CWnd *c, double v)
{
	static bool lock = false;

	if(lock) return;

	lock = true;

	CString str;

	str.Format(_T("%g"),v);

	c->SetWindowTextW(str);

	lock = false;

}

/////////////////////////////////////////////////////////////////////////////////
void SetText(CWnd *c, TCHAR *s)
{
	static bool lock = false;

	if(lock) return;

	lock = true;

	CString str;

	str.Format(_T("%s"),s);

	c->SetWindowTextW(str);

	lock = false;

}

/////////////////////////////////////////////////////////////////////////////////
void SetText(CWnd *c, CString str)
{
	static bool lock = false;

	if(lock) return;

	lock = true;	
	
	c->SetWindowTextW(str);

	lock = false;

}

/////////////////////////////////////////////////////////////////////////////////
void SetTextByID(CWnd *obj,UINT id)
{
	SetText(obj->GetDlgItem(id),GetResourceString(id));
}
/////////////////////////////////////////////////////////////////////////////////

bool CheckFloatValue(CDFI *pDfi, IC_PARAM *pParam)
{
	AFX_MANAGE_STATE( AfxGetStaticModuleState() );

	CHECK_VALUE_DATA *data = (CHECK_VALUE_DATA *)pParam->pArguments;

	if(!data) return false;

	data->result = CheckFloat(data->s,data->width,data->prec,data->isSigned);

	return true;
}



///////////////////////
bool CheckFloat(TCHAR *ss,int width,int prec, bool isSigned)
{
	int pointPos=-1; 

	CString s;

	s=ss;	

	for(int i=0;i<s.GetLength();i++)
	{ 
		if(pointPos!=-1 && ((i-pointPos)>prec)) 
		{
			s.Delete(i,1);
			continue;
		}

		if(i > width) 
		{
			s.Delete(i,1);
			continue;
		}

		if(s[i]=='.')
		{			
			if(prec == 0) 
			{
				s.Delete(i,1);
				continue;
			}
			if(pointPos==-1 && i!=-1) { pointPos=i; continue; }
		}
		else
		if(i==0 && (s[i]==L'-') && isSigned==true) continue;		
		else
		if((s[i]>=L'0') && (s[i]<=L'9')) continue;
		

		s.Delete(i,1);
	}

	if(s.GetLength()>14) { s.Truncate(14);}

	if(CString(ss) == s)

		return true;
	
	wcsncpy(ss,s.GetString(),20);

	return false;
}

///////////////////////
bool CheckInt(TCHAR *ss,int digits,bool sign)
{	
	//CString s;
	for(int i=0;i<wcslen(ss);i++)	
		if(i==0 && ss[i]=='-') continue;
		else
		if(!isdigit(ss[i])) { ss[i]=0;break; }
		

	double maxVal=powl((long)2, (long)(digits*8))-1;

	if(sign) maxVal/=2;

	long v=_wtol(ss);

	if(v<0) maxVal++;
	
	v=abs(v);

	if(abs(v)>maxVal) ss[0]=0;
		
	return true; 

	
}
////////////////////////////////////////////////////////////////


bool CheckFloatEdit(CEdit *edit,int fullWidth, int precision, bool isSign)
{
	static bool lock=false;
	bool retFlag = true;

	if(lock==true) return false;
		
	TCHAR *ss=GetText(edit);
	int selStart,selEnd;	
	edit->GetSel(selStart,selEnd);

	if(CheckFloat(ss,fullWidth,precision,isSign) == false)
	{
		SetText(edit,ss);
		edit->SetFocus();
		edit->SetSel(selStart-1,selEnd-1);
		retFlag = false;
	}
	
	lock=false;

	return retFlag;
}
///////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////
CString GetResourceString(UINT resID)
{
	HINSTANCE  hInstance = AfxGetStaticModuleState()->m_hCurrentResourceHandle;
	CString str;
	str.LoadString( hInstance, resID);
	return str;
}


void AttrTest(CString & wsItem, CString &sSection, Cdfi_Attributes *pAttributes, bool bWrite)
{
	if (bWrite) return;
	CString str;
	Cdfi_AttributeValue *attr, *attrNext;

	if (pAttributes->FindAttribute(sSection, wsItem) == FALSE)
	{
		attr = pAttributes->GetFirstItem();
		while (attr)
		{
			attrNext = pAttributes->GetNextItem(attr);

			str = attr->GetSectionName();
			if (str.Find(sSection, 0) >= 0)
				pAttributes->Remove(attr->GetName());
			attr = attrNext;
		};

	}
}

void AttrUnit(int & iUnitType, CString & wsItem, CString &sSection, CDFI *pDfi, bool bWrite, BOOL bHide)
{
	CString str;
	TCHAR cUnitName[MAX_GEOSTRING_SIZE];
	int iCode;
	int currIndex = -1;
	
	Cdfi_Attributes *pAttributes = pDfi->GetApp()->GetAttributes();
	Cdfi_Document *pDoc = pDfi->GetMainFrame()->GetActiveDocument();
	CGeoInfo *pGeoInfo = NULL;
		
	if(pDoc) pGeoInfo = pDoc->GetDocGeoInfo();

	CString sUnitName;
	int i, iUomCode;
	int Count = fnc_UOM::GetCountUom();

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	/// UnitType
	if (!pAttributes->FindAttribute(sSection, wsItem))
	{
		// 0. pixel
		//str.LoadString(AfxGetStaticModuleState()->m_hCurrentResourceHandle, IDS_UNIT_TYPE_PIXEL);
		//pAttributes->Add(sSection, wsItem, ATTRIBUTE_TYPE_ENUM, 0, 0)->AddEnumValue(0, str);

		//#ifndef _TAIS_EDITION
				
		for (i = 0; i<Count; i++)
		{
			iUomCode = fnc_UOM::GetCodeUom(i);
			if(pGeoInfo)
				pGeoInfo->GetUnitName(iUomCode, cUnitName);
			else
				fnc_UOM::GetUomName(iUomCode, cUnitName);
			str = cUnitName;
			pAttributes->Add(sSection, wsItem, ATTRIBUTE_TYPE_ENUM, 0, 0)->AddEnumValue(i + 1, str);
			if (iUnitType == iUomCode)
				currIndex = i;

		}		

		if(currIndex>=0) pAttributes->Item(sSection, wsItem)->SetEnumSel(currIndex, TRUE);
	}
	else
	{
		for (i = 0; i<Count; i++)
		{
			iUomCode = fnc_UOM::GetCodeUom(i);
			
			if (iUnitType == iUomCode)
			{
				currIndex = i;
				break;
			}
		}
	}

	//читаем аттрибут
	if (bWrite)
	{
		pAttributes->Item(sSection, wsItem)->SetEnumSel(currIndex, TRUE);
	}		
	else
	{
		currIndex = pAttributes->Item(sSection, wsItem)->GetEnumSel();

		for (i = 0; i<Count; i++)
		{
			iUomCode = fnc_UOM::GetCodeUom(i);

			if (i == currIndex)
			{
				iUnitType = iUomCode;
			}

		}
	}



/*
	if (lpcUnit)
	{
		iCode = GetGeoUnitCode(*piUnitIndex);

		if (iCode == fnc_UOM::Uom_Unknown)
			::LoadString(AfxGetResourceHandle(), IDS_UNIT_TYPE_PIXEL, lpcUnit, MAX_GEOSTRING_SIZE);
		else
			pGeoInfo->GetShortUnitName(iCode, lpcUnit);
	}
	*/
}
///////////////////////////////////////////////////
void Attr(int & value, CString & wsItem, CString &sSection, Cdfi_Attributes *pAttributes, bool bWrite, BOOL bHide)//, int minValue, int maxValue  )
{
	__int64 v = value;
	Attr((__int64)v, wsItem, sSection, pAttributes, bWrite, bHide);//(__int64)minValue, (__int64)maxValue);
	value = (int)v;
}
///////////////////////////////////////////////////
void Attr(__int64 & value, CString & wsItem, CString &sSection, Cdfi_Attributes *pAttributes, bool bWrite, BOOL bHide)//, __int64 minValue, __int64 maxValue  )
{
	CString str = wsItem;
	//str.LoadString( resID );
	AttrTest(str, sSection, pAttributes, bWrite);
	
	int option = bHide ? ATTRIBUTE_HIDDEN : 0;
				
	if (!pAttributes->FindAttribute(sSection, str) ) 
		pAttributes->Add( sSection, str, ATTRIBUTE_TYPE_INT	, 0, option )->SetInt( (int)value, FALSE );
	if(!bWrite)
		value = pAttributes->Item( sSection, str )->GetInt();
	else
		pAttributes->Item( sSection, str )->SetInt( (int)value, FALSE);

	//value = min(maxValue, max(minValue, value));
}		
/////////////////////////////////////////////////
void Attr(COLORREF & color, CString & wsItem, CString &sSection, Cdfi_Attributes *pAttributes, bool bWrite, BOOL bHide)
{
	int value = (int)color;
	CString str = wsItem;

	int option = bHide ? ATTRIBUTE_HIDDEN : 0;

	AttrTest(str, sSection, pAttributes, bWrite);
			
	if (!pAttributes->FindAttribute(sSection, str) ) 
		pAttributes->Add( sSection, str, ATTRIBUTE_TYPE_COLOR	, 0, option )->SetInt( value, FALSE );
	if(!bWrite)
	{
		value = pAttributes->Item( sSection, str )->GetInt();
		color = value;
	}
	else
		pAttributes->Item( sSection, str )->SetInt( value, FALSE);	
}		
////////////////////////////////////////////////////////
void Attr(bool & value, CString & wsItem, CString &sSection,Cdfi_Attributes *pAttributes,bool bWrite, BOOL bHide)
{	
	CString str = wsItem;
	int option = bHide ? ATTRIBUTE_HIDDEN : 0;

	AttrTest(str, sSection, pAttributes, bWrite);

	if (!pAttributes->FindAttribute(sSection, str) )
		pAttributes->Add( sSection, str, ATTRIBUTE_TYPE_CHECKBUTTON	, 0, option  )->SetBool( value, FALSE );//ATTRIBUTE_NO_REMOVE
		
	//if (typeid(std::string)==typeid(value))
	{
		if(!bWrite)
			value = pAttributes->Item( sSection, str )->GetBool();
		else
			pAttributes->Item( sSection, str )->SetBool( value, FALSE);
	}
	
}
////////////////////////////////////////////////////////
void Attr(TCHAR *value, CString & wsItem, CString &sSection, Cdfi_Attributes *pAttributes, int maxLen,bool bWrite, BOOL bHide)
{
	CString s = CString(value);

	Attr(s, wsItem, sSection, pAttributes, bWrite, bHide);

	wcsncpy(value, s.GetString(), maxLen);
}
////////////////////////////////////////////////////////
void Attr(CString & value, CString & wsItem, CString &sSection,Cdfi_Attributes *pAttributes,bool bWrite, BOOL bHide)
{
	CString str = wsItem;
	int option = bHide ? ATTRIBUTE_HIDDEN : 0;

	AttrTest(str, sSection, pAttributes, bWrite);

	if (!pAttributes->FindAttribute(sSection, str) )
		pAttributes->Add( sSection, str, ATTRIBUTE_TYPE_STRING	, 0, option  )->SetString( value, FALSE );//ATTRIBUTE_NO_REMOVE
		
	if(!bWrite)
		value = pAttributes->Item( sSection, str )->GetString();
	else
		pAttributes->Item( sSection, str )->SetString( value, FALSE);
	
	
}


////////////////////////////////////////////////////////
void Attr(double & value, CString & wsItem, CString &sSection,Cdfi_Attributes *pAttributes,bool bWrite, BOOL bHide)
{
	CString str=wsItem;
	int option = bHide ? ATTRIBUTE_HIDDEN : 0;

	AttrTest(str, sSection, pAttributes, bWrite);

	if (!pAttributes->FindAttribute(sSection, str) )
		pAttributes->Add( sSection, str, ATTRIBUTE_TYPE_DOUBLE	, 0, option )->SetDouble( value, FALSE );
		
	
	if(!bWrite)
		value = pAttributes->Item( sSection, str )->GetDouble();
	else
		pAttributes->Item( sSection, str )->SetDouble( value, FALSE);
	
	
}
//////////////////////////////////////////////////////////////////




double round(double x)
{
  return floor(x + 0.5);
}


double DISTANCE(IC_POINT3DD a, IC_POINT3DD b)
{
	return sqrt((a.x*a.x-b.x*b.x)+(a.y*a.x-b.y*b.y));
}

double GRADUS (IC_POINT3DD a, IC_POINT3DD b)
{
	return (ANGLE(a,b) * 180.0 / (M_PI));
}
double GRADUS (IC_POINT3DD a, IC_POINT3DD b, IC_POINT3DD c)
{
	 double A = (ANGLE(a,b,c) * 180.0 / (M_PI));

	 if(A < 0) A = 360 + A;
	 
	 return A;
}
///////////////////////////////////////////////////////////////////
double ANGLE (IC_POINT3DD a, IC_POINT3DD b, IC_POINT3DD c)
{	
	double Gamma1 = ANGLE (a,b);
	double Gamma2 = ANGLE (c,b);

	return  (Gamma1 - Gamma2);

}

///////////////////////////////////////////////////////////////////
double ANGLE (IC_POINT3DD a, IC_POINT3DD b)
{	
	double an;
	double dx,dy;
	
	dx = a.x-b.x;
	dy = a.y-b.y;

	if(dy == 0)	
		an = M_PI/2;	
	else
		an=atan(abs(dx/dy));

	if(dx < 0) 
		if( dy < 0) an += M_PI;
		else		an = M_PI*2 - an;
	else
		if( dy < 0) an = M_PI - an;

	return an;
}

///////////////////////////////////////////////////////////////////

bool IsPointOnTriangle(IC_POINT3DD PTest,IC_POINT3DD P1, IC_POINT3DD P2, IC_POINT3DD P3)
{
	double a = (P1.x - PTest.x) * (P2.y - P1.y) - (P2.x - P1.x) * (P1.y - PTest.y);
	double b = (P2.x - PTest.x) * (P3.y - P2.y) - (P3.x - P2.x) * (P2.y - PTest.y);
	double c = (P3.x - PTest.x) * (P1.y - P3.y) - (P1.x - P3.x) * (P3.y - PTest.y);
 
	if ((a >= 0 && b >= 0 && c >= 0) || (a <= 0 && b <= 0 && c <= 0))
		return true;
	else
		return false;
}
///////////////////////////////////////////////////////////////////

bool IsPointInTriangle(IC_POINT3DD PTest,IC_POINT3DD P1, IC_POINT3DD P2, IC_POINT3DD P3)
{
	if(PTest.x == P1.x && PTest.y == P1.y) return false;
	if(PTest.x == P2.x && PTest.y == P2.y) return false;
	if(PTest.x == P3.x && PTest.y == P3.y) return false;

	double a = (P1.x - PTest.x) * (P2.y - P1.y) - (P2.x - P1.x) * (P1.y - PTest.y);
	double b = (P2.x - PTest.x) * (P3.y - P2.y) - (P3.x - P2.x) * (P2.y - PTest.y);
	double c = (P3.x - PTest.x) * (P1.y - P3.y) - (P1.x - P3.x) * (P3.y - PTest.y);
 
	if (a == 0 && b == 0 && c == 0) return false;

	if ((a >= 0 && b >= 0 && c >= 0) || (a <= 0 && b <= 0 && c <= 0))
		return true;
	else
		return false;
}
/////////////////////////////////////////////////////////////////////////////////

bool IsIntersection(CIC_Point3DD start1, CIC_Point3DD end1, CIC_Point3DD start2, CIC_Point3DD end2, CIC_Point3DD &out_intersection)
{
    CIC_Point3DD dir1 = end1 - start1;
    CIC_Point3DD dir2 = end2 - start2;

    //считаем уравнения прямых проходящих через отрезки
    double a1 = -dir1.y;
    double b1 = +dir1.x;
    double d1 = -(a1*start1.x + b1*start1.y);

    double a2 = -dir2.y;
    double b2 = +dir2.x;
    double d2 = -(a2*start2.x + b2*start2.y);

    //подставляем концы отрезков, для выяснения в каких полуплоскотях они
    double seg1_line2_start = a2*start1.x + b2*start1.y + d2;
    double seg1_line2_end = a2*end1.x + b2*end1.y + d2;

    double seg2_line1_start = a1*start2.x + b1*start2.y + d1;
    double seg2_line1_end = a1*end2.x + b1*end2.y + d1;

    //если концы одного отрезка имеют один знак, значит он в одной полуплоскости и пересечения нет.
    if (seg1_line2_start * seg1_line2_end >= 0 || seg2_line1_start * seg2_line1_end >= 0) 
        return false;

    double u = seg1_line2_start / (seg1_line2_start - seg1_line2_end);
    //out_intersection =  start1 + u * dir1;
	out_intersection.x =  start1.x + u * dir1.x;
	out_intersection.y =  start1.y + u * dir1.y;
	out_intersection.z =  (start1.z + end1.z + start2.z + end2.z)/4 ;

    return true;
}

//////////////////
void DeleteAutoIntersections(CIC_RegionCmx &rgPolygon)
{
	for(int section = 0;section < rgPolygon.GetPolygonsCount();section++)
	{
		DeleteAutoIntersections(rgPolygon.GetPolygon(section));
	}
}
////////////////////////////////////////////////////////
void DeleteAutoIntersections(CIC_PolygonD *p)
{
	int size = p->GetSize(); 
	CIC_Point3DD pt;

	for(int i=0;i<size;i++)
	{

		for(int j = (size - 1); j>i; j--)
		{
			if(IsIntersection(p->GetData()[i],p->GetData()[i+1],p->GetData()[j-1],p->GetData()[j],pt))
			{
				p->InsertPoints(&pt,1,j);
				p->InsertPoints(&pt,1,i+1);
				size+=1;
				// change points
				int i0 = i+2;
				int j0 = j;
				int count = (1 + j0 - i0)/2;

				for(int k = 0;k<count;k++,i0++,j0--)
				{
					std::swap(p->GetData()[i0], p->GetData()[j0]);
				}				
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////


void DeleteRectIntersections(CIC_RegionCmx &rgPolygon, CIC_Rect3DD vRect)
{
	for(int section = 0;section < rgPolygon.GetPolygonsCount();section++)
	{
		DeleteAutoIntersections(rgPolygon.GetPolygon(section));
	}
}

//////////////////////////////////////////////////////////////////////////////








///////////////////////////////////////////////////////////////////


double m_dProgressIncrease;
double m_dCurProgress;
double m_dFl;
CDFI *m_pDfi;	
BOOL m_bCanceled;
CString prStr[10];


//////////////////
void SetProgress(CDFI *pDfi,int level,TCHAR *s, __int64 count)
{
	m_pDfi = pDfi;

	if(level<10) prStr[level] = s;

	CString str;

	for(int i=0;i<=level;i++) 
		str+=prStr[i];
	
	m_pDfi->GetMainFrame()->EndProgress();
	m_pDfi->GetMainFrame()->SetProgressText(str);
	m_pDfi->GetMainFrame()->StartProgress();

	m_dProgressIncrease = 100.0 / count;

	m_bCanceled = FALSE;
}
///////////////////
BOOL IncProgress()
{
	if(m_bCanceled) return TRUE;

	if (!m_pDfi) return TRUE;

	m_dCurProgress += m_dProgressIncrease;
	if(m_dCurProgress > 1.0)
	{
		m_dFl = floor(m_dCurProgress);
		m_pDfi->GetMainFrame()->IncreaseProgress(m_dFl);
		m_dCurProgress -= m_dFl;			
		if(m_pDfi->GetMainFrame()->CheckCanceledSignal() == TRUE)
		{		
			m_pDfi->GetMainFrame()->EndProgress();
			m_bCanceled = TRUE;		
		}
	}
	return m_bCanceled;
}			
///////////////////////////////
void EndProgress()
{
	if (!m_pDfi) return;

	m_pDfi->GetMainFrame()->EndProgress();
}

////////////////////////////////////////
///////////////////////////////////////////

CTimeMeasuring *pTMM;

void CreateTimeMeasuring(CDFI *pDfi)
{
	if(!pTMM)
		pTMM = new CTimeMeasuring(pDfi);
}

void StartTimeMeasuring(TCHAR *name)
{
	if (pTMM) pTMM->Start(name);
}

void StopTimeMeasuring(TCHAR *name)
{
	if (pTMM) pTMM->Stop(name);
}


double GetLastTime(TCHAR *name)
{
	if (pTMM) return pTMM->GetLastTime(name);
	return 0.0;
}

void SaveTimeMeasuring()
{
	pTMM->Save();
}

void ResetTimeMeasuring()
{
	pTMM->Reset();
}

CTimeMeasuring::CTimeMeasuring(CDFI *pDfi)
{
	m_pDfi = pDfi;
	m_resetFlag = 0;
	m_saveFlag = 0;
}

CTimeMeasuring::~CTimeMeasuring()
{
	timeObjects.clear();
}


void CTimeMeasuring::Reset()
{
	//if (m_resetFlag)
	{
		m_resetFlag = 0;
		timeObjects.clear();
	}
}

void CTimeMeasuring::Start(TCHAR *name)
{
	std::vector<CTimeObject>::iterator it;

	for (it = timeObjects.begin();it != timeObjects.end();++it)
	{
		if (!wcsncmp(it->name, name, 24))
			break;
	}

	if (it == timeObjects.end())
	{
		CTimeObject to;
		wcsncpy(to.name, name, 24);
		timeObjects.push_back(to);
		it = timeObjects.end() - 1;
		it->count = 0;
		it->sum = 0;
		it->maximum = 0;
		it->minimum = 99999;
		it->last = 0;
	}
	QueryPerformanceFrequency(&(it->time2));
	QueryPerformanceCounter(&(it->time1));
	it->freq = double(it->time2.QuadPart) / 1000; // ms
}


void CTimeMeasuring::Stop(TCHAR *name)
{
	std::vector<CTimeObject>::iterator it;

	for (it = timeObjects.begin();it != timeObjects.end();++it)
	{
		if (!wcsncmp(it->name, name, 24))
		{
			if (!wcsncmp(it->name, name, 24))
			{
				QueryPerformanceCounter(&(it->time2));

				double v = double(it->time2.QuadPart - it->time1.QuadPart) / it->freq;
				it->sum += v;
				it->count++;
				it->average = it->sum / it->count;
				if (v > it->maximum) it->maximum = v;
				if (v < it->minimum) it->minimum = v;
				it->last = v;
				break;
			}
		}
	}
}


double CTimeMeasuring::GetLastTime(TCHAR *name)
{
	std::vector<CTimeObject>::iterator it;

	for (it = timeObjects.begin();it != timeObjects.end();++it)
	{
		if (!wcsncmp(it->name, name, 24))
		{
			if (!wcsncmp(it->name, name, 24))
			{
				return it->last;
			}
		}
	}
}

void CTimeMeasuring::Save()
{
	//if (m_saveFlag)
	{
		m_saveFlag = 0;

		// open to read in text mode
		FILE* f;
		errno_t err;

		std::vector<CTimeObject>::iterator it;
		CString dir = _T("googlemap_tests");
		CString str;
		bool doHeader = false;

		CreateDirectoryW(dir,NULL);

		//dir.Format(_T("%s\\%s",dir,
		str.Format(_T("%s\\%s.csv"), dir, m_pDfi->GetMainFrame()->GetActiveDocument()->GetTitle());

		err = _wfopen_s(&f, str, _T("rt"));
		if (f) fclose(f);
		else doHeader = true;
		
		err = _wfopen_s(&f, str, _T("at"));
		if (err)	return;
		if (!f)		return;
			
		if (doHeader)
		{
			fputws(_T("date"),f);
			for (it = timeObjects.begin();it != timeObjects.end();++it)
			{
				str.Format(_T(";%s"),it->name);
				fputws(str, f);
			}
			fputws(_T("\n"), f);
		}

		struct tm *tm;
		time_t tt = time(NULL);
		tm = localtime(&tt);
		str.Format(_T("%2.2d.%2.2d.%4.4d %2.2d:%2.2d:%2.2d"), tm->tm_mday,1+tm->tm_mon,1900+tm->tm_year,tm->tm_hour,tm->tm_min,tm->tm_sec);		
		fputws(str,f);

		for (it = timeObjects.begin();it != timeObjects.end();++it)
		{
			str.Format(_T(";%.6lf (%.6lf,%.6lf)"), it->average, it->minimum, it->maximum);
			fputws(str, f);
		}
		fputws(_T("\n"), f);

		fclose(f);
	}
}


//////////////////////////////////////////////////////////////////////////


void WriteToLog(CString &s)
{
	FILE* f;
	errno_t err;

	CString dir = _T("LOG");
	CString str;
	bool doHeader = false;

	CreateDirectoryW(dir, NULL);

	str.Format(_T("%s\\log.txt"), dir);//, m_pDfi->GetMainFrame()->GetActiveDocument()->GetTitle());

	err = _wfopen_s(&f, str, _T("at"));
	if (err)	return;
	if (!f)		return;

	//char *ss = (char *)s.GetString();

	fputws(s, f);

	fclose(f);
}
///////////////////////////////////////////

