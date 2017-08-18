#pragma once

#include <string>


namespace QUtils::GUI::SDL
{
	class SDLWindow;
	
	class SDLApp
	{
		private:
		SDLWindow* window;
		public:
		SDLApp(const std::string title, const int x, const int y, const int w, const int h);
		~SDLApp();
		
		
	};
}