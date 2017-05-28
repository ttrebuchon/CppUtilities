#pragma once



namespace Utils
{
namespace Math
{
namespace Algorithms
{
	template <typename M_t, typename V_t, typename Elem, typename Index>
	struct LUP {
		
		std::function<V_t&(M_t, Index)> getM;
		std::function<Elem&(V_t, Index)> getV;
		
		
		
		
		
		bool Decompose(M_t M, M_t& A, V_t& P, Index N, Elem tolerance)
	{
		
		auto getV = this->getV;
		auto getM = this->getM;
		auto getE = [getV, getM] (M_t m, Index i, Index j) -> Elem&
		{
			return getV(getM(m, i), j);
		};
		
		
		for (Index i = 0; i < N; i++)
		{
			for (Index j = 0; j < N; j++)
			{
				getE(A, i, j) = getE(M, i, j);
			}
		}
		
		
		
		for (Index i = 0; i <= N; i++)
		{
			getV(P, i) = i;
		}
		
		Elem maxA;
		Elem absA;
		Index imax;
		
		auto eabs = [] (Elem e) -> Elem
		{
			if (e >= 0)
			{
				return e;
			}
			return e*-1;
		};
		
		for (Index i = 0; i < N; i++)
		{
			maxA = 0.0;
			imax = i;
			
			
			//Find the largest number in column i, in the lower left triangle
			//Set imax to the row index of this value
			for (Index k = i; k < N; k++)
			{
				if ((absA = eabs(getE(A, k, i))) > maxA)
				{
					maxA = absA;
					imax = k;
				}
			}
			
			if (maxA < tolerance) return false; //failure, matrix is degenerate
			
			if (imax != i)
			{
				//pivoting P
				Index j = getV(P, i);
				getV(P, i) = getV(P, imax);
				getV(P, imax) = j;
				
				//pivoting rows of A
				auto ptr = getM(A, i);
				getM(A, i) = getM(A, imax);
				getM(A, imax) = ptr;
				
				//counting pivots starting from N (for determinant)
				getV(P, N)++;
				
			}
			
			for (Index j = i + 1; j < N; j++)
			{
				getE(A, j, i) /= getE(A, i, i);
				
				for (Index k = i + 1; k < N; k++)
				{
					getE(A, j, k) -= getE(A, j, i) * getE(A, i, k);
				}
			}
		}
		
		
		
		return true;
	}
	
	
	
	/* INPUT: A,P filled in LUPDecompose; b - rhs vector; N - dimension
 * OUTPUT: x - solution vector of A*x=b
 */
	void Solve(const M_t& A, const V_t& P, const V_t& b, const Index N, V_t& x)
	{
		auto getV = this->getV;
		auto getM = this->getM;
		auto getE = [getV, getM] (M_t m, Index i, Index j) -> Elem&
		{
			return getV(getM(m, i), j);
		};
		
		
		for (Index i = 0; i < N; i++)
		{
			getV(x, i) = getV(b, getV(P, i));
			
			for (Index k = 0; k < i; k++)
			{
				getV(x, i) -= getE(A, i, k) * getV(x, k);
			}
		}
		
		for (Index i = N - 1; i >= 0; i--)
		{
			for (Index k = i + 1; k < N; k++)
			{
				getV(x, i) -= getE(A, i, k) * getV(x, k);
			}
			
			getV(x, i) = getV(x, i) / getE(A, i, i);
		
		}
	}
	

/* INPUT: A,P filled in LUPDecompose; N - dimension
 * OUTPUT: IA is the inverse of the initial matrix
 */
	void Invert(const M_t& A, const V_t& P, const Index N, M_t& IA)
	{
		auto getV = this->getV;
		auto getM = this->getM;
		auto getE = [getV, getM] (M_t m, Index i, Index j) -> Elem&
		{
			return getV(getM(m, i), j);
		};
		
		
		for (Index j = 0; j < N; j++)
		{
			for (Index i = 0; i < N; i++)
			{
				if (getV(P, i) == j)
				{
					getE(IA, i, j) = 1.0;
				}
				else
				{
					getE(IA, i, j) = 0.0;
				}
				
				for (Index k = 0; k < i; k++)
				{
					getE(IA, i, j) -= getE(A, i, k) * getE(IA, k, j);
				}
			}
			
			for (Index i = N - 1; i >= 0; i--)
			{
				for (Index k = i + 1; k < N; k++)
				{
					getE(IA, i, j) -= getE(A, i, k) * getE(IA, k, j);
				}
				
				getE(IA, i, j) = getE(IA, i, j) / getE(A, i, i);
			}
		}
	}

/* INPUT: A,P filled in LUPDecompose; N - dimension. 
 * OUTPUT: Function returns the determinant of the initial matrix
 */
	Elem Determinant(const M_t& A, const V_t& P, int N)
	{
		auto getV = this->getV;
		auto getM = this->getM;
		auto getE = [getV, getM] (M_t m, Index i, Index j) -> Elem&
		{
			return getV(getM(m, i), j);
		};
		
		Elem det = getE(A, 0, 0);
		
		for (Index i = 1; i < N; i++)
		{
			det *= getE(A, i, i);
		}
		
		if (((Index)(getV(P, N) - N)) % 2 == 0)
		{
			return det;
		}
		else
		{
			return -det;
		}
	}
	
	
	
	
	
	};
	
}
}
}