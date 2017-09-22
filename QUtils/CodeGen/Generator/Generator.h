#pragma once

#include <string>
#include "Node.h"
#include "Nodes/Nodes.h"

namespace QUtils::CodeGen
{
	class Generator
	{
		private:
		
		int includeCount;
		
		protected:
		std::vector<std::shared_ptr<Node>> children;
		
		public:
		Generator();
		
		void addInclude(const std::string, bool relative = false);
		void addRelativeInclude(const std::string);
		void addAbsoluteInclude(const std::string);
		
		
		void generate(std::ostream&);
		std::string generate();
		
		void writeToFile(const std::string);
		
		std::shared_ptr<Node> at(const unsigned int);
		std::shared_ptr<const Node> at(const unsigned int) const;
		void add(std::shared_ptr<Node>);
		unsigned int size() const;
		void insert(const std::size_t, std::shared_ptr<Node>);
		
	};
}