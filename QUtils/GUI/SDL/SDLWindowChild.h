#pragma once


namespace QUtils::GUI::SDL
{
	class SDLWindow;
	
	
	class SDLWindowChild
	{
		typedef SDLWindow* WinPtr;
		typedef const WinPtr ConstPtr;
		protected:
		SDLWindow* _win;
		
		public:
		ConstPtr& window;
		
		SDLWindowChild(SDLWindow* win) : _win(win), window(_win)
		{}
	};
}