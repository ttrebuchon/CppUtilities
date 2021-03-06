#pragma once

#include "../AppWindow.h"
#include "RenderTarget.h"

#include <string>

namespace QUtils::Drawing::SDL
{
	class Window;
	class Renderer;
	class Event;
}


namespace QUtils::GUI::SDL
{
	
	class SDLAppWindow : public AppWindow, public SDLRenderTarget
	{
		private:
		
		std::function<Drawing::SDL::Window*()> windowInitializer;
		
		protected:
		Drawing::SDL::Window* win;
		Drawing::SDL::Renderer* ren;
		
		virtual void initializeUIThread() override;
		
		virtual int handleEvent(Drawing::SDL::Event*);
		
		virtual void update() override;
		
		
		public:
		SDLAppWindow(const std::string name, const int x, const int y, const int w, const int h, bool touch = false);
		virtual ~SDLAppWindow();
		virtual RenderType renderType() const override
		{ return RenderType::Window; }
		
		virtual int width() const override;
		virtual int height() const override;
		virtual int x() const override;
		virtual int y() const override;
		
		
		virtual void handleEvents() override;
		
		virtual Drawing::SDL::Renderer* getRenderer()
		{
			return ren;
		}
		
		virtual const Drawing::SDL::Renderer* getRenderer() const
		{
			return ren;
		}
		
		
	};
}