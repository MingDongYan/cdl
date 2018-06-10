/* The Polygons class represents any kind of polygon shaped object
 * in CDL. The corners of the polygon are connected in pairs. Each
 * corner is connected to the next indexed corner in the vector. The
 * last and first corners also connect to a line segment. */

#ifndef CDL_POLYGON_HPP
#define CDL_POLYGON_HPP

#include <vector>
#include "./Vec2.hpp"
#include <QPointF>
#include <QVector>

#include "cdl_global.h"

namespace cdl {

    class POLYGON_LIBRARY Polygon
	{
	public:
        std::vector<Vec2> corners;
		Polygon() { }
        Polygon(const std::vector<Vec2> &p_corners): corners(p_corners) { }
        Polygon(const QVector<QPointF> &p_corners)
        {
            for( QPointF p : p_corners)
            {
                corners.push_back(cdl::Vec2( p.x(), p.y()));
            }
        }
        ~Polygon() { }

	};
}

#endif // CDL_POLYGON_HPP
