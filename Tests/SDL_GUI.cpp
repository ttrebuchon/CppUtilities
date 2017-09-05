#include "../Tests_Helpers.h"
#include <QUtils/GUI/SDL/SDL.h>
#include <QUtils/GUI/SDL/AbsoluteTextureView.h>
#include <QUtils/Sleep/Sleep.h>
#include <QUtils/Drawing/SDL/SDL.h>

#include <vector>

#include <thread>

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
	
	#define TOUCH true
	window = new SDLAppWindow("Window1", 0, 0, w, h, TOUCH);
	window->blockUpdate();
	window->init();
	sleep(1000);
	window->handleEvents();
	
	window->invokeUI([]() -> int
	{
		dout << "ThreadID: " << std::this_thread::get_id() << "\n";
		return 0;
	}).wait();
	
	
	window->onQuit += []() {
		dout << "Quitting!\n";
	};
	
	//#define PRINT_PRESSES
	
	#ifdef PRINT_PRESSES
	
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
	
	window->onMouseWheel += [](auto... x) {
		dout << "Mouse Wheel!\n";
		printArgs(x...);
	};
	
	#endif
	
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
	////window->update();
	dout << "Handling Events...\n";
	window->handleEvents();
	dout << "Sleeping for 1000...\n";
	sleep(1000);
	
	//Drawing::SDL::Texture* tex;
	Drawing::SDL::Renderer* ren;
	
	auto tex = window->invokeUI([=, &ren]() -> Drawing::SDL::Texture*
	{
	auto tmp = new Drawing::SDL::Texture(window->getRenderer(), Drawing::SDL::PixelFormat::RGBA8888, Drawing::SDL::TextureAccess::Target, w, h);
	ren = window->getRenderer();
	ren->target(tmp);
	ren->setDrawColor(0, 0, 0, 255);
	ren->clear();
	ren->setDrawColor(255, 255, 255, 255);
	ren->fillRect({0, 0, w, h});
	ren->renderPresent();
	ren->target(NULL);
	return tmp;
	}).get();
	
	
	#define TEXCOMP "TexComp"
	auto texComp = new SDLTextureViewComponent(TEXCOMP, TOUCH, tex);
	dout << "TexComp id: '" << texComp->id << "'\n";
	assert_ex(texComp->parent == NULL);
	assert_ex(texComp->window == NULL);
	assert_ex(texComp->id == TEXCOMP);
	
	assert_ex(window->replaceView(texComp) == NULL);
	assert_ex(texComp->parent == NULL);
	assert_ex(texComp->window == window);
	
	window->unblockUpdate();
	//window->update();
	assert_ex(window->replaceView(NULL) == texComp);
	assert_ex(texComp->parent == NULL);
	assert_ex(texComp->window == NULL);
	
	
	dout << "First Render Success\n";
	sleep(1000);
	
	
	auto texView = new SDLAbsoluteTextureView("AbsTextureView", TOUCH, w, h);
	dout << "TexView Created\n";
	
	texView->addChild(texComp, 0, 0, 1, 0.5);
	dout << "First child added\n";
	
	
	auto tex2 = window->invokeUI([=]()
	{
		auto tex2 = new Drawing::SDL::Texture(ren, Drawing::SDL::PixelFormat::RGBA8888, Drawing::SDL::TextureAccess::Target, w, h);
	window->blockUpdate();
	ren->target(tex2);
	ren->setDrawColor(0, 100, 255, 255);
	ren->clear();
	ren->fillRect(0, 0, w, h);
	ren->renderPresent();
	return tex2;
	}).get();
	
	auto texComp2 = new SDLTextureViewComponent("TexComp2", TOUCH, tex2);
	dout << "Second child created\n";
	texView->addChild(texComp2, 0.5, 0, 0.5, 1);
	dout << "Second child added\n";
	
	texComp2->onFingerDown += [](auto...x)
	{
		dout << "\nTex Comp 2 Clicked!\n\n";
	};
	
	texComp->onFingerDown += [](auto...x)
	{
		dout << "\nTex Comp Clicked!\n\n";
	};
	
	texView->onFingerDown += [](auto...x)
	{
		dout << "\nTex View Clicked!\n\n";
	};
	
	texComp2->opacity(0.2);
	auto partialOpacity = static_cast<unsigned char>(0.2*255);
	auto partialOpacity_d = static_cast<double>(partialOpacity)/255;
	
	
	assert_ex(texComp2->opacity() == partialOpacity_d);
	
	texComp2->opacity(1);
	assert_ex(texComp2->opacity() == 1);
	
	
	window->replaceView(texView);
	dout << "Window view set\n";
	assert_ex(window->updateBlocked());
	window->unblockUpdate();
	//window->update();
	dout << "Window updated\n";
	assert_ex(!window->updateBlocked());
	window->handleEvents();
	
	
	
	window->blockUpdate();
	window->invokeUI([&]
	{
		ren->target(tex);
		ren->setDrawColor(255, 0, 0, 255);
		ren->clear();
		ren->renderPresent();
		return 0;
	}).wait();
	
	texComp->textureChanged();
	window->unblockUpdate();
	//window->update();
	
	{
	int max = 30;
	
	for (int i = 0; i < max; i += 1)
	{
		//window->blockUpdate();
		window->invokeUI([&]
		{
		if (i % 2 == 0)
		{
			ren->target(tex);
			texComp->textureChanged();
			texComp->opacity(static_cast<double>(i)/max);
		}
		else
		{
			ren->target(tex2);
			texComp2->textureChanged();
			texComp2->opacity(static_cast<double>(i)/max);
		}
		
		switch (i % 3)
		{
			case 0:
			ren->setDrawColor(255, 0, 0, 255);
			break;
			
			case 1:
			ren->setDrawColor(0, 255, 0, 255);
			break;
			
			case 2:
			ren->setDrawColor(0, 0, 255, 255);
			break;
			default:
			break;
		}
		
		ren->clear();
		ren->renderPresent();
		return 0;
		}).get();
		//window->update();
		//window->unblockUpdate();
		//window->invokeUpdate().get();
	}
	}
	
	
	auto font1Loader = new SDLFontFileResourceLoader("font1", "font1.ttf");
	font1Loader->assign();
	font1Loader = NULL;
	
	
	auto labelComp = new SDLLabelViewComponent("LabelComp", TOUCH, "Hello", "font1", 400);
	labelComp->color({255, 255, 255, 255});
	
	
	texView->addChild(labelComp, 0, 0, -1, -1);
	
	//window->update();
	sleep(200);
	texView->removeChild(labelComp);
	
	
	texView->addChild(labelComp, 0, 0.5, 1, -2);
	labelComp->text("Hello, world!");
	//labelComp->wrapWidth(0.5);
	//window->update();
	
	//window->blockUpdate();
	auto tex3 = window->invokeUI([window, w, h, ren]
	{
		auto tex3 = new Drawing::SDL::Texture(window->getRenderer(), Drawing::SDL::PixelFormat::RGBA8888, Drawing::SDL::TextureAccess::Target, w, h);
		ren->target(tex3);
		ren->setDrawColor(255, 0, 255, 255);
		ren->clear();
		ren->renderPresent();
		return tex3;
	}).get();
	
	
	auto texComp3 = new SDLTextureViewComponent(tex3);
	//window->unblockUpdate();
	
	texView->addChild(texComp3, 0, 0, 1, 0);
	
	//window->update();
	
	
	
	texView->onFingerMotion += [&](auto win, auto time, auto, auto, auto x, auto y, auto dx, auto dy, auto pressure)
	{
		//texComp3->height(y+dy);
		texComp3->height(pressure);
	};
	
	sleep(10000);
	
	
	dout << "Handling Events...\n";
	window->handleEvents();
	
	auto cleanup = [](auto& ptr)
	{
		if (ptr != NULL)
		{
			delete ptr;
			ptr = NULL;
		}
	};
	window->blockUpdate();
	
	dout << "Cleaning up..." << std::endl << std::flush;
	cleanup(window);
	/*cleanup(texView);
	cleanup(texComp);
	cleanup(texComp2);
	cleanup(labelComp);
	cleanup(tex);
	cleanup(tex2);
	cleanup(tex3);*/
	
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