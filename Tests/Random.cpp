#include "../Tests_Helpers.h"
#include <QUtils/Random.h>
#include <QUtils/Types/CompilerPrint.h>

DEF_TEST(Random)
{
	using QUtils::Random;
	
	
	dout << (int)Random::Get() << "\n";
	dout << (int)Random::Get() << "\n";
	dout << "Setting seed to 0...\n";
	Random::Seed(0);
	dout << Random::Get() << "\n";
	dout << "Randomly Seeding With: " << Random::RandomSeed() << "\n";
	dout << static_cast<long>(Random::Get()) << "\n";
	
	dout << "\n\n";
	
	dout << "Range: [" << Random::Min() << ", " << static_cast<long>(Random::Max()) << "]\n";
	static_assert(Random::Min() == std::numeric_limits<Random::result_type>::min(), "");
	
	
	using namespace QUtils::Types;
	std::default_random_engine eng;
	PrintTypes<decltype(eng())>(dout) << "\n\n";
	
	
	
	{
		Random::Seed(0);
		double x = Random::GetAs<double>();
		Random::Seed(0);
		assert_ex(x == Random::Get());
	}
	
	return true;
}