#include <QUtils/GUI/QT/QTApp.h>
#include <QApplication>

namespace QUtils
{
namespace QT
{
	QTApp::QTApp() : qapp(new QApplication(0, NULL))
	{
		
	}
	
	int QTApp::execute()
	{
		return qapp->exec();
	}
}
}