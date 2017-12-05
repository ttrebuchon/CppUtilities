#pragma once

#define CLASS_PROPERTY(CLASS, TYPE, NAME) \
TYPE CLASS::NAME() const \
{ \
	return json->at(#NAME); \
}
