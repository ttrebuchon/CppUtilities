#include <QUtils/GUI/AppWindow.h>

namespace QUtils::GUI
{
	AppWindow::AppWindow(bool touch) : mainView(NULL), onQuit(), onKeyDown(!touch), onFingerDown(touch), onFingerUp(touch), onFingerMotion(touch), onMouseButtonDown(!touch), onMouseButtonUp(!touch), onMouseMotion(!touch)
	{
		
	}
	
	AppWindow::~AppWindow()
	{
		
	}
	
	
	View* AppWindow::replaceView(View* v)
	{
		auto vOld = mainView;
		mainView = v;
		return vOld;
	}
}