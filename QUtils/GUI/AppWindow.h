#pragma once

#include <list>

#include "Event.h"
#include "RenderTarget.h"

#include "Clickable.h"

namespace QUtils::GUI
{
	class ViewComponent;
	
	class AppWindow : public virtual RenderTarget, public Clickable
	{
		protected:
		ViewComponent* mainView;
		std::list<std::exception_ptr> eventExceptions;
		
		public:
		AppWindow(bool touch);
		virtual ~AppWindow();
		Event<> onQuit;
		Event<> onKeyDown;
		
		Event<AppWindow*> onShow;
		Event<AppWindow*> onHide;
		Event<AppWindow*> onExpose;
		Event<AppWindow*, int, int> onMove;
		Event<AppWindow*, int, int> onResize;
		Event<AppWindow*, int, int> onSizeChange;
		Event<AppWindow*> onMinimize;
		Event<AppWindow*> onMaximize;
		Event<AppWindow*> onRestore;
		Event<AppWindow*> onEnter;
		Event<AppWindow*> onLeave;
		Event<AppWindow*> onFocus;
		Event<AppWindow*> onUnfocus;
		Event<AppWindow*> onClose;
		Event<AppWindow*> onFocusTaken;
		
		
		virtual int width() const = 0;
		virtual int height() const = 0;
		virtual int x() const = 0;
		virtual int y() const = 0;
		
		
		virtual void update() = 0;
		
		virtual void handleEvents() = 0;
		virtual ViewComponent* replaceView(ViewComponent*);
	};
}