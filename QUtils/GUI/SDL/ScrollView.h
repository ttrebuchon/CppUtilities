#pragma once

#include "../View.h"

namespace QUtils::GUI::SDL
{
	class SDLScrollView : public View
	{
		private:
		void registerEvents();
		
		protected:
		std::recursive_mutex pos_m;
		ViewComponent* child;
		ViewComponent* background;
		long double posx, posy;
		
		double childW, childH;
		
		public:
		SDLScrollView(const std::string id, bool touch);
		SDLScrollView(bool touch);
		SDLScrollView(const std::string id);
		SDLScrollView();
		
		virtual ~SDLScrollView();
		
		
		virtual ViewComponent* setChild(ViewComponent*);
		virtual ViewComponent* setBackground(ViewComponent*);
		
		
		virtual void update() override;
		virtual void removeChildren() override;
		
		virtual void render(RenderTarget*, int x, int y, int w, int h) override;
		
		virtual int nativeWidth() const override;
		virtual int nativeHeight() const override;
		
		virtual bool changed() const override;
		
		virtual double childWidth() const;
		virtual void childWidth(const double);
		virtual double childHeight() const;
		virtual void childHeight(const double);
	};
}