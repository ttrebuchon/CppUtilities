#pragma once

#include "../Surface.h"
#include "SDLWindowChild.h"

class SDL_Surface;
class SDL_Renderer;

namespace QUtils::GUI::SDL
{
	class SDLWindow;
	class SDLTexture;
	
	
	class SDLSurface : public Surface, public SDLWindowChild
	{
		protected:
		SDL_Surface* surf;
		bool owned;
		SDL_Renderer* _ren;
		
		virtual void createRenderer();
		
		public:
		SDLSurface(SDLWindow*, SDL_Surface*, bool owned);
		
		virtual ~SDLSurface();
		
		virtual void copyTo(SDLSurface*) const;
		
		virtual SDLTexture* toTexture() const;
		inline SDL_Renderer* ren()
		{
			if (!_ren)
			{
				createRenderer();
			}
			return _ren;
		}
		
		
	};
}