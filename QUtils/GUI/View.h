#pragma once

#include "ViewComponent.h"
#include "RenderTarget.h"



namespace QUtils::GUI
{
	class View : public ViewComponent
	{
		private:
		
		protected:
		
		virtual void addChild(ViewComponent*);
		
		public:
		View(const std::string id, bool touch);
		View(bool touch);
		View(const std::string id);
		View();
		virtual ~View();
		
		virtual void update() = 0;
		virtual void removeChildren() = 0;
		virtual void removeChild(ViewComponent*);
		
	};
}