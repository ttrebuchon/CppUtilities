#include <QUtils/English/Analysis.h>


namespace QUtils
{
namespace English
{
	
	
	
	
	Analyzer::Analyzer(std::ifstream& file) : _contents(), contents(_contents)
	{
		file.seekg(0, std::ios::end);
		_contents.resize(file.tellg());
		file.seekg(0, std::ios::beg);
		file.read(&_contents[0], _contents.size());
	}
	
	Analyzer::Analyzer(const std::string& contents) : _contents(contents), contents(_contents)
	{}
	
	Analyzer::Analyzer(const std::vector<std::string>& lines) : _contents(lines.at(0)), contents(_contents)
	{
		for (auto it = lines.begin()+1; it != lines.end(); ++it)
		{
			_contents += "\n" + *it;
		}
	}
}
}