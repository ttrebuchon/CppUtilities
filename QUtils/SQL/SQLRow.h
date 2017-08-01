#pragma once

#include <string>

namespace QUtils
{
namespace SQL
{
	class SQLQuery;
	
	namespace Internal
	{
		class SQLRowContainer
		{
			protected:
			int _rowid;
			int _pkIndex;
			std::string pkValue;
			const std::string table;
			std::shared_ptr<SQLQuery> rowQuery;
			SQLRowContainer(std::shared_ptr<SQLQuery>, const std::string table, const int pkIndex, const int rid);
			SQLRowContainer(std::shared_ptr<SQLQuery>, const std::string table, const int pkIndex, const std::string pkValue);
			
			public:
		};
	}
	
	
	
	class SQLRow
	{
		protected:
		std::shared_ptr<Internal::SQLRowContainer> container;
		
		SQLRow(std::shared_ptr<Internal::SQLRowContainer>);
		public:
		
		SQLRow& operator=(SQLRow&&);
		
		const int& rowid;
		const int& pkIndex;
		const std::string table;
	};
}
}