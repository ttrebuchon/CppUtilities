#include "../Tests_Helpers.h"
#include <QUtils/Drawing/SDL/SDL.h>

using namespace QUtils::Drawing::SDL;
bool Test_SDL_Drawing()
{
	const int w = 1080;
	const int h = 1920;
	auto win = new Window("Window1", 0, 0, w, h, Shown | OpenGL);
	
	if (win != NULL)
	{
		delete win;
	}
	return true;
}