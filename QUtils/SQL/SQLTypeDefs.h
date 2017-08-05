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
		class SQLRows_Obj;
		class SQLRow_Obj;
		
	}
	
	typedef SQLObjectPointer<Internal::SQLDatabase_Obj> SQLDatabase;
	typedef SQLObjectPointer<Internal::SQLTable_Obj> SQLTable;
	typedef SQLObjectPointer<Internal::SQLRows_Obj> SQLRows;
	typedef SQLObjectPointer<Internal::SQLRow_Obj> SQLRow;
	
	
	
	
}
}