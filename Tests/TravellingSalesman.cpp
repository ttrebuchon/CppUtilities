#include "../Tests_Helpers.h"

#include <vector>
#include <map>
#include <tuple>
#include <math.h>
#include <exception>


void generateProblem(const int count, const int bound, std::vector<std::tuple<int, int, double>>& edges)
{
	std::map<int, std::tuple<int, int>> points;
	
	int x, y;
	for (int i = 0; i < count; i++)
	{
		x = (static_cast<double>(rand())/RAND_MAX - 0.5)*2*bound;
		y = (static_cast<double>(rand())/RAND_MAX - 0.5)*2*bound;
		points[i] = std::make_tuple(x, y);
	}
	
	double dist;
	int x0, y0;
	for (int i = 0; i < count; i++)
	{
		x = std::get<0>(points[i]);
		y = std::get<1>(points[i]);
		for (int j = i+1; j < count; j++)
		{
			x0 = std::get<0>(points[j]);
			y0 = std::get<1>(points[j]);
			dist = sqrt((x - x0)*(x-x0) + (y - y0)*(y - y0));
			edges.push_back(std::make_tuple(i, j, dist));
		}
	}
}








/*double getEdge(const auto edges, const int a, const int b)
{
	int A = a, B = b;
	if (a > b)
	{
		A = b;
		B = a;
	}
	return edges.at(A).at(B);
}*/
	
double fitness(const std::map<int, std::map<int, double>>& edges, const int* v, const int count)
{
	
	double total = 0;
	for (int i = 1; i < count; i++)
	{
		if (v[i-1] > v[i])
		{
			total += edges.at(v[i]).at(v[i-1]);
		}
		else
		{
			total += edges.at(v[i-1]).at(v[i]);
		}
	}
	
	if (v[count-1] > v[0])
	{
		total += edges.at(v[0]).at(v[count-1]);
	}
	else
	{
		total += edges.at(v[count-1]).at(v[0]);
	}
	
	return total;
}








void solve(int* best, double* bestD, const int count, const std::map<int, std::map<int, double>>& edges, bool* remaining, int index, int* solution)
{
	if (index == count)
	{
		double fit = fitness(edges, solution, count);
		if (fit < *bestD || *bestD < 0)
		{
			*bestD = fit;
			for (int i = 0; i < count; i++)
			{
				best[i] = solution[i];
			}
		}
		return;
	}
	
	for (int i = 0; i < count; i++)
	{
		if (remaining[i])
		{
			solution[index] = i;
			remaining[i] = false;
			solve(best, bestD, count, edges, remaining, index+1, solution);
			remaining[i] = true;
		}
	}
}

double bruteForce(int** bestPtr, int count, const std::map<int, std::map<int, double>>& edges)
{
	int* best = (*bestPtr) = new int[count];
	
	auto remaining = new bool[count];
	for (int i = 0; i < count; i++)
	{
		remaining[i] = true;
	}
	
	int* solution = new int[count];
	double bestD = -1;
	
	solve(best, &bestD, count, edges, remaining, 0, solution);
	
	delete[] solution;
	delete[] remaining;
	
	return bestD;
}




void mutate(int* solution, const int count)
{
	int i1 = rand() % count;
	int i2 = rand() % count;
	while (i2 == i1)
	{
		i2 = rand() % count;
	}
	
	solution[i1] += solution[i2];
	solution[i2] = solution[i1] - solution[i2];
	solution[i1] -= solution[i2];
	
}


void breed(const int* solution1, const int* solution2, const int count, int* child, const int rate)
{
	if (rate >= count)
	{
		throw std::exception();
	}
	const int* itS = solution1;
	for (int* itC = child; itC != child + count; itC++)
	{
		*itC = *itS;
		itS++;
	}
	
	
	int overwritten;
	int start = rand() % count;
	int nVal;
	for (auto i = 0; i < rate; i++)
	{
		overwritten = child[(start + i) % count];
		
		nVal = solution2[(start + i) % count];
		for (int j = 0; j < count; j++)
		{
			if (child[j] == nVal)
			{
				child[j] = overwritten;
			}
		}
		
		child[(start + i) % count] = nVal;
		
	}
}

