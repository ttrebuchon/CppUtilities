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
	
	
	static std::map<TextureAccess, SDL_TextureAccess> accesses = {
		{ Static, SDL_TEXTUREACCESS_STATIC },
		{ Streaming, SDL_TEXTUREACCESS_STREAMING },
		{ Target, SDL_TEXTUREACCESS_TARGET }
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