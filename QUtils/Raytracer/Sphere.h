#pragma once
#include "Object.h"
#include <memory>

namespace QUtils
{
namespace Raytracer
{
	class Sphere : public Object
	{
		private:
		
		protected:
		double radius;
		vector_t center;
		
		public:
		Sphere(std::string name, std::shared_ptr<Material> mat, double radius, const vector_t center);
		virtual ~Sphere();
		
		virtual double hits(const vector_t base, const vector_t dir) const override;
		
		virtual void move(const vector_t offset);
		
		virtual std::string toString() const override;
		
	};
}
}