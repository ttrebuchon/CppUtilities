#pragma once

#include "ViewComponent.h"

namespace QUtils::Drawing::SDL
{
	class Texture;
}

namespace QUtils::GUI::SDL
{
	class SDLTextureViewComponent : public virtual SDLViewComponent
	{
		protected:
		Drawing::SDL::Texture* texture;
		public:
		
		SDLTextureViewComponent(Drawing::SDL::Texture*);
		virtual ~SDLTextureViewComponent();
		virtual void update()
		{}
		
		virtual void render(RenderTarget*, int x, int y, int w, int h) override;
		virtual void render(RenderTarget*, int x, int y) override;
		virtual void render(RenderTarget*) override;
		
		virtual double width() const override;
		virtual double height() const override;
		
	};
}