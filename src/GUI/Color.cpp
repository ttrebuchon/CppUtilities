#include <QUtils/GUI/Color.h>
#include <QUtils/Drawing/SDL/Color.h>


namespace QUtils::GUI
{
	Color::operator Drawing::SDL::Color() const
	{
		return { r, g, b, alpha };
	}
}