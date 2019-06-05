#pragma once

#include "StdAfx.h"
#include "VectorInfo.h"
#include "dfi_vectorobjectstream.h"
#include "dfi_OverDraw.h"
#include "dfi_View.h"
#include "dfi_Layer.h"


struct VECTOR_OBJ_INFO
{
	int nLayer;
	__int64 nObj;
	int nSect;
	
	CIC_Rect3DD Rect;
};

class VECTOR_OBJ_INFO_COMPARE
{
public:
	bool operator()(const VECTOR_OBJ_INFO& s1, const VECTOR_OBJ_INFO& s2) const
	{
		 //return (s1.nLayer < s2.nLayer && s1.nObj < s2.nObj && s1.nSect < s2.nSect );		
		 if(s1.nLayer < s2.nLayer) return true;
		 if(s1.nLayer == s2.nLayer && s1.nObj < s2.nObj ) return true;
		 if(s1.nLayer == s2.nLayer && s1.nObj == s2.nObj && s1.nSect < s2.nSect) return true;
		 return false;
	}
};

#define MODE_COMMON 0
#define MODE_CHOOSE_NODES       11
#define MODE_MOVE_NODES         12
#define MODE_SELECT_OBJECTS     13

#define SEARCH_ALL			0
#define SEARCH_ALL_VISIBLE  1
#define SEARCH_UP_LAYER     2
#define SEARCH_EDIT_LAYER   3
#define SEARCH_CUSTOM_LAYER 4

#define WM_USER_SELECT_OBJ 0x404
#define WM_USER_UPDATE_OBJ 0x405

class VECTOR_INFO
{
public :
	
	CDFI *m_pDfi;
	VECTOR_INFO_DATA *m_pData;
	Cdfi_Document* m_pDocument;
	//Cdfi_View *m_pView; // do not use! GetActiveView instead/ For SetView only
	int m_LayerNum;
	Cdfi_Layer* m_pLayer;
	__int64 m_ObjectID;
	int m_sectionNum;
	int m_objType;
	
	// Styles - for future applications in third tab - properties of objects
	VECTOR_ELLIPSE_STYLE m_ellipseStyle;
	VECTOR_TEXT_STYLE m_textStyle;
	VECTOR_POINT_STYLE m_pointStyle;
	VECTOR_LINE_STYLE m_lineStyle;
	VECTOR_POLYGON_STYLE m_polygonStyle;
	CString m_Text;

	CIC_Rect3DD m_objBaseRect; // active object rect for redrawing after modifing
	bool m_canAddDelete; // can mofify count of objects nodes

	std::vector<VECTOR_OBJ_INFO> m_objList; // selected objects

	int m_mode;			// mode of recognizing input messages
	bool m_wasMoving; // use to define if temporary point must be fixed

	CIC_Point3DD m_ptGeo; // point under mouse
	CIC_Rect3DD m_rcGeo;

	CIC_Point3DD m_ptBase; // base point for moving and selecting
	CIC_Point3DD m_ptPrev; // point for cal-ng offsets while moving
	CIC_Point3DD m_ptCenter; // base center for rotating

	int m_nLastSelected;  // for shift multi choosing between this and new point
	int m_tempNodeNumber; // new point - erased if wasn\t any moving
	bool m_highlightMode; // mode of mouse cursor for marking nodes and boards
	bool m_nodesDrawLock; // locking of redraw nodes listctrl to prevent callbacks and redraw polygons in multy-adding(shift) mode

	CIC_PolygonD *m_pSelNodes; // array of selected points
	CIC_PolygonD *m_pActivePolygon; // array of selected vectors

	std::vector<IC_PARAM> m_pendingMessage; // message if document under outer lock, issues after unlocking

	int m_layersToSearchType; // the way to search objects in layers - in all, in upper and so on...
	int m_startSearchingObject; // in al searching mode
	bool m_doRotateAndInflate; // special mode of changing nodes
	
	BOOL m_fitObjectToRect; //
	int m_searchInLayers;
							
	HCURSOR hCursorArrow;
	HCURSOR hCursorHand;
	

public:
	VECTOR_INFO(CDFI *pDfi);
	~VECTOR_INFO();
	
