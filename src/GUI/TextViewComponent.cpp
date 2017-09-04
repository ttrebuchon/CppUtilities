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
			*/ViewComponent::calcRenderDimensions(w, h);
			/*return;
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
			w = nativeWidth();
		}
		
		
		if (tmpH >= 0)
		{
			h = static_cast<int>(tmpH*h);
		}
		else if (tmpH == -1)
		{
			h = nativeHeight();
		}
		
		if (tmpW == -2)
		{
			w = (static_cast<double>(nativeWidth())/nativeHeight())*h;
		}
		
		if (tmpH == -2)
		{
			h = (static_cast<double>(nativeHeight())/nativeWidth())*w;
		}*/
		
		
	}
	
	/*void ViewComponent::calcRelativeDimensions(double& outW, double& outH) const
	{
		auto tmpW = width();
		auto tmpH = height();
		
		if (tmpW == -2 && tmpH == -2)
		{
			tmpW = tmpH = -1;
		}
		
		if (tmpW >= 0)
		{
			outW = tmpW;
		}
		else if (tmpW == -1)
		{
			outW = (static_cast<double>(nativeWidth())/outW);
		}
		
		if (tmpH >= 0)
		{
			outH = tmpH;
		}
		else if (tmpH == -1)
		{
			outH = (static_cast<double>(nativeHeight())/outH);
		}
		
		
		
		if (tmpW == -2)
		{
			outW *= (static_cast<double>(nativeWidth())/nativeHeight());
		}
		
		if (tmpH == -2)
		{
			outH *= (static_cast<double>(nativeHeight())/nativeWidth());
		}
	}*/
}