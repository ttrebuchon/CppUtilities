#pragma once

#include "../../Vector.h"
#include "../SharedPtrOnly.h"
#include <QUtils/Types/IntegerSequence.h>
#include <QUtils/Exception/NotImplemented.h>
#include <QUtils/Debug/dassert.h>
#include <QUtils/NearestNeighborTree/NearestNeighborTree.h>
#include <unordered_set>

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
		
		template <class T>
		struct List_It_Compare
		{
			typedef typename std::list<T>::iterator it;
			int operator()(const it& i1, const it& i2) const
			{
				throw NotImp();
				return std::distance(i1, i2);
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
		std::map<size_t, Vertex*> vertexIndices;
		std::list<Vertex*> vertices;
		std::list<Edge*> edges;
		std::list<Face*> faces;
		std::shared_ptr<QUtils::NearestNeighbor<Vertex, T, T, T>> tree;
		
		Mesh() : points(),
		vertexIndices(),
		vertices(),
		edges(),
		faces(), tree(std::make_shared<NearestNeighbor<Vertex, T, T, T>>(
		[](auto v){return v->pos.x;},
		[](auto v){return v->pos.y;},
		[](auto v){return v->pos.z;}
		))
		{
			tree->dist =
				[](Vertex* v1, Vertex* v2)
				{
					return (v1->pos - v2->pos).value();
				};
			
			
		}
		
		
		Vertex* getPoint(const Vec_t pos)
		{
			if (points.count(pos) <= 0)
			{
				size_t index = vertices.size();
				Vertex* newV = new Vertex(pos, index);
				points[pos] = newV;
				vertices.push_back(newV);
				vertexIndices[index] = newV;
				tree->insert(newV);
				dassert(points.at(pos) != nullptr);
				dassert(tree->size() == vertices.size());
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
					
					edge->vert = this->vertexIndices.at(vIndex);
					edge->vert->edge = edge;
					edge->face = f;
					f->edge = edge;
					outgoing[edge->vert].push_back(edge);
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
			
			for (auto it = this->edges.begin(); it != this->edges.end(); ++it)
			{
				if ((*it)->sym == nullptr)
				{
					Edge* e = *it;
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
			if (points.count(pos) > 0)
			{
				//TODO
				throw std::exception();
			}
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
			Edge* e[4];
			while (true)
			{
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
		
		void triangulate()
		{
			auto end = faces.end();
			for (auto it = faces.begin(); it != end; ++it)
			{
				triangulate(*it);
			}
		}
		
		void mergeLines()
		{
			typedef typename std::list<Face*>::iterator fIt;
			std::list<fIt> fDel;
			std::set<Edge*> eDelElem;
			
			Edge *e1, *e2, *e3;
			Edge *s1, *s2, *s3;
			Vec_t v1, v2, cr;
			for (auto it = faces.begin(); it != faces.end(); ++it)
			{
				auto& face = *it;
				
				e1 = face->edge;
				e2 = e1->next;
				e3 = e2->next;
				
				if (e3->next != e1 || e1 == e3 || e1 == e2 || e2 == e3)
				{
					continue;
				}
				
				v1 = e2->vert->pos - e1->vert->pos;
				v2 = e3->vert->pos - e2->vert->pos;
				cr = v2.cross(v1);
				if (cr.value() > 0)
				{
					continue;
				}
				s1 = e1->sym;
				s2 = e2->sym;
				s3 = e3->sym;
				
				if (s1 != nullptr)
				{
					dassert(s1->sym == e1);
					s1->sym = nullptr;
				}
				if (s2 != nullptr)
				{
					dassert(s2->sym == e2);
					s2->sym = nullptr;
				}
				if (s3 != nullptr)
				{
					dassert(s3->sym == e3);
					s3->sym = nullptr;
				}
				
				fDel.push_back(it);
				eDelElem.insert(e1);
				eDelElem.insert(e2);
				eDelElem.insert(e3);
				
				if (e1->vert->edge == e1)
				{
					e1->vert->edge = nullptr;
				}
				
				if (e2->vert->edge == e2)
				{
					e2->vert->edge = nullptr;
				}
				
				if (e3->vert->edge == e3)
				{
					e3->vert->edge = nullptr;
				}
			}
			
			
			
			for (auto faceIt : fDel)
			{
				delete *faceIt;
				faces.erase(faceIt);
			}
			
			e1 = nullptr;
			for (auto it = edges.begin(); it != edges.end();)
			{
				e1 = *it;
				if (eDelElem.count(e1) <= 0)
				{
					if (e1->vert->edge == nullptr)
					{
						e1->vert->edge = e1;
					}
					++it;
				}
				else
				{
					delete e1;
					it = edges.erase(it);
				}
			}
			
			//Uncomment to delete unedged vertices
			/*for (auto it = vertices.begin(); it != vertices.end();)
			{
				if ((*it)->edge != nullptr)
				{
					++it;
				}
				else
				{
					points.erase((*it)->pos);
					vertexIndices.erase((*it)->index);
					delete *it;
					it = vertices.erase(it);
				}
			}*/
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
			throw NotImp();
		}
		
		void calculateNormals()
		{
			for (auto& face : faces)
			{
				face->calcNorm();
			}
		}
		
		Face* closestFace(const Vec_t point, Vec_t* closest = nullptr) const
		{
			if (faces.size() == 0)
			{
				return nullptr;
			}
			
			Face* closestF = nullptr;
			Vertex dummy(point, 0);
			auto results = tree->traverse(&dummy, 1);
			closestF = results.front()->edge->face;
			
			Vec_t intersect = point - ((point - results.front()->pos).dot(closestF->norm()))*closestF->norm();
			if (results.front()->edge->sym != nullptr)
			{
				auto e = results.front()->edge->sym;
				Vec_t intersect2 = point - ((point - e->vert->pos).dot(e->face->norm()))*e->face->norm();
				if ((intersect2 - point).value() < (intersect - point).value())
				{
					intersect = intersect2;
					closestF = e->face;
				}
			}
			
			if (closest != nullptr)
			{
				*closest = intersect;
			}
			
			return closestF;
		}
		
		void splitEdges()
		{
			int j = 0;
			auto len = edges.size();
			for (auto it = edges.begin(); it != edges.end() && j < len; ++it, ++j)
			{
				auto pos = ((*it)->vert->pos + (*it)->next->vert->pos)/2;
				if (points.count(pos) == 0)
				{
					splitEdge(*it, pos);
				}
			}
		}
		
	};
	
	
	template <class T>
	void Mesh<T>::Face::calcNorm() const
	{
		Vec_t n{0,0,0};
		
		Edge *start, *e;
		e = start = this->edge;
		
		do
		{
			const Vec_t& pos = e->vert->pos;
			const Vec_t& pnext = e->next->vert->pos;
			
			n.x += (pos.y - pnext.y)*(pos.z + pnext.z);
			n.y += (pos.z - pnext.z)*(pos.x + pnext.x);
			n.z += (pos.x - pnext.x)*(pos.y + pnext.y);
			e = e->next;
			
		}
		while (e != start);
		
		_norm = n.unit();
	}
	
	template <class T>
	T Mesh<T>::Face::area() const
	{
		Vec_t A, B, C;
		T a, b, c;
		
		A = edge->vert->pos;
		B = edge->next->vert->pos;
		C = edge->next->next->vert->pos;
		
		a = (A - B).value();
		b = (A - C).value();
		c = (B - C).value();
		
		assert_ex(a != 0);
		assert_ex(b != 0);
		assert_ex(c != 0);
		
		
		return std::sqrt((a+b+c)*(b+c-a)*(a+c-b)*(a+b-c))/4;
		
	}
	
}
}
}