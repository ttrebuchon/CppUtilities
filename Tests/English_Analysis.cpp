#include "../Tests_Helpers.h"
#include <QUtils/English/Analysis.h>
#include <QUtils/Markov/Markov.h>
#include <QUtils/English/Analysis/Analysis.h>
#include <QUtils/Stopwatch/Stopwatch.h>
#include <QUtils/String/String.h>

#include <fstream>

using QUtils::English::Analyzer;
bool Test_English_Analysis()
{
	std::ifstream file("Test_Files/English_Analyzer_Test.txt");
	Analyzer AN(file);
	file.close();
	
	dout << "Size: " << std::flush << AN.contents.size() << std::endl;
	
	int letters_nums = 0;
	for (auto c : AN.contents)
	{
		if (QUtils::English::isLetterOrNumber(c))
		{
			++letters_nums;
		}
	}
	dout << "Letters/Numbers: " << letters_nums << std::endl;
	
	QUtils::Stopwatch::Stopwatch sw;
	sw.start();
	
	AN.parse();
	sw.stop();
	dout << "Took " << sw.value() << std::endl;
	
	dout << "Tokens Count: " << AN.tokens.size() << "\n";
	
	/*
	sw.reset();
	sw.start();
	
	
	dout << "Getting chain...\n";
	auto MC = AN.markov(false);
	sw.stop();
	dout << "Adding data took " << sw.value() << "\n";
	
	sw.start();
	dout << "Generating...\n";
	auto chain = MC->GenerateChain();
	sw.stop();
	
	std::ofstream ofile("English_Out.txt");
	for (auto link : *chain)
	{
		//dout << link->text();
		ofile << link->text();
	}
	ofile.close();
	dout << "------------\n";
	dout << "Took " << sw.value() << "\n";
	*/
	
	/*for (int i = 0; i < 100; i++)
	{
		dout << AN.tokens[i]->text();
	}
	dout << "\n-----------\n";*/
	dout << "Expanding..." << std::endl;
	dout << "Expanded Size: " << AN.expand().size() << "\n";
	dout << "Unique Words: " << AN.words.size() << std::endl;
	{
		int i = 0;
		for (auto word : AN.words)
		{
			dout << word->text() << ", ";
			if (i++ > 100)
			{
				dout << std::endl;
				break;
			}
		}
	}
	
	dout << "Unique Sentences: " << AN.sentences.size() << std::endl;
	{
		int i = 0;
		for (auto sen : AN.sentences)
		{
			QUtils::String text = sen->text();
			if (!text.contains("[]"))
			{
			dout << "\"" << sen->text() << "\"\n";
			if (i++ > 10)
			{
				dout << "-------------\n\n";
				break;
			}
			}
		}
	}
	dout << std::flush;
	{
		std::string text;
		for (auto token : AN.tokens)
		{
			text += token->text();
		}
		dout << "Length of full string: " << text.length() << std::endl;
	}
	
	dout << "Distinct Tokens: " << AN.distinctTokens.size() << "\n";
	//dout << "Uniform Token Count: " << AN.uniformTokens.size() << std::endl;
	
	auto anubisToken = std::dynamic_pointer_cast<QUtils::English::Internal::Word>(AN.getToken("Anubis"));
	assert_ex(anubisToken != NULL);
	dout << "Anubis Token: \"" << anubisToken->text() << "\"\n";
	
	
	sw.reset();
	sw.start();
	AN.calcSubtokens();
	sw.stop();
	dout << "Calculated Subtokens.\n";
	dout << "Took " << sw.value() << std::endl;
	
	
	sw.reset();
	sw.start();
	AN.calcEquivalents();
	sw.stop();
	dout << "Calculated Equivalents.\n";
	dout << "Took " << sw.value() << std::endl;
	
	sw.reset();
	/*sw.start();
	AN.calcDistances();
	sw.stop();
	dout << "Calculated Distances.\n";
	dout << "Took " << sw.value() << std::endl;
	
	dout << "Anubis clustering count: " << AN.clusteringRatings.at(anubisToken)->size() << "\n";*/
	
	
	
	return true;
}