#pragma once

#include "../Node.h"

namespace QUtils::CodeGen
{
	class IncludeNode : public Node
	{
		private:
		
		protected:
		std::string path;
		bool relative;
		
		virtual IncludeNode* clone() const override;
		virtual void clone(IncludeNode*) const;
		
		public:
		IncludeNode(const std::string, bool relative = false);
		
		
		
		
		virtual std::string toString(const unsigned int indentation, bool startIndent = false) const override;
		
		std::shared_ptr<IncludeNode> copy() const;
		
		static std::shared_ptr<IncludeNode> Create(const std::string, bool = false);
	};
}