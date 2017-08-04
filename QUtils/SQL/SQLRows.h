#pragma once

#include <memory>
#include <map>
#include <vector>

#include "SQLTypeDefs.h"
#include "SQLObjects/SQLTableObject.h"
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
	
namespace Internal
{
	class SQLRows_Obj : public SQLTableObject
	{
		protected:
		
		SQLRows_Obj(const SQLTable);
		
		public:
		virtual ~SQLRows_Obj();
		virtual SQLRow operator[](SQLRID rid) const = 0;
		SQLRow at(SQLRID rid) const
		{ return (*this)[rid]; }
		
		virtual SQLRow operator[](SQLPK val) const = 0;
		SQLRow at(SQLPK val) const
		{ return (*this)[val]; }
		
		unsigned long count() const;
		inline unsigned long size() const
		{ return count(); }
		
		friend ::QUtils::SQL::SQLRows;
		friend class SQLTable_Obj;
	};
	
	
	
	class SQLRows_RID_Obj : public SQLRows_Obj
	{
		protected:
		std::map<SQLRID, std::shared_ptr<Internal::SQLRowContainer>> containers;
		
		SQLRows_RID_Obj(const SQLTable);
		
		public:
		
		virtual SQLRow operator[](SQLRID rid) const override;
		virtual SQLRow operator[](SQLPK val) const override;
		
		friend ::QUtils::SQL::SQLRows;
		friend class SQLTable_Obj;
	};
	
	
	class SQLRows_PK_Obj : public SQLRows_Obj
	{
		protected:
		std::map<SQLPK, std::shared_ptr<Internal::SQLRowContainer>> containers;
		
		SQLRows_PK_Obj(const SQLTable);
		
		public:
		virtual SQLRow operator[](SQLRID rid) const override;
		virtual SQLRow operator[](SQLPK val) const override;
		
		friend ::QUtils::SQL::SQLRows;
		friend class SQLTable_Obj;
	};
}
	
	/*class SQLRows : public SQLDatabaseObject
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
	};*/
}
}