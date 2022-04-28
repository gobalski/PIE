#include <iostream>
#include <array>
#include <vector>
#include <limits>
#include <math.h>

#include "GB_math.hpp"
#include "GreatBin.hpp"
#include "GreatBinExp.hpp"

int main(int argc, char* argv[]) {
  using std::cout;
  using std::endl;

  int precision = std::stoi(argv[1]);

  cout << "summing factorials..\n";

  GreatBinExp euler = GB_math::E(precision);

  cout << "converting to decimal..\n";
  cout << "Eulers Number: \n" << euler << endl;

  cout << "summing other factorials..\n";

  GreatBinExp pi = GB_math::PI(precision);

  cout << "converting to decimal..\n";
  cout << "Pi: \n" << pi << endl;

  return 0;
}
