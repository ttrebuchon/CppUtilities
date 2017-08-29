#include "../Tests_Helpers.h"
#include <QUtils/GUI/SDL/SDL.h>
#include <QUtils/GUI/ComponentView.h>
#include <QUtils/Sleep/Sleep.h>
#include <QUtils/Drawing/SDL/SDL.h>

#include <vector>

using namespace QUtils;
using namespace GUI::SDL;

void printArgs(unsigned char x)
{
	dout << ((int)x) << "\n";
}

void printArgs(unsigned char x, auto... args)
{
	dout << ((int)x) << ", ";
	printArgs(args...);
}

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
	
	SDLAppWindow* window = NULL;
	try
	{
	
	
	window = new SDLAppWindow("Window1", 0, 0, w, h, true);
	//window->update();
	
	window->onQuit += []() {
		dout << "Quitting!\n";
	};
	
	window->onFingerDown += [](auto... x) {
		dout << "Finger Down!\n";
		printArgs(x...);
	};
	
	window->onFingerMotion += [](auto... x) {
		dout << "Finger Motion!\n";
		printArgs(x...);
	};
	
	window->onMouseButtonDown += [](auto... x) {
		dout << "Mouse Down!\n";
		printArgs(x...);
	};
	
	window->onMouseButtonUp += [](auto... x) {
		dout << "Mouse Up!\n";
		printArgs(x...);
	};
	
	window->onMouseMotion += [](auto... x) {
		dout << "Mouse Motion!\n";
		printArgs(x...);
	};
	
	window->onClose += [](auto...)
	{
		dout << "Window Closed!\n";
	};
	
	window->onFocus += [](auto...)
	{
		dout << "Window Focused\n";
	};
	
	
	
	
	
	dout << "Handling Events...\n";
	window->handleEvents();
	dout << "Updating...\n";
	//window->update();
	dout << "Handling Events...\n";
	window->handleEvents();
	dout << "Sleeping for 1000...\n";
	sleep(1000);
	
	
	
	
	
	auto tex = new Drawing::SDL::Texture(window->getRenderer(), Drawing::SDL::PixelFormat::RGBA8888, Drawing::SDL::TextureAccess::Target, w, h);
	auto ren = window->getRenderer();
	ren->target(tex);
	ren->setDrawColor(0, 0, 0, 255);
	ren->clear();
	ren->setDrawColor(255, 255, 255, 255);
	ren->fillRect({0, 0, w/2, h/2});
	ren->renderPresent();
	ren->target(NULL);
	
	auto texComp = new SDLTextureViewComponent(tex);
	assert_ex(texComp->parent == NULL);
	
	auto testView = new GUI::ComponentView(texComp);
	assert_ex(texComp->parent == testView);
	
	assert_ex(window->replaceView(testView) == NULL);
	
	window->update();
	
	assert_ex(window->replaceView(NULL) == testView);
	delete testView;
	
	
	
	
	dout << "Handling Events...\n";
	window->handleEvents();
	delete window;
	}
	catch (...)
	{
		if (window != NULL)
		{
			delete window;
			window = NULL;
		}
		throw;
	}
	
	return true;
}