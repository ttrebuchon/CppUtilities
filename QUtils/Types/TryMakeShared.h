#pragma once
#include "Void_t.h"
#include "TypeSequence.h"

namespace QUtils { namespace Types {
	
	namespace TryMakeShared_Helpers
	{
		template <class Type, class... Args>
		struct ConSharedCall_t
		{
			
		};
		
		template <class Type, class... Args>
		struct ConSharedCall_t<Type, TypeSequence<Args...>>
		{
			typedef decltype(std::shared_ptr<Type>(new Type(std::declval<Args>()...))) type;
			
			inline static auto call(Args... args)
			{
				return std::shared_ptr<Type>(new Type(args...));
			}
		};
		
		template <class Type, class Args, class = void>
		struct AbleToConShared
		{
			constexpr static bool value = false;
		};
		
		template <class Type, class Args>
		struct AbleToConShared<Type, Args, void_t<typename ConSharedCall_t<Type, Args>::type>>
		{
			constexpr static bool value = true;
			
			inline static std::shared_ptr<Type> call(auto... args)
			{
				return ConSharedCall_t<Type, Args>::call(args...);
			}
		};
		
		
		
		
		
		
		template <class Type, class... Args>
		struct MakeSharedCall_t
		{
			
		};
		
		template <class Type, class... Args>
		struct MakeSharedCall_t<Type, TypeSequence<Args...>>
		{
			typedef decltype(std::make_shared<Type>(std::declval<Args>()...)) type;
			
			inline static auto call(Args... args)
			{
				return std::make_shared<Type>(args...);
			}
		};
		
		template <class Type, class Args, class = void>
		struct AbleToMakeShared : public AbleToConShared<Type, Args>
		{
			//constexpr static bool value = false;
		};
		
		template <class Type, class Args>
		struct AbleToMakeShared<Type, Args, void_t<typename MakeSharedCall_t<Type, Args>::type>>
		{
			constexpr static bool value = true;
			
			inline static std::shared_ptr<Type> call(auto... args)
			{
				return MakeSharedCall_t<Type, Args>::call(args...);
			}
		};
		
	}
	
	template <class Type, class... Args>
	using TryMakeShared = TryMakeShared_Helpers::AbleToMakeShared<Type, TypeSequence<Args...>>;
}
}