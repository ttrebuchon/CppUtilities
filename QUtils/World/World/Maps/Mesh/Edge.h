
//This is included within the Mesh<T> class
struct Edge
{
	Vertex* vert;
	Face* face;
	Edge* prev;
	Edge* next;
	Edge* sym;
	
	Edge() : vert(nullptr), face(nullptr), prev(nullptr), next(nullptr), sym(nullptr)
	{
		
	}
};