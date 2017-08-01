#pragma once

namespace QUtils
{
namespace SQL
{
	struct SQLRID
	{
		private:
		bool nullVal;
		unsigned long long rid;
		public:
		SQLRID(unsigned long long rid);
		SQLRID(std::nullptr_t);
		
		bool null() const
		{
			return nullVal;
		}
		
		unsigned long long val() const
		{
			return rid;
		}
		
		operator unsigned long long();
	};
}
}