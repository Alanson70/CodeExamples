#include "stdafx.h"
#include "Triangulator.h"

CTriangulator::CTriangulator()
{
	prevFh = NULL;
}

CTriangulator::~CTriangulator()
{
	Clear();
}

void CTriangulator::Clear()
{
	cdt_.clear();
	prevFh = NULL;
}

void mark_domains(CDT& ct,
             CDT::Face_handle start,
             int index,
             std::list<CDT::Edge>& border)
{
	if(start->info().nesting_level != -1)
		return;

	std::list<CDT::Face_handle> queue;
	queue.push_back(start);
	while(! queue.empty())
	{
		CDT::Face_handle fh = queue.front();
		queue.pop_front();
		if(fh->info().nesting_level == -1)
		{
			fh->info().nesting_level = index;
			for(int i = 0; i < 3; i++)
			{
				CDT::Edge e(fh,i);
				CDT::Face_handle n = fh->neighbor(i);
				if(n->info().nesting_level == -1)
				{
					if(ct.is_constrained(e))
						border.push_back(e);
					else
						queue.push_back(n);
				}
			}
		}
	}
}

//explore set of facets connected with non constrained edges,
//and attribute to each such set a nesting level.
//We start from facets incident to the infinite vertex, with a nesting
//level of 0. Then we recursively consider the non-explored facets incident 
//to constrained edges bounding the former set and increase the nesting level by 1.
//Facets in the domain are those with an odd nesting level.
void mark_domains(CDT &cdt)
{
	for(CDT::All_faces_iterator it = cdt.all_faces_begin(); it != cdt.all_faces_end(); ++it)
		it->info().nesting_level = -1;

	std::list<CDT::Edge> border;
	mark_domains(cdt, cdt.infinite_face(), 0, border);
	while(!border.empty())
	{
		CDT::Edge e = border.front();
		border.pop_front();
		CDT::Face_handle n = e.first->neighbor(e.second);
		if(n->info().nesting_level == -1)
			mark_domains(cdt, n, e.first->info().nesting_level+1, border);
	}
}

// while drawing pixels rounded to floor value, and calculation error occures

int I_OFFSET=-1.0;

bool CTriangulator::CreatePolygonTriangulation(CIC_RegionCmx &rgPoly, /*std::vector<std::vector<CIC_Point3DD>>*/CIC_RegionCmx &polyLines, std::vector<CIC_Point3DD> &points)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	Clear();
		
	int nPolygons = rgPoly.GetPolygonsCount();

	for(int i = 0; i < nPolygons; ++i)
	{
		CIC_PolygonD *pPoly = rgPoly.GetPolygon(i);
		int nPoints = pPoly->GetSize();	
		
		for(int j = 0; j < nPoints; ++j)
		{			
			Point p1(pPoly->GetData()[j].x + I_OFFSET, pPoly->GetData()[j].y + I_OFFSET), p2(pPoly->GetData()[(j + 1) % nPoints].x + I_OFFSET, pPoly->GetData()[(j + 1) % nPoints].y + I_OFFSET);
			CDT::Vertex_handle v1 = cdt_.insert(p1), v2 = cdt_.insert(p2);
			v1->info() = pPoly->GetData()[j].z;
			v2->info() = pPoly->GetData()[(j + 1) % nPoints].z;

			cdt_.insert_constraint(v1, v2);

			
		}
	}

	/*int nPolylines = polyLines.size();
	for(int i = 0; i < nPolylines; ++i)
	{
		int nPoints = polyLines[i].size();
		for(int j = 0; j < nPoints - 1; ++j)
		{
			Point p1(polyLines[i][j].x, polyLines[i][j].y), p2(polyLines[i][j + 1].x, polyLines[i][j + 1].y);
			CDT::Vertex_handle v1 = cdt_.insert(p1), v2 = cdt_.insert(p2);
			v1->info() = polyLines[i][j].z;
			v2->info() = polyLines[i][j + 1].z;

			cdt_.insert_constraint(v1, v2);
		}
	}*/

	int nPolylines = polyLines.GetPolygonsCount();

	for(int i = 0; i < nPolylines; ++i)
	{
		CIC_PolygonD *pPoly = polyLines.GetPolygon(i);
		int nPoints = pPoly->GetSize();

		for(int j = 0; j < nPoints - 1; ++j)
		{
			Point p1(pPoly->GetData()[j].x + I_OFFSET, pPoly->GetData()[j].y + I_OFFSET), p2(pPoly->GetData()[j + 1].x + I_OFFSET, pPoly->GetData()[j + 1].y + I_OFFSET);
			CDT::Vertex_handle v1 = cdt_.insert(p1), v2 = cdt_.insert(p2);
			v1->info() = pPoly->GetData()[j].z;
			v2->info() = pPoly->GetData()[(j + 1) % nPoints].z;

			cdt_.insert_constraint(v1, v2);
		}
	}

	int nPoints = (int)points.size();
	for(int i = 0; i < nPoints; ++i)
	{
		Point p(points[i].x + I_OFFSET, points[i].y + I_OFFSET);
		CDT::Vertex_handle v = cdt_.insert(p);
		v->info() = points[i].z;
	}

	mark_domains(cdt_);

	return true;
}

bool CTriangulator::Interpolate(double dX, double dY, double &dZ)
{
	CDT::Face_handle fh = cdt_.locate(Point(dX, dY), prevFh);
	if(fh == NULL || !fh->info().in_domain())
		return false;

	// interpolate
	CDT::Vertex_handle v1 = fh->vertex(0), v2 = fh->vertex(1), v3 = fh->vertex(2);
	double x1 = v1->point().x(), x2 = v2->point().x(), x3 = v3->point().x();
	double y1 = v1->point().y(), y2 = v2->point().y(), y3 = v3->point().y();
	double z1 = v1->info(), z2 = v2->info(), z3 = v3->info();

	double dDenom = (y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3);
	double dw1 = ((y2 - y3) * (dX - x3) + (x3 - x2) * (dY - y3)) / dDenom;
	double dw2 = ((y3 - y1) * (dX - x3) + (x1 - x3) * (dY - y3)) / dDenom;
	double dw3 = 1 - dw1 - dw2;

	dZ = (dw1 * z1 + dw2 * z2 + dw3 * z3) / (dw1 + dw2 + dw3);

	prevFh = fh;

	return true;
}

CDT& CTriangulator::GetTriangulation()
{
	return cdt_;
}