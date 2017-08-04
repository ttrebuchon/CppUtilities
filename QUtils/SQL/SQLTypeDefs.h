#pragma once
#include "SQLObjectPointer.h"

namespace QUtils
{
namespace SQL
{
	namespace Internal
	{
		class SQLDatabase_Obj;
		class SQLTable_Obj;
		
		
	}
	
	typedef SQLObjectPointer<Internal::SQLDatabase_Obj> SQLDatabase;
	typedef SQLObjectPointer<Internal::SQLTable_Obj> SQLTable;
	
	
	
	
}
}