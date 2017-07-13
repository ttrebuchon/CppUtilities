#pragma once
#include <cmath>
#include "RaytracerItem.h"

namespace QUtils
{
namespace Raytracer
{
	//TODO: Replace with actual pixel type
	struct rgbP
	{
		unsigned char R;
		unsigned char G;
		unsigned char B;
		
		rgbP() : R(0), G(0), B(0)
		{ }
		
		rgbP(int r, int g, int b) : R(r), G(g), B(b)
		{ }
		
		rgbP operator+(const rgbP p) const
		{
			rgbP n;
			n.R = R + p.R;
			n.G = G + p.G;
			n.B = B + p.B;
			return n;
		}
		
		rgbP operator-(const rgbP p) const
		{
			rgbP n;
			n.R = R - p.R;
			n.G = G - p.G;
			n.B = B - p.B;
			return n;
		}
		
		rgbP operator*(const double n) const
		{
			rgbP p;
			p.R = R*n;
			p.G = G*n;
			p.B = B*n;
			return p;
		}
		
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
	
	dpixel_t& operator*=(dpixel_t& p1, const dpixel_t p2);
	
	dpixel_t& operator+=(dpixel_t& p1, const dpixel_t p2);
	
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
	
	
	
	class img_t
	{
		private:
		
		protected:
		uint w;
		uint h;
		
		public:
		pixel_t* arr;
		
		img_t(unsigned int w, unsigned int h) : w(w), h(h), arr(new pixel_t[w*h])
		{
			
		}
		
		img_t(const img_t& img) : w(img.w), h(img.h), arr(img.arr)
		{}
		
		~img_t() {}
		
		pixel_t* operator()(const unsigned int x, const unsigned int y) const;
		
		img_t* duplicate() const
		{
			img_t* img = new img_t(w, h);
			for (auto i = 0; i < w*h; i++)
			{
				img->arr[i] = arr[i];
			}
			return img;
		}
		
		void clear()
		{
			delete[] arr;
			arr = NULL;
		}
		
	};
	//typedef img_t image_t;
	typedef pixel_t* image_t;
}
}