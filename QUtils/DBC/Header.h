#pragma once
#include <cstdint>
#include <iostream>

namespace QUtils { namespace Dbc {
	
	struct DbcHeader
	{
		uint32_t magic;
		uint32_t record_n;
		uint32_t field_n;
		uint32_t record_size;
		uint32_t string_block_size;
		
		static DbcHeader* Read(std::istream&);
		static void Read(std::istream&, DbcHeader&);
		
		inline bool verify() const
		{
			const char* m = (const char*)&this->magic;
			return
			(
				m[0] == 'W'
				&&
				m[1] == 'D'
				&&
				m[2] == 'B'
				&&
				m[3] == 'C'
			) && field_n*4 == record_size;
		}
	};
}
}