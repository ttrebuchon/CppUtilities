#pragma once
#include <tuple>
#include <list>


namespace QUtils { namespace Spatial {
	
	template <class T, class N>
	class SpatialTree
	{
		private:
		
		protected:
		
		public:
		
		class Node
		{
			public:
			const int index ;
			const int nextIndex = (index + 1) % 3;
			constexpr static int nCount = 4;
			
			
			protected:
			
			void split()
			{
				nodes = new Node*[nCount];
				for (int i = 0; i < nCount; ++i)
				{
					nodes[i] = new Node(nextIndex);
				}
				
				N width = std::get<0>(endDims) - std::get<0>(startDims);
				N height = std::get<1>(endDims) - std::get<1>(startDims);
				
				
				N sWidth = (std::get<0>(endDims) - std::get<0>(startDims))/2;
				N sHeight = (std::get<1>(endDims) - std::get<1>(startDims))/2;
				
				
				N x = std::get<0>(startDims);
				N y = std::get<1>(startDims);
				
				
				
				
				
				std::get<0>(nodes[0]->startDims) = x + sWidth;
				std::get<0>(nodes[0]->endDims) = x + width;
				std::get<1>(nodes[0]->startDims) = y + sHeight;
				std::get<1>(nodes[0]->endDims) = y + height;
				
				
				
				
				std::get<0>(nodes[1]->startDims) = x;
				std::get<0>(nodes[1]->endDims) = x + sWidth;
				std::get<1>(nodes[1]->startDims) = y + sHeight;
				std::get<1>(nodes[1]->endDims) = y + height;
				
				
				std::get<0>(nodes[2]->startDims) = x;
				std::get<0>(nodes[2]->endDims) = x + sWidth;
				std::get<1>(nodes[2]->startDims) = y;
				std::get<1>(nodes[2]->endDims) = y + sHeight;
				
				
				
				std::get<0>(nodes[3]->startDims) = x + sWidth;
				std::get<0>(nodes[3]->endDims) = x + width;
				std::get<1>(nodes[3]->startDims) = y;
				std::get<1>(nodes[3]->endDims) = y + sHeight;
				
			}
			
			int getIndex(const std::tuple<N, N>& start, const std::tuple<N, N>& end) const
			{
				N xMid = (std::get<0>(startDims) + std::get<0>(endDims))/2;
				N yMid = (std::get<1>(startDims) + std::get<1>(endDims))/2;
				
				bool right = (std::get<0>(start) > xMid);
				bool left = (std::get<0>(end) <= xMid);
				bool top = (std::get<1>(start) > yMid);
				bool bottom = (std::get<1>(end) <= yMid);
				
				if (top && right)
				{
					return 0;
				}
				else if (top && left)
				{
					return 1;
				}
				else if (bottom && left)
				{
					return 2;
				}
				else if (bottom && right)
				{
					return 3;
				}
				else
				{
					return -1;
				}
			}
			
			public:
			std::list<T*> entities;
			std::tuple<N, N> startDims;
			std::tuple<N, N> endDims;
			
			Node** nodes;
			
			Node(int index) : index(index), entities(), nodes(NULL)
			{
				
			}
			
			friend class SpatialTree;
		};
		
		
		Node* root;
		
		void test()
		{
			if (root == NULL)
			{
				root = new Node(0);
			}
			root->split();
		}
	};
	
}
}