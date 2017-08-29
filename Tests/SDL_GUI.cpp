#include "../Tests_Helpers.h"
#include <QUtils/GUI/SDL/SDL.h>
#include <QUtils/GUI/SDL/AbsoluteTextureView.h>
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
	ren->fillRect({0, 0, w, h});
	ren->renderPresent();
	ren->target(NULL);
	
	auto texComp = new SDLTextureViewComponent(tex);
	assert_ex(texComp->parent == NULL);
	assert_ex(texComp->window == NULL);
	
	assert_ex(window->replaceView(texComp) == NULL);
	assert_ex(texComp->parent == NULL);
	assert_ex(texComp->window == window);
	
	window->update();
	
	assert_ex(window->replaceView(NULL) == texComp);
	assert_ex(texComp->parent == NULL);
	assert_ex(texComp->window == NULL);
	
	
	dout << "First Render Success\n";
	sleep(1000);
	
	
	auto texView = new SDLAbsoluteTextureView(w, h);
	dout << "TexView Created\n";
	
	texView->addChild(texComp, 0, 0, 1, 0.5);
	dout << "First child added\n";
	
	auto tex2 = new Drawing::SDL::Texture(ren, Drawing::SDL::PixelFormat::RGBA8888, Drawing::SDL::TextureAccess::Target, w, h);
	ren->target(tex2);
	ren->setDrawColor(0, 100, 255, 255);
	ren->clear();
	ren->fillRect(0, 0, w, h);
	ren->renderPresent();
	
	auto texComp2 = new SDLTextureViewComponent(tex2);
	dout << "Second child created\n";
	texView->addChild(texComp2, 0.5, 0.5, 0.5, 0.5);
	dout << "Second child added\n";
	
	
	
	window->replaceView(texView);
	dout << "Window view set\n";
	window->update();
	dout << "Window updated\n";
	
	sleep(1000);
	
	
	
	
	
	dout << "Handling Events...\n";
	window->handleEvents();
	delete window;
	
	if (texComp != NULL)
	{
		delete texComp;
		texComp = NULL;
	}
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