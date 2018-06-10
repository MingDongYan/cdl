#ifndef CDL_VEC2_HPP
#define CDL_VEC2_HPP

#include <string>

namespace cdl
{
	/* This class implements a 2D vector. It provides mathematical operators for adding,
	 * subtracting and scaling. */
	class Vec2
	{
	public:
        double x;
        double y;
	
		Vec2(): x(0), y(0) { }
        Vec2(double p_x, double p_y): x(p_x), y(p_y) { }
		~Vec2() { }
		
        void set(const double p_x, const double p_y);
        double lengthSQ() const;
        double length() const;
		Vec2 perpendicular() const;
		
		Vec2& operator+=(Vec2 const& p_vec);
		Vec2& operator-=(Vec2 const& p_vec);
        Vec2& operator*=(const double p_factor);
        Vec2& operator/=(const double p_divisor);
		
		std::string str() const;
	};
	
	const Vec2 operator+(Vec2 const& p_vec1, Vec2 const& p_vec2);
	const Vec2 operator-(Vec2 const& p_vec1, Vec2 const& p_vec2);
    const Vec2 operator*(Vec2 const& p_vec, const double p_factor);
    const Vec2 operator*(const double p_factor, Vec2 const& p_vec);
    const Vec2 operator/(Vec2 const& p_vec, const double p_divisor);
	bool operator==(Vec2 const& p_vec1, Vec2 const& p_vec2);
	bool operator!=(Vec2 const& p_vec1, Vec2 const& p_vec2);
}

#endif
