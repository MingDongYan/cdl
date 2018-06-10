#include <cmath>
#include <algorithm>
#include "CollisionDetection.hpp"
#include "alt.h"

/* Formula of line intersection:
 * u1 = LINE1_INTERSECT_FAC(l1, l2) / LINE_INTERSECT_DENOM(l1, l2)
 * u2 = LINE2_INTERSECT_FAC(l1, l2) / LINE_INTERSECT_DENOM(l1, l2)
 * u1 and u2 are used as factors to calculate intersection point */
#define LINE_INTERSECT_DENOM(l1, l2) (((l2.point2.y - l2.point1.y) * (l1.point2.x - l1.point1.x)) - \
									  ((l2.point2.x - l2.point1.x) * (l1.point2.y - l1.point1.y)))
#define LINE1_INTERSECT_FAC(l1, l2) (((l2.point2.x - l2.point1.x) * (l1.point1.y - l2.point1.y)) - \
									 ((l2.point2.y - l2.point1.y) * (l1.point1.x - l2.point1.x)))
#define LINE2_INTERSECT_FAC(l1, l2) (((l1.point2.x - l1.point1.x) * (l1.point1.y - l2.point1.y)) - \
								     ((l1.point2.y - l1.point1.y) * (l1.point1.x - l2.point1.x)))
									 
/* Formulas for line circle intersection */
#define LINE_CIRCLE_INTERSECT_FAC_A(diffp1p2) ((diffp1p2.x) * (diffp1p2.x) + (diffp1p2.y) * (diffp1p2.y))
#define LINE_CIRCLE_INTERSECT_FAC_B(diffp1p2, p1) (2 * ((diffp1p2.x * p1.x) + (diffp1p2.y * p1.y)))
#define LINE_CIRCLE_INTERSECT_FAC_C(p1, rad) ((p1.x * p1.x) + (p1.y * p1.y) - (rad * rad))
#define LINE_CIRCLE_INTERSECT_DELTA(a, b, c) (b * b - (4 * a * c))

namespace cdl
{
    static void unique(std::vector<Vec2> &p_points)
	{
		for(int i = 0; i < p_points.size(); ++i) {
			for(int j = i + 1; j < p_points.size(); ++j) {
				if(p_points[i] == p_points[j]) {
					p_points.erase(p_points.begin() + j);
					--j;
				}
			}
		}
	}
	
    bool collideCircles(const Circle &p_circle1, const Circle &p_circle2, std::vector<Vec2> &p_intersectionPoints)
	{
		// vector from mid1 to mid2
		Vec2 directionVec = p_circle2.mid - p_circle1.mid;
        double sqDistance = directionVec.lengthSQ();
        double sqRadiusSum = (p_circle1.radius + p_circle2.radius) * (p_circle1.radius + p_circle2.radius);
		// square of radius sum is higher than square distance between mids
		if(sqRadiusSum < sqDistance)
			return false;
			
        double circleDist = sqrt(sqDistance);
		
		// tangent each other
		if(sqRadiusSum == sqDistance) {
			p_intersectionPoints.push_back(p_circle1.mid + ((directionVec / circleDist) * p_circle1.radius));
			return true;
		}
		
		// distance from circle1 to radicalLine
        double distance1 = (sqDistance + p_circle1.radius * p_circle1.radius - p_circle2.radius * p_circle2.radius) / (2 * circleDist);
		// points of radical line, have to normalize direction vec
		Vec2 radicalPoint1 = p_circle1.mid + ((directionVec / circleDist) * distance1);
		Vec2 radicalPoint2 = radicalPoint1 + directionVec.perpendicular();
		return collideLineCircle(Line(radicalPoint1, radicalPoint2), p_circle1, p_intersectionPoints);
	}
	
    bool collideLines(const Line &p_line1, const Line &p_line2, std::vector<Vec2> &p_intersectionPoints)
	{
		// denominator of formula for line intersection
        double denominator = LINE_INTERSECT_DENOM(p_line1, p_line2);
		if(denominator == 0)
			return false;
		// factor to calculate resulting point
        double u1 = LINE1_INTERSECT_FAC(p_line1, p_line2) / denominator;
		
		// add intersection point
		p_intersectionPoints.push_back(p_line1.point1 + (u1 * (p_line1.point2 - p_line1.point1)));
		return true;
	}
	
    bool collideLineSegments(const Line &p_line1, const Line &p_line2, std::vector<Vec2> &p_intersectionPoints)
	{
		// denominator of formula for line intersection
        double denominator = LINE_INTERSECT_DENOM(p_line1, p_line2);
		if(denominator == 0)
			return false;
		// factor to calculate resulting point
        double u1 = LINE1_INTERSECT_FAC(p_line1, p_line2) / denominator;
        double u2 = LINE2_INTERSECT_FAC(p_line1, p_line2) / denominator;
		
		// intersection point is not in between points of lines
		if (u1 < 0 || u1 > 1 || u2 < 0 || u2 > 1)
			return false;
			
		// add intersection point
		p_intersectionPoints.push_back(p_line1.point1 + (u1 * (p_line1.point2 - p_line1.point1)));
		return true;
	}
	
