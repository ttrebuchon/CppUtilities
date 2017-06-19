#include "../Tests_Helpers.h"

#include <QUtils/SQL/SQL.h>

using namespace Utils;

bool Test_SQL()
{
	SQL::SQLiteConnection con("TestDB.sqlite");
	
	assert_ex(!con.isOpen());
	con.open();
	assert_ex(con.isOpen());
	con.close();
	assert_ex(!con.isOpen());
	con.open();
	assert_ex(con.isOpen());
	
	auto dropQuery = con.tablesQuery();
	while (dropQuery->next())
	{
	try
	{
		
		auto name = dropQuery->column<std::string>(0);
		dropQuery->reset();
		//dout << "DROP TABLE [" << dropQuery->column<std::string>(0) << "];" << std::endl;
		con.vQuery("DROP TABLE IF EXISTS [" + name + "];");
		
		//dropQuery->reset();
	}
	catch (std::exception& e)
	{
		dout << "Caught " << e.what() << std::endl;
	}
	}
	delete dropQuery;
	
	
	assert_ex(con.vQuery("CREATE TABLE TTable (x integer);"));
	assert_ex(con.vQuery("INSERT INTO TTable (x) VALUES (0);"));
	assert_ex(con.vQuery("BEGIN;"));
	for (auto i = 1; i < 1000; i++)
	{
		assert_ex(con.vQuery("INSERT INTO TTable (x) VALUES (" + std::to_string(i) + ");"));
		
	}
	assert_ex(con.vQuery("COMMIT;"));
	dout << "Inserted." << std::endl;
	SQL::SQLiteQuery* q = con.query("SELECT * FROM TTable;");
	while ((*q)())
	{
	//dout << q->column<int>(0) << "\n";
	//dout << q->columnType(0) << std::endl;
	q->next();
	}
	q->reset();
	q->next();
	con.vQuery("ALTER TABLE TTable ADD y integer;");
	
	con.vQuery("UPDATE TTable SET y=x*x;");
	q->reset();
	q->next();
	q->reset();
	//(*q)();
	dout << q->columnName(0) << ", " << q->columnName(1) << "\n";
	bool first = true;
	while ((*q)())
	{
		//dout << q->column<int>(0) << ", " << q->column<int>(1) << "\n";
		
		if (first)
		{
			first = false;
			con.vQuery("INSERT INTO TTable (x, y) VALUES (100, 10000);");
		}
		
		
		q->next();
	}
	dout << q->statement() << std::endl;
	
	delete q;
	q = NULL;
	
	q = con.query("PRAGMA table_info(TTable)");
	while ((*q)())
	{
		for (int i = 0; i < q->width(); i++)
		{
			dout << " | " << q->column<std::string>(i);
		}
		dout << std::endl;
		q->next();
		
		
	}
	
	
	
	
	SQL::Database DB(&con);
	
	SQL::Table TTable = DB["TTable"];
	
	for (auto col : TTable.columns())
	{
		dout << col->name << " | " << col->type << std::endl;
	}
	
	
	assert_ex(con.vQuery("CREATE TABLE [TTable 2] (x INTEGER UNIQUE);"));
	
	SQL::Table TTable_2 = DB["TTable 2"];
	
	
	
	
	
	return true;
}