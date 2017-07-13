#pragma once
#include "Types.h"
#include <string>
#include <memory>

namespace QUtils
{
namespace Raytracer
{
	class Material;
	
	class Object : public std::enable_shared_from_this<Object>, public RaytracerItem
	{
		protected:
		
		vector_t _lastHit;
		vector_t _lastNorm;
		std::shared_ptr<Material> mat;
		
		
		public:
		Object(std::string name, std::shared_ptr<Material> mat);
		
		virtual ~Object();
		
		virtual dpixel_t ambient() const;
		virtual dpixel_t diffuse() const;
		virtual double specular() const;
		virtual double trans() const;
		virtual double shine() const;
		virtual double hits(const vector_t base, const vector_t dir) const = 0;
		virtual vector_t lastHit() const
		{ return _lastHit; }
		
		virtual vector_t lastNormal() const { return _lastNorm; }
		
		virtual std::string toString() const override;
	};
}
}