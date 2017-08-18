#include "../Tests_Helpers.h"
#include <QUtils/GUI/SDL/SDL.h>
#include <QUtils/Sleep/Sleep.h>

using namespace QUtils;
using namespace GUI::SDL;

void printArgs(auto x)
{
	dout << x << "\n";
}

void printArgs(auto x, auto... args)
{
	dout << x << ", ";
	printArgs(args...);
}

bool Test_SDL_GUI()
{
	
	const int w = 1080;
	const int h = 1920;
	dout << "Creating app...\n";
	//SDLApp app("", 0, 0, w, h);
	
	
	SDLWindow* window = new SDLWindow("Window1", 0, 0, w, h);
	//window->update();
	
	auto tex = window->createTexture(w, h);
	//auto winSurf = window->windowSurface();
	dout << "Surface retrieved\n";
	
	window->onQuit += []() {
		*((int*)NULL) = 4;
	};
	
	window->onFingerDown += [](auto... x) {
		dout << "Key pressed!\n";
		printArgs(x...);
	};
	
	
	
	
	window->handleEvents();
	window->clear(255, 255, 255);
	window->update();
	window->handleEvents();
	sleep(1000);
	
	tex->clear();
	tex->fillRect(0, 0, w, h, 0, 255, 0, 255);
	tex->update();
	window->clear(255, 255, 255);
	window->placeTexture(tex, w/4, h/4, w/2, h/2);
	dout << "Texture Placed\n";
	sleep(1000);
	window->handleEvents();
	window->update();
	dout << "Window Updated\n";
	
	sleep(1000);
	window->handleEvents();
	tex->clear();
	tex->fillRect(0, 0, w, h, 255, 0, 0, 255);
	tex->update();
	
	window->clear(255, 255, 255);
	window->update();
	window->placeTexture(tex, 0, 0, w/2, h/2);
	window->update();
	window->handleEvents();
	dout << "Window Updated\n";
	
	sleep(1000);
	window->clear(255, 255, 255);
	auto tex2 = window->createTexture(w, h);
	tex2->clear(255, 255, 0);
	tex2->fillRect(0, 0, w, h, 0, 0, 255, 255);
	tex2->update();
	window->clear(255, 255, 255);
	window->placeTexture(tex2, 0, 0, w, h);
	window->placeTexture(tex, 0, 0, w/2, h/2);
	window->update();
	sleep(1000);
	window->handleEvents();
	
	dout << "Creating surface...\n";
	//auto surf = window->createSurface(w/2, h/2, 32);
	dout << "Created.\n";
	sleep(1000);
	window->handleEvents();
	
	window->handleEvents();
	//delete tex;
	//delete tex2;
	//delete surf;
	//delete winSurf;
	//delete window;
	return true;
}