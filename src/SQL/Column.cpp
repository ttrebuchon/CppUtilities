#include <QUtils/SQL/Column.h>


namespace Util
{
namespace SQL
{
	Column::Column(const int index, const std::string name, const std::string type, const bool notNull, const std::string defaultValue, const bool PK) : _index(index), _name(name), _type(type), _notNull(notNull), _defaultValue(defaultValue), _PK(PK), index(_index), name(_name), type(_type), notNull(_notNull), defaultValue(_defaultValue), PK(_PK)
	{
		
	}
}
}