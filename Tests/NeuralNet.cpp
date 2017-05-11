#include "../Tests.h"

#include <NeuralNet/NeuralNet.h>
#include <boost/multiprecision/cpp_dec_float.hpp>

using Utils::NeuralNet::Net;
using boost::multiprecision::cpp_dec_float;
using boost::multiprecision::number;

bool Testing::Neural()
{
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
	
	/* Example Activation Functions */
	
	auto bin_A = [] (auto x) {
		if (x >= 1)
			return 1;
		return 0;
	};
	
	auto bin_D = [] (auto x) {
		return 0;
	};
	
#pragma GCC diagnostic pop
	
	
	
	
	Net<long double> nn(2, 1);
	nn.bounds.min = 0;
	nn.bounds.max = 1;
	nn.addData({0, 0}, {0});
	nn.addData({0, 1}, {1});
	nn.addData({1, 0}, {1});
	nn.addData({1, 1}, {0});
	
	const int layers = 2;
	const double multiplier = 2;
	int cycles = 10;
	
	int progressInterval = 1000;
	
	nn.grow(layers, multiplier);
	for (int i = 0; i < cycles; i++)
	{
		dout << "Training " << i*progressInterval << "\t/" << cycles*progressInterval << std::endl;
		nn.train(progressInterval);
	}
	
	auto result = nn.go({0, 0});
	dout << "Result for {0, 0}: " << result.toString() << std::endl;
	
	auto result2 = nn.go({0, 1});
	dout << "Result for {0, 1}: " << result2.toString() << std::endl;
	
	auto result3 = nn.go({1, 0});
	dout << "Result for {1, 0}: " << result3.toString() << std::endl;
	
	auto result4 = nn.go({1, 1});
	dout << "Result for {1, 1}: " << result4.toString() << std::endl;
	
	//typedef number<cpp_dec_float<10>> Precise;
	typedef double Precise;
	Precise x = 1;
	x *= 4;
	
	Net<Precise> nn2(2, 1);
	nn2.addData({0, 0}, {0});
	nn2.addData({0, 1}, {1});
	nn2.addData({1, 0}, {1});
	nn2.addData({1, 1}, {2});
	nn2.addData({2, 1}, {3});
	nn2.addData({1, 2}, {3});
	nn2.grow(layers, multiplier);

	nn2.bounds.min = 0;
	
	for (int i = 0; i < cycles; i++)
	{
		dout << "Training " << i*progressInterval << "\t/" << cycles*progressInterval << std::endl;
		nn2.train(progressInterval);
	}
	
	auto result_2 = nn2.go({0, 0});
	dout << "Result for {0, 0}: " << result_2.toString() << std::endl;
	
	auto result2_2 = nn2.go({0, 1});
	dout << "Result for {0, 1}: " << result2_2.toString() << std::endl;
	
	auto result3_2 = nn2.go({1, 0});
	dout << "Result for {1, 0}: " << result3_2.toString() << std::endl;
	
	auto result4_2 = nn2.go({1, 1});
	dout << "Result for {1, 1}: " << result4_2.toString() << std::endl;
	
	auto result5_2 = nn2.go({2, 1});
	dout << "Result for {2, 1}: " << result5_2.toString() << std::endl;
	
	auto result6_2 = nn2.go({1, 2});
	dout << "Result for {1, 2}: " << result6_2.toString() << std::endl;
	
	
	
	return true;
}