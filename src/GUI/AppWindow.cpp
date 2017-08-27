#include <QUtils/GUI/AppWindow.h>

namespace QUtils::GUI
{
	
	
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