	void UpdateCursor(); // check if need to change cursor

	void SetParams(CDFI* pDFI, VECTOR_INFO_DATA* pData); 
	bool SetDocument( Cdfi_Document* pDocument );     // main func when open, close document and function and does critically changes in objects and layers
	void SetView(Cdfi_View *pView); // function to reset overdraw

	void OverdrawInit();
	void OverdrawDelete();
	bool m_updateOverdraw;
	void OverdrawUpdate();

	bool Commander(UINT pMessage,IC_PARAM * pParam); // handler for proc messages
	void ModeCommander(UINT pMessage,WPARAM wParam, LPARAM lParam); // 
	
	// objects
	//virtual int GetSelectionMode()=0;
	void OnChangeObject(int mLayer, __int64 nObject);
	virtual void OnUpdateSelectedObjects() { }

protected:
	int SelectObjectsUnderRect(CIC_Point3DD &firstPoint, CIC_Point3DD &secPoint); 
	int SelectObjectsUnderMouse(bool addFlag, bool inverseFlag);
	bool GetSelectedObject(int n, int &nLayer,__int64 &nObj,int &nSect); // by order number
	bool GetSelectedObjectUnderMouse(int &nLayer,__int64 &nObj, int &nSect, int index = 0);
	bool IsObjectSelected(int nLayer, __int64 nObj, int nSect);
	bool IsObjectSelected(int nLayer, __int64 nObj);


	void HighlightSelectedObjects();
	void UnhighlightSelectedObjects();
	void ClearAllSelections();
	void ClearSelectedObjects();
	int GetSelectedObjectsCount();

private:
	void AddObjectToSelectionList(int nLayer, __int64 nObj,int nSection, CIC_Rect3DD rect);
	void UpdateObjectInSelectionList(int nLayer, __int64 nObj,int nSection, CIC_Rect3DD rect); // update by rects
	void RemoveObjectFromSelectionList(int nLayer, __int64 nObj);
	void ArrangeSelectionList(); 

	
public:
	bool IsActiveObjectUnderMouse();
	bool SetActiveObject(int nLayer,__int64 nObj,int nSect);
	void FitActiveObject();
	void ClearActiveObject();
	void StoreActiveObject(int mode = IDS_VINFO_XYZ_MOVE);	
	void ShowActiveObject();
	void UpdateActiveObject();
	virtual void OnUpdateActiveObject() { }
	bool GetActiveObject(int &nLayer, __int64 &nObj, int &nSect);

public:

	// nodes
	bool GetNodeByNumber(DWORD num, IC_POINT3DD &pt);
	bool GetNodeByIndex(DWORD num, IC_POINT3DD &pt);
	virtual bool IsNodeUnderNode(CIC_Point3DD &ptNode, CIC_Point3DD &ptPoint);
	virtual bool GetNodeUnderMouse(int &numPoint);
	virtual bool IsLineUnderMouse();
	void DrawSelectedNodes();

	void MoveSelectedNodesOn(CIC_Point3DD dt);
	void RotateAndInflateNodesOn(CIC_Point3DD dt);
	void ModifyNodes(int mode, IC_POINT3DD newPoint);
		
	bool AddTempNodeOnLine();
	void DeleteTempNode();

	int RunContextMenu();
	void RunXYZDialog(int mode);
	void AccessXYZFile(int mode);

	void Interpolation(CIC_PolygonD *pPolygon,__int64 index0,__int64 index1, int mode);
	////////// virtual ///
	virtual int  GetNodesCount()=0;
	virtual void SetNodeSelected(int numPoint, bool selflag, int addMode)=0;
	virtual void DeleteNodeFromSelected(int numPoint)=0;
	virtual void UpdateSelectedNodes()=0;
	virtual bool IsItSelectedNode(int numPoint)=0;
	virtual void ClearSelectedNodes()=0;
	virtual int  GetSelectedNodeIndex(int pos)=0;
	virtual int  GetSelectedNodesCount()=0;

	virtual void SetNodesCount(int count)=0;
	virtual void SetAttrCount(int num)=0;




	
};



BOOL OverdrawFunction( Cdfi_View *pView, Cdfi_MemoryDC *pMemDC, LPVOID pParam);