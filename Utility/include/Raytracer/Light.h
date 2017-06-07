#pragma once
#include "Types.h"
#include <memory>
#include <string>

namespace Util
{
namespace Raytracer
{
	class Object;
	class Model;
	
	class Light : public std::enable_shared_from_this<Light>, public RaytracerItem
	{
		protected:
		vector_t _position;
		dpixel_t _emission;
		
		
		public:
		Light(std::string name, const vector_t position, const dpixel_t emission);
		Light(std::string name);
		
		virtual ~Light();
		
		dpixel_t emission() const
		{ return _emission; }
		vector_t position() const
		{ return _position; }
		
		virtual bool visCheck(const vector_t) const;
		
		virtual void illuminate(const Model*, const vector_t& base, const std::shared_ptr<Object> obj, dpixel_t& pix) const;
		
		virtual void addGlint(const std::shared_ptr<Object> obj, const vector_t& base, const vector_t& dir, dpixel_t& pix) const;
		
		
		virtual std::string toString() const override;
	};
}
}