int* genRandomSolution(const int count)
{
	int* s = new int[count];
	for (auto i = 0; i < count; i++)
	{
		s[i] = i;
	}
	
	for (auto i = 0; i < count; i++)
	{
		std::random_shuffle(s, s+count);
	}
	
	return s;
}






bool Test_TravellingSalesman()
{
	const int count = 200;
	const int bound = 10;
	const int popSize = 100;
	const int generations = 100;
	const int genotype = count / 3;
	
	
	
	
	std::vector<std::tuple<int, int, double>> rawData;
	dout << "Generating problem..." << std::endl;
	generateProblem(count, bound, rawData);
	
	std::map<int, std::map<int, double>> edges;
	
	dout << "Organizing data..." << std::endl;
	for (auto& e : rawData)
	{
		edges[std::get<0>(e)][std::get<1>(e)] = std::get<2>(e);
	}
	
	
	
	
	
	auto pArray = [] (const int* arr, const int count) -> void
	{
		dout << "[";
		for (auto i = 0; i < count; i++)
		{
			dout << (i == 0 ? "" : ", ") << arr[i];
		}
		dout << "]\n";
	};
	
	
	dout << "Generating population..." << std::endl;
	int** population = new int*[popSize];
	for (auto i = 0; i < popSize; i++)
	{
		population[i] = genRandomSolution(count);
		assert_ex(population[i] != NULL);
	}
	
	
	
	std::map<const int*, double> populationFitness;
	
	auto evalPop = [&edges, &populationFitness, count] (int** population) -> void
	{
		for (int i = 0; i < popSize; i++)
		{
			populationFitness[population[i]] = fitness(edges, population[i], count);
		}
	};
	
	auto fitCompare = [count, &edges, &populationFitness](const int* ptr, const int* ptr2) -> bool
	{
		return populationFitness[ptr] < populationFitness[ptr2];
		//return fitness(edges, ptr, count) < fitness(edges, ptr2, count);
	};
	
	auto sortPop = [&]() -> void
	{
		evalPop(population);
		std::sort(population, population + popSize, fitCompare);
	};
	
	dout << "Sorting population..." << std::endl;
	sortPop();
	
	
	for (int g = 0; g < generations; g++)
	{
	dout << "Gen " << (g+1) << ":\n";
	
	//dout << "\tBreeding..." << std::endl;
	int eIndex = popSize-1;
	for (int i = 1; i < eIndex; i++)
	{
		breed(population[i-1], population[i], count, population[eIndex], genotype);
		eIndex--;
	}
	
	//dout << "\tMutating..." << std::endl;
	for (int i = popSize-1; i > eIndex; i--)
	{
		if (rand() % 4 == 0)
		{
			mutate(population[i], count);
		}
	}
	
	//dout << "\tSorting..." << std::endl;
	sortPop();
	dout << "\tTop: " << populationFitness[population[0]] << "\n";
	
	
	}
	
	
	
	
	dout << "Printing..." << std::endl;
	for (auto it = population; it != population + 5 && it != population + popSize; it++)
	{
		dout << "\n\n";
		pArray(*it, count);
		dout << "fit: " << fitness(edges, *it, count) << "\n";
	}
	/*
	dout << "Brute Forcing..." << std::endl;
	int* best;
	bruteForce(&best, count, edges);
	dout << "\n\nActual: " << fitness(edges, best, count) << "\n";
	pArray(best, count);
	delete[] best;*/
	
	dout << "Deleting..." << std::endl;
	delete[] population;
	dout << "Deleted." << std::endl;
	
	return true;
}