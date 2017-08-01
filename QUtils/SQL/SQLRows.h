#pragma once

#include <memory>
#include <map>
#include <vector>

#include "SQLRID.h"
#include "SQLPK.h"



namespace QUtils
{
namespace SQL
{
	namespace Internal
	{
		class SQLRowContainer;
	}
	class SQLRow;
	
	class SQLRows
	{
		private:
		
		
		protected:
		
		
		public:
	};
	
	class SQLRows_RID : public SQLRows
	{
		protected:
		std::map<SQLRID, std::shared_ptr<Internal::SQLRowContainer>> containers;
		
		public:
	};
	
	class SQLRows_PK : public SQLRows
	{
		protected:
		std::map<SQLPK, std::shared_ptr<Internal::SQLRowContainer>> containers;
		
		public:
	};
}
}