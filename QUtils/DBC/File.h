#pragma once

#include "Header.h"
#include "Row.h"

namespace QUtils { namespace Dbc {
	
	class DbcFile
	{
		private:
		unsigned char* data;
		DbcHeader* head;
		unsigned char* rows;
		unsigned char* string_tab;
		
		void read(std::istream&);
		
		bool startOfString(const size_t) const;
		
		public:
		DbcFile(const char* filename);
		DbcFile(std::istream&);
		~DbcFile();
		
		
		DbcRow operator[](size_t index);
		DbcRow at(size_t index);
		
		size_t size() const
		{ return head->record_n; }
		
		size_t columns() const
		{ return head->field_n; }
		
		template <class T>
		DbcRow findRowWithValue(const size_t col, const T value)
		{
			for (auto i = 0; i < size(); ++i)
			{
				DbcRow r = at(i);
				if (r.at<T>(col) == value)
				{
					return r;
				}
			}
			
			//TODO
			throw std::exception();
		}
		
		size_t maxStringIndex() const;
		
		size_t dataSize() const
		{
			return head->record_n*head->record_size + head->string_block_size + sizeof(DbcHeader);
		}
		
		DbcRow getById(const uint id, const size_t start = 0) const;
		inline bool uniqueID() const
		{ return uniqueKey(0); }
		bool uniqueKey(const size_t) const;
		bool uniqueKey(const std::initializer_list<size_t>) const;
		
		bool couldBeString(const size_t col, bool includeAllZero = false) const;
		
		class iterator
		{
			private:
			DbcFile& f;
			unsigned char* row;
			
			iterator(DbcFile& f, unsigned char* row) : f(f), row(row) {}
			
			public:
			
			
			iterator& operator++();
			iterator operator++(int);
			DbcRow operator*() const;
			
			
			bool operator==(const iterator) const;
			bool operator!=(const iterator) const;
			bool operator>=(const iterator) const;
			bool operator<=(const iterator) const;
			bool operator>(const iterator) const;
			bool operator<(const iterator) const;
			
			iterator operator+(const size_t) const;
			iterator& operator+=(const size_t);
			iterator operator-(const size_t) const;
			iterator& operator-=(const size_t);
			
			
			friend class DbcFile;
			
		};
		
		iterator begin();
		iterator end();
		
		const iterator begin() const;
		const iterator end() const;
		
		
		
		friend class DbcRow;
	};
}
}
#include "File.hpp"