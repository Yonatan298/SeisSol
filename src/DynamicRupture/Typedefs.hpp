#ifndef DR_TYPEDEFS
#define DR_TYPEDEFS

#include "DynamicRupture/Misc.h"
#include "Kernels/precision.hpp"
#include <Eigen/Dense>

namespace seissol::dr {

/**
 * Stores the different types of friction laws
 * The values resemble the identifiers used in the old fortran implementation
 */
enum class FrictionLawType : unsigned int {
  NoFault = 0,
  LinearSlipWeakening = 2,
  LinearSlipWeakeningBimaterial = 6,
  LinearSlipWeakeningForcedRuptureTime = 16,
  RateAndStateAgingLaw = 3,
  RateAndStateSlipLaw = 4,
  RateAndStateFastVelocityWeakening = 103,
  ImposedSlipRatesYoffe = 33,
  ImposedSlipRatesGaussian = 34,
  RateAndStateVelocityWeakening = 7,
  RateAndStateAgingNucleation = 101,
};

/**
 * Stores the P and S wave impedances for an element and its neighbor as well as the eta values from
 * Uphoff equation (4.51)
 */
struct ImpedancesAndEta {
  real zp, zs, zpNeig, zsNeig, etaP, etaS, invEtaS, invZp, invZs, invZpNeig, invZsNeig;
};

/**
 * Stores the impedance matrices for an element and its neighbor for a poroelastic material.
 * This generalizes equation (4.51) from Carsten's thesis
 */
struct ImpedanceMatrices {
  // TODO replace by storage for yateto matrix
  using Matrix44 = Eigen::Matrix<double, 4, 4>;
  Matrix44 impedance;
  Matrix44 impedanceNeig;
  Matrix44 eta;
};

/**
 * Struct that contains all input stresses
 * normalStress in direction of the face normal, traction1, traction2 in the direction of the
 * respective tangential vectors
 */
struct FaultStresses {
  real normalStress[CONVERGENCE_ORDER][misc::numPaddedPoints] = {{}};
  real traction1[CONVERGENCE_ORDER][misc::numPaddedPoints] = {{}};
  real traction2[CONVERGENCE_ORDER][misc::numPaddedPoints] = {{}};
  real fluidPressure[CONVERGENCE_ORDER][misc::numPaddedPoints] = {{}};
};

/**
 * Struct that contains all traction results
 * traction1, traction2 in the direction of the respective tangential vectors
 */
struct TractionResults {
  real traction1[CONVERGENCE_ORDER][misc::numPaddedPoints] = {{}};
  real traction2[CONVERGENCE_ORDER][misc::numPaddedPoints] = {{}};
};

} // namespace seissol::dr

#endif
