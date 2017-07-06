#include "../Tests_Helpers.h"
#include <QUtils/English/Analysis.h>
#include <QUtils/Markov/Markov.h>
#include <QUtils/English/Analysis/Token.h>

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
	
	AN.parse();
	
	dout << "Tokens Count: " << AN.tokens.size() << "\n";
	
	
	
	dout << "Getting chain...\n";
	auto MC = AN.markov();
	
	dout << "Generating...\n";
	auto chain = MC->GenerateChain();
	
	for (auto link : *chain)
	{
		dout << link->text();
	}
	
	dout << "------------\n";
	
	return true;
}