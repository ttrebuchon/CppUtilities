#include "../Tests_Helpers.h"

#include <QUtils/SQL/SQL.h>

using namespace Utils;

bool Test_SQL()
{
	SQL::SQLiteConnection con("TestDB.sqlite");
	
	assert_ex(!con.isOpen());
	con.openOrCreate();
	assert_ex(con.isOpen());
	con.close();
	assert_ex(!con.isOpen());
	con.open();
	assert_ex(con.isOpen());
	
	try
	{
		con.vQuery("DROP TABLE TTable;");
	}
	catch (...)
	{
		
	}
	assert_ex(con.vQuery("CREATE TABLE TTable (x integer);"));
	assert_ex(con.vQuery("INSERT INTO TTable (x) VALUES (0);"));
	assert_ex(con.vQuery("BEGIN;"));
	for (auto i = 1; i < 10000; i++)
	{
		assert_ex(con.vQuery("INSERT INTO TTable (x) VALUES (" + std::to_string(i) + ");"));
	}
	assert_ex(con.vQuery("ROLLBACK;"));
	
	
	SQL::SQLiteQuery* q = con.query("SELECT * FROM TTable;");
	while (q->next())
	{
	dout << q->column<int>(0) << "\n";
	//dout << q->columnType(0) << std::endl;
	}
	q->reset();
	/*while ((*q)())
	{
		
	dout << q->column<int>(0) << std::endl;
	q->next();
	}*/
	delete q;
	q = NULL;
	
	return true;
}