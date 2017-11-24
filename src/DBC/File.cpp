#include <QUtils/DBC/File.h>

#include <fstream>
#include <cassert>
#include <set>
#include <vector>


#include <iostream>

namespace QUtils { namespace Dbc {
	
	DbcFile::DbcFile(const char* filename) : data(NULL), head(NULL), rows(NULL), string_tab(NULL)
	{
		std::ifstream in(filename);
		this->read(in);
		in.close();
	}
	
	DbcFile::DbcFile(std::istream& in) : data(NULL), head(NULL), rows(NULL), string_tab(NULL)
	{
		this->read(in);
	}
	
	DbcFile::~DbcFile()
	{
		if (data)
		{
			delete[] data;
		}
	}
	
	void DbcFile::read(std::istream& in)
	{
		DbcHeader tmpHead;
		DbcHeader::Read(in, tmpHead);
		if (!tmpHead.verify())
		{
			//TODO
			throw std::exception();
		}
		
		size_t body_size = tmpHead.record_n*tmpHead.record_size + tmpHead.string_block_size;
		
		data = new unsigned char[body_size + sizeof(DbcHeader)];
		::memcpy(data, &tmpHead, sizeof(DbcHeader));
		head = (DbcHeader*)data;
		assert(head->verify());
		rows = data + sizeof(DbcHeader);
		string_tab = rows + tmpHead.record_n*tmpHead.record_size;
		
		in.read((char*)rows, body_size);
	}
	
	bool DbcFile::startOfString(const size_t offset) const
	{
		if (offset == 0)
		{
			return true;
		}
		if (offset >= head->string_block_size)
		{
			return false;
		}
		
		auto ptr = string_tab + offset - 1;
		return ptr[0] == 0;
	}
	
	
	
	DbcRow DbcFile::operator[](const size_t index)
	{
		return DbcRow(*this, rows + index*head->record_size);
	}
	
	DbcRow DbcFile::at(const size_t index)
	{
		if (index >= head->record_n)
		{
			//TODO
			throw std::exception();
		}
		return DbcRow(*this, rows + index*head->record_size);
	}
	
	size_t DbcFile::maxStringIndex() const
	{
		return head->string_block_size;
	}
	
	DbcRow DbcFile::getById(const uint id, const size_t start) const
	{
		const uint rSize = head->record_size;
		unsigned char* offset = rows + start*rSize;
		uint v;
		while (offset < string_tab)
		{
			v = *reinterpret_cast<uint*>(offset);
			if (v == id)
			{
				auto nonConst = const_cast<DbcFile*>(this);
				return DbcRow(*nonConst, offset);
			}
			offset += rSize;
		}
		
		//TODO
		throw std::exception();
	}
	
	bool DbcFile::uniqueKey(const size_t index) const
	{
		std::set<uint> values;
		const size_t offset = this->head->record_size;
		const unsigned char* end = this->string_tab;
		auto ptr = rows + index*4;
		uint value;
		while (ptr < end)
		{
			value = *reinterpret_cast<uint*>(ptr);
			if (values.count(value) > 0)
			{
				return false;
			}
			values.insert(value);
			ptr += offset;
		}
		return true;
	}
	
	bool DbcFile::uniqueKey(const std::initializer_list<size_t> indexes) const
	{
		typedef std::vector<uint> Keys;
		std::set<Keys> values;
		const size_t size = indexes.size();
		const size_t offset = this->head->record_size;
		const unsigned char* end = this->string_tab;
		auto ptr = rows;
		uint value;
		size_t i;
		Keys k;
		k.reserve(size);
		while (ptr < end)
		{
			k.clear();
			k.resize(size);
			i = 0;
			for (auto& index : indexes)
			{
				value = *reinterpret_cast<uint*>(ptr+index*4);
				k[i] = value;
			}
			if (values.count(k) > 0)
			{
				return false;
			}
			values.insert(k);
			ptr += offset;
		}
		return true;
	}
	
	bool DbcFile::couldBeString(const size_t col, bool includeAllZero) const
	{
		const unsigned char* const end = this->string_tab;
		
		if (col >= this->head->field_n)
		{
			//TODO
			throw std::exception();
		}
		
		unsigned char* ptr = this->rows + col*4;
		const size_t rec_size = this->head->record_size;
		bool allZero = true;
		unsigned int value;
		while (ptr < end)
		{
			value = *reinterpret_cast<unsigned int*>(ptr);
			
			if (!this->startOfString(value))
			{
				return false;
			}
			ptr += rec_size;
			if (allZero && value != 0)
			{
				allZero = false;
			}
		}
		return (includeAllZero || !allZero);
		
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	DbcFile::iterator DbcFile::iterator::operator++(int)
	{
		auto it = *this;
		this->operator++();
		return it;
	}
	
	DbcFile::iterator& DbcFile::iterator::operator++()
	{
		row += f.head->record_size;
		return *this;
	}
	
	DbcRow DbcFile::iterator::operator*() const
	{
		return DbcRow(f, row);
	}
	
	bool DbcFile::iterator::operator==(const iterator it) const
	{
		return (&f == &it.f) && (row == it.row);
	}
	
	bool DbcFile::iterator::operator!=(const iterator it) const
	{
		return (&f != &it.f) || (row != it.row);
	}
	
	bool DbcFile::iterator::operator>=(const iterator it) const
	{
		return (row >= it.row);
	}
	
	bool DbcFile::iterator::operator<=(const iterator it) const
	{
		return row <= it.row;
	}
	
	bool DbcFile::iterator::operator>(const iterator it) const
	{
		return row > it.row;
	}
	
	bool DbcFile::iterator::operator<(const iterator it) const
	{
		return row < it.row;
	}
	
	
	DbcFile::iterator DbcFile::iterator::operator+(const size_t offset) const
	{
		return iterator(f, row + offset*f.head->record_size);
	}
	
	DbcFile::iterator& DbcFile::iterator::operator+=(const size_t offset)
	{
		row += offset*f.head->record_size;
		return *this;
	}
	
	DbcFile::iterator DbcFile::iterator::operator-(const size_t offset) const
	{
		return iterator(f, row - offset*f.head->record_size);
	}
	
	DbcFile::iterator& DbcFile::iterator::operator-=(const size_t offset)
	{
		row -= offset*f.head->record_size;
		return *this;
	}
	
	
	
	
	DbcFile::iterator DbcFile::begin()
	{
		return iterator(*this, rows);
	}
	
	DbcFile::iterator DbcFile::end()
	{
		return iterator(*this, rows + head->record_size*head->record_n);
	}
	
	const DbcFile::iterator DbcFile::begin() const
	{
		auto nonConst = const_cast<DbcFile*>(this);
		
		return iterator(*nonConst, nonConst->rows);
	}
	
	const DbcFile::iterator DbcFile::end() const
	{
		auto nonConst = const_cast<DbcFile*>(this);
		
		return iterator(*nonConst, nonConst->rows + head->record_size*head->record_n);
	}
	
	
}
}