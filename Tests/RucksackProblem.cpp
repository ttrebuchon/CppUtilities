#include "../Tests_Helpers.h"

#include <QUtils/Genetic/Genetic.h>
#include "../Data/RucksackData.h"
#include <algorithm>
#include <random>


bool Test_RucksackProblem()
{
	const int count = RucksackData::count;
	const double space = RucksackData::space;
	auto items = RucksackData::items();
	dout << (items.size()*sizeof(items.at(0)) + sizeof(items)) << "\n";
	long double x = 0, y = 0;
	for (auto item : items)
	{
		x += std::get<0>(item);
		y += std::get<1>(item);
	}
	dout << "(" << x << ", " << y << ")\n";
	
	auto fitness = [&items, space](const auto& order) -> double
	{
		long double value = 0;
		int remspace = RucksackData::space;
		int index = 0;
		while (index < items.size() && index < order.size())
		{
			if (remspace < std::get<0>(items[order[index]]))
			{
				break;
			}
			else
			{
				remspace -= std::get<0>(items[order[index]]);
				value += std::get<1>(items[order[index]]);
				//dout << remspace << ", " << value << "\n";
			}
			++index;
		}
		return value;
	};
	
	
	auto verboseFitness = [&items, space](const auto& order) -> double
	{
		dout << "\n";
		long double value = 0;
		int remspace = RucksackData::space;
		int index = 0;
		while (index < items.size() && index < order.size())
		{
			dout << "Item is " << order[index] << "\n";
			if (remspace < std::get<0>(items[order[index]]))
			{
				dout << "Breaking\n";
				break;
			}
			else
			{
				remspace -= std::get<0>(items[order[index]]);
				value += std::get<1>(items[order[index]]);
				dout << remspace << ", " << value << "\n";
			}
			++index;
		}
		dout << "------\n" << value << "\n";
		return value;
	};
	
	std::vector<int> order(count);
	for (int i = 0; i < count; ++i)
	{
		order[i] = i;
	}
	
	auto defaultFit = fitness(order);
	dout << "\n\n-----------\n" << defaultFit << "\n\n\n";
	
	std::random_shuffle(order.begin(), order.end());
	
	auto randFit = fitness(order);
	dout << "\n\n-----------\n" << randFit << "\n";
	
	{
		const int popCount = 10;
		const int generations = 100;
		using namespace QUtils::Genetic;
		auto pop = std::make_shared<ArrayPopulation<OrderedSolution<int>>>(fitness, popCount);
		
		for (int i = 0; i < popCount; ++i)
		{
			pop->at(i) = std::make_shared<OrderedSolution<int>>(count, 0, count-1);
		}
		
		dout << "Population of " << popCount << " created..." << std::endl;
		
		CrossoverAlgorithm<OrderedSolution<int>> alg(pop);
		alg.mutateProbability = 0.5;
		alg.sequenceLength = count/100;
		if (alg.sequenceLength <= 1)
		{
			alg.sequenceLength = -1;
		}
		dout << "Algorithm created..." << std::endl;
		
		
		dout << "Initial Best: " << std::flush << fitness(*alg.best().get()) << std::endl;
		dout << "Running algorithm for " << generations << " generations...\n";
		
		const int step = 10;
		for (int i = 0; i < generations; i += step)
		{
			dout << "Running Gen(s) " << (i+1) << "-" << (i+step) << std::endl;
			alg.go(step);
			dout << "Current Best: " << fitness(*alg.best()) << "\n";
			
		}
		dout << "Algorithm ran." << std::endl;
		
		auto best = alg.best();
		assert_ex(best != NULL);
		auto bestFit = fitness(*best.get());
		dout << "\n\n\nBest: " << bestFit << "\n";
		
		auto tmpOrder = order;
		auto val = fitness(order);
		for (int i = 0; i < generations; ++i)
		{
			dout << i << ": " << std::flush;
			std::random_shuffle(tmpOrder.begin(), tmpOrder.end());
			
			auto tmpVal = fitness(tmpOrder);
			if (tmpVal > val)
			{
				val = tmpVal;
			}
			dout << val << "\n";
			
		}
		
	}
	
	return true;
}