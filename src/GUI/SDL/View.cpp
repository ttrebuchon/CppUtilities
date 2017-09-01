#include <QUtils/GUI/SDL/View.h>

namespace QUtils::GUI::SDL
{
	SDLView::SDLView(const std::string id, bool touch) : View(id, touch), SDLViewComponent(id, touch)
	{
		
	}
	
	SDLView::SDLView(bool touch) : View(touch), SDLViewComponent(touch)
	{
		
	}
	
	SDLView::SDLView(const std::string id) : View(id), SDLViewComponent(id)
	{
		
	}
	
	SDLView::SDLView() : View(), SDLViewComponent()
	{
		
	}
		
		
	SDLView::~SDLView()
	{
		
	}
}