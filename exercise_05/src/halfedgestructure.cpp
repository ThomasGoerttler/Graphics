
#include <cassert>

#include "halfedgestructure.h"
#include "polygonaldrawable.h"
#include "mathmacros.h"


HalfEdgeStructure::HalfEdgeStructure(PolygonalDrawable & drawable)
{
    setup(drawable);
}

HalfEdgeStructure::~HalfEdgeStructure()
{
}

const HalfEdgeStructure::t_halfEdges & HalfEdgeStructure::halfEdges() const
{
    return m_halfEdges;
}

const HalfEdgeStructure::t_faces & HalfEdgeStructure::faces() const
{
    return m_faces;
}

void HalfEdgeStructure::setup(PolygonalDrawable & drawable)
{
    if(drawable.indices().isEmpty())
		return;

    const int nTriangles(drawable.indices().size() / 3);
    m_faces.resize(nTriangles);

    // TODO: there is strict triangle support only...
    assert(drawable.indices().size() % 3 == 0);
  
	// Map of edges (given by two indices) -> opposite half-edge

    typedef std::map<std::pair<QVector3D const *, QVector3D const *>, HalfEdge*> t_opp_map;
    t_opp_map opp;

    const int he_count = nTriangles * 3;
	m_halfEdges.resize(he_count);

	for(int k = 0; k < nTriangles; k++) 
	{
        m_faces[k].he = &m_halfEdges[k * 3];

		for (int i = 0; i < 3; ++i) 
		{
            const int j(k * 3 + i);

            m_halfEdges[j].prev = &m_halfEdges[(i == 0) ? j + 2 : j - 1];
			m_halfEdges[j].next = &m_halfEdges[(i == 2) ? j - 2 : j + 1];
			m_halfEdges[j].opp = NULL;

            m_halfEdges[j].face = &m_faces[k];

            const int l(drawable.indices()[j]);

            m_halfEdges[j].vertex = &(drawable.vertices()[l]);
            m_halfEdges[j].normal =   drawable.normals()[l];
        }

        // set opposite-pointers

        for (int i = 0; i < 3; ++i) 
		{
            const int j(k * 3 + i);

			QVector3D const * v0 = m_halfEdges[j].vertex;
			QVector3D const * v1 = m_halfEdges[j].next->vertex;

			// Check if opposite half-edge is already stored
			t_opp_map::iterator p = opp.find(t_opp_map::key_type(v0, v1));
			if(p == opp.end()) 
			{   // no: Add half-edge in opposite direction
				opp[t_opp_map::key_type(v1, v0)] = &m_halfEdges[j];
			} 
			else 
			{
				// yes: Set opposite-pointers of both half-edges
				p->second->opp = &m_halfEdges[j];
                m_halfEdges[j].opp = p->second;

				opp.erase(p);
            }
        }
    }

    calculatePerFaceNormals();
    calculatePerVertexNormals(0.f);
}

void HalfEdgeStructure::calculatePerFaceNormals()
{
    HalfEdgeStructure::t_faces::iterator i = m_faces.begin();
    const HalfEdgeStructure::t_faces::const_iterator iEnd = m_faces.end();

    for(; i != iEnd; ++i)
	{
		QVector3D a = *(i->he->next->vertex) - *(i->he->vertex);
		QVector3D b = *(i->he->prev->vertex) - *(i->he->vertex);
		i->normal = QVector3D::normal(a, b);
	}
}

void HalfEdgeStructure::calculatePerVertexNormals(const float threshold)
{
    const int size(static_cast<int>(m_halfEdges.size()));
	
	for(int i = 0; i < size; ++i)
	{
	int counterFaces = 1;
	QVector3D vectorNormal = m_halfEdges[i].face->normal;
	HalfEdge * oldHalfEdge = NULL;
	
	if(m_halfEdges[i].opp != NULL && m_halfEdges[i].opp->next != NULL){
		HalfEdge *halfEdgeTemp = m_halfEdges[i].opp->next;
		QVector3D newVector = vectorNormal;
		while (halfEdgeTemp != &m_halfEdges[i]  && oldHalfEdge == NULL) {
			if(_acosd(QVector3D::dotProduct(vectorNormal, halfEdgeTemp->face->normal)) < threshold)
				newVector = (newVector * (counterFaces++) + halfEdgeTemp->face->normal) / counterFaces;
			if (halfEdgeTemp -> opp != NULL)
				halfEdgeTemp = halfEdgeTemp->opp->next;
			oldHalfEdge = halfEdgeTemp;
		}
		halfEdgeTemp = m_halfEdges[i].prev->opp;
		while (halfEdgeTemp != NULL && oldHalfEdge != NULL && halfEdgeTemp != oldHalfEdge) {
			if(_acosd(QVector3D::dotProduct(vectorNormal, halfEdgeTemp->face->normal)) < threshold){
				newVector = (newVector * (counterFaces++) + halfEdgeTemp->face->normal) / counterFaces;
			}
			if (halfEdgeTemp -> prev -> opp != NULL) {
				halfEdgeTemp = halfEdgeTemp->prev->opp;
			} else {
				break;
			}
		}
		m_halfEdges[i].normal = newVector;
	}
	else{
		m_halfEdges[i].normal = vectorNormal;
	}
}
}

