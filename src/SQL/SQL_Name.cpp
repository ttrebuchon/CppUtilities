#include <vector>
#include <string>

namespace QUtils
{
namespace SQL
{
	std::vector<std::string> SQL_Name_Parse(std::string input)
	{
		std::vector<std::string> segments;
		size_t i = 0;
		while (i < input.length())
		{
			if (input[i] == '.')
			{
				segments.push_back(input.substr(0, i));
				input = input.substr(i+1);
				i = 0;
			}
			else if (input[i] == '[')
			{
				auto len = input.length();
				while (input[++i] != ']' && i < len-1) ;
				if (i == len-1 && input[i] != ']')
				{
					//TODO
					throw std::exception();
				}
				segments.push_back(input.substr(1, i-1));
				if (len > i+1)
				{
					if (input[i+1] == '.')
					{
						input = input.substr(i+2);
					}
					else
					{
						input = input.substr(i+1);
					}
					i = 0;
				}
				else
				{
					return segments;
				}
			}
			else
			{
				++i;
			}
		}
		
		if (input != "")
		{
			segments.push_back(input);
		}
		return segments;
		
	}
}
}