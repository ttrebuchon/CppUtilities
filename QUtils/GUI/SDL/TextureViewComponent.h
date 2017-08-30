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
		
		virtual void textureChanged()
		{ _changed = true; }
		
		virtual int nativeWidth() const override;
		virtual int nativeHeight() const override;
		
		virtual double opacity() const override;
		virtual void opacity(double) override;
		
	};
}