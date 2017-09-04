#pragma once

#include <exception>
#include <list>

#include "Exception.h"

namespace QUtils
{
	namespace Internal
	{
		QUTILS_CUSTOM_EXCEPTION(AggregateException, );
	}
	
	class AggregateException : public Internal::AggregateException
	{
		protected:
		std::list<std::exception_ptr> exceptions;
		
		public:
		AggregateException() : Internal::AggregateException(), exceptions()
		{
			
		}
		
		template <class Container>
		AggregateException(const Container& exs) : Internal::AggregateException(), exceptions()
		{
			for (std::exception_ptr ex : exs)
			{
				if (ex != NULL)
				{
					exceptions.push_back(ex);
				}
			}
		}
		
		void add(const std::exception_ptr ex)
		{
			if (ex != NULL)
			{
				exceptions.push_back(ex);
			}
		}
		
		auto size() const
		{
			return exceptions.size();
		}
		
		
		virtual void build() override
		{
			Internal::AggregateException::build();
			
			for (const auto& ex_ptr : exceptions)
			{
				try
				{
					std::rethrow_exception(ex_ptr);
				}
				catch (std::exception& ex)
				{
					_what += std::string("\n") + ex.what();
				}
			}
			_whatC = _what.c_str();
		}
		
		
	};
}