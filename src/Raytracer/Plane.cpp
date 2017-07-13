#include <QUtils/Raytracer/Plane.h>
#include <sstream>

namespace QUtils
{
namespace Raytracer
{
	Plane::Plane(std::string name, std::shared_ptr<Material> mat, const vector_t norm, const vector_t point) : Object(name, mat), norm(norm.unit()), point(point)
	{
		this->_lastNorm = this->norm;
	}
	
	Plane::~Plane()
	{
		
	}
	
	
	double Plane::hits(const vector_t base, const vector_t dir) const
	{
		auto NdotD = norm.dot(dir);
		if (NdotD == 0)
		{
			return -1;
		}
		
		auto t = (norm.dot(point) - norm.dot(base))/NdotD;
		
		if (t <= 0)
		{
			return -1;
		}
		
		auto hitpoint = dir * t + base;
		/*if (hitpoint.z > 0)
		{
			return -1;
		}*/
		
		((Plane*)this)->_lastHit = hitpoint;
		
		return t;
		
	}
	
	
	
	
	
	
	std::string Plane::toString() const
	{
		std::stringstream ss;
		ss << Object::toString() << std::endl;
		ss << "Plane: \nNormal: " << norm << std::endl;
		ss << "Point: " << point;
		return ss.str();
	}
}
}