#include <QUtils/GUI/SDL/AppWindow.h>
#include <QUtils/GUI/ViewComponent.h>
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
	SDLAppWindow::SDLAppWindow(const std::string title, const int x, const int y, const int w, const int h, bool touch) : AppWindow(touch), win(new Drawing::SDL::Window(title, x, y, w, h, Drawing::SDL::WindowFlags::Shown)), ren(NULL)
	{
		ren = new Drawing::SDL::Renderer(win, -1, Drawing::SDL::RendererFlags::TargetTexture | Drawing::SDL::RendererFlags::PresentVsync | Drawing::SDL::RendererFlags::Accelerated);
		ren->target(NULL);
		ren->setDrawColor(0, 0, 0, 0);
		ren->clear();
		ren->renderPresent();
		
		
		Drawing::SDL::Event::AppendEventFilter([&](Drawing::SDL::Event* ev) ->int
		{
			return this->handleEvent(ev);
		});
		
		Drawing::SDL::Event::FlushEvents(0, 0xFFFFFFFF);
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
			Drawing::SDL::Event::SetEventFilter(NULL, NULL);
		}
	}
	
	
	#define ECASE(x) case Drawing::SDL::EventType::x
	
	int SDLAppWindow::handleEvent(Drawing::SDL::Event* ev)
	{
		using namespace Drawing::SDL;
		switch (ev->type)
		{
			ECASE(Quit):
			this->onQuit();
			return 0;
			
			ECASE(FingerDown):
			{
				auto fEv = (TouchFingerEvent*)ev;
				onFingerDown(this, fEv->timestamp, fEv->touchId, fEv->fingerId, fEv->x, fEv->y, fEv->dx, fEv->dy, fEv->pressure);
				}
				return 0;
				
				ECASE(FingerUp):
				{
				auto fEv = (TouchFingerEvent*)ev;
				onFingerUp(this, fEv->timestamp, fEv->touchId, fEv->fingerId, fEv->x, fEv->y, fEv->dx, fEv->dy, fEv->pressure);
				}
				return 0;
				
				ECASE(FingerMotion):
				{
				auto fEv = (TouchFingerEvent*)ev;
				onFingerMotion(this, fEv->timestamp, fEv->touchId, fEv->fingerId, fEv->x, fEv->y, fEv->dx, fEv->dy, fEv->pressure);
				}
				return 0;
				
				ECASE(MouseButtonDown):
				{
				auto mbEv = (MouseButtonEvent*)ev;
				if (mbEv->windowID != win->ID())
				{
					return 1;
				}
				onMouseButtonDown(this, mbEv->timestamp, mbEv->which, mbEv->button, mbEv->state, mbEv->clicks, mbEv->x, mbEv->y);
				}
				return 0;
				
				ECASE(MouseButtonUp):
				{
				auto mbEv = (MouseButtonEvent*)ev;
				if (mbEv->windowID != win->ID())
				{
					return 1;
				}
				onMouseButtonUp(this, mbEv->timestamp, mbEv->which, mbEv->button, mbEv->state, mbEv->clicks, mbEv->x, mbEv->y);
				}
				return 0;
				
				ECASE(MouseMotion):
				{
				auto mbEv = (MouseMotionEvent*)ev;
				if (mbEv->windowID != win->ID())
				{
					return 1;
				}
				onMouseMotion(this, mbEv->timestamp, mbEv->which, mbEv->state, mbEv->x, mbEv->y, mbEv->xrel, mbEv->yrel);
				}
				return 0;
				
				ECASE(WindowEvent):
				{
					auto winEv = (WindowEvent*)ev;
				if (winEv->windowID != win->ID())
				{
					return 1;
				}
				
				switch (winEv->event)
				{
					case WindowEventType::Shown:
					onShow(this);
					return 0;
					
					case WindowEventType::Hidden:
					onHide(this);
					return 0;
					
					case WindowEventType::Exposed:
					onExpose(this);
					return 0;
					
					case WindowEventType::Moved:
					onMove(this, winEv->data1, winEv->data2);
					return 0;
					
					case WindowEventType::Resized:
					onResize(this, winEv->data1, winEv->data2);
					return 0;
					
					case WindowEventType::SizeChanged:
					onSizeChange(this, winEv->data1, winEv->data2);
					return 0;
					
					case WindowEventType::Minimized:
					onMinimize(this);
					return 0;
					
					case WindowEventType::Maximized:
					onMaximize(this);
					return 0;
					
					case WindowEventType::Restored:
					onRestore(this);
					return 0;
					
					case WindowEventType::Enter:
					onEnter(this);
					return 0;
					
					case WindowEventType::Leave:
					onLeave(this);
					return 0;
					
					case WindowEventType::FocusGained:
					onFocus(this);
					return 0;
					
					case WindowEventType::FocusLost:
					onUnfocus(this);
					return 0;
					
					case WindowEventType::Close:
					onClose(this);
					return 0;
					
					#if SDL_VERSION_MIN(2, 0, 5)
					case WindowEventType::TakeFocus:
					onFocusTaken(this);
					return 0;
					#endif
					
					
					default:
					return 1;
				}
				}
				
				
				default:
				break;
			}
			std::cout << "No Handler for " << ev->eventName() << " (" << (int)ev->type << ")\n";
			return 1;
		}
		#undef ECASE
	
	
	
	
	
	
	
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
		if (mainView != NULL)
		{
			mainView->update();
		}
		ren->target(NULL);
		ren->setDrawColor(0, 0, 0, 0);
		ren->clear();
		if (mainView != NULL)
		{
			int w, h;
			win->size(&w, &h);
			mainView->render(this, 0, 0, w, h);
		}
		ren->renderPresent();
	}
	
	void SDLAppWindow::handleEvents()
	{
		using namespace Drawing::SDL;
		Drawing::SDL::Event* ev;
		while ((ev = Drawing::SDL::Event::PollEvent()) != NULL)
		{
			std::cout << ev->eventName() << " (" << (int)ev->type << ")\n";
			if (handleEvent(ev) != 0)
			{
			switch (ev->type)
			{
				
				default:
				std::cout << "Throwing because of " << ev->eventName() << " (" << (int)ev->type << ") [" << ev->timestamp << "]\n";
				throw NotImp();
			}
			}
		}
	}
	
}