#pragma once

namespace QUtils
{
namespace SQL
{
	struct SQLRID
	{
		private:
		unsigned long long rid;
		public:
		explicit SQLRID(unsigned long long rid) : rid(rid) {}
		
		operator unsigned long long() const
		{ return rid; }
	};
}
}