#pragma once
#include <QUtils/Exception/Exception.h>

namespace QUtils
{
namespace SQL
{
	QUTILS_CUSTOM_EXCEPTION(SQLErrorException,);
	
	QUTILS_CUSTOM_EXCEPTION(SQLObjectException,);
	
	QUTILS_CUSTOM_EXCEPTION(SQLModelConfigException,);
	
}
}