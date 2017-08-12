#pragma once

#include "SQLDatabaseObject.h"

namespace QUtils
{
namespace SQL
{
	class SQLTableObject : public SQLDatabaseObject
	{
		protected:
		SQLTable _table;
		
		SQLTableObject(const SQLTable DB);
		
		public:
		const SQLTable& table;
		
		SQLTableObject& operator=(const SQLTableObject&);
	};
}
}