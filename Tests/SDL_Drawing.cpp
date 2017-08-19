#include "../Tests_Helpers.h"
#include <QUtils/Drawing/SDL/SDL.h>

#include "../src/Drawing/SDL/IfSDL.h"

using namespace QUtils::Drawing::SDL;
bool Test_SDL_Drawing()
{
	const int w = 1080;
	const int h = 1920;
	auto win = new Window("Window1", 0, 0, w, h, Shown | OpenGL);
	
	
	win->hide();
	assert_ex(!win->visible());
	win->show();
	assert_ex(win->visible());
	
	auto ren = new Renderer(win, -1, Accelerated | TargetTexture);
	dout << "Renderer Created\n";
	//auto winsurf = win->surface();
	win->updateSurface();
	
	
	auto tex = new Texture(ren, SDL_PIXELFORMAT_RGB555, Target, w, h);
	auto tex2 = new Texture(ren, SDL_PIXELFORMAT_RGB555, Target, w, h);
	assert_ex(tex->blendMode() == tex2->blendMode());
	assert_ex(tex->blendMode() == None);
	
	//Set window to pure aqua
	ren->target(NULL);
	ren->setDrawColor(0, 255, 255, 255);
	ren->clear();
	ren->renderPresent();
	
	//Fill tex2 with yellow, then
	//add black rect in the middle
	ren->target(tex2);
	ren->setDrawColor(255, 255, 0, 255);
	ren->clear();
	ren->setDrawColor(0, 0, 0, 255);
	ren->fillRect(w/4, h/4, w/2, h/2);
	ren->renderPresent();
	
	//Copy tex2 onto tex such that the
	//left is yellow, and the right is
	//black
	ren->target(tex);
	ren->clear();
	ren->copy(tex2, { 0, h/4, w/2, h/2 }, {0, 0, w, h});
	ren->renderPresent();
	
	
	
	//Fill tex2 with aqua and copy 
	//tex with partial transparency
	//to the bottom half
	ren->target(tex2);
	ren->setDrawColor(0, 255, 255, 255);
	ren->clear();
	tex->blendMode(Blend);
	tex->alphaMod(150);
	ren->copy(tex, NULL, {0, h/2, w, h/2 });
	ren->renderPresent();
	
	
	//Copy tex2 to tex and copy a
	//partially transparent,
	//horizontally and vertically
	//flipped, tex2 to the center
	//of tex
	ren->target(tex);
	ren->blendMode(None);
	ren->setDrawColor(255, 0, 0, 0);
	ren->clear();
	tex->alphaMod(255);
	tex2->alphaMod(255);
	tex->colorMod(255, 255, 255);
	tex2->colorMod(255, 255, 255);
	tex->blendMode(None);
	tex2->blendMode(None);
	ren->copy(tex2);
	tex2->alphaMod(100);
	tex2->blendMode(Blend);
	ren->copy(tex2, NULL, {w/4, h/4, w/2, h/2}, 0, NULL, Horizontal | Vertical);
	ren->renderPresent();
	
	
	//Copy tex to window
	ren->target(NULL);
	ren->clear();
	tex->colorMod(255, 255, 255);
	tex->alphaMod(255);
	ren->copy(tex);
	ren->renderPresent();
	
	
	SDL_Delay(2000);
	
	/*if (winsurf != NULL)
	{
		delete winsurf;
	}*/
	
	if (tex != NULL)
	{
		delete tex;
	}
	
	if (tex2 != NULL)
	{
		delete tex2;
	}
	
	if (ren != NULL)
	{
		delete ren;
	}
	
	if (win != NULL)
	{
		delete win;
	}
	
	return true;
}