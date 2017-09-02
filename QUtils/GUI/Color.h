#pragma once

namespace QUtils::Drawing::SDL
{
	struct Color;
}


namespace QUtils::GUI
{
	struct Color
	{
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char alpha;
		
		operator Drawing::SDL::Color() const;
	};
}