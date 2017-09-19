#include <QUtils/CodeGen/EmbeddedData/EmbeddedData.h>
#include <QUtils/String/String.h>
#include <fstream>
#include <sstream>
#include <list>


namespace QUtils::CodeGen
{
	void escapeString(QUtils::String& str)
	{
		str = str.replace("\\", "\\\\").replace("\n", "\\n").replace("\"", "\\\"").replace("\t", "\\t").replace("\r", "\\r");
	}
	
	
	EmbeddedData::EmbeddedData() : EmbeddedData("")
	{
		
	}
	
	EmbeddedData::EmbeddedData(const std::string _template) : lastResult(), changed(true), _format(), _template(_template), _replaceSym(), data()
	{
		
	}
	
	
	
	void EmbeddedData::setTemplate(const std::string str)
	{
		changed = true;
		_template = str;
	}
	
	const std::string& EmbeddedData::getTemplate() const
	{
		return _template;
	}
		
	void EmbeddedData::setFormat(const std::string str)
	{
		changed = true;
		_format = str;
	}
	
	const std::string& EmbeddedData::getFormat() const
	{
		return _format;
	}
	
		
	void EmbeddedData::setReplace(const std::string str)
	{
		changed = true;
		_replaceSym = str;
	}
	
	const std::string& EmbeddedData::getReplace() const
	{
		return _replaceSym;
	}
	
	
	void EmbeddedData::fileWrite(const std::string filename) const
	{
		if (changed)
		{
			generate();
		}
		
		std::ofstream file(filename);
		file << lastResult;
		file.close();
	}
	
	void EmbeddedData::generate() const
	{
		//TODO
		std::list<std::vector<QUtils::String>> values;
		for (auto item : data)
		{
			values.push_back(std::vector<QUtils::String>());
			auto& back = values.back();
			for (auto s : item->strings())
			{
				back.push_back(s);
			}
			//item->embed(ss, segments);
		}
		
		std::vector<std::string> segments;
		//TODO
		//segments = ...
		
		std::stringstream ss;
		
		for (auto& vals : values)
		{
			//TODO
			
			QUtils::String entry = _format;
			int index = 0;
			while (entry.contains("${" + std::to_string(index) + "}") || index < vals.size())
			{
				
				if (index >= vals.size())
				{
					entry = entry.replace("${" + std::to_string(index) + "}", "");
				}
				else
				{
					escapeString(vals[index]);
					entry = entry.replace("${" + std::to_string(index) + "}", vals[index]);
				}
				
				
				++index;
			}
			ss << entry;
		}
		
		QUtils::String str = _template;
		lastResult = QUtils::String(_template).replace(_replaceSym, ss.str());
		
		changed = false;
	}
}