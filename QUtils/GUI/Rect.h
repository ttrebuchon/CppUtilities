#pragma once

#include <QUtils/Drawing/SDL/Rect.h>

namespace QUtils::GUI
{
	struct Rect
	{
		double x;
		double y;
		double w;
		double h;
		
		bool overlaps(const Rect&) const;
	};
}