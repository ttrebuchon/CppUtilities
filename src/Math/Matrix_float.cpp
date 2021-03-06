#include <QUtils/Math/Matrix.h>

namespace QUtils
{
namespace Math
{



template class Matrix<3, float, int>;
template class Matrix<2, float, int>;
template class Matrix<1, float, int>;

template class tensor_t<3, float, int>;
template class tensor_t<2, float, int>;
template class tensor_t<1, float, int>;

template class FuncMatrix<3, float, int>;
template class FuncMatrix<2, float, int>;
template class FuncMatrix<1, float, int>;

template class DataMatrix<3, float, int>;
template class DataMatrix<2, float, int>;
template class DataMatrix<1, float, int>;
}
}