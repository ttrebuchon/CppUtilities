#pragma once

namespace QUtils::GUI
{
	class View;
	
	class ViewComponent
	{
		typedef View* ViewPtr_t;
		friend class View;
		private:
		
		protected:
		View* _parent;
		double _w, _h;
		
		virtual void addToView(View*);
		virtual void removeFromView();
		
		public:
		const ViewPtr_t& parent;
		ViewComponent();
		virtual ~ViewComponent();
		
		
		virtual void update() = 0;
		
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
	};
}