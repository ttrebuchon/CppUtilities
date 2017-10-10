#pragma once

#include <future>

#include "Message.h"
#include <QUtils/Exception/NotImplemented.h>

namespace QUtils
{
namespace Network
{
	template <class Ret = void>
	class ReturnMessage : public Message
	{
		private:
		
		protected:
		std::promise<Ret> prom;
		std::future<Ret> fut;
		std::shared_future<Ret> sfut;
		
		template <class F>
		void setValue(F f)
		{
			try
			{
				prom.set_value(f());
			}
			catch (...)
			{
				try
				{
					
				prom.set_exception(std::current_exception());
				}
				catch (std::exception& ex) {
					std::cerr << ex.what() << "\n";
				}
			}
		}
		
		void setException(std::exception_ptr ex)
		{
			prom.set_exception(ex);
		}
		
		public:
		
		ReturnMessage() : Message(true), prom(), fut(), sfut()
		{
			fut = prom.get_future();
			sfut = fut.share();
		}
		
		virtual std::shared_future<Ret> future()
		{
			//return fut.share();
			return sfut;
		}
		
		//DEBUG
		virtual void serialize(nlohmann::json&) const
		{
			throw NotImp();
		}
		
	};
	
	template <>
	template <class F>
	void ReturnMessage<void>::setValue(F f)
	{
		try
		{
		f();
		prom.set_value();
		}
		catch (...)
		{
			try
			{
			prom.set_exception(std::current_exception());
			}
			catch (std::exception& ex)
			{
				std::cerr << ex.what() << "\n";
			}
		}
	}
	
}
}