#include <iostream>
#include <array>
#include <vector>
#include <limits>
#include <math.h>

#include "GreatBin.cpp"

int main(int argc, char* argv[]) {
  if(argc != 3){std::cout << "zu wenig argumente " << std::endl; return 1;}

  int val1 = std::stol(argv [1]);
  int val2 = std::stol(argv [2]);
  int max = std::numeric_limits<int>::max();
  //long min = std::numeric_limits<long>::min();

  GreatBin bin1 {1,1};
  GreatBin bin2 {1,1};
  GreatBin bin3 {bin1.mul(bin2)};

  int N = val1;
  for (int i = 0; i < N; i++) {
    bin3 = bin1.add(bin2);
    bin3.print_chunks();
    bin1 = bin2;
    bin2 = bin3;
  }
  //GreatBin bin4 = bin3.mul(bin1);

  //GreatBin bin4 {bin3.digitshift(2)};

  return 0;
}
