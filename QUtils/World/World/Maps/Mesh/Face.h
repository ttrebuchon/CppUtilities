
//This is included within the Mesh<T> class
struct Face
{
	private:
	mutable bool normSet = false;
	mutable Vec_t _norm;
	
	public:
	Vertex* vert;
	Edge* edge;
	
	
	Face() : vert(nullptr), edge(nullptr)
	{
		
	}
	
	void calcNorm() const;
	
	const Vec_t& norm() const
	{
		if (!normSet)
		{
			calcNorm();
		}
		return _norm;
	}
	
	T area() const;
	
	std::vector<Vertex*> vertices() const
	{
		std::vector<Vertex*> v;
		v.reserve(3);
		Edge* e = edge;
		do
		{
			v.push_back(e->vert);
			e = e->next;
		}
		while (e != edge);
		return v;
	}
	
	long perimeterSize() const
	{
		if (edge == nullptr)
		{
			return -1;
		}
		long p = 0;
		Edge* e = edge;
		do
		{
			++p;
			e = e->next;
		}
		while (e != edge);
		return p;
	}
};