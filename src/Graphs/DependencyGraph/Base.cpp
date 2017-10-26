#include <QUtils/Graphs/DependencyGraph/Base.h>


namespace QUtils { namespace Graphs {
namespace DependencyGraph_NS {
	
	DependencyGraph_Base::DependencyGraph_Base() : Graph()
	{
		
	}
	
	std::shared_ptr<Node> DependencyGraph_Base::getNext()
	{
		throw NotImp();
	}
	
	std::size_t DependencyGraph_Base::ready() const
	{
		throw NotImp();
	}
	
	void DependencyGraph_Base::push_back(const Node_ptr node)
	{
		throw NotImp();
	}
}
}
}