#pragma once
#include <string>

namespace QUtils
{
namespace Raytracer
{
	class RaytracerItem
	{
		protected:
		
		std::string _name;
		public:
		RaytracerItem(std::string name) : _name(name)
		{}
		
		std::string name() const
		{ return _name; }
		virtual std::string toString() const
		{
			return std::string("Name: ") + _name;
		}
	};
}
}