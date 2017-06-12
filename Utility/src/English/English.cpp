#include <English/English.h>

namespace Util
{
namespace English
{
	Language::Language(Lang lang) : words(), filename(FileTable().at(lang))
	{
		
	}
	
	bool Language::load()
	{
		
		
		return true;
	}
}
}