#include <Raytracer/Material.h>
#include <sstream>

namespace Util
{
namespace Raytracer
{
	Material::Material(std::string name, dpixel_t amb, dpixel_t dif, double spec, double shine, double trans) : RaytracerItem(name), _ambient(amb), _diffuse(dif), _specular(spec), _shine(shine), _trans(trans)
	{
		
	}
	
	Material::Material(std::string name) : RaytracerItem(name), _ambient(), _diffuse(), _specular(), _shine(), _trans()
	{
		
	}
	
	Material::~Material()
	{
		
	}
	
	
	std::string Material::toString() const
	{
		std::stringstream ss;
		ss << RaytracerItem::toString() << std::endl;
		ss << "Ambient: #" << std::hex << _ambient.R << _ambient.G << _ambient.B << std::endl;
		ss << "Diffusion: #" << _diffuse.R << _diffuse.G << _diffuse.B << std::endl;
		ss << "Specular: " << std::dec << _specular << std::endl;
		ss << "Shine: " << _shine << std::endl;
		ss << "Transparency: " << _trans;
		return ss.str();
		
	}
}
}