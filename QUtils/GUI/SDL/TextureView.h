#pragma once

#include "../View.h"
#include "RenderTarget.h"

namespace QUtils::Drawing::SDL
{
	class Texture;
	class Renderer;
}

namespace QUtils::GUI::SDL
{
	class SDLTextureView : public View, public SDLRenderTarget
	{
		private:
		
		
		protected:
		Drawing::SDL::Texture* texture;
		Drawing::SDL::Renderer* tmpRen;
		
		virtual void setWindow(AppWindow*) override;
		int texW, texH;
		
		virtual void updateTexture() = 0;
		
		public:
		SDLTextureView(const std::string id, bool touch, int w, int h);
		SDLTextureView(bool touch, int w, int h);
		SDLTextureView(const std::string id, int w, int h);
		SDLTextureView(int w, int h);
		virtual ~SDLTextureView();
		
		
		virtual void update() override;
		
		virtual void render(RenderTarget*, int x, int y, int w, int h) override;
		
		virtual RenderType renderType() const
		{ return RenderType::Texture; }
		
		virtual Drawing::SDL::Renderer* getRenderer() override;
		
		virtual int nativeWidth() const override;
		virtual int nativeHeight() const override;
	};
}