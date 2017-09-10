#pragma once
#include <QUtils/Exception/Exception.h>

namespace QUtils
{
namespace GUI
{
	QUTILS_CUSTOM_EXCEPTION(ParentChildException,);
	
	QUTILS_CUSTOM_EXCEPTION(IncompatibleGUI_TypeException,);
	
	QUTILS_CUSTOM_EXCEPTION(RenderException, );
}
}