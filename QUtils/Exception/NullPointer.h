#pragma once

#include "Exception.h"

UTIL_CUSTOM_EXCEPTION(NullPointerException, Null pointer dereference found);

#define NullPtrEx() NullPointerException("", __func__)

#define NULLPTRCHECK(x) (x != NULL ? x : throw NullPointerException().Line(__LINE__).Function(__func__).File(__FILE__).Msg(std::string(#x) + " is NULL"))