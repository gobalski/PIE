#include <iostream>
#include <array>
#include <vector>
#include <limits>
#include <math.h>

#include "GreatBin.hpp"
#include "GB_math.hpp"

int main(int argc, char* argv[]) {
  using std::cout;
  using std::endl;

  int max = std::numeric_limits<int>::max();
  // cout << "max: " << max << "\n";
  // long min = std::numeric_limits<long>::min();

  GreatBin TEN {10};

  std::vector<int> inp_digits;
  for (int i =1; i < argc; i++){
    inp_digits.push_back(std::stoi(argv[i]));
  }
  GreatBin inp {inp_digits};


  int prec {20};

  GreatBin inv_inp { GB_math::reziproc(inp, prec) };

  cout << "precision: " << prec << "\n\n";

  cout << " BASE 2^31 \n";
  cout << " 1 / ";
  inp.print_digits(cout);
  cout << " = " ;
  inv_inp.print_digits(cout);
  cout << "\n\n";

  cout << " BASE 10 \n";
  cout << " 1 / " << inp << " = " << inv_inp << endl;


  return 0;
}
