#pragma once
#include "Env.h"


namespace QUtils
{
namespace Clips
{
	namespace Helpers
	{
		struct AtoS
		{
		template <typename ...T>
		static std::string ArgsToString(const std::string arg, const T... args)
		{
			static_assert(sizeof...(args) > 0, "This should not be reached");
			return arg + " " + ArgsToString(args...);
		}
		static std::string ArgsToString(const std::string arg)
		{
			return arg;
		}
		};
		
		
	}
	
	
	
	class Fact;
	
	template <typename ...T>
	std::shared_ptr<Fact> Environment::assert_f(const std::string relation, const T... values)
	{
		std::string assertStr = "(";
		assertStr += relation + " ";
		assertStr += Helpers::AtoS::ArgsToString(values...);
		
		
		return assert_f(assertStr + ")");
	}
}
}