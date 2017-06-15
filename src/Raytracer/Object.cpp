#include <Raytracer/Object.h>
#include <Raytracer/Material.h>

#include <sstream>

namespace Util
{
namespace Raytracer
{
	Object::Object(std::string name, std::shared_ptr<Material> mat) : RaytracerItem(name), _lastHit(), _lastNorm(), mat(mat)
	{
		
	}
	
	Object::~Object()
	{
		
	}
	
	
	dpixel_t Object::ambient() const
	{
		return mat->ambient();
	}
	
	dpixel_t Object::diffuse() const
	{
		return mat->diffuse();
	}
	
	double Object::specular() const
	{
		return mat->specular();
	}
	
	double Object::trans() const
	{
		return mat->trans();
	}
	
	double Object::shine() const
	{
		return mat->shine();
	}
	
	std::string Object::toString() const
	{
		std::stringstream ss;
		ss << RaytracerItem::toString() << std::endl;
		ss << "Object:" << std::endl << "Material : " << (mat != NULL ? mat->name() : "");
		
		return ss.str();
	}
	
}
}