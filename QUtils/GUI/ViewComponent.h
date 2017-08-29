#pragma once

namespace QUtils::GUI
{
	class RenderTarget;
	class View;
	class AppWindow;
	
	class ViewComponent
	{
		typedef View* ViewPtr_t;
		typedef AppWindow* AppWinPtr_t;
		friend class View;
		friend class AppWindow;
		private:
		
		protected:
		View* _parent;
		AppWindow* _window;
		double _w, _h;
		bool _changed;
		
		virtual void addToView(View*);
		virtual void removeFromView();
		virtual void setWindow(AppWindow* win)
		{
			_window = win;
		}
		
		
		
		public:
		const ViewPtr_t& parent;
		const AppWinPtr_t& window;
		
		ViewComponent();
		virtual ~ViewComponent();
		
		
		virtual void update() = 0;
		
		virtual void render(RenderTarget*, int x, int y, int w, int h) = 0;
		virtual void render(RenderTarget*, int x, int y) = 0;
		virtual void render(RenderTarget*) = 0;
		
		
		
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
	};
}