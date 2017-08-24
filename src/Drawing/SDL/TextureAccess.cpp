#include <QUtils/Drawing/SDL/TextureAccess.h>
#include "IfSDL.h"
#include <map>


namespace QUtils::Drawing::SDL
{
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
	
	
	
	int SDL_RawTextureAccess(TextureAccess access)
	{
		return accesses.at(access);
	}
	
	TextureAccess SDL_EnumTextureAccess(int access)
	{
		return revAccesses.at((SDL_TextureAccess)access);
	}
}