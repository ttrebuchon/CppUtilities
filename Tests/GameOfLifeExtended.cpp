#include "../Tests_Helpers.h"
#include <vector>
#include <map>
#include <cmath>
#include <stdexcept>
#include <climits>

#include <QUtils/Combinatorial/Combinatorial.h>
#include <QUtils/Genetic/Genetic.h>






































struct Vec;

std::ostream& operator<<(std::ostream& os, const Vec v);
Vec operator-(const Vec v1, const Vec v2);
Vec operator+(const Vec v1, const Vec v2);
Vec operator*(const Vec v1, const double n);
Vec operator/(const Vec v1, const double n);

struct Vec
{
	double x;
	double y;
	
	Vec() : x(0), y(0)
	{}
	
	Vec(double x, double y) : x(x), y(y)
	{}
	
	/*Vec rotateClock(int count = 1) const
	{
		Vec v;
		v.x = x;
		v.y = y;
		
		int tmp;
		while (count-- > 0)
		{
			tmp = v.y;
			v.y = -v.x;
			v.x = tmp;
		}
		
		return v;
		
		
	}*/
	
	Vec normalize() const
	{
		double mag = sqrt(x*x + y*y);
		Vec v(x/mag, y/mag);
		return v;
	}
	
	
	Vec resolve(const int speed) const
	{
		Vec v = normalize() * speed;
		
		int dist = speed;
		
		Vec pos = {0, 0};
		Vec dir;
		while (dist-- > 0)
		{
			dir = v - pos;
			
			if (fabs(dir.x) > fabs(dir.y))
			{
				if (dir.x > 0)
				{
					pos.x++;
				}
				else
				{
					pos.x--;
				}
			}
			else
			{
				if (dir.y > 0)
				{
					pos.y++;
				}
				else
				{
					pos.y--;
				}
			}
		}
		
		
		return pos;
	}
	
	double mag() const
	{
		return sqrt(x*x + y*y);
	}
	
};

std::ostream& operator<<(std::ostream& os, const Vec v)
{
	return (os << "<" << v.x << ", " << v.y << ">");
}

Vec operator-(const Vec v1, const Vec v2)
{
	return {v1.x - v2.x, v1.y - v2.y};
}

Vec operator+(const Vec v1, const Vec v2)
{
	return {v1.x + v2.x, v1.y + v2.y};
}

Vec operator*(const Vec v1, const double n)
{
	return {v1.x*n, v1.y*n};
}

Vec operator/(const Vec v1, const double n)
{
	return {v1.x/n, v1.y/n};
}

bool operator==(const Vec v1, const Vec v2)
{
	return (v1.x == v2.x && v1.y == v2.y);
}

bool operator!=(const Vec v1, const Vec v2)
{
	return (v1.x != v2.x || v1.y != v2.y);
}












class Organism;

struct Stimuli
{
	id_t organId;
	Vec offset;
	
	Stimuli() : organId(0), offset()
	{
		
	}
};

bool operator<(const Stimuli s1, const Stimuli s2)
{
	if (s1.organId == s2.organId)
	{
		if (s1.offset.x == s2.offset.x)
		{
			return (s1.offset.y < s2.offset.y);
		}
		return (s1.offset.x < s2.offset.x);
	}
	return (s1.organId < s2.organId);
}









class GridCell
{
	public:
	GridCell* left;
	GridCell* right;
	GridCell* up;
	GridCell* down;
	
	std::vector<std::shared_ptr<Organism>> occupants;
	
	GridCell() : left(NULL), right(NULL), up(NULL), down(NULL), occupants()
	{
		
	}
	
	std::vector<id_t> stimuli() const;
};


class Grid
{
	private:
	std::vector<std::vector<GridCell*>> cells;
	int w;
	int h;
	
