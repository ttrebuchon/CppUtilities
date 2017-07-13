#include <QUtils/Raytracer/Sphere.h>
#include <cmath>
#include <sstream>

namespace QUtils
{
namespace Raytracer
{
	Sphere::Sphere(std::string name, std::shared_ptr<Material> mat, double radius, const vector_t center) : Object(name, mat), radius(radius), center(center)
	{
		
	}
	
	Sphere::~Sphere()
	{
		
	}
	
	
	double Sphere::hits(const vector_t base, const vector_t dir) const
	{
		vector_t newBase = base - center;
		
		auto a = dir.dot(dir);
		auto b = newBase.dot(dir)*2;
		auto c = newBase.dot(newBase) - radius*radius;
		
		auto disc = b*b - 4*a*c;
		
		if (disc < 0)
		{
			return -1;
		}
		
		auto t = (-b - std::sqrt(disc))/(2*a);
		
		auto dirScaled = dir*t;
		auto hitPt = dirScaled + base;
		((Sphere*)this)->_lastHit = hitPt;
		((Sphere*)this)->_lastNorm = (hitPt - center).unit();
		
		return t;
		
	}
	
	void Sphere::move(const vector_t offset)
	{
		center = center + offset;
	}
		
	std::string Sphere::toString() const
	{
		std::stringstream ss;
		ss << Object::toString() << std::endl;
		ss << "Sphere:" << std::endl;
		ss << "Radius: " << radius << std::endl;
		ss << "Center: " << center;
		
		return ss.str();
	}
}
}