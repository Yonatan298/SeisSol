#ifndef SEISSOL_MATH_H
#define SEISSOL_MATH_H

#define DR_AS_QUADRATURE 0
#define DR_AS_CELLAVERAGE 1

#include <stdexcept>
#include <cmath>

namespace seissol::dr::aux {
template <int DrMethod>
constexpr int numGaussPoints2d(const int Order) {
  throw std::runtime_error("unknown Dynamic Rupture method");
  return -1;
}

template <>
constexpr int numGaussPoints2d<DR_AS_QUADRATURE>(const int Order) {
  return std::pow(Order + 1, 2);
}

struct CellAveragePrecomputed {
  // Precomputed values according to:
  // numberOfPoints = int(4**math.ceil(math.log(order*(order+1)/2,4)))
  constexpr static int NumberOfPoints[10] = {1, 4, 16, 16, 16, 64, 64, 64, 64, 64};

  constexpr static int getNumPoints(int Order) { return NumberOfPoints[Order]; }
};

template <>
constexpr int numGaussPoints2d<DR_AS_CELLAVERAGE>(const int Order) {
  return CellAveragePrecomputed::getNumPoints(Order);
}
} // namespace seissol::dr::aux

#endif // SEISSOL_MATH_H