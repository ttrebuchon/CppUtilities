#include "../Tests_Helpers.h"
#include "QUtils/Markov/Markov.h"
#include <QUtils/Stopwatch/Stopwatch.h>

#include <string>

#define TEST_COUNT 5
#define GROUPING 1

struct Word
{
	std::string word;
	
	Word(std::string str) : word(str) {}
};

Word MakeWord(std::string str)
{
	for (int i = 0; i < str.length(); i++)
	{
		str[i] = std::tolower(str[i]);
	}
	
	
	return Word(str);
}

bool ValidCurrent(std::string s)
{
	std::string cur = "";
	for (char c : s)
	{
		if (c!=' '&&c!='\t'&&c!='\n')
		{
			cur += c;
		}
	}
	return (cur.length() > 0);
}

std::vector<Word> ParseMsg(std::string msg)
{
	std::vector<Word> words;
	
	std::vector<std::string> elems;
	std::vector<std::string> tmp;
	std::string current = "";
	
	for (int i = 0; i < msg.length(); i++)
	{
		char c = msg[i];
		if (c == ' ' || c=='\t'||c=='\n')
		{
			if (ValidCurrent(current))
			{
				elems.push_back(current);
			}
			current = "";
		}
		else
		{
			current += c;
		}
	}
	if (ValidCurrent(current))
	{
		elems.push_back(current);
	}
	current = "";
	
	tmp = elems;
	elems = std::vector<std::string>();
	
	for (int i = 0; i < tmp.size(); i++)
	{
		for (char c : tmp[i])
		{
			if (c == '.'||c=='?'||c=='!'||c==','||c==';'||c==':')
			{
				if (ValidCurrent(current))
				{
					elems.push_back(current);
				}
				current = "";
				elems.push_back(std::string("") + c);
			}
			else
			{
				current += c;
			}
		}
		if (ValidCurrent(current))
		{
			elems.push_back(current);
		}
		current = "";
	}
	
	tmp = elems;
	elems = std::vector<std::string>();
	
	for (int i = 0; i < tmp.size(); i++)
	{
		current = "";
		if (tmp[i] == ".")
		{
			current += ".";
			int g = i+1;
			while (g < tmp.size())
			{
				if (tmp[g] != ".")
				{
					break;
				}
				g++;
			}
			for (int h = i+1; h < g; h++)
			{
				current += ".";
			}
			elems.push_back(current);
			i = g-1;
		}
		else if (tmp[i] == "!" || tmp[i] == "?")
		{
			current += tmp[i];
			int g = i+1;
			while (g < tmp.size())
			{
				if (tmp[g] != "?" && tmp[g] != "!")
				{
					break;
				}
				current += tmp[g];
				g++;
			}
			elems.push_back(current);
			i = g-1;
		}
		else
		{
			elems.push_back(tmp[i]);
		}
	}
	
	
	for (auto str : elems)
	{
		words.push_back(MakeWord(str));
	}
	
	
	return words;
}





std::string FormMsg(std::vector<Word>& vec)
{
	std::string str = "";
	for (int i = 0; i < vec.size(); i++)
	{
		std::string w = vec[i].word;
		char c = w[0];
		if (i > 0 && c != ',' && c != '.' && c != '!' && c != '?')
		{
			str += " ";
		}
		if (w.length() == 1 && c == 'i')
		{
			w = "I";
		}
		
		if (i == 0)
		{
			w[0] = std::toupper(w[0]);
		}
		str += w;
	}
	
	return str;
}






using Mk = QUtils::Markov::Markov<Word>;
bool Test_Markov()
{
	Mk m;
	auto _words = "Hello, world! I am a person...and I wrote you!?!?";
	std::vector<std::string> trainingStrings = { 
	_words,
	"This is a sentence",
	"This is also a sentence",
	"Hello, world!",
	"Test Message",
	".....wtf",
	"Yeah gimme a sec",
	"I'll be on in a sec",
	"That's always fun. But I'm super excited that the recording worked this time! Finally I can do editing and get back into that hobby",
	"Rylan and I playing ds",
	"Also the recording worked from last night and now it's not a frame a second!",
	
	
	};
	std::vector<std::vector<Word>> trainingSets;
	for (auto str : trainingStrings)
	{
		auto parsed = ParseMsg(str);/*
		std::vector<Word> grouped;
		for (int i = GROUPING-1; i < parsed.size(); i++)
		{
			std::string sect = "";
			for (int k = i - (GROUPING-1); k <= i; k++)
			{
				if (k > (i - (GROUPING-1)))
				{
					sect += " ";
				}
				sect += parsed[k].word;
			}
			Word w(sect);
			grouped.push_back(w);
		}
		
		
		trainingSets.push_back(grouped);*/
		trainingSets.push_back(parsed);
	}
	
	m.equals = [](Word w1, Word w2) { return (w1.word == w2.word); };
	
	for (auto words : trainingSets)
	{
		m.AddTrainChain(words);
	}
	
	dout << "Generating chain..." << std::endl;
	auto vec = m.GenerateChain();
	dout << "Printing..." << std::endl;
	//dout << "\n\n" << std::endl;
	dout << "\n\"" << FormMsg(*vec) << "\"" << std::endl;
	delete vec;
	
	
	
	dout << "\nGenerating More...\n" << std::endl;
	QUtils::Stopwatch::Stopwatch sw;
	sw.start();
	for (int i = 0; i < TEST_COUNT; i++)
	{
		//sw.start();
		vec = m.GenerateChain();
		//sw.stop();
		dout << "\"" << FormMsg(*vec) << "\"" << std::endl;
		delete vec;
	}
	sw.stop();
	
	dout << "\nTime to generate " << TEST_COUNT << " chains: " << sw.value() << " seconds" << std::endl;
	
	
	dout << "\n\nTesting many chains..." << std::endl;
	sw.reset();
	int manyCount = 100000;
	std::vector<std::vector<Word>*> vecs;
	
	
	sw.start();
	for (auto i = 0; i < manyCount; i++)
	{
		//sw.start();
		vec = m.GenerateChain();
		//sw.stop();
		//dout << "\"" << FormMsg(*vec) << "\"" << std::endl;
		delete vec;
		//vecs.push_back(vec);
	}
	sw.stop();
	
	dout << "\nTime to generate " << manyCount << " chains: " << sw.value() << " seconds" << std::endl;
	
	
	
	
	return true;
}