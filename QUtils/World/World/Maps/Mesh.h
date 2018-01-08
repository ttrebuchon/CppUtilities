#pragma once

#include "../../Vector.h"
#include "../SharedPtrOnly.h"
#include <QUtils/Types/IntegerSequence.h>
#include <QUtils/Exception/NotImplemented.h>

namespace QUtils { namespace World {
namespace Maps {
	
	namespace Mesh_Helpers
	{
		template <class>
		struct Tuple_To_Init_List;
		
		
		template <int... Indexes>
		struct Tuple_To_Init_List<QUtils::Types::Sequence<Indexes...>>
		{
			template <class T, class... G>
			static std::vector<T> go(const std::tuple<T, G...>& tup)
			{
				return {std::get<Indexes>(tup)...};
			}
		};
		
		template <class T>
		struct Get_List
		{
			private:
			
			typedef typename std::remove_reference<decltype(*std::declval<T>().begin())>::type G;
			
			public:
			
			template <class Container>
			static void Go(Container cont, T& t)
			{
				for (auto& x : t)
				{
					cont.insert(x);
				}
			}
			
			static std::vector<G> Get(T t)
			{
				return std::vector<G>(t.begin(), t.end());
			}
		};
		
		template <class T, class ...G>
		struct Get_List<std::tuple<T, G...>>
		{
			private:
			typedef typename QUtils::Types::SequenceGen<sizeof...(G)>::type Sequence;
			
			public:
			
			template <class Container>
			static void Go(Container cont, std::tuple<T, G...>& t)
			{
				for (auto& x : Tuple_To_Init_List<Sequence>::go(t))
				{
					cont.insert(x);
				}
			}
			
			static auto Get(T& t)
			{
				return Tuple_To_Init_List<typename QUtils::Types::SequenceGen<sizeof...(G)>::type>::go(t);
			}
		};
	}
	
	template <class T>
	class Mesh
	{
		private:
		struct Vec_Comparator
		{
			bool operator()(const Vector<T>& v1, const Vector<T>& v2) const
			{
				if (v1.x < v2.x)
				{
					return true;
				}
				else if (v1.x == v2.x)
				{
					if (v1.y < v2.y)
					{
						return true;
					}
					else if (v1.y == v2.y)
					{
						if (v1.z < v2.z)
						{
							return true;
						}
					}
				}
				
				
				return false;
			}
		};
		
		
		
		public:
		SHARED_PTR_ONLY(Mesh)
		typedef Vector<T> Vec_t;
		
		struct Edge;
		struct Face;
		struct Vertex;
		
		
		struct Vertex
		{
			std::set<Edge*> edges;
			Vec_t pos;
			
			bool connected(const Vertex* end) const;
		};
		
		
		struct Edge
		{
			private:
			size_t index;
			Edge* next;
			
			Edge(Vertex* vStart, Vertex* vEnd) : index(), next(nullptr), start(vStart), dest(vEnd), edges{nullptr, nullptr, nullptr, nullptr}, face(nullptr)
			{
				
			}
			
			Edge() : Edge(nullptr, nullptr)
			{
				
			}
			
			~Edge();
			
			public:
			Vertex *start, *dest;
			Edge* edges[4];
			Face *face;
			
			
			static Edge* Create()
			{
				auto ptr = new Edge[4];
				for (int i = 0; i < 4; ++i)
				{
					ptr[i].index = i;
				}
				
				ptr[0].next = ptr+0;
				ptr[1].next = ptr+3;
				ptr[2].next = ptr+2;
				ptr[3].next = ptr+1;
				
				return ptr;
			}
			
			
			
			Edge* rot() const;
			Edge* invRot() const;
			Edge* sym() const;
			Edge* sNext() const
			{
				return next;
			}
			Edge* sPrev() const
			{
				return rot()->sNext()->rot();
			}
			Edge* dNext() const
			{
				return sym()->sNext()->sym();
			}
			Edge* dPrev() const
			{
				return invRot()->sNext()->invRot();
			}
			
			Edge* lNext() const
			{
				return invRot()->sNext()->rot();
			}
			
			Edge* lPrev() const
			{
				return sNext()->sym();
			}
			
			Edge* rNext() const
			{
				return rot()->sNext()->invRot();
			}
			
			Edge* rPrev() const
			{
				return sym()->sNext();
			}
			
			Edge* left() const
			{
				return rot()->face;
			}
			
			Edge* right() const
			{
				return invRot()->face;
			}
			
			static void splice(Edge* a, Edge* b)
			{
				Edge* alpha = a->sNext()->rot();
				Edge* beta = b->sNext()->rot();
				
				Edge* t1 = b->sNext();
				Edge* t2 = a->sNext();
				Edge* t3 = beta->sNext();
				Edge* t4 = alpha->sNext();
				
				a->next = t1;
				b->next = t2;
				alpha->next = t3;
				beta->next = t4;
			}
			
			void setStart(Vertex* s)
			{
				start = s;
				s->addEdge(this);
			}
			
			void setDest(Vertex* s)
			{
				sym()->start = s;
				s->addEdge(sym());
			}
			
			void setLeft(Face* f)
			{
				rot()->face = f;
				f->addEdge(this);
			}
			
			void setRight(Face* f)
			{
				invRot()->face = f;
				f->addEdge(sym());
			}
		};
		
		
		
		
		
		
		
		
		//protected:
		std::map<Vec_t, Vertex*, Vec_Comparator> vertices;
		std::vector<Face*> faces;
		
		Mesh() : vertices(), faces()
		{
			
		}
		
		
		
