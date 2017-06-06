#include <Raytracer/Types.h>
#include <iostream>

namespace Util
{
namespace Raytracer
{
	dpixel_t pixScale(const double n, const dpixel_t p)
	{
		return dpixel_t(p.R*n, p.G*n, p.B*n );
	}
	
	dpixel_t operator*(const dpixel_t p1, const dpixel_t p2)
	{
		return dpixel_t(p1.R*p2.R, p1.G*p2.G, p1.B*p2.B);
	}
	
	dpixel_t operator+(const dpixel_t p1, const dpixel_t p2)
	{
		return dpixel_t(p1.R+p2.R, p1.G+p2.G, p1.B+p2.B);
	}
	
	std::ostream& operator<<(std::ostream& os, const vector_t v)
	{
		return os << "(" << v.x << ", " << v.y << ", " << v.z << "(";
	}
	
	
	
	
	
	
}
}