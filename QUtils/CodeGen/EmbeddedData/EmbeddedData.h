#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <tuple>

namespace QUtils::CodeGen
{
	namespace Internal
	{
		namespace Helpers
		{
			template <int Index, int Count, class... Items>
			struct WriteItems
			{
				static void call(std::ostream& os, const std::tuple<Items...>& items, const std::vector<std::string>& segments)
				{
					if (Index >= segments.size())
					{
						return;
					}
					os << segments[Index] << std::get<Index>(items);
					WriteItems<Index+1, Count, Items...>::call(os, items, segments);
				}
			};
				
			template <int N, class... Items>
			struct WriteItems<N, N, Items...>
			{
					
				static void call(std::ostream& os, const std::tuple<Items...>& items, const std::vector<std::string>& segments)
				{
						
				}
			};
			
			
			template <template <class...> class List, int Index, int Count, class... Items>
			struct ListWrite
			{
				static void call(std::stringstream& ss, const std::tuple<Items...>& items, List<std::string>& list)
				{
					ss.str("");
					ss << std::get<Index>(items);
					list.push_back(ss.str());
					ListWrite<List, Index+1, Count, Items...>::call(ss, items, list);
				}
			};
			
			template <template <class...> class List, int N, class... Items>
			struct ListWrite<List, N, N, Items...>
			{
				static void call(std::stringstream& ss, const std::tuple<Items...>& items, List<std::string>& list)
				{
					
				}
			};
		}
		
		
		
		
		
		
		
		class EmbeddedItem
		{
			public:
			virtual ~EmbeddedItem() {}
			
			virtual void embed(std::ostream&, const std::vector<std::string>&) const = 0;
			
			virtual std::vector<std::string> strings() const = 0;
			
		};
		
		template <class... Items>
		class EmbeddedGeneric : public EmbeddedItem
		{
			std::tuple<Items...> values;
			public:
			EmbeddedGeneric(Items... values) : values(values...)
			{
				
			}
			
			virtual ~EmbeddedGeneric() {}
			
			virtual void embed(std::ostream& os, const std::vector<std::string>& segments) const override
			{
				Helpers::WriteItems<0, sizeof...(Items), Items...>::call(os, values, segments);
			}
			
			virtual std::vector<std::string> strings() const override
			{
				std::vector<std::string> list;
				std::stringstream ss;
				
				Helpers::ListWrite<std::vector, 0, sizeof...(Items), Items...>::call(ss, values, list);
				return list;
			}
		};
	}
	
	
	
	
	
	class EmbeddedData
	{
		private:
		mutable std::string lastResult;
		mutable bool changed;
		
		protected:
		std::string _format;
		std::string _template;
		std::string _replaceSym;
		
		std::vector<Internal::EmbeddedItem*> data;
		
		public:
		EmbeddedData();
		EmbeddedData(const std::string _template);
		
		void setTemplate(const std::string);
		const std::string& getTemplate() const;
		
		void setFormat(const std::string);
		const std::string& getFormat() const;
		
		
		void setReplace(const std::string);
		const std::string& getReplace() const;
		
		
		void fileWrite(const std::string file) const;
		
		void write(std::ostream&) const;
		
		void generate() const;
		
		template <class Item>
		void addItem(Item item)
		{
			data.push_back(new Internal::EmbeddedGeneric<Item>(item));
		}
		
		
		
		
		
		
		//Aliases
		inline void setReplaceSymbol(const std::string x)
		{ setReplace(x); }
		inline const std::string& getReplaceSymbol() const
		{ return getReplace(); }
		inline void setSymbol(const std::string x)
		{ setReplace(x); }
		inline const std::string& getSymbol() const
		{ return getReplace(); }
		
		
		
		
	};
}