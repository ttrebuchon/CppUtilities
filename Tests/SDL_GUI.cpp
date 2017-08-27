#include "../Tests_Helpers.h"
#include <QUtils/GUI/SDL/SDL.h>
#include <QUtils/Sleep/Sleep.h>

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
		*((int*)NULL) = 4;
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
	
	
	auto x = new SDLView();
	
	assert_ex(window->replaceView(x) == NULL);
	
	assert_ex(window->replaceView(NULL) == x);
	delete x;
	
	
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