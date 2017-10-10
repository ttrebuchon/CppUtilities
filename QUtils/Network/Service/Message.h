#pragma once

#include "Service.h"

#include <json/json.hpp>


namespace QUtils
{
namespace Network
{
	class Service;
	
	class Message
	{
		private:
		const std::chrono::system_clock::time_point createTime = std::chrono::system_clock::now();
		
		protected:
		Message(const bool responseRequired = false) : responseRequired(responseRequired)
		{

		}
		
		
		
		virtual void visit(Service& srv)
		{
			srv.process(*this);
		}
		
		public:
		const bool responseRequired;

		virtual int priority() const = 0;
		virtual std::chrono::system_clock::time_point time() const
		{
			return createTime;
		}
		
		virtual void serialize(nlohmann::json&) const = 0;
		
		template <class Service_t>
		friend class ServiceRouter;
	};
	
	void to_json(nlohmann::json& j, const Message& msg);
	void from_json(const nlohmann::json& j, Message& msg);
	
}
}