	public:
	Grid(const int x, const int y) : cells(x), w(x), h(y)
	{
		if (x <= 0 || y <= 0)
		{
			//TODO
			throw std::exception();
		}
		
		for (int i = 0; i < w; i++)
		{
			auto& col = cells[i] = std::vector<GridCell*>(h);
			
			for (int j = 0; j < h; j++)
			{
				col[j] = new GridCell();
				
			}
		}
		
		for (int i = 0; i < w; i++)
		{
			auto& col = cells[i];
			auto& lcol = cells[(i+w-1)%w];
			auto& rcol = cells[(i+w+1)%w];
			for (int j = 0; j < h; j++)
			{
				col[j]->left = lcol[j];
				col[j]->right = rcol[j];
				col[j]->up = col[(j+h+1)%h];
				col[j]->down = col[(j+h-1)%h];
			}
		}
	}
	
	virtual ~Grid()
	{
		for (auto& col : cells)
		{
			for (auto& cell : col)
			{
				delete cell;
			}
			col.clear();
		}
		cells.clear();
	}
	
	GridCell* cell(int x, int y) const
	{
		
		x += w*(abs((int)x/w) + 1);
		
		y += h*(abs((int)y/h) + 1);
		
		return cells[x % w][y % h];
	}
	
	void clear()
	{
		for (auto& column : cells)
		{
			for (auto& cell : column)
			{
				cell->occupants.clear();
			}
		}
	}
	
};







struct Gene
{
	Stimuli stim;
	Vec response;
};

typedef std::map<Stimuli, Gene> Genotype_t;












class Organism
{
	//protected:
	public:
	long nourishment;
	long age;
	id_t _id;
	int _vision;
	long starveThreshold;
	
	Genotype_t genes;
	
	bool alive;
	std::vector<id_t> _eats;
	
	public:
	Organism(const id_t id, const int vision, const long ST, const Genotype_t genes, const std::vector<id_t> food) : nourishment(0), age(0), _id(id), _vision(vision), starveThreshold(ST), genes(genes), alive(true), _eats(food), id(_id), vision(_vision), pos()
	{
		
	}
	
	virtual std::string species() const = 0;
	
	const id_t& id;
	const int& vision;
	Vec pos;
	
	const Vec operator[](const int i) const
	{
		return at(i);
	}
	
	const Vec& at(const int i) const
	{
		if (i >= genes.size())
		{
			throw std::out_of_range("index is out of bounds in Organism::at(const int) const");
		}
		auto it = genes.begin();
		for (auto j = 0; j <= i; j++)
		{
			it++;
		}
		return const_cast<Organism*>(this)->genes[it->first].response;
	}
	
	Vec& operator[](const int i)
	{
		return at(i);
	}
	
	Vec& at(const int i)
	{
		if (i >= genes.size())
		{
			throw std::out_of_range("index is out of bounds in Organism::at(const int) const");
		}
		auto it = genes.begin();
		for (auto j = 0; j <= i; j++)
		{
			it++;
		}
		return genes[it->first].response;
	}
	
	int size() const
	{
		return genes.size();
	}
	
	virtual int speed() const = 0;
	
	virtual std::shared_ptr<Organism> clone() const = 0;
	
	virtual bool living() const
	{
		return alive;
	}
	
	virtual void kill()
	{
		alive = false;
	}
	
	bool eats(const id_t id) const
	{
		return (std::find(_eats.begin(), _eats.end(), id) != _eats.end());
	}
	
	Vec response(const Stimuli& stim) const
	{
		Vec r {0, 0};
		if (speed() == 0 || genes.size() == 0)
		{
			return r;
		}
		return const_cast<Organism*>(this)->genes[stim].response;
		
	}
	
	virtual bool starved() const
	{
		return (nourishment <= starveThreshold);
	}
	
	
	
	
	
