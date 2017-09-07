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
	
	window->onMinimize += [](auto...)
	{
		dout << "\n\nMinimizing!!\n\n\n" << std::flush;
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
	
	/*texView->onFingerDown += [](auto...x)
	{
		dout << "\nTex View Clicked!\n\n";
	};*/
	
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
	dout << "Handling Events...\n";
	window->handleEvents();
	dout << "Handled" << std::endl;
	
	
	
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
	dout << "Font1 resource assigned\n" << std::flush;
	
	
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
	
	
	auto texComp3 = new SDLTextureViewComponent("TexComp3", TOUCH, tex3);
	//window->unblockUpdate();
	
	texView->addChild(texComp3, 0, 0, 1, 0);
	dout << "TexComp3 Added\n" << std::flush;
	
	//window->update();
	
	
	
	auto tex3HandlerID = texView->onFingerMotion += [&](auto win, auto time, auto, auto, auto x, auto y, auto dx, auto dy, auto rdx, auto rdy, auto pressure)
	{
		//texComp3->height(y+dy);
		texComp3->height(pressure);
	};
	
	sleep(1000);
	
	texView->onFingerMotion -= tex3HandlerID;
	texComp3->height(0);
	
	
	
	
	
	
	
	
	
	auto tex4 = window->invokeUI([window, ren]{
		auto tex4 = new Drawing::SDL::Texture(ren, Drawing::SDL::PixelFormat::RGBA8888, Drawing::SDL::TextureAccess::Target, w, 4*h);
		ren->target(tex4);
		ren->setDrawColor(255, 255, 255, 255);
		ren->clear();
		for (int i = 0; i < 4*h; ++i)
		{
			ren->setDrawColor((255 - static_cast<double>(i)/(4*h-1)*255), 255, 255, 255);
			ren->fillRect({0, i, w, 1});
		}
		ren->setDrawColor(255, 0, 0, 255);
		ren->fillRect({0, 0, w, 30});
		ren->setDrawColor(0, 0, 0, 255);
		for (int i = 2*h/3; i < 4*h; i += 4*h/6)
		{
			ren->drawLine(0, i, w, i);
		}
		ren->renderPresent();
		
		return tex4;
	}).get();
	
	dout << "Tex4 Defined\n" << std::flush;
	
	auto texComp4 = new SDLTextureViewComponent("TexComp4", TOUCH, tex4);
	
	auto scrollView = new SDLScrollView("ScrollView", TOUCH);
	
	scrollView->setChild(texComp4);
	scrollView->childWidth(-1);
	scrollView->childHeight(-1);
	
	//texView->addChild(scrollView, 0.125, 0.125, 0.75, 0.75);
	texView->addChild(scrollView, 0, 0, 0.5, 0.5);
	sleep(2000);
	window->invokeUpdate().get();
	
	
	
	dout << "Removing TexView Children...\n";
	texView->removeChildren();
	
	dout << "Adding TexComp2 as child...\n" << std::flush;
	texView->addChild(texComp2, 0, 0, 1, 1);
	dout << "Invoking Update...\n";
	window->invokeUpdate().get();
	
	
	auto fingerPaintHandler = texComp2->onFingerDown += [ren, tex2, window, texComp2](auto win, auto time, auto touchID, auto fingerID, auto x, auto y, auto pressure)
	{
		window->invokeUI([x, y, ren, tex2, texComp2]()
		{
			ren->target(tex2);
			ren->setDrawColor(255, 0, 0, 255);
			ren->setViewport(x*tex2->width()-25, y*tex2->height()-25, 50, 50);
			ren->fillRect(NULL);
			ren->renderPresent();
			ren->resetViewport();
			
			texComp2->textureChanged();
			
			return 0;
		});
	};
	
	
	sleep(1000);
	
	window->invokeUpdate().get();
	
	texComp2->onFingerDown -= fingerPaintHandler;
	
	
	auto textScroll = new SDLScrollView("TextScrollView", TOUCH);
	
	auto text = new SDLLabelViewComponent("TextScroll_TextComp", TOUCH, "Hello!!!! World, this issss AWDDTF a test", "font1", 50);
	text->color({255, 255, 255, 255});
	text->wrapWidth(1080);
	
	textScroll->setChild(text);
	
	texView->removeChildren();
	texView->addChild(textScroll, 0, 0, 1, 1);
	
	sleep(5000);
	
	
	
	
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
	cleanup(texView);
	cleanup(texComp);
	cleanup(texComp2);
	cleanup(labelComp);
	cleanup(scrollView);
	cleanup(tex);
	cleanup(tex2);
	cleanup(tex3);
	cleanup(tex4);
	
	
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