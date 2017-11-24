#include <QUtils/DBC/Header.h>
#include <cstdio>

namespace QUtils { namespace Dbc {
	
	DbcHeader* DbcHeader::Read(std::istream& in)
	{
		DbcHeader* head = new DbcHeader();
		
		//auto file = ::fopen(filename, "r");
		
		try
		{
			Read(in, *head);
		}
		catch (...)
		{
			delete head;
			throw;
		}
		return head;
	}
	
	void DbcHeader::Read(std::istream& in, DbcHeader& head)
	{
		in.read((char*)&head, sizeof(DbcHeader));
		
	}
}
}