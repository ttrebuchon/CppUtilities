#pragma once
#include "ValueType.h"
#include <string>

namespace Util
{
namespace SQL
{
	class Query
	{
		protected:
		virtual double columnDouble(int) = 0;
		virtual int columnInt(int) = 0;
		virtual long columnLong(int) = 0;
		virtual std::string columnString(int) = 0;
		
		
		public:
		
		virtual ~Query();
		
		template <class T> T column(int Index);
		
		virtual int count() const = 0;
		virtual ValueType columnType(int Index) const = 0;
		virtual bool columnNULL(int) = 0;
		virtual bool next() = 0;
		virtual void reset() = 0;
		virtual bool operator()() = 0;
		
	};
	
}
}