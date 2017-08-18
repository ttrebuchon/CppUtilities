#pragma once
#include "SDLObject.h"


class SDL_Surface;


namespace QUtils::Drawing::SDL
{
	class Texture;
	class Renderer;
	
	class Surface : public Internal::SDLObject<SDL_Surface, Surface>
	{
		typedef Internal::SDLObject<SDL_Surface, Surface> Base;
		friend Base;
		protected:
		Surface();
		Surface(SDL_Surface*);
		
		public:
		
		
		
		virtual ~Surface();
		
		
		Texture* createTexture(Renderer*) const;
	};
}