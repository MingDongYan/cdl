/* The CollisionDetection component of CDL provides functions to calculate collisions
 * between various 2 dimensional objects.
 * Every function returns true if a collision happened. In this case the intersection points
 * are stored in the vector given as last argument. */
 
#ifndef CDL_COLLISION_DETECTION_HPP
#define CDL_COLLISION_DETECTION_HPP

#include <vector>
#include "Polygon.hpp"
#include "Circle.hpp"
#include "Line.hpp"
#include <QtDebug>

namespace cdl
{
    bool collideCircles(const Circle &p_circle1, const Circle &p_circle2, std::vector<Vec2> &p_intersectionPoints);
    bool collideLines(const Line &p_line1, const Line &p_line2, std::vector<Vec2> &p_intersectionPoints);
    bool collideLineSegments(const Line &p_line1, const Line &p_line2, std::vector<Vec2> &p_intersectionPoints);
    bool collideLineLineSegment(const Line &p_line, const Line &p_lineSegment, std::vector<Vec2> &p_intersectionPoints);
    bool collideLineCircle(const Line &p_line, const Circle &p_circle, std::vector<Vec2> &p_intersectionPoints);
    bool collideLineSegmentCircle(const Line &p_line, const Circle &p_circle, std::vector<Vec2> &p_intersectionPoints);
    bool collidePolygons(const Polygon &p_polygon1, const Polygon &p_polygon2, std::vector<Vec2> &p_intersectionPoints);
    bool collideLinePolygon(const Line &p_line, const Polygon &p_polygon, std::vector<Vec2> &p_intersectionPoints);
    bool collideLineSegmentPolygon(const Line &p_line, const Polygon &p_polygon, std::vector<Vec2> &p_intersectionPoints);
    bool collideCirclePolygon(const Circle &p_circle, const Polygon &p_polygon, std::vector<Vec2> &p_intersectionPoints);

    bool collidePolygons(const Polygon &p_polygon1, const Polygon &p_polygon2);

    bool collidePolygons(const QVector<QPointF>& p_polygon1, const QVector<QPointF>& p_polygon2);

    bool collidePolygons(const QVector<QPointF>& p_polygon1, const QVector<QPointF>& p_polygon2 ,QVector<QPointF>& p_intersectionPoints);

    bool collideCircles(const QPointF& cir_1,const QPointF cir_2,double r1,double r2);

    bool collideCirclePolygon(const QPointF& cir_1, const double r , const QVector<QPointF>& p_polygon1 );
}




#endif // CDL_COLLISION_DETECTION_HPP
