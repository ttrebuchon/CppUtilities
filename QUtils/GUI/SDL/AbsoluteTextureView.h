#pragma once

#include "TextureView.h"
#include <vector>
#include <tuple>

namespace QUtils::GUI::SDL
{
	class SDLAbsoluteTextureView : public SDLTextureView
	{
		private:
		void registerEvents();
		
		protected:
		std::vector<std::tuple<ViewComponent*, double, double>> children;
		
		virtual void updateTexture() override;
		
		public:
		SDLAbsoluteTextureView(const std::string id, bool touch, int w, int h);
		SDLAbsoluteTextureView(bool touch, int w, int h);
		SDLAbsoluteTextureView(const std::string id, int w, int h);
		SDLAbsoluteTextureView(int w, int h);
		
		virtual ~SDLAbsoluteTextureView();
		
		virtual void removeChildren() override;
		bool changed() const override;
		
		virtual void addChild(ViewComponent*, double x, double y, double w, double h);
		virtual void removeChild(ViewComponent*) override;
	};
}