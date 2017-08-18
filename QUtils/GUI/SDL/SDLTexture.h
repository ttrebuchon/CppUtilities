#pragma once

#include "../Texture.h"
#include "SDLWindowChild.h"

class SDL_Texture;
class SDL_Surface;
class SDL_Renderer;


namespace QUtils::GUI::SDL
{
	
	class SDLTexture : public Texture, public SDLWindowChild
	{
		protected:
		SDL_Texture* tex;
		SDL_Renderer* ren;
		
		SDLTexture(SDLWindow*);
		
		public:
		SDLTexture(SDLWindow*, const int w, const int h);
		SDLTexture(SDLWindow*, SDL_Surface*);
		virtual ~SDLTexture();
		
		virtual void fillRect(int x, int y, int w, int h, int r, int g, int b, int alpha) override;
		
		virtual void render(int x, int y, int w, int h);
		
		
		
		virtual void placeTexture(Texture*, int x, int y, int w, int h) override;
		virtual void update() override;
		virtual void clear(int r = 0, int g = 0, int b = 0) override;
		
		friend class SDLWindow;
	};
}