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
			return SQLObjectPointer(std::shared_ptr<Object>(new Object(args...)));
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