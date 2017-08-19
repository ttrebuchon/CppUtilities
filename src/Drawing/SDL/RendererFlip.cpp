#include <QUtils/Drawing/SDL/RendererFlip.h>
#include <map>
#include "IfSDL.h"


namespace QUtils::Drawing::SDL
{
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
	
	
	static std::map<RendererFlip, unsigned int> flips = {
		{ NoFlip, SDL_FLIP_NONE },
		{ Horizontal, SDL_FLIP_HORIZONTAL },
		{ Vertical, SDL_FLIP_VERTICAL }
	};
	
	static std::map<unsigned int, RendererFlip> revFlips = Helpers::reverseMap(flips);
	
	
	unsigned int SDL_RawRendererFlip(RendererFlip fl)
	{
		unsigned int i = 0;
		for (const auto& pair : flips)
		{
			if ((fl & pair.first) > 0)
			{
				i |= pair.second;
			}
		}
		return i;
	}
	
	RendererFlip SDL_EnumRendererFlip(unsigned int fl)
	{
		RendererFlip i = (RendererFlip)0;
		for (const auto& pair : revFlips)
		{
			if ((fl & pair.first) > 0)
			{
				i = i | pair.second;
			}
		}
		return i;
	}
	
	
}