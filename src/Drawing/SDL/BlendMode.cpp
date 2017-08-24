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
	
	#define DEFTYPE(x, y) { BlendMode::x, SDL_BLENDMODE_##y }
	
	static std::map<BlendMode, SDL_BlendMode> modes = {
		DEFTYPE(None, NONE),
		DEFTYPE(Blend, BLEND),
		DEFTYPE(Add, ADD),
		DEFTYPE(Mod, MOD),
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