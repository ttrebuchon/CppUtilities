#include <iostream>

#include <QUtils/String/String.h>
#include <QUtils/Network/Utilities.h>
#include <QUtils/SQL/SQL.h>
#include <QUtils/SQL/SQLite/SQLite.h>


using QUtils::String;




int main()
{
	String str = "!!!Hello, world!";
	
	std::cout << str << "\n";
	str = str.substr(3).toUpper();
	std::cout << str << "\n";
	
	
	
	
	std::cout << "______________________\n\n\n";
	std::cout << QUtils::Network::getPage("www.google.com") << "\n";
	QUtils::SQL::SQLiteConnection con("file.sqlite");
	con.open();
	
	con.close();
	
	
	return 0;
}