	virtual Vec getResponses(const Grid* grid, const Vec pos) const
	{
		Vec res;
		Stimuli stim;
		for (int x = -vision; x <= vision; x++)
		{
			stim.offset.x = x;
			for (int y = -abs(vision - abs(x)); abs(x) + abs(y) <= vision; y++)
			{
				stim.offset.y = y;
				auto cell = grid->cell(pos.x + x, pos.y + y);
				for (auto occupant : cell->occupants)
				{
					stim.organId = occupant->id;
					res = res + response(stim);
				}
				stim.organId = 0;
				res = res + response(stim);
			}
		}
		
		return res.normalize().resolve(speed());
	}
	
};

class Foliage : public Organism
{
	protected:
	
	public:
	Foliage(const id_t id, const Genotype_t genes) : Organism(id, 0, -INT_MAX, genes, {})
	{
		
	}
	
	Foliage(const Genotype_t genes) : Foliage(1, genes)
	{
		
	}
	
	virtual std::string species() const override { return "Foliage"; }
	
	int speed() const override { return 0; }
	
	virtual std::shared_ptr<Organism> clone() const override
	{
		return std::dynamic_pointer_cast<Organism>(std::make_shared<Foliage>(id, this->genes));
	}
	
	virtual bool starved() const override
	{
		return false;
	}
};

class Herbivore : public Organism
{
	protected:
	
	
	public:
	Herbivore(const id_t id, const int vision, const long starveThresh, const Genotype_t genes) : Organism(id, vision, starveThresh, genes, {1})
	{
		
	}
	
	Herbivore(const int vision, const Genotype_t genes) : Herbivore(2, vision, -5, genes)
	{
		
	}
	
	virtual std::string species() const override { return "Herbivore"; }
	
	virtual int speed() const {
		return 2;
	};
	
	virtual std::shared_ptr<Organism> clone() const override
	{
		return std::dynamic_pointer_cast<Organism>(std::make_shared<Herbivore>(id, vision, starveThreshold, this->genes));
	}
	
};




class Carnivore : public Organism
{
	protected:
	
	public:
	Carnivore(const id_t id, const int vision, const long starveThresh, const Genotype_t genes) : Organism(id, vision, starveThresh, genes, {2})
	{
		
	}
	
	Carnivore(const int vision, const Genotype_t genes) : Carnivore(4, vision, -3, genes)
	{
		
	}
	
	virtual std::string species() const override { return "Carnivore"; }
	
	virtual int speed() const {
		return 4;
	};
	
	virtual std::shared_ptr<Organism> clone() const override
	{
		return std::dynamic_pointer_cast<Organism>(std::make_shared<Carnivore>(id, vision, starveThreshold, this->genes));
	}
	
};

























Vec randomVec()
{
	return (Vec {static_cast<double>((rand() % 11)-5), static_cast<double>((rand() % 11)-5)});
}


Genotype_t genotype(std::vector<id_t> ids, const int vision)
{
	Genotype_t gType;
	
	
	typename std::vector<id_t>::iterator it;
	
	for (int i = 0; i < ids.size() - 1; i++)
	{
		if ((it = std::find(ids.begin() + i+1, ids.end(), ids[i])) != ids.end())
		{
			ids.erase(it);
			i--;
		}
	}
	
	
	
	for (int x = -vision; x <= vision; x++)
	{
		for (int y = -abs(vision - abs(x)); abs(y) + abs(x) <= vision; y++)
		{
			for (auto id : ids)
			{
				Gene g;
				g.stim.organId = id;
				g.stim.offset.x = x;
				g.stim.offset.y = y;
				g.response = randomVec().normalize()*rand();
				gType[g.stim] = g;
				if (id == 1)
				{
					g.response.x = x;
					g.response.y = y;
					g.response = g.response.normalize()*(static_cast<double>(10000)/g.response.mag() + (rand() % 3));
					gType[g.stim] = g;
				}
				else
				{
					g.response.x = x;
					g.response.y = y;
					g.response = g.response.normalize()*1;
					gType[g.stim] = g;
				}
			}
		}
	}
	
	return gType;
}

std::vector<Vec> extractResponses(const Genotype_t genes)
{
	std::vector<Vec> v(genes.size());
	for (auto& geneP : genes)
	{
		auto& gene = geneP.second;
		v.push_back(gene.response);
	}
	return v;
}


























