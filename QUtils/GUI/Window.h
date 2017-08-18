#pragma once

#include "Event.h"
#include "RenderTarget.h"

namespace QUtils::GUI
{
	class Texture;
	class Surface;
	
	class Window : public RenderTarget
	{
		protected:
		
		public:
		
		Event<> onQuit;
		Event<> onKeyDown;
		Event<unsigned int, int, int, float, float, float, float, float> onFingerDown;
		
		virtual int width() const = 0;
		virtual int height() const = 0;
		virtual int x() const = 0;
		virtual int y() const = 0;
		
		virtual Texture* createTexture(const int w, const int h) = 0;
		virtual Surface* createSurface(int w, int h, int depth, int rmask = 0, int gmask = 0, int bmask = 0, int alphamask = 0) = 0;
		virtual void placeTexture(Texture*, int x, int y, int w, int h) = 0;
		
		virtual void update() = 0;
		
		virtual void handleEvents() = 0;
		virtual void clear(int r = 0, int g = 0, int b = 0) = 0;
	};
}