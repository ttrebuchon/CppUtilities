#include <QUtils/Drawing/SDL/RendererFlags.h>
#include <map>
#include "IfSDL.h"


namespace QUtils::Drawing::SDL
{
	#ifdef QUTILS_HAS_SDL2
	namespace Helpers
	{
		std::map<unsigned int, RendererFlags> reverseMap(const std::map<RendererFlags, unsigned int>& map)
		{
			std::map<unsigned int, RendererFlags> nMap;
			for (auto& pair : map)
			{
				nMap[pair.second] = pair.first;
			}
			return nMap;
		}
	}
	
	#define DEFENUM(x, y) { RendererFlags::x, SDL_RENDERER_##y }
	
	static std::map<RendererFlags, unsigned int> flags = {
		DEFENUM(Software, SOFTWARE),
		DEFENUM(Accelerated, ACCELERATED),
		DEFENUM(PresentVsync, PRESENTVSYNC),
		DEFENUM(TargetTexture, TARGETTEXTURE),
	};
	
	static std::map<unsigned int, RendererFlags> revFlags = Helpers::reverseMap(flags);
	
	#endif
	
	unsigned int SDL_RawRendererFlags(RendererFlags fl)
	{
		#ifdef QUTILS_HAS_SDL2
		unsigned int i = 0;
		for (const auto& pair : flags)
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
	
	RendererFlags SDL_EnumRendererFlags(unsigned int fl)
	{
		#ifdef QUTILS_HAS_SDL2
		RendererFlags i = (RendererFlags)0;
		for (const auto& pair : revFlags)
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