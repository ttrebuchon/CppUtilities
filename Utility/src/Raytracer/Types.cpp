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
	
	dpixel_t clamp(const dpixel_t p)
	{
		//return p;
		dpixel_t p2;
		double tmp;
		if (p.R < 0.0)
		{
			tmp = 0;
		}
		else if (p.R > 255.0)
		{
			tmp = 255;
		}
		else
		{
			tmp = p.R;
		}
		p2.R = tmp;
		
		
		if (p.G < 0.0)
		{
			tmp = 0;
		}
		else if (p.G > 255.0)
		{
			tmp = 255;
		}
		else
		{
			tmp = p.G;
		}
		p2.G = tmp;
		
		
		if (p.B < 0.0)
		{
			tmp = 0;
		}
		else if (p.B > 255.0)
		{
			tmp = 255;
		}
		else
		{
			tmp = p.B;
		}
		p2.B = tmp;
		
		return p2;
	}
	
	std::ostream& operator<<(std::ostream& os, const vector_t v)
	{
		return os << "<" << v.x << ", " << v.y << ", " << v.z << ">";
	}
	
	std::ostream& operator<<(std::ostream& os, const dpixel_t p)
	{
		return os << "{" << p.R << ", " << p.G << ", " << p.B << "}";
	}
	
	
	
	
	
	
}
}