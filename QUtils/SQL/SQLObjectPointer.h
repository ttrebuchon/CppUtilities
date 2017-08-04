#pragma once

#include <memory>
#include <QUtils/Types/OperatorForwarding.h>

namespace QUtils
{
namespace SQL
{
	
	template <class Object>
	class SQLObjectPointer : public Types::AllOperatorForward<Object>
	{
		protected:
		std::shared_ptr<Object> obj;
		
		
		public:
		SQLObjectPointer(std::shared_ptr<Object> obj) : Types::AllOperatorForward<Object>(obj.get()), obj(obj) {}
		
		template <class ...Args>
		static SQLObjectPointer Create(Args... args)
		{
			auto obj = new Object(args...);
			try
			{
				return obj->shared_from_this();
			}
			catch (std::bad_weak_ptr&)
			{
				return std::shared_ptr<Object>(obj);
			}
			//return SQLObjectPointer(std::shared_ptr<Object>(new Object(args...)));
		}
		
		auto operator->() const
		{
			return obj;
		}
		
		auto operator->()
		{
			return obj;
		}
		
	};
}
}