#include <QUtils/CodeGen/Generator/Nodes/FunctionBody.h>


namespace QUtils::CodeGen
{
	FunctionBodyNode* FunctionBodyNode::clone() const
	{
		auto ptr = new FunctionBodyNode();
		this->clone(ptr);
		return ptr;
	}
	
	void FunctionBodyNode::clone(FunctionBodyNode* ptr) const
	{
		BodyNode::clone(ptr);
	}
	
	
	
	FunctionBodyNode::FunctionBodyNode() : BodyNode(), children(BodyNode::children)
	{
		
	}
	
	std::string FunctionBodyNode::toString(const unsigned int indentation, bool startIndent) const
	{
		return BodyNode::toString(indentation, true);
	}
		
	std::shared_ptr<FunctionBodyNode> FunctionBodyNode::copy() const
	{
		return std::shared_ptr<FunctionBodyNode>(clone());
	}
	
	std::shared_ptr<FunctionBodyNode> FunctionBodyNode::Create()
	{
		return std::make_shared<FunctionBodyNode>();
	}
}