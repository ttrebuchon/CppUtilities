#pragma once

#include "Exception.h"

UTIL_CUSTOM_EXCEPTION(FeatureNotAvailableException, This feature is not available);

#define NotAvail() FeatureNotAvailableException("", __func__)

using NotAvailableException = FeatureNotAvailableException;