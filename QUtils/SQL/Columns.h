#pragma once

#include <memory>
#include <map>
#include <vector>



namespace QUtils
{
namespace SQL
{
	class Column;
	
	class Columns
	{
		private:
		
		
		
		Columns(std::vector<std::shared_ptr<Column>>& cols, std::map<std::string, std::shared_ptr<Column>>& colsByName, std::shared_ptr<Column>& PK) : columns(cols), columnsByName(colsByName), PK(PK)
		{}
		
		public:
		typedef typename std::vector<std::shared_ptr<Column>>::const_iterator iterator;
		
		const std::vector<std::shared_ptr<Column>>& columns;
		const std::map<std::string, std::shared_ptr<Column>>& columnsByName;
		
		const std::shared_ptr<Column>& PK;
		const Column& operator[](const std::string columnName) const;
		
		
		iterator begin() const;
		iterator end() const;
		
		friend class Table;
	};
}
}