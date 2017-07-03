#pragma once
#include <memory>

namespace QUtils
{
namespace Math
{
	class Tensor
	{
		private:
		
		public:
		typedef std::shared_ptr<Tensor> Tensor_R;
		typedef std::shared_ptr<const Tensor> Tensor_CR;
		
		virtual int order() const = 0;
		virtual size_t size(const int) const = 0;
		virtual double det() const = 0;
		virtual Tensor_R contract(const Tensor&) const = 0;
		
		virtual Tensor_R operator*(const double) const = 0;
		
		virtual Tensor_R operator*(const Tensor&) const = 0;
		
		virtual Tensor_R operator/(const double) const = 0;
		
		virtual Tensor_R operator/(const Tensor&) const = 0;
		
		virtual Tensor_R operator+(const double) const = 0;
		
		virtual Tensor_R operator+(const Tensor&) const = 0;
		
		virtual Tensor_R operator-(const double) const = 0;
		
		virtual Tensor_R operator-(const Tensor&) const = 0;
		
		virtual Tensor_R operator[](const int) const = 0;
		
		virtual Tensor_R operator()(const int) = 0;
		
		virtual Tensor_CR operator()(const int) const = 0;
		
	};
}
}