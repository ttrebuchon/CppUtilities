#include <QUtils/Drawing/SDL/TextureAccess.h>
#include "IfSDL.h"
#include <map>


namespace QUtils::Drawing::SDL
{
	#ifdef QUTILS_HAS_SDL2
	namespace Helpers
	{
		std::map<SDL_TextureAccess, TextureAccess> reverseMap(const std::map<TextureAccess, SDL_TextureAccess>& map)
		{
			std::map<SDL_TextureAccess, TextureAccess> nMap;
			for (auto& pair : map)
			{
				nMap[pair.second] = pair.first;
			}
			return nMap;
		}
	}
	
	#define DEFENUM(x, y) { TextureAccess::x, SDL_TEXTUREACCESS_##y }
	
	static std::map<TextureAccess, SDL_TextureAccess> accesses = {
		DEFENUM(Static, STATIC),
		DEFENUM(Streaming, STREAMING),
		DEFENUM(Target, TARGET),
	};
	
	static std::map<SDL_TextureAccess, TextureAccess> revAccesses = Helpers::reverseMap(accesses);
	
	#endif
	
	int SDL_RawTextureAccess(TextureAccess access)
	{
		#ifdef QUTILS_HAS_SDL2
		return accesses.at(access);
		#else
		throw NotAvail();
		#endif
	}
	
	TextureAccess SDL_EnumTextureAccess(int access)
	{
		#ifdef QUTILS_HAS_SDL2
		return revAccesses.at((SDL_TextureAccess)access);
		#else
		throw NotAvail();
		#endif
	}
}