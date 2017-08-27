#pragma once

#include "../AppWindow.h"

#include <string>

namespace QUtils::Drawing::SDL
{
	class Window;
	class Renderer;
}


namespace QUtils::GUI::SDL
{
	
	class SDLAppWindow : public AppWindow
	{
		private:
		
		protected:
		Drawing::SDL::Window* win;
		Drawing::SDL::Renderer* ren;
		
		//std::map<SDLTexture*, std::list<SDL_Rect>> textures;
		
		public:
		SDLAppWindow(const std::string name, const int x, const int y, const int w, const int h);
		virtual ~SDLAppWindow();
		
		virtual int width() const override;
		virtual int height() const override;
		virtual int x() const override;
		virtual int y() const override;
		
		virtual void update() override;
		virtual void handleEvents() override;
		
		
	};
}