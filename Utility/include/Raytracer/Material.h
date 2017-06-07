#pragma once
#include "Types.h"
#include <string>

namespace Util
{
namespace Raytracer
{
	class Material : public std::enable_shared_from_this<Material>, public RaytracerItem
	{
		private:
		dpixel_t _ambient;
		dpixel_t _diffuse;
		double _specular;
		double _shine;
		double _trans;
		
		public:
		Material(std::string name, dpixel_t amb, dpixel_t dif, double spec, double shine, double trans);
		Material(std::string name);
		virtual ~Material();
		
		virtual dpixel_t ambient() const { return _ambient; }
		virtual dpixel_t diffuse() const { return _diffuse; }
		virtual double specular() const { return _specular; }
		virtual double shine() const { return _shine; }
		virtual double trans() const { return _trans; }
		
		virtual std::string toString() const override;
	};
}
}