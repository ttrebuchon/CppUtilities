#include <QUtils/Drawing/SDL/BlendMode.h>
#include "IfSDL.h"
#include <map>


namespace QUtils::Drawing::SDL
{
	#ifdef QUTILS_HAS_SDL2
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
	
	#endif
	
	int SDL_RawBlendMode(BlendMode mode)
	{
		#ifdef QUTILS_HAS_SDL2
		return modes.at(mode);
		#else
		throw NotAvail();
		#endif
	}
	
	BlendMode SDL_EnumBlendMode(int mode)
	{
		#ifdef QUTILS_HAS_SDL2
		return revModes.at((SDL_BlendMode)mode);
		#else
		throw NotAvail();
		#endif
	}
}