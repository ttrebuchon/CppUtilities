#include "../Tests_Helpers.h"

#include <QUtils/String/String.h>
#include <QUtils/Stopwatch/Stopwatch.h>

#include <string>

double CppPerfTest(int perfcount)
{
	QUtils::Stopwatch::Stopwatch sw;
	std::vector<std::string> cppStrs;
	
	sw.start();
	for (int i = 0; i < 100; i++)
	{
		std::string cppStr;
		for (int x = 0; x <= perfcount; x++)
		{
			cppStr += std::to_string(x);
		}
		cppStrs.push_back(cppStr);
	}
	sw.stop();
	return sw.value();
}

double UtilPerfTest(int perfcount)
{
	QUtils::Stopwatch::Stopwatch sw;
	std::vector<QUtils::String> utilStrs;
	
	
	sw.start();
	for (int i = 0; i < 100; i++)
	{
		QUtils::String utilStr;
		for (int x = 0; x <= perfcount; x++)
		{
			utilStr << x;
		}
		utilStrs.push_back(utilStr);
	}
	sw.stop();
	return sw.value();
}

using QUtils::String;

bool Test_String()
{
	QUtils::String str;
	
	assert_ex(((std::string)str) == "");
	
	str += "Hello";
	assert_ex(str == "Hello");
	
	str = "Helo";
	assert_ex(str == "Helo");
	
	assert_ex(str[0] == 'H');
	str[0] = 'h';
	assert_ex(str[0] == 'h');
	assert_ex(str == "helo");
	assert_ex(str[1] == 'e');
	str[0] = 'H';
	str[1] = 'E';
	str[str.length()-1] = 'O';
	assert_ex(str == "HElO");
	
	QUtils::String str_2 = str;
	assert_ex(str_2.toLower() == "helo");
	assert_ex(str_2.toUpper() == "HELO");
	str += ' ';
	str += "abc ";
	str_2 = str;
	assert_ex(str.toLower() == "helo abc ");
	assert_ex(str.toUpper() == "HELO ABC ");
	
	assert_ex((str_2 = str.replace(" ", "")) == "HElOabc");
	
	str_2 = str_2.toLower();
	str_2 = str_2.substr(0, 4);
	assert_ex(str_2 == "helo");
	
	assert_ex(str_2.size() == str_2.length());
	assert_ex(str_2.size() == 4);
	
	assert_ex(&str_2.at(1) == &str_2[1]);
	
	str_2 = "";
	assert_ex(str_2.empty());
	
	str_2 << "_______A";
	assert_ex(str_2 == "_______A");
	assert_ex(str_2.contains("A"));
	assert_ex(str_2.find("A") == 7);
	
	assert_ex(str_2.startsWith("___"));
	assert_ex(str_2.startsWith(QUtils::String("___")));
	assert_ex(str_2.endsWith("A"));
	str = "A";
	assert_ex(str_2.endsWith(str));
	str_2 = "   " + str_2;
	assert_ex(str_2 == "   _______A");
	assert_ex(str_2.removeWhitespaces() == "_______A");
	assert_ex(str_2.removeWhitespaces().reverse() == "A_______");
	
	assert_ex(str_2.count("_") == 7);
	assert_ex(str_2.count("__") == 3);
	
	//dout << "\"" << str_2 << "\" -> shuffle() -> \"" << str_2.shuffle() << "\"" << std::endl;
	assert_ex(str_2.shuffle() != str_2);
	
	str = "A B C D";
	str_2 = "Hello, world!";
	
	
	auto v1 = str.separateBy(" ");
	auto v2 = str_2.separateBy(",");
	
	assert_ex(v1.size() == 4);
	for (int i = 0; i < v1.size(); i++)
	{
		QUtils::String correctV;
		switch (i)
		{
			case 0:
			correctV = "A";
			break;
			
			case 1:
			correctV = "B";
			break;
			
			case 2:
			correctV = "C";
			break;
			
			case 3:
			correctV = "D";
			break;
			
			default:
			assert_ex(i <= v1.size());
			break;
		}
		
		assert_ex(correctV == v1[i]);
	}
	
	assert_ex(v2.size() == 2);
	for (int i = 0; i < v2.size(); i++)
	{
		QUtils::String correctV;
		switch (i)
		{
			case 0:
			correctV = "Hello";
			break;
			
			case 1:
			correctV = " world!";
			break;
			
			default:
			assert_ex(i <= v2.size());
			break;
		}
		
		assert_ex(correctV == v2[i]);
	}
	
	assert_ex(QUtils::String("ABCDE").separateBy(" ").size() == 1);
	
	str = "4";
	assert_ex(str.toInt() == (int)4);
	str_2 = "4.26";
	assert_ex(str_2.toDouble() == (double)4.26);
	assert_ex(str_2.toFloat() == (float)4.26);
	
	str << 6;
	assert_ex(str.toInt() == 46);
	
	assert_ex(str_2.insert(1, "6") == "46.26");
	
	//Test iteration
	int i = 0;
	for (auto c : str_2)
	{
		switch (i)
		{
			case 0:
			assert_ex(c == '4');
			break;
			
			case 1:
			assert_ex(c == '.');
			break;
			
			case 2:
			assert_ex(c == '2');
			break;
			
			case 3:
			assert_ex(c == '6');
			break;
			
			default:
			assert_ex(false);
			break;
		}
		i++;
	}
	assert_ex(i == 4);
	
	
	
	
	//Performance Test
	double cppTime, utilTime;
	int perfcount = 10000;
	
	//Cpp string testing
	cppTime = CppPerfTest(perfcount);
	
	
	//Util String testing
	utilTime = UtilPerfTest(perfcount);
	
	dout << "cpp time:\t" << cppTime << "\nutil time:\t" << utilTime << std::endl;
	assert_ex(utilTime - cppTime < 0.000015*perfcount);
	
	{
		std::string cppStr = "\n\t\n\\  gh \n";
		String str = cppStr;
		assert_ex(cppStr == str);
		
		auto str2 = str.replace("\n", "abc");
		assert_ex(str2 == "abc\tabc\\  gh abc");
		
		str = str.replace("\n", "abc");
		assert_ex(str == "abc\tabc\\  gh abc");
		assert_ex(str == str2);
		
		
		str = cppStr;
		
		str2 = str.replace("\n", "\\n");
		assert_ex(str2 == "\\n\t\\n\\  gh \\n");
		
		
	}
	
	return true;
}