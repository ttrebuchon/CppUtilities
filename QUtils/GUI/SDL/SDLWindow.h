#pragma once

#include "../Window.h"
#include "SDLTexture.h"
#include "SDLSurface.h"

#include <string>

class SDL_Window;
class SDL_Renderer;

namespace QUtils::GUI::SDL
{
	
	class SDLWindow : public Window
	{
		private:
		
		protected:
		SDL_Window* win;
		SDL_Renderer* ren;
		
		//std::map<SDLTexture*, std::list<SDL_Rect>> textures;
		
		public:
		SDLWindow(const std::string name, const int x, const int y, const int w, const int h);
		virtual ~SDLWindow();
		
		virtual int width() const override;
		virtual int height() const override;
		virtual int x() const override;
		virtual int y() const override;
		
		virtual SDLTexture* createTexture(const int w, const int h) override;
		virtual SDLSurface* createSurface(int w, int h, int depth, int rmask = 0, int gmask = 0, int bmask = 0, int alphamask = 0) override;
		
		virtual void placeTexture(Texture*, int x, int y, int w, int h);
		
		virtual void update() override;
		virtual void handleEvents() override;
		virtual void clear(int r = 0, int g = 0, int b = 0) override;
		
		virtual SDLSurface* windowSurface();
		virtual const SDL_Renderer* renderer() const;
		
		virtual SDL_Renderer* renderer();
		virtual SDL_Window* operator*();
		
		
	};
}