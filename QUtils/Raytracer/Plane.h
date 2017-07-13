#pragma once
#include "Object.h"
#include <memory>

namespace QUtils
{
namespace Raytracer
{
	class Plane : public Object
	{
		private:
		double NdotQ;
		
		protected:
		vector_t norm;
		vector_t point;
		
		public:
		Plane(std::string name, std::shared_ptr<Material> mat, const vector_t norm, const vector_t point);
		virtual ~Plane();
		
		virtual double hits(const vector_t base, const vector_t dir) const override;
		
		virtual std::string toString() const override;
		
	};
}
}