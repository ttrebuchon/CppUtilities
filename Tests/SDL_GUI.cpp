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
	
	
	SDLAppWindow* window = new SDLAppWindow("Window1", 0, 0, w, h);
	//window->update();
	
	window->onQuit += []() {
		*((int*)NULL) = 4;
	};
	
	window->onFingerDown += [](auto... x) {
		dout << "Key pressed!\n";
		printArgs(x...);
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
	
	
	
	
	window->handleEvents();
	delete window;
	return true;
}