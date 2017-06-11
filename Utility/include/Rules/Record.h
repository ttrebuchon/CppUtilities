#pragma once
#include <tuple>
#include <vector>
#include <castor.h>
#include <functional>
#include <Tuple/Tuple.h>

namespace Util
{
namespace Rules
{
	namespace Helpers
	{
		
		//Takes 2 tuples, t1<A, B, C, ...> and t2<A2, B2, C2 ...>, and returns a tuple<F(A, A2), F(B, B2), F(C, C2), ...>
		template <int N, typename F, typename T, typename ...G>
		struct TupZip
		{
			template <typename T2, typename ...G2>
			static auto call(F f, Tuple<T, G...> t1, Tuple<T2, G2...> t2)
			{
				auto fR = f(t1.template get<0>(), t2.template get<0>());
				return TupZip<N-1, F, G...>::template call<G2...>(f, t1.template takeBack<N-1>(), t2.template takeBack<N-1>()).prepend(fR);
			}
		};
		
		template <typename F, typename T, typename ...G>
		struct TupZip<1, F, T, G...>
		{
			template <typename T2, typename ...G2>
			static auto call(F f, Tuple<T, G...> t1, Tuple<T2, G2...> t2)
			{
				auto fR = f(t1.template get<0>(), t2.template get<0>());
				return Make_Tuple(std::make_tuple(fR));
			}
		};
		
		
		
		
		struct TupAnd
		{
			template <typename T, typename ...G>
			static auto call(Tuple<T, G...> t)
			{
				
				return (t.template get<0>()) && TupAnd::call<G...>(t.template takeBack<sizeof...(G)>());
			}
			
			template <typename T>
			static auto call(std::tuple<T> t)
			{
				
				return std::get<0>(t);
			}
		};
		
		
		struct TupForEach
		{
			template <typename F, typename T, typename ...G>
			static void call(F& f, Tuple<T, G...> t)
			{
				
				f(t.template get<0>());
				call<F, G...>(f, (t.template takeBack<sizeof...(G)>()));
			}
			
			template <typename F, typename T>
			static void call(F& f, Tuple<T> t)
			{
				f(t.template get<0>());
			}
		
		
		};
		
		class RelWrapper
		{
			castor::relation* ptr;
			
			public:
			
			
			RelWrapper(castor::relation r) : ptr(new castor::relation(r))
			{}
			
			RelWrapper(const RelWrapper& r) : ptr(r.ptr)
			{}
			
			RelWrapper(const RelWrapper&& r) : ptr(r.ptr)
			{}
			
			auto& get() { return *ptr; }
			//RelWrapper& operator
		};
		
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	class Engine;
	
	template <typename T, typename ...G>
	class Record
	{
		public:
		typedef std::function<castor::relation(castor::lref<T>, castor::lref<G>...)> Result;
		
		typedef std::function<castor::relation(const Engine*, castor::lref<T>, castor::lref<G>...)> Rule;
		
		private:
		
		
		
		
		std::vector<std::tuple<T, G...>> facts;
		bool changed = true;
		
		
		Result record;
		Rule rule;
		
		public:
		Record() : facts(), record(), rule()
		{
			
		}
		
		void add(const T t, const G... g)
		{
			facts.push_back(std::make_tuple(t, g...));
			changed = true;
		}
		
		Result get(const Engine* eng)
		{
			if (!changed)
			{
				return record;
			}
			
			auto eqR = [](auto& x, auto& y) -> Helpers::RelWrapper//castor::relation
			{
				return Helpers::RelWrapper(castor::eq(x, y));
			};
			
			
			
			Result f = Result([=] (castor::lref<T> t, castor::lref<G>... g) -> castor::relation
			{
				castor::Disjunctions dis;
				
				for (auto v : facts)
				{
					castor::Conjunctions con;
					
					
					auto conTup = Helpers::TupZip<sizeof...(G)+1, decltype(eqR), T, G...>::call(eqR, v, Make_Tuple(std::make_tuple(t, g...)));
					
					
					
					auto conjAdd = [&] (auto& a) {
						con.push_back(a.get());
					};
					
					Helpers::TupForEach::call(conjAdd, conTup);
					
					
					
					
					
					//auto anded = Helpers::TupAnd::call(conTup);
					
					//con.push_back(eqR(std::get<0>(v), t));
					dis.push_back(con);
				}
				if (rule)
				{
					return dis || rule(eng, t, g...);
				}
				else
				{
					return dis;
				}
			});
			record = f;
			changed = false;
			return record;
		}
		
		void setRule(const Rule r)
		{
			this->rule = r;
			this->changed = true;
		}
	};
	
}
}