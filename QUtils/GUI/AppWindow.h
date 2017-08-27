#pragma once

#include "Event.h"

namespace QUtils::GUI
{
	class View;
	
	class AppWindow
	{
		protected:
		View* mainView;
		
		public:
		
		virtual ~AppWindow();
		Event<> onQuit;
		Event<> onKeyDown;
		Event<unsigned int, long, long, float, float, float, float, float> onFingerDown;
		
		virtual int width() const = 0;
		virtual int height() const = 0;
		virtual int x() const = 0;
		virtual int y() const = 0;
		
		
		virtual void update() = 0;
		
		virtual void handleEvents() = 0;
		virtual View* replaceView(View*);
	};
}