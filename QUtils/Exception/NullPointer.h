#pragma once

#include "Exception.h"

UTIL_CUSTOM_EXCEPTION(NullPointerException, Null pointer dereference found);

#define NullPtrEx() NullPointerException("", __func__)