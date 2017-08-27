#pragma once

#include "ViewComponent.h"



namespace QUtils::GUI
{
	class View : public virtual ViewComponent
	{
		private:
		
		protected:
		
		public:
		
		virtual ~View() {}
		
		virtual void update() override
		{}
		
	};
}