#include <QUtils/GUI/AppWindow.h>
#include <QUtils/GUI/ViewComponent.h>

namespace QUtils::GUI
{
	AppWindow::AppWindow(bool touch) : RenderTarget(), Clickable(touch), mainView(NULL), onQuit(), onKeyDown(!touch)
	{
		relayEvents([](auto _this) {
			return ((AppWindow*)_this)->mainView;
		});
	}
	
	AppWindow::~AppWindow()
	{
		
	}
	
	
	ViewComponent* AppWindow::replaceView(ViewComponent* v)
	{
		auto vOld = mainView;
		mainView = v;
		if (vOld != NULL)
		{
			vOld->setWindow(NULL);
		}
		if (v != NULL)
		{
			v->setWindow(this);
		}
		return vOld;
	}
}