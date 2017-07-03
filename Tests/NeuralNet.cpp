#include "../Tests_Helpers.h"

#include <QUtils/NeuralNet/NeuralNet.h>
#include <sstream>
#include <limits>
//#include <boost/multiprecision/cpp_dec_float.hpp>

using Utils::NeuralNet::Net;
//using boost::multiprecision::cpp_dec_float;
//using boost::multiprecision::number;

template <typename T>
T recipricoal(T t)
{
	T t1 = 1;
	return t1/t;
}
template <typename T>
T invSigmoid(T x)
{
	return -1*log(recipricoal<T>(x) - 1);
}

template <typename T>
T invSigmoid_D(T x)
{
	return recipricoal<T>(x - x*x);
}


auto outF(auto f, auto str)
{
	return [=] (auto x)
	{
		dout << str << ": " << x << "\t";
		auto res = f(x);
		dout << res << std::endl;
		return res;
	};
}

template <typename T>
std::string vPrint(const std::vector<T>& v)
{
	std::stringstream ss;
	if (v.size() <= 0)
	{
		return "< >";
	}
	ss << "< " << v[0];
	for (auto i = 1; i < v.size(); i++)
	{
		ss << ", " << v[i];
	}
	ss << " >";
	return ss.str();
}

bool Mult_Test();

bool Neural_Run()
{
	
	/* Example Activation Functions */
	
	// auto bin_A = [] (auto x) {
	// 	if (x >= 1)
	// 		return 1;
	// 	return 0;
	// };
	
	// auto bin_D = [] (auto x) {
	// 	return 0;
	// };
	
	auto invSig_A= [] (auto x) {
		return invSigmoid<decltype(x)>(x);
	};
	
	auto invSig_D = [] (auto x) {
		return invSigmoid_D<decltype(x)>(x);
	};

	
	
	
	
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
	
	nn.grow(layers, multiplier, Utils::NeuralNet::LayerType::Unique);
	for (int i = 0; i < cycles; i++)
	{
		dout << "Training " << i*progressInterval << "\t/" << cycles*progressInterval << std::endl;
		nn.train(progressInterval);
	}
	
	auto result = nn.go({0, 0});
	dout << "Result for {0, 0}: " << vPrint(result) << std::endl;
	
	auto result2 = nn.go({0, 1});
	dout << "Result for {0, 1}: " << vPrint(result2) << std::endl;
	
	auto result3 = nn.go({1, 0});
	dout << "Result for {1, 0}: " << vPrint(result3) << std::endl;
	
	auto result4 = nn.go({1, 1});
	dout << "Result for {1, 1}: " << vPrint(result4) << std::endl;
	
	//typedef number<cpp_dec_float<10>> Precise;
	typedef double Precise;
	Precise x = 1;
	x *= 4;
	x = invSig_A(x);
	x = invSig_D(x);
	
	Net<Precise> nn2(2, 1);
	//nn2.setOutputActivation(invSig_A, invSig_D);
	//nn2.addData({0, 0}, {0});
	nn2.addData({0, 1}, {1});
	nn2.addData({1, 0}, {1});
	//nn2.addData({1, 1}, {2});
	nn2.addData({2, 1}, {3});
	nn2.addData({1, 2}, {3});
	nn2.grow(layers, multiplier, Utils::NeuralNet::LayerType::FullyConnected);

	nn2.bounds.min = 0;
	
	for (int i = 0; i < cycles; i++)
	{
		nn2.learningRate = 0.5*(1 - static_cast<Precise>(i)/cycles);
		dout << "Training " << i*progressInterval << "\t/" << cycles*progressInterval << std::endl;
		nn2.train(progressInterval);
	}
	
	auto result_2 = nn2.go({0, 0});
	dout << "Result for {0, 0}: " << vPrint(result_2) << std::endl;
	
	auto result2_2 = nn2.go({0, 1});
	dout << "Result for {0, 1}: " << vPrint(result2_2) << std::endl;
	
	auto result3_2 = nn2.go({1, 0});
	dout << "Result for {1, 0}: " << vPrint(result3_2) << std::endl;
	
	auto result4_2 = nn2.go({1, 1});
	dout << "Result for {1, 1}: " << vPrint(result4_2) << std::endl;
	
	auto result5_2 = nn2.go({2, 1});
	dout << "Result for {2, 1}: " << vPrint(result5_2) << std::endl;
	
	auto result6_2 = nn2.go({1, 2});
	dout << "Result for {1, 2}: " << vPrint(result6_2) << std::endl;
	
	
	
	return Mult_Test();
}

bool Mult_Test()
{
	Net<double> n(2, 1);
	n.addData({1, 0}, {0});
	n.addData({0, 0}, {0});
	n.addData({0, 1000}, {0});
	n.addData({1000, 0}, {0});
	n.addData({1, 1}, {1});
	n.addData({-1, 1}, {-1});
	n.addData({-1, -1}, {1});
	n.addData({1, 3}, {3});
	n.addData({2, 3}, {6});
	n.addData({6, 4}, {24});
	
	
	
	
	
	auto prodN = new Utils::NeuralNet::Neurons::ProductNeuron<double>();
	
	
	auto ins = n.inputLayer();
	for (auto in : ins)
	{
		assert_ex(in->getOuts().size() == 0);
	}
	
	auto outputs = n.outputLayer();
	prodN->addDown(outputs[0], 1);
	for (auto in : ins)
	{
		assert_ex(in->getAllDown().size() == 0);
		assert_ex(in->getOuts().size() == 0);
	}
	
	
	for (auto in : ins)
	{
		prodN->addUp(in, 1);
		
		
		
		assert_ex(in->getAllDown().size() == 2);
		assert_ex(in->getOuts().size() == 1);
	}
	
	
	assert_ex(prodN->getIns().size() == 2);
	assert_ex(outputs[0]->getIns().size() == 1);
	
	
	
	
	
	dout << n.toString() << std::endl;
	for (int i = 0; i < 10; i++)
	{
	n.train(1);
	dout << "Training done" << std::endl;
	dout << n.toString() << std::endl;
	}
	n.train(4);
	dout << "Training done" << std::endl;
	dout << n.toString() << std::endl;
	
	auto r1_3 = n.go({1, 3});
	dout << "Result for <1,3>:  " << vPrint(r1_3) << std::endl;
	
	return true;
}