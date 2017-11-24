#include <QUtils/DBC/File.h>
#include <QUtils/DBC/Row.h>


#include <cassert>

namespace QUtils { namespace Dbc {
	
	size_t DbcRow::width() const
	{
		return file.head->field_n;
	}
	
	float DbcRow::floatAt(const size_t col) const
	{
		return *reinterpret_cast<float*>(row + col*4);
	}
	
	unsigned int DbcRow::uintAt(const size_t col) const
	{
		return *reinterpret_cast<unsigned int*>(row + col*4);
	}
	
	int DbcRow::intAt(const size_t col) const
	{
		return *reinterpret_cast<int*>(row + col*4);
	}
	
	template <>
	const char* DbcRow::at<const char*>(const size_t col) const
	{
		auto strPtr = at<unsigned int>(col) + file.string_tab;
		return reinterpret_cast<const char*>(strPtr);
	}
	
	template <>
	std::string DbcRow::at<std::string>(const size_t col) const
	{
		return std::string(this->at<const char*>(col));
	}
	
	bool DbcRow::couldBeString(const size_t col, bool includeZero) const
	{
		const auto v = this->at<unsigned int>(col);
		return (v != 0 || includeZero) && file.startOfString(v);
	}
}
}
	