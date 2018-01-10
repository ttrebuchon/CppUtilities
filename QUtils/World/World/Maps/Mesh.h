#pragma once

#include "../../Vector.h"
#include "../SharedPtrOnly.h"
#include <QUtils/Types/IntegerSequence.h>
#include <QUtils/Exception/NotImplemented.h>
#include <QUtils/Debug/dassert.h>

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
		
		template <class G, class T>
		struct Get_List
		{
			private:
			
			
			public:
			
			template <class Container>
			static void Go(Container cont, T& t)
			{
				for (auto& x : t)
				{
					cont.insert(x);
				}
			}
			
			static std::vector<G> Get(auto t)
			{
				return std::vector<G>(t.begin(), t.end());
			}
		};
		
		template <class Out, class T, class ...G>
		struct Get_List<Out, std::tuple<T, G...>>
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
		
		struct Face;
		struct Edge;
		
		struct Vertex
		{
			Vec_t pos;
			size_t index;
			Edge* edge;
			
			Vertex(const Vec_t pos, const size_t index) : pos(pos), index(index), edge(nullptr)
			{
				
			}
		};
		
		
		#include "Mesh/Face.h"
		#include "Mesh/Edge.h"
		
		
		
		//protected:
		std::map<Vec_t, Vertex*, Vec_Comparator> points;
		std::vector<Vertex*> vertices;
		std::vector<Edge*> edges;
		std::vector<Face*> faces;
		
		Mesh() : points(), vertices(), edges(), faces()
		{
			
		}
		
		
		Vertex* getPoint(const Vec_t pos)
		{
			if (points.count(pos) <= 0)
			{
				size_t index = vertices.size();
				vertices.push_back(points[pos] = new Vertex(pos, index));
				dassert(points.at(pos) != nullptr);
			}
			return points.at(pos);
		}
		
		void addFaces(const auto& ptFaces)
		{
			std::vector<std::vector<size_t>> vertFaces;
			std::set<size_t> vertexIndices;
			
			for (const auto& face : ptFaces)
			{
				std::vector<size_t> vFace;
				for (const auto& pt : face)
				{
					Vertex* vert = getPoint(pt);
					dassert(vert != nullptr);
					vFace.push_back(vert->index);
					vertexIndices.insert(vert->index);
				}
				
				vertFaces.push_back(vFace);
			}
			
			int eCount = 0;
			for (auto& f : vertFaces)
			{
				eCount += f.size();
			}
			std::vector<Edge*> edges(eCount);
			std::vector<Face*> faces;
			std::map<Vertex*, std::vector<Edge*>> outgoing;
			
			for (auto& e : edges)
			{
				e = new Edge;
			}
			
			int edgeIndex = 0;
			for (auto& face : vertFaces)
			{
				int i = 0;
				Face* f = new Face;
				for (auto& vIndex : face)
				{
					Edge* edge = edges[edgeIndex + i];
					
					edge->vert = vertices.at(vIndex);
					edge->vert->edge = edge;
					edge->face = f;
					f->edge = edge;
					outgoing[vertices.at(vIndex)].push_back(edge);
					if (i > 0)
					{
						edge->prev = edges[edgeIndex+i-1];
						edges[edgeIndex+i-1]->next = edge;
					}
					
					++i;
				}
				
				edges[edgeIndex]->prev = edges[edgeIndex+i-1];
				edges[edgeIndex+i-1]->next = edges[edgeIndex];
				
				faces.push_back(f);
				
				edgeIndex += i;
			}
			
			for (auto& e : edges)
			{
				this->edges.push_back(e);
			}
			
			for (auto& f : faces)
			{
				this->faces.push_back(f);
			}
			
			for (int i = 0; i < this->edges.size(); ++i)
			{
				if (this->edges[i]->sym == nullptr)
				{
					Edge* e = this->edges[i];
					Vertex* v = e->next->vert;
					for (auto& out : outgoing.at(v))
					{
						if (out->next->vert == e->vert)
						{
							e->sym = out;
							dassert(out->sym == nullptr || out->sym == e);
							out->sym = e;
							break;
						}
					}
					
				}
				
			}
		}
		
		void splitEdge(Edge* e, const Vec_t pos)
		{
			Edge* eNew = new Edge;
			eNew->sym = e->sym;
			
			
			size_t index = vertices.size();
			Vertex* vNew = new Vertex(pos, index);
			vertices.push_back(vNew);
			dassert(points.count(pos) <= 0);
			points[pos] = vNew;
			
			
			eNew->vert = vNew;
			vNew->edge = eNew;
			eNew->face = e->face;
			
			
			eNew->prev = e;
			eNew->next = e->next;
			
			
			e->next->prev = eNew;
			e->next = eNew;
			
			edges.push_back(eNew);
			
			
			
			if (e->sym != nullptr)
			{
				Edge* symNew = new Edge;
				symNew->sym = e;
				symNew->vert = vNew;
				symNew->face = e->sym->face;
				symNew->prev = e->sym;
				symNew->next = e->sym->next;
				e->sym->next->prev = symNew;
				e->sym->next = symNew;
				e->sym->sym = eNew;
				e->sym = symNew;
				
				edges.push_back(symNew);
			}
		}
		
		void triangulate(Face* face)
		{
			dassert(face != nullptr);
			while (true)
			{
				Edge* e[4];
				e[0] = face->edge;
				dassert(e[0] != nullptr);
				e[1] = e[0]->next;
				dassert(e[1] != nullptr);
				e[2] = e[1]->next;
				dassert(e[2] != nullptr);
				e[3] = e[2]->next;
				dassert(e[3] != nullptr);
				
				if (e[0] == e[3])
				{
					break;
				}
				
				Vertex *v1, *v3;
				v1 = e[1]->vert;
				v3 = e[3]->vert;
				
				Edge* eNew = new Edge;
				Edge* symNew = new Edge;
				Face* fNew = new Face;
				
				eNew->face = face;
				eNew->vert = v1;
				eNew->prev = e[0];
				eNew->next = e[3];
				eNew->sym = symNew;
				
				symNew->vert = v3;
				symNew->face = fNew;
				symNew->prev = e[2];
				symNew->next = e[1];
				symNew->sym = eNew;
				
				fNew->edge = e[1];
				e[1]->prev = e[2]->next = symNew;
				e[3]->prev = e[0]->next = eNew;
				e[1]->face = e[2]->face = fNew;
				face->edge = eNew;
				
				edges.push_back(eNew);
				edges.push_back(symNew);
				faces.push_back(fNew);
			}
		}
		
		public:
		
		
		virtual ~Mesh()
		{
			for (auto vert : vertices)
			{
				delete vert;
			}
			
			for (auto face : faces)
			{
				delete face;
			}
			
			for (auto edge : edges)
			{
				delete edge;
			}
		}
		
		static Ptr FromPoints(const auto& faces)
		{
			Ptr mesh = Create();
			
			if (faces.begin() == faces.end())
			{
				return mesh;
			}
			
			
			std::vector<std::vector<Vec_t>> converted;
			for (auto& face : faces)
			{
				converted.push_back(Mesh_Helpers::Get_List<Vec_t, std::vector<Vec_t>>::Get(face));
			}
			
			mesh->addFaces(converted);
			
			return mesh;
		}
		
		template <class ...Vecs>
		void faceFromPoints(const std::tuple<Vecs...>& face)
		{
			typedef typename QUtils::Types::SequenceGen<sizeof...(Vecs)-1>::type Sequence;
			typedef Mesh_Helpers::Tuple_To_Init_List<Sequence> Type;
			faceFromPoints(Type::go(face));
		}
		
		void faceFromPoints(const std::vector<Vec_t>&)
		{
			
		}
		
	};
	
}
}
}