#pragma once

#include "ViewComponent.h"
#include "RenderTarget.h"



namespace QUtils::GUI
{
	class View : public virtual ViewComponent
	{
		private:
		
		protected:
		
		virtual void addChild(ViewComponent*);
		
		public:
		View();
		virtual ~View();
		
		virtual void update() = 0;
		virtual void removeChildren() = 0;
		
	};
}