#pragma once
#include "Types.h"
#include <string>

namespace Util
{
namespace Raytracer
{
	class Texture : public std::enable_shared_from_this<Texture>, public RaytracerItem
	{
		private:
		
		public:
		
		
		std::string toString() const;
	};
}
}