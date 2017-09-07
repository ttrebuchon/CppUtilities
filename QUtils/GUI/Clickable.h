#pragma once

#include "Event.h"

namespace QUtils::GUI
{
	class AppWindow;
	
	
	class Clickable
	{
		protected:
		virtual void relayEvents(std::function<Clickable*(Clickable*)>);
		
		public:
		Event<AppWindow*, unsigned int, long, long, float, float, float> onFingerDown;
		Event<AppWindow*, unsigned int, long, long, float, float, float> onFingerUp;
		Event<AppWindow*, unsigned int, long, long, float, float, float, float, double, double, float> onFingerMotion;
		
		Event<AppWindow*, unsigned int, unsigned int, unsigned char, unsigned char, unsigned char, int, int> onMouseButtonDown;
		Event<AppWindow*, unsigned int, unsigned int, unsigned char, unsigned char, unsigned char, int, int> onMouseButtonUp;
		Event<AppWindow*, unsigned int, unsigned int, unsigned int, int, int, int, int> onMouseMotion;
		Event<AppWindow*, unsigned int, unsigned int, int, int, unsigned int> onMouseWheel;
		
		
		
		Clickable(bool touch);
		Clickable();
	};
}