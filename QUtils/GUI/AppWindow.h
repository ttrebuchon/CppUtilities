#pragma once

#include "Event.h"
#include "RenderTarget.h"

namespace QUtils::GUI
{
	class ViewComponent;
	
	class AppWindow : public virtual RenderTarget
	{
		protected:
		ViewComponent* mainView;
		
		public:
		AppWindow(bool touch);
		virtual ~AppWindow();
		Event<> onQuit;
		Event<> onKeyDown;
		
		Event<AppWindow*, unsigned int, long, long, float, float, float, float, float> onFingerDown;
		Event<AppWindow*, unsigned int, long, long, float, float, float, float, float> onFingerUp;
		Event<AppWindow*, unsigned int, long, long, float, float, float, float, float> onFingerMotion;
		
		Event<AppWindow*, unsigned int, unsigned int, unsigned char, unsigned char, unsigned char, int, int> onMouseButtonDown;
		Event<AppWindow*, unsigned int, unsigned int, unsigned char, unsigned char, unsigned char, int, int> onMouseButtonUp;
		Event<AppWindow*, unsigned int, unsigned int, unsigned int, int, int, int, int> onMouseMotion;
		
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