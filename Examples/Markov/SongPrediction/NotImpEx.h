#pragma once

#include <QUtils/Exception/Exception.h>

QUTILS_CUSTOM_EXCEPTION(NotImplementedException, This has not been implemented);

#define NotImp() NotImplementedException("", __func__)