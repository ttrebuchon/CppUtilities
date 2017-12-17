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
	SDLScrollView::SDLScrollView(const std::string id, bool touch) : View(id, touch), pos_m(), child(NULL), background(NULL), posx(0), posy(0), childW(-1), childH(-1), stickBottom(false)
	{
		registerEvents();
	}
	
	SDLScrollView::SDLScrollView(bool touch) : View(touch), pos_m(), child(NULL), background(NULL), posx(0), posy(0), childW(-1), childH(-1), stickBottom(false)
	{
		registerEvents();
	}
	
	SDLScrollView::SDLScrollView(const std::string id) : View(id), pos_m(), child(NULL), background(NULL), posx(0), posy(0), childW(-1), childH(-1), stickBottom(false)
	{
		registerEvents();
	}
	
	SDLScrollView::SDLScrollView() : View(), pos_m(), child(NULL), background(NULL), posx(0), posy(0), childW(-1), childH(-1), stickBottom(false)
	{
		registerEvents();
	}
	
	SDLScrollView::~SDLScrollView()
	{
		std::lock_guard<std::recursive_mutex> lock(this_m);
		removeChildren();
	}
	
	void SDLScrollView::registerEvents()
	{
		onFingerMotion += [&](auto win, auto time, auto touch, auto finger, auto x, auto y, auto dx, auto dy, auto rdx, auto rdy, auto pressure)
		{
			std::async(std::launch::async, 
			[&]()
			{
			std::lock_guard<std::recursive_mutex> pos_lock(pos_m);
			if (dx != 0 || dy != 0)
			{
				_changed = true;
				posx += rdx;
				posy += rdy;
				
				if (posy > 0)
				{
					posy = 0;
				}
				
				if (posx > 0)
				{
					posx = 0;
				}
			}
			
			});
		};
	}
	
	ViewComponent* SDLScrollView::setChild(ViewComponent* newComp)
	{
		std::lock_guard<std::recursive_mutex> lock(this_m);
		_changed = true;
		auto old = child;
		removeChild(old);
		addChild(newComp);
		child = newComp;
		return old;
	}
	
	ViewComponent* SDLScrollView::setBackground(ViewComponent* newBG)
	{
		std::lock_guard<std::recursive_mutex> lock(this_m);
		_changed = true;
		auto old = background;
		removeChild(old);
		addChild(newBG);
		background = newBG;
		return old;
	}
	
	void SDLScrollView::update()
	{
		std::lock_guard<std::recursive_mutex> lock(this_m);
		if (child != NULL)
		{
			if (child->changed())
			{
				childChanged = true;
			}
			if ((child->width() != childW) || (child->height() != childH))
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
		std::lock_guard<std::recursive_mutex> lock(this_m);
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
		std::lock_guard<std::recursive_mutex> lock(this_m);
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
		
		double posx, posy;
		
		
		
		if (stickBottom && childChanged)
		{
			this->posy = -(INT_MAX-1);
			childChanged = false;
		}
		
		
		double childRenX, childRenY;
		
		{
			std::lock_guard<std::recursive_mutex> pos_lock(pos_m);
			posx = this->posx;
			posy = this->posy;
		
		
		
		
		childRenX = x+(posx*w);
		
		if (childRenX < w + x - cw)
		{
			childRenX = w + x - cw;
			this->posx = posx = 1 - static_cast<double>(cw/w);
		}
		
		if (childRenX > x)
		{
			childRenX = x;
		}
		
		childRenY = y+(posy*h);
		
		
		if (childRenY < y + h - ch)
		{
			childRenY = y + h - ch;
			this->posy = posy = 1 - static_cast<double>(ch/h);
		}
		
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
	
	bool SDLScrollView::stickToBottom() const
	{
		return stickBottom;
	}
	
	void SDLScrollView::stickToBottom(bool value)
	{
		stickBottom = value;
	}
	
	
}