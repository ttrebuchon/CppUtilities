#include "../Tests.h"
#include <Math/Matrix.h>
#include <Math/Matrix_Algs.h>

#include <Stopwatch/Stopwatch.h>

#include <boost/multiprecision/cpp_dec_float.hpp>

using boost::multiprecision::cpp_dec_float;
using boost::multiprecision::number;

using namespace Utils;
using namespace Math;

template <typename T>
void printM(T** M, int N)
{
	for (int k = 0; k < N; k++)
	{
	std::cout << "[";
	for (int i = 0; i < N-1; i++)
	{
		std::cout << M[k][i] << ", ";
	}
	std::cout << M[k][N-1] << "]" << std::endl;
	}
	std::cout << "\n";
}

template <typename T>
void printV(T* V, int N)
{
	for (int i = 0; i < N; i++) {
		std::cout << "[" << V[i] << "]\n";
	}
	std::cout << std::endl;
}

template <typename T>
T** allocArr(int N, T init = 0)
{
	T** M = new T*[N];
	for (int i = 0; i < N; i++)
	{
		M[i] = new T[N];
		for (int j = 0; j < N; j++)
		{
			M[i][j] = init;
		}
	}
	
	return M;
}


bool Testing::Matrix_Algs()
{
	typedef double Num;
	//typedef number<cpp_dec_float<14368>> Num;
	
	
	
	int N = 3;
	Num** M = allocArr<Num>(N);
	
	M[0][0] = 1;
	M[0][1] = 2;
	M[0][2] = 3;
	
	M[1][0] = 0;
	M[1][1] = 1;
	M[1][2] = 4;
	
	M[2][0] = 5;
	M[2][1] = 6;
	M[2][2] = 0;
	
	printM(M, N);
	
	std::function<Num*&(Num**, int)> getM = [](Num** m, int i) ->Num*&
	{
		return m[i];
	};
	
	std::function<Num&(Num*, int)> getV = [](Num* v, int i) ->Num&
	{
		return v[i];
	};
	
	Num* P = new Num[N+1];
	
	
	Num** R = new Num*[N];
	
	for (int i = 0; i < N; i++)
	{
		R[i] = new Num[N];
	}
	
	Utils::Math::Algorithms::LUP<Num**, Num*, Num, int> LUP;
	LUP.getM = getM;
	LUP.getV = getV;
	LUP.Decompose(M, R, P, N, 0.1);
	
	printM(R, N);
	
	
	
	Num** I = new Num*[N];
	
	for (int i = 0; i < N; i++)
	{
		I[i] = new Num[N];
	}
	
	LUP.Invert(R, P, N, I);
	
	printM(I, N);
	
	dout << "Det: " << std::flush << LUP.Determinant(R, P, N) << std::endl;
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	tensor_t<2, Num> M2 = {{1, 2, 3}, {0, 1, 4}, {5, 6, 0}};
	
	
	
	dout << M2.toString() << "\n" << std::endl;
	
	tensor_t<1, Num> P2 = new DataMatrix<1, Num>();
	P2.setSize(0, N+1);
	
	
	
	
	
	
	tensor_t<2, Num> R2 = new DataMatrix<2, Num>();
	R2.setSize(0, N);
	R2.setSize(1, N);
	
	
	
	std::function<tensor_t<1, Num>&(tensor_t<2, Num>, int)> getM2 = [](tensor_t<2, Num> m, int i) -> tensor_t<1, Num>&
	{
		return m(i);
	};
	
	std::function<Num&(tensor_t<1, Num>, int)> getV2 = [](tensor_t<1, Num> v, int i) -> Num&
	{
		return v(i);
	};
	
	
	
	Algorithms::LUP<tensor_t<2, Num>, tensor_t<1, Num>, Num, int> LUP2;
	LUP2.getM = getM2;
	LUP2.getV = getV2;
	LUP2.Decompose(M2, R2, P2, N, 0.1);
	
	
	
	dout << R2.toString() << "\n" << std::endl;
	dout << P2.toString() << std::endl;
	
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			assert_ex(R2(i, j) == R[i][j]);
		}
		assert_ex(P[i] == P2[i]);
	}
	assert_ex(P[N] == P2[N]);
	
	tensor_t<2, Num> I2 = new DataMatrix<2, Num>();
	I2.setSize(0, N);
	I2.setSize(1, N);
	
	LUP2.Invert(R2, P2, N, I2);
	
	dout << I2.toString() << "\n" << std::endl;
	
	
	
	
	
	int N2 = 100;
	
	
	
	Utils::Stopwatch sw;
	tensor_t<2, Num> largeMat = new FuncMatrix<2, Num>([](int i, int j) {return (i*2) + j + 1;});
	largeMat.setSize(0, N2);
	largeMat.setSize(1, 2);
	
	largeMat = largeMat.contract(largeMat.T());
	
	
	
	
	sw.start();
	Algorithms::LUP<tensor_t<2, Num>, tensor_t<1, Num>, Num, int> LUP2_1;
	LUP2_1.getM = getM2;
	LUP2_1.getV = getV2;
	tensor_t<2, Num> largeMatR = new DataMatrix<2, Num>();
	largeMatR.setSize(0, N2);
	largeMatR.setSize(1, N2);
	tensor_t<1, Num> largeP = new DataMatrix<1, Num>();
	largeP.setSize(0, N2+1);
	LUP2_1.Decompose(largeMat, largeMatR, largeP, N2, 0.1);
	auto timedDet = LUP2_1.Determinant(largeMatR, largeP, N2);
	sw.stop();
	
	auto LUPTime = sw.value();
	
	dout << "LUP Done: " << LUPTime << std::endl;
	
	sw.reset();
	
	sw.start();
	auto manTimedDet = largeMat.det();
	sw.stop();
	auto manTime = sw.value();
	
	dout << "Values: {Manual, LUP} = {" << manTimedDet << ", " << timedDet << "}\n";
	
	dout << "Times: {Manual, LUP} = {" << manTime << ", " << LUPTime << "}" << std::endl;
	
	
	
	return true;
}