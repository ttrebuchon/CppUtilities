#include "../Tests_Helpers.h"
#include <QUtils/Drawing/SDL/SDL.h>

#include "../src/Drawing/SDL/IfSDL.h"

#include <QUtils/Types/CompilerPrint.h>

template <int N, class... T>
int EventCB(T...)
{
	dout << "EventCB Called\n";
	return N;
}


using namespace QUtils::Drawing::SDL;
bool Test_SDL_Drawing()
{
	const int w = 1080;
	const int h = 1920;
	Window* win = NULL;
	try
	{
	win = new Window("Window1", 0, 0, w, h, WindowFlags::Shown | WindowFlags::OpenGL);
	
	
	win->hide();
	assert_ex(!win->visible());
	win->show();
	assert_ex(win->visible());
	
	auto ren = new Renderer(win, -1, RendererFlags::Accelerated | RendererFlags::TargetTexture);
	dout << "Renderer Created\n";
	//auto winsurf = win->surface();
	win->updateSurface();
	
	
	auto tex = new Texture(ren, PixelFormat::RGB555, TextureAccess::Target, w, h);
	auto tex2 = new Texture(ren, PixelFormat::RGB555, TextureAccess::Target, w, h);
	assert_ex(tex->blendMode() == tex2->blendMode());
	assert_ex(tex->blendMode() == BlendMode::None);
	
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
	tex->blendMode(BlendMode::Blend);
	tex->alphaMod(150);
	ren->copy(tex, NULL, {0, h/2, w, h/2 });
	ren->renderPresent();
	
	
	//Copy tex2 to tex and then copy
	//tex2 partially transparent,
	//horizontally and vertically
	//flipped, to the center
	//of tex
	ren->target(tex);
	ren->blendMode(BlendMode::None);
	ren->setDrawColor(255, 0, 0, 0);
	ren->clear();
	tex->alphaMod(255);
	tex2->alphaMod(255);
	tex->colorMod(255, 255, 255);
	tex2->colorMod(255, 255, 255);
	tex->blendMode(BlendMode::None);
	tex2->blendMode(BlendMode::None);
	ren->copy(tex2);
	tex2->alphaMod(100);
	tex2->blendMode(BlendMode::Blend);
	ren->copy(tex2, NULL, {w/4, h/4, w/2, h/2}, 0, NULL, RendererFlip::Horizontal | RendererFlip::Vertical);
	ren->renderPresent();
	
	//#define FORMAT SDL_PIXELFORMAT_RGB888
	#define FORMAT PixelFormat::RGB888
	
	unsigned char* pixels = (unsigned char*)malloc(SDL_BYTESPERPIXEL(SDL_RawPixelFormat(FORMAT))*w*h*sizeof(char));
	
	
	
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
	
	
	const int size = SDL_BYTESPERPIXEL(SDL_RawPixelFormat(FORMAT));
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
	
	sren->blendMode(BlendMode::Blend);
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
	
	
	{
		SDL_Event ev;
		ev.type = SDL_WINDOWEVENT;
		ev.window.event = SDL_WINDOWEVENT_RESIZED;
		
		auto wev = new typename QUtils::Drawing::SDL::WindowEvent(&ev.window);
		
		
		delete wev;
	}
	
	Event::SetEventFilter(EventCB<1, void*, SDL_Event*>, NULL);
	
	std::function<int(SDL_Event*)> ef;
	assert_ex(Event::GetEventFilter(&ef));
	
	Event* ev = NULL;
	while ((ev = Event::PollEvent()) != NULL)
	{
		dout << ev->eventName() << ", ";
		delete ev;
	}
	dout << "\n";
	
	dout << "Testing EF...";
	ef(NULL);
	dout << "...\n";
	
	Event::SetEventFilter([=](SDL_Event* ev) -> int {
		dout << "Lambda Filter - ";
		return ef(ev) & 1;
	});
	
	std::function<int(SDL_Event*)> ef2;
	Event::GetEventFilter(&ef2);
	dout << "Testing...";
	ef2(NULL);
	dout << "...\n";
	
	Event::SetEventFilter(NULL, NULL);
	
	
	dout << "Adding Event Watch...\n";
	auto watchIndex = Event::AddEventWatch([&win](Event* x) -> int
	{
		dout << "Event Watcher: [" << (x != NULL ? (std::to_string((int)x->type) + ": " + x->eventName()) : "") << "]\n";
		if (x != NULL)
		{
			if (x->type == EventType::WindowEvent)
			{
				auto ev = (WindowEvent*)x;
				dout << (int)ev->event << "\n";
				dout << ev->windowID << "\n";
				auto evWin = Window::GetFromID(ev->windowID);
				assert_ex(win->ID() == evWin->ID());
				assert_ex(evWin == win);
				//return 0;
			}
		}
		return 1;
	});
	
	win->setSize(w/2, h);
	
	while ((ev = Event::PollEvent()) != NULL)
	{
		dout << ev->eventName() << ", ";
		delete ev;
	}
	dout << "\n";
	
	
	win->setSize(w, h);
	
	{
		SDL_Delay(1000);
		/*SDL_Event ev;
		while (SDL_PollEvent(&ev) != 0)
		{
			dout << "Event: " << ev.type << "\n";
		}*/
		while ((ev = Event::PollEvent()) != NULL)
		{
			dout << ev->eventName() << ", ";
			delete ev;
		}
		dout << "\n";
		
	}
	
	dout << "Removing Event Watch...\n";
	Event::DelEventWatch(watchIndex);
	
	
	
	
	
	
	{
		const int ptSize = 1000;
		Font* font1 = Font::Open("font1.ttf", ptSize);
		assert_ex(font1 != NULL);
		dout << "FontData: \n\n";
		dout << "Height: " << font1->height() << "\n";
		assert_ex(font1->height() == 921);
		font1->hinting(FontHinting::Mono);
		assert_ex(font1->hinting() == FontHinting::Mono);
		assert_ex(!font1->isFixedWidth());
		
		const std::string testStr = "Hello, world!";
		int adv, minx, maxx;
		for (char c : testStr)
		{
			assert_ex(c != '\0');
			font1->glyphMetrics(c, &minx, &maxx, NULL, NULL, &adv);
			dout << c << ": (" << minx << ", " << maxx << ", " << adv << ")\n";
		}
		
		std::string testStr2 = "";
		int _w;
		for (auto c : testStr)
		{
			testStr2 += c;
			font1->textSize(testStr2, &_w, NULL);
			dout << "Width: [" << _w << "] \t(" << testStr2 << ")\n";
		}
		
		testStr2 = "";
		font1->textSize(testStr2.c_str(), &_w, NULL);
		dout << "Zero Length String Width: " << _w << "\n";
		
		
		std::string testStr3;
		testStr2 = testStr;
		testStr3 = "";
		int w2;
		int w3;
		
		while (testStr2.length() > 0)
		{
			font1->textSize(testStr2.c_str(), &_w, NULL);
			font1->textSize(testStr3.c_str(), &w2, NULL);
			font1->textSize((testStr2 + testStr3).c_str(), &w3, NULL);
			dout << "(" << _w << ", " << w2 << ") [" << w3 << "]\n";
			
			testStr3 = testStr2[testStr2.length()-1] + testStr3;
			testStr2 = testStr2.substr(0, testStr2.length()-1);
			
		}
		font1->textSize(testStr2.c_str(), &_w, NULL);
		font1->textSize(testStr3.c_str(), &w2, NULL);
		font1->textSize((testStr2 + testStr3).c_str(), &w3, NULL);
		dout << "(" << _w << ", " << w2 << ") [" << w3 << "]\n";
		
		int _h;
		font1->textSize(testStr, &_w, &_h);
		dout << "\n\n\n\nSurface Size: (" << _w << ", " << _h << ")\n";
		
		auto stringSurf = font1->surfaceBlended(testStr, {255, 255, 255, 255});
		auto stringTex = stringSurf->createTexture(ren);
		delete stringSurf;
		
		int renderWidth = w;
		int renderHeight = static_cast<double>(w)/_w * _h;
		
		ren->target(NULL);
		ren->setDrawColor(0, 0, 0, 255);
		ren->clear();
		ren->copy(tex3);
		ren->copy(stringTex, NULL, {0, h/2, renderWidth, renderHeight});
		ren->renderPresent();
		
		SDL_Delay(2000);
		
		delete font1;
		delete stringTex;
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	/*if (winsurf != NULL)
	{
		delete winsurf;
	}*/
	
	Event::SetEventFilter(NULL, NULL);
	
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
		win = NULL;
	}
	}
	catch (...)
	{
		if (win != NULL)
		{
			delete win;
		}
		throw;
	}
	
	return true;
}