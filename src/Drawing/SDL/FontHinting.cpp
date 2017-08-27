#include <QUtils/Drawing/SDL/FontHinting.h>
#include "IfTTF.h"
#include <map>


namespace QUtils::Drawing::SDL
{
	namespace Helpers
	{
		std::map<int, FontHinting> reverseMap(const std::map<FontHinting, int>& map)
		{
			std::map<int, FontHinting> nMap;
			for (auto& pair : map)
			{
				nMap[pair.second] = pair.first;
			}
			return nMap;
		}
	}
	
	#define DEFENUM(x, y) { FontHinting::x, TTF_HINTING_##y }
	
	static std::map<FontHinting, int> hintings = {
		DEFENUM(Normal, NORMAL),
		DEFENUM(Light, LIGHT),
		DEFENUM(Mono, MONO),
		DEFENUM(None, NONE),
	};
	
	static std::map<int, FontHinting> revHintings = Helpers::reverseMap(hintings);
	
	
	
	int SDL_RawFontHinting(FontHinting hinting)
	{
		return hintings.at(hinting);
	}
	
	FontHinting SDL_EnumFontHinting(int hinting)
	{
		return revHintings.at((int)hinting);
	}
}