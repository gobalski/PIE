#ifndef GB_MATH_HPP
#define GB_MATH_HPP

#include "GreatBinExp.hpp"

struct GB_math {
  // Calculates the n-th Factorial
  static GreatBin fac (GreatBin&);
  static GreatBin fac (int);

  // Calculates 1/GreatBin with given precision.
  static GreatBinExp reziproc (const GreatBin&, int);

  // Calculates Eulers number with given precision.
  static GreatBinExp E (int);

  // Calculates PI with given precision.
  static GreatBinExp PI (int);
};

#endif
