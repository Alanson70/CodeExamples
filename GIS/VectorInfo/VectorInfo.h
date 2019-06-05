#pragma once

#include "resource.h"
#include "dfi.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "dfi_vector.h"
#include "dfi_vectortable.h"
#include "dfi_Layer.h"
#include "dfi_vectorobject.h"


#define MIN_DIALOG_WIDTH 60
#define RIGHT_OFFSET 5
#define TOP_POSITION 60

#define TOLERANCE 5 

class CVectorInfoDialog;

struct VECTOR_INFO_DATA
{
	CVectorInfoDialog* pDialog;
	CRect rcLast;
};


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////


CString GetResourceString(UINT resID);

bool VectorInfo( CDFI* pDFInterface, IC_PARAM *pParam );
bool UpdateVectorInfo( CDFI* pDFInterface, CCmdUI * pExtra );
bool VectorInfoProc( CDFI * pDFInterface, IC_PARAM * pParam );


VECTOR_INFO_DATA* GetVectorInfoFunctionData( CDFI* pDfi );
void EndFunction(CDFI* pDFInterface);
bool DoFunction(CDFI* pDFInterface);


void Attr(BOOL &value, CString &str, CString &sSection, Cdfi_Attributes *pAttributes, bool bWrite);
void Attr(long &value, CString &s, CString &sSection, Cdfi_Attributes *pAttributes, bool bWrite);