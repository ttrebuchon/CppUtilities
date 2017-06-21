#include "../Tests_Helpers.h"

#include <QUtils/SQL/SQL.h>

using namespace QUtils;

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
	
	const int rCount = 1000;
	assert_ex(con.vQuery("CREATE TABLE TTable (x INTEGER PRIMARY KEY);"));
	assert_ex(con.vQuery("INSERT INTO TTable (x) VALUES (0);"));
	assert_ex(con.vQuery("BEGIN;"));
	for (auto i = 1; i < rCount; i++)
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
			con.vQuery("INSERT INTO TTable (x, y) VALUES (" + std::to_string(rCount+1) + ", " + std::to_string((rCount+1)*(rCount+1)) + ");");
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
	
	for (auto col : TTable.columns)
	{
		dout << col->name << " | " << col->type << std::endl;
	}
	
	
	assert_ex(con.vQuery("CREATE TABLE [TTable 2] (x INTEGER PRIMARY KEY, z INTEGER, [x z] INTEGER);"));
	
	SQL::Table TTable_2 = DB["TTable 2"];
	
	assert_ex(con.vQuery("BEGIN;"));
	for (auto i = 0; i < rCount; i++)
	{
		assert_ex(con.vQuery("INSERT INTO [TTable 2] (x) VALUES (" + std::to_string(i) + ");"));
		
	}
	
	assert_ex(con.vQuery("UPDATE [TTable 2] SET z=x*x*x;"));
	assert_ex(con.vQuery("UPDATE [TTable 2] SET [x z]=x+z;"));
	assert_ex(con.vQuery("COMMIT;"));
	
	SQL::Table joined = TTable.join(TTable_2, "x", "x");
	
	q = con.query("SELECT * FROM [TTable_TTable 2];");
	int pIndex = 0;
	while ((*q)())
	{
		for (int i = 0; i < q->width(); i++)
		{
			dout << " | " << q->column<std::string>(i);
		}
		dout << std::endl;
		q->next();
		pIndex++;
		if (pIndex > 5)
		{
			break;
		}
	}
	
	delete q;
	
	for (auto col : joined.columns)
	{
		dout << col->name << " | " << col->type << " | PK: " << col->PK << std::endl;
	}
	
	
	
	dout << "Dropping join table..." << std::endl;
	joined.drop();
	dout << "Dropped." << std::endl;
	
	auto cl = ((TTable["x"] == TTable["y"]) || (TTable["x"] > 1000));
	dout << cl.toString() << std::endl;
	
	q = con.query("SELECT * FROM TTable WHERE " + cl.toString() + ";");
	while (q->next())
	{
		dout << q->column<int>(0) << "\n";
	}
	delete q;
	
	dout << "Joining on y->z...\n";
	joined = TTable.join(TTable_2, "y", "z");
	dout << "Joined.\n";
	
	for (auto col : joined.columns)
	{
		dout << col->name << " | " << col->type << " | PK: " << col->PK << std::endl;
	}
	
	
	q = con.query("SELECT * FROM [TTable_TTable 2];");
	pIndex = 0;
	dout << "Iterating...\n";
	while ((*q)())
	{
		for (int i = 0; i < q->width(); i++)
		{
			dout << " | " << q->column<std::string>(i);
		}
		dout << std::endl;
		q->next();
		pIndex++;
		if (pIndex > 5)
		{
			break;
		}
	}
	dout << "Done.\n";
	delete q;
	
	SQL::Query* q2 = joined.select("x", "y AS yz", "z AS zy", "[x:1]", "x z");
	pIndex = 0;
	dout << "Iterating...\n";
	while ((*q2)())
	{
		for (int i = 0; i < q2->width(); i++)
		{
			dout << " | " << q2->column<std::string>(i);
		}
		dout << std::endl;
		q2->next();
		pIndex++;
		if (pIndex > 5)
		{
			break;
		}
	}
	dout << "Done.\n";
	
	delete q2;
	
	
	for (auto table : DB)
	{
		dout << "Table: [" << table.name << "]\n";
	}
	
	return true;
}