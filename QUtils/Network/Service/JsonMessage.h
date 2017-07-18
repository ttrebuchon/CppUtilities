#pragma once

#include "Message.h"

namespace QUtils
{
namespace Network
{
	template <class Ret, class ...T>
	class JsonMessage : public ReturnMessage<Ret>
	{
		protected:
		std::string _name;
		std::string _contents;
		
		
		public:
		JsonMessage(std::string name, std::string contents) : _name(name), _contents(contents)
		{
			
		}
	};
}
}