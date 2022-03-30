#include <iostream>
#include <array>
#include <vector>
#include <limits>
#include <math.h>

#include "GreatBin.cpp"
#include "GB_math.cpp"

int main(int argc, char* argv[]) {

  int max = std::numeric_limits<int>::max();
  // std::cout << "max: " << max << "\n";
  // long min = std::numeric_limits<long>::min();

  GreatBin TEN {10};

  std::vector<int> inp_digits;
  for (int i =1; i < argc; i++){
    inp_digits.push_back(std::stoi(argv[i]));
  }
  GreatBin inp {inp_digits};

  GreatBin factorial = GB_Math::fac( inp );

  factorial.print_digits(std::cout) ;
  std::cout << "\n";
  std::cout << factorial << std::endl;


  return 0;
}
