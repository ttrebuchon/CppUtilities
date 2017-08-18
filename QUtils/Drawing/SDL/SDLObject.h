#pragma once
#include <map>


namespace QUtils::Drawing::SDL::Internal
{
	template <class SDLType, class Type>
	class SDLObject
	{
		protected:
		static std::map<SDLType*, Type*> instantiated;
		
		SDLType* ptr;
		
		static void setInstance(SDLType* SDLPtr, Type* ptr)
		{
			instantiated[SDLPtr] = ptr;
		}
		
		public:
		SDLObject(SDLType* ptr) : ptr(ptr)
		{
		}
		
		virtual ~SDLObject()
		{
			if (ptr != NULL && instantiated.count(ptr) > 0)
			{
				instantiated.erase(ptr);
			}
		}
		
		
		static Type* getObject(SDLType* SDLPtr)
		{
			if (SDLPtr == NULL)
			{
				return NULL;
			}
			
			if (instantiated.count(SDLPtr) > 0)
			{
				return instantiated.at(SDLPtr);
			}
			else
			{
				auto obj = new Type(SDLPtr);
				instantiated[SDLPtr] = obj;
				return obj;
			}
		}
		
		SDLType* operator*()
		{
			return ptr;
		}
		
		const SDLType* operator*() const
		{
			return ptr;
		}
	};
	
	template <class SDLType, class Type>
	std::map<SDLType*, Type*> SDLObject<SDLType, Type>::instantiated;
}