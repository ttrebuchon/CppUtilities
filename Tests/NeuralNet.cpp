#include "../Tests.h"

#include <NeuralNet/NeuralNet.h>

using Utils::NeuralNet::Net;

bool Testing::Neural()
{
	Net<long double> nn(2, 1);
	nn.addData({0, 0}, {0});
	nn.addData({0, 1}, {1});
	nn.addData({1, 0}, {1});
	nn.addData({1, 1}, {0});
	
	const int layers = 1;
	const int multiplier = 1;
	const int cycles = 1000000;
	
	const int progressInterval = 10000;
	
	nn.grow(layers, multiplier);
	for (int i = 0; i < cycles/progressInterval; i++)
	{
		dout << "Training " << i*progressInterval << "\t/" << cycles << std::endl;
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
	
	
	return true;
}