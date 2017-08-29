#include <QUtils/GUI/AppWindow.h>
#include <QUtils/GUI/ViewComponent.h>

namespace QUtils::GUI
{
	AppWindow::AppWindow(bool touch) : mainView(NULL), onQuit(), onKeyDown(!touch), onFingerDown(touch), onFingerUp(touch), onFingerMotion(touch), onMouseButtonDown(!touch), onMouseButtonUp(!touch), onMouseMotion(!touch)
	{
		
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