#pragma once

#include <memory>
#include <map>
#include <vector>

#include "SQLTypeDefs.h"
#include "SQLObjects/SQLDatabaseObject.h"
#include "SQLRID.h"
#include "SQLPK.h"
#include "SQLRow.h"




namespace QUtils
{
namespace SQL
{
	namespace Internal
	{
		class SQLRowContainer;
	}
	class SQLRow;
	class SQLRows;
	
namespace Internal
{
	class SQLRows_Obj
	{
		protected:
		
		virtual SQLRow operator[](SQLRID rid) const = 0;
		SQLRow at(SQLRID rid) const
		{ return (*this)[rid]; }
		
		virtual SQLRow operator[](SQLPK val) const = 0;
		SQLRow at(SQLPK val) const
		{ return (*this)[val]; }
		
		unsigned long count() const;
		inline unsigned long size() const
		{ return count(); }
		
		friend class ::QUtils::SQL::SQLRows;
	};
	
	
	
	class SQLRows_RID_Obj : public SQLRows_Obj
	{
		protected:
		std::map<SQLRID, std::shared_ptr<Internal::SQLRowContainer>> containers;
		
		virtual SQLRow operator[](SQLRID rid) const override;
		virtual SQLRow operator[](SQLPK val) const override;
		
		
	};
	
	
	class SQLRows_PK_Obj : public SQLRows_Obj
	{
		protected:
		std::map<SQLPK, std::shared_ptr<Internal::SQLRowContainer>> containers;
		
		virtual SQLRow operator[](SQLRID rid) const override;
		virtual SQLRow operator[](SQLPK val) const override;
		
	};
}
	
	class SQLRows : public SQLDatabaseObject
	{
		private:
		protected:
		std::shared_ptr<Internal::SQLRows_Obj> behind;
		
		SQLRows(std::shared_ptr<Internal::SQLRows_Obj>, const SQLDatabase&);
		public:
		
		
		SQLRow operator[](SQLRID rid) const;
		SQLRow operator[](SQLPK val) const;
		
		friend SQLTable;
		friend class Internal::SQLTable_Obj;
	};
}
}