class EcoSystem
{
	private:
	public:
	Grid* grid;
	std::map<id_t, std::shared_ptr<Organism>> baseModel;
	std::map<id_t, int> startCounts;
	std::vector<std::shared_ptr<Organism>> entities;
	const int w;
	const int h;
	
	public:
	EcoSystem(const int w, const int h) : grid(new Grid(w, h)), entities(), w(w), h(h)
	{
		
	}
	
	virtual ~EcoSystem()
	{
		delete grid;
		grid = NULL;
	}
	
	
	
	
	void clear()
	{
		grid->clear();
		entities.clear();
	}
	
	
	void base(const int startCount, std::shared_ptr<Organism> ptr)
	{
		this->baseModel[ptr->id] = ptr;
		this->startCounts[ptr->id] = startCount;
	}
	
	void init()
	{
		for (auto species : this->baseModel)
		{
			auto count = this->startCounts[species.first];
			for (int i = 0; i < count; i++)
			{
				auto clone = species.second->clone();
				auto rx = rand() % w;
				
				auto ry = rand() % h;
				clone->pos.x = rx;
				clone->pos.y = ry;
				
				this->grid->cell(rx, ry)->occupants.push_back(clone);
				
				entities.push_back(clone);
			}
		}
	}
	
	
	
	
	
	
	void step(int steps = 1)
	{
		#define PRINT
		#ifdef PRINT
		#define p(x)  dout << x
		#else
		#define p(x)
		#endif
		std::vector<GridCell*> cells;
		while (steps-- > 0)
		{
			cells.clear();
			for (auto ent : entities)
			{
				auto cell = grid->cell(ent->pos.x, ent->pos.y);
				if (std::find(cells.begin(), cells.end(), cell) == cells.end())
				{
					cells.push_back(cell);
				}
			}
			
			for (int i = 0; i < cells.size(); i++)
			{
				auto cell = cells[i];
				std::random_shuffle(cell->occupants.begin(), cell->occupants.end());
				bool anyEaten = true;
				while (anyEaten)
				{
				anyEaten = false;
				for (auto occupant : cell->occupants)
				{
					if (!occupant->living())
					{
						continue;
					}
					
					for (int j = 0; j < cell->occupants.size(); j++)
					{
						if (cell->occupants[j] == occupant)
						{
							continue;
						}
						if (!cell->occupants[j]->living())
						{
							continue;
						}
						
						if (occupant->eats(cell->occupants[j]->id))
						{
							p(occupant->species() << " eats " << cell->occupants[j]->species() << "\n");
							occupant->nourishment++;
							cell->occupants[j]->kill();
							anyEaten = true;
							break;
						}
					}
				}
				}
			}
			
			for (auto cell : cells)
			{
				for (auto organism : cell->occupants)
				{
					if (!organism->living())
					{
						continue;
					}
					
					organism->nourishment--;
					organism->age++;
					if (organism->starved())
					{
						organism->kill();
						p(organism->species() << " starved\n");
					}
				}
			}
			std::map<std::shared_ptr<Organism>, Vec> responses;
			for (auto cell : cells)
			{
				bool anyLeft = false;
				for (auto org : cell->occupants)
				{
					if (org->living())
					{
						anyLeft = true;
						break;
					}
				}
				if (!anyLeft)
				{
					continue;
				}
				
				for (auto org : cell->occupants)
				{
					Vec response = org->getResponses(grid, org->pos);
					responses[org] = response;
				}
				
			}
			
			for (auto cell : cells)
			{
				cell->occupants.clear();
			}
			for (auto org : entities)
			{
				if (org->speed() > 0)
				{
				if (responses.count(org) > 0)
				{
					p(org->species() << " moves from " << org->pos << " to " << (org->pos + responses[org]) << "\n");
					org->pos = org->pos + responses[org];
					
				}
				}
				grid->cell(org->pos.x, org->pos.y)->occupants.push_back(org);
			}
			
			
		}
	}
	
	
	std::vector<std::shared_ptr<Organism>> living() const
	{
		std::vector<std::shared_ptr<Organism>> v;
		for (auto org : entities)
		{
			if (org->living())
			{
				v.push_back(org);
			}
		}
		return v;
	}
	
	
	const std::vector<std::shared_ptr<Organism>>& organisms() const
	{
		return entities;
	}
};















