
//This is included within the Mesh<T> class
struct Face
{
	Vertex* vert;
	Edge* edge;
	
	Face() : vert(nullptr), edge(nullptr)
	{
		
	}
};