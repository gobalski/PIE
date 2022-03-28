#include <iostream>
#include <array>
#include <vector>
#include <limits>
#include <math.h>

#include "GreatBin.cpp"

int main(int argc, char* argv[]) {
  if(argc != 3){std::cout << "zu wenig argumente " << std::endl; return 1;}

  int val1 = std::stoi(argv [1]);
  int val2 = std::stoi(argv [2]);
  int max = std::numeric_limits<int>::max();
  //long min = std::numeric_limits<long>::min();

  GreatBin bin1 {val1};
  GreatBin bin2 {val2};
  GreatBin max_bin {max};
  std::cout << "bin1 and bin2 \n";
  bin1.print_chunks();
  bin2.print_chunks();

  std::pair<GreatBin,GreatBin> div_pair {bin1.div(bin2)};
  std::cout << " bin1 / bin2 = \n";
  div_pair.first.print_chunks();
  div_pair.second.print_chunks();

  GreatBin bin4 {bin1.mul(bin2)};
  std::cout << " bin1 * bin2 = \n";
  bin4.print_chunks();

  return 0;
}
