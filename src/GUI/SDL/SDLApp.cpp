#include <QUtils/GUI/SDL/SDLApp.h>

#ifdef QUTILS_HAS_SDL2

#include <SDL2/SDL.h>

#else

#include <QUtils/Exception/NotAvailable.h>

#endif

namespace QUtils
{
namespace SDL
{
	SDLApp::SDLApp(const std::string title, int x, int y, int w, int h) : window(NULL)
	{
		#ifdef QUTILS_HAS_SDL2
		window = SDL_CreateWindow(title.c_str(), x, y, w, h, SDL_WINDOW_SHOWN);
		#else
		throw NotAvail();
		#endif
	}
	
	int SDLApp::execute()
	{
		return -1;
	}
}
}