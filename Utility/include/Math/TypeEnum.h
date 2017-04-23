#pragma once

namespace Util
{
namespace Math
{
	struct Exp_type {
	enum type
	{
		Constant,
		Num,
		Var,
		Addition,
		Division,
		Exponent,
		Multiplication,
		Subtraction,
	};
	};
	
	const Exp_type exp_type;
	
	
}
}