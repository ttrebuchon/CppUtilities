#include <QUtils/CodeGen/Generator/Generator.h>

#include <sstream>
#include <fstream>


namespace QUtils::CodeGen
{
	Generator::Generator() : children()
	{
		
	}
	
	
	void Generator::generate(std::ostream& out)
	{
		for (auto child : children)
		{
			if (child != NULL)
			{
				out << child->toString(0, true);
			}
		}
	}
	
	std::string Generator::generate()
	{
		std::stringstream out;
		generate(out);
		return out.str();
	}
	
	
	
	void Generator::writeToFile(const std::string filename)
	{
		std::ofstream file(filename);
		generate(file);
		file.close();
	}
	
	
	std::shared_ptr<Node> Generator::at(const unsigned int index)
	{
		return children.at(index);
	}
	
	std::shared_ptr<const Node> Generator::at(const unsigned int index) const
	{
		return children.at(index);
	}
	
	void Generator::add(std::shared_ptr<Node> child)
	{
		children.push_back(child);
	}
	
	unsigned int Generator::size() const
	{
		return children.size();
	}
	
	void Generator::insert(const std::size_t index, std::shared_ptr<Node> node)
	{
		children.insert(children.begin() + index, node);
	}
}