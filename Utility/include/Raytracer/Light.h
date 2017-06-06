#pragma once
#include "Types.h"
#include <memory>
#include <string>

namespace Util
{
namespace Raytracer
{
	class Object;
	
	
	class Light : public std::enable_shared_from_this<Light>, RaytracerItem
	{
		protected:
		vector_t _position;
		dpixel_t _emission;
		
		
		public:
		
		dpixel_t emission() const
		{ return _emission; }
		vector_t position() const
		{ return _position; }
		
		virtual bool visCheck(const vector_t) const;
		
		virtual void illuminate(const vector_t& base, const std::shared_ptr<Object> obj, dpixel_t& pix) const;
		
		virtual void addGlint(const std::shared_ptr<Object> obj, const vector_t&, const vector_t&, dpixel_t&) const;
		
		
		virtual std::string toString() const;
	};
}
}