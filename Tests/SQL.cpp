#include "../Tests_Helpers.h"

#include <QUtils/SQL/SQL.h>

#include <sqlite3.h>

#include <QUtils/SQL/SQL_Name.h>

#include <QUtils/SQL/ORM/ORM.h>

#include <QUtils/GUID/GUID.h>
#include <QUtils/Exception/NotImplemented.h>
#include <QUtils/Types/CompilerPrint.h>


using namespace QUtils;

bool Test_SQL()
{
	auto printQuery = [](SQL::SQLQuery* q) -> SQL::SQLQuery*
	{
		for (int i = 0; i < q->width(); ++i)
		{
			dout << "|" << q->columnName(i) << "|";
		}
		dout << "\n";
		while (q->next())
		{
			for (int i = 0; i < q->width(); ++i)
			{
				dout << "|" << q->column<std::string>(i) << "|";
			}
			dout << "\n";
		}
		
		
		return q;
	};

	{
	const std::string filename = "TestDB";
	SQL::SQLiteConnection con(filename + ".sqlite");
	{
	
	assert_ex(!con.isOpen());
	con.open();
	assert_ex(con.isOpen());
	con.close();
	assert_ex(!con.isOpen());
	con.open();
	assert_ex(con.isOpen());
	
	long long int updates = 0;
	std::map<int, long long int> updatesByCode;
	con.setUpdateCallback([&updates, &updatesByCode](int code, char const* db, char const* table, long long row) {
		bool print = false;
		if (print)
		{
		++updates;
		++updatesByCode[code];
		if (updates % 100 == 0 || updates == 1)
		{
			//dout << "[" << db << "].[" << table << "]->" << row << "\n";
			dout << updates << " Updates\n";
		}
		if (updatesByCode[code] % 100 == 0 || updatesByCode[code] == 1)
		{
			dout << updatesByCode[code] << " Updates for " << code << "\n";
		}
		}
	});
	
	con.setAuthorizerCallback([&updates, &updatesByCode](auto a, auto b, auto c, auto d, auto e) -> int
	{
		//dout << a << (b != NULL ? ", " : "") << (b != NULL ? b : "") << (c != NULL ? ", " : "") << (c != NULL ? c : "") << (d != NULL ? ", " : "") << (d != NULL ? d : "") << (e != NULL ? ", " : "") << (e != NULL ? b : "") << "\n";
		return 0;
		if (a == 21) //SELECT
		{
			return 0;
		}
		else if (a == 20) //READ
		{
			return 0;
		}
		//return 0;//SQLITE_OK;
		//return 1; //SQLITE_DENY;
		//return 2; //SQLITE_IGNORE;
	});
	
	
	auto dropQuery = con.tablesQuery();
	std::vector<std::string> dropTableNames;
	while (dropQuery->next())
	{
		if (dropQuery->column<std::string>(0) != "sqlite_sequence")
		{
			dropTableNames.push_back(dropQuery->column<std::string>(0));
		}
	}
	delete dropQuery;
	
	for (auto name : dropTableNames)
	{
		try
		{
			//dout << "DROP TABLE [" << dropQuery->column<std::string>(0) << "];" << std::endl;
			dout << "Dropping [" << name + "]\n";
			con.vQuery("DROP TABLE [" + name + "];");
		}
		catch (std::exception& e)
		{
			dout << "Caught " << e.what() << std::endl;
		}
	}
	
	
	std::string ttableCreateStmt = "CREATE TABLE TTable (x INTEGER PRIMARY KEY)";
	const int rCount = 1000;
	assert_ex(con.vQuery(ttableCreateStmt));
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
	
	
	
	
	dout << "Pending Statements:\n";
	auto werePending = con.pending();
	for (auto stmt : werePending)
	{
		dout << sqlite3_expanded_sql(stmt) << "\n";
		assert_ex(std::string(sqlite3_expanded_sql(stmt)) == "PRAGMA table_info(TTable)");
	}
	assert_ex(werePending.size() == 1);
	delete q;
	assert_ex(con.pending().size() == 0);
	
	
	
	
	SQL::SQLDatabase DB = SQL::SQLDatabase::Create(&con);
	dout << "Database object created\n";
	
	SQL::SQLTable TTable = DB["TTable"];
	
	for (auto col : TTable->columns)
	{
		dout << col->name << " | " << col->type << std::endl;
	}
	
	
	assert_ex(con.vQuery("CREATE TABLE [TTable 2] (x INTEGER PRIMARY KEY, z INT, [x z] INTEGER);"));
	
	SQL::SQLTable TTable_2 = DB["TTable 2"];
	dout << "TTable 2 table object created.\n";
	
	assert_ex(con.vQuery("BEGIN;"));
	for (auto i = 0; i < rCount; i++)
	{
		assert_ex(con.vQuery("INSERT INTO [TTable 2] (x) VALUES (" + std::to_string(i) + ");"));
		
	}
	
	assert_ex(con.vQuery("UPDATE [TTable 2] SET z=x*x*x;"));
	assert_ex(con.vQuery("UPDATE [TTable 2] SET [x z]=x+z;"));
	assert_ex(con.vQuery("COMMIT;"));
	
	dout << "Joining " << TTable->name << " and " << TTable_2->name << " on their x columns...\n";
	SQL::SQLTable joined = TTable->join(TTable_2, "x", "x");
	dout << "Joined.\n";
	assert_ex(joined->name == "[TTable_TTable 2]");
	
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
	
	dout << "Printing columns...\n";
	for (auto col : joined->columns)
	{
		dout << col->name << " | " << col->type << " | PK: " << col->PK << std::endl;
	}
	dout << "Columns printed.\n";
	/*q = con.query("PRAGMA TABLE_INFO(" + joined.name + ");");
	while (q->next())
	{
		dout << q->column<std::string>(0) << "\n";
	}
	delete q;
	dout << "\"" << joined.name + "\"\n";
	for (auto segment : SQL::SQL_Name_Parse(joined.name))
	{
		dout << segment << "\n";
	}*/
	
	{
		const std::string nameTestString = "[TTable].[x].[z].y.h.[c]";
		auto testSegments = SQL::SQL_Name_Parse(nameTestString);
		assert_ex(testSegments.size() == 6);
		assert_ex(testSegments[0] == "TTable");
		assert_ex(testSegments[1] == "x");
		assert_ex(testSegments[2] == "z");
		assert_ex(testSegments[3] == "y");
		assert_ex(testSegments[4] == "h");
		assert_ex(testSegments[5] == "c");
		
	}
	
	
	
	dout << "Dropping join table..." << std::endl;
	joined->drop();
	dout << "Dropped." << std::endl;
	
	auto cl = ((TTable->columns["x"] == TTable->columns["y"]) || (TTable->columns["x"] > 1000));
	dout << cl.toString() << std::endl;
	
	q = con.query("SELECT * FROM TTable WHERE " + cl.toString() + ";");
	while (q->next())
	{
		dout << q->column<int>(0) << "\n";
	}
	delete q;
	
	dout << "Joining on y->z...\n";
	joined = TTable->join(TTable_2, "y", "z");
	assert_ex(joined->name == "[TTable_TTable 2]");
	dout << "Joined.\n";
	
	for (auto col : joined->columns)
	{
		dout << col->name << " | " << col->type << " | PK: " << col->PK << std::endl;
	}
	dout << "Columns Printed\n";
	dout << "Querying...\n";
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
	
	SQL::SQLQuery* q2 = joined->select("x", "y AS yz", "z AS zy", "[x:1]", "x z");
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
	
	/*
	for (auto table : DB)
	{
		dout << "Table: " << table->name << "\n";
	}*/
	//TODO
	
	
	
	
	dout << "TTable Create Statement:\n";
	auto ttableTableStmt = TTable->tableStatement();
	dout << ttableTableStmt << std::endl;
	assert_ex(ttableTableStmt == "CREATE TABLE TTable (x INTEGER PRIMARY KEY, y integer)");
	
	
	try
	{
		dout << joined->tableStatement() << "\n";
		assert_not_reached();
	}
	catch (SQL::SQLErrorException)
	{
		dout << "Successfully caught exception for missing sql statement for joined table\n"; 
	}
	
	
	assert_ex(con.tableExists("TTable"));
	assert_ex(!con.tableExists("[TTable]"));
	
	con.vQuery("ATTACH DATABASE '" + filename + "-1.sqlite' AS DB2;");
	SQL::SQLDatabase DB2 = SQL::SQLDatabase::Create(&con, "DB2");
	
	
	
	
	auto ridClause = joined->columns["rowid"] <= 1;
	dout << ridClause.toString() << "\n";
	q2 = joined->select("rowid", "*", ridClause);
	while (q2->next())
	{
		for (int i = 0; i < q2->width(); ++i)
		{
			dout << q2->columnName(i) << ", ";
		}
		dout << "\n";
		for (int i = 0; i < q2->width(); ++i)
		{
			dout << q2->column<std::string>(i) << ", ";
		}
		dout << "\n";
		/*dout << q2->columnName(0) << ", " << q2->columnName(1) << "\n";
		dout << q2->column<int>(0) << ", " << q2->column<std::string>(1) << "\n";*/
	}
	delete q2;
	
	
	dout << "Getting rows from collections...\n";
	try
	{
		SQL::SQLRow jRow0 = joined->rows[SQL::SQLPK("H")];
		assert_not_reached();
	}
	catch (SQL::SQLErrorException&)
	{
		dout << "jRow0 Exception successfully caught\n";
	}
	
	SQL::SQLRow row0 = TTable->rows[SQL::SQLRID(1)];
	assert_ex(row0[0] == "1");
	auto row1 = TTable->rows[SQL::SQLRID(1)];
	assert_ex(row1[0] == "1");
	row1 = row0;
	assert_ex(row1[0] == "1");
	
	
	
	
	delete printQuery(con.query("SELECT (x + 1 + (SELECT COUNT(*) FROM [TTable])) AS x, y FROM [DB2].[TTable] LIMIT 10"));
	con.vQuery("INSERT INTO [TTable] SELECT (x + 1 + (SELECT COUNT(*) FROM [TTable])) AS x, y FROM [DB2].[TTable]");
	auto lastTen = printQuery(con.query("SELECT * FROM [TTable] ORDER BY x DESC LIMIT 10"));
	con.vQuery("UPDATE [TTable] SET y=x*x");
	delete printQuery(lastTen);
	
	
	}
	
	dout << "\nPending Statements:\n";
	for (auto stmt : con.pending())
	{
		dout << sqlite3_expanded_sql(stmt) << "\n";
	}
	assert_ex(con.pending().size() == 0);
	}
	
	
	
	
	
	
	
	
	
	
	
	
	//ORM Testing
	{
		const std::string filename = "ORM_DB.sqlite";
		auto con = new SQL::SQLiteConnection(filename);
		auto sys = SQL::SQLSystem::Create(con);
		
		
		auto dropQuery = con->tablesQuery();
		std::vector<std::string> dropTableNames;
		while (dropQuery->next())
		{
			if (dropQuery->column<std::string>(0) != "sqlite_sequence")
			{
				dropTableNames.push_back(dropQuery->column<std::string>(0));
			}
		}
		delete dropQuery;
		
		for (auto name : dropTableNames)
		{
			try
			{
				//dout << "DROP TABLE [" << dropQuery->column<std::string>(0) << "];" << std::endl;
				dout << "Dropping [" << name + "]\n";
				con->vQuery("DROP TABLE [" + name + "];");
			}
			catch (std::exception& e)
			{
				dout << "Caught " << e.what() << std::endl;
			}
		}
		
		
		
		#define GUID_t
		class Person
		{
			public:
			#ifdef GUID_t
			typedef QUtils::GUID id_t;
			#else
			typedef long id_t;
			#endif
			private:
			id_t id;
			
			public:
			Person()
			{
				#ifdef GUID_t
				id = QUtils::GUID::Create();
				#else
				id = 1;
				#endif
			}
			
			std::string fname;
			std::string lname;
			//decltype(time(NULL)) birth;
			unsigned long birth;
			
			auto age() const
			{
				return static_cast<long double>(time(NULL) - birth)/(3600*24*365);
			}
			
			static Person Birth(std::string fname, std::string lname)
			{
				Person p;
				p.fname = fname;
				p.lname = lname;
				p.birth = time(NULL);
				return p;
			}
			
			friend class PersonModel;
		};
		
		class PersonModel : public SQL::SQLModel<Person>
		{
			protected:
			
			void buildModel(SQL::SQLModelBuilder<Person>& builder) override
			{
				builder.tablename("Person");
				builder.property("fname", [](auto& obj) -> std::string& { return obj.fname; }).notNull();
				builder.property("lname", [](auto& obj) -> std::string& { return obj.lname; }).notNull();
				builder.property("birth", [](auto& obj) -> decltype(obj.birth)& { return obj.birth; }).notNull();
				builder.id([](auto& obj) -> decltype(obj.id)& { return obj.id; });
				
			}
			
			std::string modelName() const override
			{
				return "Person";
			}
		};
		
		
		
		sys->model<PersonModel>();
		
		
		sys->buildModels(/*dropIfConflict: */true);
		
		
		Person p1 = Person::Birth("SomePerson", "SomeSurname");
		
		sys->checkIn(p1);
		
		dout << "\n\nPerson Table: \n";
		auto personQ = printQuery(sys->connection->query("SELECT * FROM [Person];"));
		
		
		
		auto p1Query = sys->connection->query("UPDATE [Person] SET [fname]=@val2 WHERE [birth] > @VAL");
		p1Query->bind("@VAL", 100);
		p1Query->bind("@val2", "NewName");
		dout << "\n\nP1 Query: \n";
		dout << p1Query->statement() << "\n";
		delete printQuery(p1Query);
		
		
		
		Person p2 = Person::Birth("Person2", "SomeSurname");
		
		sys->checkIn(p2);
		
		
		
		dout << "\n\nPerson Table: \n";
		personQ->reset();
		printQuery(personQ);
		
		sys->checkIn(p1);
		
		dout << "\n\nPerson Table: \n";
		personQ->reset();
		printQuery(personQ);
		
		sys->checkIn(p2);
		
		Person p3 = Person::Birth("Person'3", "SomeSurname");
		
		sys->checkIn(p3);
		
		dout << "\n\nPerson Table: \n";
		personQ->reset();
		printQuery(personQ);
	}
	
	
	
	
	
	
	dout << "\n\n";
	return true;
}