    bool collideLineLineSegment(const Line &p_line, const Line &p_lineSegment, std::vector<Vec2> &p_intersectionPoints)
	{
		// denominator of formula for line intersection
        double denominator = LINE_INTERSECT_DENOM(p_line, p_lineSegment);
		if(denominator == 0)
			return false;
        double u = LINE2_INTERSECT_FAC(p_line, p_lineSegment) / denominator;
		
		// intersection point is not in between points of lineSegment
		if (u < 0 || u > 1)
			return false;
			
		// add intersection point
		p_intersectionPoints.push_back(p_lineSegment.point1 + (u * (p_lineSegment.point2 - p_lineSegment.point1)));
		return true;
	}
	
    bool collideLineCircle(const Line &p_line, const Circle &p_circle, std::vector<Vec2> &p_intersectionPoints)
	{
		Vec2 localPoint1 = p_line.point1 - p_circle.mid;
		Vec2 localPoint2 = p_line.point2 - p_circle.mid;
		// direction vector of the line
		Vec2 diffP2P1 = localPoint2 - localPoint1;
		
        double a = LINE_CIRCLE_INTERSECT_FAC_A(diffP2P1);
        double b = LINE_CIRCLE_INTERSECT_FAC_B(diffP2P1, localPoint1);
        double c = LINE_CIRCLE_INTERSECT_FAC_C(localPoint1, p_circle.radius);
        double delta = LINE_CIRCLE_INTERSECT_DELTA(a, b, c);
		//no intersection
		if (delta < 0)
			return false;
		// one intersection, tangent
		else if (delta == 0) {
            double u = -b / (2 * a);
			p_intersectionPoints.push_back(p_line.point1 + (u * diffP2P1));
		//two intersections
		} else {
            double sqrtDelta = sqrt(delta);
            double u1 = (-b + sqrtDelta) / (2 * a);
            double u2 = (-b - sqrtDelta) / (2 * a);
			
			p_intersectionPoints.push_back(p_line.point1 + (u1 * diffP2P1));
			p_intersectionPoints.push_back(p_line.point1 + (u2 * diffP2P1));
		}
		
		return true;
	}
	
    bool collideLineSegmentCircle(const Line &p_line, const Circle &p_circle, std::vector<Vec2> &p_intersectionPoints)
	{
		Vec2 localPoint1 = p_line.point1 - p_circle.mid;
		Vec2 localPoint2 = p_line.point2 - p_circle.mid;
		// direction vector of the line
		Vec2 diffP2P1 = localPoint2 - localPoint1;
		
        double a = LINE_CIRCLE_INTERSECT_FAC_A(diffP2P1);
        double b = LINE_CIRCLE_INTERSECT_FAC_B(diffP2P1, localPoint1);
        double c = LINE_CIRCLE_INTERSECT_FAC_C(localPoint1, p_circle.radius);
        double delta = LINE_CIRCLE_INTERSECT_DELTA(a, b, c);
		//no intersection
		if (delta < 0)
			return false;
		// one intersection, tangent
		else if (delta == 0) {
            double u = -b / (2 * a);
			// is not on the line segment
			if(u < 0 || u > 1)
				return false;
			else {
				p_intersectionPoints.push_back(p_line.point1 + (u * diffP2P1));
				return true;
			}
		//two intersections
		} else {
            double sqrtDelta = sqrt(delta);
            double u1 = (-b + sqrtDelta) / (2 * a);
            double u2 = (-b - sqrtDelta) / (2 * a);
			
			if((u1 < 0  || u1 > 1) && (u2 < 0 || u2 > 1))
				return false;
			
			if(u1 >= 0  && u1 <= 1)
				p_intersectionPoints.push_back(p_line.point1 + (u1 * diffP2P1));
			if(u2 >= 0  && u2 <= 1)
				p_intersectionPoints.push_back(p_line.point1 + (u2 * diffP2P1));
			return true;
		}
		
		return true;
	}
	
    bool collidePolygons(const Polygon &p_polygon1, const Polygon &p_polygon2, std::vector<Vec2> &p_intersectionPoints)
	{
		bool result = false;
		int next;
        std::vector<Vec2> resultList;
		
		for(int i = 0; i < p_polygon1.corners.size(); ++i) {
			next = (i + 1) % p_polygon1.corners.size();
			//collide all line segments of polygon1 with polygon 2
			if(collideLineSegmentPolygon(Line(p_polygon1.corners[i], p_polygon1.corners[next]), p_polygon2, resultList))
				result = true;
		}
		
		// if collision is right on corner, there may be duplicates from each lineSegment of polygon
		unique(resultList);
		p_intersectionPoints.insert(p_intersectionPoints.end(), resultList.begin(), resultList.end());
		
		return result;
	}
	
