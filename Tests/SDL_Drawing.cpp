#include "../Tests_Helpers.h"
#include <QUtils/Drawing/SDL/SDL.h>

#include "../src/Drawing/SDL/IfSDL.h"

using namespace QUtils::Drawing::SDL;
bool Test_SDL_Drawing()
{
	const int w = 1080;
	const int h = 1920;
	auto win = new Window("Window1", 0, 0, w, h, Shown | OpenGL);
	
	dout << SDL_WINDOW_SHOWN << ", " << SDL_WINDOW_HIDDEN << std::endl;
	
	win->hide();
	assert_ex(!win->visible());
	win->show();
	assert_ex(win->visible());
	
	auto winsurf = win->surface();
	win->updateSurface();
	
	if (winsurf != NULL)
	{
		delete winsurf;
	}
	
	if (win != NULL)
	{
		delete win;
	}
	
	return true;
}