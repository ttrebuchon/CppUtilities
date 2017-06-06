#include <Raytracer/Object.h>
#include <Raytracer/Material.h>

namespace Util
{
namespace Raytracer
{
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
	
}
}