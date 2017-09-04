#include <QUtils/Math/Matrix.h>

namespace QUtils
{
namespace Math
{
template class Matrix<3, double, int>;
template class Matrix<2, double, int>;
template class Matrix<1, double, int>;

template class tensor_t<3, double, int>;
template class tensor_t<2, double, int>;
template class tensor_t<1, double, int>;

template class FuncMatrix<3, double, int>;
template class FuncMatrix<2, double, int>;
template class FuncMatrix<1, double, int>;

template class DataMatrix<3, double, int>;
template class DataMatrix<2, double, int>;
template class DataMatrix<1, double, int>;
}
}