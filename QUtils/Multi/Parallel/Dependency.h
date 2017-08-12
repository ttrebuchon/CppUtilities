#pragma once

namespace QUtils
{
namespace Multi
{
	class Job;
	
	class Dependency
	{
		private:
		std::shared_ptr<Job> _parent;
		std::shared_ptr<Job> _child;
		
		public:
		Dependency(std::shared_ptr<Job> child, std::shared_ptr<Job> parent) : _parent(parent), _child(child) {}
		
		std::shared_ptr<const Job> parent() const
		{
			return _parent;
		}
		std::shared_ptr<const Job> child() const
		{
			return _child;
		}
		
		std::shared_ptr<Job> parent()
		{
			return _parent;
		}
		std::shared_ptr<Job> child()
		{
			return _child;
		}
	};
}
}