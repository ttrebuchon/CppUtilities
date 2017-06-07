#pragma once
#include <cmath>
#include "RaytracerItem.h"

namespace Util
{
namespace Raytracer
{
	//TODO: Replace with actual pixel type
	struct rgbP
	{
		char R;
		char G;
		char B;
		
		rgbP() : R(0), G(0), B(0)
		{ }
		
		rgbP(int r, int g, int b) : R(r), G(g), B(b)
		{ }
		
	};
	typedef rgbP pixel_t;
	
	struct drgbP
	{
		double R;
		double G;
		double B;
		
		drgbP() : R(0), G(0), B(0)
		{ }
		
		drgbP(double r, double g, double b) : R(r), G(g), B(b)
		{ }
	};
	
	typedef drgbP dpixel_t;
	
	dpixel_t pixScale(const double n, const dpixel_t p);
	
	dpixel_t operator*(const dpixel_t p1, const dpixel_t p2);
	
	dpixel_t operator+(const dpixel_t p1, const dpixel_t p2);
	
	dpixel_t clamp(const dpixel_t);
	
	std::ostream& operator<<(std::ostream&, const dpixel_t);
	
	//TODO: Replace with actual vector type
	struct pseudoVec
	{
		double x;
		double y;
		double z;
		
		pseudoVec() : x(0), y(0), z(0)
		{
			
		}
		
		pseudoVec(double x, double y, double z) : x(x), y(y), z(z)
		{
		}
		
		double length() const
		{
			return sqrt(x*x + y*y + z*z);
		}
		
		pseudoVec unit() const
		{
			pseudoVec u;
			auto len = this->length();
			u.x = x/len;
			u.y = y/len;
			u.z = z/len;
			return u;
		}
		
		pseudoVec operator+(const pseudoVec v) const
		{
			pseudoVec r;
			r.x = x + v.x;
			r.y = y + v.y;
			r.z = z + v.z;
			return r;
		}
		
		pseudoVec operator-(const pseudoVec v) const
		{
			pseudoVec r;
			r.x = x - v.x;
			r.y = y - v.y;
			r.z = z - v.z;
			return r;
		}
		
		pseudoVec operator*(const pseudoVec v) const
		{
			pseudoVec r;
			r.x = x * v.x;
			r.y = y * v.y;
			r.z = z * v.z;
			return r;
		}
		
		pseudoVec operator*(const double n) const
		{
			pseudoVec r;
			r.x = x * n;
			r.y = y * n;
			r.z = z * n;
			return r;
		}
		
		double dot(const pseudoVec v) const
		{
			return x*v.x + y*v.y + z*v.z;
		}
		
		pseudoVec reflect(const pseudoVec n) const
		{
			auto u = unit() * -1;
			double UdotN = u.dot(n);
			
			return (n*2*UdotN) - u;
		}
	};
	typedef pseudoVec vector_t;
	
	std::ostream& operator<<(std::ostream&, const vector_t);
	
	
	
	struct img_t
	{
		pixel_t* pix;
		img_t(int x, int y)
		{
			pix = new pixel_t[x*y];
		}
		~img_t()
		{
			delete[] pix;
		}
	};
	
	typedef img_t image_t;
}
}