		public:
		
		
		virtual ~Mesh()
		{
			for (auto& v : vertices)
			{
				delete v.second;
			}
			vertices.clear();
		}
		
		static Ptr FromPoints(const auto& faces)
		{
			Ptr mesh = Create();
			
			if (faces.begin() == faces.end())
			{
				return mesh;
			}
			
			std::vector<std::vector<Vec_t>> vecFaces;
			
			for (auto& face : faces)
			{
				std::vector<Vec_t> conv = Mesh_Helpers::Get_List<std::vector<Vec_t>>::Get(face);
				vecFaces.emplace_back(conv.begin(), conv.end());
				
			}
			
			
			
			
			
			
			for (auto& face : faces)
			{
				mesh->faceFromPoints(face);
			}
			
			return mesh;
		}
		
		template <class ...Vecs>
		Face* faceFromPoints(const std::tuple<Vecs...>& face)
		{
			typedef typename QUtils::Types::SequenceGen<sizeof...(Vecs)-1>::type Sequence;
			typedef Mesh_Helpers::Tuple_To_Init_List<Sequence> Type;
			return faceFromPoints(Type::go(face));
		}
		
		Face* faceFromPoints(const auto& face)
		{
			if (face.begin() == face.end())
			{
				return nullptr;
			}
			
			struct TVert;
			struct TFace;
			
			struct TSector
			{
				TVert* p;
				TFace* f;
				TVert* q;
			};
			
			typedef std::vector<TSector*> Arc;
			
			struct TVert
			{
				Vec_t pos;
				std::vector<Arc*> arcs;
				Vertex* vertex;
				bool done = false;
			};
			
			struct TFace
			{
				std::vector<TVert*> arcs;
				Face* finished;
				
				void addArcs(decltype(face)& verts, std::map<Vec_t, Vertex*, Vec_Comparator>& vertices)
				{
					for (auto p : verts)
					{
						arcs.push_back(new TVert{p});
						if (vertices.count(p) > 0)
						{
							//arcs.back()->vertex = vertices.at(p);
						}
					}
					
					
					auto w = arcs.begin();
					auto v = w++;
					auto u = v;
					for (auto it = arcs.begin(); it != arcs.end(); ++it)
					{
						u = it;
					}
					
					for (; w != arcs.end(); u = v, v = w, ++w)
					{
						this->merge_arc(*v, *w, *u);
					}
					this->merge_arc(*v, *arcs.begin(), *u);
				}
				
				void merge_arc(TVert* v, TVert* p, TVert* q)
				{
					Arc* bef = nullptr;
					Arc* aft = nullptr;
					TSector* sector = new TSector{p, this, q};
					
					for (auto a : v->arcs)
					{
						if (a->back()->q == p)
						{
							bef = a;
						}
						
						if (a->back()->p == q)
						{
							aft = a;
						}
					}
					
					if (bef)
					{
						if (aft)
						{
							bef->push_back(sector);
							if (bef == aft)
							{
								v->done = true;
								return;
							}
							v->arcs.erase(std::find(v->arcs.begin(), v->arcs.end(), aft));
							for (auto& x : *aft)
							{
								bef->push_back(x);
							}
						}
						else
						{
							bef->push_back(sector);
						}
					}
					else
					{
						if (aft)
						{
							aft->insert(aft->begin(), sector);
						}
						else
						{
							Arc* arc = new Arc;
							arc->push_back(sector);
							v->arcs.push_back(arc);
						}
					}
				}
				
				Face* makeFace(Mesh* m)
				{
					TFace* x = arcs.front()->arcs.front()->front()->f;
					assert(x != nullptr);
					throw NotImp();
				}
			};
			
			TFace* tface = new TFace;
			tface->addArcs(face, this->vertices);
			
			Face* f = tface->makeFace(this);
			
			delete tface;
			return f;
			
			/*int count = -1;
			
			std::vector<Vertex*> vertices;
			for (auto& point : face)
			{
				if (this->vertices.count(point) <= 0)
				{
					this->vertices[point] = new Vertex{{},point};
					vertices.push_back(this->vertices[point]);
				}
				else if (std::find(vertices.begin(), vertices.end(), this->vertices.at(point)) == vertices.end())
				{
					vertices.push_back(this->vertices[point]);
				}
				++count;
			}
			{
			int n = 0;
			auto it = face.begin();
			Vec_t first = *it;
			Vec_t last;
			while (it != face.end())
			{
				last = *it;
				++n;
				++it;
			}
			
			if (first != last)
			{
				++count;
			}
			}
			
			std::vector<Edge*> edges(count);
			{
				int i = 0;
				Vertex * last = nullptr;
				Vertex* current;
				Vertex* first = nullptr;
				for (auto& p : face)
				{
					current = this->vertices.at(p);
					if (i != 0)
					{
						Edge* e = edges[i-1] = new Edge(last, current);
						last->edges.insert(e);
					}
					else
					{
						first = current;
					}
					
					last = current;
					++i;
				}
				edges[i-1] = new Edge(last, first);
			}
			
			//int faceCount = 2 + edges.size() - vertices.size();
			
			std::map<Vertex*, std::set<Edge*>> edgeOuts;
			for (auto e : edges)
			{
				edgeOuts[e->start].insert(e);
			}
			
			*/
			
			//TODO
			throw NotImp();
		}
		
	};
	
	template <class T>
	inline bool Mesh<T>::Vertex::connected(const Vertex* v2) const
	{
		for (const auto& e : edges)
		{
			if ((e->start == this && e->dest == v2) || (e->dest == this && e->start == v2))
			{
				return true;
			}
		}
		return false;
	}
	
}
}
}