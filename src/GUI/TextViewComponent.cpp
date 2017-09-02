#include <QUtils/GUI/TextViewComponent.h>


namespace QUtils::GUI
{
	
	TextViewComponent::TextViewComponent(const std::string id, bool touch) : ViewComponent(id, touch)
	{
		
	}
	
	TextViewComponent::TextViewComponent(bool touch) : ViewComponent(touch)
	{
		
	}
	
	TextViewComponent::TextViewComponent(const std::string id) : ViewComponent(id)
	{
		
	}
	
	TextViewComponent::TextViewComponent() : ViewComponent()
	{
		
	}
	
	TextViewComponent::~TextViewComponent()
	{
		
	}
	
	void TextViewComponent::calcRenderDimensions(int& w, int& h)
	{
		/*if (wrapWidth() == -1)
		{
			*/ViewComponent::calcRenderDimensions(w, h);/*
			return;
		}
		
		auto tmpW = width();
		auto tmpH = height();
		
		if (tmpW == -2 && tmpH == -2)
		{
			tmpW = tmpH = -1;
		}
		
		if (tmpW >= 0)
		{
			w = static_cast<int>(tmpW*w);
		}
		else if (tmpW == -1)
		{
			w = -1;
		}
		
		
		if (tmpH >= 0)
		{
			h = static_cast<int>(tmpH*h);
		}
		else if (tmpH == -1)
		{
			h = -1;
		}
		
		if (tmpW == -2)
		{
			if (h > 0)
			{
				w = (static_cast<double>(nativeWidth())/nativeHeight())*h;
			}
			else
			{
				w = -2;
			}
		}
		
		if (tmpH == -2)
		{
			if (w > 0)
			{
				h = (static_cast<double>(nativeHeight())/nativeWidth())*w;
			}
			else
			{
				h = -2;
			}
		}*/
	}
}