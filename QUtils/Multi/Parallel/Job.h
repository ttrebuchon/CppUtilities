#pragma once
#include <functional>
#include <vector>
#include <condition_variable>

#include "Result.h"
#include "Dependency.h"

namespace QUtils
{
namespace Multi
{
	template <class Result_t>
	class AJob;
	
	namespace Helpers
	{
		template <class Return_t, class Arg_t>
		struct FunctionTypeArgHelper
		{ };
		
		template <class Return_t, class... Args>
		struct FunctionTypeArgHelper<Return_t, std::tuple<Args...>>
		{
			typedef std::function<Return_t(Args...)> type;
		};
		
		template <class>
		struct AJobResultExtractor
		{};
		
		template <class ...T>
		struct AJobResultExtractor<AJob<Result<T...>>>
		{
			typedef std::tuple<T...> type;
		};
	}
	
	
	
	
	class Job : public std::enable_shared_from_this<Job>
	{
		protected:
		std::vector<std::shared_ptr<Dependency>> _dependencies;
		std::vector<std::shared_ptr<Dependency>> _dependents;
		
		unsigned long rawPriority;
		
		std::vector<std::function<void()>> callbacks;
		
		std::condition_variable cond;
		
		std::shared_ptr<std::exception> ex;
		
		public:
		Job(unsigned long priority) : _dependencies(), _dependents(), rawPriority(priority), callbacks(), cond(), ex(NULL) {}
		Job() : Job(1) {}
		
		virtual ~Job() {}
		
		virtual bool running() const = 0;
		virtual unsigned long priority() const = 0;
		virtual void depends(std::shared_ptr<Job>);
		
		virtual const std::vector<std::shared_ptr<Dependency>>& dependencies() const;
		
		virtual const std::vector<std::shared_ptr<Dependency>>& dependents() const;
		
		virtual std::vector<std::shared_ptr<const Job>> previousJobs() const;
		
		virtual std::vector<std::shared_ptr<Job>> previousJobs();
		
		void addCallback(std::function<void()>);
		
		virtual void wait();
		
		virtual std::shared_ptr<const std::exception> exception() const;
		
	};
	
	
}
}