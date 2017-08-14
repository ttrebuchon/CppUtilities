#pragma once

#include <string>

class SDL_Window;
namespace QUtils
{
namespace SDL
{
	
	class SDLApp
	{
		private:
		SDL_Window* window;
		public:
		SDLApp(const std::string title, int x, int y, int w, int h);
		
		virtual int execute();
	};
}
}