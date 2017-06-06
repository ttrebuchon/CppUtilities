#pragma once
#include "Types.h"
#include <string>

namespace Util
{
namespace Raytracer
{
	class Material : public std::enable_shared_from_this<Material>, RaytracerItem
	{
		private:
		
		public:
		
		
		dpixel_t ambient() const;
		dpixel_t diffuse() const;
		double specular() const;
		double shine() const;
		double trans() const;
		
		std::string toString() const;
	};
}
}