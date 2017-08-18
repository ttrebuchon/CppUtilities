#pragma once
#include "SDLObject.h"

class SDL_Texture;


namespace QUtils::Drawing::SDL
{
	class Texture : public Internal::SDLObject<SDL_Texture, Texture>
	{
		typedef Internal::SDLObject<SDL_Texture, Texture> Base;
		friend Base;
		protected:
		Texture();
		Texture(SDL_Texture*);
		
		public:
		
		
		virtual ~Texture();
		
		
	};
}