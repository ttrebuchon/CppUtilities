#include <QUtils/Drawing/SDL/FontStyle.h>
#include <map>
#include "IfTTF.h"


namespace QUtils::Drawing::SDL
{
	#ifdef QUTILS_HAS_SDL2
	namespace Helpers
	{
		std::map<int, FontStyle> reverseMap(const std::map<FontStyle, int>& map)
		{
			std::map<int, FontStyle> nMap;
			for (auto& pair : map)
			{
				nMap[pair.second] = pair.first;
			}
			return nMap;
		}
	}
	
	#define DEFENUM(x, y) { FontStyle::x, TTF_STYLE_##y }
	
	static std::map<FontStyle, int> styles = {
		DEFENUM(Normal, NORMAL),
		DEFENUM(Bold, BOLD),
		DEFENUM(Italic, ITALIC),
		DEFENUM(Underline, UNDERLINE),
		DEFENUM(Strikethrough, STRIKETHROUGH),
	};
	
	static std::map<int, FontStyle> revStyles = Helpers::reverseMap(styles);
	
	#endif
	
	int SDL_RawFontStyle(FontStyle fl)
	{
		#ifdef QUTILS_HAS_SDL2
		int i = 0;
		for (const auto& pair : styles)
		{
			if ((int)(fl & pair.first) > 0)
			{
				i |= pair.second;
			}
		}
		return i;
		#else
		throw NotAvail();
		#endif
	}
	
	FontStyle SDL_EnumFontStyle(int fl)
	{
		#ifdef QUTILS_HAS_SDL2
		FontStyle i = (FontStyle)0;
		for (const auto& pair : revStyles)
		{
			if ((fl & pair.first) > 0)
			{
				i = i | pair.second;
			}
		}
		return i;
		#else
		throw NotAvail();
		#endif
	}
	
	
}