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
	
	
	//Copy tex2 to tex and then copy
	//tex2 partially transparent,
	//horizontally and vertically
	//flipped, to the center
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
	
	#define FORMAT SDL_PIXELFORMAT_RGB888
	
	unsigned char* pixels = (unsigned char*)malloc(SDL_BYTESPERPIXEL(FORMAT)*w*h*sizeof(char));
	
	
	
	
	//Copy tex to window
	ren->target(NULL);
	ren->setDrawColor(0, 0, 0, 0);
	ren->clear();
	tex->colorMod(255, 255, 255);
	tex->alphaMod(255);
	ren->copy(tex);
	ren->renderPresent();
	
	
	ren->target(tex);
	ren->readPixels({w/4, h/4, w/2, h/2}, FORMAT, pixels, w/2);
	
	
	auto pixelChecker = [](unsigned char* ptr, unsigned char r, unsigned char g, unsigned char b, unsigned char alpha)
	{
		bool v = true;
		v = v && (ptr[0] == r);
		v = v && (ptr[1] == g);
		v = v && (ptr[2] == b);
		v = v && (ptr[3] == alpha);
		return v;
	};
	
	auto printPix = [](unsigned char* ptr, int size)
	{
		for (int j = 0; j < size-1; ++j)
		{
			dout << (int)ptr[j] << ", ";
		}
		dout << (int)ptr[size - 1] << "\n";
	};
	
	
	const int size = SDL_BYTESPERPIXEL(FORMAT);
	for (int i = 0; i < w/2*h/2; ++i)
	{
		//assert_ex(pixels[i*size+3] == 0);
		switch (pixels[i*size])
		{
			case 91:
			if (!pixelChecker(&pixels[i*size], 91, 255, 164, 0))
			{
				printPix(&pixels[i*size], size);
				assert_ex(false);
			}
			break;
			case 0:
			if (!(pixelChecker(&pixels[i*size], 0, 196, 196, 0) || pixelChecker(&pixels[i*size], 0, 0, 0, 0)))
			{
				printPix(&pixels[i*size], size);
				assert_ex(false);
			}
			break;
			case 59:
			if (!pixelChecker(&pixels[i*size], 59, 255, 196, 0))
			{
				printPix(&pixels[i*size], size);
				assert_ex(false);
			}
			break;
			default:
			{
				printPix(&pixels[i*size], size);
				assert_ex(false);
			}
			break;
		}
		
		
	}
	
	
	SDL_Delay(1000);
	
	
	
	
	
	
	auto surf = new Surface(w, h, FORMAT);
	auto sren = surf->createSoftwareRenderer();
	sren->clear();
	
	
	auto surf2 = new Surface(w, h, FORMAT);
	auto sren2 = surf2->createSoftwareRenderer();
	sren2->clear();
	
	const int tileW = w/(20.4);
	const int tileH = tileW;
	
	const int offset = w/10;
	
	sren2->setDrawColor(0, 200, 255, 255);
	for (int x = 0; x < w + offset; x += tileW)
	{
		for (int y = (x/tileW % 2)*tileH; y < h; y += tileH*2)
		{
			sren2->fillRect({x-offset, y, tileW, tileH});
		}
	}
	
	
	
	sren2->setDrawColor(200, 0, 255, 255);
	
	for (int x = 0; x < w + offset; x += tileW)
	{
		for (int y = ((x/tileW % 2)*-1 + 1)*tileH; y < h; y += tileH*2)
		{
			sren2->fillRect({x - offset, y, tileW, tileH});
		}
	}
	
	surf2->blitTo(surf, {0, 0, surf2->w(), surf2->h()}, {0, 0, w, h});
	
	sren->blendMode(Blend);
	sren->setDrawColor(255, 0, 0, 200);
	sren->fillRect({0, 0, w/2, h/2});
	sren->renderPresent();
	
	
	auto tex3 = surf->createTexture(ren);
	
	
	ren->target(NULL);
	ren->setDrawColor(0, 0, 0, 255);
	ren->clear();
	ren->copy(tex3);
	ren->renderPresent();
	
	SDL_Delay(1000);
	
	free(pixels);
	pixels = (unsigned char*)surf->pixels();
	
	for (int i = 0; i < surf->w()*surf->h(); ++i)
	{
		//assert_ex(pixels[i*size+3] == 0);
		switch (pixels[i*size])
		{
			case 255:
			if (!(pixelChecker(&pixels[i*size], 255, 200, 0, 0) || pixelChecker(&pixels[i*size], 255, 0, 200, 0)))
			{
				printPix(&pixels[i*size], size);
				assert_ex(false);
			}
			break;
			case 55:
			if (!(pixelChecker(&pixels[i*size], 55, 43, 200, 0) || pixelChecker(&pixels[i*size], 55, 0, 243, 0)))
			{
				printPix(&pixels[i*size], size);
				assert_ex(false);
			}
			break; 
			default:
			{
				printPix(&pixels[i*size], size);
				assert_ex(false);
			}
			break;
		}
		
		
	}
	
	
	
	
	/*if (winsurf != NULL)
	{
		delete winsurf;
	}*/
	
	if (tex3 != NULL)
	{
		delete tex3;
	}
	
	if (surf2 != NULL)
	{
		delete surf2;
	}
	
	if (surf != NULL)
	{
		delete surf;
	}
	
	if (sren != NULL)
	{
		delete sren;
	}
	
	if (sren2 != NULL)
	{
		delete sren2;
	}
	
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