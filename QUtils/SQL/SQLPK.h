#pragma once

#include <string>

namespace QUtils
{
namespace SQL
{
	struct SQLPK
	{
		private:
		std::string val;
		public:
		SQLPK(std::string val) : val(val)
		{
			
		}
		SQLPK() : SQLPK("NULL") {}
		
		operator std::string()
		{ return val; }
		
	};
}
}