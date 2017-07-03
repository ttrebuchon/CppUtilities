#pragma once

#include "Tensor.h"
#include "tensor_t.h"

namespace QUtils
{
namespace Math
{
	namespace Internal
	{
		template <int Dims>
		class Tensor_Imp : public Tensor
		{
			protected:
			tensor_t<Dims, double, int> ten;
			
			public:
			
			
			
			virtual int order() const override
			{
				return Dims;
			}
			
		};
	}
}
}