#pragma once
#include "Mesh.h"
#include "../Map.h"
#include "../SharedPtrOnly.h"

namespace QUtils { namespace World {
namespace Maps {
	
	template <class T>
	class MeshMap : public Map<T>
	{
		protected:
		//DEBUG
		public:
		typename Mesh<T>::Ptr mesh;
		
		MeshMap(typename Mesh<T>::Ptr m) : mesh(m)
		{
			
		}
		
		public:
		SHARED_PTR_ONLY(MeshMap)
		
		
	};
}
}
}