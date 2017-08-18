#include <QUtils/Drawing/SDL/BlendMode.h>
#include "IfSDL.h"
#include <map>


namespace QUtils::Drawing::SDL
{
	namespace Helpers
	{
		std::map<SDL_BlendMode, BlendMode> reverseMap(const std::map<BlendMode, SDL_BlendMode>& map)
		{
			std::map<SDL_BlendMode, BlendMode> nMap;
			for (auto& pair : map)
			{
				nMap[pair.second] = pair.first;
			}
			return nMap;
		}
	}
	
	
	static std::map<BlendMode, SDL_BlendMode> modes = {
		{ None, SDL_BLENDMODE_NONE },
		{ Blend, SDL_BLENDMODE_BLEND },
		{ Add, SDL_BLENDMODE_ADD },
		{ Mod, SDL_BLENDMODE_MOD }
	};
	
	static std::map<SDL_BlendMode, BlendMode> revModes = Helpers::reverseMap(modes);
	
	
	
	int SDL_RawBlendMode(BlendMode mode)
	{
		return modes.at(mode);
	}
	
	BlendMode SDL_EnumBlendMode(int mode)
	{
		return revModes.at((SDL_BlendMode)mode);
	}
}