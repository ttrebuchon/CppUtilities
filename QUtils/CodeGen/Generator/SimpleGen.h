#pragma once

#include <string>



namespace QUtils::CodeGen
{
	class SimpleGen
	{
		private:
		
		protected:
		std::vector<std::tuple<std::string, bool>> includes;
		
		public:
		SimpleGen();
		
		
		
		void addInclude(const std::string, bool relative = false);
		void addRelativeInclude(const std::string);
		void addAbsoluteInclude(const std::string);
		
		
		std::string* generate() const;
	};
}