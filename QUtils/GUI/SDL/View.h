#pragma once

#include "ViewComponent.h"
#include "../View.h"


namespace QUtils::GUI::SDL
{
	class SDLView : public virtual View, public virtual SDLViewComponent
	{
		private:
		
		protected:
		
		public:
		
		virtual ~SDLView();
		
	};
}