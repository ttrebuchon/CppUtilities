#include "../Tests_Helpers.h"
#include <QUtils/GUI/SDL/SDL.h>

using namespace QUtils::SDL;

bool Test_SDL_GUI()
{
	SDLApp app;
	
	app.execute();
	return true;
}