#pragma once
#include "Types.h"
#include <string>
#include <memory>

namespace QUtils
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