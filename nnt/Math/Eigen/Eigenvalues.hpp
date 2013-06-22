#ifndef EIGEN_EIGENVALUES_MODULE_H
#define EIGEN_EIGENVALUES_MODULE_H

#include "Core.hpp"

#include "src/Core/util/DisableStupidWarnings.h"

#include "Cholesky.hpp"
#include "Jacobi.hpp"
#include "Householder.hpp"
#include "LU.hpp"

namespace Eigen {

/** \defgroup Eigenvalues_Module Eigenvalues module
  *
  *
  *
  * This module mainly provides various eigenvalue solvers.
  * This module also provides some MatrixBase methods, including:
  *  - MatrixBase::eigenvalues(),
  *  - MatrixBase::operatorNorm()
  *
  * \code
  * #include <Eigen/Eigenvalues>
  * \endcode
  */

#include "src/Eigenvalues/Tridiagonalization.h"
#include "src/Eigenvalues/RealSchur.h"
#include "src/Eigenvalues/EigenSolver.h"
#include "src/Eigenvalues/SelfAdjointEigenSolver.h"
#include "src/Eigenvalues/GeneralizedSelfAdjointEigenSolver.h"
#include "src/Eigenvalues/HessenbergDecomposition.h"
#include "src/Eigenvalues/ComplexSchur.h"
#include "src/Eigenvalues/ComplexEigenSolver.h"
#include "src/Eigenvalues/MatrixBaseEigenvalues.h"

} // namespace Eigen

#include "src/Core/util/ReenableStupidWarnings.h"

#endif // EIGEN_EIGENVALUES_MODULE_H
/* vim: set filetype=cpp et sw=2 ts=2 ai: */
