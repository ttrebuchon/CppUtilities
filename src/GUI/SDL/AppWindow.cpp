#include <QUtils/GUI/SDL/AppWindow.h>
#include <QUtils/GUI/Errors.h>
#include <QUtils/GUI/SDL/Common.h>
#include <QUtils/Drawing/SDL/Renderer.h>
#include <QUtils/Drawing/SDL/Window.h>
#include <QUtils/Drawing/SDL/Events/Events.h>

#include <iostream>
#include <QUtils/Output/HexObject.h>

#include <QUtils/Exception/NotImplemented.h>

namespace QUtils::GUI::SDL
{
	SDLAppWindow::SDLAppWindow(const std::string title, const int x, const int y, const int w, const int h) : AppWindow(), win(new Drawing::SDL::Window(title, x, y, w, h, Drawing::SDL::WindowFlags::Shown)), ren(NULL)
	{
		ren = new Drawing::SDL::Renderer(win, -1, Drawing::SDL::RendererFlags::TargetTexture);
		ren->target(NULL);
		ren->setDrawColor(0, 0, 0, 0);
		ren->clear();
		ren->renderPresent();
		auto window = this->win;
		Drawing::SDL::Event::AppendEventFilter([window] (Drawing::SDL::Event* ev) -> int
		{
			int x = window->x();
			int w = window->width();
			std::cout << "(" << x << ", " << w << ") - " << ev->eventName();
			std::cout << "\n";
			return (int)(x >= w);
		});
		
		Drawing::SDL::Event::AppendEventFilter([window] (Drawing::SDL::Event* ev) -> int
		{
			std::cout << ev->eventName();
			std::cout << "\n";
			return 1;
		});
		
		
		
		Drawing::SDL::Event* ev;
		while ((ev = Drawing::SDL::Event::PollEvent()) != NULL)
		{
			delete ev;
		}
	}
	
	SDLAppWindow::~SDLAppWindow()
	{
		if (ren != NULL)
		{
			delete ren;
		}
		if (win != NULL)
		{
			delete win;
		}
	}
	
	int SDLAppWindow::width() const
	{
		int w;
		win->size(&w, NULL);
		return w;
	}
	
	int SDLAppWindow::height() const
	{
		int h;
		win->size(NULL, &h);
		return h;
	}
	
	int SDLAppWindow::x() const
	{
		int x;
		win->position(&x, NULL);
		return x;
	}
	
	int SDLAppWindow::y() const
	{
		int y;
		win->position(NULL, &y);
		return y;
	}
	
	void SDLAppWindow::update()
	{
		throw NotImp();
	}
	
	void SDLAppWindow::handleEvents()
	{
		using namespace Drawing::SDL;
		Drawing::SDL::Event* ev;
		while ((ev = Drawing::SDL::Event::PollEvent()) != NULL)
		{
			std::cout << ev->eventName() << "\n";
			switch (ev->type)
			{
				case EventType::Quit:
				onQuit();
				break;
				
				case EventType::FingerDown:
				{
				auto fEv = (TouchFingerEvent*)ev;
				onFingerDown(fEv->timestamp, fEv->touchId, fEv->fingerId, fEv->x, fEv->y, fEv->dx, fEv->dy, fEv->pressure);
				}
				break;
				
				default:
				
				throw NotImp();
			}
		}
	}
	
}