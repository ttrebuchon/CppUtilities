
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
};