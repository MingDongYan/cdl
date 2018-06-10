/* The Circle class represents a cricle shape in CDL. It provides a Vec2 as Mid
 * and a radius. */
 
#ifndef CDL_CIRCLE_HPP
#define CDL_CIRCLE_HPP

#include "./Vec2.hpp"
#include<QPointF>

namespace cdl
{
	class Circle
	{
	public:
		Vec2 mid;
        double radius;
		Circle() { }
        Circle(const Vec2 &p_mid, const double p_radius): mid(p_mid), radius(p_radius) { }
        Circle(const QPointF &p_mid, const double p_radius) :radius(p_radius)
        {
            double p_x=p_mid.x();
            double p_y=p_mid.y();
            mid.set(p_x,p_y);
        }
		~Circle() { }

	};

}

#endif
