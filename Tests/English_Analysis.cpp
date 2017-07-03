#include "../Tests_Helpers.h"
#include <QUtils/English/Analysis.h>

using QUtils::English::Analyzer;
bool Test_English_Analysis()
{
	std::ifstream file("Test_Files/ScatterAndHowl.txt");
	Analyzer AN(file);
	file.close();
	
	dout << "Size: " << AN.contents.size() << std::endl;
	
	int letters_nums = 0;
	for (auto c : AN.contents)
	{
		if (QUtils::English::isLetterOrNumber(c))
		{
			++letters_nums;
		}
	}
	dout << "Letters/Numbers: " << letters_nums << std::endl;
	return true;
}