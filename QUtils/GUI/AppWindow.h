#pragma once

#include <list>
#include <thread>
#include <future>

#include "Event.h"
#include "RenderTarget.h"

#include "Clickable.h"

namespace QUtils::GUI
{
	class ViewComponent;
	
	class AppWindow : public virtual RenderTarget, public Clickable
	{
		private:
		std::list<std::function<void()>> UIcalls;
		std::timed_mutex UIcalls_m;
		protected:
		ViewComponent* mainView;
		std::list<std::exception_ptr> eventExceptions;
		std::mutex eventExceptions_m;
		
		void addEventException(std::exception_ptr ptr);
		
		unsigned int updateHolds;
		mutable std::mutex update_m;
		std::condition_variable update_c;
		
		std::thread UIThread;
		bool exiting;
		std::mutex exiting_m;
		
		virtual void initializeUIThread() = 0;
		
		virtual void update() = 0;
		
		public:
		AppWindow(bool touch);
		virtual ~AppWindow();
		
		void init();
		
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
		
		
		
		void blockUpdate();
		void unblockUpdate();
		
		virtual void handleEvents() = 0;
		virtual ViewComponent* replaceView(ViewComponent*);
		
		template <class F>
		auto invokeUI(F func)
		{
			typedef decltype(func()) Ret;
			auto prom = new std::promise<Ret>();
			std::lock_guard<std::timed_mutex> lock(UIcalls_m);
			UIcalls.push_back([&, prom]()
			{
				try
				{
				prom->set_value(func());
				}
				catch (...)
				{
					prom->set_exception(std::current_exception());
				}
				delete prom;
			});
			return prom->get_future();
		}
		
		bool updateBlocked() const;
		
		std::future<void> invokeUpdate();
	};
}