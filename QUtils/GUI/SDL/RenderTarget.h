#pragma once
#include "../RenderTarget.h"
#include "RenderType.h"

namespace QUtils::Drawing::SDL
{
	class Renderer;
}

namespace QUtils::GUI::SDL
{
	class SDLRenderTarget : public virtual RenderTarget
	{
		public:
		virtual RenderType renderType() const = 0;
		
		virtual Drawing::SDL::Renderer* getRenderer() = 0;
	};
}