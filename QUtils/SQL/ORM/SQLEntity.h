#pragma once

namespace QUtils
{
namespace SQL
{
	class SQLMinEntity
	{
		protected:
		std::string _name;
		bool _notNull;
		bool _unique;
		
		public:
		SQLMinEntity(const std::string name) : _name(name), _notNull(false), _unique(false)
		{
			
		}
		
	};
	
	template <class Object>
	class SQLEntity : public SQLMinEntity
	{
		protected:
		
		public:
		SQLEntity(const std::string name) : SQLMinEntity(name)
		{
			
		}
	};
}
}