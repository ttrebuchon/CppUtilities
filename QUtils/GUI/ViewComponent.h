#pragma once

#include <string>

#include "Clickable.h"

namespace QUtils::GUI
{
	class RenderTarget;
	class View;
	class AppWindow;
	
	class ViewComponent : public Clickable
	{
		static int idCounter;
		typedef View* ViewPtr_t;
		typedef AppWindow* AppWinPtr_t;
		friend class View;
		friend class AppWindow;
		private:
		
		protected:
		std::string _id;
		View* _parent;
		AppWindow* _window;
		double _w, _h;
		double _opacity;
		bool _changed;
		
		virtual void addToView(View*);
		virtual void removeFromView();
		virtual void setWindow(AppWindow* win)
		{
			_window = win;
		}
		
		virtual void calcRenderDimensions(int& width, int& height);
		
		public:
		const std::string& id;
		const ViewPtr_t& parent;
		const AppWinPtr_t& window;
		
		ViewComponent(const std::string id, bool touch);
		ViewComponent(bool touch);
		ViewComponent(const std::string id);
		ViewComponent();
		virtual ~ViewComponent();
		
		
		virtual void update() = 0;
		
		virtual void render(RenderTarget*, int x, int y, int w, int h) = 0;
		
		
		
		inline double w() const
		{ return width(); }
		inline double h() const
		{ return height(); }
		virtual double width() const;
		virtual double height() const;
		
		inline void w(double val)
		{ width(val); }
		inline void h(double val)
		{ height(val); }
		virtual void width(double);
		virtual void height(double);
		
		virtual bool changed() const
		{ return _changed; }
		
		virtual int nativeWidth() const = 0;
		virtual int nativeHeight() const = 0;
		virtual double opacity() const;
		virtual void opacity(double v);
	};
}