#pragma once

#include "Exception.h"

UTIL_CUSTOM_EXCEPTION(NotImplementedException, This has not been implemented);

#define NotImp() NotImplementedException("", __func__)