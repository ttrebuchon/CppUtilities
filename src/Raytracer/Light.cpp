#include <QUtils/Raytracer/Light.h>
#include <QUtils/Raytracer/Model.h>
#include <QUtils/Raytracer/Object.h>

#include <sstream>
#include <cmath>

namespace QUtils
{
namespace Raytracer
{
	Light::Light(std::string name, const vector_t position, const dpixel_t emission) : RaytracerItem(name), _position(position), _emission(emission)
	{
		
	}
	
	Light::Light(std::string name) : RaytracerItem(name), _position(), _emission()
	{
		
	}
	
	Light::~Light()
	{
		
	}
	
	
	
	
	bool Light::visCheck(const vector_t) const
	{
		return false;
	}
	
	void Light::illuminate(const Model* model, const vector_t& base, const std::shared_ptr<Object> obj, dpixel_t& pix) const
	{
		vector_t hitPt;
		vector_t lastNorm;
		vector_t dir;
		dpixel_t diffuse;
		double dist;
		
		hitPt = obj->lastHit();
		dir = position() - hitPt;
		dist = dir.length();
		dir = dir.unit();
		
		lastNorm = obj->lastNormal();
		
		double cos = dir.dot(lastNorm);
		if (cos < 0)
		{
			return;
		}
		
		double closestObjDist = model->findClosestObj(hitPt, dir, obj, NULL);
		if (closestObjDist > 0 && closestObjDist < dist)
		{
			return;
		}
		
		diffuse = obj->diffuse();
		diffuse = diffuse*emission();
		diffuse = pixScale(cos/dist, diffuse);
		pix = pix + diffuse;
		
		addGlint(obj, base, dir, pix);
		
	}
	
	void Light::addGlint(const std::shared_ptr<Object> obj, const vector_t& base, const vector_t& dir, dpixel_t& pix) const
	{
		double shine = obj->shine();
		if (shine <= 0)
		{
			return;
		}
		
		auto hitPt = obj->lastHit();
		auto hitLight = position() - hitPt;
		hitLight = hitLight.unit();
		auto source = hitPt - base;
		source = source.unit();
		auto sum = source + hitLight;
		sum = sum.unit();
		
		auto norm = obj->lastNormal().unit();
		
		double intens = std::pow(sum.dot(norm), shine);
		
		double spec = obj->specular();
		dpixel_t diff = pixScale(intens*spec, emission());
		pix = pix + diff;
		
		
	}
	
	
	
	std::string Light::toString() const
	{
		std::stringstream ss;
		ss << RaytracerItem::toString() << std::endl;
		ss << "Light: " << std::endl;
		ss << "Position: " << _position << std::endl;
		ss << "Emission: #" << std::hex << _emission.R << _emission.G << _emission.B;
		return ss.str();
	}
}
}