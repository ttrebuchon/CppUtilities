#include <QUtils/Drawing/SDL/RendererFlip.h>
#include <map>
#include "IfSDL.h"


namespace QUtils::Drawing::SDL
{
	#ifdef QUTILS_HAS_SDL2
	namespace Helpers
	{
		std::map<unsigned int, RendererFlip> reverseMap(const std::map<RendererFlip, unsigned int>& map)
		{
			std::map<unsigned int, RendererFlip> nMap;
			for (auto& pair : map)
			{
				nMap[pair.second] = pair.first;
			}
			return nMap;
		}
	}
	
	#define DEFENUM(x, y) { RendererFlip::x, SDL_FLIP_##y }
	
	static std::map<RendererFlip, unsigned int> flips = {
		DEFENUM(None, NONE),
		DEFENUM(Horizontal, HORIZONTAL),
		DEFENUM(Vertical, VERTICAL),
	};
	
	static std::map<unsigned int, RendererFlip> revFlips = Helpers::reverseMap(flips);
	
	#endif
	
	unsigned int SDL_RawRendererFlip(RendererFlip fl)
	{
		#ifdef QUTILS_HAS_SDL2
		unsigned int i = 0;
		for (const auto& pair : flips)
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
	
	RendererFlip SDL_EnumRendererFlip(unsigned int fl)
	{
		#ifdef QUTILS_HAS_SDL2
		RendererFlip i = (RendererFlip)0;
		for (const auto& pair : revFlips)
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