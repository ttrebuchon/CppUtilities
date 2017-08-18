#pragma once

#include "RenderTarget.h"

namespace QUtils::GUI
{
	class Texture : public RenderTarget
	{
		protected:
		
		public:
		
		virtual void fillRect(int x, int y, int w, int h, int r, int g, int b, int alpha) = 0;
		
		
		virtual void placeTexture(Texture*, int x, int y, int w, int h) = 0;
		virtual void update() = 0;
		virtual void clear(int r = 0, int g = 0, int b = 0) = 0;
		
	};
}