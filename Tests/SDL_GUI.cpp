#include "../Tests_Helpers.h"
#include <QUtils/GUI/SDL/SDL.h>

using namespace QUtils::SDL;

bool Test_SDL_GUI()
{
	dout << "Creating app...\n";
	SDLApp app("", 0, 0, 640, 480);
	
	app.execute();
	return true;
}