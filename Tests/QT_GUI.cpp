#include "../Tests_Helpers.h"
#include <QUtils/GUI/QT/QT.h>

using namespace QUtils::QT;

bool Test_QT_GUI()
{
	QTApp app;
	
	app.execute();
	return true;
}