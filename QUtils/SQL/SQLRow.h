#pragma once

#include <string>

#include "SQLRID.h"

namespace QUtils
{
namespace SQL
{
	class SQLQuery;
	
	namespace Internal
	{
		class SQLRows_RID_Obj;
		class SQLRows_PK_Obj;
		
		
		class SQLRow_Obj
		{
			protected:
			SQLRID _rowid;
			int _pkIndex;
			std::string pkValue;
			std::shared_ptr<SQLQuery> rowQuery;
			SQLRow_Obj(std::shared_ptr<SQLQuery>, const std::string table, SQLRID rid);
			SQLRow_Obj(std::shared_ptr<SQLQuery>, const std::string table, const int pkIndex, const std::string pkValue);
			
			public:
			
			virtual ~SQLRow_Obj();
			
			const SQLRID& rowid;
			const int& pkIndex;
			const std::string table;
			
			std::string operator[](const size_t);
			std::string operator[](const std::string);
			
			friend SQLRows_RID_Obj;
			friend SQLRows_PK_Obj;
		};
	}
	
	
	
	/*class SQLRow
	{
		protected:
		std::shared_ptr<Internal::SQLRowContainer> container;
		
		SQLRow(std::shared_ptr<Internal::SQLRowContainer>);
		public:
		SQLRow(const SQLRow&);
		
		SQLRow& operator=(SQLRow&&);
		
		const int& rowid;
		const int& pkIndex;
		const std::string table;
		
		friend class Internal::SQLRows_RID_Obj;
		friend class Internal::SQLRows_PK_Obj;
	};*/
}
}