#include <QUtils/Drawing/SDL/RendererFlags.h>
#include <map>
#include "IfSDL.h"


namespace QUtils::Drawing::SDL
{
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
	
	
	static std::map<RendererFlags, unsigned int> flags = {
		{ Software, SDL_RENDERER_SOFTWARE },
		{ Accelerated, SDL_RENDERER_ACCELERATED },
		{ PresentVsync, SDL_RENDERER_PRESENTVSYNC },
		{ TargetTexture, SDL_RENDERER_TARGETTEXTURE }
	};
	
	static std::map<unsigned int, RendererFlags> revFlags = Helpers::reverseMap(flags);
	
	
	unsigned int SDL_RawRendererFlags(RendererFlags fl)
	{
		unsigned int i = 0;
		for (const auto& pair : flags)
		{
			if ((fl & pair.first) > 0)
			{
				i |= pair.second;
			}
		}
		return i;
	}
	
	RendererFlags SDL_EnumRendererFlags(unsigned int fl)
	{
		RendererFlags i = (RendererFlags)0;
		for (const auto& pair : revFlags)
		{
			if ((fl & pair.first) > 0)
			{
				i = i | pair.second;
			}
		}
		return i;
	}
	
	
}