bool Test_GameOfLifeExtended()
{
	std::vector<id_t> ids {1, 2, 4};
	
	
	Grid* grid = new Grid(100, 100);
	grid->clear();
	
	
	delete grid;
	
	const int herbVis = 20;
	
	
	EcoSystem sys(10, 10);
	auto herbivore = std::make_shared<Herbivore>(herbVis, genotype(ids, herbVis));
	sys.base(20, herbivore);
	sys.base(200, std::make_shared<Foliage>(genotype(ids, 0)));
	sys.init();
	
	/*auto foliageC = [&]() -> int
	{
		int folCount = 0;
	for (auto org : sys.living())
	{
		if (org->species() == "Foliage")
		{
			folCount++;
		}
		
	}
	return folCount;
	};*/
	
	const int stepCount = 50;
	const int startCount = 2;
	
	auto herbivoreFitness = [&sys, stepCount, startCount, herbVis] (const auto& genes)
	{
		sys.clear();
		sys.base(startCount, std::make_shared<Herbivore>(herbVis, genes));
		sys.init();
		sys.step(stepCount);
		
		std::vector<std::shared_ptr<Herbivore>> herbivores;
		for (auto org : sys.organisms())
		{
			if (org->species() == "Herbivore")
			{
				herbivores.push_back(std::dynamic_pointer_cast<Herbivore>(org));
			}
		}
		
		double fitness = 0;
		for (auto herb : herbivores)
		{
			fitness += herb->age;
			fitness += herb->nourishment;
		}
		
		for (auto herb : herbivores)
		{
			dout << "\n\nFor herbivore at " << herb->pos << "\n";
			std::vector<std::shared_ptr<Organism>> close;
			for (auto ent : sys.organisms())
			{
				if (!ent->living())
				{
					continue;
				}
				if ((ent->pos - herb->pos).mag() <= 20)
				{
					close.push_back(ent);
				}
			}
			for (auto org : close)
			{
				dout << org->species() << " at " << org->pos << std::endl;
			}
		}
		
		
		return fitness;
	};
	
	auto best = -1;
	
	while (best <= 0)
	{
		auto randGenes = genotype(ids, herbVis);
		dout << (best = herbivoreFitness(randGenes)) << std::endl;
		dout << "\n\n____________\n\n";
	}
	
	/*const int popCount = 20;
	
	typedef QUtils::Genetic::NumericVectorSolution<Vec> Sol_t;
	
	auto pop = std::make_shared<QUtils::Genetic::ArrayPopulation<Sol_t>>([&] (auto s)
	{
		return herbivoreFitness(s.get());
	}, popCount);
	
	for (auto i = 0; i < popCount; i++)
	{
		auto genes = extractResponses(genotype(ids, 1));
		pop->at(i) = std::make_shared<Sol_t>(genes.size());
		for (int j = 0; j < genes.size(); j++)
		{
			pop->at(i)->at(j) = genes[j];
		}
	}
	
	QUtils::Genetic::CrossoverAlgorithm<Sol_t> alg(pop);
	alg.mutateOverride = [](auto& sol)
	{
		int index = rand() % sol.size();
		sol.at(index) = randomVec();
	};
	
	const int genCount = 100;
	for (int i = 0; i < genCount; i += 10)
	{
	alg.go(10);
	dout << "Generation " << i << "\n";
	}
	auto bestG = alg.best()->get();
	auto bestV = herbivoreFitness(bestG);
	dout << "\n\nBest: " << bestV << std::endl;*/
	
	
	return true;
}