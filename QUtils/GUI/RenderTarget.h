#pragma once

namespace QUtils::GUI
{
	class Texture;
	
	class RenderTarget
	{
		protected:
		
		public:
		
		virtual void placeTexture(Texture*, int x, int y, int w, int h) = 0;
		virtual void update() = 0;
		virtual void clear(int r = 0, int g = 0, int b = 0) = 0;
	};
}