    bool collideLinePolygon(const Line &p_line, const Polygon &p_polygon, std::vector<Vec2> &p_intersectionPoints)
	{
		bool result = false;
		int next;
        std::vector<Vec2> resultList;
		
		for(int i = 0; i < p_polygon.corners.size(); ++i) {
			next = (i + 1) % p_polygon.corners.size();
			//collide all line segments of the polygon with the line
			if(collideLineLineSegment(p_line, Line(p_polygon.corners[i], p_polygon.corners[next]), resultList))
				result = true;
		}
		
		// if collision is right on corner, there may be duplicates from each lineSegment of polygon
		unique(resultList);
		p_intersectionPoints.insert(p_intersectionPoints.end(), resultList.begin(), resultList.end());
		
		return result;
	}
	
    bool collideLineSegmentPolygon(const Line &p_line, const Polygon &p_polygon, std::vector<Vec2> &p_intersectionPoints)
	{
		bool result = false;
		int next;
        std::vector<Vec2> resultList;
		
		for(int i = 0; i < p_polygon.corners.size(); ++i) {
			next = (i + 1) % p_polygon.corners.size();
			// collide all line segments of polygon with line segment
			if(collideLineSegments(p_line, Line(p_polygon.corners[i], p_polygon.corners[next]), resultList))
				result = true;
		}
		
		// if collision is right on corner, there may be duplicates from each lineSegment of polygon
		unique(resultList);
		p_intersectionPoints.insert(p_intersectionPoints.end(), resultList.begin(), resultList.end());
		
		return result;
	}
	
    bool collideCirclePolygon(const Circle &p_circle, const Polygon &p_polygon, std::vector<Vec2> &p_intersectionPoints)
	{
		bool result = false;
		int next;
        std::vector<Vec2> resultList;
		
		for(int i = 0; i < p_polygon.corners.size(); ++i) {
			next = (i + 1) % p_polygon.corners.size();
			//collide all line segments of polygon with circle
			if(collideLineSegmentCircle(Line(p_polygon.corners[i], p_polygon.corners[next]), p_circle, resultList))
				result = true;
		}
		
		// if collision is right on corner, there may be duplicates from each lineSegment of polygon
		unique(resultList);
		p_intersectionPoints.insert(p_intersectionPoints.end(), resultList.begin(), resultList.end());
		
        return result;
    }


    bool collidePolygons(const Polygon &p_polygon1, const Polygon &p_polygon2)
    {
        std::vector<Vec2> p_intersectionPoints;
        return collidePolygons(p_polygon1,p_polygon2,p_intersectionPoints);
    }




    bool collideCircles(const QPointF &cir_1, const QPointF cir_2, double r1, double r2)
    {
       double distance = sqrt(pow(cir_2.x() - cir_1.x(),2) + pow(cir_2.y() - cir_1.y(),2));
       if(distance > (r1 + r2))
       {
           return false;
       }
       return true;
    }

    bool collidePolygons( const QVector<QPointF>& p_polygon1, const QVector<QPointF>& p_polygon2)
    {
        Polygon polygon_1 = alt::getPolygonFromVec( p_polygon1 );

        Polygon polygon_2 = alt::getPolygonFromVec( p_polygon2 );

        return collidePolygons( polygon_1 , polygon_2 );
    }

    bool collidePolygons( const QVector<QPointF>& p_polygon1, const QVector<QPointF>& p_polygon2, QVector<QPointF> &p_intersectionPoints)
    {
        p_intersectionPoints.clear();
        std::vector<Vec2> intersectionPoints;

        Polygon polygon_1 = alt::getPolygonFromVec( p_polygon1 );

        Polygon polygon_2 = alt::getPolygonFromVec( p_polygon2 );

        bool ok = cdl::collidePolygons(polygon_1 , polygon_2 , intersectionPoints );
        if( ok )
        {
            for( Vec2 p :  intersectionPoints )
            {
                p_intersectionPoints.push_back(QPointF( p.x ,p.y ));
            }
        }
        return ok;
    }

    bool collideCirclePolygon(const QPointF &cir_1, const double r, const QVector<QPointF> &p_polygon1)
    {
        Circle c( cir_1 , r );
        Polygon po( p_polygon1 );
        std::vector<Vec2> intersectionPoints;

        return collideCirclePolygon( c , po , intersectionPoints );
    }

}



