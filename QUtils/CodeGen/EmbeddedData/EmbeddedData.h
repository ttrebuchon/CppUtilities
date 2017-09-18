#pragma once

#include <string>

namespace QUtils::CodeGen
{
	class EmbeddedData
	{
		private:
		std::string lastResult;
		bool changed;
		
		protected:
		std::string _format;
		
		public:
		EmbeddedData();
		EmbeddedData(const std::string _template);
		
		
		
		
	};
}