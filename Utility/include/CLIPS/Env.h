#include <Clips/clips.h>
#include <string>
#include <vector>
#include <map>
#include <memory>

namespace Clips
{
	
	class Fact;

	class Environment
	{
		private:
		void* env;
		static std::map<void*, int> use_counts;
		std::map<int, std::shared_ptr<Fact>> _facts;
		public:
		Environment();
		Environment(const Environment&) = delete;
		~Environment();


		void clear();
		void reset();
		bool build(const std::string);
		
		std::vector<std::string> facts() const;

		std::shared_ptr<Fact> assert_f(const std::string);
		
		int run(int runlimit);

		bool watch(const std::string);

		Environment& operator=(const Environment&);


		std::vector<std::string> evaluate(const std::string);
	};
	
	
	
	
}