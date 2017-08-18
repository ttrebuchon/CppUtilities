#include <QUtils/GUI/SDL/SDLApp.h>
#include <QUtils/GUI/SDL/SDLWindow.h>
#include <QUtils/GUI/SDL/Errors.h>


namespace QUtils::GUI::SDL
{
	SDLApp::SDLApp(const std::string title, const int x, const int y, const int w, const int h) : window(NULL)
	{
		window = new SDLWindow(title, x, y, w, h);
	}
	
	SDLApp::~SDLApp()
	{
		if (window != NULL)
		{
			delete window;
			window = NULL;
		}
	}
	
}