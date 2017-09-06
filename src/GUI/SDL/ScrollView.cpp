#include <QUtils/GUI/SDL/ScrollView.h>
#include <QUtils/GUI/SDL/AppWindow.h>
#include <QUtils/Drawing/SDL/SDL.h>
#include <QUtils/GUI/SDL/RenderTarget.h>
#include <QUtils/GUI/Errors.h>

#include <QUtils/Exception/NotImplemented.h>

#include <iostream>

#include <QUtils/Output/Utility.h>

namespace QUtils::GUI::SDL
{
	SDLScrollView::SDLScrollView(const std::string id, bool touch) : View(id, touch), child(NULL), background(NULL), posx(0), posy(0), childW(-1), childH(-1)
	{
		registerEvents();
	}
	
	SDLScrollView::SDLScrollView(bool touch) : View(touch), child(NULL), background(NULL), posx(0), posy(0), childW(-1), childH(-1)
	{
		registerEvents();
	}
	
	SDLScrollView::SDLScrollView(const std::string id) : View(id), child(NULL), background(NULL), posx(0), posy(0), childW(-1), childH(-1)
	{
		registerEvents();
	}
	
	SDLScrollView::SDLScrollView() : View(), child(NULL), background(NULL), posx(0), posy(0), childW(-1), childH(-1)
	{
		registerEvents();
	}
	
	SDLScrollView::~SDLScrollView()
	{
		removeChildren();
	}
	
	void SDLScrollView::registerEvents()
	{
		onFingerMotion += [&](auto win, auto time, auto touch, auto finger, auto x, auto y, auto dx, auto dy, auto pressure)
		{
			if (dx != 0 || dy != 0)
			{
				_changed = true;
				posx += dx;
				posy += dy;
				
				if (posy > 0)
				{
					posy = 0;
				}
				
				if (posx > 0)
				{
					posx = 0;
				}
			}
		};
	}
	
	ViewComponent* SDLScrollView::setChild(ViewComponent* newComp)
	{
		_changed = true;
		auto old = child;
		removeChild(old);
		addChild(newComp);
		child = newComp;
		return old;
	}
	
	ViewComponent* SDLScrollView::setBackground(ViewComponent* newBG)
	{
		_changed = true;
		auto old = background;
		removeChild(old);
		addChild(newBG);
		background = newBG;
		return old;
	}
	
	void SDLScrollView::update()
	{
		if (child != NULL)
		{
			if (child->width() != childW || child->height() != childH)
			{
				child->width(childW);
				child->height(childH);
			}
			child->update();
		}
		
		if (background != NULL)
		{
			background->update();
		}
		_changed = false;
	}
	
	void SDLScrollView::removeChildren()
	{
		if (child != NULL)
		{
			removeChild(child);
			child = NULL;
		}
		
		if (background != NULL)
		{
			removeChild(background);
			background = NULL;
		}
	}
	
	void SDLScrollView::render(RenderTarget* genericTarget, int x, int y, int w, int h)
	{
		if (child == NULL)
		{
			return;
		}
		auto sdlTarget = dynamic_cast<SDLRenderTarget*>(genericTarget);
		if (sdlTarget == NULL)
		{
			throw IncompatibleGUI_TypeException().Msg("RenderTarget isn't an SDLRenderTarget").File(__FILE__).Function(__func__);
		}
		
		auto ren = sdlTarget->getRenderer();
		
		calcRenderDimensions(w, h);
		
		auto clip = ren->getClipRect();
		
		ren->setClipRect({x, y, w, h});
		if (background == NULL)
		{
			ren->setDrawColor(0, 0, 0, 255);
			ren->fillRect(NULL);
		}
		else
		{
			background->render(sdlTarget, x, y, w, h);
		}
		
		double cw = w, ch = h;
		child->calcRelativeDimensions(cw, ch);
		cw *= w;
		ch *= h;
		
		double childRenX, childRenY;
		
		childRenX = x+(posx*w);
		
		if (childRenX < w + x - cw)
		{
			childRenX = w + x - cw;
		}
		
		if (childRenX > x)
		{
			childRenX = x;
		}
		
		childRenY = y+(posy*h);
		
		
		if (childRenY < y + h - ch)
		{
			childRenY = y + h - ch;
		}
		
		if (childRenY > y)
		{
			childRenY = y;
		}
			
		
		child->render(sdlTarget, childRenX, childRenY, w, h);
		
		ren->setClipRect(clip);
		
		
	}
	
	int SDLScrollView::nativeWidth() const
	{
		throw NotImp();
	}
	
	int SDLScrollView::nativeHeight() const
	{
		throw NotImp();
	}
	
	bool SDLScrollView::changed() const
	{
		return ((child != NULL ? child->changed() : false) || _changed || (background != NULL ? background->changed() : false));
	}
	
	double SDLScrollView::childWidth() const
	{
		return childW;
	}
	
	void SDLScrollView::childWidth(const double value)
	{
		_changed = true;
		childW = value;
	}
	
	double SDLScrollView::childHeight() const
	{
		return childH;
	}
	
	void SDLScrollView::childHeight(const double value)
	{
		_changed = true;
		childH = value;
	}
	
	
}