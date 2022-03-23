#include <vector>

struct GreatBin {
  int CHUNK_NO;
  std::vector<long long> chunks_;
  GreatBin(const int CHUNK_NO);
  virtual ~GreatBin();

};
