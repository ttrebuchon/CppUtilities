#pragma once

class QApplication;
namespace QUtils
{
namespace QT
{
	
	class QTApp
	{
		private:
		QApplication* qapp;
		public:
		QTApp();
		
		virtual int execute();
	};
}
}