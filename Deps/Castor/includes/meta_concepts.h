#if !defined CASTOR_META_CONCEPTS_H
#define CASTOR_META_CONCEPTS_H 1

namespace castor
{
namespace meta
{
	template <class...>
	using void_t = void;
	
	
	template <class, class = void_t<>>
    struct SupportsInvoke : std::false_type {};
    
    template <class T>
    struct SupportsInvoke<T, void_t<decltype(std::declval<T>().operator()())>> : std::true_type {};
}
}


#endif