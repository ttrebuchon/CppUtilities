#pragma once

namespace QUtils { namespace Dbc {
	
	class DbcFile;
	
	class DbcRow
	{
		private:
		DbcFile& file;
		unsigned char* row;
		
		DbcRow(DbcFile& file, unsigned char* row) : file(file), row(row)
		{}
		
		public:
		
		size_t width() const;
		
		
		friend class DbcFile;
		
		float floatAt(const size_t col) const;
		unsigned int uintAt(const size_t col) const;
		int intAt(const size_t col) const;
		const char* cstringAt(const size_t col) const;
		
		template <class T>
		T at(const size_t col) const
		{
			static_assert(sizeof(T) == 4);
			
			return *reinterpret_cast<T*>(row + 4*col);
		}
		
		bool couldBeString(const size_t col, bool includeZero = false) const;
	};
	
	template <>
	const char* DbcRow::at<const char*>(const size_t col) const;
	
	template <>
	std::string DbcRow::at<std::string>(const size_t col) const;
}
}