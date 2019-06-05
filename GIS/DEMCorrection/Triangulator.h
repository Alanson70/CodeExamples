#pragma once

#include "RegionCmx.h"
#include <vector>

#define CGAL_NO_AUTOLINK
#define CGAL_NDEBUG
#define BOOST_ALL_NO_LIB


#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>

struct FaceInfo2
{
	FaceInfo2(){}
	
	bool in_domain()
	{
		return nesting_level % 2 == 1;
	}

	int nesting_level;
};

typedef CGAL::Exact_predicates_inexact_constructions_kernel			K;
typedef CGAL::Triangulation_vertex_base_with_info_2<double, K>		Vb;
typedef CGAL::Triangulation_face_base_with_info_2<FaceInfo2,K>		Fbb;
typedef CGAL::Constrained_triangulation_face_base_2<K,Fbb>			Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>					TDS;
typedef CGAL::Exact_predicates_tag									Itag;
typedef CGAL::Constrained_Delaunay_triangulation_2<K, TDS, Itag>	CDT;
typedef CDT::Point													Point;

class CTriangulator
{
public:
	CTriangulator();
	~CTriangulator();

private:
	void Clear();

public:
	bool CreatePolygonTriangulation(CIC_RegionCmx &rgPoly, /*std::vector<std::vector<CIC_Point3DD>>*/CIC_RegionCmx &polyLines, std::vector<CIC_Point3DD> &points);
	bool Interpolate(double dX, double dY, double &dZ);

	CDT& GetTriangulation();

private:
	CDT cdt_;
	CDT::Face_handle prevFh;
};


extern int I_OFFSET;


