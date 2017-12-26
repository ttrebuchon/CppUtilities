#pragma once
#include <QUtils/GUID.h>
#include <memory>

namespace QUtils { namespace World {
	
	class World_t;
	
	class WorldObject : public std::enable_shared_from_this<WorldObject>
	{
		private:
		
		protected:
		World_t* world;
		GUID objID;
		WorldObject(World_t*, const GUID);
		WorldObject(World_t*);
		
		void registerObj();
		
		
		public:
		typedef std::shared_ptr<WorldObject> Ptr;
		
		virtual ~WorldObject() = default;
		
		inline const GUID& id() const
		{ return objID; }
		
		
		friend class World_t;
	};
	
	
	
	
	
	#define WORLD_OBJECT(X) \
	typedef std::shared_ptr<X> Ptr; \
	typedef std::shared_ptr<const X> CPtr; \
	template <class... Args> \
	inline static Ptr Create(Args... args) \
	{ \
		auto ptr = Ptr(new X(args...)); \
		ptr->registerObj(); \
		return ptr; \
	}
}
}