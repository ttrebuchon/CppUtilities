#pragma once

#include "../ViewComponent.h"

namespace QUtils::Drawing::SDL
{
	class Texture;
}

namespace QUtils::GUI::SDL
{
	class SDLTextureViewComponent : public ViewComponent
	{
		protected:
		Drawing::SDL::Texture* texture;
		public:
		SDLTextureViewComponent(const std::string id, bool touch, Drawing::SDL::Texture*);
		SDLTextureViewComponent(bool touch, Drawing::SDL::Texture*);
		SDLTextureViewComponent(const std::string id, Drawing::SDL::Texture*);
		SDLTextureViewComponent(Drawing::SDL::Texture*);
		virtual ~SDLTextureViewComponent();
		virtual void update()
		{
			onUpdate(this);
			_changed = false;
		}
		
		virtual void render(RenderTarget*, int x, int y, int w, int h) override;
		
		virtual void textureChanged()
		{ _changed = true; }
		
		virtual int nativeWidth() const override;
		virtual int nativeHeight() const override;
		
	};
}